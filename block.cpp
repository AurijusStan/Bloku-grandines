#include "block.h"
#include "sha256.h"
#include "generator.h"
#include <sstream>

std::string sha256(const std::string& input) {
    uint8_t hash[32];
    SHA256_CTX ctx;
    sha256_init(&ctx);
    sha256_update(&ctx, reinterpret_cast<const uint8_t*>(input.c_str()), input.size());
    sha256_final(&ctx, hash);

    std::stringstream ss;
    for (int i = 0; i < 32; ++i)
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    return ss.str();
}

Block::Block(int idx, const std::vector<Transaction>& txs, const std::string& prevHash) 
    : index(idx), transactions(txs), prevHash(prevHash), nonce(0), timestamp(time(nullptr)) {
    merkleRoot = calculateMerkleRoot();
    hash = calculateHash();
}

std::string Block::calculateMerkleRoot() const {
    std::string combined;
    for (const auto& tx : transactions) {
        combined += sha256(tx.sender + "->" + tx.receiver + ": " + std::to_string(tx.amount));
    }
    return sha256(combined);
}

std::string Block::calculateHash() const {
    std::stringstream ss;
    ss << index << prevHash << merkleRoot << timestamp << nonce << version << difficultyTarget;
    return sha256(ss.str());
}

int Block::getIndex() const {
    return index;
}