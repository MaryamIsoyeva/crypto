#include "Num.h"
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
using namespace std;
Num::Num(){
    
}
Num::Num(string ns){
    if (ns[0] == '-') {
        sign = -1;
        for(int i = 1; i < ns.length(); ++i){
            n.push_back(ns[i] - '0');
        }
    }
    else {
        sign = 1;
        for(int i = 0; i < ns.length(); ++i){
            n.push_back(ns[i] - '0');
        }
    }
}
Num ::Num(short int signn, vector<short int> numn){
    sign = signn;
    n = numn;
}

vector<short int> Num::sumn(vector<short int> s1, vector<short> s2){
    vector<short int> v1 = s1;
    vector<short int> v2 = s2;
    vector<short int>::iterator it;
    vector<short int> sum;
    vector<short int>::iterator its;
    
    size_t diflen = 0;
    if(v1.size()!= v2.size()){
        if(v1.size() > v2.size()){
            diflen = v1.size() - v2.size();
            it = v2.begin();
            v2.insert(it, diflen, 0);
        }
        else{
            diflen = v2.size() - v1.size();
            it = v1.begin();
            v1.insert(it, diflen, 0);
            
        }
    }
    int c = 0;
    int s = 0;
    for(size_t i = v1.size() - 1; i != (size_t) -1; --i){
        s = v1[i] + v2[i] + c;
        c = s / 10;
        if(s >= 10) sum.push_back(s%10);
        else sum.push_back(s);
        
        
    }
    if(c !=0)
        sum.push_back(c);
    
    reverse(sum.begin(), sum.end());
    return sum;
}
Num Num :: Add(Num on){
    vector<short int> sum;
    if(sign == -1 && on.sign == -1){
        sum = sumn(n, on.n);
        return Num(-1, sum);
    }
    if (sign == 1 && on.sign == 1){
        sum = sumn(n, on.n);
        return Num(1, sum);
    }
    else {
        if(sign == -1)
        {
            Num ns = on.Min(Num(1, n));
            return ns;
            
        }
        else {
            return this -> Min(Num(1, on.n));
        }
    }
}
Num Num::Min(Num on){
    vector<short int> sub;
    if(sign == -1 && on.sign == -1){
        return this -> Add(Num(1, on.n));
    }
    if(sign == 1 && on.sign == 1){
        if(this -> Compare(on) == 1){
            return Num(1, minv(n, on.n));
        }
        if(this -> Compare(on) == -1){
            return Num(-1, minv(on.n, n));
        }
        if(this -> Compare(on) == 0){
            sub.push_back(0);
            return Num(1, sub);
        }
    }
    if(sign == -1 && on.sign == 1){
        return Num(-1, sumn(n, on.n));
        
    }
    if(sign == 1 && on.sign == -1){
        return Num(1, sumn(n, on.n));
    }
    else { sub.push_back(0);return Num(1, sub); }
    
}

vector<short int> Num:: minv(vector<short int> m1, vector<short int> m2){
    vector<short int> m1v = m1;
    vector<short int> m2v = m2;
    reverse(m1v.begin(), m1v.end());
    reverse(m2v.begin(), m2v.end());
    if(m1v.size()!= m2v.size()){
        if(m1v.size() > m2v.size()){
            int diflen = m1v.size() - m2v.size();
            while(diflen != 0){
                m2v.push_back(0);
                --diflen;
            }
        }
        else{
            int diflen = m2v.size() - m1v.size();
            while(diflen != 0){
                m1v.push_back(0);
                --diflen;
            }
        }
    }
    vector<short int> res = m1v;
    for (int i = 0;i<res.size();i++)
    {
        res[i] -= m2v[i];
        if (res[i]<0)
        {
            res[i]+=10;
            res[i+1]--;
        }
    }
    int pos = res.size() - 1;
    while(pos && ! res[pos]){
        res.pop_back();
        --pos;
    }
    reverse(res.begin(), res.end());
    return res;
    
    
    
}
/**
 returns 1 if this is greater
 -1 if this is less
 0 if equal
 */
int Num::Compare(Num on){
    size_t thislen = this->n.size();
    size_t onlen = on.n.size();
    if(sign == -1 && on.sign != -1) return -1;
    if(sign == 1 && on.sign == -1) return 1;//sign
    if(thislen > onlen) return 1;
    if(thislen < onlen) return -1;
    size_t i = 0;
    
    //    size_t i = thislen;
    while(i < thislen) {
        if(this->n[i] > on.n[i]) return 1;
        if(this->n[i] < on.n[i]) return -1;
        else { i = i+1; /*continue;*/}
        
    }
    return 0;
}

