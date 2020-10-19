#include "CFB.h"
#include "AES.h"
CFB::CFB(){
    for(int z = 0; z < 16; ++z){
        iv[z] = rand()%122;
    }
}
void CFB::decipher(string filename){
    FILE * file = fopen(filename.c_str(), "r+");
    FILE * fileoutput = fopen("/Users/elena/Downloads/Output.txt", "w+");
    
    int size = 11;
    unsigned char * in = (unsigned char *) malloc(size);
    unsigned char ci[16];
    unsigned char cipheredTextOutput[16];
    for(int i = 0; i < 16; ++i){
        ci[i] = iv[i];
        cipheredTextOutput[i] = iv[i];
    }
    while(fread(in, sizeof(unsigned char), size, file)){

        AES c(cipheredTextOutput, 4);
        c.cipher();
        for(int i = 0; i < size; ++i){
            ci[i] = in[i]^c.output[i];
            cipheredTextOutput[i] = c.output[i];
        }

        fwrite(ci, sizeof(unsigned char), size, fileoutput);
    }
    
    fclose(file);
    fclose(fileoutput);
    free(in);

}
void CFB::cipher(string filename){
    FILE * file = fopen(filename.c_str(), "r+");
    FILE * fileoutput = fopen("/Users/elena/Downloads/Output.txt", "w+");
    
    int size = 11;
    unsigned char * in = (unsigned char *) malloc(size);
    unsigned char ci[16];
    for(int i = 0; i < 16; ++i){
        ci[i] = iv[i];
    }
    while(fread(in, sizeof(unsigned char), size, file)){
        //        cout << in[0];
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