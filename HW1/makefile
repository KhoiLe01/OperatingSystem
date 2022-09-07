main: hangfunctions.o hangperson.o
	gcc -o main hangfunctions.o hangperson.o

test: hangfunctions.o hangtest.o
	gcc -o test hangfunctions.o hangtest.o

hangfunctions.o: hangfunctions.c
	gcc -Wall -c hangfunctions.c

hangperson.o: hangperson.c
	gcc -Wall -c hangperson.c

hangtest.o: hangtest.c
	gcc -Wall -c hangtest.c

clean:
	del *.o
	del *.exe
	del *.out
