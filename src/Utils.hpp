#pragma once

#include "Polyhedron.hpp"
#include "UCDUtilities.hpp"

using namespace std;

//Function that check if values of input are correct
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



// Function that normalizes the vertices (Geometry.cpp)
void normalizeVertex(Vertex& v);

// Function which computes the barycenter of a face (Geometry.cpp)
Vertex Barycenter(const Polyhedron& P, const unsigned int& f_id);

// Function that creates the dual of the polyhedron (Geometry.cpp)
Polyhedron Dual(const Polyhedron& P);



// Functions that checks if the new vertex already exists (Triangle.cpp)
unsigned int addVertexIfMissing(Polyhedron& P, const Vertex& v);

// Functions that check if the new edge already exists and add it to P(Triangle.cpp)
//bool checkEdge(const Polyhedron& P, const Edge& e);
//void addEdge(Polyhedron& P, Edge& e);
void addEdgeIfMissing(Polyhedron& P, unsigned int id1, unsigned int id2);

// Functions that check if the new face already exists and add it to P(Triangle.cpp)
bool checkFace(const Polyhedron& P, const Face& f);
void addFace(Polyhedron& P, Face& f);


// Functions for Class I and Class II triangulation of a polyhedron (Triangle.cpp)
Polyhedron TriangleClassI(const Polyhedron& P_old, const unsigned int& val);
//Polyhedron TriangleClassII(const Polyhedron& P_old, const unsigned int& val);
