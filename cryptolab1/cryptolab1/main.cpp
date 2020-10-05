#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <fstream>
#include "AES.h"
#include "TestCasesAES.h"
#include "Kalyna.h"
using namespace std;
//void generateFile(){
//    
//}
void testAESOnFile(string filename){
//    unsigned char buf[16];
//    fstream f("/Users/elena/Downloads/2600-0.txt");
    FILE * file = fopen(filename.c_str(), "r+");
    FILE * fileoutput = fopen("/Users/elena/Downloads/Output.txt", "w+");
    
    
    int size = 16;
    unsigned char * in = (unsigned char *) malloc(size);
    chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    while(fread(in, sizeof(unsigned char), size, file)){
        AES c(in, 4);
        c.cipher();
        fwrite(c.output, sizeof(unsigned char), size, fileoutput);
    }
    chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Ciphering time " << chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "ms" << "\n";
    fclose(file);
    fclose(fileoutput);
    free(in);
}
void testAESDecipherOnFile(string filename){
    FILE * file = fopen(filename.c_str(), "r+");
    FILE * fileoutput = fopen("/Users/elena/Downloads/DecipherOutput.txt", "w+");
    int size = 16;
    unsigned char * in = (unsigned char *) malloc(size);
    chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    while(fread(in, sizeof(unsigned char), size, file)){
        AES c(in, 4, 16);
        c.invCipher();
        fwrite(c.output, sizeof(unsigned char), size, fileoutput);
    }
    chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Deciphering time " << chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "ms" << "\n";
    fclose(file);
    fclose(fileoutput);
    free(in);

}
int main(int argc, const char * argv[])
{
    testAESOnFile("/Users/elena/Downloads/2600-0.txt");
    testAESDecipherOnFile("/Users/elena/Downloads/Output.txt");
//    unsigned char c;
//    std::cout << sizeof(c);
//    unsigned char input[16] = {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76};
//    for(int i = 0; i<16; ++i) cout << hex << (int) input[i] <<" ";
//     cout <<"\n";
//    AES cip(input);
//    for(int i = 0; i<16; ++i) cout << cip.input[i] <<" ";
//    cip.cipher();
//    cout <<"\n";
//    for(int i = 0; i<4; ++i) for(int j = 0; j<4; ++j) cout << cip.s[i][j] << " ";
//    unsigned char x1 = 0x57;
//    unsigned char x2 = 0x83;
//    cout << hex << (int)(x1^x2);
//    unsigned char input[16] = {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76};
    unsigned char input[16] = {0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34};
    unsigned char key[16] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
    
    //basic substitution
//    unsigned char x1 = 0xff;
//    unsigned char r, c;
//    AES cip(input, 4);
//    unsigned char subst;
//    r = x1 / 0x10;
//    c = x1 % 0x10;
//    subst = cip.sbox[r][c];
//    cout << ((int)subst == 0x16);
    
    //check subbytes
    
//    unsigned char c1 = 0x80;
//    if(c1==0x80) cout<<1;
//    TestCasesAES t;
//    cout << "Tests pass" << t.allTests();
//    unsigned char input[16] = {'a','b','c','d','e','f','g','e','a','b','c','d','e','f','g','e'};
    AES c(input, 4);
//    c.invShiftRows();
//    for(int i = 0; i < 4; ++i){
//        for(int j = 0; j < 4; ++j){
//        cout << hex << (int)c.state[i][j] << " ";
//        }
//        cout << "\n";
//    }
    c.cipher();
    c.invCipher();
    cout <<"decrypted";
    for(int i = 0; i < 16; ++i){
        cout << hex << (int)c.decrypted[i] << " ";
//        cout << c.decrypted[i] << " ";
    }
//    cout << c.nk;
//    c.keyExpansion();
    
//    unsigned char input[16] = {0x32, 0x88, 0x31, 0xe0, 0x43, 0x5a, 0x31, 0x37, 0xf6, 0x30, 0x98, 0x07, 0xa8, 0x8d, 0xa2, 0x34};
//    AES c(input, 4);
//    c.cipher();
//    cout <<"decrypted";
//    for(int i = 0; i < 16; ++i){
//        cout << hex << (int)c.output[i] << " ";
//    }
    Kalyna b(128, 128, 10, 2);
    
    return 0;
}

