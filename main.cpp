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

#include "generator.h"
#include "blockchain.h"
#include <iostream>

int main() {
    std::cout << "Starting user generation...\n";
    int userCount = 10;
    std::vector<User> users = generateUsers(userCount);
    std::cout << "User generation completed.\n";

    std::cout << "Starting transaction generation...\n";
    int transactionCount = 20;
    std::vector<Transaction> transactions = generateTransactions(users, transactionCount);
    std::cout << "Transaction generation completed.\n";

    Blockchain blockchain;
    Block newBlock(blockchain.getChain().size(), transactions, blockchain.getLatestBlock().hash);
    blockchain.addBlock(newBlock);

    std::cout << "Blockchain setup completed.\n";
    return 0;
}