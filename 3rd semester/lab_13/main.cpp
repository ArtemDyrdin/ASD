#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class HashTable {
public:
    std::vector<std::string> table;
private:
    int size;

    [[nodiscard]] int hash_function(const std::string& key) const {
        int sum = 0;
        for (char c : key)
            sum += static_cast<int>(c);
        return sum % size;
    }

public:
    explicit HashTable(int size) : size(size), table(size) {}

    // Вставить слово с обработкой коллизии вложением
    void insert(const std::string& key) {
        int index = hash_function(key);
        while (!table[index].empty()) {
            index = (index + 1) % size;
        }
        table[index] = key;
    }
};

int main() {
    HashTable hash_table(100);

    std::ifstream file("text.txt");
    std::string word;
    while (file >> word) {
        hash_table.insert(word);
    }
    file.close();

    std::ofstream outfile("output.txt");
    if (outfile.is_open()) {
        for (int i = 0; i < hash_table.table.size(); i++)
            outfile << i << " " << hash_table.table[i] << std::endl;
        outfile.close();
    } else
        std::cout << "Unable to open file for writing" << std::endl;

    return 0;
}

