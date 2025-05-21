#pragma once

#include <gtest/gtest.h>

#include "Utils.hpp"


using namespace std;


TEST(VertexTest, VertexNormalization)
{
	Vertex v = {0, {4.3, 5.0, 6.8}};
	Vertex v0 = normalizeVertex(v);
	double length = v0.coords.norm();
	ASSERT_NEAR(length, 1.0, numeric_limits<double>::epsilon());
}


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


TEST(PolyhedronTest, Barycenter)
{
	// build a face struct and manually compute barycenter
	// compare it with the implementation of the function
	//////////// DA COMPLETARE /////////
}


TEST(PolyhedronTest, VertexAddition)
{
	// Polyhedron P;
	// unsigned int id0 = addVertex(P, {0.0, 0.0, 1.0});
	// unsigned int id1 = addVertex(P, {0.0, 0.0, 1.0}); // duplicate
	// unsigned int id2 = addVertex(P, {0.1, 3.4, 1.0}); // not normalized
	// ASSERT_EQ(id0, 0);
	// ASSERT_EQ(id1, 0);
	// ASSERT_EQ(id2, 1);
	// ASSERT_EQ(P.numVertices(), 2); // id0, id2
	// Vertex v2 = P.vertices[1];
	// double length2 = sqrt(v2.x * v2.x + v2.y * v2.y + v2.z * v2.z);
	// ASSERT_NEAR(length2, 1.0, numeric_limits<double>::epsilon());
}

TEST(PolyhedronTest, EdgeAddition)
{
	// Polyhedron P;
	// unsigned int id0 = addVertex(P, 1.0, 0.0, 0.0); // id = 0
	// unsigned int id1 = addVertex(P, 0.0, 1.0, 0.0); // id = 1
	// unsigned int id2 = addVertex(P, 0.0, 0.0, 1.0); // id = 2
	// unsigned int e0 = addEdge(P, id0, id1); // edge valido
	// ASSERT_EQ(e0, 0);
	// ASSERT_EQ(P.numEdges(), 1); // e0
	// unsigned int e1 = addEdge(P, id0, id1); // duplicato (stesso ordine)
	// ASSERT_EQ(e1, 0);
	// unsigned int e2 = addEdge(P, id1, id0); // duplicato (ordine inverso)
	// ASSERT_EQ(e2, 0);
	// ASSERT_EQ(P.numEdges(), 1); // e0
	// unsigned int e3 = addEdge(P, id1, id2); // edge valido
	// ASSERT_EQ(e3, 1);
	// ASSERT_EQ(P.numEdges(), 2); // e0, e3
	// unsigned int e4 = addEdge(P, id0, id0); // edge non valido
	// ASSERT_EQ(e4, UINT_MAX);
	// /////////////// SISTEMARE IN BASE A COSA SI METTE IN addEdge() ///////////////////
	// ASSERT_EQ(P.numEdges(), 2); // e0, e3
}

/*
TEST(TriangleTest, ClassI)
{
	
}

TEST(TriangleTest, ClassII)
{
	
}
*/