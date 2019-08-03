//******************************************************************
//
//  battle_client.cc	
//
//  Author: Zach Tumbleson
//
//	Date: 3-23-2019
//
//	Brief: Implements the client side of the assignment
//		   given in the assignment 4 handout. The client
//		   allows each user to place a ship, sends the
//		   location to the server, and then plays a 
//		   simplified version of battleship.
//
//	Controls: Use arrow keys to move between squares.
//			  when placing your ship, press space to 
//			  select the starting square, then use the
//			  arrow keys to rotate the ship. When you are
//			  happy with the ship's configuration, press
//			  space again to submit its position to the server.
//
//			  When taking shots, move between squares with the
//			  arrow keys, and press space to submit the square
//			  as your move for that turn. The move will be marked
//			  as a hit or miss on the board. When one player gets
//		      3 hits, the game is over.
//
//	Note*: The client defined in this file and battle.h is largely based on the 
//		   code provided by Dr. Juedes in battle_example.cc and rsp_client.cc.
//
//*****************************************************************

#include <ncurses.h>
#include <iostream>
#include <vector>
#include <string>
#include <boost/asio.hpp>
#include "battle.h"
#include "rotate.h"
#include "client_helpers.h"
using namespace std;
using boost::asio::ip::tcp;

int main(int argc, char *argv[]) {
  int rows;
  int cols;
  int cur_row=0;
  int cur_col=0;
  int ch;
  bool placed = false;

  Direction orientation;
  
  //If ship is not rotated, ship's inital coordinates are (0, 0), (1, 1), (2, 2)
  nextShip ship;

  //Initialize the board as empty
  vector<vector<int> > my_board, opp_board;
  for (int i=0;i<4;i++) {
    vector<int> t;
    for (int j=0;j<4;j++) {
      t.push_back(0);
    }
    my_board.push_back(t);
    opp_board.push_back(t);
  }
  
  // Screen initialization

  initscr();
  // Clear the screen

  clear();

  // Get the size of the window!
  getmaxyx(stdscr,rows,cols);
  //remove warning
  rows++;
  
  cbreak();  // Pass all characters to this program!

  keypad(stdscr, TRUE); // Grab the special keys, arrow keys, etc.
  
  //***********************//
  //					   //
  // BEGIN SHIP PLACEMENT  //
  //					   //
  //***********************//
  
  // choose a square to place your ship
  // used to deal with escaping to choose a new square
placeShip: clear_board(my_board);
  draw_top_matrix(my_board, opp_board, 0, 0, placed);
  refresh();
  while ((ch = getch())!=' '){
    switch (ch) {
      case KEY_RIGHT:
      	cur_col++;
        	cur_col%=4;
        	draw_top_matrix(my_board, opp_board, cur_row,cur_col, placed);
        	// Redraw the screen.
        	refresh();
        	break;
      case KEY_LEFT:
      	cur_col--;
      	cur_col = (4+cur_col)%4;
      	draw_top_matrix(my_board, opp_board, cur_row,cur_col, placed);
      	// Redraw the screen.
      	refresh();
      	break;
      case KEY_UP:
        	cur_row--;
        	cur_row=(4+cur_row) % 4;
        	draw_top_matrix(my_board, opp_board, cur_row,cur_col, placed);
        
        	// paint_markers(rows,cols,10,cur_row,cur_col);
        	// Redraw the screen.
        	refresh();
        	break;
      case KEY_DOWN:
        	cur_row++;
        	cur_row%=4;
        	draw_top_matrix(my_board, opp_board, cur_row,cur_col, placed);
          // paint_markers(rows,cols,10,cur_row,cur_col);
        	// Redraw the screen.
        	refresh();
        	break;
      }
  }

  // place the ship on the my_board and get orientation
  orientation = place_ship(my_board, cur_row, cur_col, ship);
  draw_top_matrix(my_board, opp_board, cur_row, cur_col, placed);
  refresh();

  // Choose the orientation of the ship and confirm with " ".
  while((ch = getch())!=' '){
  	switch(ch){
  		case KEY_RIGHT:

  			do{
  				//rotate the ship right until a legal ship is found
  				ship = rotate_right(my_board, cur_row, cur_col, orientation);
  			} while(!is_legal(ship, (int)(my_board.size())));

  			//Place the rotated ship
  			clear_board(my_board);

  			my_board[ship.x1][ship.y1] = 1;
  			my_board[ship.x2][ship.y2] = 1;
  			my_board[ship.x3][ship.y3] = 1;

  	  	draw_top_matrix(my_board, opp_board, cur_row, cur_col, placed);
  	  	refresh();
  	  	break;
  	  case KEY_LEFT:
  	  	
  	  	do{
  	  		//rotate the ship left until a legal ship is found
  	  		ship = rotate_left(my_board, cur_row, cur_col, orientation);

  	  	} while(!is_legal(ship, (int)(my_board.size())));

  	  	//Place the rotated ship
  	  	clear_board(my_board);

  	  	my_board[ship.x1][ship.y1] = 1;
  	  	my_board[ship.x2][ship.y2] = 1;
  	  	my_board[ship.x3][ship.y3] = 1;

    		draw_top_matrix(my_board, opp_board, cur_row,cur_col, placed);
    		// Redraw the screen.
    		refresh();
    		break;
      case (char)(27):
        //restart first square selection
        goto placeShip;
        break;
  	}
  }

  //************************//
  //					              //
  //   END SHIP PLACEMENT   //
  //					              //
  //************************//


  //*****************************//
  //							               //
  //  README - Network messages  //
  //							               //
  //*****************************//
  //
  // All data sent via the network are stored as integers using the following encoding:
  //
  // Ship coordinates are sent as a 6 digit integer xxxxxx, where each digit is obtained
  // by multiplying the digit by 10^place. For example a ship placed at (0, 0), (1, 1), (2, 2)
  // would be sent via the network as 001122 or:
  //
  //	0 * 10^5 = 0
  //	0 * 10^4 = 0
  //	1 * 10^3 = 10000
  //	1 * 10^2 = 1000
  //	2 * 10^1 = 20
  //	2 * 10^0 = 2
  //
  // Adding: 0+0+10000+1000+20+2 = 001122 or 1122
  //
  // This value is then converted to a string to comply with boost buffers
  //
  // To decode this back into coordinates (ship struct used for organization), convert the string
  // an int and divide by decreasing powers of 10 and get the remainder in between each step:
  //
  // ship.x1 = 1122 / 100000 = 0
  // 1122 % 100000 = 1122
  // ship.y1 = 1122 / 10000 = 0
  // 1122 % 10000 = 1122
  // ship.x2 = 1122 / 1000 = 1
  // 1122 % 1000 = 122
  // ship.y2 = 122 / 100 = 1
  // 122 % 100 = 22
  // ship.x3 = 22 / 10 = 2
  // 22 % 10 = 2
  // ship.y3 = 2 / 1 = 2
  // 2 % 1 = 0
  //
  // Similarly, moves are sent as 2 digit integers using the same encoding scheme.
  //


  //************************//
  //                        //
  //      OPEN SOCKET       //
  //                        //
  //************************//

  // Read in server address and port number
  string server_address = argv[1];
  int port_number = atoi(argv[2]);

  // Standard boost code to connect to a server.
  // Comes from the boost tutorial
  boost::asio::io_service my_service;

  tcp::resolver resolver(my_service);
  // Find the server/port number.
  // tcp::resolver::results_type endpoints = resolver.resolve(argv[2], argv[3]);

  tcp::socket socket(my_service);

  socket.connect(tcp::endpoint(boost::asio::ip::address::from_string(server_address),port_number));

  //Convert my ship to an integer
  int ship_int = convert_ship(ship);

  //convert the ship number to a string
  string ship_string = to_string(ship_int);
  ship_string += "\n";

  //Send message
  boost::asio::write( socket, boost::asio::buffer(ship_string) );

  // Get the response from the server!
  string answer;
  int n = 0;
  boost::asio::streambuf server_buffer;
  istream is(&server_buffer);
  n = boost::asio::read_until( socket, server_buffer, '\n' );
  getline(is, answer);

  //ship placed successfully and sent to the server, use opponent board from now on
  if(answer == "Board Received"){
    placed = true;
  }

  //************************//
  //                        //
  //	  BEGIN BATTLESHIP    //
  //		             				//
  //************************//

  // I/O Loop....
  // Stop when the q Key is hit.
  //
  //Server set up, get first move
  
  //Used to send and collect moves from the socket
  string move_string = "", opp_move_string = "";
  
  //Used as intermediary stages for moves
  int move_int = 0, opp_move_int = 0;
  
  //Store the opponents moves and check for hits and misses
  Move opp_move;
  opp_move.x = 0;
  opp_move.y = 0;

  //program ends when one player gets 3 hits
  int my_hit_count = 0, opp_hit_count = 0;

  while ((ch = getch())!=(char)(27) && my_hit_count < 3 && opp_hit_count < 3) {
  	switch (ch) {
  		case ' ': 
          //If the space has already been guessed, you can't guess it again
          if(opp_board[cur_row][cur_col] != 0){
            break;
          }
          // take the current row and column and convert to a single string
          move_int = convert_move(cur_row,cur_col);
          move_string = to_string(move_int);
          move_string += "\n";

          //send move to server
          boost::asio::write( socket, boost::asio::buffer(move_string) );

          n = boost::asio::read_until( socket, server_buffer, '\n' );
          getline(is, answer);
          
          if(answer == "hit"){ // Mark as hit
            opp_board[cur_row][cur_col] = 3;
            my_hit_count++;
          } else { // Mark as miss
            opp_board[cur_row][cur_col] = 2;
          }
          
          n = boost::asio::read_until( socket, server_buffer, '\n' );
          n++;
          getline(is, answer); 

          opp_move_string = answer;          
          opp_move_int = stoi(answer);

          opp_move.x = opp_move_int / 10;
          opp_move_int = opp_move_int % 10;
          opp_move.y = opp_move_int;

          if(is_hit(opp_move, my_board)){ //mark as hit
            my_board[opp_move.x][opp_move.y] = 3;
            opp_hit_count++;
          } else { //mark as miss
            my_board[opp_move.x][opp_move.y] = 2;
          }

          draw_top_matrix(my_board, opp_board,cur_row,cur_col, placed);
          // Redraw the screen.
          refresh();          
  	  		break;
  		case KEY_RIGHT:
  		  	cur_col++;
  		  	cur_col%=4;
  		  	draw_top_matrix(my_board, opp_board,cur_row,cur_col, placed);
  		  	// Redraw the screen.
  		  	refresh();
  		  	break;
  		case KEY_LEFT:
  		  	cur_col--;
  	  		cur_col = (4+cur_col)%4;
  	  		draw_top_matrix(my_board, opp_board,cur_row,cur_col, placed);
  	  		// Redraw the screen.
  	  		refresh();
  	  		break;
  		case KEY_UP:
  			cur_row--;
  		  	cur_row=(4+cur_row) % 4;
  	  		draw_top_matrix(my_board, opp_board,cur_row,cur_col, placed);
  	  
  	  		// paint_markers(rows,cols,10,cur_row,cur_col);
  	  		// Redraw the screen.
  	  		refresh();
  	  		break;
  		case KEY_DOWN:
  	  		cur_row++;
  	  		cur_row%=4;
  	  		draw_top_matrix(my_board, opp_board,cur_row,cur_col, placed);
  	        
  	        // paint_markers(rows,cols,10,cur_row,cur_col);
  	  		// Redraw the screen.
  	  		refresh();
  	  		break;
  	}
    draw_top_matrix(my_board, opp_board,cur_row,cur_col, placed);
    refresh();

  }

  endwin();

  n = boost::asio::read_until( socket, server_buffer, '\n' );
  getline(is, answer);

  //Game is over
  if(answer == "tie"){
    cout << "\n\nIt's a tie!\n\n\n";
  } else if(answer == "win"){ //I sank the other ship
    cout << "\n\nCongratulations! You Win!\n\n\n";
  } else { //
    cout << "\n\nSorry, you lose. Better luck next time.\n\n\n";
  }
  return 0;
}

