#ifndef __cryptolab2__CFB__
#define __cryptolab2__CFB__

#include <iostream>
using namespace std;
class CFB{
public:
    CFB();
    unsigned char iv[16];
    void cipher(string filename);
    void decipher(string filename);
};
#endif /* defined(__cryptolab2__CFB__) */
