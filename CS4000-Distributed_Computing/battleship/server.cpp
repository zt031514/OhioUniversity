
// Receive coordinates of start.
// Send verification.
// LOOP: while either score is less than three
	// Receive coordinates of attack.
	// Send hit or miss.
// Determine winner.
	// Higher score wins, with possible tie
	// Send congratulations
	// Send condolences

#include <iostream>
#include <string>
#include <sstream>
#include <boost/asio.hpp>

//using namespace std;

using namespace std;
using boost::asio::ip::tcp;

int main() {
	boost::asio::io_service my_service;

	// Accept connections on
	// Advertise a service on port 4700
	tcp::acceptor acceptor(my_service, tcp::endpoint(tcp::v4(), 4700));

	tcp::socket socket1(my_service);
	// Wait for a connection from 
	acceptor.accept(socket1);
	// Connection Established!!!

	// Read from Socket 1 until newline
	boost::asio::streambuf buf;
	boost::asio::read_until( socket1, buf, "\n" );
	string data = boost::asio::buffer_cast<const char*>(buf.data());
	cout << data << endl;

	//Wait for a connection on Socket #2 
	tcp::socket socket2(my_service);
	acceptor.accept(socket2);
	// Connection Established!!!!

	// Read from Socket #2 until newline
	boost::asio::streambuf buf2;
	boost::asio::read_until( socket2, buf2, "\n" );
	string data2 = boost::asio::buffer_cast<const char*>(buf2.data());
	cout << data2 << endl;

	boost::asio::write( socket1, boost::asio::buffer("1\n") );	
	boost::asio::write( socket2, boost::asio::buffer("1\n") );


	vector<vector<int> > p1_board;
	vector<vector<int> > p2_board;
	for (int i=0;i<4;i++) {
		vector<int> t;
		for (int j=0;j<4;j++) {
			t.push_back(0);
		}
		p1_board.push_back(t);
		p2_board.push_back(t);
	}

	//Setup ships
	p1_board[data[0] - '0'][data[1] - '0'] = 1;
	p1_board[data[2] - '0'][data[3] - '0'] = 1;
	p1_board[data[4] - '0'][data[5] - '0'] = 1;

	p2_board[data2[0] - '0'][data2[1] - '0'] = 1;
	p2_board[data2[2] - '0'][data2[3] - '0'] = 1;
	p2_board[data2[4] - '0'][data2[5] - '0'] = 1;

	int p1_score = 0, p2_score = 0;
	while (p1_score < 3 || p2_score < 3) {
		// Read from Socket 1 until newline
		boost::asio::read_until( socket1, buf, "\n" );
		string temp = data = boost::asio::buffer_cast<const char*>(buf.data());
		cout << "socket1 data: " << data << endl;
	
		// Read from Socket #2 until newline
		boost::asio::read_until( socket2, buf2, "\n" );
		data2 = boost::asio::buffer_cast<const char*>(buf2.data());
		cout << "socket2 data: " << data2 << endl;

		cout << "Player 1 tries to hit " << data;
		if (p2_board[data[0] - '0'][data[1] - '0'] == 1) {
			p1_score++;
			data = "H";
			cout << " and hits!" << endl;
		} else {
			data = "M";
			cout << " and misses!" << endl;
		}

		data += data2;

		cout << "Player 2 tries to hit " << data2;
		if (p1_board[data[0] - '0'][data[1] - '0'] == 1) {
			p2_score++;
			data2 = "H";
			cout << " and hits!" << endl;
		} else {
			data2 = "M";
			cout << " and misses!" << endl;
		}

		data2 += temp;

		// 0 not over
		// 1 win
		// 2 lost
		// 3 tie

		if (p2_score < 3 && p1_score < 3) {
			data2[5] = '0';
			data[5] = '0';
		} else if (p2_score == 3 && p1_score == 3) {
			data2[5] = '3';
			data[5] = '3';
		} else if (p2_score == 3) {
			data2[5] = '1';
			data[5] = '2';
		} else if (p2_score == 3) {
			data2[5] = '2';
			data[5] = '1';
		}
		data += "\n";
		data2 += "\n";

		cout << "Sending: " << data << " to socket1" << endl;
		cout << "Sending: " << data2 << " to socket2" << endl;

		boost::asio::write( socket1, boost::asio::buffer(data) );	
		boost::asio::write( socket2, boost::asio::buffer(data2) );
	}
	return 0;
}