all : client server
client : client.cpp
		g++ client.cpp -lncurses -lboost_system -lboost_thread -lpthread -o client
server : server.cpp
		g++ server.cpp -lboost_system -lboost_thread -lpthread -o server
clean : cleanClient cleanServer

cleanClient :
		rm client
cleanServer :
		rm server