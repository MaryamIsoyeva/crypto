#include "SHA256.h"
SHA256::SHA256(){
    hashv[0] = 0x6a09e667;
    hashv[1] = 0xbb67ae85;
    hashv[2] = 0x3c6ef372;
    hashv[3] = 0xa54ff53a;
    hashv[4] = 0x510e527f;
    hashv[5] = 0x9b05688c;
    hashv[6] = 0x1f83d9ab;
    hashv[7] = 0x5be0cd19;
}

void SHA256::hash(unsigned char m_[], int l){
    if(l<64){
        int i;
        for(i = 0; i < l; ++i){
            m[i] = m_[i];
        }
        m[i] = 0x80;
        m[63] = l % 2;
        m[62] = l % 4;
        m[61] = l % 8;
        m[60] = l % 16;
    }
    else{
        for(int i = 0; i < l; ++i){
            m[i] = m_[i];
        }
    }
    int i;
    for(i = 0; i <= 15; ++i){
        schedule[i] = m[i];
    }
    for(;i<=63;++i){
        schedule[i] = sigma1small(schedule[i-2]) + schedule[i-7]+ sigma0small(schedule[i-15]) + schedule[i-16];
    }
    a = hashv[0];
    b = hashv[1];
    c = hashv[2];
    d = hashv[3];
    e = hashv[4];
    f = hashv[5];
    g = hashv[6];
    h = hashv[7];
    
    uint32_t T1, T2;
    for(int t = 0; t <= 63; ++t){
        T1 = h + sigma1(e) + CH(e, f, g) + constants[t] + schedule[t];
        T2 = sigma0(a) + MAJ(a, b, c);
        h = g;
        g = f;
        f = e;
        e = d + T1;
        d = c;
        c = b;
        b = a;
        a = T1 + T2;
    }
    
    hashv[0] = a + hashv[0];
    hashv[1] = b + hashv[1];
    hashv[2] = c + hashv[2];
    hashv[3] = d + hashv[3];
    hashv[4] = e + hashv[4];
    hashv[5] = f + hashv[5];
    hashv[6] = g + hashv[6];
    hashv[7] = h + hashv[7];
}

uint32_t SHA256::sigma0small(uint32_t x){
    return (ROTR(x,  7) ^ ROTR(x, 18) ^ SHFR(x,  3));
}
uint32_t SHA256::sigma1small(uint32_t x){
    return (ROTR(x, 17) ^ ROTR(x, 19) ^ SHFR(x, 10));
}
uint32_t SHA256::sigma0(uint32_t x){
    return (ROTR(x,  2) ^ ROTR(x, 13) ^ ROTR(x, 22));
}
uint32_t SHA256::sigma1(uint32_t x){
    return (ROTR(x,  6) ^ ROTR(x, 11) ^ ROTR(x, 25));
}
void SHA256::hashSeq(string s){
//    string
}
