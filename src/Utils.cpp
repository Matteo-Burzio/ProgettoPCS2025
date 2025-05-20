#include "Utils.hpp"
#include <cmath>

using namespace std;


namespace PolyhedralLibrary {


// Function that constructs a tetrahedron represented as a Polyhedron
Polyhedron Tetrahedron()
{
	Polyhedron P;
	P.id = 0;
	vector<Vertex> nonNormalizedVertices = {
		{0,1,1,1},
		{1,-1,-1,1},
		{2,-1,1,-1},
		{3,1,-1,-1}
	};
	for (const Vertex& v : nonNormalizedVertices)
	{
		P.vertices.push_back(normalizeVertex(v));
	}
	P.edges = {
		{0,0,1}, {1,1,2}, {2,2,0},
		{3,0,3}, {4,3,1}, {5,3,2}
	};
	P.faces = {
		{0, {0,1,2}, {0,1,2}},
		{1, {0,3,2}, {3,5,2}},
		{2, {0,1,3}, {0,4,3}},
		{3, {1,2,3}, {1,5,4}}
	};
	return P;
}       

// Function that constructs an octahedron represented as a Polyhedron
Polyhedron Octahedron()
{
	Polyhedron P;
	P.id = 1;
	P.vertices = {
		{0,1,0,0},
		{1,-1,0,0},
		{2,0,1,0},
		{3,0,-1,0},
		{4,0,0,1},
		{5,0,0,-1}
	};
	P.edges = {
		{0,0,2}, {1,2,1}, {2,1,3}, {3,3,0},
		{4,0,4}, {5,2,4}, {6,1,4}, {7,3,4},
		{8,0,5}, {9,2,5}, {10,1,5}, {11,3,5}
	};
	P.faces = {
		{0, {0,2,4}, {0,5,4}},
		{1, {0,4,3}, {4,7,3}},
		{2, {4,3,1}, {7,2,6}},
		{3, {4,1,2}, {6,1,5}},
		{4, {5,1,2}, {10,1,9}},
		{5, {5,2,0}, {9,0,8}},
		{6, {0,5,3}, {8,11,3}},
		{7, {3,5,1}, {11,10,2}}
	};
	return P;
}

// Function that constructs an icosahedron represented as a Polyhedron
Polyhedron Icosahedron()
{
	Polyhedron P;
	P.id = 2;
	const double phi = (1.0 + sqrt(5.0)) / 2.0;
	vector<Vertex> nonNormalizedVertices = {
		{0,-1,phi,0},
		{1,1,phi,0},
		{2,-1,-phi,0},
		{3,1,-phi,0},
		{4,0,-1,phi},
		{5,0,1,phi},
		{6,0,-1,-phi},
		{7,0,1,-phi},
		{8,phi,0,-1},
		{9,phi,0,1},
		{10,-phi,0,-1},
		{11,-phi,0,1}
	};
	for (const Vertex& v : nonNormalizedVertices)
	{
		P.vertices.push_back(normalizeVertex(v));
	}
	P.edges = {
		{0,0,5}, {1,0,1}, {2,0,11}, {3,0,10}, {4,0,7},
		{5,1,5}, {6,1,7}, {7,1,8}, {8,1,9}, {9,5,9},
		{10,5,11}, {11,9,8}, {12,8,7}, {13,9,4}, {14,9,3},
		{15,4,3}, {16,5,4}, {17,4,11}, {18,2,4}, {19,2,11},
		{20,2,3}, {21,2,6}, {22,6,3}, {23,8,3}, {24,8,6},
		{25,7,6}, {26,2,10}, {27,10,6}, {28,10,7}, {29,11,10}
	};
	P.faces = {
		{0, {5,0,11}, {0,2,10}},
		{1, {0,5,1}, {0,5,1}},
		{2, {5,1,9}, {5,8,9}},
		{3, {5,4,9}, {16,13,9}},
		{4, {4,5,11}, {16,10,17}},
		{5, {4,3,9}, {15,14,13}},
		{6, {4,11,2}, {17,19,18}},
		{7, {2,3,6}, {20,22,21}},
		{8, {6,2,10}, {21,26,27}},
		{9, {3,8,6}, {23,24,22}},
		{10, {8,9,3}, {11,14,23}},
		{11, {9,8,1}, {11,7,8}},
		{12, {8,7,1}, {12,6,7}},
		{13, {6,7,8}, {25,12,24}},
		{14, {7,10,6}, {28,27,25}},
		{15, {7,10,0}, {28,3,4}},
		{16, {0,10,11}, {3,29,2}},
		{17, {4,2,3}, {18,20,15}},
		{18, {1,0,7}, {1,4,6}},
		{19, {11,2,10}, {19,26,29}}
	};
	return P;
}


// Function that normalizes the coordinates of a vertex to lie on the unit sphere
Vertex normalizeVertex(const Vertex& v)
{
	// Compute the Euclidean norm of the vector
	double length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);

	// Return the vertex with normalized coordinates
	return Vertex{v.id, v.x/length, v.y/length, v.z/length};
}


}