#ifndef BLOCK_H
#define BLOCK_H

#include <bits/stdc++.h>
#include "transaction.h"

class Block {
public:
    Block(int idx, const std::vector<Transaction>& transactions, const std::string& prevHash);

    std::string calculateHash() const;
    std::string calculateMerkleRoot() const;

    int getIndex() const;
    std::string getPreviousHash() const;
    std::string getHash() const;
    std::string getMerkleRoot() const;
    time_t getTimestamp() const;
    int getNonce() const;
    int getVersion() const;
    int getDifficultyTarget() const;
    const std::vector<Transaction>& getTransactions() const;
    void setHash(const std::string& newHash);
    void setMerkleRoot(const std::string& newMerkleRoot);
    void setNonce(int newNonce);

private:
    int index;
    std::string prevHash;
    std::string hash;
    std::string merkleRoot;
    time_t timestamp;
    int nonce;
    int version;
    int difficultyTarget;
    std::vector<Transaction> transactions;
};

#endif
