#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include "sha256.h"

class Transaction {
public:
    std::string id;
    std::string sender;
    std::string receiver;
    int amount;

    Transaction() = default;

    Transaction(const std::string& sender, const std::string& receiver, int amount);

    Transaction(const Transaction& other);

    Transaction& operator=(const Transaction& other);

    bool isValid() const;

    bool operator==(const Transaction& other) const {
        return id == other.id && sender == other.sender && receiver == other.receiver && amount == other.amount;
    }

private: 
    std::string generateTransactionID() const;
};

#endif
