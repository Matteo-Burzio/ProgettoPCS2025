#pragma once

#include "Polyhedron.hpp"


// Functions that checks if the new vertex already exists (Triangle.cpp)
unsigned int addVertexIfMissing(Polyhedron& P, const Vector3d coords_V);

// Functions that check if the new edge already exists and add it to P(Triangle.cpp)
unsigned int addEdgeIfMissing(Polyhedron& P, unsigned int id1, unsigned int id2,
							  unsigned int id_e = numeric_limits<unsigned int>::max());

// Functions for Class I and Class II triangulation of a polyhedron (Triangle.cpp)
Polyhedron TriangleClassI(const Polyhedron& P_old, const unsigned int& val);
//Polyhedron TriangleClassII(const Polyhedron& P_old, const unsigned int& val);
