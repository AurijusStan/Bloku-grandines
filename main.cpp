#include <bits/stdc++.h>
#include "blockchain.h"
#include "generator.h"
#include "transaction.h"

std::vector<Transaction> selectRandomTransactions(const std::vector<Transaction>& transactions, int maxCount = 100) {
    int count = std::min(maxCount, static_cast<int>(transactions.size()));
    
    std::vector<Transaction> selectedTransactions;
    
    if (count == 0) {
        std::cout << "No transactions available for selection.\n";
        return selectedTransactions;
    }

    selectedTransactions = transactions;
    std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
    std::shuffle(selectedTransactions.begin(), selectedTransactions.end(), gen);

    selectedTransactions.resize(count);

    return selectedTransactions;
}

bool processTransaction(const Transaction& tx, std::vector<User>& users) {
    auto senderIt = std::find_if(users.begin(), users.end(), [&tx](const User& user) { return user.publicKey == tx.sender; });
    auto receiverIt = std::find_if(users.begin(), users.end(), [&tx](const User& user) { return user.publicKey == tx.receiver; });

    if (senderIt == users.end() || receiverIt == users.end()) {
        std::cout << "Transaction invalid: Sender or receiver not found.\n";
        return false;
    }

    if (senderIt->balance < tx.amount) {
        std::cout << "Transaction invalid: Insufficient funds.\n";
        return false;
    }

    senderIt->balance -= tx.amount;
    receiverIt->balance += tx.amount;

    std::cout << "Processed transaction " << tx.id << ": " << tx.amount << " from " << senderIt->name << " to " << receiverIt->name << "\n";
    return true;
}

void mineBlock(Blockchain& blockchain, std::vector<User>& users, std::vector<Transaction>& transactions, int difficulty) {
    const std::string prevHash = blockchain.getLatestBlock().hash;

    std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
    std::shuffle(transactions.begin(), transactions.end(), gen);

    std::vector<Transaction> blockTransactions;
    auto txIt = transactions.begin();
    while (blockTransactions.size() < 100 && txIt != transactions.end()) {
        if (txIt->isValid()) {
            blockTransactions.push_back(*txIt);
        }
        ++txIt;
    }

    if (blockTransactions.empty()) {
        std::cout << "No valid transactions to mine.\n";
        return;
    }

    Block newBlock(blockchain.getChain().size(), blockTransactions, prevHash);

    std::string target(difficulty, '0');
    while (newBlock.hash.substr(0, difficulty) != target) {
        newBlock.nonce++;
        newBlock.hash = newBlock.calculateHash();
    }
    std::cout << "Block mined: " << newBlock.hash << std::endl;

    for (const auto& tx : newBlock.transactions) {
        if (processTransaction(tx, users)) {
            auto txToErase = std::find(transactions.begin(), transactions.end(), tx);
            if (txToErase != transactions.end()) {
                transactions.erase(txToErase);
            }
        }
    }

    blockchain.addBlock(newBlock);
    std::cout << "Block added to blockchain.\n";
}

void attemptMiningCandidates(Blockchain& blockchain, std::vector<User>& users, std::vector<Transaction>& transactions, int difficulty) {
    const int numCandidates = 5;
    int timeLimitMs = 1000;
    int maxIterations = 10000; 

    while (true) {
        std::vector<Block> candidates;

        for (int i = 0; i < numCandidates; ++i) {
            std::vector<Transaction> blockTransactions = selectRandomTransactions(transactions, 100);

            if (!blockTransactions.empty()) {
                Block candidateBlock(blockchain.getChain().size(), blockTransactions, blockchain.getLatestBlock().hash);
                candidates.push_back(candidateBlock);
            }
        }

        bool blockMined = false;

        for (Block& candidate : candidates) {
            auto start = std::chrono::steady_clock::now();
            int iterations = 0;
            std::string target(difficulty, '0');

            while (candidate.hash.substr(0, difficulty) != target &&
                   std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() < timeLimitMs &&
                   iterations < maxIterations) {
                candidate.nonce++;
                candidate.hash = candidate.calculateHash();
                iterations++;
            }

            if (candidate.hash.substr(0, difficulty) == target) {
                std::cout << "Successfully mined block with hash: " << candidate.hash << "\n";
                
                for (auto& tx : candidate.transactions) {
                    if (processTransaction(tx, users)) {
                        auto txIt = std::find(transactions.begin(), transactions.end(), tx);
                        if (txIt != transactions.end()) transactions.erase(txIt);
                    }
                }

                blockchain.addBlock(candidate);
                blockMined = true;
                break;
            }
        }

        if (blockMined) {
            std::cout << "Block successfully mined and added to the blockchain.\n";
            break;
        }

        std::cout << "No block mined. Increasing time limit and iteration count.\n";
        timeLimitMs *= 2;
        maxIterations *= 2;
    }
}


