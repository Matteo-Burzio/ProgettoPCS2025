#pragma once

#include <gtest/gtest.h>
#include "Graph.hpp"
#include "Geometry.hpp"


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
	}

    ASSERT_EQ(graph.adjacencyList[0], vector<unsigned int>({1, 2, 3}));
    ASSERT_EQ(graph.adjacencyList[1], vector<unsigned int>({0, 2, 3}));
    ASSERT_EQ(graph.adjacencyList[2], vector<unsigned int>({0, 1, 3}));
    ASSERT_EQ(graph.adjacencyList[3], vector<unsigned int>({0, 1, 2}));

}

