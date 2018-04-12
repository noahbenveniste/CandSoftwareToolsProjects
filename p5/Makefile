all: encode decode

encode: encode.o codes.o bits.o
	gcc encode.o codes.o bits.o -o encode

decode: decode.o codes.o bits.o
	gcc decode.o codes.o bits.o -o decode
	
encode.o:
	gcc -Wall -std=c99 -c encode.c codes.c bits.c

decode.o:
	gcc -Wall -std=c99 -c decode.c codes.c bits.c
	
codes.o:
	gcc -Wall -std=c99 -c codes.c
	
bits.o:
	gcc -Wall -std=c99 -c bits.c

clean:
	rm -f encode.o decode.o codes.o bits.o
	rm -f encode decode