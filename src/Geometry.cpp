#include "Geometry.hpp"

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

// // Function which finds the neighbours of each vertex and edge
// void getNeighbours(Polyhedron& P)
// {
	// // iterate along vertices of the polyhedron
	// for(const auto& v : P.vertices)
	// {
		// for(const auto& f : P.faces)
		// {
			// if(find(f.idVertices.begin(), f.idVertices.end(), v.id) != f.idVertices.end())
			// {
				// v.faceNeighbours.push_back(f.id);
			// }
		// }

		// // Get an arbitrary face to start from
		// unsigned int id_f0 = v.faceNeighbours[0];

		// for(const auto& id_e : P.faces[id_f0].idEdges)
		// {
			// if((v.id == P.edges[id_e].origin) || (v.id == P.edges[id_e].end))
			// {
				// v.edgeNeighbours.push_back(id_e);
			// }
		// }

		// unsigned int i=1;
		// while (v.edgeNeighbours[i] != v.edgeNeighbours[0])
		// {
			// unsigned int id_fi = v.faceNeighbours[i];

			// for(const auto& id_e : P.faces[id_fi].idEdges)
			// {
				// if((v.id == P.edges[id_e].origin) || (v.id == P.edges[id_e].end))
				// {
					// if (find(v.edgeNeighbours.begin(), v.edgeNeighbours.end(), id_e) == v.edgeNeighbours.end())
					// v.edgeNeighbours.push_back(id_e);
				// }
			// }






			// i++;
		// }

	// }
// }


// // Function that creates the dual of the polyhedron
// Polyhedron Dual(const Polyhedron& P)
// {
	// // Initialize dual polyhedron
	// Polyhedron Q;
	
	// // Assign its ID
	// Q.id = P.id + 2;
	
	// // Reserve correct amount of space
	// Q.vertices.reserve(P.numFaces());
	// Q.edges.reserve(P.numEdges());
	// Q.faces.reserve(P.numVertices());
	
	// // Create vertices of the dual polyhedron
	// // They are the barycenters of P's faces

	
	// // Iterate along faces to create Q's vertices
	// for(const auto& f : P.faces)
	// {
		// // Initialize dual's vertex
		// Vertex v_dual = Barycenter(P, f.id);
		
		// // Normalize the vertex
		// normalizeVertex(v_dual);
		
		// // Add vertex to Q
		// Q.vertices.push_back(v_dual);
	// }
	
	// // Iterate along P's vertices
	// for(auto& v : P.vertices)
	// {
		// // Initialize dual's face
		// Face f_dual;
		
		// // Set the correct ID
		// f_dual.id = v.id;


		
		
	// }
		
	
	// return Q;
// }
