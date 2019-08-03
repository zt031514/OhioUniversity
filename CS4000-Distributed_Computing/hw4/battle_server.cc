//**************************************************************************
//
//  battle_server.cc	
//
//  Author: Zach Tumbleson
//
//	Date: 3-23-2019
//
//	Brief: Implements the server side of the assignment
//		   given in the assignment 4 handout. The client
//		   allows each user to place a ship, sends the
//		   location to the server. The server checks to see
//		   if either move is a hit or miss, and sends the result
//		   along with the opponent's move back to the client. The server
//		   ends the game if one player gets 3 hits.
//
//	
//	Note*: The server defined in this file is based on the 
//		   code provided by Dr. Juedes in rsp_server.cc.
//
//
//  Acknowledgement:
//  Based on the approach found here:
//  https://www.codeproject.com/Articles/1264257/Socket-Programming-in-Cplusplus-using-boost-asio-T
//***************************************************************************

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <boost/asio.hpp>
#include <string>
#include "server_helpers.h"

using namespace std;
using boost::asio::ip::tcp;

void battleship_server() {
    boost::asio::io_service my_service;
    int n;

    // Accept connections on
    // Advertise a service on port 4700
    tcp::acceptor acceptor(my_service, tcp::endpoint(tcp::v4(), 4700));

    tcp::socket socket1(my_service);
    // Wait for a connection from 
    acceptor.accept(socket1);
    cout << "Connected to player 1.\n";
    // Connection Established!!!

    // Read from Socket 1 until newline
    boost::asio::streambuf player1_buffer;
    string player1_data;
    istream is1(&player1_buffer);
    n = boost::asio::read_until( socket1, player1_buffer, '\n' );
    getline(is1, player1_data);
    cout << player1_data << endl;

    //Wait for a connection on Socket #2 
    tcp::socket socket2(my_service);
    acceptor.accept(socket2);
    cout << "Connected to player 2.\n";
    // Connection Established!!!!
    
    // Read from Socket #2 until newline
    boost::asio::streambuf player2_buffer;
    istream is2(&player2_buffer);
    string player2_data;
    n = boost::asio::read_until( socket2, player2_buffer, '\n' );
    getline(is2, player2_data); 

    cout << player2_data << endl; 

    //Convert ship position strings to int
    int player1_ship = stoi(player1_data);
    int player2_ship = stoi(player2_data);
    
    //use player ships to create boards
    vector<vector<int> > player1_board, player2_board;
    player1_board = ::getBoard(player1_ship);
    player2_board = ::getBoard(player2_ship);

    //Send received message back to players
    string player1_message = "Board Received\n";
    string player2_message = "Board Received\n";

    //Send messages
    boost::asio::write( socket1, boost::asio::buffer(player1_message) );
    boost::asio::write( socket2, boost::asio::buffer(player2_message) );

    //Count player hits
    int player1_hits = 0, player2_hits = 0;
    int player1_int = 0, player2_int = 0;

    //Create structs to store player moves
    Move player1_move;
    player1_move.x = 0;
    player1_move.y = 0;

    Move player2_move;
    player2_move.x = 0;
    player2_move.y = 0;
    
    while(player1_hits < 3 && player2_hits < 3){

        //Read in player moves
        n = boost::asio::read_until( socket1, player1_buffer, '\n' );
        n++; // get rid of compiler warning
        getline(is1, player1_data);

        n = boost::asio::read_until( socket2, player2_buffer, '\n' );
        getline(is2, player2_data);        

        //convert player moves to ints
        player1_int = stoi(player1_data);
        player2_int = stoi(player2_data);

        //Convert ints to moves
        player1_move = get_move(player1_int);
        player2_move = get_move(player2_int);
        
        //Send miss unless the player gets a hit
        player1_message = "miss\n";
        player2_message = "miss\n";

        //check the player boards for hits and misses
        if(is_hit(player1_move, player2_board)){
            player1_hits++;
            player1_message = "hit\n";
        }

        if(is_hit(player2_move, player1_board)){
            player2_hits++;
            player2_message = "hit\n";
        }

        //Send "hit" or "miss" back to the players
        boost::asio::write( socket1, boost::asio::buffer(player1_message) );
        boost::asio::write( socket2, boost::asio::buffer(player2_message) );

        //Prepare to send player moves
        player1_message = player2_data;
        player2_message = player1_data;
        player1_message += "\n";
        player2_message += "\n";

        //Send opponent's move to each player
        boost::asio::write( socket1, boost::asio::buffer(player1_message) );
        boost::asio::write( socket2, boost::asio::buffer(player2_message) );

    }

    //send results to players
    if(player1_hits == 3 && player2_hits == 3){ //tie
        player1_message = player2_message = "tie\n";
        cout << "\nGame over! It's a tie!\n\n";
    } else if(player1_hits == 3){ //player 1 wins
        player1_message = "win\n";
        player2_message = "lose\n";
        cout << "\nGame over! Player 1 wins!\n\n";
    } else { //player 2 wins
        player1_message = "lose\n";
        player2_message = "win\n";
        cout << "\nGame over! Player 2 wins!\n\n";
    }

    //send game result messages and exit
    boost::asio::write( socket1, boost::asio::buffer(player1_message) );
    boost::asio::write( socket2, boost::asio::buffer(player2_message) );
}


int main()
{
  battleship_server();
  return 0;
}