#include "blockchain.h"
#include "transaction.h"

Blockchain::Blockchain() {
    Transaction genesisTransaction("Genesis", "Genesis", 0);
    std::vector<Transaction> genesisTransactions = { genesisTransaction };
    
    Block genesisBlock(0, genesisTransactions, "0");
    chain.push_back(genesisBlock);
}

void Blockchain::addBlock(const Block& newBlock) {
    chain.push_back(newBlock);
}

const Block& Blockchain::getLatestBlock() const {
    return chain.back();
}

bool Blockchain::isBlockValid(const Block& currentBlock, const Block& previousBlock) const {
    if (currentBlock.getPreviousHash() != previousBlock.getHash()) {
        return false;
    }
    if (currentBlock.getHash() != currentBlock.calculateHash()) {
        return false;
    }
    return true;
}

const std::vector<Block>& Blockchain::getChain() const {
    return chain;
}
