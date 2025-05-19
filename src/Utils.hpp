#pragma once

#include <iostream>
#include <sstream>

#include "Polyhedron.hpp"

using namespace std;
using namespace PolyhedralLibrary;

// Functions that create tetrahedron, octahedron and icosahedron (Polyhedron.cpp)
Polyhedron Tetrahedron();
Polyhedron Octahedron();
Polyhedron Icosahedron();

// Function that normalizes the vertices (Polyhedron.cpp)
Vertex normalizeVertex(const Vertex& v);
