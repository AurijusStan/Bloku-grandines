#include "transaction.h"

Transaction::Transaction(const std::string& id, const std::string& sender, const std::string& receiver, int amount)
    : id(id), sender(sender), receiver(receiver), amount(amount) {}
