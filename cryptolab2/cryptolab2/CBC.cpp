#include "CBC.h"
#include "AES.h"
CBC::CBC(){
    for(int z = 0; z < 16; ++z){
        iv[z] = rand()%122;
    }
}
void CBC::decipher(string filename){
    FILE * file = fopen(filename.c_str(), "r+");
    FILE * fileoutput = fopen("/Users/elena/Downloads/Input.txt", "w+");
    
    int size = 16;
    unsigned char * in = (unsigned char *) malloc(size);
    unsigned char ci[16];
    for(int i = 0; i < 16; ++i){
        ci[i] = iv[i];
    }
    while(fread(in, sizeof(unsigned char), size, file)){
        for(int i = 0; i < 16; ++i){
            ci[i] = in[i]^ci[i];
        }
        AES c(ci, 4, 128);
        c.invCipher();
        for(int i = 0; i < 16; ++i){
            ci[i] = c.decrypted[i];
        }
        fwrite(ci, sizeof(unsigned char), size, fileoutput);
    }
    
    fclose(file);
    fclose(fileoutput);
    free(in);
}
void CBC::cipher(string filename){
    FILE * file = fopen(filename.c_str(), "r+");
    FILE * fileoutput = fopen("/Users/elena/Downloads/Output.txt", "w+");
    
    int size = 16;
    unsigned char * in = (unsigned char *) malloc(size);
    unsigned char ci[16];
    for(int i = 0; i < 16; ++i){
        ci[i] = iv[i];
    }
    while(fread(in, sizeof(unsigned char), size, file)){
        for(int i = 0; i < 16; ++i){
            ci[i] = in[i]^ci[i];
        }
        AES c(ci, 4);
        c.cipher();
        for(int i = 0; i < 16; ++i){
            ci[i] = c.output[i];
        }
        fwrite(ci, sizeof(unsigned char), size, fileoutput);
    }
    
    fclose(file);
    fclose(fileoutput);
    free(in);
}