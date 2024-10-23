#include "Block.h"
#include "hash.h"

Block::Block(int idx, const std::string& prevHash, const std::string& data) {
    this->index = idx;
    this->prevHash = prevHash;
    this->data = data;
    this->timestamp = time(nullptr);
    this->nonce = 0;
    this->hash = calculateHash();
}

std::string Block::calculateHash() const {
    return myhash(std::to_string(index) + prevHash + std::to_string(timestamp) + data + std::to_string(nonce));
}

void Block::mineBlock(int difficulty) {
    std::string str(difficulty, '0');
    while (hash.substr(0, difficulty) != str) {
        nonce++;
        hash = calculateHash();

        if (nonce % 10000 == 0) {
            std::cout << "Nonce: " << nonce << " | Hash: " << hash << std::endl;
        }
    }
    std::cout << "Block mined with nonce: " << nonce << " | Hash: " << hash << std::endl;
}

