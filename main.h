#include <stdio.h>

typedef unsigned char byte;


#define Nb  4 
#define Nr  10


void Cipher(byte* in[4*Nb], byte* out[4*Nb]);

void SubBytes(byte* state);                     // 테스트 완료

void ShiftRows(byte* state);                    // 테스트 완료

void PrintArray(char* str, byte* state);