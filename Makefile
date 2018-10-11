all: draw

clean:
	rm -f draw filemanipulation.o polygon.o pixel.o line.o rasterize.o

draw: main.cpp filemanipulation.o polygon.o pixel.o line.o rasterize.o
	g++ main.cpp -lglut -lGL -o draw filemanipulation.o polygon.o pixel.o line.o rasterize.o

filemanipulation.o: filemanipulation.cpp filemanipulation.h
	g++ -c filemanipulation.cpp

polygon.o: polygon.cpp polygon.h
	g++ -c polygon.cpp

pixel.o: pixel.cpp pixel.h
	g++ -c pixel.cpp

line.o: line.cpp line.h
	g++ -c line.cpp

rasterize.o: rasterize.cpp rasterize.h
	g++ -c rasterize.cpp
