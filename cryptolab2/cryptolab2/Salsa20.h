#ifndef __cryptolab2__Salsa20__
#define __cryptolab2__Salsa20__

#include <iostream>
using namespace std;
class Salsa20{
public:
    unsigned char key[32];
    uint32_t state[16];
    void cipher(string filename);
    uint32_t cipheredBlock[16];
    uint32_t cipheredText[16];
    void cipher(uint32_t buf[16]);
    void decipher(string filename);
    Salsa20();
    int rounds = 20;
    uint32_t rotate(uint32_t x, int n);
    void qr(uint32_t cstate[16], int a, int b, int c, int d);
};

#endif /* defined(__cryptolab2__Salsa20__) */
