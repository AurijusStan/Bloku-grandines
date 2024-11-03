#include <bits/stdc++.h>
#include "blockchain.h"
#include "generator.h"
#include "transaction.h"

bool processTransaction(Transaction& tx, std::vector<User>& users) {
    auto senderIt = std::find_if(users.begin(), users.end(), [&tx](const User& user) { return user.publicKey == tx.sender; });
    auto receiverIt = std::find_if(users.begin(), users.end(), [&tx](const User& user) { return user.publicKey == tx.receiver; });

    if (senderIt == users.end() || receiverIt == users.end()) {
        std::cout << "Transaction invalid: Sender or receiver not found.\n";
        return false;
    }

    if (senderIt->balance < tx.amount) {
        std::cout << "Transaction invalid: Insufficient funds.\n";
        return false;
    }

    senderIt->balance -= tx.amount;
    receiverIt->balance += tx.amount;

    std::cout << "Processed transaction " << tx.id << ": " << tx.amount
              << " from " << senderIt->name << " to " << receiverIt->name << "\n";
    return true;
}

void mineBlock(Blockchain& blockchain, std::vector<User>& users, std::vector<Transaction>& transactions, int difficulty) {
    const std::string prevHash = blockchain.getLatestBlock().hash;

    std::vector<Transaction> blockTransactions;
    for (int i = 0; i < std::min(100, static_cast<int>(transactions.size())); ++i) {
        blockTransactions.push_back(transactions[i]);
    }

    Block newBlock(blockchain.getChain().size(), blockTransactions, prevHash);

    std::string target(difficulty, '0');
    while (newBlock.hash.substr(0, difficulty) != target) {
        newBlock.nonce++;
        newBlock.hash = newBlock.calculateHash();
    }
    std::cout << "Block mined: " << newBlock.hash << std::endl;

    for (auto& tx : newBlock.transactions) {
        if (processTransaction(tx, users)) {
            transactions.erase(transactions.begin());
        }
    }

    blockchain.addBlock(newBlock);
}

int main() {
    int userCount = 1000;
    std::vector<User> users = generateUsers(userCount);

    int transactionCount = 10000;
    std::vector<Transaction> transactions = generateTransactions(users, transactionCount);

    Blockchain blockchain;
    int difficulty = 4;

    while (!transactions.empty()) {
        std::cout << "\nMining a new block with " << std::min(100, static_cast<int>(transactions.size())) << " transactions...\n";
        mineBlock(blockchain, users, transactions, difficulty);
    }

    std::cout << "\nFinal user balances:\n";
    for (const auto& user : users) {
        std::cout << "User: " << user.name << ", Balance: " << user.balance << "\n";
    }

    std::cout << "\nBlockchain:\n";
    for (const auto& block : blockchain.getChain()) {
        std::cout << "Block Index: " << block.getIndex() << ", Hash: " << block.hash << ", PrevHash: " << block.prevHash << "\n";
    }

    return 0;
}