#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include "sha256.h"

class Transaction {
public:
    

    Transaction() = default;

    Transaction(const std::string& sender, const std::string& receiver, int amount);

    Transaction(const Transaction& other);

    Transaction& operator=(const Transaction& other);

    std::string getId() const;
    std::string getSender() const;
    std::string getReceiver() const;
    int getAmount() const;

    void setSender(const std::string& sender);
    void setReceiver(const std::string& receiver);
    void setAmount(int amount);

    bool isValid() const;

    bool operator==(const Transaction& other) const {
        return id == other.id && sender == other.sender && receiver == other.receiver && amount == other.amount;
    }

private: 
    std::string id;
    std::string sender;
    std::string receiver;
    int amount;

    std::string generateTransactionID() const;
};

#endif
