#include <stdio.h>

typedef unsigned char byte;
typedef unsigned int byte_4;

//          128     192     256            
#define Nk  4   //  6       8
#define Nb  4   //  4       4 
#define Nr  10  //  12      14

byte_4 w[Nr+1] = {0,};

byte_4 Rcon_Nr10[10] = {0x01000000, 0x02000000, 0x04000000, 0x08000000, 0x10000000, 0x20000000, 0x40000000, 0x80000000, 0x1b000000, 0x36000000};

void Cipher(byte* in, byte* out);

void KeyExpansion(byte* key);

void SubBytes(byte* state);

void ShiftRows(byte* state);

void MixColumns(byte* state);

void AddRoundKey(byte* state, int round);

byte xtime(byte byte1);

byte_4 SubWord(byte_4 num);

byte_4 RotWord(byte_4 num);

void PrintArray(char* str, byte* state);

void PrintW();