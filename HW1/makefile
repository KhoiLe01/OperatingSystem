main: hangfunctions.o hangperson.o
	gcc -o main hangfunctions.o hangperson.o

hangfunctions.o: hangfunctions.c
	gcc -Wall -c hangfunctions.c

hangperson.o: hangperson.c
	gcc -Wall -c hangperson.c

clean:
	rm *.o
	rm main
