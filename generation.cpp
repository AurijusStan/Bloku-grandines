#include <bits/stdc++.h>

struct User {
    std::string name;
    std::string publicKey;
    int balance;
};

std::random_device rd;
std::mt19937 gen(rd());

std::string generateRandomHex(int length) {
    static const char hex_chars[] = "0123456789ABCDEF";
    std::uniform_int_distribution<> dis(0, 15);

    std::ostringstream oss;
    for (int i = 0; i < length; ++i) {
        oss << hex_chars[dis(gen)];
    }
    return oss.str();
}

std::string generateName() {
    static const std::vector<std::string> firstNames = {
        "Alice", "Bob", "Charlie", "Diana", "Eve", "Frank", "Grace", "Hank", "Ivy", "Jack"
    };
    static const std::vector<std::string> lastNames = {
        "Smith", "Johnson", "Williams", "Jones", "Brown", "Davis", "Miller", "Wilson", "Moore", "Taylor"
    };

    std::uniform_int_distribution<> firstDis(0, firstNames.size() - 1);
    std::uniform_int_distribution<> lastDis(0, lastNames.size() - 1);

    return firstNames[firstDis(gen)] + " " + lastNames[lastDis(gen)];
}

int generateBalance() {
    std::uniform_int_distribution<> balanceDis(100, 1000000);
    return balanceDis(gen);
}

std::vector<User> generateUsers(int count) {
    std::vector<User> users;
    users.reserve(count);

    for (int i = 0; i < count; ++i) {
        User user;
        user.name = generateName();
        user.publicKey = generateRandomHex(64);
        user.balance = generateBalance();
        users.push_back(user);
    }
    return users;
}

struct Transaction {
    std::string id;
    std::string sender;
    std::string receiver;
    int amount;
};

std::string generateTransactionID(int length = 16) {
    static const char hex_chars[] = "0123456789ABCDEF";
    std::uniform_int_distribution<> dis(0, 15);

    std::ostringstream oss;
    for (int i = 0; i < length; ++i) {
        oss << hex_chars[dis(gen)];
    }
    return oss.str();
}

int generateTransactionAmount() {
    std::uniform_int_distribution<> amountDis(1, 10000);
    return amountDis(gen);
}

std::vector<Transaction> generateTransactions(const std::vector<User>& users, int transactionCount) {
    std::vector<Transaction> transactions;
    transactions.reserve(transactionCount);

    std::uniform_int_distribution<> userDis(0, users.size() - 1);

    for (int i = 0; i < transactionCount; ++i) {
        Transaction tx;
        tx.id = generateTransactionID();

        int senderIndex = userDis(gen);
        int receiverIndex;
        do {
            receiverIndex = userDis(gen);
        } while (receiverIndex == senderIndex);

        tx.sender = users[senderIndex].publicKey;
        tx.receiver = users[receiverIndex].publicKey;
        tx.amount = generateTransactionAmount();

        transactions.push_back(tx);
    }
    return transactions;
}

int main() {
    int userCount = 1000;
    int transactionCount = 10000;

    std::vector<User> users = generateUsers(userCount);

    std::vector<Transaction> transactions = generateTransactions(users, transactionCount);

    std::unordered_map<std::string, std::string> publicKeyToName;
    for (const auto& user : users) {
        publicKeyToName[user.publicKey] = user.name;
    }

    for (int i = 0; i < 10; ++i) {
        const Transaction& tx = transactions[i];
        std::cout << "Transaction ID: " << tx.id
                  << ", Sender: " << publicKeyToName[tx.sender]
                  << ", Receiver: " << publicKeyToName[tx.receiver]
                  << ", Amount: " << tx.amount << '\n';
    }

    return 0;
}
