#ifndef __cryptolab2__ECB__
#define __cryptolab2__ECB__

#include <iostream>
using namespace std;
class ECB{
public:
    void cipher(string filename);
    void decipher(string filename);
};
#endif /* defined(__cryptolab2__ECB__) */
