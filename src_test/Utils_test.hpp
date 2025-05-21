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
	Vertex v = {0, {4.3, 5.0, 6.8}};
	Vertex v0 = normalizeVertex(v);
	double length = v0.coords.norm();
	ASSERT_NEAR(length, 1.0, numeric_limits<double>::epsilon());
}


TEST(GeometryTest, BarycenterComputation)
{
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
	Polyhedron P;
	Vertex v0 = {0, {1,2,3}};
	P.vertices.push_back(v0);
	Vertex v1 = {0, {1,2,3}}; // exact duplicate
	ASSERT_FALSE(checkVertex(P, v1));
	Vertex v2 = {0, {1 + numeric_limits<double>::epsilon(),
					 2 + numeric_limits<double>::epsilon(),
					 3 + numeric_limits<double>::epsilon()}}; // near duplicate
	ASSERT_FALSE(checkVertex(P, v2));
	Vertex v3 = {0, {4,5,6}}; // different
	ASSERT_TRUE(checkVertex(P, v3));
}


TEST(TriangleTest, VertexAddition)
{
	Polyhedron P;
	Vertex v;
	v.coords = {1,2,3};
	addVertex(P, v);
	ASSERT_EQ(P.numVertices(), 1); // add vertex
	ASSERT_EQ(v.id, 0);
	ASSERT_EQ(P.vertices[0].id, 0); // correct id
	ASSERT_TRUE(P.vertices[0].coords.isApprox(v.coords));
}


TEST(TriangleTest, EdgeCheck)
{
	Polyhedron P;
	P.vertices = {{0, {0,0,1}}, {1, {1,0,0}}, {2, {0,1,0}}}; // 3 vertices
	Edge e0 = {0,0,1};
	P.edges = {e0}; // 1 edge
	Edge e1 = {0,2,3}; // non existing vertex
	ASSERT_FALSE(checkEdge(P, e1));
	Edge e2 = {0,0,1}; // duplicate (same order)
	ASSERT_FALSE(checkEdge(P, e2));
	Edge e3 = {0,1,0}; // duplicate (different order)
	ASSERT_FALSE(checkEdge(P, e3));
	Edge e4 = {0,1,2}; // different edge
	ASSERT_TRUE(checkEdge(P, e4));
}


TEST(TriangleTest, EdgeAddition)
{
	Polyhedron P;
	P.vertices = {{0, {0,0,1}}, {1, {1,0,0}}}; // 2 vertices
	Edge e0 = {0,0,1}; // valid edge
	addEdge(P, e0);
	ASSERT_EQ(P.numEdges(), 1); // add edge
	ASSERT_EQ(e0.id, 0);
	ASSERT_EQ(P.edges[0].id, 0); // correct id
	ASSERT_EQ(P.edges[0].origin, e0.origin); // correct origin
	ASSERT_EQ(P.edges[0].end, e0.end); // correct end
}


TEST(TriangleTest, ClassI)
{
	
}


TEST(TriangleTest, ClassII)
{
	
}