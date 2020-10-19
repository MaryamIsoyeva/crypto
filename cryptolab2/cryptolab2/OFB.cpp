#include "OFB.h"
#include "AES.h"
OFB::OFB(){
    for(int z = 0; z < 16; ++z){
        iv[z] = rand()%122;
    }
}
void OFB::decipher(string filename){
    cipher(filename);
}
void OFB::cipher(string filename){
    FILE * file = fopen(filename.c_str(), "r+");
    FILE * fileoutput = fopen("/Users/elena/Downloads/Output.txt", "w+");
    
    int size = 16;
    unsigned char * in = (unsigned char *) malloc(size);
    unsigned char ci[16];
    for(int i = 0; i < 16; ++i){
        ci[i] = iv[i];
    }
    while(fread(in, sizeof(unsigned char), size, file)){
        AES c(ci, 4);
        c.cipher();
        for(int i = 0; i < size; ++i){
            ci[i] = in[i]^c.output[i];
        }

        fwrite(ci, sizeof(unsigned char), size, fileoutput);
    }
    
    fclose(file);
    fclose(fileoutput);
    free(in);
}
