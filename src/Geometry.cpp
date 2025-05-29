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


/////////////////////////////////////////////////////////////////////////////

// // Function which finds the faces and edges adjacent to each vertex of the polyhedron
// void getVertexNeighbors(Polyhedron& P)
// {
// 	// Iterate along the vertices of the Polyhedron
// 	for (auto& v : P.vertices)
// 	{
// 		// Initilize the vector for the faces that contain the vertex (not in order)
// 		vector<unsigned int> incidentFaces;

// 		// reserve per incidentFaces ??
		
// 		// Find all the faces that contain the vertex
// 		for (const auto& f : P.faces)
// 		{
// 			if (find(f.idVertices.begin(), f.idVertices.end(), v.id) != f.idVertices.end())
// 			{
// 				// Add the face to the vector
// 				incidentFaces.push_back(f.id);
// 			}
// 		}

// 		// Initialize temporary vectors for the faces and edges that contain the vertex (in order)
// 		vector<unsigned int> orderedFaces;
// 		vector<unsigned int> orderedEdges;

// 		// Choose an arbitrary face to start with and add it to the ordered faces
// 		// (in this case, the first one)
// 		orderedFaces.push_back(incidentFaces.front());
		
// 		// Delete the face from the unordered faces
// 		incidentFaces.erase(incidentFaces.begin()); ///////////////////////////////////// usare una lista?

// 		// Iterate until the vector of the unorderes faces is empty
// 		while (!incidentFaces.empty())
// 		{
// 			// Get a reference to the last face in the vector of ordered faces
// 			Face& currentFace = P.faces[orderedFaces.back()];

// 			// Iterate along vector of faces to be visited 
// 			for (auto it = incidentFaces.begin(); it != incidentFaces.end(); ++it)
// 			{
// 				// Get a reference to current face
// 				Face& candidate = P.faces[*it];   /////////////// cambiare in f_id?

// 				// Iterate along edges to find the one shared with previous face
// 				for (unsigned int e_id : currentFace.idEdges)
// 				{
// 					// Get a reference to current edge
// 					Edge& edge = P.edges[e_id];

// 					// Skip to next edge if neither its origin nor its end
// 					// is the current vertex
// 					if (edge.origin != v.id && edge.end != v.id)
// 					{
// 						continue;
// 					}

// 					// If the edge is in the current face and the vertex is in the current edge
// 					if (find(candidate.idEdges.begin(), candidate.idEdges.end(), e_id)
// 						!= candidate.idEdges.end() &&
// 						find(candidate.idVertices.begin(), candidate.idVertices.end(), v.id)
// 						!= candidate.idVertices.end())
// 					{

// 						// Add the face and the edge to the vectors
// 						orderedFaces.push_back(*it);
// 						orderedEdges.push_back(e_id);
// 						incidentFaces.erase(it); ///////////////////// pop?

// 						// If found, stop iterating
// 						break;
// 					}
// 				}
// 			}
// 		}

// 		// Get a reference to first and last visited face
// 		Face& firstFace = P.faces[orderedFaces.front()];
// 		Face& lastFace = P.faces[orderedFaces.back()];

// 		// Iterate along edges of the first face
// 		for (unsigned int e_id : firstFace.idEdges)
// 		{
// 			// get a reference to current edge
// 			Edge& edge = P.edges[e_id];
			
// 			// If the current vertex is origin/end of the current edge
// 			// and the current edge is in the last face
// 			if ((edge.origin == v.id || edge.end == v.id) &&
// 				find(lastFace.idEdges.begin(), lastFace.idEdges.end(), e_id) != lastFace.idEdges.end())
// 			{
// 				// Add the last edge
// 				orderedEdges.push_back(e_id);

// 				// If found, stop iterating
// 				break;
// 			}
// 		}

// 		// Store the found values
// 		v.faceNeighbors = orderedFaces;
// 		v.edgeNeighbors = orderedEdges;
// 	}
// }


// Function which finds the faces and edges adjacent to each vertex of the polyhedron
void getVertexNeighbors(Polyhedron& P)
{
	// Iterate along the vertices of the Polyhedron
	for (auto& v : P.vertices)
	{
		// Initilize a list of faces that contain the vertex (not in order)
		list<unsigned int> incidentFaces;

		// reserve per incidentFaces ??
		
		// Find all the faces that contain the vertex
		for (const auto& f : P.faces)
		{
			if (find(f.idVertices.begin(), f.idVertices.end(), v.id) != f.idVertices.end())
			{
				// Add the face to the list
				incidentFaces.push_back(f.id);
			}
		}

		// Choose an arbitrary face to start with and add it to the ordered faces
		// (in this case, the first one)
		
		// If the list is not empty
		if (!incidentFaces.empty())
		{
			// Add first face to neighbors and remove it from the list
			v.faceNeighbors.push_back(incidentFaces.front());
			incidentFaces.pop_front();
		}

		// Iterate until the list of the unorderes faces is empty
		while (!incidentFaces.empty())
		{
			// Get a reference to the last neighboring face
			Face& currentFace = P.faces[v.faceNeighbors.back()];

			// Iterate along list of faces to be visited 
			for (auto f_id : incidentFaces)
			{
				// Get a reference to current face
				Face& candidate = P.faces[f_id];

				// Iterate along edges to find the one shared with previous face
				for (unsigned int e_id : currentFace.idEdges)
				{
					// Get a reference to current edge
					Edge& edge = P.edges[e_id];

					// Skip to next edge if neither its origin nor its end
					// is the current vertex
					if (edge.origin != v.id && edge.end != v.id)
					{
						continue;
					}

					// If the edge is in the current face and the vertex is in the current edge
					if (find(candidate.idEdges.begin(), candidate.idEdges.end(), e_id)
						!= candidate.idEdges.end() &&
						find(candidate.idVertices.begin(), candidate.idVertices.end(), v.id)
						!= candidate.idVertices.end())
					{

						// Add the face and the edge to the vectors
						v.faceNeighbors.push_back(f_id);
						v.edgeNeighbors.push_back(e_id);
						incidentFaces.remove(f_id);

						// If found, stop iterating
						break;
					}
				}
			}
		}

		// Get a reference to first and last visited face
		Face& firstFace = P.faces[v.faceNeighbors.front()];
		Face& lastFace = P.faces[v.faceNeighbors.back()];

		// Iterate along edges of the first face
		for (unsigned int e_id : firstFace.idEdges)
		{
			// get a reference to current edge
			Edge& edge = P.edges[e_id];
			
			// If the current vertex is origin/end of the current edge
			// and the current edge is in the last face
			if ((edge.origin == v.id || edge.end == v.id) &&
				find(lastFace.idEdges.begin(), lastFace.idEdges.end(), e_id) != lastFace.idEdges.end())
			{
				// Add the last edge
				v.edgeNeighbors.push_back(e_id);

				// If found, stop iterating
				break;
			}
		}
	}
}


// Function which finds which faces each edge is adjacent to
void getEdgeNeighbors(Polyhedron& P)
{
	// Iterate along the edges of P
	for (auto& e : P.edges)
	{
		// Iterate along the faces of P
		for (const auto& f : P.faces)
		{
			// If the edge is in the face
			if (find(f.idEdges.begin(), f.idEdges.end(), e.id) != f.idEdges.end())
			{
				// Save the edge in the vector of neighbors
				e.faceNeighbors.push_back(f.id);

				// After 2 faces are found, the loop can be stopped
				if (e.faceNeighbors.size() == 2)
				{
					break;
				}
			}
		}
	}
}



/////////////////////////////////////////////////////////////////////////////


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

