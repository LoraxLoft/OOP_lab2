#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#define BASE 10
#define base_len 1

using namespace std;

// have to deal with 0-s

class VeryLong{

    vector<int> value;

public:

    VeryLong(){
        value.push_back(0);
    }
    VeryLong(string num){
        value.push_back(stoi(num.substr(0, num.size()%base_len)));
        for(int i = 0; i<num.size()/base_len; i++){
            value.push_back(stoi(num.substr(num.size()%base_len + i*base_len, base_len)));
        }
    }



};

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

vector<int> div_on_scalar(vector<int> vec, int scal){
    if(scal==1){
        return vec;
    }
    vector<int> res;
    for(int i=0; i<vec.size()-1; i++){
        res.push_back(vec[i]/scal);
        vec[i+1] += (vec[i]%scal)*BASE;
    }
    res.push_back(vec[vec.size()-1]/scal);
    normalise(res);
    return res;
}

vector<int> KaratsubaMultipl(vector<int> a, vector<int> b, int depth = 0){
    //cout<< "depth now:"<< depth<<endl;
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

        a1b1 = KaratsubaMultipl(a1, b1, depth+1);
        a0b0 = KaratsubaMultipl(a0, b0, depth+1);
        abmini = KaratsubaMultipl(summ(a1, a0), summ(b1, b0), depth+1);

        res = summ(summ(sdvig(a1b1, (a.size() - a.size()/2)*2), a0b0),sdvig(subtr(subtr(abmini, a1b1), a0b0), a.size() - a.size()/2));

        return res;
    }
}

vector<int> SchoolMultipl(vector<int> a, vector<int> b){
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
        return SchoolMultipl(b,a);
    }
}

vector<int> polynoom(vector<int>& a, vector<int>& b, vector<int>& c, int x){
    vector<int> X_zminna, X_zminna_2;
    X_zminna_2.push_back(x*x);
    X_zminna.push_back(x);
    return summ(summ(SchoolMultipl(a, X_zminna_2), SchoolMultipl(b, X_zminna)), c);
}

vector<int> ToomMultipl(vector<int> a, vector<int> b){
    int a_s = a.size();
    urovnenie(a,b);
    if (a.size()<=3){
        return SchoolMultipl(a,b);
    } else {
        vector<int> res;
        res.push_back(0);
        vector<int> a2, a1, b2, b1, u4, u3, u2, u1, u0, v4, v3, v2, v1, v0, w4, w3, w2, w1, w0;
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

        u1 = polynoom(a2, a1, u0, 1);
        u2 = polynoom(a2, a1, u0, 2);
        u3 = polynoom(a2, a1, u0, 3);
        u4 = polynoom(a2, a1, u0, 4);
        v1 = polynoom(b2, b1, v0, 1);
        v2 = polynoom(b2, b1, v0, 2);
        v3 = polynoom(b2, b1, v0, 3);
        v4 = polynoom(b2, b1, v0, 4);

        w.push_back(ToomMultipl(u0, v0));
        w.push_back(ToomMultipl(u1, v1));
        w.push_back(ToomMultipl(u2, v2));
        w.push_back(ToomMultipl(u3, v3));
        w.push_back(ToomMultipl(u4, v4));

        vector<vector<int>> bufferL, bufferS2(1);
        vector<int> bufferS1(1);

        for(int i = 1; i<=4; i++){
            for(int j = i; j<=4; j++){
                bufferL.push_back(div_on_scalar(subtr(w[j],w[j-1]), i));
            }
            //намечается костыль
            w.erase(w.begin()+i,w.end());
            w.insert(w.end(), bufferL.begin(), bufferL.end());
            bufferL.erase(bufferL.begin(), bufferL.end());
        }

        for(int i = 3; i>=1; i--){
            bufferS1[0] =i;
            for(int j = 3; j>=i; j--){
                bufferS2[0]=(subtr(w[j], SchoolMultipl(w[j+1], bufferS1)));
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

int main0(){
    string x, y;
    x = "1234";
    y = "2341";

    vector<int> chuva, ch ,lol;
    chuva = separator(x);
    ch = separator(y);
    unsigned int str = clock();
    lol = ToomMultipl(chuva, ch);
    unsigned int end = clock();
    for(int i:lol){
        cout<< i<< ' ';
    }
    cout<<'\n'<<end-str<<'\n';
    return 0;
}


int main(){
    unsigned long long z;
    z = pow(2, 15);
    for(unsigned long long i=1000; i<=z;i++){
        for(unsigned long long j = 1000;j<=z;j++){
            if (ToomMultipl(separator(to_string(i)), separator(to_string(j))) == SchoolMultipl(separator(to_string(i)), separator(to_string(j)))){continue;}
            else{
                cout<<i<< ','<< j<< "Houston, we've got a problem"<<endl;
                break;
            }
        }
    }
    return 0;
}