#pragma once

#include <gtest/gtest.h>

#include "Utils.hpp"


using namespace std;



// Input TEST

TEST(InputTest, InputCheck)
{
	
}


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

TEST(TriangleTest, VertexAddition)
{
	// Create a polyhedron object
	Polyhedron P;
	
	// Add a vertex
	Vector3d v0_coords = {1,2,3};
	unsigned int id0 = addVertexIfMissing(P, v0_coords);
	ASSERT_EQ(id0, 0);
	ASSERT_EQ(P.numVertices(), 1);
	
	// Add a near duplicate
	Vector3d v1_coords = {1 + numeric_limits<double>::epsilon(),
						  2 + numeric_limits<double>::epsilon(),
						  3 + numeric_limits<double>::epsilon()};
	unsigned int id1 = addVertexIfMissing(P, v1_coords);
	ASSERT_EQ(id1, 0);
	ASSERT_EQ(P.numVertices(), 1);
	
	// Add a different vertex
	Vector3d v2_coords = {4,5,6};
	unsigned int id2 = addVertexIfMissing(P, v2_coords);
	ASSERT_EQ(id2, 1);
	ASSERT_EQ(P.numVertices(), 2);
}


TEST(TriangleTest, EdgeAddition)
{
	// Create a polyhedron with 3 vertices
	Polyhedron P;
	P.vertices = {{0, {0,0,0}}, {1, {1,0,0}}, {2, {0,1,0}}};

	// Add a valid edge
	unsigned int id0 = addEdgeIfMissing(P, 0, 1);
	ASSERT_EQ(id0, 0);
	ASSERT_EQ(P.numEdges(), 1);
	
	// Add a duplicate (different order)
	unsigned int id1 = addEdgeIfMissing(P, 1, 0);
	ASSERT_EQ(id1, 0);
	ASSERT_EQ(P.numEdges(), 1);
	
	// Add invalid edges
	unsigned int id2 = addEdgeIfMissing(P, 1, 1);
	unsigned int id3 = addEdgeIfMissing(P, 1, 4);
	ASSERT_EQ(id2, static_cast<unsigned int>(-1)); // quello che esce se metto -1 a un unsigned int
	ASSERT_EQ(id3, static_cast<unsigned int>(-1)); // quello che esce se metto -1 a un unsigned int
	ASSERT_EQ(P.numEdges(), 1);
	
	// Add a different edge
	unsigned int id4 = addEdgeIfMissing(P, 1, 2);
	ASSERT_EQ(id4, 1);
	ASSERT_EQ(P.numEdges(), 2);
}


TEST(TriangleTest, ClassI)
{
	// Create a tetrahedron and perform Class I Triangulation
	Polyhedron P_old = Tetrahedron();

	// Perform Class I triangulation with val = 2
	Polyhedron P = TriangleClassI(P_old, 2);

	// We expect 10 vertices, 24 edges and 16 faces
	ASSERT_EQ(P.numVertices(), 10);
	ASSERT_EQ(P.numEdges(), 24);
	ASSERT_EQ(P.numFaces(), 16);

	// Check that all faces have 3 vertices and 3 edges
	for (const auto& f : P.faces)
	{
		ASSERT_EQ(f.idVertices.size(), 3);
		ASSERT_EQ(f.idEdges.size(), 3);
	}

	// Check that there are no invalid edges
	for (const auto& e : P.edges)
	{
		ASSERT_NE(e.origin, e.end);            // NE = Not Equal
		ASSERT_LT(e.origin, P.numVertices());  // LT = Less Than
		ASSERT_LT(e.end, P.numVertices());
	}
}


TEST(TriangleTest, ClassII)
{
	
}

