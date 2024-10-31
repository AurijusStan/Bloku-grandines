#include <bits/stdc++.h>
#include "blockchain.h"
#include "generator.h"
#include "transaction.h"

void mineBlock(Blockchain& blockchain, std::vector<User>& users, std::vector<Transaction>& transactions, int difficulty) {
    std::vector<Transaction> blockTransactions;
    for (int i = 0; i < 100 && !transactions.empty(); ++i) {
        blockTransactions.push_back(transactions.back());
        transactions.pop_back();
    }

    Block newBlock(blockchain.getChain().size(), blockTransactions, blockchain.getLatestBlock().hash);

    std::string target(difficulty, '0');
    while (newBlock.hash.substr(0, difficulty) != target) {
        newBlock.nonce++;
        newBlock.hash = newBlock.calculateHash();
    }

    std::cout << "Block mined: " << newBlock.hash << std::endl;

    for (const auto& tx : newBlock.transactions) {
        auto senderIt = std::find_if(users.begin(), users.end(), [&tx](const User& user) { return user.publicKey == tx.sender; });
        auto receiverIt = std::find_if(users.begin(), users.end(), [&tx](const User& user) { return user.publicKey == tx.receiver; });

        if (senderIt != users.end() && receiverIt != users.end() && senderIt->balance >= tx.amount) {
            senderIt->balance -= tx.amount;
            receiverIt->balance += tx.amount;
        }
    }

    newBlock.transactions.clear();

    blockchain.addBlock(newBlock);
}

int main() {
    Blockchain blockchain;
    std::vector<User> users = generateUsers(1000);
    std::vector<Transaction> transactions = generateTransactions(users, 10000);

    int difficulty = 4;

    std::cout << "Mining Block 1..." << std::endl;
    mineBlock(blockchain, users, transactions, difficulty);

    std::cout << "Mining Block 2..." << std::endl;
    mineBlock(blockchain, users, transactions, difficulty);

    for (const auto& block : blockchain.getChain()) {
        std::cout << "Block Index: " << block.getIndex() << std::endl;
        std::cout << "Previous Hash: " << block.prevHash << std::endl;
        std::cout << "Hash: " << block.hash << std::endl;
        std::cout << "Nonce: " << block.nonce << std::endl;
        std::cout << "---------------------------" << std::endl;
    }

    std::cout << "\nUser balances after mining:" << std::endl;
    for (const auto& user : users) {
        std::cout << "User: " << user.name << ", Balance: " << user.balance << std::endl;
    }

    return 0;
}
