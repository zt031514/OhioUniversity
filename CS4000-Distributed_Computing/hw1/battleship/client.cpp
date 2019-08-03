//***************************************************************************
// File: client.cpp
//
// Author: David W. Juedes
//
// Editor: Joe Wamsley
//
// Date: March 4th, 2019
//
// Edit Date: March 17th, 2019
//
// The following example shows how to use the curses
// library to display a 4x4 boards for "Mini-Battleship"
//
//
//
// The program exits when the F10 key is hit.
//
//*************************************************************************** 
#include <ncurses.h>
#include <vector>
#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
using namespace std;
using boost::asio::ip::tcp;

#define ESC 27

using namespace std;

void draw_board (vector<vector<int> > &attack_board,
	vector<vector<int> > &defend_board,
	int cur_board, int cur_row, int cur_col) {
	//draw_attack_matrix(attack_board);
	//move(10,0);
	for (int j=0;j<4;j++) {
		move(0,2*j);
		printw("+-");
	}
	move(0,2*4);
	printw("+");
	for (int i=0;i<4;i++) {
		for (int j=0;j<4;j++) {
			move(2*i+1,2*j);
			printw("|");
			move(2*i+1,2*j+1);
			if (attack_board[i][j] == 1) {
				printw("X");
			} else if (attack_board[i][j] == 2) {
				printw("H");
			} else if (attack_board[i][j] == 3) {
				printw("M");
			} else
				printw(" ");
		}
		move(2*i+1,2*4);
		printw("|");
		for (int j=0;j<4;j++) {
			move(2*i+2,2*j);
			printw("+-");
		}
		move(2*i+2,2*4);
		printw("+");
	}

	for (int j=0;j<4;j++) {
		move(10,2*j);
		printw("+-");
	}
	move(10,2*4);
	printw("+");
	for (int i=0;i<4;i++) {
		for (int j=0;j<4;j++) {
			move(2*i+11,2*j);
			printw("|");
			move(2*i+11,2*j+1);
			if (defend_board[i][j] == 1) {
				printw("X");
			} else if (defend_board[i][j] == 2) {
				printw("H");
			} else if (defend_board[i][j] == 3) {
				printw("M");
			} else
				printw(" ");
		}
		move(2*i+11,2*4);
		printw("|");
		for (int j=0;j<4;j++) {
			move(2*i+12,2*j);
			printw("+-");
		}
		move(2*i+12,2*4);
		printw("+");
	}

	if (cur_board == 1)
		move(2*cur_row+1,2*cur_col+1);
	else
		move(11 + 2*cur_row,2*cur_col+1);
}

int rotate(vector<vector<int> > &board, int rotation, int cur_col, int cur_row) {
	// Rotate until in a legal configuration
	int done = 0;
	switch (rotation) {
		case 0:
			// Go to 0: Is 0 (north) legal?
			if (cur_row > 1) {
				done = 1;
				board[cur_row - 1][cur_col] = board[cur_row - 2][cur_col] = 1;
			}
			break;
		case 1:
			// Go to 1: Is 1 (northeast) legal?
			if (cur_row > 1 && cur_col < 2) {
				done = 1;
				board[cur_row - 1][cur_col + 1] = board[cur_row - 2][cur_col + 2] = 1;
			}
			break;
		case 2:
			// Go to 2: Is 2 (east) legal?
			if (cur_col < 2) {
				done = 1;
				board[cur_row][cur_col + 1] = board[cur_row][cur_col + 2] = 1;
			}
			break;
		case 3:
			// Go to 3: Is 3 (southeast) legal?
			if (cur_col < 2 && cur_row < 2) {
				done = 1;
				board[cur_row + 1][cur_col + 1] = board[cur_row + 2][cur_col + 2] = 1;
			}
			break;
		case 4:
			// Go to 4: Is 4 (south) legal?
			if (cur_row < 2) {
				done = 1;
				board[cur_row + 1][cur_col] = board[cur_row + 2][cur_col] = 1;
			}
			break;
		case 5:
			// Go to 5: Is 5 (southwest) legal?
			if (cur_col > 1 && cur_row < 2) {
				done = 1;
				board[cur_row + 1][cur_col - 1] = board[cur_row + 2][cur_col - 2] = 1;
			}
			break;
		case 6:
			// Go to 6: Is 6 (west) legal?
			if (cur_col > 1) {
				done = 1;
				board[cur_row][cur_col - 1] = board[cur_row][cur_col - 2] = 1;
			}
			break;
		case 7:
			// Go to 7: Is 7 (northwest) legal?
			if (cur_col > 1 && cur_row > 1) {
				done = 1;
				board[cur_row - 1][cur_col - 1] = board[cur_row - 2][cur_col - 2] = 1;
			}
			break;
	}
	return done;
}

