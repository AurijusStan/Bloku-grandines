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

    if(binary.size()%32!=0){
        for(int i=0; i<(32-(binary.size()%32)); i++){
            if(i%2 == 0){
                binary += '1';
            } 
            else{
                binary += '0';
            }
        }
    }

    string h[32]={};
    string h2[32]={};
    int k = 0;

    for(int i=0; i<binary.size(); i++){
        h[k] += (binary[i]);
        k++;
        if(k==32){
            k=0;
        }
    }

    // for(int i=0; i<32; i++){
    //     cout<<h[i]<<" ";
    // }

    for(int i=0; i<32; i++){
        long long num = stoi(h[i]);
        num += 14+i;
        num *= 2743-(32-i);
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

    for(int i=0; i<32; i++){
        swap(h2[i][0], h2[i][h2[i].size() - 1]);
        char b=82+i;
        h2[i]+b;
        h[i]=stobinary(h2[i]);
        if(h[i].size()%2!=0) h[i].pop_back();
        while(h[i].size()>8){
            if(h[i].size()%2!=0) h[i].pop_back();
            int x = stoi(h[i].substr(0, h[i].size()/2), nullptr, 2);
            int y = stoi(h[i].substr(h[i].size()/2), nullptr, 2);
            bitset<8> z(x+y);
            h[i]=z.to_string();
        }
        
    }

    for(int i=0; i<32; i++){
        cout<<h[i]<<" ";
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