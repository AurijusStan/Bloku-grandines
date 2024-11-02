#include "transaction.h"

Transaction::Transaction(const std::string& id, const std::string& sender, const std::string& receiver, int amount)
    : id(id), sender(sender), receiver(receiver), amount(amount) {}

Transaction::Transaction(const Transaction& other)
    : id(other.id), sender(other.sender), receiver(other.receiver), amount(other.amount) {}

Transaction& Transaction::operator=(const Transaction& other) {
    if (this != &other) {
        id = other.id;
        sender = other.sender;
        receiver = other.receiver;
        amount = other.amount;
    }
    return *this;
}
