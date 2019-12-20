#include "MovieTree.hpp"
#include <iostream>

MovieTree::MovieTree() {
    root = nullptr;
}

MovieTree::~MovieTree() {
    DeleteAll(root);
}

void MovieTree::DeleteAll(MovieNode* node) {
    if(node == nullptr) {
        return ;
    }
    else {
        DeleteAll(node->leftChild);
        DeleteAll(node->rightChild);
        delete node;
    }
}

void MovieTree::printHelper(MovieNode* node) {
    if(node == nullptr) {
        return ;
    }
    else {
        printHelper(node->leftChild);
        std::cout << "Movie: " << node->title << " " << node->quantity << std::endl;
        printHelper(node->rightChild);
    }
}

void MovieTree::printMovieInventory() {
    if(root == nullptr) {
        return ;
    }
    printHelper(root);
}

MovieNode* MovieTree::searchHelper(MovieNode *node, std::string title) {
    if(node->title > title) {
        if(node->leftChild == nullptr) {
            return node;
        }
        return searchHelper(node->leftChild, title);
    }
    else if (node->title < title) {
        if(node->rightChild == nullptr) {
            return node;
        }
        return searchHelper(node->rightChild, title);
    }
    return node;
}

void MovieTree::addMovieNode(int ranking, std::string title, int releaseYear, int quantity) {
    MovieNode* newMovie = new MovieNode(ranking, title, releaseYear, quantity);
    if (root == nullptr) {
        root = newMovie;
        return ;
    }
    else {
        MovieNode* foundMovie = searchHelper(root,title);
        // if the title is smaller
        if(foundMovie->title > title) {
            if(foundMovie->leftChild == nullptr) {
                foundMovie->leftChild = newMovie;
            }
        }
        // if the title is bigger
        else if(foundMovie->title < title) {
            if(foundMovie->rightChild == nullptr) {
                foundMovie->rightChild = newMovie;
            }
        }
    }
}

void MovieTree::findMovie(std::string title) {
    // prevents a seg fault when calling searchHelper
    if(root == nullptr) {
        std::cout << "Movie not found." << std::endl;
        return ;
    }
    else {
        MovieNode *tempMovie = MovieTree::searchHelper(root,title);
        if(tempMovie->title != title) {
            std::cout << "Movie not found." << std::endl;
        }
        else {
            std::cout << "Movie " << "'"<< tempMovie->title <<"' Info:"<< std::endl;
            std::cout << "================================" << std::endl;
            std::cout << "Ranking : " << tempMovie->ranking << std::endl;
            std::cout << "Title   : " << tempMovie->title << std::endl;
            std::cout << "Year    : " << tempMovie->year << std::endl;
            std::cout << "Quantity: " << tempMovie->quantity << std::endl;
        }
    }
}

void MovieTree::rentMovie(std::string title) {
    // this is to prevent a seg fault when calling searchHelper with null
    if(root == nullptr) {
        std::cout << "Movie not found." << std::endl;
        return ;
    }
    else {
        MovieNode *tempMovie = MovieTree::searchHelper(root,title);
        if(tempMovie->title != title) {
            std::cout << "Movie not found." << std::endl;
            return ;
        }
        else if (tempMovie->quantity == 0) {
            std::cout << "Movie out of stock." << std::endl;
        }
        else {
            tempMovie->quantity--;
            std::cout << "Movie has been rented." << std::endl;
            std::cout << "Movie " << "'"<< tempMovie->title <<"' Info:"<< std::endl;
            std::cout << "================================" << std::endl;
            std::cout << "Ranking : " << tempMovie->ranking << std::endl;
            std::cout << "Title   : " << tempMovie->title << std::endl;
            std::cout << "Year    : " << tempMovie->year << std::endl;
            std::cout << "Quantity: " << tempMovie->quantity << std::endl;
            if (tempMovie->quantity == 0) {
                deleteMovie(title);
            }
        }
    }
}

MovieNode* MovieTree::getMinHelper(MovieNode* node) {
    if (node->leftChild == nullptr) {
        return node;
    }
    return getMinHelper(node->rightChild);
}

MovieNode* MovieTree::deleteMovieHelper(MovieNode* node, std::string title) {
    if (node == nullptr) {
        std::cout << "Movie doesn't exist." << std::endl;
    }
    else if (title > node->title) {
        node->rightChild = deleteMovieHelper(node->rightChild, title);
    }
    else if (title < node->title) {
        node->leftChild = deleteMovieHelper(node->leftChild, title);
    }
    else {
        if (node->leftChild == nullptr && node->rightChild == nullptr) {
            delete node;
            node = nullptr;
        }
        else if (node->rightChild == nullptr) {
            MovieNode* temp = node->leftChild;
            delete node;
            node = temp;
        }
        else if (node->leftChild == nullptr) {
            MovieNode* temp = node->rightChild;
            delete node;
            node = temp;
        }
        else {
            MovieNode* minValue = getMinHelper(node->rightChild);
            node->title = minValue->title;
            node->quantity = minValue->quantity;
            node->ranking = minValue->ranking;
            node->year = minValue->year;
            node->rightChild = deleteMovieHelper(node->rightChild, minValue->title);
        }
    }
    return node;
}


void MovieTree::deleteMovie(std::string title) {
    if (root == nullptr) {
        std::cout << "Movie not found." << std::endl;
        return ;
    }
    root = deleteMovieHelper(root, title);
}

int MovieTree::countHelper(MovieNode* node) {
    if(node == nullptr) {
        return 0;
    }
    return countHelper(node->leftChild) + countHelper(node->rightChild) + 1;
}

void MovieTree::countMovies() {
    std::cout << "Count = " << countHelper(root) << std::endl;
}