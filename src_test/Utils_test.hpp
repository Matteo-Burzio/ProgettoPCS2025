#pragma once

#include <gtest/gtest.h>

#include "Utils.hpp"


using namespace std;


// Polyhedron TEST

TEST(PolyhedronTest, ValidTetrahedron)
{
	Polyhedron P = Tetrahedron();
	ASSERT_TRUE(P.checkFaces());
}


TEST(PolyhedronTest, ValidOctahedron)
{
	Polyhedron P = Octahedron();
	ASSERT_TRUE(P.checkFaces());
}


TEST(PolyhedronTest, ValidIcosahedron)
{
	Polyhedron P = Icosahedron();
	ASSERT_TRUE(P.checkFaces());
}


// Export TEST

TEST(ExportTest, ExportParaview)
{
	
}


// Geometry TEST

TEST(GeometryTest, VertexNormalization)
{
	// Create a vertex 
	Vertex v = {0, {4.3, 5.0, 6.8}};

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
	Vertex v0 = {0, {0, 0, 0}};
	Vertex v1 = {1, {1, 0, 0}};
	Vertex v2 = {2, {0, 1, 0}};

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


TEST(GeometryTest, DualComputation)
{
	
}



// Triangle TEST

TEST(TriangleTest, VertexCheck)
{
	// Create a polyhedron object
	Polyhedron P;
	
	// Create a vertex object ad add it to the polyhedron
	Vertex v0 = {0, {1,2,3}};
	P.vertices.push_back(v0);

	// Compare the vertex with a duplicate
	Vertex v1 = {0, {1,2,3}};
	ASSERT_FALSE(checkVertex(P, v1));

	// Compare the vertex with a near duplicate
	Vertex v2 = {0, {1 + numeric_limits<double>::epsilon(),
					 2 + numeric_limits<double>::epsilon(),
					 3 + numeric_limits<double>::epsilon()}};
	ASSERT_FALSE(checkVertex(P, v2));

	// Compare the vertex with a different one
	Vertex v3 = {0, {4,5,6}};
	ASSERT_TRUE(checkVertex(P, v3));
}


TEST(TriangleTest, VertexAddition)
{
	// Create a polyhedron object
	Polyhedron P;
	
	// Create a vertex object
	Vertex v;
	v.coords = {1,2,3};

	// Add the vertex to the polyhedron
	addVertex(P, v);

	// Check that the vertex has been added
	ASSERT_EQ(P.numVertices(), 1);

	// Check that the ID is the correct value
	ASSERT_EQ(v.id, 0);
	ASSERT_EQ(P.vertices[0].id, 0);

	// Check if the added vertex is the correct one
	ASSERT_TRUE(P.vertices[0].coords.isApprox(v.coords));
}


TEST(TriangleTest, VertexResearch)
{
	// Create a polyhedron object
	Polyhedron P;
	
	// Create a vertex object
	Vertex v = {0, {1,2,3}};

	// Add the vertex to the polyhedron
	addVertex(P, v);

	// Check that the function return the correct ID
	ASSERT_EQ(P.vertices[0].id, 0);
}


TEST(TriangleTest, EdgeCheck)
{
	// Create a polyhedron with 3 vertices
	Polyhedron P;
	P.vertices = {{0, {0,0,1}}, {1, {1,0,0}}, {2, {0,1,0}}};

	// Create ad edge object and add it to the polyhedron
	Edge e0 = {0,0,1};
	P.edges = {e0};

	// Try to add an edge connected to a non-existing vertex
	Edge e1 = {0,2,3};
	ASSERT_FALSE(checkEdge(P, e1));

	// Try to add a duplicate edge (same order)
	Edge e2 = {0,0,1};
	ASSERT_FALSE(checkEdge(P, e2));

	// Try to add a duplicate edge (different order)
	Edge e3 = {0,1,0};
	ASSERT_FALSE(checkEdge(P, e3));

	// Try to add a different edge
	Edge e4 = {0,1,2};
	ASSERT_TRUE(checkEdge(P, e4));
}


TEST(TriangleTest, EdgeAddition)
{
	// Create a polyhedron object with 2 vertices
	Polyhedron P;
	P.vertices = {{0, {0,0,1}}, {1, {1,0,0}}};

	// Create an edge object
	Edge e = {0,0,1};
	
	// Add the edge to the polyhedron
	addEdge(P, e);
	
	// Check that the edge has been added
	ASSERT_EQ(P.numEdges(), 1);
	
	// Check that the ID is the correct value
	ASSERT_EQ(e.id, 0);
	ASSERT_EQ(P.edges[0].id, 0);
	
	// Check if the added edge is the correct one
	ASSERT_EQ(P.edges[0].origin, e.origin);
	ASSERT_EQ(P.edges[0].end, e.end);
}


TEST(TriangleTest, FaceCheck)
{
	// Create a polyhedron object
	Polyhedron P;
	
	// Create a face object and add it to the polyhedron
	Face f0;
	f0.idVertices = {0, 1, 2};
	P.faces.push_back(f0);
	
	// Try to add a duplicate face (different order)
	Face f1;
	f1.idVertices = {2, 0, 1};
	ASSERT_FALSE(checkFace(P, f1));

	// Try to add a different face
	Face f2;
	f2.idVertices = {3,4,5};
	ASSERT_TRUE(checkFace(P, f2));
}


TEST(TriangleTest, FaceAddition)
{
	
}


TEST(TriangleTest, ClassI)
{
	
}


TEST(TriangleTest, ClassII)
{
	
}