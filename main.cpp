#include <bits/stdc++.h>
#include "blockchain.h"
#include "generator.h"

void mineBlock(Blockchain& blockchain, const std::vector<Transaction>& transactions, int difficulty) {
    std::vector<std::string> transactionStrings;
    for (const auto& tx : transactions) {
        transactionStrings.push_back(tx.sender + " pays " + tx.receiver + " " + std::to_string(tx.amount) + " BTC");
    }

    Block newBlock(blockchain.getChain().size(), transactionStrings, blockchain.getLatestBlock().hash);
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
    
    std::vector<User> users = generateUsers(1000);
    std::vector<Transaction> allTransactions = generateTransactions(users, 10000);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(allTransactions.begin(), allTransactions.end(), gen);

    std::vector<Transaction> transactionsForBlock1(allTransactions.begin(), allTransactions.begin() + 100);
    std::vector<Transaction> transactionsForBlock2(allTransactions.begin() + 100, allTransactions.begin() + 200);

    std::cout << "Mining Block 1..." << std::endl;
    mineBlock(blockchain, transactionsForBlock1, difficulty);

    std::cout << "Mining Block 2..." << std::endl;
    mineBlock(blockchain, transactionsForBlock2, difficulty);

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
