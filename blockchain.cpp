#include "blockchain.h"

Blockchain::Blockchain() {
    difficulty = 4;
    chain.push_back(Block(0, "0", "Genesis Block"));
}

void Blockchain::addBlock(Block newBlock) {
    newBlock.prevHash = getLatestBlock().hash;
    newBlock.mineBlock(difficulty);
    chain.push_back(newBlock);
}

Block Blockchain::getLatestBlock() const {
    return chain.back();
}

bool Blockchain::isChainValid() const {
    for (size_t i = 1; i < chain.size(); ++i) {
        const Block& currentBlock = chain[i];
        const Block& prevBlock = chain[i - 1];

        if (currentBlock.hash != currentBlock.calculateHash()) {
            return false;
        }
        
        if (currentBlock.prevHash != prevBlock.hash) {
            return false;
        }
    }
    return true;
}
