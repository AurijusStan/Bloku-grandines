#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <bits/stdc++.h>

class Transaction {
public:
    std::string id;
    std::string sender;
    std::string receiver;
    int amount;

    Transaction() = default;

    Transaction(const std::string& id, const std::string& sender, const std::string& receiver, int amount)
        : id(id), sender(sender), receiver(receiver), amount(amount) {}

    Transaction(const Transaction& other) 
        : id(other.id), sender(other.sender), receiver(other.receiver), amount(other.amount) {}

    Transaction& operator=(const Transaction& other) {
        if (this != &other) {
            id = other.id;
            sender = other.sender;
            receiver = other.receiver;
            amount = other.amount;
        }
        return *this;
    }
};

#endif