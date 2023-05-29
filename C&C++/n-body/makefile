cxx = g++
cflags = -O3
inc = -I./
sfml-libs = -lsfml-window -lsfml-graphics -lsfml-system

all: nbody-nographics nbody-graphics

nbody-nographics : nbody.cpp
	${cxx} -g -fopenmp nbody.cpp  -o nbody-nographics ${cflags} ${inc} -pthread

nbody-graphics : nbody.cpp
	${cxx} -g -fopenmp nbody.cpp  -o nbody-graphics ${cflags} ${inc} ${sfml-libs} -DGRAPHICS -pthread

clean:
	rm nbody-graphics nbody-nographics

run:
	./nbody-nographics