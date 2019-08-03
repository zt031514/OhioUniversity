all: battle

battle: battle_client.cc battle_server.cc
	g++ -o battle_client -Wall -std=c++11 battle_client.cc -lncurses -lboost_system -lboost_thread -lpthread
	g++ -o battle_server -Wall -std=c++11 battle_server.cc -lncurses -lboost_system -lboost_thread -lpthread

debug: battle_client.cc
	g++ -o battle -Wall -g  -std=c++11 battle_client.cc -lncurses

clean:
	rm battle_client battle_server