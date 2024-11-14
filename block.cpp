#include "block.h"
#include "sha256.h"
#include "generator.h"

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

Block::Block(int idx, const std::vector<Transaction>& txs, const std::string& previousHash)
    : index(idx), transactions(txs), prevHash(previousHash), nonce(0), timestamp(time(nullptr)), version(1), difficultyTarget(4) {
    merkleRoot = calculateMerkleRoot();
    hash = calculateHash();
}

std::string Block::calculateMerkleRoot() const {
    std::string combined;
    for (const auto& tx : transactions) {
        combined += sha256(tx.getSender() + "->" + tx.getReceiver() + ": " + std::to_string(tx.getAmount()));
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

std::string Block::getPreviousHash() const {
    return prevHash;
}

std::string Block::getHash() const {
    return hash;
}

std::string Block::getMerkleRoot() const {
    return merkleRoot;
}

time_t Block::getTimestamp() const {
    return timestamp;
}

int Block::getNonce() const {
    return nonce;
}

int Block::getVersion() const {
    return version;
}

int Block::getDifficultyTarget() const {
    return difficultyTarget;
}

const std::vector<Transaction>& Block::getTransactions() const {
    return transactions;
}

void Block::setHash(const std::string& newHash) {
    hash = newHash;
}

void Block::setMerkleRoot(const std::string& newMerkleRoot) {
    merkleRoot = newMerkleRoot;
}

void Block::setNonce(int newNonce) {
    nonce = newNonce;
}