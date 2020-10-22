#include <iostream>
#include <string>
#include <vector>

#define BASE 10
#define base_len 1

using namespace std;

vector<int> div_for_shin(vector<int> a, vector<int> m){
    //we count on thet m=2^n - 1
    vector<int> res;
    int ukaz = 0, m_s = m.size(), delitsa=1, a_s = a.size();

    while(a_s-ukaz>m_s) {
        for (int i = ukaz; i < m_s + ukaz; i++) {
            if (a[i] == 0) {
                delitsa = 0;
            }
        }
        if (delitsa) {
            ukaz += m_s;
        } else {
            a[ukaz] = 0;
            int buf = 0;
            while (a[ukaz + m_s - buf] == 1) {
                a[ukaz + m_s - buf] = 0;
                buf += 1;

            }
            a[ukaz + m_s - buf] = 1;
            while (a[ukaz] == 0) {
                ukaz += 1;
            }
        }
        delitsa=1;
    }

    if(a_s-ukaz<m_s){
        res.insert(res.begin(), a.begin()+ukaz, a.end());
    } else {
        for(int i = ukaz; i<m_s+ukaz; i++){
            if(a[i]==0){
                delitsa = 0;
            }
        }
        if(delitsa){
            res.push_back(0);
        } else {
            res.insert(res.begin(), a.begin()+ukaz, a.end());
        }
    }
    return res;
}

class IlangLong;

class Multiplication{
public:
    virtual IlangLong multiply(IlangLong a, IlangLong b) = 0;
};

class IlangLong{

public:

    vector<int> value;
    int Base = 10;
    int base_Len = 1;
    static Multiplication* mult_metod;

    IlangLong(int num=0){
        value.push_back(num);
    }

    IlangLong(vector<int> a){
        value = a;
    }

    IlangLong(const string& num){
        if (num.size()%base_Len != 0){
            value.push_back(stoi(num.substr(0, num.size()%base_Len)));
        }
        for(int i = 0; i<num.size()/base_Len; i++){
            value.push_back(stoi(num.substr(num.size()%base_Len + i*base_Len, base_Len)));
        }
    }

    IlangLong& operator=(string s){
        *this = IlangLong(s);
        return *this;
    }

    void urovnenie(vector<int>& a, vector<int>& b){
        int a_s = a.size(), b_s = b.size();
        if (a_s == b_s) {
            return;
        } else {
            vector<int> buffer;
            buffer.push_back(0);
            if (a_s > b_s){
                for(int i = 0; i<(a_s - b_s); i++){
                    b.insert(b.begin(), buffer.begin(), buffer.end());
                }
            } else {
                for(int i = 0; i<b_s - a_s; i++){
                    a.insert(a.begin(), buffer.begin(), buffer.end());
                }
            }
        }
    }

    void normalise(vector<int>& vec){
        int nosilki = 0;
        for(int i = vec.size()-1; i>=0; i--){
            vec[i]+=nosilki;
            nosilki = vec[i]/BASE;
            vec[i] %= BASE;
        }
        while (nosilki!=0){
            vector<int> nos;
            nos.push_back(nosilki%BASE);
            nosilki/=BASE;
            vec.insert(vec.begin(), nos.begin(), nos.end());
        }
        while(vec.size()!=1 && vec[0] == 0){
            vec.erase(vec.begin());
        }
    }

    vector<int> summ(vector<int> a, vector<int> b){
        urovnenie(a,b);
        vector<int> res;
        for(int i = 0; i < a.size(); i++){
            res.push_back(a[i]+b[i]);
        }
        normalise(res);
        return res;
    }

    IlangLong operator+(IlangLong a){
        return IlangLong(summ((*this).value, a.value));
    }

    void operator+=(IlangLong a){
        *this = *this + a;
    }

    vector<int> subtr(vector<int> a, vector<int> b){
        urovnenie(a, b);
        vector<int> res, buff(1);
        for(int i = a.size()-1; i>=0; i--){
            if (a[i] < b[i]){
                if (i==0){
                    cout<<"Subst problems"<<a[i]<<' '<<b[i]<<endl;
                }
                a[i-1]-=1;
                a[i] += BASE;
            }
            buff[0] = a[i] - b[i];
            res.insert(res.begin(), buff.begin(), buff.end());
            buff[0] = 0;
        }
        normalise(res);
        return res;
    }