Num Num:: Mult(Num on){
    vector<short int> mul;
    if((n.size() == 1 && n[0] == 0) || ( on.n.size() == 1 && on.n[0] == 0) ) { mul.push_back(0); return Num(1, mul);}
    if(sign == -1 && on.sign == -1){
        return Num(1, multv(n, on.n));
    }
    if(sign == 1 && on.sign == 1){
        Num m(1, multv(n, on.n));
        return m;
    }
    if(sign == -1 || on.sign == -1){
        return Num(-1, multv(n, on.n));
    }
    
    mul.push_back(0);
    return Num(1, mul);
    
}
vector<short int> Num:: multv(vector<short int> m1, vector<short int> m2){
    vector<short int> mul;
    vector<short int>::iterator its = mul.begin();
    int c = 0;
    int m = 0;
    
    vector<short int> v1 = m1;
    vector<short int> v2 = m2;
    
    reverse(v1.begin(), v1.end());
    reverse(v2.begin(), v2.end());
    mul.insert(its, v1.size()+v2.size() + 2, 0);
    for(size_t i = 0; i < v1.size(); ++i){
        for(size_t j = 0; j < v2.size(); ++j){
            mul[i+j] += v1[i] * v2[j];
        }
    }
    for(size_t n = 1; n < mul.size(); ++n){
        mul[n] += mul[n - 1] /10;
        mul[n-1] = mul[n-1] % 10;
    }
    while(mul.back() == 0){
        mul.pop_back();
    }
    reverse(mul.begin(), mul.end());
    return mul;
}
Num Num::Divvec(Num on){
    return Num(1, vector<short int> (1, 1));
    
}
Num Num:: Div(Num on){
    vector<short int> divn;
    if (this -> Compare(on) == 0) return Num("1");
    if(Num(1, n).Compare(Num(1, on.n)) == 0) {return Num(sign*on.sign , vector<short int>(1, 1));}
    if (this -> Compare(on) == -1 && sign > 0 && on.sign >0){ divn.push_back(0); return Num(1, divn);}
    if(on.n.size() == 1 && on.n[0] == 0) {cout<< "\n cannot divide by zero"; divn.push_back(0); return Num(1, divn);}
    if(n.size() == 1 && n[0] == 0){ divn.push_back(0); return Num(1, divn);}
    
    Num v1 = Num(1, n);
    Num v2 = Num(1, on.n);
    Num divnum = Num(1, vector<short int> (1, 0));
    Num modnumb = Num(1, n);
    do{
        modnumb = modnumb.Min(v2);
        divnum.n = sumn(divnum.n, vector<short int>( 1, 1));
        
    } while(modnumb.Compare(v2) >= 0);
    return Num(sign* on.sign, divnum.n);
    
    
    Num modNum = Num(1, n);
    
    vector<short int> divv = vector<short int> (1, 0);
    Num divnn = Num(1, divv);
    Num thisn = Num(1, n);
    Num onn = Num (1, on.n);
    do {
        modNum = modNum.Min(onn);
        divnn.n = sumn(  divnn.n, vector<short int>( 1, 1));
        
    }while(modNum.Compare(onn) >= 0);
    
    divnn.sign = sign * on.sign;
    return divnn;
}
Num Num::Divv(Num on){
    vector<short int> divn;
    if (this -> Compare(on) == 0) { divn.push_back(1); return Num(1, divn);}
    if (this -> Compare(on) == -1){ divn.push_back(0); return Num(1, divn);}
    if(on.n.size() == 1 && on.n[0] == 0) {cout<< "\n cannot divide by zero"; divn.push_back(0); return Num(1, divn);}
    if(n.size() == 1 && n[0] == 0){ divn.push_back(0); return Num(1, divn);}
    vector<short int> divv;
    divv.insert(divv.begin(), n.size(), 0);
    vector<short int> modv;
    modv.push_back(0);
    Num mod = Num(1, modv);
    Num div = Num(1, divv);
    vector<short int>::iterator itdiv;
    itdiv = divv.begin();
    vector<short int>::iterator itmod;
    itmod = modv.begin();
    
    vector<short int> ten;
    ten.push_back(1); ten.push_back(0);
    
    for(size_t i = 0; i < n.size(); ++i){
        mod = mod.Mult(Num(1, ten));
        mod.n[mod.n.size() - 1] = n[i];
        while(mod.Compare(on) >= 0){
            mod = mod.Min(on);
            div.n[i] = div.n[i] +1 ;
        }
    }
    while(div.n.size() > 1 && !div.n[div.n.size() -1]) div.n.erase(div.n.begin(), div.n.begin() + 1);
    
    
    cout<<"remainder: "; mod.printNum();
    cout<<"\n";
    cout<< "quotient: " ; div.printNum();
    
    return div;
}


