#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>

#include "graph.hpp"

void addFiles(std::string filename, Graph &g2);
int main(int argc, char *argv[]) {
    std::string file_name = argv[1];
    
    Graph g2;
    addFiles(file_name,g2);
    g2.assignDistricts();
    g2.displayEdges();


    return 0;
}

void addFiles(std::string filename, Graph &g2) {
    std::ifstream file;
    file.open(filename);
    std::vector<std::string> cityNames;
    std::string line;
    std::string place;



    // int line_count = 0;
    // // vector of city names from first line in file
    // std::vector<std::string> cities;

    // std::ifstream file;
    // file.open(filename);
    // if(file.is_open()) {
    //     std::string line;
    //     while(getline(file,line)) {

    //         bool flag = false;
    //         int iterator = 0;

    //         std::stringstream ss(line);
    //         std::string inner_line;
            
    //         while(getline(ss, inner_line, ',')) {

    //             if(line_count == 0) {
    //                 cities.push_back(inner_line);
    //                 // skips the first string
    //                 if(flag) {
    //                     g2.addVertex(inner_line);
    //                 }
    //                 flag = true;
    //                 continue ;
    //             }

    //             else {
    //                 // skips the first string
    //                 if(iterator > 0) {
    //                     // if the edge is from the last element in vector (wrap around)
    //                     int temp_count = line_count + iterator;
    //                     int num = cities.size(); // 16 or 3 (small)
    //                     if(temp_count == num) {
    //                         temp_count = 1;
    //                         if(line_count == 1) {
    //                             temp_count++;
    //                         }
    //                     }
    //                     // inside to avoid invalid argument on string
    //                     if(stoi(inner_line) > 0) {
    //                         g2.addEdge(cities[line_count], cities[temp_count], stoi(inner_line));
    //                         std::cout << " ... Reading in " << cities[line_count] << " -- " << cities[temp_count] << " -- "     << inner_line << std::endl;
    //                     }
    //                 }
    //                 iterator++;
    //             }
    //         }
    //         line_count++;
    //     }
    // }
}


