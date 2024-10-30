#ifndef BLOCK_H
#define BLOCK_H

#include <bits/stdc++.h>

class Block {
public:
    std::string prevHash;
    std::string hash;
    std::string merkleRoot;
    time_t timestamp;
    int nonce;
    int version;
    int difficultyTarget;
    std::vector<std::string> transactions;

    Block(int index, const std::vector<std::string>& transactions, const std::string& prevHash);

    std::string calculateHash() const;
    std::string calculateMerkleRoot() const;

    int getIndex() const;

private:
    int index;
};

#endif