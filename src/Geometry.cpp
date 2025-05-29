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


void getVertexNeighbors(Polyhedron& P)
{
	// Iterate along the vertices of the Polyhedron
	for (auto& v : P.vertices)
	{
		// Initilize the vector for the faces that contain the vertex (not in order)
		vector<unsigned int> incidentFaces;

		// reserve per incidentFaces ??
		
		// Find all the faces that contain the vertex
		for (const auto& f : P.faces)
		{
			if (find(f.idVertices.begin(), f.idVertices.end(), v.id) != f.idVertices.end())
			{
				// Add the face to the vector
				incidentFaces.push_back(f.id);
			}
		}

		// Initialize vectors for the faces and adges that contain the vertex (in order)
		vector<unsigned int> orderedFaces;
		vector<unsigned int> orderedEdges;

		// Choose an arbitrary face to start with and add it to the ordered faces
		orderedFaces.push_back(incidentFaces.front()); //////////////////////////////////
		
		// Delete the face from the unordered faces
		incidentFaces.erase(incidentFaces.begin()); /////////////////////////////////////

		// Iterate until the vector of the unorderes faces is empty
		while (!incidentFaces.empty())
		{
			// l'ultima faccia che ho messo in quello ordinato
			Face& currentFace = P.faces[orderedFaces.back()];

			// cerco la prossima faccia adiacente che condivide un edge e contiene il vertice
			for (auto it = incidentFaces.begin(); it != incidentFaces.end(); ++it)
			{
				// faccia che devo controllare
				Face& candidate = P.faces[*it];

				// devono condividere un edge che contiene v.id
				for (unsigned int e_id : currentFace.idEdges)
				{
					// lato che devo controllare
					Edge& edge = P.edges[e_id];

					// edge deve contenere v
					if (edge.origin != v.id && edge.end != v.id)
					{
						continue;
					}

					if (find(candidate.idEdges.begin(), candidate.idEdges.end(), e_id)
						!= candidate.idEdges.end() &&
						find(candidate.idVertices.begin(), candidate.idVertices.end(), v.id)
						!= candidate.idVertices.end())
					{

						// aggiungo faccia e lato
						orderedFaces.push_back(*it);
						orderedEdges.push_back(e_id);
						incidentFaces.erase(it);
						break;
					}
				}
			}
		}

		// aggiungo l'ultimo lato che serve per chiudere il cerchio (collega la prima e l'ultima faccia)
		Face& firstFace = P.faces[orderedFaces.front()];
		Face& lastFace = P.faces[orderedFaces.back()];
		for (unsigned int e_id : firstFace.idEdges)
		{
			Edge& edge = P.edges[e_id];
			if ((edge.origin == v.id || edge.end == v.id) &&
				find(lastFace.idEdges.begin(), lastFace.idEdges.end(), e_id) != lastFace.idEdges.end())
			{
				orderedEdges.push_back(e_id);
				break;
			}
		}

		// salvo gli ID ordinati
		v.faceNeighbors = orderedFaces;
		v.edgeNeighbors = orderedEdges;
	}
}




void getEdgeNeighbors(Polyhedron& P)
{
	for (auto& e : P.edges)
	{
		// controllo le facce
		for (const auto& f : P.faces)
		{
			if (find(f.idEdges.begin(), f.idEdges.end(), e.id) != f.idEdges.end())
			{
				e.faceNeighbors.push_back(f.id);
				// devo trovare 2 facce e evito che faccia cicli inutili
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

