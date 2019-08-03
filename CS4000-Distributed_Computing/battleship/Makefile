all : client server
client : client.cpp
		g++ -g -std=c++11 client.cpp -lncurses -lboost_system -lboost_thread -lpthread -o client
server : server.cpp
		g++ -g -std=c++11 server.cpp -lboost_system -lboost_thread -lpthread -o server
clean : cleanClient cleanServer

cleanClient :
		rm client
cleanServer :
		rm server
