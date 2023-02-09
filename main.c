#include <stdio.h>
#include "main.h"
#include "sbox.c"




int main() {

    byte in[16] = {0x19,0x3d,0xe3,0xbe,0xa0,0xf4,0xe2,0x2b,0x9a,0xc6,0x8d,0x2a,0xe9,0xf8,0x48,0x08};
    byte out[16];

    PrintArray("Before Sbox",in);
    SubBytes(in);
    PrintArray("After Sbox",in);

}


/**
 * 암호화 동작 함수
 * TODO : word w[Nb*(Nr+1)] 파라미터로 추가
 * w[] => contains the key schedule
*/
void Cipher(byte* in[4*Nb], byte* out[4*Nb]) {
    byte* state[4*Nb];

    // state = in
    for(int i = 0; i < 4*Nb; i++) { 
        state[i] = in[i];
    }

    // TODO : AddRoundKey (state, w[0, Nb-1])

    for(int i = 0; i < Nr; i ++) {
        // SubBytes(state)
        // ShiftRows(State)
        // MixColumns(state)
        // AddRoundKey(state, w[round*Nb, (round+1*Nb-1)])
    }

    // SubBytes(state)
    // ShiftRows(State)
    // MixColumns(state)
    // AddRoundKey(state, w[round*Nb, (round+1*Nb-1)])

    // state = in
    for(int i = 0; i < 4*Nb; i++) {
        out[i] = state[i];
    }
}


/**
 * sub bytes 
*/
void SubBytes(byte* state) {
    for(int i = 0; i < 4*Nb; i++) {
        state[i] = s_box[state[i]];
    }
}


/**
 * 배열 출력 함수
*/
void PrintArray(char* str, byte* state) {
    printf("## %s ## : ", str);
    for(int i = 0; i < 4*Nb; i++) {
        printf("%02x, ", state[i]);
    }
    printf("\n");
}