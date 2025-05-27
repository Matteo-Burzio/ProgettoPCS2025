#include "Utils.hpp"

using namespace std;
using namespace Eigen;


// Function that normalizes the coordinates of a vertex to lie on the unit sphere
void normalizeVertex(Vertex& v)
{
	// Compute the Euclidean norm of the vector
	double length = v.coords.norm();

	// Normalize the coordinates
	v.coords /= length;
}


// Function which returns the barycenter of a face
Vertex Barycenter(const Polyhedron& P, const unsigned int& f_id)
{
	// Initialize a vertex
	Vertex bc;
	bc.coords = {0, 0, 0};

	// Assign same ID as the face
	bc.id = f_id;
	
	// Get number of vertices (we expect always 3)
	unsigned int num_v = P.faces[f_id].numVertices();

	//Compute coordinates of bc
	for (size_t i = 0; i < num_v; i++)
	{
		unsigned int id_v = P.faces[f_id].idVertices[i];
		bc.coords += P.vertices[id_v].coords;
	}
	bc.coords /= num_v;

	return bc;
}


// Function that creates the dual of the polyhedron
Polyhedron Dual(const Polyhedron& P)
{
	// Initialize dual polyhedron
	Polyhedron Q;
	
	// Assign its ID
	Q.id = P.id + 2;
	
	// Reserve correct amount of space
	Q.vertices.reserve(P.numFaces());
	Q.edges.reserve(P.numEdges());
	Q.faces.reserve(P.numVertices());
	
	// Create vertices of the dual polyhedron
	// They are the barycenters of P's faces
	
	// Iterate along faces to create Q's vertices
	for(const auto& f : P.faces)
	{
		// Initialize dual's vertex
		Vertex v_dual = Barycenter(P, f.id);
		
		// Normalize the vertex
		normalizeVertex(v_dual);
		
		// Add vertex to Q
		Q.vertices.push_back(v_dual);
	}
	
	//
	for(const auto& v : P.vertices)
	{
		// Initialize dual's face
		Face f_dual;
		
		// Set the correct ID
		f_dual.id = v.id;

		// Get IDs of vertices of the dual's face
		for(const auto& f : P.faces)
		{
			if(find(f.idVertices.begin(), f.idVertices.end(), v.id) != f.idVertices.end())
			{
				f_dual.idVertices.push_back(f.id);
			}				
		}
		
		
	}
		
	
	return Q;
}
