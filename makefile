all:
	gcc -g main.c list.o scan.c cscan.c fn.c -o DSSimul
	./DSSimul

clean:
	rm DSSimul