all: draw

clean:
	rm -f draw filemanipulation.o polygon.o pixel.o

draw: main.cpp filemanipulation.o polygon.o pixel.o
	g++ main.cpp -lglut -lGL -o draw filemanipulation.o polygon.o pixel.o

filemanipulation.o: filemanipulation.cpp filemanipulation.h
	g++ -c filemanipulation.cpp

polygon.o: polygon.cpp polygon.h
	g++ -c polygon.cpp

pixel.o: pixel.cpp pixel.h
	g++ -c pixel.cpp
