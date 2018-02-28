hangman: hangman.o wordlist.o display.o
	gcc hangman.o wordlist.o display.o -o hangman
	
hangman.o:
	gcc -Wall -std=c99 -c hangman.c
	
wordlist.o:
	gcc -Wall -std=c99 -c wordlist.c
	
display.o:
	gcc -Wall -std=c99 -c display.c

clean:
	rm -f hangman.o wordlist.o display.o
	rm -f hangman