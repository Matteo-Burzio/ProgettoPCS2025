#include "Polyhedron.hpp"
#include "Utils.hpp"

using namespace std;


namespace PolyhedralLibrary {

// Function that adds vertices to a face if it's not already present (within a tolerance)
unsigned int addVertex(Polyhedron& P, double x, double y, double z)
{
	// Get machine precision
	const double eps = numeric_limits<double>::epsilon();
	
	// Check if the new vertex already exists in P (within a tolerance)
	for (unsigned int i = 0; i < P.numVertices(); ++i)
	{
		const Vertex& existing = P.vertices[i];
		double dx = existing.x - x;
		double dy = existing.y - y;
		double dz = existing.z - z;
		double distSquared = dx * dx + dy * dy + dz * dz;
		if (distSquared < eps * eps)
		{
			return i; // The new vertex is duplicate 
		}
	}
	
	// If the new vertex doesn't exist in P
	Vertex v0 = {P.numVertices(), x, y, z}; // Define the new vertex
	Vertex v = normalizeVertex(v0); // Normalize the new vertex
	P.vertices.push_back(v); // Add the normalized new vertex to P
	return v.id; 
}


// Function that adds edges to a face if it's not already present
unsigned int addEdge(Polyhedron& P, unsigned int origin, unsigned int end)
{
	// Check that the edge is valid
	if (origin == end)
	{
		cerr << "Error: invalid extrema in adding an edge" << endl;
		return -1; // Returns max unsigned int = 2^64 - 1 (macchina a 64 bit)
		////////////////////// SISTEMA STA COSA ///////////////////////////
	}
	// Check if the new edge already exists in P
	for (unsigned int i = 0; i < P.numEdges(); ++i)
	{
		const Edge& existing = P.edges[i];
		if ((existing.origin == origin && existing.end == end) ||
			(existing.origin == end && existing.end == origin))
		{
			return i; // The new edge is a duplicate
		}
	}
	// If the new edge doesn't exist in P
	Edge e = {P.numEdges(), origin, end}; // Define the new edge
	P.edges.push_back(e); // Add the new edge to P
	return e.id;
}







/*


// Function for Class I triangulation of a polyhedron with parameter a (a > 0)
Polyhedron TriangleClassI(Polyhedron& P, unsigned int a)
{

	return P;
};









// Function for Class II triangulation of a polyhedron with parameter a (b = c =: a > 0)
Polyhedron TriangleClassII(Polyhedron& P, unsigned int a)
{

	return P;
};



*/

}