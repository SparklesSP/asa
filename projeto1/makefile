FLAGS = -g -c

main: main.o
	gcc -o main main.o

main.o: main.c
	gcc $(FLAGS) main.c

clean:
	rm *.o main

run:
	./main
