all: draw

clean:
	rm -f draw filemanipulation.o polygon.o

draw: main.cpp filemanipulation.o polygon.o
	g++ main.cpp -lglut -lGL -o draw filemanipulation.o polygon.o

filemanipulation.o: filemanipulation.cpp filemanipulation.h
	g++ -c filemanipulation.cpp

polygon.o: polygon.cpp polygon.h
	g++ -c polygon.cpp
