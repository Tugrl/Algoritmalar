#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef struct Node {
    char letter;
    int frequency;
    struct Node* left;
    struct Node* right;
} Node;
typedef struct HashNode {
    char letter;
    int frequency;
    struct Node* chain;
} HashNode;
#define TABLE_SIZE 8
char letters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
int hashFunction(char letter) {
    return (int)letter % TABLE_SIZE;
}
void printFrequencyTable(HashNode* hashTable) {
    printf("Frekans Tablosu:\n");
    printf("\n");
    printf("Harf    Frekans\n");
    printf("\n");
    
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = hashTable[i].chain;
        while (current != NULL) {
            printf("  %c       %d\n", current->letter, current->frequency);
            current = current->right;
        }
    }
    
    printf("\n");
}
void printHuffmanTree(Node* root, char* code, int level) {
    if (root->letter != '\0') {
        code[level] = '\0';
        printf("  %c: %s\n", root->letter, code);
        return;
    }
    
    code[level] = '0';
    printHuffmanTree(root->left, code, level + 1);
    code[level] = '1';
    printHuffmanTree(root->right, code, level + 1);
}
Node* createNode(char letter, int frequency) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->letter = letter;
    newNode->frequency = frequency;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
void addToHashTable(HashNode* hashTable, char letter, int frequency) {
    int index = hashFunction(letter);
    Node* newNode = createNode(letter, frequency);
    
    if (hashTable[index].chain == NULL) {
        hashTable[index].chain = newNode;
    } else {
        Node* current = hashTable[index].chain;
        while (current->right != NULL) {
            current = current->right;
        }
        current->right = newNode;
    }
}
void generateNormalFile(int N) {
    FILE* file = fopen("normal.txt", "w");
    if (file == NULL) {
        printf("Dosya oluşturulamadi!");
        return;
    }  
    int letterCount = sizeof(letters) / sizeof(letters[0]); 
    srand(time(NULL));
    
    for (int i = 0; i < N; i++) {
        int randomIndex = rand() % letterCount;
        char randomLetter = letters[randomIndex];
        fputc(randomLetter, file);
    }
    
    fclose(file);
    printf("normal.txt dosyasi oluşturuldu.\n");
}


void createFrequencyTable() {
    HashNode hashTable[TABLE_SIZE];
    memset(hashTable, 0, sizeof(hashTable));
    FILE* file = fopen("normal.txt", "r");
    if (file == NULL) {
        printf("Dosya bulunamadi!");
        return;
    }
    
    int frequencyCount[TABLE_SIZE] = {0};
    
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        int index = hashFunction(ch);
        frequencyCount[index]++;
    }
    
    fclose(file);
    
    for (int i = 0; i < TABLE_SIZE; i++) {
        char letter = letters[i];
        int frequency = frequencyCount[i];
        addToHashTable(hashTable, letter, frequency);
    }
    
    printFrequencyTable(hashTable);
}
Node* createHuffmanTree(Node* nodes[], int size) {
    while (size > 1) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->letter = '\0';
        newNode->frequency = nodes[size - 2]->frequency + nodes[size - 1]->frequency;
        newNode->left = nodes[size - 2];
        newNode->right = nodes[size - 1];
        
        int insertIndex = size - 2;
        while (insertIndex > 0 && newNode->frequency < nodes[insertIndex - 1]->frequency) {
            nodes[insertIndex] = nodes[insertIndex - 1];
            insertIndex--;
        }
        
        nodes[insertIndex] = newNode;
        size--;
    }
    
    return nodes[0];
}
void buildHuffmanTree(HashNode* hashTable, Node* nodes[], int* size) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* node = createNode(hashTable[i].letter, hashTable[i].frequency);
        nodes[*size] = node;
        (*size)++;
    }
    
    while (*size < TABLE_SIZE) {
        nodes[*size] = createNode('\0', 0);
        (*size)++;
    }
    
    Node* root = createHuffmanTree(nodes, *size);
    
    char code[TABLE_SIZE];
    printf("Huffman agaci:\n");
    printf("-------------\n");
    printHuffmanTree(root, code, 0);
    
}

int main() {
    int N;
    printf("Toplam harf sayisini girin: ");
    scanf("%d", &N);
    
    generateNormalFile(N);
    createFrequencyTable();
    
    HashNode hashTable[TABLE_SIZE];
    memset(hashTable, 0, sizeof(hashTable));
    
    FILE* file = fopen("normal.txt", "r");
    if (file == NULL) {
        printf("Dosya bulunamadi!");
        return 0;
    }
    
    int frequencyCount[TABLE_SIZE] = {0};
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        int index = hashFunction(ch);
        frequencyCount[index]++;
    }
    
    fclose(file);
    
    for (int i = 0; i < TABLE_SIZE; i++) {
        char letter = letters[i];
        int frequency = frequencyCount[i];
        addToHashTable(hashTable, letter, frequency);
    }
    
    printFrequencyTable(hashTable);
    
    Node* nodes[TABLE_SIZE];
    int size = 0;
    
    buildHuffmanTree(hashTable, nodes, &size);
    
    return 0;
}
