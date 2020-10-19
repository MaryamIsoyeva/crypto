#ifndef __cryptolab2__CTR__
#define __cryptolab2__CTR__

#include <iostream>
using namespace std;
class CTR{
public:
    CTR();
    unsigned char iv[16];
    void cipher(string filename);
    void decipher(string filename);
};
#endif /* defined(__cryptolab2__CTR__) */
