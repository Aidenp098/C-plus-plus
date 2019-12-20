#include "HashTable.hpp"
#include <iostream>
#include <sstream>
#include <fstream>


int main(int argc, char *argv[]) {
    // verify we have the correct # of parameters, else throw error msg & return
    if (argc != 5)    {
        std::cout << "Usage: ";
        std::cout << argv[0] << " <number of words> <filename.txt> <ignorefilename.txt> <size of hashtbl>";
        std::cout << std::endl;
        return 0;
    }

    HashTable ignore_table(STOPWORD_TABLE_SIZE);

    std::string str_num = argv[1]; // number of words for printtopN
    int num = stoi(str_num);

    std::string filename = argv[2]; // script file name

    char* stop_name = argv[3]; // stop words file name
    getStopWords(stop_name, ignore_table);

    std::string hash_size = argv[4];
    int hash_s = stoi(hash_size);

    HashTable uniqueWordsTable(hash_s);

    std::ifstream file;
    file.open(filename);

    if (file.is_open())
    {
        std::string line;
        while(file >> line)
        {
            if(!isStopWord(line, ignore_table)) {
                if(uniqueWordsTable.isInTable(line)) {
                    uniqueWordsTable.incrementCount(line);
                }
                else {
                    uniqueWordsTable.addWord(line);
                }
            }
        }
        uniqueWordsTable.printTopN(num);
        int col = uniqueWordsTable.getNumCollisions();
        int unique = uniqueWordsTable.getNumItems();
        int total = uniqueWordsTable.getTotalNumWords();
        std::cout << "#" << std::endl;
        std::cout << "Number of collisions: " << col << std::endl;
        std::cout << "#" << std::endl;
        std::cout << "Unique non-stop words: " << unique << std::endl;
        std::cout << "#" << std::endl;
        std::cout << "Total non-stop words: " << total << std::endl;
    }
    else
    {
        std::cout <<"fail" << std::endl;
    }
    file.close();
    return 0;
}

void getStopWords(char *ignoreWordFileName, HashTable &stopWordsTable) {
    std::ifstream file;
    file.open(ignoreWordFileName);

    std::string line;
    while(getline(file,line)) {
        stopWordsTable.addWord(line);
    }
    file.close();
}

bool isStopWord(std::string word, HashTable &stopWordsTable) {
    return stopWordsTable.isInTable(word);
}