#include "ECB.h"
#include "AES.h"
void ECB::cipher(string filename){
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
void ECB::decipher(string filename){
    FILE * file = fopen(filename.c_str(), "r+");
    FILE * fileoutput = fopen("/Users/elena/Downloads/DecipherOutput.txt", "w+");
    int size = 16;
    unsigned char * in = (unsigned char *) malloc(size);
    chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    while(fread(in, sizeof(unsigned char), size, file)){
        AES c(in, 4, 16);
        c.invCipher();
        fwrite(c.decrypted, sizeof(unsigned char), size, fileoutput);
    }
    chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Deciphering time " << chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "ms" << "\n";
    fclose(file);
    fclose(fileoutput);
    free(in);
}