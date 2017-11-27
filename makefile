all:	main

main:	main.cpp	classes.o	classes.h
		g++	main.cpp	classes.o	-g	-std=c++11	-o	main

classes.o:	classes.cpp
		g++	-c	classes.cpp	-g	-std=c++11

clean:
		rm	-rf	*.o	main
