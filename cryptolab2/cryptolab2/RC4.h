#ifndef __cryptolab2__RC4__
#define __cryptolab2__RC4__

#include <iostream>
#include <vector>
using namespace std;
class RC4{
private:
    
    unsigned char S[256];
    
    int i;
    int j;
public:
    unsigned char key[256];
    int keylength;
    RC4(string key_);
    RC4(unsigned char key_[256]);
    vector<unsigned char> ciphered;
    vector<unsigned char> deciphered;
    unsigned char cipheredText;
    void cipher(unsigned char buf[], int s);
    void cipher(string filename);
    void decipher();
    void decipher(vector<unsigned char> v);
    unsigned char step();
};

#endif /* defined(__cryptolab2__RC4__) */
