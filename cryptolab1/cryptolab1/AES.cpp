#include "AES.h"
void AES::cipher(){
//    void * p = input;
//    memcpy(state, p, 16);
    for(int i = 0; i < nb; ++i){
        for(int j = 0; j < nb; ++j){
            state[i][j] = input[i+4*j];
        }
    }
    keyExpansion();
    addRoundKey(0);
    for (int round = 1; round <= nr-1; ++round){
        subBytes();
        shiftRows();
        mixColumns();
        addRoundKey(round);
    }
    subBytes();
    shiftRows();
    addRoundKey(nr);
    for(int i = 0; i < nb; ++i){
        for(int j = 0; j < nb; ++j){
            output[i + 4*j] = state[i][j];
        }
    }
}
void AES::invCipher(){
//    void * p = output;
//    memcpy(state, p, 16);
    for(int i = 0; i < nb; ++i){
        for(int j = 0; j < nb; ++j){
            state[i][j] = output[i+4*j];
        }
    }
    keyExpansion();
    addRoundKey(nr);
    int round = nr - 1;
    for(; round >=1; --round){
        invShiftRows();
        invSubBytes();
        addRoundKey(round);
        invMixColumns();
    }
    invShiftRows();
    invSubBytes();
    addRoundKey(round);
    for(int i = 0; i < nb; ++i){
        for(int j = 0; j < nb; ++j){
            decrypted[i+4*j] = state[i][j];
        }
    }
    
}
AES::AES(unsigned char inputbytes[], int nk_){
//    for(int i = 0; i < 4; ++i){
//        
//    }
    nk = nk_;
    if(nk==4){
        nr = 10;
        key = key128;
    }
    if(nk==6){
        nr = 12;
        key = key192;
    }
    if(nk==8){
        nr = 14;
        key = key256;
    }
//    for(int i = 0; i < nk*4; ++i){
//        cout << hex<< (int)key[i];
//    }
    memcpy(input, inputbytes, 16);
}
AES::AES(unsigned char outputbytes[], int nk_, int keysize){
    nk = nk_;
    if(nk==4){
        nr = 10;
        key = key128;
    }
    if(nk==6){
        nr = 12;
        key = key192;
    }
    if(nk==8){
        nr = 14;
        key = key256;
    }
    memcpy(output, outputbytes, 16);
}
void AES::subBytes(){
    unsigned char r, c;
    unsigned char subst;
    for(int i = 0; i < 4; ++i){
        for(int j = 0; j < nb; ++j){
            r = state[i][j] / 0x10;
            c = state[i][j] % 0x10;
            
            subst = sbox[16*r+c];
            state[i][j] = subst;
        }
    }
}
void AES::shiftRows(){
    unsigned char temp;
    temp = state[1][0];
    for(int i = 0; i < 3; ++i){
        state[1][i] = state[1][i+1];
    }
    state[1][3] = temp;
    
    temp = state[2][0];
    state[2][0] = state[2][2];
    state[2][2] = temp;
    temp = state[2][1];
    state[2][1] = state[2][3];
    state[2][3] = temp;
    
    temp = state[3][3];
    for(int i = 3; i > 0; --i){
        state[3][i] = state[3][i-1];
    }
    state[3][0] = temp;
    
}
void AES::invShiftRows(){
    unsigned char temp;
    temp = state[1][3];
    for(int i = 3; i > 0; --i){
        state[1][i] = state[1][i-1];
    }
    state[1][0] = temp;
    
    temp = state[2][3];
    state[2][3] = state[2][1];
    state[2][1] = state[2][3];
    temp = state[2][0];
    state[2][0] = state[2][2];
    state[2][2] = temp;
    
    temp = state[3][0];
    for(int i = 0; i < 3; ++i){
        state[3][i] = state[3][i+1];
    }
    state[3][3] = temp;
}
void AES::invSubBytes(){
    unsigned char r, c;
    unsigned char subst;
    for(int i = 0; i < 4; ++i){
        for(int j = 0; j < nb; ++j){
            r = state[i][j] / 0x10;
            c = state[i][j] % 0x10;
            
            subst = invSbox[16*r+c];
            state[i][j] = subst;
        }
    }
}
unsigned char AES::mul02(unsigned char n){
    unsigned char res;
    if(n<0x80){
        res = (n << 1);
    }
    else{
        res = (n << 1)^0x1b;
    }
    return res%0x100;
}
unsigned char AES::mul03(unsigned char n){
    return (mul02(n)^n);
}
unsigned char AES::mul09(unsigned char n){
    return (mul02(mul02(mul02(n)))^n);
}
unsigned char AES::mul0b(unsigned char n){
    return (mul02(mul02(mul02(n)))^mul02(n)^n);
}
unsigned char AES::mul0d(unsigned char n){
    return (mul02(mul02(mul02(n)))^mul02(mul02(n))^n);
}
unsigned char AES::mul0e(unsigned char n){
    return (mul02(mul02(mul02(n)))^mul02(mul02(n))^mul02(n));
}
void AES::mixColumns(){
    unsigned char s0, s1, s2, s3;
    for(int i = 0; i < nb; ++i){
        s0 = mul02(state[0][i])^mul03(state[1][i])^state[2][i]^state[3][i];
        s1 = state[0][i]^mul02(state[1][i])^mul03(state[2][i])^state[3][i];
        s2 = state[0][i]^state[1][i]^mul02(state[2][i])^mul03(state[3][i]);
        s3 = mul03(state[0][i])^state[1][i]^state[2][i]^mul02(state[3][i]);
        
        state[0][i] = s0;
        state[1][i] = s1;
        state[2][i] = s2;
        state[3][i] = s3;
    }
    
}
void AES::invMixColumns(){
    unsigned char s0, s1, s2, s3;
    for(int i = 0; i < nb; ++i){
        s0 = mul0e(state[0][i])^mul0b(state[1][i])^mul0d(state[2][i])^mul09(state[3][i]);
        s1 = mul09(state[0][i])^mul0e(state[1][i])^mul0b(state[2][i])^mul0d(state[3][i]);
        s2 = mul0d(state[0][i])^mul09(state[1][i])^mul0e(state[2][i])^mul0b(state[3][i]);
        s3 = mul0b(state[0][i])^mul0d(state[1][i])^mul09(state[2][i])^mul0e(state[3][i]);
        
        state[0][i] = s0;
        state[1][i] = s1;
        state[2][i] = s2;
        state[3][i] = s3;
    }
}
void AES::keyExpansion(){
    //copy initial key
    for(int i = 0; i < nb; ++i){
        for(int j = 0; j < nk; ++j){
            keyScheduleAES[i][j] = key[i+4*j];
        }
    }
/*    if(nk == 4){
        memcpy(keyScheduleAES, key128, nk*4);
        
    }
    if(nk == 6){
        memcpy(keyScheduleAES, key192, nk*4);
    }
    if(nk == 8){
        memcpy(keyScheduleAES, key256, nk*4);
    }*/
    for(int i = 0; i < nb; ++i){
        for(int j = 0; j < nk*4; ++j){
            cout << hex << (int)keyScheduleAES[i][j] <<" ";
        }
        cout << "\n";
    }
    unsigned char s;
    unsigned char tmp[4];
    unsigned char sboxr, sboxc, sboxe;
    for(int c = nk; c < nb*(nr+1); ++c){
        if(c % nk == 0){
            //shift
            for(int i = 1; i<=3; ++i){
                tmp[i-1] = keyScheduleAES[i][c-1];
            }
            tmp[3] = keyScheduleAES[0][c-1];
            for(int j = 0; j < nb; ++j){
                sboxr = (tmp[j] / 0x10);
                sboxc = (tmp[j] % 0x10);
                sboxe = sbox[16*sboxr+sboxc];
                tmp[j] = sboxe;
            }
            for(int r = 0; r < nb; ++r){
                s = (keyScheduleAES[r][c-4])^(tmp[r])^(rcon[r][c/nk-1]);
                keyScheduleAES[r][c] = s;
            }
            
        }
        else{
            for(int r = 0; r < nb; ++r){
                s = keyScheduleAES[r][c-4]^keyScheduleAES[r][c-1];
                keyScheduleAES[r][c] = s;
            }
        }
    }
    for(int i = 0; i < nb; ++i){
        for(int j = 0; j < (nb*(nr+1)); ++j){
            cout << hex << (int)keyScheduleAES[i][j] <<" ";
        }
        cout << "\n";
    }
}
void AES::addRoundKey(int round){
    unsigned char s0, s1, s2, s3;
    for(int c = 0; c < nk; ++c){
        s0 = state[0][c] ^ keyScheduleAES[0][nb*round+c];
        s1 = state[1][c] ^ keyScheduleAES[1][nb*round+c];
        s2 = state[2][c] ^ keyScheduleAES[2][nb*round+c];
        s3 = state[3][c] ^ keyScheduleAES[3][nb*round+c];
        
        state[0][c] = s0;
        state[1][c] = s1;
        state[2][c] = s2;
        state[3][c] = s3;
    }
    
}
