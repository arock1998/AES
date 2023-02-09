#include <stdio.h>

typedef unsigned char byte;


#define Nb  4 
#define Nr  10


void Cipher(byte* in[4*Nb], byte* out[4*Nb]);

void SubBytes(byte* state);

void PrintArray(char* str, byte* state);