Num Num::Mod(Num on){
    if ((this->sign == -1)&& (on.sign == -1)){
        Num v1 = Num(1, n);
        Num v2 = Num(1, on.n);
        int comparen = v1.Compare(v2);
        if(comparen == -1) return *this;
        vector<short int> modm;
        if(comparen == 0) {modm.push_back(0); return Num(1, modm);}
        modm = this -> n;
        Num modNum = Num(1, modm);
        do{
            modNum = modNum.Min(v2);
        }while(modNum.Compare(v2) >= 0);
        
        return Num(-1, modNum.n);
        
        
    }
    if (((this->sign == -1)&& (on.sign != -1)  )|| ((on.sign == -1) && (sign != -1) )){
        Num divid = this -> Div(on);
        Num c = divid.Mult(on);
        return this -> Min(c);
        
        
    }
    int comparen = this -> Compare(on);
    if(comparen == -1) return *this;
    vector<short int> modm;
    if(comparen == 0) {modm.push_back(0); return Num(1, modm);}
    modm = this -> n;
    Num modNum = Num(1, modm);
    do{
        modNum = modNum.Min(on);
    }while(modNum.Compare(on) >= 0);
    return modNum;
}
Num Num::Pow(int n){
    vector<short int> powv;
    if(n == 0){ powv.push_back(1); return Num(1, powv);}
    if(n == 1){ return *this;}
    if(n%2!=0){
        return this -> Mult((this->Mult(*this).Pow( (n-1)/2)));
        
        
    }
    else{
        return (this->Mult(*this)).Pow(n/2);
    }
    
}
bool Num::isOdd(){
    if(n.back() % 2 != 0) return true;
    else return false;
}
Num Num:: Pow(Num on){
    vector<short int> powv;
    if(n.size() == 1 && n[0] == 0) { powv.push_back(0); return Num(1, powv);}
    if(on.n.size() == 1 && on.n[0] == 0){ powv.push_back(1); return Num(1, powv);}
    if(n.size() == 1 && n[0] == 0){ return *this;}
    if(on.isOdd()){
        return this -> Mult((this->Mult(*this)).Pow(on.Min(Num(1, vector<short int>(1, 1))).Div(Num(1, vector<short int>(1, 2)))) );
        
    }
    else{
        return (this->Mult(*this)).Pow(on.Div(Num(1, vector<short int>(1, 2)) ));
    }
    
    
}
Num Num::MultInv(Num mod){
    Num t = Num("0");
    Num newt = Num("1");
    Num r = mod;
    Num newr = *this;
    Num prov = Num("1");
    Num quot = Num("0");
    while(newr.Compare(Num("0"))){
        quot = r.Div(newr);
        prov = newt;
        newt = t.Min(quot.Mult(prov));
        t = prov;
        
        prov = newr;
        newr = r.Min(quot.Mult(prov));
        r = prov;
    }
    if(r.Compare(Num("1")) > 0) { cout << "number is not invertible"; return Num("1");}
    if(t.Compare(Num("0")) < 0 ) { t = t.Add(mod);}
    return t;
    
    
}
Num Num::System(){
    cout<< "\nSystem of congruences x = c_i (mod m_i)\nPlease, enter parameters, when done enter\'q\'\n";
    string c;
    string m;
    int i = 0;
    string q;
    vector<Num> systemc;
    vector<Num> systemm;
    do{
        cout<<"c_" << i << ": ";
        cin >> c;
        systemc.push_back(Num(c));
        cout<<"m_" << i <<": ";
        cin >> m;
        systemm.push_back(Num(m));
        ++i;
        cout<< "Enter \'q\' to quit, \'c\' to continue";
        cin>>q;
    } while(q != "q");
    vector<Num> systemn;
    Num x = Num("0");
    Num mn = Num("1");
    Num cm = Num("1");
    for(size_t i = 0 ; i < systemc.size(); ++i){
        mn = mn.Mult(systemm[i]);
    }
    vector<Num> systemms;
    Num ms = Num("1");
    for(size_t s = 0 ; s < systemm.size(); ++s){
        ms = mn.Div(systemm[s]);
        systemms.push_back(ms);
        systemn.push_back( ms.MultInv(systemm[s]));
        
    }
    for(size_t j = 0 ; j < systemc.size(); ++j){
        x = x.Add((systemms[j].Mult(systemn[j]).Mult(systemc[j])).module(mn));
        
    }
    cout<<"x = "; x.module(mn).printNum() ; cout<<" mod "; mn.printNum(); cout<<"\n";
    return x.module(mn);
    
}
Num Num:: ModAdd(Num on, Num m){
    return ((this->Mod(m)).Add(on.Mod(m))).Mod(m); //+m for negative?
}
Num Num::ModMin(Num on, Num m){
    return ((this->Mod(m)).Min(on.Mod(m))).Mod(m);
}
Num Num::ModMult(Num on , Num m){
    return ((this->Mod(m)).Mult(on.Mod(m))).Mod(m);
}
Num Num::ModPow(Num on, Num m){
    vector<short int> powv;
    if(n.size() == 1 && n[0] == 0) { powv.push_back(0); return Num(1, powv);}
    if(n.size() == 1 && n[0] == 0){ return *this;}
    powv.push_back(0);
    Num nm = Num(1, powv);
    if(on.n.size() >0 && ! on.isOdd()) {
        
        nm = this -> ModPow(on.DivOp(Num(2)), m);
        nm = nm.Mult(nm).module(m);
    }
    else {
        if(on.n.size()>0){
            nm = this -> Mod(m);
            nm = (nm.Mult(this->ModPow(on.Min(Num("1")), m).module(m))).module(m);
        }
    }
    return nm.module(m);
}

Num Num::IntSqrt(){
    if(sign == -1) {cout<< "cannot take sqrt of negative number"; return *this;}
    if(n.size() == 1 && (n[0] == 0 || n[0] == 1)){
        return *this;
    }
    
    Num l = Num(1, vector<short int>(1, 0));
    Num res = Num(1, vector<short int>(1, 0));
    Num r = *this;
    while (l.Compare(r)< /*=*/ 0){
        Num m = (l.Add(r)).DivOp(Num("2"));
        if((m.Mult(m)).Compare(*this) <= 0){
            res = m;
            l = m.Add(Num("1"));
        }
        else {
            r = m.Min(Num("1"));
        }
    }
    
    return res;
    
    
}

Num Num :: SqrtN(){
    if(sign == -1) {cout<< "cannot take sqrt of negative number"; return *this;}
    if(n.size() == 1 && (n[0] == 0 || n[0] == 1)){
        return *this;
    }
    Num s = Num("1");
    Num b = *this;
    vector<short int> sqrtv;
    vector<short int> midv;
    Num sqr = Num(1, sqrtv);
    Num mid = Num(1, midv);
    while(s.Compare(b) <= 0){
        mid = (s.Add(b)).DivOp(Num("2"));
        Num mult = mid.Mult(mid);
        if(mult.Compare(*this) == 0){
            return mid;
        }
        if(mult.Compare(*this) < 0)
        {
            s = mid.Add(Num(1, vector<short int>(1, 1)));
            sqr = mid;
        }
        else{
            b = mid.Min(Num(1, vector<short int>(1, 1)));
        }
    }
    return sqr;
    
}
Num Num::ModDiv(Num on, Num m){
    Num onmod = on.module(m);
    if(on.Compare(Num(0)) == 0 || onmod.Compare(Num(0)) == 0){cout<<"cannot divide by zero"; return Num(0);}
    //check whether coprime
    Num d(0);
    Num* dp = &d;
    Num x(0);
    Num * px = &x;
    Num y(0);
    Num *yp = &y;
    gcdExt(*this, on, dp, px, yp);
    if(d.Compare(Num(1)) != 0){
        cout << "second argument and mod are not co-prime so modular division is not definied\n";
        return Num(0);
    }
    Num v1 (*this);
    v1 = v1.module(m);
    Num modInv =  ((x.module(m)).Add(m)).module(m);
    return modInv.Mult(v1).module(m);
}

Num Num::SqrtS(){
    if(sign == -1) {cout<< "cannot take sqrt of negative number"; return *this;}
    if(n.size() == 1 && (n[0] == 0 || n[0] == 1)){
        return *this;
    }
    Num s = Num(1, vector<short int>(1, 0 /*1*/));
    while(s.Mult(s).Compare(*this) < /*<= */0){
        s = s.Add(Num("1"));
    }
    return s;
    do{
        s = s.Add(Num("1"));
    }
    while(s.Mult(s).Compare(*this) < /*<= */0);
    return s;
    
}


