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
                cout<<"Subst problems";
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

int main(){
    string x, y;
    x = "11";
    y = "19";

    vector<int> chuva, ch ,lol;
    chuva = separator(x);
    ch = separator(y);
    unsigned int str = clock();
    lol = KaratsubaMultipl(chuva, ch);
    unsigned int end = clock();
    for(int i:lol){
        cout<< i<< ' ';
    }
    cout<<'\n'<<end-str<<'\n';
    return 0;
}


int main0(){
    unsigned long long z;
    z = pow(2, 10);
    for(unsigned long long i=100; i<=z;i++){
        for(unsigned long long j = 100;j<=z;j++){
            if (KaratsubaMultipl(separator(to_string(i)), separator(to_string(j))) == SchoolMultipl(separator(to_string(i)), separator(to_string(j)))){continue;}
            else{
                cout<<i<< ','<< j<< "Houston, we've got a problem";
                break;
            }
        }
    }
    return 0;
}