#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

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

vector<int> subtr(vector<int> a, vector<int> b){
    urovnenie(a, b);
    vector<int> res, buff(1);
    for(int i = a.size()-1; i>=0; i--){
        if (a[i] < b[i]){
            a[i-1]-=1;
            a[i] += 10000;
        }
        buff[0] = a[i] - b[i];
        res.insert(res.begin(), buff.begin(), buff.end());
        buff[0] = 0;
    }
    return res;
}

vector<int> sdvig(vector<int> a, int n){
    for(int i = 0; i<n; i++){
        a.push_back(0);
    }
    return a;
}

vector<int> multipl(vector<int> a, vector<int> b){
    urovnenie(a, b);
    if (a.size() == 0){
        vector<int> res;
        return res;
    }
    if (a.size() == 1){
        vector<int> res;
        int result = a[0] * b[0];
        res.push_back(result);
        normalise(res);
        return res;
    } else {
        vector<int> a1b1, a0b0, abmini, a1, b1, a0, b0;
        a1.insert(a1.begin(), a.begin(), a.begin()+a.size()/2);
        a0.insert(a0.begin(), a.begin()+a.size()/2, a.end());
        b1.insert(b1.begin(), b.begin(), b.begin()+b.size()/2);
        b0.insert(b0.begin(), b.begin()+b.size()/2, b.end());

        a1b1 = multipl(a1, b1);
        a0b0 = multipl(a0, b0);
        abmini = multipl(summ(a1, a0), summ(b1, b0));
/*
        cout<<"a1b1:  ";
        for(int i: a1b1){cout<<i<<' ';}
        cout<<"\na0b0:  ";
        for(int i: a0b0){cout<<i<<' ';}
        cout<<"\nabmini:  ";
        for(int i: abmini){cout<<i<<' ';}
*/
        return summ(summ(sdvig(a1b1, (a.size() - a.size()/2)*2), a0b0),sdvig(subtr(subtr(abmini, a1b1), a0b0), a.size() - a.size()/2)) ;
    }
}

vector<int> separator(const string& s){
    vector<int> res;
    res.push_back(stoi(s.substr(0, s.size()%4)));
    for(int i = 0; i<s.size()/4; i++){
        res.push_back(stoi(s.substr(s.size()%4 + i*4, 4)));
    }
    return res;
}

int main(){
    string x, y;
    x = "9";
    y = "9876543219876543213345663424526357764648646123465612345672345999999999999999999999999999999999999";

    vector<int> chuva, ch ,lol;
    chuva = separator(x);
    ch = separator(y);
    lol = multipl(chuva, ch);
    for(int i:lol){
        cout<< i<< ' ';
    }
    cout<<'\n'<<lol.size();
/*
    Karatsuba karatel = Karatsuba(x,y);

    karatel.show();

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
    */
    return 0;
}