Num Num:: ModExt(Num b){
    return this->Min((this-> Div(b)).Mult(b));
}
Num Num::DivDiv(Num on){
    Num c = Num("1");
    Num cur = Num("0");
    Num left = Num("0");
    Num v1 = Num(1, n);
    Num v2 = Num(1, on.n);
    int m = (int) v1.n.size() - v1.n.size();
    int diflen = m;
    if ( Num(1, vector<short int>(v1.n.begin(), v1.n.begin() + v2.n.size() ) ).Compare(v2) < 0){
        m = m + 1;
    }
    Num div = Num(1, vector<short int>(m, 0));
    vector<short int> divv;
    for(int i = m ; i<= v1.n.size() -1 ; ){
        while(Num(1, vector<short int>(v1.n.begin(), v1.n.begin() + m)).Compare(v2) < 0 ){
            m = m+1;
            i += 1;
        }
        left = Num(1, vector<short int>(v1.n.begin() + i - m, v1.n.begin() + i));
        c = left.Div(v2);
        divv.push_back(c.n[0]);
        cur = left.Min(v2.Mult(c));
        if(cur.Compare(Num("0")) != 0){
            copy_n(cur.n.begin(), cur.n.size(), &v1.n[0]);
        }
        else {
            v1.n.erase(v1.n.begin(), v1.n.begin() + m);
        }
        
        m=0;
    }
    
    return Num(sign*on.sign, divv);
}
Num Num:: DivLong(Num on){
    
    vector<short int> v1v = n;
    vector<short int> v2v = on.n;
    reverse(v1v.begin(), v1v.end());
    reverse(v2v.begin(), v2v.end());
    Num v1 = Num(1, v1v);
    Num v2 = Num(1, v2v);
    int nv = (int)on.n.size();
    int qq;
    int r;
    Num q = Num("0");
    size_t m = n.size() - on.n.size();
    for(int j = (int) m; j >=0 ; --j){
        qq = (v1.n[j+nv] * 10 + v1.n[j+nv-1])/ v2.n[nv-1] ;
        r = (v1.n[j+nv] *10 + v1.n[j+nv-1]) % v2.n[nv-1];
        if(qq == 10 || (qq*v2.n[nv-2] > 10* r + v1.n[j+nv-2])){
            qq = qq - 1;
            r += v2.n[nv- 1];
        }
    }
    return Num("1");
}

Num Num::DivBig(Num on){
    //    cout << vector<short int>(1, 5) [0];
    vector<short int> v1v = n;
    reverse(v1v.begin(), v1v.end());
    vector<short int> v2v = on.n;
    reverse(v2v.begin(), v2v.end());
    Num v1 = Num(1, v1v);
    Num v2 = Num(1, v2v);
    Num res =Num("0");
    Num curv = Num("0");
    for(int i = v1.n.size() - 1; i>=0; --i){
        
        for(int j = v1.n.size(); j>=1;--j){
            v1.n[j]=v1.n[j-1];
        }
        //push
        
        curv.n[0] = v1.n[i];
        int x = 0;
        int l=0;
        int r = 10;
        while(l<=r){
            int m = (l+r) >>1;
            
        }
    }
    return Num("1");
}
Num::Num(int on){
    sign = 1;
    vector<short int> vec;
    if(on == 0) vec.push_back(0);
    vector<short int>::iterator it = vec.begin();
    while(on>0){
        it = vec.begin();
        vec.insert(it, on%10);
        on /= 10;
    }
    n = vec;
}
Num Num::DivC(Num on){
    vector<short int> divn;
    if (this -> Compare(on) == 0) { divn.push_back(1); return Num(1, divn);}
    if(Num(1, n).Compare(Num(1, on.n)) == 0) {return Num(sign*on.sign , vector<short int>(1, 1));}
    if (this -> Compare(on) == -1 && sign > 0 && on.sign >0){ divn.push_back(0); return Num(1, divn);}
    if(on.n.size() == 1 && on.n[0] == 0) {cout<< "\n cannot divide by zero"; divn.push_back(0); return Num(1, divn);}
    if(n.size() == 1 && n[0] == 0){ divn.push_back(0); return Num(1, divn);}
    
    Num c = Num("1");
    Num cur = Num("0");
    Num left = Num("0");
    Num v1 = Num(1, n);
    Num v2 = Num(1, on.n);
    int m = (int) v1.n.size() - v2.n.size() + 1;
    int diflen = m;
    if ( Num(1, vector<short int>(v1.n.begin(), v1.n.begin() + m/*v2.n.size() */) ).Compare(v2) < 0){
        m = m + 1;
    }
    Num div = Num(1, vector<short int>(m, 0));
    vector<short int> divv;
    int mm= m;
    for(int i = 0; i< m && Num(1, vector<short int>(div.n.begin(), div.n.begin() + i + 1)).Mult(v2).Compare(v1) <= 0; ++i){
        
        while(Num(1, vector<short int>(v1.n.begin(), v1.n.begin() + mm )).Compare(v2) < 0 ){
            mm = mm+1;
        }
        left = Num(1, vector<short int>(v1.n.begin() , v1.n.begin() + mm));
        c = left.Div(v2);
        cur = left.Min(v2.Mult(c));
        cur.sign = 1;
        if(cur.Compare(Num(0)) != 0){
            copy_n(cur.n.begin(), cur.n.size(), &v1.n[0]);
        }
        else{
            //            v1.n.erase(v1.n.begin(), v1.n.begin() + mm);
            //            v1.printNum(); cout<<"\n";
        }
        mm=0;
        
    }
    reverse(div.n.begin(), div.n.end());
    while(div.n.back() == 0){
        div.n.pop_back();
    }
    reverse(div.n.begin(), div.n.end());
    div.sign = sign*on.sign;
    return div;
    
    
    for(int i = m ; i<= v1.n.size() -1 ; ){
        while(Num(1, vector<short int>(v1.n.begin(), v1.n.begin() + m)).Compare(v2) < 0 ){
            m = m+1;
            i += 1;
        }
        left = Num(1, vector<short int>(v1.n.begin() + i - m, v1.n.begin() + i));
        c = left.Div(v2);
        divv.push_back(c.n[0]);
        cur = left.Min(v2.Mult(c));
        if(cur.Compare(Num("0")) != 0){
            copy_n(cur.n.begin(), cur.n.size(), &v1.n[0]);
        }
        else {
            v1.n.erase(v1.n.begin(), v1.n.begin() + m);
        }
        
        m=0;
    }
    return Num(sign*on.sign, divv);
}



