all: battle

battle: battle_client.cc
	g++ -o battle_client -Wall -std=c++11 battle_client.cc -lncurses -lboost_system -lboost_thread -lpthread

clean:
	rm battle_client