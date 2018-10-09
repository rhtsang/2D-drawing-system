all: draw

clean:
	rm -f draw filemanipulation.o polygon.o pixel.o line.o

draw: main.cpp filemanipulation.o polygon.o pixel.o line.o
	g++ main.cpp -lglut -lGL -o draw filemanipulation.o polygon.o pixel.o line.o

filemanipulation.o: filemanipulation.cpp filemanipulation.h
	g++ -c filemanipulation.cpp

polygon.o: polygon.cpp polygon.h
	g++ -c polygon.cpp

pixel.o: pixel.cpp pixel.h
	g++ -c pixel.cpp

line.o: line.cpp line.h
	g++ -c line.cpp
