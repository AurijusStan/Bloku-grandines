#include <bits/stdc++.h>
#include "transaction.h"

std::string toHexString(const uint8_t* hash, size_t length) {
    std::stringstream ss;
    for (size_t i = 0; i < length; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    return ss.str();
}

Transaction::Transaction(const std::string& sender, const std::string& receiver, int amount)
    : sender(sender), receiver(receiver), amount(amount) {
        id = generateTransactionID();
    }

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

bool Transaction::isValid() const {
    return id == generateTransactionID();
}

std::string Transaction::generateTransactionID() const {
    std::string data = sender + receiver + std::to_string(amount);

    SHA256_CTX ctx;
    sha256_init(&ctx);
    sha256_update(&ctx, reinterpret_cast<const uint8_t*>(data.c_str()), data.size());

    uint8_t hash[SHA256_BLOCK_SIZE];
    sha256_final(&ctx, hash);

    return toHexString(hash, SHA256_BLOCK_SIZE);
}