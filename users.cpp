#include <bits/stdc++.h>

struct User {
    std::string name;
    std::string publicKey;
    int balance;
};

std::string generateRandomHex(int length) {
    static const char hex_chars[] = "0123456789ABCDEF";
    std::random_device rd;
    std::mt19937 gen(rd());
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

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> firstDis(0, firstNames.size() - 1);
    std::uniform_int_distribution<> lastDis(0, lastNames.size() - 1);

    return firstNames[firstDis(gen)] + " " + lastNames[lastDis(gen)];
}

int generateBalance() {
    std::random_device rd;
    std::mt19937 gen(rd());
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

int main() {
    int userCount = 1000;
    std::vector<User> users = generateUsers(userCount);

    for (const auto& user : users) {
        std::cout << "Name: " << user.name << ", Public Key: " << user.publicKey << ", Balance: " << user.balance << '\n';
    }

    return 0;
}
