CFLAGS=-Wall
CC=clang $(CFLAGS)

main   :	main.o	
	clang -o wordcounter main.o vstring.o wordlist.o
main.o :	main.c
	$(CC) -c main.c
	$(CC) -c vstring.c
	$(CC) -c wordlist.c
all	:
	$(CC) -c main.c 
	$(CC) -c vstring.c
	$(CC) -c wordlist.c
	clang -o wordcounter main.o vstring.o wordlist.o
clean   :
	rm -rf wordcounter main.o vstring.o wordlist.o
format  :
	clang-format -i -style=file *.c