    IlangLong operator-(IlangLong a){
        return IlangLong(subtr((*this).value, a.value));
    }

    void operator-=(IlangLong a){
        *this = *this - a;
    }

    IlangLong operator*(IlangLong a){
        return mult_metod -> multiply((*this).value, a.value);
    }

    pair<IlangLong, int> division_on_scal(int scal){
        if(scal==1){
            return {*this, 0};
        }
        vector<int> res;
        for(int i=0; i<value.size()-1; i++){
            res.push_back(value[i]/scal);
            value[i+1] += (value[i]%scal)*Base;
        }
        res.push_back(value.back()/scal);
        normalise(res);
        return {IlangLong(res), value.back()%scal};
    }

    IlangLong div_on_scal(int a){
        return division_on_scal(a).first;
    }

    int mod_of_scal(int a){
        return division_on_scal(a).second;
    }

    IlangLong sdvig(int n){
        vector<int> res;
        res = value;
        for(int i = 0; i<n; i++){
            res.push_back(0);
        }
        return IlangLong(res);
    }

    IlangLong SchoolMultipl(IlangLong b){
        IlangLong res;
        int a_s=value.size(), b_s=b.value.size();
        if (a_s>=b_s){
            for(int i=b_s-1; i>=0; i--){
                IlangLong buffbig, buffsmal;
                buffbig.value.clear(), buffsmal.value.clear();
                for(int j=a_s-1; j>=0; j--){
                    buffsmal.value.push_back(value[j]*b.value[i]);
                    buffbig.value.insert(buffbig.value.begin(), buffsmal.value.begin(), buffsmal.value.end());
                    buffsmal.value.erase(buffsmal.value.begin());
                }
                normalise(buffbig.value);
                res += buffbig.sdvig(b_s-i-1);
            }
            return res;
        }else{
            return b.SchoolMultipl(*this);
        }
    }

    void base_to_2(){
        vector<int> res;
        pair<IlangLong, int> buffer;
        while(value[0]!=0){
            buffer = (*this).division_on_scal(2);
            (*this) = buffer.first;
            res.push_back(buffer.second);
        }
        reverse(res.begin(), res.end());
        (*this) = res;
        Base = 2;
        base_Len = 1;
    }

    static void setMult(Multiplication *some_way){
        mult_metod = some_way;
    }

    void print(const string& name = ""){
        if (!name.empty()){
            cout<<name<< ": ";
        }
        for(int i:value){
            cout<<i<< ' ';
        }
        cout<<endl;
    }
};

class KaratsubaMult: public Multiplication{

public:
    KaratsubaMult() = default;

    IlangLong multiply(IlangLong a, IlangLong b) override{
        a.urovnenie(a.value, b.value);
        if (a.value.size() <= 2){
            return a.SchoolMultipl(b);
        } else {
            IlangLong a1b1, a0b0, abmini, a1, b1, a0, b0, res;
            a1.value.clear(), b1.value.clear(), a0.value.clear(), b0.value.clear();
            a1.value.insert(a1.value.begin(), a.value.begin(), a.value.begin()+a.value.size()/2);
            a0.value.insert(a0.value.begin(), a.value.begin()+a.value.size()/2, a.value.end());
            b1.value.insert(b1.value.begin(), b.value.begin(), b.value.begin()+b.value.size()/2);
            b0.value.insert(b0.value.begin(), b.value.begin()+b.value.size()/2, b.value.end());

            a1b1 = multiply(a1, b1);
            a0b0 = multiply(a0, b0);
            abmini = multiply(a1 + a0, b1+ b0);

            res = a1b1.sdvig((a.value.size() - a.value.size()/2)*2) + a0b0 + (abmini - a1b1 - a0b0).sdvig(a.value.size() - a.value.size()/2);
            return res;
        }
    }

};

class ToomMult: public Multiplication{
public:
    ToomMult()=default;

