
all : make build

make : main.c sbox.c aes.c 
	gcc main.c sbox.c aes.c -o main

build : ./main

clean : rm -f main

