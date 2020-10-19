#include <iostream>
#include "RC4.h"
#include "Salsa20.h"
#include "CBC.h"
#include "CFB.h"
#include "ECB.h"
#include "CTR.h"
#include "OFB.h"
using namespace std;
int main(int argc, const char * argv[])
{
    unsigned char buf[5] = {'a', 'b', 'c', 'd', 'e'};
    RC4 c("");
    c.cipher(buf, 5);
    RC4 dc(c.key);
    dc.decipher(c.ciphered);
//    for(int z = 0; z < dc.deciphered.size(); ++z){
//        cout << dc.deciphered[z] << " ";
//    }
//    cout << "\n";
    
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
    
    OFB ofb1;
    begin = std::chrono::steady_clock::now();
    ofb1.cipher("/Users/elena/Downloads/10mb.txt");
    end = std::chrono::steady_clock::now();
    cout << "Ciphering time for OFB " << chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "ms" << "\n";
    
    CTR ctr1;
    begin = std::chrono::steady_clock::now();
    ctr1.cipher("/Users/elena/Downloads/10mb.txt");
    end = std::chrono::steady_clock::now();
    cout << "Ciphering time for CTR " << chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "ms" << "\n";
    
    return 0;
}

