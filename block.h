#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <ctime>

class Block {
public:
    std::string hash;
    std::string prevHash;
    std::string data;
    time_t timestamp;
    int index;
    int nonce;

    Block(int idx, const std::string& prevHash, const std::string& data);

    std::string calculateHash() const;
    void mineBlock(int difficulty);
    
private:
    std::string getHashString() const;
};

#endif
