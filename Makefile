all: a.out

a.out:
	gcc -g -I"libs" -O2 -Wall -pedantic -Wno-unused-result src/*.c -lm

clean:
	rm a.out