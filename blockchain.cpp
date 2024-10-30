#include "blockchain.h"

Blockchain::Blockchain() {
    chain.emplace_back(Block(0, {"Genesis Block"}, "0"));
}

void Blockchain::addBlock(const Block& newBlock) {
    chain.push_back(newBlock);
}

const Block& Blockchain::getLatestBlock() const {
    return chain.back();
}

bool Blockchain::isBlockValid(const Block& currentBlock, const Block& previousBlock) const {
    if (currentBlock.prevHash != previousBlock.hash) {
        return false;
    }
    if (currentBlock.hash != currentBlock.calculateHash()) {
        return false;
    }
    return true;
}

const std::vector<Block>& Blockchain::getChain() const {
    return chain;
}