Num Num:: DivOp(Num on){
    vector<short int> divn;
    if (this -> Compare(on) == 0) { divn.push_back(1); return Num(1, divn);}
    if(Num(1, n).Compare(Num(1, on.n)) == 0) {return Num(sign*on.sign , vector<short int>(1, 1));}
    if (this -> Compare(on) == -1 && sign > 0 && on.sign >0){ divn.push_back(0); return Num(1, divn);}
    if(Num(1, n).Compare(Num(1, on.n)) < 0) {return Num(0);}
    if(on.n.size() == 1 && on.n[0] == 0) {cout<< "\n cannot divide by zero"; divn.push_back(0); return Num(1, divn);}
    if(n.size() == 1 && n[0] == 0){ divn.push_back(0); return Num(1, divn);}
    
    vector<short int> res;
    for(int i = n.size(); i>=0; --i){
        res.push_back(0);
    }
    Num currentValue(0);
    for(int i = 0; i< n.size(); ++i){
        currentValue = currentValue.Mult(Num(10));
        currentValue.n[currentValue.n.size() -1] = n[i];
        int x =0;
        int leftIndex = 0;
        int rightindex = 10;
        while(leftIndex <= rightindex){
            int middle = (leftIndex + rightindex) >> 1;
            Num cur = Num(1, on.n).Mult(Num(middle));
            if(Num(1, cur.n).Compare(Num(1, currentValue.n)) <= 0){
                x = middle;
                leftIndex = middle + 1;
            }
            else{
                rightindex = middle - 1;
            }
        }
        res[i] = x;
        currentValue = currentValue.Min(Num(1, on.n).Mult(Num(x)));
    }
    reverse(res.begin(), res.end());
    while(res.size()>= 1 && res.back() ==0){
        res.pop_back();
    }
    reverse(res.begin(), res.end());
    res.pop_back();
    n = res;
    sign = sign*on.sign;
    return *this;
    
}

Num Num:: DivByTwo(){
    short int nn = n[n.size() - 1] /2;
    if(n.size()> 1){
        n.pop_back();
        n = multv(n, vector<short int>(1, 5));
        n = sumn(n, vector<short int>(1, nn));
        return *this;
    }
    n[n.size() - 1] = nn;
    return *this;
    
}
Num Num:: DivBin(Num on){
    Num v1 = Num(1, n);
    Num v2 = Num(1, on.n);
    Num rem = *this;
    Num left = Num("0");
    Num right = rem;
    Num mid (1);
    Num mults = rem.Mult(v2);
    while(! ( (mults.Compare(v1) == 0) || (mults.Add(Num(1)).Compare(v1) == 0) || (mults.Min(Num(1)).Compare(v1) == 0)) ){
        if(mults.Compare(v1) > 0){
            Num y0 = mid;
            mid = (left.Add(right)).DivByTwo();
            right = y0;
            
        }
        else{
            if(mults.Compare(v1) < 0){
                Num y0 = mid;
                mid = (left.Add(right)).DivByTwo();
                left = y0;
            }
        }
        rem =mid;
        mults = rem.Mult(v2);
        
    }
    return rem;
}


void Num::removeZeros() {
    if (n.empty()) {
        this->n.push_back(0);
        this->sign = 1;
    }
    while (n.size() > 1 && n.back() == 0)
        n.pop_back();
}


void Num:: gcdExt(Num a, Num b, Num *gcd, Num *x, Num *y){
    if(b.Compare(Num(0)) ==0){
        *gcd = a;
        *x = Num(1);
        *y = Num(0);
        return;
    }
    gcdExt(b, a .module(b), gcd, x, y);
    Num c(0);
    c = *y;
    *y = x -> Min( (a .DivOp(b)).Mult(*y) );
    *x = c ;
}

Num Num::ModularPower(Num on , Num m){
    Num res(1);
    Num x = this ->module(m);
    Num p = on;
    while(p.Compare(Num(0)) > 0){
        if(p.isOdd()){
            res = res.Mult(x).module(m);
        }
        p = p.DivOp(Num(2));
        x = x.Mult(x).module(m);
    }
    return res;
}

Num Num::ToModPow(Num on, Num m){
    vector<short int> powv;
    if(n.size() == 1 && n[0] == 0) { powv.push_back(0); return Num(1, powv);}
    if(on.n.size() == 1 && on.n[0] == 0){ powv.push_back(1); return Num(1, powv);}
    if(n.size() == 1 && n[0] == 0){ return *this;}
    if(on.isOdd()){
        return (this -> Mult( ((this->Mult(*this)).module(m)).ToModPow(on.Min(Num(1, vector<short int>(1, 1))).Div(Num(1, vector<short int>(1, 2))), m) )).module(m);
    }
    else{
        return ((this->Mult(*this)).module(m)).ToModPow(on.Div(Num(1, vector<short int>(1, 2)) ) , m).module(m);
    }
    
}

