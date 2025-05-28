#include "Geometry.hpp"
#include "Triangle.hpp"

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

// Function which finds the neighbors of each vertex and edge
void getNeighbors(Polyhedron& P)
{
	// iterate along vertices of the polyhedron
	for(auto& v : P.vertices)
	{
		// Initialize a list of IDs of faces
		list<unsigned int> adjacentFaces_id;

		// Find all faces containing the vertex
		for(const auto& f: P.faces)
		{
			if (find(f.idVertices.begin(), f.idVertices.end(), v.id) != f.idVertices.end())
			{
				adjacentFaces_id.push_back(f.id);
			}
		}

		// Get first element in the list (arbitrary)
		unsigned int currentFace_id = adjacentFaces_id.front();
		adjacentFaces_id.pop_front();
		v.faceNeighbors.push_back(currentFace_id);

		// Set a flag to know if to keeping iterating
		// Set to true to enter the while loop
		bool foundNext = true;

		// Iterate until the list is empty
		while(!adjacentFaces_id.empty() && foundNext)
		{
			foundNext = false; // set to false

			// Iterate along current face's edges
			for(unsigned int e_id : P.faces[currentFace_id].idEdges)
			{
				// If both origin and end are not the current vertex,
				// skip to next edge of current face
				if((P.edges[e_id].origin != v.id) && (P.edges[e_id].end))
				{
					continue;
				}

				// Find another face in the list that has both vertex v and edge e
				for(const auto& f_id : adjacentFaces_id)
				{
					if((find(P.faces[f_id].idVertices.begin(), P.faces[f_id].idVertices.end(), v.id) != P.faces[f_id].idVertices.end()) &&
						(find(P.faces[f_id].idEdges.begin(), P.faces[f_id].idEdges.end(), e_id) != P.faces[f_id].idEdges.end()))
						{
							// Update current face
							currentFace_id = f_id;

							// Add the vertex ID to v's neighbors
							v.edgeNeighbors.push_back(e_id);

							// Add the face ID to v's neighbors
							v.faceNeighbors.push_back(f_id);

							// Remove the face from the list
							adjacentFaces_id.remove(f_id);

							// Set flag to true
							foundNext = true;

							break;
						}

				}

				// Stopiterating along edges when next face is found
				if(foundNext)
				{
					break;
				}
			}
		}

		// Last edge???? (da finire)










		////////////////////////////////// Scritto in classe:
		
		// for(const auto& f : P.faces)
		// {
			// if(find(f.idVertices.begin(), f.idVertices.end(), v.id) != f.idVertices.end())
			// {
				// v.faceNeighbors.push_back(f.id);
			// }
		// }

		// // Get an arbitrary face to start from
		// unsigned int id_f0 = v.faceNeighbors[0];

		// for(const auto& id_e : P.faces[id_f0].idEdges)
		// {
			// if((v.id == P.edges[id_e].origin) || (v.id == P.edges[id_e].end))
			// {
				// v.edgeNeighbors.push_back(id_e);
			// }
		// }

		// unsigned int i=1;
		// while (v.edgeNeighbors[i] != v.edgeNeighbors[0])
		// {
			// unsigned int id_fi = v.faceNeighbors[i];

			// for(const auto& id_e : P.faces[id_fi].idEdges)
			// {
				// if((v.id == P.edges[id_e].origin) || (v.id == P.edges[id_e].end))
				// {
					// if (find(v.edgeNeighbors.begin(), v.edgeNeighbors.end(), id_e) == v.edgeNeighbors.end())
					// v.edgeNeighbors.push_back(id_e);
				// }
			// }
			// i++;
		// }
		////////////////////////////////////////////


	}
}


// Function that creates the dual of a polyhedron
Polyhedron Dual(const Polyhedron& P)
{
	// Initialize the dual polyhedron
	Polyhedron Q;
	
	// Assign the ID of the dual
	Q.id = P.id + 2;
	
	// Reserve correct amount of space for vertices, edges and faces
	Q.vertices.reserve(P.numFaces());
	Q.edges.reserve(P.numEdges());
	Q.faces.reserve(P.numVertices());
	
	
	// Create vertices of the dual polyhedron (barycenters of P's faces)

	// Iterate along the faces of the old polyhedron
	for (const auto& f : P.faces)
	{
		// Initialize the vertex of the dual
		Vertex v_dual = Barycenter(P, f.id);
		
		// Normalize the vertex
		normalizeVertex(v_dual);
		
		// Add the vertex to the dual
		Q.vertices.push_back(v_dual);
	}
	
	
	
	// Create edges of the dual polyhedron
	
	// Iterate along the edges of the old polyhedron
	for (const auto& e : P.edges)
	{
		// Add the edge to the dual
		addEdgeIfMissing(Q, e.faceNeighbors[0], e.faceNeighbors[1], e.id);
	}
	
	
	// Create faces of the dual polyhedron
	
	// Iterate along the vertices of the old polyhedron
	for (const auto& v : P.vertices)
	{
		// Initialize the face of the dual
		Face f_dual;
		
		// Assign the same ID as the vertex of the old polyhedron
		f_dual.id = v.id;
		
		// Iterate along the neighbor faces of the old polyhedron's vertex
		for (unsigned int id_f : v.faceNeighbors)
		{
			// Set the vertices of the dual's face
			f_dual.idVertices.push_back(id_f);
		}
		
		// Iterate along the neighbor edges of the old polyhedron's vertex
		for (unsigned int id_e : v.edgeNeighbors)
		{
			// Set the edges of the dual's face
			f_dual.idEdges.push_back(id_e);
		}
		
		// Add the face to the dual
		Q.faces.push_back(f_dual);
		
	}
	
	return Q;
}

