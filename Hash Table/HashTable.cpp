#include "HashTable.hpp"
#include <iostream>

HashTable::HashTable(int size) {
    hashTableSize = size;
    hashTable = new wordItem*[size];
    for (int i = 0; i < size; i++) {
        hashTable[i] = nullptr;
    }
    numItems = 0;
    numCollisions = 0;
}

HashTable::~HashTable() {
    wordItem* temp;
    wordItem* temp_next;
    for(int x = 0; x < hashTableSize; x++) {
        temp = hashTable[x];
        while(temp) {
            temp_next = temp->next;
            delete temp;
            temp = temp_next;
        }
    } 
    delete[] hashTable;
}

wordItem* makeNode(std::string word, wordItem* next, int count) {
    wordItem* ptr = new wordItem;
    ptr->next = next;
    ptr->word = word;
    ptr->count = count;
    return ptr;
}

unsigned int HashTable::getHash(std::string str) {
    unsigned int hashValue = 5381;

    int len = str.length();
    for (int i = 0; i < len; i++) {
        hashValue = (hashValue*33) + str[i];
    }
    return hashValue%hashTableSize;
}

wordItem* HashTable::searchTable(std::string str) {
    unsigned int idx = getHash(str);

    wordItem* wordptr = hashTable[idx];
    while(wordptr) {
        if (wordptr->word == str) {
            return wordptr;
        }
        wordptr = wordptr->next;
    }
    return nullptr;
}

void HashTable::addWord(std::string word) {
    if(!searchTable(word)) {
        unsigned int inx = getHash(word);
        wordItem* w_item = makeNode(word, nullptr, 1);

        // if LL not empty
        if(hashTable[inx]) {
            w_item->next = hashTable[inx];
            hashTable[inx] = w_item;
            numItems++;
            numCollisions++;
        }
        // if LL empty
        else {
            hashTable[inx] = w_item;
            numItems++;
        }
    }
    else {
        std::cout << "Duplicate key." << std::endl;
    }
}

bool HashTable::isInTable(std::string word) {
    if(searchTable(word) == nullptr) {
        return false;
    }
    else {
        return true;
    }
}

void HashTable::incrementCount(std::string word) {
    wordItem* ptr = searchTable(word);
    // if the word exists
    if(ptr != nullptr) {
        ptr->count++;
    }
}

int HashTable::getTotalNumWords() {
    int count = 0;
    for (int i = 0; i < hashTableSize; i++) {
        wordItem* temp = hashTable[i];
        while(temp) {
            count += temp->count;
            temp = temp->next;
        }
    }
    return count;
}

int HashTable::getNumCollisions() {
    return numCollisions;
}

int HashTable::getNumItems() {
    return numItems;
}

void HashTable::printTopN(int num) {
    wordItem* arr[num];
    for(int index = 0; index < num; index++) {
        wordItem* max;
        int max_n = -999999999;
        for(int j = 0; j < hashTableSize; j++) {
            wordItem* temp = hashTable[j];
            while(temp && index != num) {
                if(index == 0 && temp->count > max_n) {
                    max = temp;
                    max_n = temp->count;
                }
                else if(index > 0 && temp->count >= max_n && temp->count < arr[index-1]->count) {
                    max = temp;
                    max_n = temp->count;
                }
                temp = temp->next;
            }
        }
        arr[index] = max;
    }

    for(int i = 0; i < num; i++) {
        std::cout << arr[i]->count << " - " << arr[i]->word << std::endl;
    }
}