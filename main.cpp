#include <bits/stdc++.h>
#include "blockchain.h"

void mineBlock(Blockchain& blockchain, const std::vector<std::string>& transactions, int difficulty) {
    const std::string prevHash = blockchain.getLatestBlock().hash;

    Block newBlock(blockchain.getChain().size(), transactions, prevHash);

    std::string target(difficulty, '0');

    while (newBlock.hash.substr(0, difficulty) != target) {
        newBlock.nonce++;
        newBlock.hash = newBlock.calculateHash();
    }

    std::cout << "Block mined: " << newBlock.hash << std::endl;
    
    blockchain.addBlock(newBlock);
}

int main() {
    Blockchain blockchain;

    int difficulty = 4;
    std::vector<std::string> transactions1 = {"Alice pays Bob 10 BTC", "Charlie pays Dave 5 BTC"};
    std::vector<std::string> transactions2 = {"Eve pays Frank 20 BTC", "George pays Helen 15 BTC"};
    
    std::cout << "Mining Block 1..." << std::endl;
    mineBlock(blockchain, transactions1, difficulty);

    std::cout << "Mining Block 2..." << std::endl;
    mineBlock(blockchain, transactions2, difficulty);

    for (const auto& block : blockchain.getChain()) {
        std::cout << "Block Index: " << block.getIndex() << std::endl;
        std::cout << "Previous Hash: " << block.prevHash << std::endl;
        std::cout << "Transactions: " << block.merkleRoot << std::endl;
        std::cout << "Hash: " << block.hash << std::endl;
        std::cout << "Nonce: " << block.nonce << std::endl;
        std::cout << "Timestamp: " << block.timestamp << std::endl;
        std::cout << "---------------------------" << std::endl;
    }

    return 0;
}