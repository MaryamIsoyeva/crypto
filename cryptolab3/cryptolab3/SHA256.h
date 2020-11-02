#ifndef __cryptolab3__SHA256__
#define __cryptolab3__SHA256__

#include <iostream>
class SHA256{
public:
    unsigned int sha [8];
    unsigned int schedule[64];
    unsigned int variables[8];
    unsigned int hashv [8];
    void hash(unsigned char m[], int l);
    SHA256();
};

#endif /* defined(__cryptolab3__SHA256__) */
