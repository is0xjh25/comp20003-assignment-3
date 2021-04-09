all: map1 map2
map1: main1.o read.o kdtree.o search.o output.o
	gcc -o map1 main1.o read.o kdtree.o search.o output.o -lm
map2: main2.o read.o kdtree.o search.o output.o
	gcc -o map2 main2.o read.o kdtree.o search.o output.o -lm
main1.o: main1.c
	gcc -c -Wall main1.c
main2.o: main2.c
	gcc -c -Wall main2.c
read.o: read.c read.h
	gcc -c -Wall read.c
kdtree.o: kdtree.c kdtree.h
	gcc -c -Wall kdtree.c
search.o: search.c search.h
	gcc -c -Wall search.c
output.o: output.c output.c
	gcc -c -Wall output.c
