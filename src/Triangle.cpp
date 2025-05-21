#include "Utils.hpp"

using namespace std;
using namespace Eigen;


// Function that checks if the new vertex already exists in the Polyhedron
bool checkVertex(const Polyhedron& P, const Vertex& v)
{
	// Get machine precision
	const double eps = numeric_limits<double>::epsilon();
	
	// Iterate along vertices to check if it doesn't exist yet
	for (unsigned int i = 0; i < P.numVertices(); ++i)
	{
		// Get a reference to the current vertex
		const Vertex& existing = P.vertices[i];

		// Check if it's the same
		if (v.coords.isApprox(existing.coords, eps))
		{
			return false; // The new vertex already exists
		}
	}

	return true;
}


// Function that adds a new vertex to the polyhedron
void addVertex(Polyhedron& P, Vertex& v)
{
	// ID of new vertex is the first available natural number
	v.id = P.numVertices();

	// Add the new vertex to P
	P.vertices.push_back(v);
}



// Function that checks if the new edge already exists in the Polyhedron
bool checkEdge(const Polyhedron& P, const Edge& e)
{
	// Check if vertices exist
	if (e.origin >= P.numVertices() || e.end >= P.numVertices())
		return false;
		
	// Check that the edge is valid
	if (e.origin == e.end)
		return false;

	// Iterate along edges to check if it doesn't exist yet
	for (unsigned int i = 0; i < P.numEdges(); ++i)
	{
		// Get a reference to the current vertex
		const Edge& existing = P.edges[i];
		
		// Check if it's the same
		if ((existing.origin == e.origin && existing.end == e.end) ||
			(existing.origin == e.end && existing.end == e.origin))
			return false; // The new edge already exists
	}
	
	return true;
}


// Function that adds a new edge to the polyhedron
void addEdge(Polyhedron& P, Edge& e)
{
	// ID of new edge is the first available natural number
	e.id = P.numEdges();

	// Add the new edge to P
	P.edges.push_back(e);
}


/*


// Function for Class I triangulation of a polyhedron with parameter val (val > 0)
Polyhedron TriangleClassI(const Polyhedron& P_old, const unsigned int& val)
{
	// Initialize a new polyhedron
	Polyhedron P;

	// (da completare)
	// Allocate the correct amount of space for new vertices
	unsigned int num_vertices = (val * (val + 1)) * 0.5 * P_old.numFaces;
	P.edges.reserve(num_vertices);
		
	// Allocate the correct amount of space for new edges
	unsigned int num_edges = (val * (val + 1)) * 1.5 * P_old.numFaces;
	P.edges.reserve(num_edges);

	// Allocate the correct amount of space for new faces
	unsigned int num_triangles = (val ^ 2) * P_old.numFaces;
	P.faces.reserve(num_triangles);


	// Iterate along faces of the platonic solid
	for(auto& face : P.faces)
	{
		// We expect all faces to be triangles
		// Get IDs and a reference of each vertex of the face
		unsigned int id_A = face.idVertices[0];
		const Vertex& A = P.vertices[id_A];
		
		unsigned int id_B = face.idVertices[1];
		const Vertex& B = P.vertices[id_B];
		
		unsigned int id_C = face.idVertices[2];
		const Vertex& C = P.vertices[id_C];
		

		// Triangulation algorithm
		for (size_t i = 0; i <= val; i++)
		{
			for (size_t j=0; j<= val-i;j++)
			{
				// Initialize a vertex
				Vertex V;

				// Set the vertex's coordinates
				V.coords = (i * A.coords + j* B.coords +(val-i-j) * C.coords) / val;

				// Check if the vertex already exists
				if (checkVertex(P,V))
				{
					// Add the vertex to the polyhedron
					addVertex(P,V);
				}
				
				// Connect vertices with proper edges


				// be careful about double edges

				// Create new faces

				// Check faces


			}
		}
	}

	return P;
}









// Function for Class II triangulation of a polyhedron with parameter a (b = c =: a > 0)
Polyhedron TriangleClassII(const Polyhedron& P_old, const unsigned int& val)
{

	return P;
}



*/