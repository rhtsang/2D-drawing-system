all: draw

clean:
	rm -f draw filemanipulation.o polygon.o pixel.o line.o rasterize.o transform.o clip.o

draw: main.cpp filemanipulation.o polygon.o pixel.o line.o rasterize.o transform.o clip.o
	g++ main.cpp -lglut -lGL -o draw filemanipulation.o polygon.o pixel.o line.o rasterize.o transform.o clip.o

filemanipulation.o: filemanipulation.cpp filemanipulation.h
	g++ -std=c++11 -c filemanipulation.cpp

polygon.o: polygon.cpp polygon.h
	g++ -c polygon.cpp

pixel.o: pixel.cpp pixel.h
	g++ -c pixel.cpp

line.o: line.cpp line.h
	g++ -c line.cpp

rasterize.o: rasterize.cpp rasterize.h
	g++ -c rasterize.cpp

transform.o: transform.cpp transform.h
	g++ -c transform.cpp

clip.o: clip.cpp clip.h
	g++ -c clip.cpp