    IlangLong polynoom(IlangLong a, IlangLong b, IlangLong c, int x){
        IlangLong X_zminna(x), X_zminna_2(x*x);
        return a.SchoolMultipl(X_zminna_2)+ b.SchoolMultipl(X_zminna) + c;
    }

    IlangLong multiply(IlangLong a, IlangLong b){
        a.urovnenie(a.value,b.value);
        int a_s = a.value.size();
        if (a.value.size()<=3){
            return a.SchoolMultipl(b);
        } else {
            IlangLong res;
            IlangLong a2, a1, b2, b1,u0,v0;
            vector<IlangLong> w;

            a1.value.clear(), a2.value.clear(), b1.value.clear(), b2.value.clear(), u0.value.clear(), v0.value.clear();

            int first_size, else_size;
            if (a_s%3){
                else_size = a_s/3+1;
                first_size = else_size - (3-a_s%3);
            } else {
                else_size = a_s/3; first_size = else_size;
            }
            a2.value.insert(a2.value.begin(), a.value.begin(), a.value.begin()+first_size);
            a1.value.insert(a1.value.begin(), a.value.begin()+first_size, a.value.begin()+first_size+else_size);
            u0.value.insert(u0.value.begin(), a.value.begin()+first_size+else_size, a.value.end());

            b2.value.insert(b2.value.begin(), b.value.begin(), b.value.begin()+first_size);
            b1.value.insert(b1.value.begin(), b.value.begin()+first_size, b.value.begin()+first_size+else_size);
            v0.value.insert(v0.value.begin(), b.value.begin()+first_size+else_size, b.value.end());

            if (a2.value.empty()){
                a2.value.push_back(0);
            }
            if(b2.value.empty()){
                b2.value.push_back(0);
            }

            //a goes for U(x), b goes for V(x)
            //There are no a0 and b0, cause U(0) = a0 = u0, same to v0 = b0

            w.push_back(multiply(u0, v0));

            for (int i = 1; i<=4; i++) {
                w.push_back(multiply(polynoom(a2, a1, u0, i),
                                        polynoom(b2, b1, v0, i)));
            }

            vector<IlangLong> bufferL, bufferS2(1);
            IlangLong bufferS1;

            for(int i = 1; i<=4; i++){
                for(int j = i; j<=4; j++){
                    bufferL.push_back((w[j]-w[j-1]).div_on_scal(i));
                }
                //намечается костыль
                w.erase(w.begin()+i,w.end());
                w.insert(w.end(), bufferL.begin(), bufferL.end());
                bufferL.erase(bufferL.begin(), bufferL.end());
            }

            for(int i = 3; i>=1; i--){
                bufferS1.value[0]=i;
                for(int j = 3; j>=i; j--){
                    bufferS2[0]= w[j] - w[j+1].SchoolMultipl(bufferS1);
                    bufferL.insert(bufferL.begin(), bufferS2.begin(), bufferS2.end());
                }
                //он же продолжается
                w.erase(w.begin()+i, w.begin()+4);
                w.insert(w.begin()+i, bufferL.begin(), bufferL.end());
                bufferL.erase(bufferL.begin(), bufferL.end());
            }

            for(int i = 0; i<=4; i++){
                res += w[i].sdvig( i*else_size);
            }
            return res;
        }
    }
};

class ShingageMult: public Multiplication{
public:
    ShingageMult()=default;

    IlangLong multiply(IlangLong a, IlangLong b){
        IlangLong res;
        return res;
    }
};

Multiplication* IlangLong::mult_metod = new ToomMult();
int main(){

    IlangLong x, y;

    x = "3";
    y = "1234509867";

    IlangLong lol = x*y;
    lol.print();

    x.base_to_2();
    x.print();

    return 0;
}

/*
int main0(){
    unsigned long long z;
    z = pow(2, 20);
    for(unsigned long long i=1111; i<=z;i++){
        for(unsigned long long j = 41567;j<=z;j++){
            if (ToomMultipl(separator(to_string(i)), separator(to_string(j))) == SchoolMultipl(separator(to_string(i)), separator(to_string(j)))){continue;}
            else{
                cout<<i<< ','<< j<< "\tHouston, we've got a problem"<<endl ;
                break;
            }
        }
    }
    return 0;
}*/