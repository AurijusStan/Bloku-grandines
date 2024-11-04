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

void displayMenu() {
    Blockchain blockchain;
    std::vector<User> users;
    std::vector<Transaction> transactions;
    int difficulty = 4;

    while (true) {
        std::cout << "\nMenu:\n";
        std::cout << "1. Generate Users\n";
        std::cout << "2. Generate Transactions\n";
        std::cout << "3. Add 100 Random Transactions to New Block\n";
        std::cout << "4. Mine Block\n";
        std::cout << "5. Display Blockchain and User Balances\n";
        std::cout << "6. Exit\n";
        std::cout << "Choose an option: ";

        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number between 1 and 6.\n";
            continue;
        }

        if (choice == 1) {
            int userCount;
            std::cout << "Enter the number of users to generate: ";
            std::cin >> userCount;
            users = generateUsers(userCount);
            std::cout << "Generated " << userCount << " users.\n";

        } else if (choice == 2) {
            if (users.empty()) {
                std::cout << "Please generate users first.\n";
                continue;
            }
            int transactionCount;
            std::cout << "Enter the number of transactions to generate: ";
            std::cin >> transactionCount;
            transactions = generateTransactions(users, transactionCount);
            std::cout << "Generated " << transactionCount << " transactions.\n";

        } else if (choice == 3) {
            if (transactions.size() < 100) {
                std::cout << "Not enough transactions to add to a block. Generate more transactions.\n";
                continue;
            }
            std::vector<Transaction> blockTransactions;
            for (int i = 0; i < 100 && i < transactions.size(); ++i) {
                blockTransactions.push_back(transactions[i]);
            }
            Block newBlock(blockchain.getChain().size(), blockTransactions, blockchain.getLatestBlock().hash);
            std::cout << "Added 100 transactions to a new block (not yet mined).\n";

        } else if (choice == 4) {
            if (transactions.empty()) {
                std::cout << "No transactions to mine. Please generate transactions first.\n";
            } else {
                mineBlock(blockchain, users, transactions, difficulty);
            }

        } else if (choice == 5) {
            std::cout << "\nBlockchain:\n";
            for (const auto& block : blockchain.getChain()) {
                std::cout << "Block Index: " << block.getIndex() << ", Hash: " << block.hash << ", PrevHash: " << block.prevHash << "\n";
            }

            std::cout << "\nUser Balances:\n";
            for (const auto& user : users) {
                std::cout << "User: " << user.name << ", Balance: " << user.balance << "\n";
            }

        } else if (choice == 6) {
            std::cout << "Exiting program.\n";
            break;

        } else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

int main() {
    displayMenu();
    return 0;
}
