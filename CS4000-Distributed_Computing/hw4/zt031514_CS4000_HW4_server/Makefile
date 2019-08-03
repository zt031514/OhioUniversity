all: battle

battle: battle_server.cc
	g++ -o battle_server -Wall -std=c++11 battle_server.cc -lncurses -lboost_system -lboost_thread -lpthread

clean:
	rm battle_server