#include "ECB.h"
#include "AES.h"
void ECB::cipher(string filename){
    FILE * file = fopen(filename.c_str(), "r+");
    FILE * fileoutput = fopen("/Users/elena/Downloads/Output.txt", "w+");
    
    
    int size = 16;
    unsigned char * in = (unsigned char *) malloc(size);
    
    while(fread(in, sizeof(unsigned char), size, file)){
        AES c(in, 4);
        c.cipher();
        fwrite(c.output, sizeof(unsigned char), size, fileoutput);
    }
    
    fclose(file);
    fclose(fileoutput);
    free(in);
}
void ECB::decipher(string filename){
    FILE * file = fopen(filename.c_str(), "r+");
    FILE * fileoutput = fopen("/Users/elena/Downloads/DecipherOutput.txt", "w+");
    int size = 16;
    unsigned char * in = (unsigned char *) malloc(size);
    
    while(fread(in, sizeof(unsigned char), size, file)){
        AES c(in, 4, 16);
        c.invCipher();
        fwrite(c.decrypted, sizeof(unsigned char), size, fileoutput);
    }
    
    fclose(file);
    fclose(fileoutput);
    free(in);
}