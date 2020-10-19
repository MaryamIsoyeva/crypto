#include <iostream>
#include "RC4.h"
#include "Salsa20.h"
#include "CBC.h"
#include "CFB.h"
#include "ECB.h"
#include "CTR.h"
using namespace std;
//void m(uint32_t x[16], int a, int b, int c, int d){
//    x[a] = 9;
//}
int main(int argc, const char * argv[])
{
    unsigned char buf[5] = {'a', 'b', 'c', 'd', 'e'};
    RC4 c("");
    c.cipher(buf, 5);
    RC4 dc(c.key);
    dc.decipher(c.ciphered);
    for(int z = 0; z < dc.deciphered.size(); ++z){
        cout << dc.deciphered[z] << " ";
    }
    cout << "\n";
    
//Test on file
    RC4 cFile("");
    chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    cFile.cipher("/Users/elena/Downloads/10mb.txt");
    chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    cout << "Ciphering time for RC4 " << chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "ms" << "\n";
    
    RC4 dcFile(cFile.key);
    begin = std::chrono::steady_clock::now();
    dcFile.decipher(cFile.ciphered);
    dcFile.deciphered.clear();
    cFile.ciphered.clear();
    end = std::chrono::steady_clock::now();
//    cout << "Deciphering time for RC4 " << chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "ms" << "\n";
    
    
    unsigned char input[16] = {0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34};
    unsigned char key[16] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};

//    uint32_t v[16] = {1, 2, 3, 4, 5, 6,7,8,8,10,11,12,13,14,15,16};
//    for(int z = 0; z < 16; ++z){
//        cout << v[z] << " ";
//    }
//    m(v, 1, 2, 3,4);
//    cout <<"\n";
//    for(int z = 0; z < 16; ++z){
//        cout << v[z] << " ";
//    }
    
    Salsa20 s;
    begin = std::chrono::steady_clock::now();
    s.cipher("/Users/elena/Downloads/10mb.txt");
    end = std::chrono::steady_clock::now();
    cout << "Ciphering time for Salsa20 " << chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "ms" << "\n";
    
    ECB ecb1;
    begin = std::chrono::steady_clock::now();
    ecb1.cipher("/Users/elena/Downloads/10mb.txt");
    end = std::chrono::steady_clock::now();
    cout << "Ciphering time for ECB " << chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "ms" << "\n";
    
    CBC cbc1;
    begin = std::chrono::steady_clock::now();
    cbc1.cipher("/Users/elena/Downloads/10mb.txt");
    end = std::chrono::steady_clock::now();
    cout << "Ciphering time for CBC " << chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "ms" << "\n";
//    begin = std::chrono::steady_clock::now();
//    cbc1.decipher("/Users/elena/Downloads/10mb.txt");
//    end = std::chrono::steady_clock::now();
//    cout << "Deciphering time for CBC " << chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "ms" << "\n";
    
    CFB cfb1;
    begin = std::chrono::steady_clock::now();
    cfb1.cipher("/Users/elena/Downloads/10mb.txt");
    end = std::chrono::steady_clock::now();
    cout << "Ciphering time for CFB " << chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "ms" << "\n";
//    begin = std::chrono::steady_clock::now();
//    cfb1.decipher("/Users/elena/Downloads/10mb.txt");
//    end = std::chrono::steady_clock::now();
//    cout << "Deciphering time for CBC " << chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "ms" << "\n";
    
    CTR ctr1;
    begin = std::chrono::steady_clock::now();
    ctr1.cipher("/Users/elena/Downloads/10mb.txt");
    end = std::chrono::steady_clock::now();
    cout << "Ciphering time for CTR " << chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "ms" << "\n";
    
    return 0;
}

