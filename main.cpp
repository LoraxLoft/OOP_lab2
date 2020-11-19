#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

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

    friend std::ostream& operator<< (std::ostream &out, const IlangLong &ilangLong);

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
            nosilki = vec[i]/Base;
            vec[i] %= Base;
        }
        while (nosilki!=0){
            vector<int> nos;
            nos.push_back(nosilki%Base);
            nosilki/=Base;
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
                a[i] += Base;
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

    void set_Base(int n){
        switch (n){
            case 2:
                (*this).base_to_2();
                Base = 2, base_Len = 1;
                break;
            case 10:
                (*this).base_to_10();
                Base = 10, base_Len = 1;
                break;
            default:
                cout<<"Imposible base to convert to\n";
        }
    }

    vector<int> modul_for_shin(vector<int> a, int m_s){
        //we count on that m=2^m_s - 1
        vector<int> res;

        int ukaz = 0, delitsa=1, a_s = a.size();

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

    IlangLong mod_for_shin(int m_s){
        (*this).normalise(value);
        if (value[0]==0){
            return IlangLong(0);
        }
        return IlangLong(modul_for_shin(value, m_s));
    }

    IlangLong mult_for_shin(int m_s){
        IlangLong res=0;
        for(int i = 0; i<m_s; i++){
            res += (*this).sdvig(i);
        }
        return res;
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
        int bas = b.Base;
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
    }

    void base_to_10(){
        IlangLong res;
        IlangLong cur_step_2 = 1;
        for(int i = value.size()-1; i>=0; i--){
            if(value[i]){
                res+=cur_step_2;
            }
            cur_step_2 = cur_step_2.SchoolMultipl(2);
        }
        (*this) = res;
    }

    static void setMult(Multiplication *some_way){
        mult_metod = some_way;
    }
};

std::ostream& operator<< (std::ostream &out, const IlangLong &ilangLong)
{
    for(int i: ilangLong.value){
        out << i;
    }

    return out;
}

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
            abmini = multiply(a1 + a0, b1 + b0);

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
    int depth = 0;

    IlangLong multiply(IlangLong a, IlangLong b) override{
        a.urovnenie(a.value, b.value);
        IlangLong res;
        //cout<<"your good";
        if (a.value.size()<=26){
            return a.SchoolMultipl(b);
        } else {
            vector<IlangLong> u, v, w;
            int k = int(log((float(a.value.size())-8)/9 -1)/log(3.0)) +1;
            int qk = int(pow(3, k)+1)/2;
            int mods[6] = {-1, 1, 2, 3, 5, 7};
            //cout<<"your good1";
            for(int & mod : mods){
                mod = 6*qk + mod;
            }
            //cout<<"your good2";
            for(int mod : mods){
                w.push_back(multiply(a.mod_for_shin(mod), b.mod_for_shin(mod)).mod_for_shin(mod));
            }
            //w is right
            // creating w_
            vector<IlangLong> w_;
            w_.push_back(w[0].mod_for_shin(mods[0]));
            IlangLong buffer;
            //cout<<"your good3";
            for (int i = 1; i<6 ; i++){
                buffer = w[i];
                //cout<<"your good4";
                for (int j = 0; j<i; j++){
                    //cout<<mods[j]<<' '<<mods[i]<<endl;
                    int buf10 = poisk(mods[j], mods[i]);
                    //cout<<"\tb="<<buf10<<endl;
                    int b2=0;
                    int counter = 0;
                    while (buf10!=0){
                        b2 += buf10%2 * (int)pow(10, counter);
                        buf10/=2;
                        counter+=1;
                    }
                    int ak = mods[j];
                    int dk = (b2%10)*ak;
                    //buffer.print("buf");
                    //w_[j].print("w_");
                    IlangLong uk = buffer - w_[j];
                    IlangLong vk = uk.SchoolMultipl(b2%10);
                    //cout<<"k = 0\n\t"<<"a0 = "<<ak<<", d0 = "<< dk<<endl;
                    //uk.print("\tu0");
                    //vk.print("\tv0");
                    //cout<<"your good5";
                    for (int c = 1; c<counter; c++){
                        //cout<<"your good7";
                        uk = (uk + uk.sdvig(ak)).mod_for_shin(mods[i]);
                        vk = (vk + uk.SchoolMultipl((int)(b2/pow(10,c))%10).sdvig(dk)).mod_for_shin(mods[i]);
                        ak = (2*ak)%mods[i];
                        dk = (dk + ((int)(b2/pow(10,c))%10)*ak)%mods[i];
                        //cout<<"k = "<<k<<"\n\t"<<"a"<<k<<" = "<<ak<<", d"<<k<<" = "<<dk<<endl;
                        //uk.print("\tu");
                        //vk.print("\tv");
                    }
                    buffer = vk;
                }
                w_.push_back(buffer);
            }
            res = w_[5];
            for (int i = 4; i>=0; i--){
                res = res.mult_for_shin(mods[i]) + w_[i];
            }

            return res;
        }
    }

    static long long poiskObratnogo(long long x, long long mod) {
        long long obrat = 1;
        long long stepen = x;
        for(long long k = mod-2; k>0; k/=2){
            if(k%2){
                obrat = (obrat*stepen)%mod;
            }
            stepen = (stepen*stepen)%mod;
        }
        return obrat;
    }

    static int poisk(int x, int m){
        return (Evklid_Algo(x, m).first%m+m)%m;
    }

    static pair<int, int> Evklid_Algo(int a, int b){
        int x, y;
        if (a==0){
            return {0,1};
        }
        pair<int, int> x1y1 = Evklid_Algo(b%a, a);
        x = x1y1.second - (b/a) * x1y1.first;
        y = x1y1.first;
        return {x, y};
    }
};

Multiplication* IlangLong::mult_metod = nullptr; //Null ptr
int main(){

    IlangLong x, y, z, w;
    IlangLong::mult_metod = new KaratsubaMult();
    //x = "11100011010010111011011011100100110";

    x = "34567865435987";
    y = "73459234659237";


    z = x*y;
    w = x.SchoolMultipl(y);
    cout<<z<< '\n'<<w;

    return 0;
}