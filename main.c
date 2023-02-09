#include <stdio.h>
#include "main.h"
#include "sbox.c"




int main() {

    byte in[16] = {0x19,0x3d,0xe3,0xbe,0xa0,0xf4,0xe2,0x2b,0x9a,0xc6,0x8d,0x2a,0xe9,0xf8,0x48,0x08};
    byte out[16];

    PrintArray("Before Sbox",in);
    SubBytes(in);
    PrintArray("After Sbox",in);
    ShiftRows(in);
    PrintArray("After ShiftRows",in);
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
 * shift rows
*/
void ShiftRows(byte* state) {
    byte temp[Nb];
    
    for(int i = 1; i < 4; i++) {
        // temp에 열 담기
        for(int j = 0; j < Nb; j++) { //1,5,9,13 //2,6,10,14 //3,6,11,15
            temp[j] = state[j*Nb+i];
        }

        // i번 만큼 왼쪽으로 이동
        // TODO : 더 좋은 방법이 있지 않을까?
        for(int k = i; k > 0; k--) {
            byte t0 = (unsigned char)temp[0];
            for(int l = 0; l < 3; l++) {
                temp[l] = temp[l+1];
            }
            temp[3] = t0;

        }

        // state에 shift 된 것들 저장
        for(int j = 0; j < Nb; j++) { //1,5,9,13 //2,6,10,14 //3,6,11,15
            state[j*Nb+i] = temp[j];
        }
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