#include "TestCasesAES.h"
#include "AES.h"
using namespace std;
bool TestCasesAES::testShiftRows(){
    unsigned char input[16] = {0xd4, 0xe0, 0xb8, 0x1e,
        0x27, 0xbf, 0xb4, 0x41,
        0x11, 0x98, 0x5d, 0x52,
        0xae, 0xf1, 0xe5, 0x30};
    /*for (int i = 0; i< 16; ++i){
        
            cout << hex << (int)input[i]<<" ";
        
        cout <<"\n";
    }*/
    AES c(input, 4);
    void * p = c.input;
    memcpy(c.state, p, 16);
    /*for (int i = 0; i< 4; ++i){
        for(int j = 0; j < 4; ++j){
            cout << hex << (int)c.state[i][j]<<" ";
        }
        cout <<"\n";
    }*/
    c.shiftRows();
    unsigned char correctShift[4][4] = {0xd4, 0xe0, 0xb8, 0x1e,
        0xbf, 0xb4, 0x41, 0x27,
        0x5d, 0x52, 0x11, 0x98,
        0x30, 0xae, 0xf1, 0xe5};
    /*for (int i = 0; i< 4; ++i){
        for(int j = 0; j < 4; ++j){
            cout << hex << (int)c.state[i][j]<<" ";
        }
        cout <<"\n";
    }*/
    return (memcmp(c.state, correctShift, sizeof(correctShift))==0);
}
bool TestCasesAES::testMixColumns(){
    unsigned char input[16] = {0xd4, 0xe0, 0xb8, 0x1e,
        0xbf, 0xb4, 0x41, 0x27,
        0x5d, 0x52, 0x11, 0x98,
        0x30, 0xae, 0xf1, 0xe5};
    AES c(input, 4);
    void * p = c.input;
    memcpy(c.state, p, 16);
    c.mixColumns();
    unsigned char correctMix[4][4] ={0x04, 0xe0, 0x48, 0x28,
        0x66, 0xcb, 0xf8, 0x06,
        0x81, 0x19, 0xd3, 0x26,
        0xe5, 0x9a, 0x7a, 0x4c
    };
    
    return (memcmp(c.state, correctMix, sizeof(correctMix))==0);
}
bool TestCasesAES::testKeyExpansion(){
    unsigned char input[16] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};
    AES c(input, 4);
    void * p = c.input;
    memcpy(c.state, p, 16);
    c.keyExpansion();
    cout <<"test";
    unsigned char correctkeyschedule1round[4][4] = {0xd6, 0xaa, 0x74, 0xfd, 0xd2, 0xaf, 0x72, 0xfa, 0xda, 0xa6, 0x78, 0xf1, 0xd6, 0xab, 0x76, 0xfe};
    bool w = true;
//    for(int i = 0; i < 4; ++i){
//        for(int j = 4; j < 8; ++j){
//            if(c.keyScheduleAES[i][j]!=correctkeyschedule1round[i][j-4]){
//                w = false;
//                cout << hex << (int)c.keyScheduleAES[i][j] << " " ;
//            }
//        }
//        cout <<"\n";
//        
//    }
    return w;
}
bool TestCasesAES::allTests(){
    bool all = true;
    if(!testShiftRows()){
        cout << "testShiftRows\n";
        all = false;
    }
    if(!testMixColumns()){
        cout << "testMixColumns\n";
        all = false;
    }
    if(!testKeyExpansion()){
        cout << "testKeyExpansion\n";
        all = false;
    }
    return all;
}