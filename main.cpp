#include <iostream>
#include <string>
#include <vector>

#define BASE 10
#define base_len 1

using namespace std;

void print(vector<int> a, string name=""){
    cout<<name<< ": ";
    for(int i:a){
        cout<<i<< ' ';
    }
    cout<<endl;
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

vector<int> sdvig(vector<int> a, int n){
    if(n==0){return a;}
    for(int i = 0; i<n; i++){
        a.push_back(0);
    }
    return a;
}

pair<vector<int>, int> div_on_scalar(vector<int> vec, int scal){
    if(scal==1){
        return {vec, 0};
    }
    vector<int> res;
    for(int i=0; i<vec.size()-1; i++){
        res.push_back(vec[i]/scal);
        vec[i+1] += (vec[i]%scal)*BASE;
    }
    res.push_back(vec.back()/scal);
    normalise(res);
    return {res, vec.back()%scal};
}

vector<int> KaratsubaMultipl(vector<int> a, vector<int> b){
    urovnenie(a, b);
    if (a.size() == 1){
        vector<int> res;
        int result = a[0] * b[0];
        res.push_back(result);
        normalise(res);
        return res;
    } else {
        vector<int> a1b1, a0b0, abmini, a1, b1, a0, b0, res;
        a1.insert(a1.begin(), a.begin(), a.begin()+a.size()/2);
        a0.insert(a0.begin(), a.begin()+a.size()/2, a.end());
        b1.insert(b1.begin(), b.begin(), b.begin()+b.size()/2);
        b0.insert(b0.begin(), b.begin()+b.size()/2, b.end());

        a1b1 = KaratsubaMultipl(a1, b1);
        a0b0 = KaratsubaMultipl(a0, b0);
        abmini = KaratsubaMultipl(summ(a1, a0), summ(b1, b0));

        res = summ(summ(sdvig(a1b1, (a.size() - a.size()/2)*2), a0b0),sdvig(subtr(subtr(abmini, a1b1), a0b0), a.size() - a.size()/2));

        return res;
    }
}

vector<int> SchoolMultip(vector<int> a, vector<int> b){
    vector<int> res;
    res.push_back(0);
    int a_s=a.size(), b_s=b.size();
    if (a_s>=b_s){
        for(int i=b_s-1; i>=0; i--){
            vector<int> buffbig, buffsmal;
            for(int j=a_s-1; j>=0; j--){
                buffsmal.push_back(a[j]*b[i]);
                buffbig.insert(buffbig.begin(), buffsmal.begin(), buffsmal.end());
                buffsmal.erase(buffsmal.begin());
            }
            normalise(buffbig);
            res = summ(sdvig(buffbig,b_s-i-1), res);
        }
        return res;
    }else{
        return SchoolMultip(b,a);
    }
}

vector<int> polynoom(vector<int>& a, vector<int>& b, vector<int>& c, int x){
    vector<int> X_zminna, X_zminna_2;
    X_zminna_2.push_back(x*x);
    X_zminna.push_back(x);
    return summ(summ(SchoolMultip(a, X_zminna_2), SchoolMultip(b, X_zminna)), c);
}

vector<int> ToomMultipl(vector<int> a, vector<int> b){
    urovnenie(a,b);
    int a_s = a.size();
    if (a.size()<=3){
        return SchoolMultip(a,b);
    } else {
        vector<int> res;
        res.push_back(0);
        vector<int> a2, a1, b2, b1,u0,v0;
        vector<vector<int>> w;
        int first_size, else_size;
        if (a_s%3){
            else_size = a_s/3+1;
            first_size = else_size - (3-a_s%3);
        } else {
            else_size = a_s/3; first_size = else_size;
        }
        a2.insert(a2.begin(), a.begin(), a.begin()+first_size);
        a1.insert(a1.begin(), a.begin()+first_size, a.begin()+first_size+else_size);
        u0.insert(u0.begin(), a.begin()+first_size+else_size, a.end());

        b2.insert(b2.begin(), b.begin(), b.begin()+first_size);
        b1.insert(b1.begin(), b.begin()+first_size, b.begin()+first_size+else_size);
        v0.insert(v0.begin(), b.begin()+first_size+else_size, b.end());

        if (a2.empty()){
            a2.push_back(0);
        }
        if(b2.empty()){
            b2.push_back(0);
        }

        //a goes for U(x), b goes for V(x)
        //There are no a0 and b0, cause U(0) = a0 = u0, same to v0 = b0

        w.push_back(ToomMultipl(u0, v0));

        for (int i = 1; i<=4; i++) {
            w.push_back(ToomMultipl(polynoom(a2, a1, u0, i),
                                    polynoom(b2, b1, v0, i)));
        }

        vector<vector<int>> bufferL, bufferS2(1);
        vector<int> bufferS1(1);

        for(int i = 1; i<=4; i++){
            for(int j = i; j<=4; j++){
                bufferL.push_back(div_on_scalar(subtr(w[j],w[j-1]), i).first);
            }
            //намечается костыль
            w.erase(w.begin()+i,w.end());
            w.insert(w.end(), bufferL.begin(), bufferL.end());
            bufferL.erase(bufferL.begin(), bufferL.end());
        }

        for(int i = 3; i>=1; i--){
            bufferS1[0] =i;
            for(int j = 3; j>=i; j--){
                bufferS2[0]=(subtr(w[j], SchoolMultip(w[j+1], bufferS1)));
                bufferL.insert(bufferL.begin(), bufferS2.begin(), bufferS2.end());
            }
            //он же продолжается
            w.erase(w.begin()+i, w.begin()+4);
            w.insert(w.begin()+i, bufferL.begin(), bufferL.end());
            bufferL.erase(bufferL.begin(), bufferL.end());
        }

        for(int i = 0; i<=4; i++){
            res = summ(res, sdvig(w[i], i*else_size));
        }
        return res;
    }
}


vector<int> div_for_shin(vector<int> a, const vector<int>& m){
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

vector<int> Shingage(vector<int> a, vector<int> b){
    vector<int> res;

    return res;
}

vector<int> separator(const string& s){
    vector<int> res;
    if (s.size()%base_len != 0){
        res.push_back(stoi(s.substr(0, s.size()%base_len)));
    }
    for(int i = 0; i<s.size()/base_len; i++){
        res.push_back(stoi(s.substr(s.size()%base_len + i*base_len, base_len)));
    }
    return res;
}

vector<int> base_to_2(vector<int> a){
    vector<int> res;
    pair<vector<int>, int> buffer;
        while(a[0]!=0){
             buffer = div_on_scalar(a, 2);
             a = buffer.first;
             res.push_back(buffer.second);
        }
        reverse(res.begin(), res.end());
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

    IlangLong operator+(IlangLong a){
        return IlangLong(summ((*this).value, a.value));
    }

    void operator+=(IlangLong a){
        *this = *this + a;
    }

    IlangLong operator-(IlangLong a){
        return IlangLong(subtr((*this).value, a.value));
    }

    IlangLong operator*(IlangLong a){
        return mult_metod -> multiply((*this).value, a.value);
    }

    IlangLong& operator=(string s){
        *this = IlangLong(s);
        return *this;
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
        return IlangLong(SchoolMultip(value, b.value));
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
        urovnenie(a.value, b.value);
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

            normalise(res.value);
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
        urovnenie(a.value,b.value);
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


Multiplication* IlangLong::mult_metod = new ToomMult();
int main(){

    IlangLong x, y;

    x = "1234567898";
    y = "1234509867";

    IlangLong lol = x*y;
    lol.print();
    print(ToomMultipl(x.value, y.value));

    return 0;
}

int main1(){
    string x, y;
    x = "11119876543213456890998764534231234576878987688670505876";
    y = "12345098675432456789654632345767890987654323456789098766";

    vector<int> chuva, ch ,lol, kek;
    chuva = separator(x);
    ch = separator(y);
    //unsigned int str = clock();
    lol = KaratsubaMultipl(chuva, ch);
    //kek = SchoolMultipl(chuva, ch);
    //unsigned int end = clock();
    print(lol, "lol");
    //print(kek, "kek");
    //cout<<'\n'<<end-str<<'\n';
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