#include <bits/stdc++.h>

using namespace std;

string btohex(const bitset<8>& b) {
    stringstream ss;
    ss << hex << uppercase << setw(2) << setfill('0') << b.to_ulong();
    return ss.str();
}

string stobinary(string i) {
    string binary;
    for (char c : i) {
        bitset<8> b(c);
        binary += b.to_string();
    }
    return binary;
}



unsigned long long foldBinaryString(const string& binaryStr, size_t chunkSize = 64) {
    unsigned long long foldedNum = 0;
    size_t length = binaryStr.size();

    for (size_t i = 0; i < length; i += chunkSize) {
        string chunk = binaryStr.substr(i, chunkSize);
        
        if (chunk.empty()) {
            continue; 
        }

        if (chunk.find_first_not_of("01") != string::npos) {
            continue;
        }

        unsigned long long num = stoull(chunk, nullptr, 2);
        foldedNum ^= num;
    }
    return foldedNum;
}


unsigned long long rotateLeft(unsigned long long value, int shift, int bits = 64) {
    return (value << shift) | (value >> (bits - shift));
}

string myhash(string s) {
    const size_t blockSize = 64; 
    const size_t targetHashSize = 64; 

    string binary = stobinary(s);

    if (binary.size() % 512 != 0) {
        int paddingSize = 512 - (binary.size() % 512);
        binary.append(paddingSize, '1');  
    }

    bitset<256> finalHash; 

    for (size_t i = 0; i < binary.size(); i += 512) {
        string block = binary.substr(i, 512);
        string h[32] = {};
        int k = 0;

        for (int j = 0; j < block.size(); j++) {
            h[k] += block[j];
            k++;
            if (k == 32) {
                k = 0;
            }
        }

        for (int i = 0; i < 32; i++) {
            char originalChar = s[i % s.size()];
            bitset<8> originalbinary(originalChar);
            char b = 7 * (i + 1);
            h[i] += b;
            h[i] = stobinary(h[i]);

            for (int m = 0; m < h[i].size(); m++) {
                h[i][m] = h[i][m] ^ originalbinary[m % 8];
            }

            if (i > 0 && i < 31) {
                for (int m = 0; m < h[i].size(); m++) {
                    h[i][m] = h[i][m] ^ h[i - 1][m % h[i - 1].size()] ^ h[i + 1][m % h[i + 1].size()];
                }
            }

            if (i > 0) {
                for (int m = 0; m < h[0].size(); m++) {
                    h[0][m] = h[0][m] ^ h[i][m % h[i].size()];
                }
            }
        }

        for (int i = 0; i < 32; i++) {
            unsigned long long num = 0;

            if (!h[i].empty()) num = foldBinaryString(h[i]);

            char originalChar = s[i % s.size()];

            for(int j = 0; j < 5; j++){
                num += (originalChar ^ (147 ^ (i + 1))) % 4267291;
                num = (num * ((274 + i) ^ (originalChar + 3153))) ^ ((num >> 3) + 57 * i);
                num = rotateLeft(num, (j + i) % 64);
            }
            

            bitset<8> compressedNum(num & 0xFF); 
            size_t finalHashStart = (i * 8) % 256;
            for (size_t j = 0; j < 8; j++) {
                finalHash[finalHashStart + j] = finalHash[finalHashStart + j] ^ static_cast<bool>(compressedNum[j]);
            }
        }
    }

    stringstream ss;
    for (size_t i = 0; i < 256; i += 8) {
        bitset<8> byte(finalHash.to_string().substr(i, 8));
        ss << btohex(byte);
    }

    string finalHexHash = ss.str();

    if (finalHexHash.size() > targetHashSize) {
        finalHexHash = finalHexHash.substr(0, targetHashSize);
    } else {
        while (finalHexHash.size() < targetHashSize) {
            finalHexHash = "0" + finalHexHash;
        }
    }

    return finalHexHash;
}

string skaityti(int i) {
    string input;
    string failas = "konstitucija";

    ifstream file(failas + ".txt");

    if (!file.is_open()) {
        try {
            throw runtime_error("Wrongly entered data\n");
        } catch (const runtime_error &e) {
            cout << e.what();
        }
    } 
    else {
        int startLine = i, numLines = 512;
        string temp;
        int currentLine = 1;
        while (currentLine < startLine && getline(file, temp)) {
            currentLine++;
        }

        while (numLines > 0 && getline(file, temp)) {
            input += temp + " ";
            numLines--;
            // getline(file, temp);
            // if(myhash(input) == myhash(temp)) i++;
            // input = "";
            // numLines--;
        }

        file.close();
    }

    return input;
}

int main() {
    string input;
    int x=2;

    // while (true) {
    //     cout << "1 - by hand; 2 - from file" << endl;
    //     if (!(cin >> x) || x < 1 || x > 2) {
    //         try {
    //             throw runtime_error("Wrongly entered data\n");
    //         } catch (const runtime_error &e) {
    //             cin.clear();
    //             cin.ignore();
    //             cout << e.what();
    //         }
    //     } else break;
    // }

    // cin.ignore();

    if (x == 1) {
        cout << "Enter a line of text: ";
        getline(cin, input);
    } 
    else {
        input = skaityti(1);
    }
    
    auto start = chrono::high_resolution_clock::now();

    string final = myhash(input);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration = end - start;

    cout << "Final hash: " << final << endl;
    cout << "Time taken to hash: " << duration.count() << " milliseconds" << endl;

    return 0;
}