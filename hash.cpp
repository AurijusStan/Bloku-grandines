#include <bits/stdc++.h>

using namespace std;

string btohex(string b){
    stringstream ss;
    bitset<32> bb(b);
    ss << hex << uppercase << bb.to_ulong();
    return ss.str();
}

string stobinary(string i){
    string binary;
    for(char c : i){
        bitset<8> b(c);
        binary += b.to_string();
    }
    return binary;
}

string myhash(string s){
    string endhash;

    string binary = stobinary(s);

    if(binary.size()%32!=0){
        int k = binary.size();
        int d = 1;
        for(int i=0; i<(32-(k%32)); i++){
            if(i%2 != 0){
                binary += (binary.size() % d == 0) ? '1' : '0';
                d++;
            } 
            else{
                binary += '1';
            }
        }
    }
    cout<<binary<<endl;

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

    for(int i=0; i<32; i++){
        long long num = 0;
        if (!h[i].empty()) num = stoll(h[i], nullptr, 2);

        char originalChar = s[i % s.size()];        
        num += (originalChar ^ (1487 ^ (i + 1))) % 429967291;
        num = (num * ((274 + i) ^ (originalChar + 3153))) ^ ((num >> 3) + 57 * i);
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
            num = stoll(s);
        }

        for (int m = 0; m < h[i].size(); m++) {
            h[i][m] = h[i][m] ^ originalChar; 
        }

        if (i > 0 && i < 31) {
            for (int m = 0; m < h[i].size(); m++) {
                h[i][m] = h[i][m] ^ h[i-1][m % h[i-1].size()] ^ h[i+1][m % h[i+1].size()];
            }
        }
    }

    for(int i=0; i<32; i++){
        swap(h2[i][0], h2[i][h2[i].size() - 1]);
        char b=82+i;
        h2[i]+b;
        h[i]=stobinary(h2[i]);

        while(h[i].size() < 10) {
            h[i] += "1";
        }

        if(h[i].size()%2!=0) h[i].pop_back();

        while(h[i].size()>8){
            if(h[i].size()%2!=0) h[i].pop_back();
            int x = stoi(h[i].substr(0, h[i].size()/2), nullptr, 2);
            int y = stoi(h[i].substr(h[i].size()/2), nullptr, 2);
            bitset<8> z((x ^ (y >> 2)) ^ (2953 ^ (i + 7)));
            h[i]=z.to_string();
        }
        endhash += btohex(h[i]);
    }

    return endhash;
}

int main() {
    string input;

    cout << "Enter a line of text: ";

    std::getline(std::cin, input);

    string final = myhash(input);

    cout<<"Final hash: "<<final;

    return 0;
}