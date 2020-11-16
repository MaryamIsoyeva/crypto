#include <iostream>
#include "Num.h"
int main(int argc, const char * argv[])
{
/*//    for(int i = 0; i< 5;++i){
//        cout << i;
//        for(int j = 6; j< 9;++j){
//            cout <<j;
//            if(j==7){
//                break;
//            }
//        }
//    }*/

//    cout << "   Extended Euclidean algorithm\n";
//    cout << "ax + by = gcd(a, b)\n";
//    cout << "a : ";
//    string s;
//    cin >> s;
//    Num a = Num(s);
//    cout << "b : ";
//    cin >> s;
//    cout << "\n";
//    Num b = Num(s);
//    Num d (0), x(0), y(0);
//    Num(0).gcdExt(a, b, &d, &x, &y);
//    cout << "GCD: ";
//    d.printNum();
//    cout << "\nx: ";
//    x.printNum();
//    cout << "\ny: ";
//    y.printNum();
//    cout << "\n";
//    return 0;
    string s = "93911";
    if(Num(s).MillerRabinTest(3)){ cout << s << " is prime\n";}
    else {cout << s << " is composite\n";}
    
    Num(0).RSA(Num("3557"), Num("2579"), Num("111111"));
    Num(0).RSA(Num("1125899839733759"), Num("18014398241046527"), Num("111111"));
    Num(0).RSA(Num("263130836933693530167218012159999999"), Num("8683317618811886495518194401279999999"), Num("111111"));
    
    Num(0).RSAOAEP();
    
    return 0;
}

