#include <bits/stdc++.h>

using namespace std;

string stobinary(string i){
    string binary;

    for(char c : i){
        bitset<8> b(c);
        binary += b.to_string();
    }

    return binary;
}

string myhash(string i){
    string endhash;

    string binary = stobinary(i);

    if(binary.size()%64!=0){
        for(int i=0; i<(64-(binary.size()%64)); i++){
            if(i%2 == 0){
                binary += '1';
            } 
            else{
                binary += '0';
            }
        }
    }

    string h[64]={};
    string h2[64]={};
    int k = 0;

    for(int i=0; i<binary.size(); i++){
        h[k] += (binary[i]);
        k++;
        if(k==64){
            k=0;
        }
    }

    for(int i=0; i<64; i++){
        cout<<h[i]<<" ";
    }

    for(int i=0; i<64; i++){
        long long num = stoi(h[i]);
        num += 14;
        num *= 2743;
        while(num>-1){
            int p=1;
            long long iterations=0;
            while(num/p>255){
                p*=10;
                iterations++;
            }
            char c;
            c = num/p;
            h2[i]+=c;
            string s = to_string(num);
            s = s.substr(s.size()-iterations);
            if(s.empty()) break;
            num = stoi(s);
        }
    }

    for(int i=0; i<64; i++){
        cout<<h2[i]<<" ";
    }

    return endhash;
}

int main() {
    string input;

    cout << "Enter a line of text: ";

    std::getline(std::cin, input);

    string final = myhash(input);

    return 0;
}