#include <stdio.h>
#include "sbox.c"

typedef unsigned char byte;
typedef unsigned int byte_4;

//          128     192     256            
#define Nk  4   //  6       8
#define Nb  4   //  4       4 
#define Nr  10  //  12      14

void AESTest();

void Cipher(byte* in, byte* out, byte_4* w);

void InvCipher(byte* in, byte* out, byte_4* w);

void KeyExpansion(byte* key, byte_4* w);

void SubBytes(byte* state);

void InvSubBytes(byte* state);

void ShiftRows(byte* state);

void InvShiftRows(byte* state);

void MixColumns(byte* state);

void InvMixColumns(byte* state);

void AddRoundKey(byte* state, int round, byte_4* w);

byte xtime(byte byte1);

byte_4 SubWord(byte_4 num);

byte_4 RotWord(byte_4 num);

void PrintArray(char* str, byte* state);

void PrintW();