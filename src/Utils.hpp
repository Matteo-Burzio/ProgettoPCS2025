#pragma once

#include "Polyhedron.hpp"
#include "UCDUtilities.hpp"

using namespace std;

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

bool writeOutput(const Polyhedron& P);