Num Num:: SqrtOfNum(){
    Num l = Num(0);
    Num r = *this;
    Num thisn = *this;
    Num thisnp = this->Add(Num(1));
    Num x = l;
    Num px = x;
    Num x2 = Num(0);
    int compare;
    while(! (( thisn.Compare(x2) <= 0 ) && (thisnp.Compare(x2) > 0) ) && l.Compare(r) != 0){
        x = l.Add(r.Min(l).DivOp(Num(2)));
        x2 = x.Pow(2);
        compare = x2.Compare(*this);
        if(compare == 0){
            return x;
        }
        else{
            if(compare < 0 ){
                l = x.Add(Num(1));
            }
            else {
                r =x;
            }
            
            
        }
    }
    return x;
}
Num Num::Sqrtj(){
    if(this -> Compare(Num(0)) < 0) {return Num(0);}
    if(this -> Compare(Num(1)) ==0) return *this;
    Num curVal = Num(0);
    Num curValp = Num(0);
    Num lower = Num(0);
    Num upper = *this;
    while(true){
        curValp = curVal.Add(Num(1));
        if((curVal.Mult(curVal).Compare(*this) <= 0 )&& ((curVal.Add(Num(1)).Mult(curVal.Add(Num(1)))).Compare(*this) > 0)){
            break;
        }
        else if(curVal.Mult(curVal).Compare(*this) > 0){
            Num y0 = curVal;
            curVal = (upper.Add(lower)).DivOp(Num(2));
            upper = y0;
        }
        else if(curVal.Mult(curVal).Compare(*this) < 0 ){
            Num x0 = curVal;
            curVal = (upper.Add(lower)).DivOp(Num(2));
            lower = x0;
        }
    }
    return curVal;
}
void Num::printNum(){
    bool b = false;
    if(sign == -1) cout<<"-";
    for(int i = 0 ; i< n.size(); ++i){
        if(/*n[i] != 0*/true) b = true;
        if(b == true || i == n.size() -1) cout<< n[i];
    }
}





Num Num:: gcdRho(Num a, Num b){
    Num rem(0);
    while(b.Compare(Num(0)) != 0){
        rem = a.module(b);
        a = b;
        b = rem;
    }
    return a;
}


Num Num::RhoPollard(){
    int count = 0;
    int loop = 1;
    Num x_fixed = Num(2);
    int size = 2;
    Num x = Num(2);
    Num factor = Num(1);
    //    Num y = Num(2);
    //    Num d = Num(1);
    while(factor.Compare(Num(1)) == 0){
        printf("   loop %d  \n", loop);
        for(count  = 1; (count <= size) && (factor.Compare(Num(1)) <= 0 ); ++count){
            x = (x.Mult(x).Add(Num(1))).module(*this);
            factor = gcdRho(Num(1, x.Min(x_fixed).n), *this);
            printf("count = %d  x = ", count);
            x.printNum();
            cout << " factor " ; factor.printNum(); cout<<"\n";
        }
        size = 2 * size;
        x_fixed = x;
        loop = loop +1;
        
    }
    factor.printNum();
    return factor;
    
}

Num Num::LegendreSymbol(Num p){
    return (this->modular_power(p.Min(Num(1)).DivByTwo(), p));
}

void NewXAB(Num & x, Num& a, Num & b , Num N, Num n, Num alpha, Num beta){
    Num s = x.module(Num(3));
    if(s.Compare(Num(0)) == 0){
        x = (x.Mult(x)).module(N);
        a = (a.Mult(Num(2))).module(n);
        b = (b.Mult(Num(2))).module(n);
        return;
    }
    if(s.Compare(Num(1)) == 0){
        x = (x.Mult(alpha)).module(N);
        a = (a.Add(Num(1))).module(n);
        return;
    }
    if(s.Compare(Num(2)) == 0){
        x = (x.Mult(beta)).module(N);
        b = (b.Add(Num(1))).module(n);
        return;
    }
}

Num Num::RhoPollardDiscreteLog(Num beta, Num N){
    //this is generator
    //mod N
    
    Num nn = /*this ->*/ N.Min(Num(1));
    Num x = Num(1);
    Num a = Num(0);
    Num b = Num(0);
    Num X = x;
    Num A = a;
    Num B = b;
    for(Num i(1) ; i.Compare(nn) < 0 ; i = i.Add(Num(1)) ){
        NewXAB(x, a, b, N, nn, *this, beta);
        NewXAB(X, A, B, N, nn, *this, beta);
        NewXAB(X, A, B, N, nn, *this, beta);
        cout<<"i   x   a   b   X    A   B  \n";
        i.printNum(); cout<<" "; x.printNum(); cout<<" "; a.printNum(); cout<<" "; b.printNum(); cout<<" "; X.printNum(); cout<<" "; A.printNum(); cout<<" "; B.printNum(); cout<<"\n";
        //        printf("%3d  %4d %3d %3d  %4d %3d %3d\n", i, x, a, b, X, A, B);
        if(x.Compare(X) == 0) break;
    }
    cout<<"("; B.printNum(); cout<<" - "; b.printNum(); cout<<")"; cout<<"y = "; a.printNum(); cout<<" - "; A.printNum(); cout<<" (mod "; nn.printNum(); cout<<")";
    Num aext = B.Min(b);
    Num bext = a.Min(A);
    Num d = Num(0);
    Num * dp = &d;
    Num xext = Num (0);
    Num * xextp = & xext;
    Num yext = Num(0);
    Num * yextp = & yext;
    gcdExt(aext, nn, dp, xextp, yextp);
    if(d.Compare(Num(1)) > 0){
        aext = aext.DivOp(d);
        bext = bext.DivOp(d);
        nn = nn.DivOp(d);
        xextp = & xext;
        yextp = & yext;
        Num dd = Num(1);
        Num * ddp = &dd;
        gcdExt(aext, nn, ddp, xextp, yextp);
        cout<<"\n";
        return (bext.Mult(xext)).module(nn);
    }
    return Num(0);
    
}



