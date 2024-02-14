#include <iostream>
#include <iomanip>

struct Node {
    std::string key_;

    explicit Node(const std::string& key) : key_(key) { }
};

class HashLPTable {
private:
    Node **hash_table_;

    int capacity_;
    int size_;

public:
    explicit HashLPTable(int capacity) : capacity_(capacity), size_(0) {
        hash_table_ = new Node *[capacity]();
    }

    ~HashLPTable() {
        for (int i = 0; i < capacity_; ++i) {
            if (hash_table_[i] != nullptr && !hash_table_[i]->key_.empty()) {
                delete hash_table_[i];
                hash_table_[i] = nullptr;
            }
        }

        delete[] hash_table_;
    }

    void insert(const std::string& key) {
        if (size_ == capacity_) {
            std::cout << "HashTable is filled; Unable to insert key: " << key << std::endl;
            return;
        }

        size_t target = -1;
        size_t index = hash(key);

        if (hash_table_[index] == nullptr || hash_table_[index]->key_ == key) {
            target = index;
        } else {
            size_t next_index = (index + 1) % capacity_;

            while (next_index != index) {
                if (hash_table_[next_index] == nullptr || hash_table_[next_index]->key_ == key) {
                    target = next_index;
                    break;
                }
                next_index = (next_index + 1) % capacity_;
            }
        }

        Node *new_node = new Node(key);
        hash_table_[target] = new_node;

        std::cout << "Successfully inserted key: " << key << std::endl;
        size_++;
    }

    bool remove(const std::string& key) {
        size_t target = -1;
        size_t index = hash(key);

        if (hash_table_[index] != nullptr && hash_table_[index]->key_ == key) {
            target = index;
        } else {
            size_t next_index = (index + 1) % capacity_;

            while (next_index != index && hash_table_[next_index] != nullptr) {
                if (hash_table_[next_index]->key_ == key) {
                    target = next_index;
                    break;
                }
                next_index = (next_index + 1) % capacity_;
            }
        }

        if (target == -1) {
            std::cout << "- Failed to delete key: " << key << std::endl;
            return false;
        }

        delete hash_table_[target];
        hash_table_[target] = new Node("");
        size_--;

        std::cout << "- Successfully deleted key: " << key << std::endl;
        return true;
    }

    bool search(const std::string& key)
    {
        size_t index = hash(key);

        if (hash_table_[index]->key_ == key) {
            std::cout << "- Successfully founded key: " << key << "; at index: " << index << std::endl;
            return true;
        }

        size_t next_index = (index + 1) % capacity_;

        while (next_index != index && hash_table_[next_index] != nullptr) {
            if (hash_table_[next_index]->key_ == key) {
                std::cout << "- Successfully founded key: " << key << "; at index: " << next_index << std::endl;
                return true;
            }
            next_index = (next_index + 1) % capacity_;
        }

        std::cout << "- Unable to find key: " << key << std::endl;
        return false;
    }

    void display() {
        std::cout << std::endl;
        std::cout << "HASHTABLE; SIZE = " << size_ << std::endl;
        for (int i = 0; i < capacity_; ++i) {
            std::cout << i << " ";
            Node *node = hash_table_[i];

            std::cout << " ";
            if (node != nullptr) {
                std::cout << node->key_;
            }

            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    size_t hash(const std::string& key) {
        size_t hash = std::hash<std::string>{}(key);
        std::cout << std::endl;
        std::cout << "Hash of key: " << key << " is " << hash << "; % capacity = " << hash % capacity_ << std::endl;
        return hash % capacity_;
    }
};

int main() {
    HashLPTable hashtable(7);

    // inserting
    hashtable.insert("hse");
    hashtable.insert("fkn");
    hashtable.insert("algorithms");
    hashtable.insert("data");
    hashtable.insert("structures");
    hashtable.display();

    // deleting
    hashtable.remove("noSuchKey");
    hashtable.remove("hse");
    hashtable.remove("data");
    hashtable.display();

    // searching
    hashtable.search("data");
    hashtable.search("algorithms");

    return 0;
}
