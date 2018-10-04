all: draw

clean:
	rm -f draw

draw: HelloGraphics.cpp
	g++ HelloGraphics.cpp -lglut -lGL -o draw
