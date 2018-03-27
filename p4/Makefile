attractions: attractions.o pointlist.o point.o
	gcc attractions.o pointlist.o point.o -o attractions -lm
	
attractions.o:
	gcc -Wall -std=c99 -D_GNU_SOURCE -c attractions.c pointlist.c point.c
	
pointlist.o:
	gcc -Wall -std=c99 -D_GNU_SOURCE -c pointlist.c point.c
	
point.o:
	gcc -Wall -std=c99 -D_GNU_SOURCE -c point.c

clean:
	rm -f attractions.o pointlist.o point.o
	rm -f attractions