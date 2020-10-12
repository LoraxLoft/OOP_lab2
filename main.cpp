#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

void urovnenie(vector<int>& a, vector<int>& b){
    if (a.size() == b.size()) {
        return;
    } else {
        vector<int> buffer;
        buffer.push_back(0);
        if (a.size() > b.size()){
            for(int i = 0; i<a.size() - b.size() + 1; i++){
                b.insert(b.begin(), buffer.begin(), buffer.end());
            }
        } else {
            for(int i = 0; i<b.size() - a.size() + 1; i++){
                a.insert(a.begin(), buffer.begin(), buffer.end());
            }
        }
    }
}

void normalise(vector<int>& vec){
    int nosilki = 0;
    for(int i = vec.size()-1; i>=0; i--){
        vec[i]+=nosilki;
        nosilki = vec[i]/10000;
        vec[i] %= 10000;
    }
    while (nosilki){
        vector<int> nos;
        nos.push_back(nosilki%10000);
        nosilki/=10000;
        vec.insert(vec.begin(), nos.begin(), nos.end());
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

void sdvig(vector<int>& a, int n){
    int pustie_rozryadi = n/4;
    a[a.size()-1] *= pow(10,n%4);
    normalise(a);
    for(int i = 0; i<pustie_rozryadi; i++){
        a.push_back(0);
    }
}


vector<int> multipl(string a, string b){
    if (a.size() <= 4){
        vector<int> res;
        int result = stoi(a) * stoi(b);
        res.push_back(result);
        normalise(res);
        return res;
    } else {
        string a1, a0, b1, b0;
        vector<int> a1b1, a0b0, a1_a0b1_b0;
        a1 = a.substr(0, a.size()/2);
        a0 = a.substr(a.size()/2,a.size());
        b1 = a.substr(0, b.size()/2);
        b0 = a.substr(b.size()/2,b.size());
        
        return a1b1;
    }
}

class Karatsuba{

    vector <int> n,m;
    string c,d;
public:
    Karatsuba(const string& ch1,const string& ch2){
        c = ch1; d = ch2;
        for(int i = 0; i< ch1.size(); i+=1){
            n.push_back(stoi(ch1.substr(i, 1)));
        }
        for(int i = 0; i< ch2.size(); i+=1){
            m.push_back(stoi(ch1.substr(i, 1)));
        }
    }

    void show(){
        vector<int> n;
        for(int i : n){
            cout << i<< ' ';
        }
    }

};

int main(){
    string x, y;
    /*
    x = "12345678900000000";
    y = "321";

    Karatsuba karatel = Karatsuba(x,y);

    karatel.show();
    */
    vector<int> sum;
    vector<int> chuva(3);
    chuva[0] = 1234;
    chuva[1] = 1568;
    chuva[2] = 9876;
    vector<int> chuvak(4);
    chuvak[0] = 1234;
    chuvak[1] = 1568;
    chuvak[2] = 9876;
    chuvak[3] = 1234;
    sum = summ(chuva, chuvak);
    for(int i: chuva){
        cout<< i<< ' ';
    }
    cout<< endl;
    for(int i: chuvak){
        cout<< i<< ' ';
    }
    cout<< endl;
    for(int i: sum){
        cout<< i<< ' ';
    }
    return 0;
}
