#include "RC4.h"
#include <cstdlib>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <fstream>
using namespace std;
RC4::RC4(string key_){
//    key = key_.c_str();
    if(key_ == ""){
        for(int z = 0; z < 256; ++z){
            key[z] = rand()%122;
//            cout << key[z] << "\n";
        }
        keylength = 256;
    }
    else{
        keylength = key_.length();
        for(int z = 0; z < keylength; ++z){
            key[z] = key_[z];
        }
    }
    for (int z = 0; z <= 255; ++z){
        S[z] = z;
    }
    
    i = 0, j = 0;
    unsigned char temp;
    for(; i <=255; ++i){
        j = (j +S[i] + key[i % keylength]) % 256;
        temp = S[i];
        S[i] = S[j];
        S[j] = temp;
    }
}
RC4::RC4(unsigned char key_[256]){
    keylength = 256;
        for(int z = 0; z < keylength; ++z){
            key[z] = key_[z];
        }
    
    for (int z = 0; z <= 255; ++z){
        S[z] = z;
    }
    
    i = 0, j = 0;
    unsigned char temp;
    for(; i <=255; ++i){
        j = (j +S[i] + key[i % keylength]) % 256;
        temp = S[i];
        S[i] = S[j];
        S[j] = temp;
    }
}
unsigned char RC4::step(){
    unsigned char temp;
    i = (i + 1) % 256;
    j = (j + S[i]) % 256;
    temp = S[i];
    S[i] = S[j];
    S[j] = temp;
    return S[(S[i] + S[j]) %256];
}
void RC4::cipher(unsigned char buf[], int s){
    for (int z = 0; z < s; ++z){
        ciphered.push_back(buf[z]^step());
    }
}
void RC4::decipher(){
    for (int z = 0; z < ciphered.size(); ++z){
        deciphered.push_back(ciphered[z]^step());
    }

}
void RC4::decipher(vector<unsigned char> v){
    for (int z = 0; z < v.size(); ++z){
        deciphered.push_back(v[z]^step());
    }
    
}
void RC4::cipher(string filename){
    FILE * file = fopen(filename.c_str(), "r+");
//    FILE * fileoutput = fopen("/Users/elena/Downloads/Output.txt", "w+");
    
    
    int size = 1;
    unsigned char * in = (unsigned char *) malloc(size);
    while(fread(in, sizeof(unsigned char), size, file)){
        //        cout << in[0];
        
        cipher(in, size);
    }
    
    fclose(file);
    free(in);

}