void displayBlockInfo(const Blockchain& blockchain, int blockIndex) {
    if (blockIndex < 0 || blockIndex >= blockchain.getChain().size()) {
        std::cout << "Invalid block index.\n";
        return;
    }

    const Block& block = blockchain.getChain()[blockIndex];
    std::cout << "\nBlock Index: " << block.getIndex() << "\n";
    std::cout << "Hash: " << block.hash << "\n";
    std::cout << "Previous Hash: " << block.prevHash << "\n";
    std::cout << "Merkle Root: " << block.merkleRoot << "\n";
    std::cout << "Timestamp: " << block.timestamp << "\n";
    std::cout << "Nonce: " << block.nonce << "\n";
    std::cout << "Transactions:\n";
    for (const auto& tx : block.transactions) {
        std::cout << "  ID: " << tx.id << ", Amount: " << tx.amount << ", From: " << tx.sender << ", To: " << tx.receiver << "\n";
    }
    std::cout << "---------------------------\n";
}

void displayTransactionInfo(const Blockchain& blockchain, const std::string& transactionID) {
    for (const auto& block : blockchain.getChain()) {
        for (const auto& tx : block.transactions) {
            if (tx.id == transactionID) {
                std::cout << "\nTransaction ID: " << tx.id << "\n";
                std::cout << "Amount: " << tx.amount << "\n";
                std::cout << "Sender: " << tx.sender << "\n";
                std::cout << "Receiver: " << tx.receiver << "\n";
                std::cout << "Included in Block Index: " << block.getIndex() << "\n";
                return;
            }
        }
    }
    std::cout << "Transaction ID " << transactionID << " not found in any block.\n";
}

void displayMenu() {
    Blockchain blockchain;
    std::vector<User> users;
    std::vector<Transaction> transactions;
    int difficulty = 5;

    while (true) {
        std::cout << "\nMenu:\n";
        std::cout << "1. Generate Users\n";
        std::cout << "2. Generate Transactions\n";
        std::cout << "3. Add 100 Random Transactions to New Block\n";
        std::cout << "4. Mine Block\n";
        std::cout << "5. Display Blockchain and User Balances\n";
        std::cout << "6. View Block Information\n";
        std::cout << "7. View Transaction Information\n";
        std::cout << "8. Attempt Mining with Multiple Candidates\n";
        std::cout << "9. Exit\n";
        std::cout << "Choose an option: ";

        int choice;
        std::cin >> choice;

        if (std::cin.fail() || choice < 1 || choice > 9) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid choice. Please enter a number between 1 and 8.\n";
            continue;
        }

        if (choice == 1) {
            int userCount;
            std::cout << "Enter the number of users to generate: ";
            std::cin >> userCount;
            users = generateUsers(userCount);
            std::cout << "Generated " << userCount << " users.\n";

        } else if (choice == 2) {
            if (users.empty()) {
                std::cout << "Please generate users first.\n";
                continue;
            }
            int transactionCount;
            std::cout << "Enter the number of transactions to generate: ";
            std::cin >> transactionCount;
            transactions = generateTransactions(users, transactionCount);
            std::cout << "Generated " << transactionCount << " transactions.\n";

        } else if (choice == 3) {
            std::vector<Transaction> selectedTransactions = selectRandomTransactions(transactions, 100);
            const std::string prevHash = blockchain.getLatestBlock().hash;
            if (selectedTransactions.empty()) {
                std::cout << "No transactions available to create a new block.\n";
            } else {
                Block newBlock(blockchain.getChain().size(), selectedTransactions, prevHash);
                std::cout << "New block with 100 random transactions prepared but not mined.\n";
            }
        } else if (choice == 4) {
            if (transactions.empty()) {
                std::cout << "No transactions to mine. Please generate transactions first.\n";
            } else {
                mineBlock(blockchain, users, transactions, difficulty);
            }

        } else if (choice == 5) {
            std::cout << "\nBlockchain:\n";
            for (const auto& block : blockchain.getChain()) {
                std::cout << "Block Index: " << block.getIndex() << ", Hash: " << block.hash << ", PrevHash: " << block.prevHash << "\n";
            }

            std::cout << "\nUser Balances:\n";
            for (const auto& user : users) {
                std::cout << "User: " << user.name << ", Balance: " << user.balance << "\n";
            }

        } else if (choice == 6) {
            int blockIndex;
            std::cout << "Enter the block index to view: ";
            std::cin >> blockIndex;
            displayBlockInfo(blockchain, blockIndex);

        } else if (choice == 7) {
            std::string transactionID;
            std::cout << "Enter the transaction ID to view: ";
            std::cin >> transactionID;
            displayTransactionInfo(blockchain, transactionID);

        } else if (choice == 8) {
            attemptMiningCandidates(blockchain, users, transactions, difficulty);

        } else if (choice == 9) {
            std::cout << "Exiting program.\n";
            break;

        } else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

int main() {
    displayMenu();
    return 0;
}
