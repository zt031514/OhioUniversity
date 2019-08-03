all : game doc

game : main.o othello.o game.o
	g++ -o game main.o othello.o game.o

main.o : main.cc game.h othello.h
	g++ -c main.cc
othello.o : othello.cc othello.h piece.h colors.h
	g++ -c othello.cc
game.o : game.cc game.h
	g++ -c game.cc

clean :
	rm game main.o othello.o game.o Doxyfile
	rm -rf html latex

doc : 
	doxygen -g
	doxygen Doxyfile

