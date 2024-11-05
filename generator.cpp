#include "generator.h"
#include "transaction.h"
#include <bits/stdc++.h>

std::string generateRandomHex(int length) {
    static const char hex_chars[] = "0123456789ABCDEF";
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dis(0, 15);

    std::ostringstream oss;
    for (int i = 0; i < length; ++i) {
        oss << hex_chars[dis(gen)];
    }

    std::string result = oss.str();
    return result;
}

std::string generateName() {
    static const std::vector<std::string> firstNames = {
        "Alice", "Bob", "Charlie", "Diana", "Eve", "Frank", "Grace", "Hank", "Ivy", "Jack"
    };
    static const std::vector<std::string> lastNames = {
        "Smith", "Johnson", "Williams", "Jones", "Brown", "Davis", "Miller", "Wilson", "Moore", "Taylor"
    };

    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> firstDis(0, firstNames.size() - 1);
    std::uniform_int_distribution<> lastDis(0, lastNames.size() - 1);

    std::string result = firstNames[firstDis(gen)] + " " + lastNames[lastDis(gen)];
    return result;
}

int generateBalance() {
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> balanceDis(100, 1000000);

    int balance = balanceDis(gen);
    return balance;
}

std::vector<User> generateUsers(int count) {
    std::vector<User> users;
    users.reserve(count);
    std::unordered_set<std::string> usedKeys;

    std::random_device rd;
    std::mt19937 gen(rd());

    for (int i = 0; i < count; ++i) {
        User user;
        user.name = generateName();

        std::string newKey = generateRandomHex(64);
        while (usedKeys.find(newKey) != usedKeys.end()) {
            newKey = generateRandomHex(64);
        }
        usedKeys.insert(newKey);
        user.publicKey = newKey;
        user.balance = generateBalance();

        users.push_back(user);
        
        std::cout << "Generated user " << i + 1 << ": " << user.name << ", Public Key: " << user.publicKey << ", Balance: " << user.balance << "\n";
    }

    std::cout << "Finished generating users.\n";
    return users;
}

// std::string generateTransactionID(int length = 16) {
//     static const char hex_chars[] = "0123456789ABCDEF";
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::uniform_int_distribution<> dis(0, 15);

//     std::ostringstream oss;
//     for (int i = 0; i < length; ++i) {
//         oss << hex_chars[dis(gen)];
//     }
//     return oss.str();
// }

int generateTransactionAmount() {
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> amountDis(1, 100000);

    int amount = amountDis(gen);
    return amount;
}

std::vector<Transaction> generateTransactions(const std::vector<User>& users, int transactionCount) {
    std::vector<Transaction> transactions;
    transactions.reserve(transactionCount);

    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> userDis(0, users.size() - 1);

    for (int i = 0; i < transactionCount; ++i) {
        int senderIndex, receiverIndex;
        
        senderIndex = userDis(gen);
        do {
            receiverIndex = userDis(gen);
        } while (receiverIndex == senderIndex);

        int amount = generateTransactionAmount();

        Transaction tx(users[senderIndex].publicKey, users[receiverIndex].publicKey, amount);
        transactions.push_back(tx);

        std::cout << "Generated transaction " << i + 1 << ": " << tx.id << " from " << tx.sender << " to " << tx.receiver << ", Amount: " << tx.amount << "\n";
    }

    std::cout << "Finished generating transactions.\n";
    return transactions;
}