#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <vector>
#include "block.h"

class Blockchain {
public:
    Blockchain();

    void addBlock(Block newBlock);
    bool isChainValid() const;
    
private:
    int difficulty;
    std::vector<Block> chain;

    Block getLatestBlock() const;
};

#endif
