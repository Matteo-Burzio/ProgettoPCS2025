#pragma once

#include "Polyhedron.hpp"

// Graph struct containing the adjacency matrix
struct Graph
{
    vector<list<unsigned int>> adjacencyList;
};


// Function which creates the graph 
Graph createGraph(const Polyhedron& pol);


