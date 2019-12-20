#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>

#include "graph.hpp"
Graph::Graph() {
    // dont need these
}

Graph::~Graph() {
    // dont need these
}

vertex* Graph::findVertex(std::string name) {
    int num = vertices.size();
    for(int i = 0; i < num; i++) {
    
    
        if(vertices[i].name == name) {
            return &vertices[i];
        }
    }
    return nullptr;
}

void Graph::addVertex(std::string name) {
    // make vertex
    vertex v1;
    v1.ID = -1;
    v1.name = name;
    v1.district = -1;
    v1.visited = false;

    vertices.push_back(v1);
}

void Graph::addEdge(std::string v1, std::string v2, int distance) {
    vertex* curr = findVertex(v1);
    vertex* ad = findVertex(v2);

    // create adjacent vertex
    adjVertex adj_v;
    adj_v.v = ad;
    adj_v.distance = distance;

    curr->adj.push_back(adj_v);
}

void Graph::assignDistricts() {
    std::queue<vertex*> sp;
    int poll = 0;
    
    
    // size
    int size = vertices.size();
    for(int i = 0; i < size; i++) {
        if(vertices[i].district < 0) {
            sp.push(&vertices[i]);
            poll++;
            
            
            while(!sp.empty()) {
                vertex* node = sp.front();
                node->district = poll;
                sp.pop();
                
                
                // s
                int s = node->adj.size();
                for(int k = 0; k < s; k++) {
                
                
                    // n
                    int n = node->adj[k].v->district;
                    if(n < 0) {
                        sp.push(node->adj[k].v);
                    }
                }
            }
        }
    }
}

void Graph::displayEdges() {
    // num
    int num = vertices.size();
    for(int k = 0; k < num; k++) {
        std::cout << vertices[k].district;
        std::cout<< ":" << vertices[k].name << "-->";
        
        
        // n
        int n = vertices[k].adj.size();
        for(int i = 0; i < n; i++) {
            std::cout << vertices[k].adj[i].v->name;
            std::cout << " (" << vertices[k].adj[i].distance << " miles)";
            
            
            // m
            int m = vertices[k].adj.size();
            if(i != m-1) {
                std::cout << "***";
                // continue to skip the endl, just formatting
                continue ;
            }
            std::cout << std::endl;
        }
    }
}