#pragma once

#include <gtest/gtest.h>

#include "Utils.hpp"
#include "Graph.hpp"


using namespace std;



// Graph TEST

TEST(TestGraph, CreateGraph)
{
    // Create a tetrahedron to test the graph creation
	Polyhedron P = Tetrahedron();
	getEdgeNeighbors(P);
	getVertexNeighbors(P);

	// Create the graph
	Graph graph = createGraph(P);

	// Test the graph creation
	ASSERT_EQ(graph.adjacencyList.size(), P.numVertices());

	// Test the adjacency list for each vertex
	for(unsigned int i = 0; i < P.numVertices(); ++i)
	{
		ASSERT_EQ(graph.adjacencyList[i].size(), P.vertices[i].edgeNeighbors.size());

        sort(graph.adjacencyList[i].begin(), graph.adjacencyList[i].end());
	}

    ASSERT_EQ(graph.adjacencyList[0], vector<unsigned int>({1, 2, 3}));
    ASSERT_EQ(graph.adjacencyList[1], vector<unsigned int>({0, 2, 3}));
    ASSERT_EQ(graph.adjacencyList[2], vector<unsigned int>({0, 1, 3}));
    ASSERT_EQ(graph.adjacencyList[3], vector<unsigned int>({0, 1, 2}));

}

TEST(TestGraph, CreateWeightsMatrix)
{
    // Create tetrahedron
	Polyhedron P = Tetrahedron();
	getEdgeNeighbors(P);
	getVertexNeighbors(P);

	// Create the graph
	Graph graph = createGraph(P);

    MatrixXd weights = createWeights(graph, P);

    // Check if the matrix is symmetric
    for(unsigned int i = 0; i < weights.rows(); i++)
    {
        // Check if the matrix is symmetric
        for(unsigned int j = 0; j < weights.cols(); j++)
        {
            ASSERT_EQ(weights(i,j), weights(j,i)); 
        }

        // This tests the unweighted case
        ASSERT_EQ(weights(0,1), 1);
        ASSERT_EQ(weights(1,2), 1);
        ASSERT_EQ(weights(2,3), 1);
        ASSERT_EQ(weights(3,0), 1);
    }
    
}


TEST(TestGraph, Dijkstra_ShortestPath)
{
    // Create a simple polyhedron (octahedron)
    Polyhedron P = Octahedron();
    
    // Initialize edge and vertex neighbor relations
    getEdgeNeighbors(P);
    getVertexNeighbors(P);

    // Build graph and weight matrix
    Graph graph = createGraph(P);
    MatrixXd weights = createWeights(graph, P);

    // Define start and end nodes
    unsigned int id_path_start = 5;
    unsigned int id_path_end = 6;

    // Run Dijkstra algorithm
    vector<unsigned int> path = Dijkstra(graph, id_path_start, id_path_end, weights);

    // Expected path
    vector<unsigned int> expected_path = {5, 6};

    // Check total size of path
    ASSERT_EQ(path.size(), expected_path.size());

    // Check each individual node in the path
    for (size_t i = 0; i < path.size(); ++i) {
        EXPECT_EQ(path[i], expected_path[i]);
    }

}
