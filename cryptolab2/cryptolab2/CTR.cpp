#include "CTR.h"
#include "AES.h"
CTR::CTR(){
    for(int z = 0; z < 16; ++z){
        iv[z] = rand()%122;
    }
}
void CTR::cipher(string filename){
    FILE * file = fopen(filename.c_str(), "r+");
    FILE * fileoutput = fopen("/Users/elena/Downloads/Output.txt", "w+");
    
    int size = 16;
    unsigned char * in = (unsigned char *) malloc(size);
    unsigned char ci[16];
    for(int i = 0; i < 16; ++i){
        ci[i] = iv[i];
    }
    while(fread(in, sizeof(unsigned char), size, file)){
        ++ci[15];
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
void CTR::decipher(string filename){
    cipher(filename);
}