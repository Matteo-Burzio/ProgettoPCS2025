#pragma once

#include "Polyhedron.hpp"

// Graph struct containing the adjacency matrix
struct Graph
{
    vector<list<unsigned int>> adjacencyList;
};


// Function which creates the graph 
Graph createGraph(const Polyhedron& pol);

// Function which creates the weights matrix
MatrixXi createWeights(const Graph& graph, const Polyhedron& pol);

// Function which finds the shortest path using Diskstra's algorithm
vector<unsigned int> Dijkstra(const Graph& graph,
                                    unsigned int id_path_start,
                                    unsigned int id_path_end,
                                    MatrixXi weights);


