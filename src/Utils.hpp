	#ifndef __UTILS_HPP_
#define __UTILS_HPP_


#include <iostream>
#include <sstream>


#include "polyhedral_mesh.hpp"


using namespace std;
using namespace PolyhedralLibrary;

// funzioni per generare tetraedro, ottaedro e icosaedro (Polyhedron.cpp)
Polyhedron Tetrahedron();
Polyhedron Octahedron();
Polyhedron Icosahedron();

// funzione per portare i vertici sulla sfera di raggio 1 (Polyhedron.cpp)
Vertex normalizeVertex(const Vertex& v);

#endif