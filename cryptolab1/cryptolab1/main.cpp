#include <iostream>
#include "AES.h"
#include "TestCasesAES.h"
using namespace std;
int main(int argc, const char * argv[])
{

    unsigned char input[16] = {0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34};
//    unsigned char key[16] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
//    
    //basic substitution
//    unsigned char x1 = 0xff;
//    unsigned char r, c;
//    AES cip(input, 4);
//    unsigned char subst;
//    r = x1 / 0x10;
//    c = x1 % 0x10;
//    subst = cip.sbox[r][c];
//    cout << ((int)subst == 0x16);
    
    AES c(input, 4);

    for(int i = 0; i < 4; ++i){
        for(int j = 0; j < 4; ++j){
        cout << hex << (int)c.state[i][j] << " ";
        }
        cout << "\n";
    }
    c.cipher();
    c.invCipher();
    cout <<"decrypted";
    for(int i = 0; i < 16; ++i){
        cout << hex << (int)c.output[i] << " ";
    }
    
    
    return 0;
}

