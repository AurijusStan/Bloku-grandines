#ifndef GENERATOR_H
#define GENERATOR_H

#include <bits/stdc++.h>
#include "transaction.h"

struct User {
    std::string name;
    std::string publicKey;
    int balance;

    User() = default;
    User(const std::string& name, const std::string& publicKey, int balance)
        : name(name), publicKey(publicKey), balance(balance) {}
};

std::string generateRandomHex(int length);

std::string generateName();

int generateBalance();

std::vector<User> generateUsers(int count);

std::string generateTransactionID(int length);

int generateTransactionAmount();

std::vector<Transaction> generateTransactions(const std::vector<User>& users, int transactionCount);

#endif
