#pragma once
#include "Eigen/Eigen"
#include <iostream>
#include <sstream>
#include <limits>

#include "Polyhedron.hpp"

using namespace std;


namespace PolyhedralLibrary {

// Functions that create tetrahedron, octahedron and icosahedron (Utils.cpp)
Polyhedron Tetrahedron();
Polyhedron Octahedron();
Polyhedron Icosahedron();


// Function that normalizes the vertices (Utils.cpp)
Vertex normalizeVertex(const Vertex& v);

// Function which computes the barycenter of a face
Vertex Barycenter(const Polyhedron& P, const unsigned int& f_id);

// Function that exports the polyhedron for Paraview
void exportPolyhedron(const Polyhedron& P);


// Function that adds a vertex to a polyhedron if it's not already present (Triangle.cpp)
// Returns the ID of the vertex in P.vertices
unsigned int addVertex(Polyhedron& P, double x, double y, double z);


// Function that adds an edge to a polyhedron if it's not already present (Triangle.cpp)
// Returns the ID of the edge in P.edges
unsigned int addEdge(Polyhedron& P, unsigned int origin, unsigned int end);


// Functions for Class I and Class II triangulation of a polyhedron (Triangle.cpp)
Polyhedron TriangleClassI(Polyhedron& P, unsigned int a);
Polyhedron TriangleClassII(Polyhedron& P, unsigned int a);


}