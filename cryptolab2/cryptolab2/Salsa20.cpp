#include "Salsa20.h"
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <fstream>
using namespace std;
Salsa20::Salsa20(){
    
}
void Salsa20::cipher(uint32_t buf[16]){
    uint32_t cstate[16];
    for (int i = 0; i < 16; ++i){
		cstate[i] = buf[i];
    }
	for (int i = 0; i < rounds; i += 2) {
		
		qr(cstate, 0, 4, 8,12);
		qr(cstate, 5, 9, 13, 1);
		qr(cstate, 10, 14, 2, 6);
		qr(cstate, 15, 3, 7, 11);
		qr(cstate, 0, 1, 2, 3);
		qr(cstate, 5, 6, 7, 4);
		qr(cstate, 10, 11, 8, 9);
		qr(cstate, 15, 12, 13, 14);
	}
	for (int i = 0; i < 16; ++i)
		cipheredBlock[i] = cstate[i] + buf[i];
    
}
uint32_t Salsa20::rotate(uint32_t x, int n){
    return (((x) << (n)) | ((x) >> (32 - (n))));
}
void Salsa20::qr(uint32_t cstate[16], int a, int b, int c, int d){
    cstate[b] ^= rotate(a + d, 7);
	cstate[c] ^= rotate(b + a, 9);
	cstate[d] ^= rotate(c + b,13);
	cstate[a] ^= rotate(d + c,18);
}
void Salsa20::cipher(string filename){
    FILE * file = fopen(filename.c_str(), "r+");
    int size = 16;
    unsigned char * in = (unsigned char *) malloc(size);
    uint32_t buf[16] = {0x61707865, 0x04030201, 0x08070605, 0x0c0b0a09,
        0x100f0e0d, 0x3320646e, 0x01040103, 0x06020905,
        0x00000007, 0x00000000, 0x79622d32, 0x14131211,
        0x18171615, 0x1c1b1a19, 0x201f1e1d, 0x6b206574};
    while(fread(in, sizeof(unsigned char), size, file)){
        //        cout << in[0];
        
        cipher(buf);
        for(int i = 0; i <size; ++i){
            buf[8] = i % 8;
            cipheredText[i] = cipheredBlock[i]^in[i];
        }
    }
    
    fclose(file);
    free(in);
}
void Salsa20::decipher(string filename){
    cipher(filename);
}

