// generator.h
#ifndef GENERATOR_H
#define GENERATOR_H

#include <vector>
#include <string>

struct User {
    std::string name;
    std::string publicKey;
    int balance;
};

struct Transaction {
    std::string id;
    std::string sender;
    std::string receiver;
    int amount;
};

std::vector<User> generateUsers(int count);
std::vector<Transaction> generateTransactions(const std::vector<User>& users, int transactionCount);

#endif
