OBJ=main.o libfb.o
CC=gcc

main:$(OBJ) 
	$(CC) $(OBJ) -o main

libfb.o:libfb.c libfb.h
	$(CC) libfb.c -c

main.o:main.c libfb.h
	$(CC) main.c -c

run:main
	sudo ./main

clean:
	-rm *.o
	-rm main
