#ifndef __cryptolab2__CBC__
#define __cryptolab2__CBC__

#include <iostream>
using namespace std;
class CBC{
public:
    CBC();
    unsigned char iv[16];
    void cipher(string filename);
    void decipher(string filename);
};

#endif /* defined(__cryptolab2__CBC__) */
