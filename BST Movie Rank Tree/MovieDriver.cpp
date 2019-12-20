#include "MovieTree.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>


void makeTree(std::string filename, MovieTree* node);
int main(int argc, char *argv[])
{
    
    bool quit = false;
    MovieTree* tree = new MovieTree;
    makeTree(argv[1], tree);
    
    while(quit == false)
    {
        int choice;
        std::string title;
    
    
        std::cout << "======Main Menu======" << std::endl;
        std::cout << "1. Find a movie" << std::endl;
        std::cout << "2. Rent a movie" << std::endl;
        std::cout << "3. Print the inventory" << std::endl;
        std::cout << "4. Delete a movie" << std::endl;
        std::cout << "5. Count movies" << std::endl;
        std::cout << "6. Quit" << std::endl;
    
        std::cin >> choice;
        // to be able to make use of getline
        std::cin.ignore();
    
        if(choice == 1)
        {
            std::cout << "Enter title:" << std::endl;
            getline(std::cin, title);
            tree->findMovie(title);
        }
        else if (choice == 2)
        {
            std::cout << "Enter title:" << std::endl;
            getline(std::cin,title);
            tree->rentMovie(title);
        }
        else if (choice == 3)
        {
            tree->printMovieInventory();
        }
        else if (choice == 4)
        {
            std::cout << "Enter title:" << std::endl;
            getline(std::cin,title);
            tree->deleteMovie(title);
        }
        else if (choice == 5)
        {
            tree->countMovies();
        }
        else if (choice == 6) 
        {
            std::cout << "Goodbye!" << std::endl;
            quit = true;
            break;
        }
    }
}


void makeTree(std::string filename, MovieTree* node)
{
    std::ifstream file;
    file.open(filename);
    
    std::string line;
    if(file.fail())
    {
       std::cout << "Failed" <<std::endl;
    }
    else
    {
        while(getline(file,line))
        {
            int count = 0;
            
            
            int rating; 
            std::string title;
            int year;
            int stock;
            std::stringstream ss(line);
            std::string inner_line;
            while(getline(ss,inner_line,','))
            {
                if (count == 0)
                {
                    rating = stoi(inner_line);
                }
                else if(count == 1)
                {
                    title = inner_line;
                }
                else if(count == 2)
                {
                    year = stoi(inner_line);
                }
                else if(count == 3)
                {
                    stock = stoi(inner_line);
                }
                count++;
            }
            node->addMovieNode(rating,title,year,stock);
            
        }
    }
}