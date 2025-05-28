#pragma once

#include "Polyhedron.hpp"
#include "UCDUtilities.hpp"

// Function that normalizes the vertices (Geometry.cpp)
void normalizeVertex(Vertex& v);

// Function which computes the barycenter of a face (Geometry.cpp)
Vertex Barycenter(const Polyhedron& P, const unsigned int& f_id);

// Function which finds the neighbours of each vertex and edge
void getNeighbours(Polyhedron& P);

// // Function that creates the dual of the polyhedron (Geometry.cpp)
// Polyhedron Dual(const Polyhedron& P); //commento perchè non è ancora implementata in cpp