#ifndef __cryptolab2__OFB__
#define __cryptolab2__OFB__

#include <iostream>
using namespace std;
class OFB{
public:
    OFB();
    unsigned char iv[16];
    void cipher(string filename);
    void decipher(string filename);
};
#endif /* defined(__cryptolab2__OFB__) */
