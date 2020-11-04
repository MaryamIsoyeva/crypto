#include <iostream>
#include "SHA256.h"
using namespace std;
void proofOfWork(bool sha, int n){
    chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    if(sha){
        bool zero = false;
        unsigned char mes[64] = {'a', 'b', 'c', 'd', 'e'};
        unsigned char x = 'a';
          int c = 1;
        while(!zero){
            SHA256 s;
            for(int i = 0; i < c; ++i){
                mes[63-i] = x++;
                if(x > 'y'){
                    x = 'a';
                }
            }
            if(x > 'y'){
                ++c;
                if(c>62){
                    c = 1;
                }
            }
            s.hash(mes, 64);
            uint32_t shifted = (1 << (32 - n-1));
            if (s.hashv[0] < shifted){
                zero = true;
            }
//        s.hash(
        }
    }
    else{
        
    }
    chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time for " << n << " zeroes " << chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "ms" << "\n";
}

int main(int argc, const char * argv[])
{
//    int i;
//    for(i = 0; i < 5; ++i){
//       
//    }
//    
//    std::cout << i;
//    std::cout << "Proof of work";
    int n = 1;
//    proofOfWork(true, n);
    
    
    proofOfWork(true, n);
    
//    uint32_t shifted = (1 << (31));
//    cout << shifted;
//    uint32_t one = 1;
//    cout << (one << (31));
//    uint32_t shifted = (1 << (32 - 3 -1));
//    cout << shifted;
    return 0;
}

