#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class Transaction {
public:
    std::string id;
    std::string sender;
    std::string receiver;
    int amount;

    Transaction() = default;

    Transaction(const std::string& id, const std::string& sender, const std::string& receiver, int amount);

    Transaction(const Transaction& other);

    Transaction& operator=(const Transaction& other);
};

#endif
