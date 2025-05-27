#pragma once

#include "Polyhedron.hpp"
#include "UCDUtilities.hpp"

using namespace std;

///// Utils.cpp /////

//Function that check if values of input are correct (Utils.cpp)
bool check_input(int argc, char* argv[],
				 unsigned int &p, unsigned int &q,
				 unsigned int &b, unsigned int &c,
				 unsigned int &val, unsigned int &flag);

// Functions that create tetrahedron, octahedron and icosahedron (Utils.cpp)
Polyhedron Tetrahedron();
Polyhedron Octahedron();
Polyhedron Icosahedron();

// Function that exports the polyhedron for Paraview (Utils.cpp)
void exportPolyhedron(const Polyhedron& P);


///// Geometry.cpp /////

// Function that normalizes the vertices (Geometry.cpp)
void normalizeVertex(Vertex& v);

// Function which computes the barycenter of a face (Geometry.cpp)
Vertex Barycenter(const Polyhedron& P, const unsigned int& f_id);

// Function that creates the dual of the polyhedron (Geometry.cpp)
Polyhedron Dual(const Polyhedron& P);


///// Triangle.cpp /////

// Functions that checks if the new vertex already exists (Triangle.cpp)
unsigned int addVertexIfMissing(Polyhedron& P, const Vector3d coords_V);

// Functions that check if the new edge already exists and add it to P(Triangle.cpp)
unsigned int addEdgeIfMissing(Polyhedron& P, unsigned int id1, unsigned int id2);

// Functions for Class I and Class II triangulation of a polyhedron (Triangle.cpp)
Polyhedron TriangleClassI(const Polyhedron& P_old, const unsigned int& val);
//Polyhedron TriangleClassII(const Polyhedron& P_old, const unsigned int& val);