Num Num:: RhoPollardN(){
    //    Num i = Num(1);
    int i = 0;//1;
    Num x1 = Num(rand());
    if(x1.Compare(this->Min(Num(1))) >= 0 ){
        x1 = Num(2);
    }
    Num xp = Num(0);
    Num y = x1;
    Num d = Num(0);
    int k = 2;
    while(true){
        i = i + 1;
        xp = (x1.Mult(x1).Min(Num(1))).module(*this);
        d = this->gcd(y.Min(xp));//gcdRho(y.Min(xp), (*this));
        if((d.Compare(Num(1)) != 0) && d.Compare(*this) !=0){
            d.printNum();
            return d;
        }
        if(i == k){
            y = xp;
            k = 2*k;
            
        }
        x1 = xp;
    }
}


int Num:: MobiusFunc(vector<Num> m){
    if(m.size()>1){
        int nm = 0;
        for(int  i= 0; i < m.size(); ++i){
            Num cur = m[i];
            nm = 1;
            for(int j = i + 1; j < m.size(); ++j){
                if(m[j].Compare(cur) == 0){
                    nm = nm +1;
                }
            }
            if(nm >= 2) return 0;
        }
        return pow(-1, m.size());
        
    }
    else return -3;
}

vector<Num> Num::getFactors(){
    vector<Num> factors;
    Num x = *this;
    Num factor(0);
    do{
        factor = x.RhoPollard();
        x = x.DivOp(factor);
        cout<< " factor " ;factor.printNum(); cout <<"\n";
        if(factor.Compare(Num(1)) !=  0) factors.push_back(factor);
        else return factors;
    } while(/*factor.Compare(Num(1)) !=  0 ||*/ factor.Compare(*this) != 0);
    
    return factors;
}
Num Num::EulerFunction(){
    Num res = *this;
    for(Num i = Num(2); i.Mult(i).Compare(*this) <= 0; i = i.Add(i)){
        if((this -> module(i)).Compare(Num(0)) == 0){
            while((this -> module(i)).Compare(Num(0)) == 0){
                *this = this ->DivOp(i);
            }
            res = res.Min(res.DivOp(i));
        }
    }
    if(this->Compare(Num(1)) > 0){
        res = res.Min(res.DivOp(*this));
    }
    return res;
}
Num Num::gcd(Num b){
    
    if (b.Compare(Num(0)) ==0) return *this;
    
    return b.gcd((*this) .module(b));
    
}
bool Num::SolovayStrassen(int k){
    for(int i  = 1; i <=k; ++i){
        //        Num a(0);
        //        if(k==1) a = Num("11");
        //        if(k==2) a = Num("5");
        int nn = rand();
        Num a = Num(nn/*rand()*/);
        if(a.Compare(this->Min(Num(1))) >= 0 ){
            a = Num(2);
        }
        if(a.gcd(*this).Compare(Num(1)) > 0){
            cout<<"Not prime";
            return 0;
        }
        if( a.modular_power((this->Min(Num("1"))).DivByTwo(), *this)/*(a.Pow((this->Min(Num(1))).DivByTwo()) % *this)*/.Compare(a.JacobiSymbol(*this)) != 0){
            cout<<"Not prime";
            return 0;
            
        }
    }
    cout << "n is prime with probability 1 - 2^(-" << k <<")";
    return 1;
}
Num Num::ModMulPow(Num b, Num mod){
    vector<short int> powv;
    if(b.Compare(Num(0)) == 0){ powv.push_back(1); return Num(1, powv);}
    if(b.Compare(Num(1)) == 0){ return *this;}
    //    Num pown;
    if(b.isOdd() ){
        return (this -> module(mod)).Mult((this -> module(mod)).Mult(this->module(mod)).ModMulPow( (b.Min(Num(1)).DivOp(Num(2))), mod));
        
    }
    else{
        return (this->module(mod)).Mult(this->module(mod)).ModMulPow(b.DivOp(Num(2)), mod);
    }
}
Num Num::JacobiSymbol(Num b){
    Num a = *this;
    if(a.gcd(b)/*gcdRho(a, b)*/.Compare(Num(1)) != 0) return Num(0);
    Num r = Num(1);
    if(a.sign<0){
        a = Num(1, a.n);
        if((b.module(Num(4))).Compare(Num(3)) == 0) r=Num(-1, r.n);
    }
step: Num t = Num(0);
    while(!a.isOdd()){
        t = t.Add(Num(1));
        a = a.DivByTwo();
    }
    if(t.isOdd() ){
        Num m = b.module(Num(8));
        if(m.Compare(Num(3)) == 0 || m.Compare(Num(5)) == 0){
            r = Num(-1*r.sign, r.n);
        }
    }
    if( (a.module(Num(4))).Compare(Num(3)) == 0 && (b.module(Num(4))).Compare(Num(3)) == 0) r= Num(-1*r.sign, r.n);
    Num c= a;
    a= b.module(c);
    b = c;
    if(a.Compare(Num(0)) !=0) goto step;
    else{
        return r;
    }
}
bool Num::SolovayStrassenTest(int k){
    //    cout<< k <<" ";
    for(int i =0 ; i<k; ++i){
        Num a = Num(rand());
        if(a.Compare(Num(2)) <= 0 || a.Compare(this->Min(Num(1))) >= 0){
            a  = Num("3");
        }
        //        cout<<"num";a.printNum(); cout<<" ";
        Num x = a.JacobiSymbol(*this);
        if((x.Compare(Num(0)) == 0) || a.modular_power((this->Min(Num(1))).DivByTwo(), *this).Compare(x)){
            cout<<"composite";
            return false;
        }
        
    }
    cout<<"probably prime(n is prime with probability 1 - 2^(-" << k <<"))";
    return true;
}
//
Num Num::ChippoloDiscreteRoot(Num p){
    srand(rand());
    Num b = Num(2);
    int i = 0;
    while(true){
        b = /*Num("2"); //*/Num(rand()%12345);
        if(b.Compare(p) >= 0){
            b = Num("2").Add(Num(i));//Num("2");
        }
        cout<<" b "; b.printNum();
        Num w =(((b.Mult(b)).Min(*this)).module(p) );
        w.printNum(); cout<<" ";
        if(w.Compare(Num(0)) == 0){
            cout<<"+-"; b.printNum();
            return b;
        }
        if(w.LegendreSymbol(p).Compare(Num(1)) == 0) {i = i+1;continue;}
        else{
            Num x = multChippolo(b, Num(1), w, (p.Add(Num(1))).DivByTwo(), p)[0];
            cout<<"+-"; x.printNum();
            return x;
        }
        i = i+1;
    }
    
}
vector<Num> Num::multChippolo(Num a1, Num a2, Num w, Num power, Num p){
    a1.printNum(); cout<<" "; a2.printNum(); cout<<" w"; w.printNum(); cout<<" ";
    Num num1 = a1;
    Num num2 = a2;
    vector<Num> multn;
    Num p1 = Num(0);
    Num p2 = Num(0);
    Num c1 = Num(0);
    Num c2 = Num(0);
    Num b1 = a1;
    Num b2 = a2;
    Num l1 = Num(0);
    Num l2 = Num(0);
    bool odd = false;
    if(power.Compare(Num(1)) == 0) {
        //        b1 = ((b1.Mult(b1)).Add( ( (b2.Mult(b2)).Mult( w ) )  )).module(p);
        //        b2 = ((Num(2).Mult(a1)).Mult(b2)).module(p);
        multn.push_back(b1); multn.push_back(b2);
        return multn;
    }
    if(power.Compare(Num(2)) == 0) {
        b1 = ((b1.Mult(b1)).Add( ( (b2.Mult(b2)).Mult( w ) )  )).module(p);
        b2 = ((Num(2).Mult(a1)).Mult(b2)).module(p);
        multn.push_back(b1); multn.push_back(b2);
        return multn;
    }
    if(power.isOdd()) {odd = true; power = power.Min(Num(1));}
    b1 = ((b1.Mult(b1)).Add( ( (b2.Mult(b2)).Mult( w ) )  )).module(p);
    b2 = ((Num(2).Mult(a1)).Mult(b2)).module(p);
    b1.printNum(); cout<<" "; b2.printNum(); cout<<"\n";
    p1 = b1;
    p2 = b2;
    l1 = b1;
    l2 = b2;
    for(Num i = Num(2)/*2*/; i.Compare(power)<0 ; i = i.Mult(Num(2))){
        //        cout <<" "; i.printNum();
        l1 = ((p1.Mult(b1)).Add(p2.Mult(b2).Mult(w))).module(p);
        l2 = ((p2.Mult(b1)).Add(p1.Mult(b2))).module(p);
        p1 = l1;
        p2 = l2;
        
        p1.printNum(); cout<<" "; p2.printNum(); cout<<"\n";
    }
    
    if(odd){
        c1 = (num1.Mult(p1)).Add(num2.Mult(p2).Mult(w));
        c2 = (num2.Mult(p1)).Add(num1.Mult(p2));
    }
    else{
        c1 = l1;
        c2 = l2;
    }
    c1 = c1.module(p);
    c2 = c2.module(p);
    multn.push_back(c1);
    //    c1.printNum(); cout<<" ";
    multn.push_back(c2);
    //    c2.printNum();
    return multn;
}

