#include <bits/stdc++.h>

using namespace std;

string btohex(string b){
    stringstream ss;
    bitset<8> bb(b);
    ss << hex << uppercase << setw(2) << setfill('0') << bb.to_ulong();
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

string skaityti(int i){
    string input;
    // cout << "Enter file name without '.txt': ";
    string failas="random";
    // cin>>failas;

    ifstream file(failas+".txt");

    if(!file.is_open()){
        try{
            throw runtime_error("Wrongly entered data\n"); 
        }
        catch(const runtime_error &e){
            cout<<e.what();
        }
    }
    else{
        int startLine=i, numLines=1;
        // cout << "Enter the starting line: ";
        // cin >> startLine;
        // cout << "Enter the number of lines to read: ";
        // cin >> numLines;

        string temp;
        int currentLine = 1;
        while(currentLine < startLine && std::getline(file, temp)) {
            currentLine++;
        }

        while(numLines > 0 && std::getline(file, temp)){
            input += temp+" ";
            numLines--;
        }

        file.close();
    }

    return input;
}

unsigned long long foldBinaryString(const string& binaryStr, size_t chunkSize = 64) {
    unsigned long long foldedNum = 0;
    size_t length = binaryStr.size();
    for (size_t i = 0; i < length; i += chunkSize) {
        string chunk = binaryStr.substr(i, chunkSize);
        unsigned long long num = stoull(chunk, nullptr, 2);
        foldedNum ^= num;
    }
    return foldedNum;
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
        unsigned long long num = 0;

        if (!h[i].empty()) num = foldBinaryString(h[i]);

        char originalChar = s[i % s.size()];        
        num += (originalChar ^ (147 ^ (i + 1))) % 4267291;
        num = (num * ((274 + i) ^ (originalChar + 3153))) ^ ((num >> 3) + 57 * i);
        while(num>-1){
            if(s.empty()) break;
            int p=1;
            unsigned long long iterations=0;
            while(num/p>255){
                p*=10;
                iterations++;
            }
            char c;
            c = num/p;
            h2[i]+=c;
            if(p==1) break;
            string s = to_string(num);
            s = s.substr(s.size()-iterations);
            if(s.empty()) break;
            if(!s.empty()) num = stoll(s);
        }
    }

    for(int i=0; i<32; i++){
        char originalChar = s[i % s.size()];
        bitset<8> originalbinary(originalChar);
        char b=7*(i+1);
        h2[i]+=b;
        h[i]=stobinary(h2[i]);

        for (int m = 0; m < h[i].size(); m++) {
            h[i][m] = h[i][m] ^ originalbinary[m%8]; 
        }

        if (i > 0 && i < 31) {
            for (int m = 0; m < h[i].size(); m++) {
                h[i][m] = h[i][m] ^ h[i-1][m % h[i-1].size()] ^ h[i+1][m % h[i+1].size()];
            }
        }

        // if (i > 0) {
        //     for (int m = 0; m < h[0].size(); m++) {
        //         h[0][m] = h[0][m] ^ h[i][m % h[i].size()];
        //     }
        // }

        while(h[i].size() % 16 != 0) {
            h[i] += (h[i].size() % 2 == 0) ? '0' : '1';
        }

        while(h[i].size()>8){
            if(h[i].size()%2!=0) h[i].pop_back();
            int x = stoi(h[i].substr(0, h[i].size()/2), nullptr, 2);
            int y = stoi(h[i].substr(h[i].size()/2), nullptr, 2);
            bitset<8> z(x ^ y);
            // bitset<8> z((x ^ (y >> 2)) ^ (2953 ^ (i + 7)));
            h[i]=z.to_string();
        }
        while(h[i].size()<8){
            h[i]="0" + h[i];
        }

        endhash += btohex(h[i]);
    }

    return endhash;
}

int main() {
    string input;

    int x=2;
    // while(true){
    //     cout<<"1-by hand; 2-from file"<<endl;
    //     if(!(cin>>x)||x<1||x>2){
    //         try{
    //             throw runtime_error("Wrongly entered data\n");
    //         }
    //         catch(const runtime_error &e){
    //             cin.clear();
    //             cin.ignore();
    //             cout<<e.what();
    //         }
    //     }
    //     else break;
    // }

    // cin.ignore();

    if(x==1){
        cout << "Enter a line of text: ";
        std::getline(std::cin, input);
    }
    else{
        int kartojasi=0;
        for(int i=0; i<100000-2; i++){
            string input1 = skaityti(i);
            i++;
            string input2 = skaityti(i);
            if(myhash(input1)==myhash(input2)) kartojasi++;
        }
        cout<<kartojasi;
    }
    
    // auto start = chrono::high_resolution_clock::now();

    // string final = myhash(input);

    // auto end = chrono::high_resolution_clock::now();
    // chrono::duration<double, milli> duration=end-start;

    // cout<<"Final hash: "<<final<<endl;
    // cout<<"Time taken to hash: "<<duration.count()<<" milliseconds"<<endl;

    return 0;
}