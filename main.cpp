/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <sstream>
#include <functional>
using namespace std;

// Drug structure
struct Drug {
    string batchID;
    string name;
    int quantity;
    string expiryDate;
    string temperature;
    string location;
};

// Block structure for tracking drug entries
class Block {
public:
    int index;
    string timestamp;
    string data;
    string prevHash;
    string hash;

    Block(int idx, string data, string prevHash) {
        this->index = idx;
        this->data = data;
        this->prevHash = prevHash;
        this->timestamp = getCurrentTime();
        this->hash = computeHash();
    }

    string computeHash() {
        string toHash = to_string(index) + timestamp + data + prevHash;
        std::hash<string> hasher;
        return to_string(hasher(toHash));
    }

    string getCurrentTime() {
        time_t now = time(0);
        return ctime(&now);
    }
};

// Blockchain class
class Blockchain {
public:
    vector<Block> chain;

    Blockchain() {
        chain.push_back(createGenesisBlock());
    }

    Block createGenesisBlock() {
        return Block(0, "Genesis Block", "0");
    }

    void addBlock(string data) {
        Block newBlock(chain.size(), data, chain.back().hash);
        chain.push_back(newBlock);
    }

    void showChain() {
        for (const auto& block : chain) {
            cout << "\n--- Block " << block.index << " ---\n";
            cout << "Timestamp: " << block.timestamp;
            cout << "Data: " << block.data << endl;
            cout << "Prev Hash: " << block.prevHash << endl;
            cout << "Hash: " << block.hash << endl;
        }
    }
};

// Global inventory and blockchain ledger
vector<Drug> inventory;
Blockchain ledger;

// Add drug to inventory and ledger
void insertDrug(string batchID, string name, int qty, string expiry, string temp, string location) {
    Drug d = {batchID, name, qty, expiry, temp, location};
    inventory.push_back(d);

    stringstream ss;
    ss << name << "-" << batchID << " | Qty: " << qty << " | Exp: " << expiry;
    ledger.addBlock(ss.str());

    cout << "✅ Drug Added: " << name << " | Batch: " << batchID << endl;
}

// Show current inventory
void showInventory() {
    cout << "\n📦 Inventory:\n";
    for (const auto& d : inventory) {
        cout << "BatchID: " << d.batchID
             << ", Name: " << d.name
             << ", Qty: " << d.quantity
             << ", Expiry: " << d.expiryDate
             << ", Temp: " << d.temperature
             << ", Location: " << d.location << endl;
    }
}

// Main program
int main() {
    insertDrug("RFID001", "Paracetamol", 100, "2025-12-31", "22°C", "Pune");
    insertDrug("RFID002", "Ibuprofen", 60, "2026-01-15", "20°C", "Mumbai");
    insertDrug("RFID003", "Amoxicillin", 75, "2025-10-10", "18°C", "Delhi");

    showInventory();

    cout << "\n🔗 Blockchain Ledger:\n";
    ledger.showChain();

    return 0;
}
