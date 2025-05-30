#pragma once

#include <gtest/gtest.h>

#include "Geometry.hpp"


using namespace std;



// Geometry TEST

TEST(GeometryTest, VertexNormalization)
{
	// Create a vertex 
	Vertex v = {0, {4.3, 5.0, 6.8}, {0,0,0}, {0,0,0}};

	// Normalize the vertex
	normalizeVertex(v);

	// Check that the function worked correctly
	double length = v.coords.norm();
	ASSERT_NEAR(length, 1.0, numeric_limits<double>::epsilon());
}


TEST(GeometryTest, BarycenterComputation)
{
	// Create a polyhedron object
	Polyhedron P;
	Vertex v0 = {0, {0, 0, 0}, {0,0,0}, {0,0,0}};
	Vertex v1 = {1, {1, 0, 0}, {0,0,0}, {0,0,0}};
	Vertex v2 = {2, {0, 1, 0}, {0,0,0}, {0,0,0}};

	P.vertices.push_back(v0);
	P.vertices.push_back(v1);
	P.vertices.push_back(v2);

	Face f;
	f.id = 0;
	f.idVertices = {0, 1, 2};
	P.faces.push_back(f);

	// Compute the barycenter and check if it's corrrect
	Vertex bc = Barycenter(P, 0);
	Vector3d expected = {1.0/3.0, 1.0/3.0, 0};
	ASSERT_TRUE(bc.coords.isApprox(expected, numeric_limits<double>::epsilon()));
}


// DualTest

TEST(DualTest, NeighborsComputation)
{
	// Create a tetrahedron
	Polyhedron P = Tetrahedron();

	// Get vertex neighbors
	getVertexNeighbors(P);

	// Test vertex 0's neighbors
	ASSERT_EQ(P.vertices[0].edgeNeighbors, vector<unsigned int>({0, 2, 3}));
	ASSERT_EQ(P.vertices[0].faceNeighbors, vector<unsigned int>({0, 1, 2}));

	// Test vertex 1's neighbors
	ASSERT_EQ(P.vertices[1].edgeNeighbors, vector<unsigned int>({0, 1, 4}));
	ASSERT_EQ(P.vertices[1].faceNeighbors, vector<unsigned int>({0, 2, 3}));

	// Test vertex 2's neighbors
	ASSERT_EQ(P.vertices[2].edgeNeighbors, vector<unsigned int>({1, 2, 5}));
	ASSERT_EQ(P.vertices[2].faceNeighbors, vector<unsigned int>({0, 1, 3}));

	// Test vertex 3's neighbors
	ASSERT_EQ(P.vertices[3].edgeNeighbors, vector<unsigned int>({3, 4, 5}));
	ASSERT_EQ(P.vertices[3].faceNeighbors, vector<unsigned int>({1, 2, 3}));
}


TEST(DualTest, EdgeNeighborsComputation)
{
	// Create a polyhedron
	Polyhedron P = Tetrahedron();

	// Get vertex neighbors
	getVertexNeighbors(P);
	getEdgeNeighbors(P);

	// Test edge neighbors
	for (const auto& e : P.edges)
	{
		ASSERT_EQ(e.faceNeighbors.size(), 2);
	}
}


TEST(DualTest, DualComputation)
{
	// Create a polyhedron object
	Polyhedron P = Tetrahedron();
	getVertexNeighbors(P);
	getEdgeNeighbors(P);
	
	// Compute the dual (tetrahedron)
	Polyhedron Q = Dual(P);

	// Check the number of vertices, edges and faces
	ASSERT_EQ(Q.numVertices(), P.numFaces());
	ASSERT_EQ(Q.numEdges(), P.numEdges());
	ASSERT_EQ(Q.numFaces(), P.numVertices());

	// Check that the vertices are normalized
	for (const auto& v : Q.vertices)
	{
		double length = v.coords.norm();
		ASSERT_NEAR(length, 1.0, numeric_limits<double>::epsilon());
	}

	// Check the number of vertices and edges in a face
	for (const auto& f : Q.faces)
	{
		ASSERT_EQ(f.idVertices.size(), 3);
		ASSERT_EQ(f.idEdges.size(), 3);
	}
}
