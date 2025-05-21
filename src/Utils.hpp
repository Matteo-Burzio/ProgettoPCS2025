#pragma once

#include "Polyhedron.hpp"
#include "UCDUtilities.hpp"

using namespace std;


// Functions that create tetrahedron, octahedron and icosahedron (Utils.cpp)
Polyhedron Tetrahedron();
Polyhedron Octahedron();
Polyhedron Icosahedron();

// Function that exports the polyhedron for Paraview (Utils.cpp)
void exportPolyhedron(const Polyhedron& P);



// Function that normalizes the vertices (Geometry.cpp)
Vertex normalizeVertex(const Vertex& v);

// Function which computes the barycenter of a face (Geometry.cpp)
Vertex Barycenter(const Polyhedron& P, const unsigned int& f_id);

// Function that creates the dual of the polyhedron (Geometry.cpp)
Polyhedron Dual(const Polyhedron& P);



// Functions that check if the new vertex already exists and add it to P(Triangle.cpp)
bool checkVertex(const Polyhedron& P, const Vertex& v);
void addVertex(Polyhedron& P, Vertex& v);

// Functions that check if the new edge already exists and add it to P(Triangle.cpp)
bool checkEdge(const Polyhedron& P, const Edge& e);
void addEdge(Polyhedron& P, Edge& e);


/*
// Functions for Class I and Class II triangulation of a polyhedron (Triangle.cpp)
Polyhedron TriangleClassI(const Polyhedron& P_old, const unsigned int& val);
Polyhedron TriangleClassII(const Polyhedron& P_old, const unsigned int& val);
*/