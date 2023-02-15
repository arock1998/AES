#include "aes.h"


/**
 * 암호화 동작 함수
 * w[] => contains the key schedule
*/
void Cipher(byte* in, byte* out, byte_4* w) {
    byte state[4*Nb] = {0, };

    for(int i = 0; i < 4*Nb; i++) { 
        state[i] = in[i];
    }

    AddRoundKey(state, 0, w);
    for(int i = 1; i < Nr; i ++) {
        SubBytes(state);
        ShiftRows(state);
        MixColumns(state);
        AddRoundKey(state, i, w);
    }
    SubBytes(state);
    ShiftRows(state);
    AddRoundKey(state, Nr, w);

    for(int i = 0; i < 4*Nb; i++) {
        out[i] = state[i];
    }
}


/**
 * key expansion 
*/
void KeyExpansion(byte* key, byte_4* w) {
    byte_4 Rcon_Nr10[10] = {0x01000000, 0x02000000, 0x04000000, 0x08000000, 0x10000000, 0x20000000, 0x40000000, 0x80000000, 0x1b000000, 0x36000000};
    byte_4 temp;
    for(int i = 0; i < Nk; i++) {
        w[i] = (key[Nk*i] << 24) ^ (key[Nk*i+1] << 16) ^ (key[Nk*i+2] << 8) ^ (key[Nk*i+3]);
    }
    for(int i = 4; i < Nb*(Nr+1); i++) {
        temp = w[i-1];
        if(i % Nk == 0) {
            temp = SubWord(RotWord(temp)) ^ Rcon_Nr10[i/Nk-1];
        } else if (Nk > 6 && (i % Nk == 4)) {
            temp = SubWord(temp);
        }
        w[i] = w[i-Nk] ^ temp;
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
    byte t0;
    
    for(int i = 1; i < 4; i++) {
        for(int j = 0; j < Nb; j++) { 
            temp[j] = state[j*Nb+i];
        }
        // i번 만큼 왼쪽으로 이동
        // TODO : 더 좋은 방법이 있지 않을까?
        for(int k = i; k > 0; k--) {
            t0 = (byte)temp[0];
            for(int l = 0; l < 3; l++) {
                temp[l] = temp[l+1];
            }
            temp[3] = t0;
        }
        for(int j = 0; j < Nb; j++) { 
            state[j*Nb+i] = temp[j];
        }
    }
}


/**
 * mix columns
*/
void MixColumns(byte* state) {
    byte temp[4*Nb];
    for(int i = 0; i < 4*Nb; i++) {
        temp[i] = state[i];
    }
    for(int i = 0; i < Nb; i++) {
        state[4*i+0] = xtime(temp[4*i+0]) ^ xtime(temp[4*i+1]) ^ temp[4*i+1] ^ temp[4*i+2] ^ temp[4*i+3];
        state[4*i+1] = xtime(temp[4*i+1]) ^ xtime(temp[4*i+2]) ^ temp[4*i+2] ^ temp[4*i+3] ^ temp[4*i+0];
        state[4*i+2] = xtime(temp[4*i+2]) ^ xtime(temp[4*i+3]) ^ temp[4*i+3] ^ temp[4*i+0] ^ temp[4*i+1];
        state[4*i+3] = xtime(temp[4*i+3]) ^ xtime(temp[4*i+0]) ^ temp[4*i+0] ^ temp[4*i+1] ^ temp[4*i+2];
    }
}


/**
 * add round key
*/
void AddRoundKey(byte* state, int round, byte_4* w) {
    for(int i = 0; i < Nb; i++) {
        state[4*i+0] = state[4*i+0] ^ (w[round*Nb+i] >> 24) & 0xff;
        state[4*i+1] = state[4*i+1] ^ (w[round*Nb+i] >> 16) & 0xff;
        state[4*i+2] = state[4*i+2] ^ (w[round*Nb+i] >> 8) & 0xff;
        state[4*i+3] = state[4*i+3] ^ (w[round*Nb+i] >> 0) & 0xff;
    }
}


/**
 * sub word
*/
byte_4 SubWord(byte_4 num) {
    byte list[4] = {0, };
    list[0] = s_box[(num >> 24) & 0xFF];
    list[1] = s_box[(num >> 16) & 0xFF];
    list[2] = s_box[(num >> 8) & 0xFF];
    list[3] = s_box[(num >> 0) & 0xFF];
    return (list[0] << 24) ^ (list[1] << 16) ^ (list[2] << 8) ^ (list[3]);
}


/**
 * rot word
*/
byte_4 RotWord(byte_4 num) {
    return ((num << 8) & 0xffffff00) ^ ((num >> 24) & 0xff);
}


/**
 * xtime 
*/
byte xtime(byte byte1) {
    int b7 = byte1 >> 7 & 0x01;
    byte1 = byte1 << 1;
    if(b7 == 1) {
        byte1 ^= 0x1b;
    }
    return byte1;
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


/**
 * w 출력 함수
*/
void PrintW(byte_4* w) {
    for(int i = 0; i < Nk*(Nr+1); i++) {
        printf("w[%d] : %x \n", i, w[i]);
    } 
}