#ifndef MOVIETREE_HPP
#define MOVIETREE_HPP

#include <string>

/* MovieNode: Node object to store in 
 * the binary search tree (BST). Each movie's 
 * info will be stored in one node. */
class MovieNode
{
  public:
    // instance variables
    int ranking;
    std::string title;
    int year;
    int quantity;
    MovieNode *leftChild;
    MovieNode *rightChild;

    // constructors
    MovieNode()
    {
        ranking = -1;
        year = 0;
        quantity = -1;
        leftChild = rightChild = nullptr;
    };
    MovieNode(int in_ranking, std::string in_title, int in_year, int in_quantity)
    {
        ranking = in_ranking;
        title = in_title;
        year = in_year;
        quantity = in_quantity;
        leftChild = rightChild = nullptr;
    }

};

/* MovieTree: Class implementing the BST:
 *  - You will implement the methods marked TODO.
 *  - Root of tree is pointed at by 'root' */
class MovieTree
{
  private:
    // instance var pointing to root node in tree
    MovieNode* root;
    MovieNode* searchHelper(MovieNode *node, std::string title);
    MovieNode* addHelper(MovieNode* node, std::string title);
    MovieNode* deleteMovieHelper(MovieNode* node, std::string title);
    int countHelper(MovieNode* node);
    MovieNode* getMinHelper(MovieNode* node);
    void printHelper(MovieNode* node);
    void DeleteAll(MovieNode* node);

  public:
    // Constructor (TODO)
    MovieTree();

    // Destructor (TODO)
    ~MovieTree();

    // Descr: see 'print the entire inventory'
    //    in the homework manual. (TODO)
    void printMovieInventory();

    // Descr: add movie to BST, at spot in tree
    //    alphabetically-sorted by title. (TODO)
    //  param rating: IMDB rating of movie
    //  param title: title of movie
    //  param releaseYear: release year of movie
    //  param quantity: # of copies available to rent
    void addMovieNode(int ranking, std::string title, int releaseYear, int quantity);

    // Descr: Search the BST for the given title and
    //    print that movie's info in the predefined 
    //    format. See 'Find a movie' in the manual. (TODO)
    //  param title: title of node to find
    void findMovie(std::string title);

    // Descr: update the inventory to indicate a movie
    //    has been rented and print predefined info.
    //    See 'Rent a movie' in the manual. (TODO)
    //  param title: title of node to rent
    void rentMovie(std::string title);

    void deleteMovie(std::string title);

    void countMovies();
};

#endif // MOVIETREE_HPP
