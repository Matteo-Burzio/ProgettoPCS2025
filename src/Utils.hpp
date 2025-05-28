#pragma once

#include "Polyhedron.hpp"
#include "UCDUtilities.hpp"

using namespace std;

//Function that check if values of input are correct
bool check_input(int argc, char* argv[],
				 unsigned int &p, unsigned int &q,
				 unsigned int &b, unsigned int &c,
				 unsigned int &val, unsigned int &flag);

// Functions that create tetrahedron, octahedron and icosahedron
Polyhedron Tetrahedron();
Polyhedron Octahedron();
Polyhedron Icosahedron();

// Function that exports the polyhedron for Paraview
void exportPolyhedron(const Polyhedron& P);

// Function that writes the output
bool writeOutput(const Polyhedron& P);

