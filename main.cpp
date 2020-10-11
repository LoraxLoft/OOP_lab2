#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;


string summ(string x, string y){
    string res="";
    int perehod=0, sum;
    for(int i = x.size()-1; i>=0; i--){
        sum = x[i] - '0' + y[i] - '0' + perehod;
        perehod = sum/10;
        sum %= 10;
        res.insert(0, to_string(sum));
    }
    if (perehod!=0){
        res.insert(0, to_string(perehod));
    }
    return res;
}

string multipl(string a, string b){
    if (a.size() <= 4){
        return to_string(stoi(a)*stoi(b));
    } else {
        string a1, a0, b1, b0;
        a1 = a.substr(0, a.size()/2);
        a0 = a.substr(a.size()/2,a.size());
        b1 = a.substr(0, b.size()/2);
        b0 = a.substr(b.size()/2,b.size());

        return "";
    }

}


class Karatsuba{

    vector <int> a,b;

public:
    Karatsuba(const string& ch1,const string& ch2){

        for(int i = 0; i< ch1.size(); i+=1){
            a.push_back(stoi(ch1.substr(i, 1)));
        }
        for(int i = 0; i< ch2.size(); i+=1){
            b.push_back(stoi(ch1.substr(i, 1)));
        }
    }

    void show(){
        for(int i : a){
            cout << i<< ' ';
        }
    }

};

int main(){
    string x, y;
    x = "012";
    y = "321";
    /*
    Karatsuba karatel = Karatsuba(x,y);

    karatel.show();
    */
    cout<<summ(x,y);
    return 0;
}
