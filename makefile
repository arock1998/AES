
all : make build

make : main.c sbox.c
	gcc main.c sbox.c -o main

build : ./main

clean : rm -f main

