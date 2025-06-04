#pragma once

#include "Polyhedron.hpp"
#include "UCDUtilities.hpp"

using namespace std;

// Function that check if values of polyhedron input are correct
bool checkPolyhedronInput(int argc, char* argv[],
				 unsigned int &p, unsigned int &q,
				 unsigned int &b, unsigned int &c,
				 unsigned int &val, unsigned int &flag);

// Function that check if values of graph input are correct
bool checkInputGraph(const unsigned int& id_path_start, 
					const unsigned int& id_path_end, 
					const Polyhedron& P);

// Functions that create tetrahedron, octahedron and icosahedron
Polyhedron Tetrahedron();
Polyhedron Octahedron();
Polyhedron Icosahedron();

// Function that exports the polyhedron for Paraview
void exportPolyhedron(const Polyhedron& P);

// Function that writes the output
bool writeOutput(const Polyhedron& P);

