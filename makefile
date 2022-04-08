all:
	gcc -g main.c list.o -o DSSimul
	./DSSimul

clean:
	rm DSSimul