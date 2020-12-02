#ifndef __cryptolab5__Num__
#define __cryptolab5__Num__

#include <iostream>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <string>
using namespace std;
class Num{
public:
    //private:
    vector<short int> n;
    short int sign;
    //public:
    Num();
    Num(string ns);
    Num(short int signn, vector<short int> numn);
    Num Add(Num on);
    Num Min(Num on);
    Num Mult(Num on);
    Num Div(Num on);
    Num Divv(Num on);
    Num DivMod(Num on);
    Num Mod(Num on);
    Num Pow(int n);
    Num Pow(Num on);
    Num MultInv(Num mod);
    Num System();
    Num ModAdd(Num on, Num m);
    Num ModMin(Num on, Num m);
    Num ModDiv(Num on, Num m);
    Num ModMult(Num on, Num m);
    Num ModPow(Num on, Num m);
    Num Divvec(Num on);
    Num IntSqrt();
    Num SqrtN();
    Num SqrtS();
    
    Num DivS(Num on);
    
    Num ModExt(Num b);
    Num DivLong(Num on);
    Num DivShort(Num on);
    Num DivDiv(Num on);
    Num DivBig(Num on);
    Num DivC(Num on);
    Num DivOp(Num on);
    Num DivBin(Num on);
    Num DivByTwo();
    void removeZeros();
    Num sqrtNum();
    Num division(const Num &lhs, const Num &rhs);
    void gcdExt(Num a, Num b, Num *d, Num *x, Num *y);
    Num ModInverse(Num mod);
    Num ModularPower(Num on , Num m);
    Num ToModPow(Num on, Num m);
    Num SqrtOfNum();
    Num sqrtDiv();
    Num Sqrtj();
    Num(int on);
    bool isOdd();
    int Compare(Num on);
    bool IsLess(Num on);
    bool IsGreater(Num on);
    bool IsEqual(Num on);
    vector<short int> sumn(vector<short int> s1, vector<short int> s2);
    vector<short int> minv(vector<short int> m1, vector<short int> m2);
    vector<short int> multv(vector<short int> m1, vector<short int> m2);
    void printNum();
    Num gcdRho(Num a, Num b);
    Num RhoPollard();
    Num RhoPollardDiscreteLog(Num beta, Num N);
    Num LegendreSymbol(Num p);
    Num longDivision(string number, Num divisor);
    Num RhoPollardN();
    int MobiusFunc(vector<Num> m);
    vector<Num> getFactors();
    Num EulerFunction();
    bool SolovayStrassen(int k);
    Num JacobiSymbol(Num b);
    Num ModMulPow(Num b, Num mod);
    Num gcd(Num b);
    bool SolovayStrassenTest(int k);
    Num ChippoloDiscreteRoot(Num p);
    Num modularPow(Num exp, Num mod);
    Num modular_power(Num exp, Num mod);
    vector<Num> factorization();
    Num module(Num m);
    vector<Num> multChippolo(Num a1, Num a2, Num w, Num power, Num p);
    vector<Num> multGroupChipolo(Num a1, Num a2, Num b1, Num b2);
    vector<Num> multChippoloBin(Num a1, Num a2, Num w, Num power);
    Num ElGamalSystem(/*Num N*/);
    vector<vector<Num>> Keys(Num prime, Num g, Num beta);
    void gcdExt(Num b, Num *d, Num *x, Num *y);
    //    void gcdExt(Num b, Num &d, Num &x, Num &y);
    vector<Num> gcdExt(Num a, Num b);
};

#endif /* defined(__cryptolab5__Num__) */
