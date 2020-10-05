#ifndef __cryptolab1__TestCasesAES__
#define __cryptolab1__TestCasesAES__

#include <iostream>
class TestCasesAES{
public:
    bool testShiftRows();
    bool testMixColumns();
    bool testKeyExpansion();
    bool testinvShiftRows();
    bool testCipher();
    bool testCipherText();
    bool allTests();
};
#endif /* defined(__cryptolab1__TestCasesAES__) */
