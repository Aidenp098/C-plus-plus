// ==========================================
// Created: September 20, 2018
// @Aiden Prohaska
//
// Description: Counts unique words in a file
// outputs the top N most common words
// ==========================================

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// struct to store word + count combinations
struct wordItem
{
    string word;
    int count;
};

/*
* Function name: getStopWords
* Purpose: read stop word list from file and store into vector
* @param ignoreWordFile - filename (the file storing ignore/stop words)
* @param _vecIgnoreWords - store ignore words from the file (pass by reference)
* @return - none
* Note: The number of words is fixed to 50
*/
void getStopWords(const char *ignoreWordFileName, vector<string> &_vecIgnoreWords);


/*
* Function name: isStopWord
* Purpose: to see if a word is a stop word
* @param word - a word (which you want to check if it is a stop word)
* @param _vecIgnoreWords - the vector type of string storing ignore/stop words
* @return - true (if word is a stop word), or false (otherwise)
*/
bool isStopWord(string word, vector<string> &_vecIgnoreWords);

/*
* Function name: getTotalNumberNonStopWords
* Purpose: compute the total number of words saved in the words array (including repeated words)
* @param list - an array of wordItems containing non-stopwords
* @param length - the length of the words array
* @return - the total number of words in the words array (including repeated words multiple times)
*/
int getTotalNumberNonStopWords(wordItem list[], int length);

/*
* Function name: arraySort
* Purpose: sort an array of wordItems, decreasing, by their count fields
* @param list - an array of wordItems to be sorted
* @param length - the length of the words array
*/
void arraySort(wordItem list[], int length);

/**
* Function name: printTopN
* Purpose: to print the top N high frequency words
* @param wordItemList - a pointer that points to a *sorted* array of wordItems
* @param topN - the number of top frequency words to print
* @return none
*/
void printTopN(wordItem wordItemList[], int topN);

const int STOPWORD_LIST_SIZE = 50;

const int INITIAL_ARRAY_SIZE = 100;


// ./a.out 10 HW2-HungerGames_edit.txt HW2-ignoreWords.txt
int main(int argc, char *argv[])
{
    vector<string> vecIgnoreWords(STOPWORD_LIST_SIZE);

    // verify we have the correct # of parameters, else throw error msg & return
    if (argc != 4)    {
        cout << "Usage: ";
        cout << argv[0] << " <number of words> <filename.txt> <ignorefilename.txt>";
        cout << endl;
        return 0;
    }

    int doubles = 0;
    int unique = 0;


    int capacity = 100;
    wordItem *word_structs;
    word_structs = new wordItem[capacity];

    string str_num = argv[1];
    int num = stoi(str_num);
    string filename = argv[2];

    const char* stop_name = argv[3];
    getStopWords(stop_name, vecIgnoreWords);

    ifstream file;
    file.open(argv[2]);

    if (file.is_open())
    {
        string line;
        while(getline(file,line))
        {
            string line2 = "Hello";
            stringstream ss(line);
            while (getline(ss,line2,' '))
            {
                bool stopword = false;
                int vec = vecIgnoreWords.size();
                for (int i = 0; i < vec;i++)
                {
                    if(line2 != vecIgnoreWords[i])
                    {
                        stopword = false;
                    }
                    else
                    {
                        stopword = true;
                        break;
                    }
                }
                if (stopword == false)
                {
                    if (unique == 0)
                    {
                        wordItem s1;
                        s1.word = line2;
                        s1.count = 1;
                        word_structs[0] = s1;
                        unique++;
                    }
                    else
                    {
                        bool find = false;
                        for (int j = 0; j < unique; j++)
                        {
                            // cout << j << endl;
                            // cout << unique << endl;
                            if (line2 == word_structs[j].word)
                            {
                                word_structs[j].count++;
                                find = true;
                                break;
                            }
                        }
                        if(unique == capacity)
                        {
                            capacity = capacity*2;
                            doubles++;
                            wordItem *newarray;
                            newarray = new wordItem[capacity];
                            for(int a = 0; a < unique;a++)
                            {
                                newarray[a] = word_structs[a];
                            }
                            delete [] word_structs;
                            word_structs = newarray;
                        }
                        if (find == false)
                        {
                            wordItem s1;
                            word_structs[unique] = s1;
                            word_structs[unique].word = line2;
                            word_structs[unique].count = 1;
                            unique++;
                        }

                    }
                }
            }
        }
        arraySort(word_structs,unique);
        printTopN(word_structs,num);
        int total = getTotalNumberNonStopWords(word_structs,unique);
        cout << "#" << endl;
        cout << "Array doubled: " << doubles << endl;
        cout << "#" << endl;
        cout << "Unique non-stop words: " << unique << endl;
        cout << "#" << endl;
        cout << "Total non-stop words: " << total << endl;
        // for (int l = 0; l < unique;l++)
        // {
        //     cout << word_structs[l].count << endl;
        // }
        // cout << doubles << endl;
    }
    else
    {
        cout <<"fail" <<endl;
    }
    file.close();
    /* **********************************
    1. Implement your code here.

    Read words from the file passed in on the command line, store and
    count the words.

    2. Implement the six functions after the main() function separately.
    ********************************** */

    return 0;
}




// This worked with getStopWords!!!!!
// int main()
// {
//     const char *ignoreWordFileName = "HW2-stopwords.txt";
//     vector<string> _vecIgnoreWords;
//     getStopWords(ignoreWordFileName, _vecIgnoreWords);

//     for (int i = 0; i < 100; i++)
//     {
//         cout << _vecIgnoreWords[i] << endl;
//     }
//     return 0;
// }
void getStopWords(const char *ignoreWordFileName, vector<string> &_vecIgnoreWords)
{
  ifstream file;
  file.open(ignoreWordFileName);

  string line;
  while(getline(file, line))
  {
      _vecIgnoreWords.push_back(line);
  }
  file.close();
}

// to test the isStopWord function!!!!!!
// int main()
// {
//     const char *ignoreWordFileName = "HW2-stopwords.txt";
//     vector<string> _vecIgnoreWords;
//     getStopWords(ignoreWordFileName, _vecIgnoreWords);

//     string x = "me";
//     bool y = isStopWord(x, _vecIgnoreWords);
//     cout << y;
//     return 0;
// }
bool isStopWord(string word, vector<string> &_vecIgnoreWords)
{
    int _vec = _vecIgnoreWords.size();
    for (int i = 0; i < _vec; i++)
    {
        if (_vecIgnoreWords[i] == word)
        {
            return true;
        }
        if (i == _vec)
        {
            return false;
        }
    }
    return false;
}

int getTotalNumberNonStopWords(wordItem list[], int length)
{
    int count = 0;
    for (int i = 0; i < length; i++)
    {
        if (list[i].word.length() > 0)
        {
            count += list[i].count;
        }
    }
    return count;
}


// my bubble sort from CSCI1300 lab
void arraySort(wordItem list[], int length)
{
    wordItem temp;
    int comp = 0;

    for (int x = length; x>0; x--)
    {
        bool flag = true;
        for(int y =0; y<x-1; y++)
        {
            comp=comp+1;
            if (list[y].count < list[y+1].count)
            {

                flag = false;

                temp = list[y+1];

                list[y+1]=list[y];
                list[y]=temp;
            }
        }
        if (flag==true)
        {
            break;
        }
    }
}

void printTopN(wordItem wordItemList[], int topN)
{
    for (int i = 0; i < topN; i++)
    {
        cout << wordItemList[i].count << " - " << wordItemList[i].word << endl;
    }
}