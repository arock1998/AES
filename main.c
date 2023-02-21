#include <stdio.h>
#include "aes.h"

int main() {
    
    byte key[16] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
    byte in[16] = {0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34};
    byte_4 w[(Nr+1)*Nb] = {0,};
    byte out[16] = {0, };

    KeyExpansion(key, w);
    PrintW(w);
    Cipher(in, out, w);
    PrintArray("output : ", out);

    byte inin[16] = {0x39, 0x25, 0x84, 0x1d, 0x02, 0xdc, 0x09, 0xfb, 0xdc, 0x11, 0x85, 0x97, 0x19, 0x6a, 0x0b, 0x32};

    PrintArray("print inin :  ", inin);
    AddRoundKey(inin, 10, w);
    PrintArray("after addroundkey :  ", inin);

    InvShiftRows(inin);
    PrintArray("after shift row          : ", inin);
    InvSubBytes(inin);
    PrintArray("after inverse sub byte   : ", inin);

    AddRoundKey(inin, 9, w);
    PrintArray("after addroundkey :  ", inin);
    InvMixColumns(inin);
    PrintArray("after inverse mix column :  ", inin);

    
}
