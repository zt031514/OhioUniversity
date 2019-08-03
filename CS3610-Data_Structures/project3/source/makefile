all: go knights_tour.o

go: knights_tour.o
	g++ -o go knights_tour.o main.cpp 

knights_tour.o : knights_tour.cpp
	g++ -c knights_tour.cpp

clean:
	rm knights_tour.o go

