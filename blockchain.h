#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <vector>
#include "block.h"

class Blockchain {
public:
    Blockchain();
    void addBlock(const Block& newBlock);
    const Block& getLatestBlock() const;

    const std::vector<Block>& getChain() const;

private:
    std::vector<Block> chain;
    bool isBlockValid(const Block& currentBlock, const Block& previousBlock) const;
};

#endif