Num Num:: modularPow(Num exp, Num mod){
    Num c = Num(1);
    Num expp = exp.Min(Num(1));
    expp.printNum(); cout<<" ";
    for(Num i(0); i.Compare(expp) <= 0 ; i = i.Add(Num(1))){
        c = c.Mult(*this).module(mod);
    }
    return c;
}

Num Num::modular_power(Num exp, Num mod){
    Num res = Num(1);
    Num base = (*this).module(mod);
    while(exp.Compare(Num(0)) > 0 ){
        if(exp.isOdd()){
            res = (res.Mult(base)).module(mod);
        }
        exp = exp.DivByTwo();
        base = (base.Mult(base)) .module(mod);
    }
    return res;
}
vector<Num> Num::factorization(){
    Num factor = Num(0);// = this->RhoPollard();
    Num current = * this;
    vector<Num> factors;
    bool fp;
    bool fe;
    while(true){
        factor = current.RhoPollard();
        fp =factor.Compare(Num(1)) !=0 ;
        fe = factor.Compare(current) != 0;
        if(fp && fe ){
            //            factor.printNum(); cout<<"\n";
            factors.push_back(factor);
            current = current.DivOp(factor);
        }
        
        else {
            if(! fe){
                factors.push_back(factor);
            }
            cout<<"\nfactors ";
            for(int i = 0; i<factors.size();++i){
                factors[i].printNum(); cout<<" ";
            }
            return factors;
        }
    }
    
    cout<<"\nfactors";
    for(int i = 0; i<factors.size();++i){
        factors[i].printNum(); cout<<" ";
    }
    return factors;
}
Num Num:: module(Num m){
    Num thisnum = *this;
    //thisnum.sign = 1;
    if(thisnum.Compare(m) < 0 && thisnum.sign >0 ) return *this;
    Num div = thisnum.DivOp(m);
    //    div.printNum();
    Num mod = (*this).Min( (m.Mult(div)) );
    //    mod.printNum();
    if(mod.sign == -1) return mod.Add(m);
    return mod;
}
Num Num::ElGamalSystem(/*Num N*/){
    string str;
    cout<<"\nOrder of the group: ";
    cin>>str;
    Num N = Num(str);
    cout<<"\nGenerator: ";
    cout<<"\nx:";
    cin >> str;
    Num xp = Num(str);
    cout<<"\ny:";
    cin >> str;
    Num yp = Num (str);
    Num k = Num(rand());
    if(k.Compare(N.Min(Num(1))) == 0){
        k = Num(2);
    }
    Num xY = Num(0);
    Num yY = Num(0);
    
    return N;
    
}