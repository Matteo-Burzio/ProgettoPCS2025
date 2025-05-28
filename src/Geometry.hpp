#pragma once

#include "Polyhedron.hpp"


// Function that normalizes the vertices (Geometry.cpp)
void normalizeVertex(Vertex& v);

// Function which computes the barycenter of a face (Geometry.cpp)
Vertex Barycenter(const Polyhedron& P, const unsigned int& f_id);

// Function which finds the neighbors of each vertex and edge
void getNeighbors(Polyhedron& P);

// Function that creates the dual of the polyhedron (Geometry.cpp)
Polyhedron Dual(const Polyhedron& P);