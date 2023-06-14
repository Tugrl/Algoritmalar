#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <queue>

// Huffman Ağacı düğümü için sınıf tanımı
struct HuffmanNode {
    char character;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char c, int freq) : character(c), frequency(freq), left(nullptr), right(nullptr) {}
};

// Huffman Ağacı düğümlerini frekanslarına göre sıralamak için özel karşılaştırıcı
struct CompareNodes {
    bool operator()(HuffmanNode* node1, HuffmanNode* node2) {
        return node1->frequency > node2->frequency;
    }
};

// Normal.txt dosyasından harf frekanslarını hesaplayan fonksiyon
std::unordered_map<char, int> calculateFrequencies(const std::string& filename) {
    std::ifstream file(filename);
    std::unordered_map<char, int> frequencies;

    if (file.is_open()) {
        char c;
        while (file >> c) {
            frequencies[c]++;
        }
        file.close();
    }
    else {
        std::cout << "Dosya acilamadi: " << filename << std::endl;
    }

    return frequencies;
}

// Huffman Ağacını oluşturan fonksiyon
HuffmanNode* buildHuffmanTree(const std::unordered_map<char, int>& frequencies) {
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CompareNodes> pq;

    // Her harf için ayrı bir düğüm oluştur
    for (const auto& pair : frequencies) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    // Tüm düğümleri birleştirerek Huffman ağacını oluştur
    while (pq.size() > 1) {
        HuffmanNode* left = pq.top();
        pq.pop();
        HuffmanNode* right = pq.top();
        pq.pop();

        int combinedFreq = left->frequency + right->frequency;
        HuffmanNode* newNode = new HuffmanNode('\0', combinedFreq);
        newNode->left = left;
        newNode->right = right;

        pq.push(newNode);
    }

    return pq.top();
}

// Huffman ağacını ekrana gösteren yardımcı fonksiyon
void printHuffmanTree(HuffmanNode* root, std::string prefix = "") {
    if (root) {
        if (!root->left && !root->right) {
            std::cout << root->character << " : " << prefix << std::endl;
        }

        printHuffmanTree(root->left, prefix + "0");
        printHuffmanTree(root->right, prefix + "1");
    }
}

// Huffman ağacından karakter kodlamalarını hesaplayan yardımcı fonksiyon
void generateHuffmanCodes(HuffmanNode* root, std::unordered_map<char, std::string>& codes, std::string code = "") {
    if (root) {
        if (!root->left && !root->right) {
            codes[root->character] = code;
        }

        generateHuffmanCodes(root->left, codes, code + "0");
        generateHuffmanCodes(root->right, codes, code + "1");
    }
}

// Harfleri frekans değerlerine göre kapasitesi 8 olan bir Hash tablosuna ekleyen fonksiyon
void addToHashTable(std::unordered_map<char, std::string>& hashTable, const std::unordered_map<char, int>& frequencies) {
    for (const auto& pair : frequencies) {
        char character = pair.first;
        int frequency = pair.second;

        if (hashTable.find(character) == hashTable.end()) {
            if (frequency <= 8) {
                hashTable[character] = std::string(frequency, character);
            }
            else {
                std::cout << "Frekans 8'den buyuk: " << character << " : " << frequency << std::endl;
            }
        }
    }
}

// Huffman kodlamasını kullanarak metni sıkıştıran fonksiyon
void compressText(const std::string& inputFilename, const std::string& outputFilename, const std::unordered_map<char, std::string>& codes) {
    std::ifstream inputFile(inputFilename);
    std::ofstream outputFile(outputFilename, std::ios::binary);

    if (inputFile.is_open() && outputFile.is_open()) {
        char c;
        std::string compressedText;

        while (inputFile.get(c)) {
            compressedText += codes.at(c);
        }

        // Sıkıştırılmış veriyi 8 bitlik parçalar halinde yaz
        unsigned char buffer = 0;
        int bitsWritten = 0;
        for (char bit : compressedText) {
            buffer <<= 1;
            buffer |= (bit - '0');

            if (++bitsWritten == 8) {
                outputFile.write(reinterpret_cast<const char*>(&buffer), sizeof(buffer));
                buffer = 0;
                bitsWritten = 0;
            }
        }

        // Tamamlanmamış son byte'ı yaz
        if (bitsWritten > 0) {
            buffer <<= (8 - bitsWritten);
            outputFile.write(reinterpret_cast<const char*>(&buffer), sizeof(buffer));
        }

        inputFile.close();
        outputFile.close();
    }
    else {
        std::cout << "Dosya acilamadi: " << inputFilename << " veya " << outputFilename << std::endl;
    }
}

int main() {
    std::unordered_map<char, int> frequencies = calculateFrequencies("normal.txt");

    // Frekansları ekrana yazdır
    for (const auto& pair : frequencies) {
        std::cout << pair.first << " : " << pair.second << std::endl;
    }

    // Hash tablosunu oluştur
    std::unordered_map<char, std::string> hashTable;
    addToHashTable(hashTable, frequencies);

    // Huffman Ağacını oluştur
    HuffmanNode* root = buildHuffmanTree(frequencies);

    // Huffman Ağacını ekrana yazdır
    printHuffmanTree(root);

    // Huffman kodlamalarını hesapla
    std::unordered_map<char, std::string> codes;
    generateHuffmanCodes(root, codes);

    // Sıkıştırılmış veriyi oluştur
    compressText("normal.txt", "compressed.txt", codes);

    return 0;
}