int attack(vector<vector<int> > &attack_board, vector<vector<int> > &defend_board, int cur_row, int cur_col) {
	// Later...
}

int main() {
	int rows;
	int cols;
	int cur_row=0;
	int cur_col=0;
	int ch;

	boost::asio::io_service my_service;

	tcp::resolver resolver(my_service);
	// Find the server/port number.
	//  tcp::resolver::results_type endpoints = resolver.resolve(argv[2], argv[3]);

	tcp::socket socket(my_service);

	socket.connect(tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"),4700));

	vector<vector<int> > defend_board;
	vector<vector<int> > attack_board;
	for (int i=0;i<4;i++) {
		vector<int> t;
		for (int j=0;j<4;j++) {
			t.push_back(0);
		}
		attack_board.push_back(t);
		defend_board.push_back(t);
	}

	// Screen initialization

	initscr();
	// Clear the screen

	clear();

	// Get the size of the window!
	getmaxyx(stdscr,rows,cols);


	cbreak();  // Pass all characters to this program!

	keypad(stdscr, TRUE); // Grab the special keys, arrow keys, etc.

	// Paint the row and column markers.
	//paint_markers(rows,cols,10,0,0);
	// Redraw the screen.
	refresh();

	draw_board(attack_board,defend_board,0,0,0);
	int rotation = 0;
	string board_data;

	// 0 north; 1 northeast; 2 east; 3 southeast; 4 south; 5 southwest; 6 west; 7 northwest
	int curr_io = 0;
	while (curr_io <= 2) {
		ch = getch();
		switch (ch) {
			case ' ':
				if (curr_io == 0) {
					if (cur_col == 1 || cur_col == 0) {
						defend_board[cur_row][cur_col] = defend_board[cur_row][cur_col + 1] = defend_board[cur_row][cur_col + 2] = 1;
						rotation = 2;
					} else if ((cur_col == 2 || cur_col == 3) && cur_row < 2) {
						defend_board[cur_row][cur_col] = defend_board[cur_row + 1][cur_col] = defend_board[cur_row + 2][cur_col] = 1;
						rotation = 4;
					} else if ((cur_col == 2 || cur_col == 3) && cur_row > 2) {
						defend_board[cur_row][cur_col] = defend_board[cur_row - 1][cur_col] = defend_board[cur_row - 2][cur_col] = 1;
						rotation = 0;
					}
				} else {
					// send data
					board_data = to_string(cur_row) + to_string(cur_col);
					switch (rotation) {
						case 0:
							board_data += to_string(cur_row - 1) + to_string(cur_col);
							board_data += to_string(cur_row - 2) + to_string(cur_col);
							break;
						case 1:
							board_data += to_string(cur_row - 1) + to_string(cur_col + 1);
							board_data += to_string(cur_row - 2) + to_string(cur_col + 2);
							break;
						case 2:
							board_data += to_string(cur_row) + to_string(cur_col + 1);
							board_data += to_string(cur_row) + to_string(cur_col + 2);
							break;
						case 3:
							board_data += to_string(cur_row + 1) + to_string(cur_col + 1);
							board_data += to_string(cur_row + 2) + to_string(cur_col + 2);
							break;
						case 4:
							board_data += to_string(cur_row + 1) + to_string(cur_col);
							board_data += to_string(cur_row + 2) + to_string(cur_col);
							break;
						case 5:
							board_data += to_string(cur_row + 1) + to_string(cur_col - 1);
							board_data += to_string(cur_row + 2) + to_string(cur_col - 2);
							break;
						case 6:
							board_data += to_string(cur_row) + to_string(cur_col - 1);
							board_data += to_string(cur_row) + to_string(cur_col - 2);
							break;
						case 7:
							board_data += to_string(cur_row - 1) + to_string(cur_col - 1);
							board_data += to_string(cur_row - 2) + to_string(cur_col - 2);
							break;
					}
				}
				curr_io++;
				draw_board(attack_board,defend_board,0,cur_row,cur_col);
				// Redraw the screen.
				refresh();
				break;

			case KEY_RIGHT:
				if (curr_io == 0) {
					cur_col++;
					cur_col%=4;
				} else {
					// Rotate
					for (int i=0;i<4;i++)
						for (int j=0;j<4;j++)
							defend_board[i][j] = 0;
					defend_board[cur_row][cur_col] = 1;
					do {
						rotation = (rotation + 1) % 8;
					} while (!rotate(defend_board, rotation, cur_col, cur_row));
				}
				draw_board(attack_board,defend_board,0,cur_row,cur_col);
				// Redraw the screen.
				refresh();
				break;
		
			case KEY_LEFT:
				if (curr_io == 0) {
					cur_col--;
					cur_col = (4+cur_col)%4;		
				} else {
					// Rotate
					for (int i=0;i<4;i++)
						for (int j=0;j<4;j++)
							defend_board[i][j] = 0;
					defend_board[cur_row][cur_col] = 1;
					do {
						rotation = (rotation - 1);
						if (rotation < 0)
							rotation = rotation + 8;
					} while (!rotate(defend_board, rotation, cur_col, cur_row));
				}
				draw_board(attack_board,defend_board,0,cur_row,cur_col);
				// Redraw the screen.
				refresh();
				break;
		
			case KEY_UP:
				if (curr_io == 0) {
					cur_row--;
					cur_row=(4+cur_row) % 4;
					draw_board(attack_board,defend_board,0,cur_row,cur_col);
					// paint_markers(rows,cols,10,cur_row,cur_col);
					// Redraw the screen.
					refresh();	
				}
				break;

			case KEY_DOWN:
				if (curr_io == 0) {
					cur_row++;
					cur_row%=4;
					draw_board(attack_board,defend_board,0,cur_row,cur_col);
					//paint_markers(rows,cols,10,cur_row,cur_col);
					// Redraw the screen.
					refresh();		
				}
				break;
			case ESC:
				if (curr_io == 0) {
					endwin();
					cout << "EXITING EARLY" << endl;
					return 1;
				}
				if (curr_io == 1) {
					for (int i=0;i<4;i++)
						for (int j=0;j<4;j++)
							defend_board[i][j] = 0;
					curr_io--;
					draw_board(attack_board,defend_board,0,cur_row,cur_col);
					//paint_markers(rows,cols,10,cur_row,cur_col);
					// Redraw the screen.
					refresh();
				} 
				break;
		}
	}

	// Done with set up.
	// send positions to server

	board_data+= "\n";
	boost::asio::write( socket, boost::asio::buffer(board_data) );

	// Get the response from the server!
	boost::asio::streambuf buf;
	boost::asio::read_until( socket, buf, "\n" );

	// send attacks to server
	int done = 0;
	draw_board(attack_board,defend_board,1,0,0);
	refresh();
	do {
		ch = getch();
		switch (ch) {
			case ' ':
				if (attack_board[cur_row][cur_col] == 0) {
					// Send coordinates to server and receive hit or miss
					// Receive opponents attack
					// Receive if games over:
						// 0 not over
						// 1 win
						// 2 lost
						// 3 tie
					//

					string msg = to_string(cur_row) + to_string(cur_col);
					msg+= "\n";
					boost::asio::write( socket, boost::asio::buffer(msg) );

					// Get the response from the server!
					int n = boost::asio::read_until( socket, buf, "\n" );
					string answer;
					istream is(&buf);
					getline(is, answer);
					
					//string answer = boost::asio::buffer_cast<const char*>(buf2.data());

					switch(answer[0]) { // Hit or miss. (H/M)
						case 'H':
							attack_board[cur_row][cur_col] = 2;
							break;
						case 'M':
							attack_board[cur_row][cur_col] = 3;
							break;
					}
					switch(defend_board[answer[3] - '0'][answer[4] - '0']) {
						case 0:
							defend_board[answer[3] - '0'][answer[4] - '0'] = 3;
							break;
						case 1:
							defend_board[answer[3] - '0'][answer[4] - '0'] = 2;
							break;
					}
					done = answer[1] - '0';

					draw_board(attack_board,defend_board,1,cur_row,cur_col);
					// Redraw the screen.
					refresh();
				}
				break;

			case KEY_RIGHT:
				cur_col++;
				cur_col%=4;
				draw_board(attack_board,defend_board,1,cur_row,cur_col);
				// Redraw the screen.
				refresh();
				break;
		
			case KEY_LEFT:
				cur_col--;
				cur_col = (4+cur_col)%4;		
				draw_board(attack_board,defend_board,1,cur_row,cur_col);
				// Redraw the screen.
				refresh();
				break;
		
			case KEY_UP:
					cur_row--;
					cur_row=(4+cur_row) % 4;
					draw_board(attack_board,defend_board,1,cur_row,cur_col);
					// paint_markers(rows,cols,10,cur_row,cur_col);
					// Redraw the screen.
					refresh();	
				break;

			case KEY_DOWN:
					cur_row++;
					cur_row%=4;
					draw_board(attack_board,defend_board,1,cur_row,cur_col);
					//paint_markers(rows,cols,10,cur_row,cur_col);
					// Redraw the screen.
					refresh();		
				break;
			case ESC:
				// Forfeit?
				draw_board(attack_board,defend_board,1,cur_row,cur_col);
				refresh();
				break;
		}
	} while (!done);
	// receive hit/miss and coordinates of other

	endwin();
	cout << "Winner!" <<endl;
	return 0;
}