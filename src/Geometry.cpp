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



// Function which finds which faces each edge is adjacent to
void getEdgeNeighbors(Polyhedron& P)
{
	// For each edge
	for (auto& e : P.edges)
	{
		// Clear existing neighbors
		e.faceNeighbors.clear();
		
		// Find faces containing this edge
		for (const auto& f : P.faces)
		{
			if (find(f.idEdges.begin(), f.idEdges.end(), e.id) != f.idEdges.end())
			{
				// Add face to neighbors
				e.faceNeighbors.push_back(f.id);
				
				// Each edge should connect exactly 2 faces
				if (e.faceNeighbors.size() == 2)
				{
					break;
				}
			}
		}
	}
}


// Function which finds which faces and edges each vertex is adjacent to
void getVertexNeighbors(Polyhedron& P)
{
	// Map that collects each vertex's neighbor edges
	unordered_map<unsigned int, vector<unsigned int>> unordered_neighbors;
	
	// Iterate on the polyhedron's edges to fill the map
	for (const auto& e : P.edges)
	{
		// Add each edge to the neighborhood of its origin and end
		unordered_neighbors[e.origin].emplace_back(e.id);
		unordered_neighbors[e.end].emplace_back(e.id);
	}
	
	// Iterate on the polyhedron's vertices
	for (auto& v : P.vertices)
	{
		// Clear existing neighbors
		v.faceNeighbors.clear();
		v.edgeNeighbors.clear();
		
		
		// Get its edge neighbors
		vector<unsigned int>& neighbors = unordered_neighbors[v.id];
		
		// Choose the starting edge (the first of the neighbors)
		unsigned int startEdgeId = neighbors[0];
		Edge startEdge = P.edges[startEdgeId];
		
		// Choose the starting face between the two neighbors of the first edge (the first)
		   // The starting face is also the first face to be added
		unsigned int currentFaceId = startEdge.faceNeighbors[0];
		
		// Add the first face to the face neighbors of the vertex
		v.faceNeighbors.push_back(currentFaceId);
		
		// Initialize the ID of the first edge to be added
		unsigned int currentEdgeId;
		
		// Find the first edge between the edges of the first face
		for (unsigned int e_id : P.faces[currentFaceId].idEdges) // 3 cycles
		{
			// Exclude the starting edge
			if (e_id == startEdgeId)
			{
				continue;
			}
			
			// Exclude the edge that doesn't contain the vertex
			if (find(neighbors.begin(), neighbors.end(), e_id) == neighbors.end())
			{
				continue;
			}
			
			// The only edge that remains is the correct one (the first edge)

			// Save the ID of the first edge
			currentEdgeId = e_id;
			
			// Add the first edge to the edge neighbors of the vertex
			v.edgeNeighbors.push_back(currentEdgeId);
			
			break;
		}
		
		// currentFaceId and currentEdgeId are the IDs of the first face and edge
		
		// Iterate until the cycle is closed: until the the currect edge is the starting edge
		while (currentEdgeId != startEdgeId)
		{
			// Initialize the ID of the next face to be added
			unsigned int nextFaceId;
			
			// Find the next face between the two face neighbors of the edge
			for (unsigned int f_id : P.edges[currentEdgeId].faceNeighbors) // 2 cycles
			{
				// Exclude the face which has already been added
				if (find(v.faceNeighbors.begin(), v.faceNeighbors.end(), f_id) != v.faceNeighbors.end())
				{
					continue;
				}
				
				// The only face that remains is the correct one (the next face)
				
				// Save the ID of the next face
				nextFaceId = f_id;
				
				// Add the next face to the face neighbors of the vertex
				v.faceNeighbors.push_back(nextFaceId);
				
				break;
			}
			
			// Initialize the ID of the next edge to be added
			unsigned int nextEdgeId;
			
			// Find the next edge between the edges of the next face
			for (unsigned int e_id : P.faces[nextFaceId].idEdges) // 3 cycles
			{
				// Exclude the edge which has already been added
				if (find(v.edgeNeighbors.begin(), v.edgeNeighbors.end(), e_id) != v.edgeNeighbors.end())
				{
					continue;
				}
				
				// Exclude the edge that doesn't contain the vertex
				if (find(neighbors.begin(), neighbors.end(), e_id) == neighbors.end())
				{
					continue;
				}
				
				// The only edge that remains is the correct one (the next edge)
				
				// Save the ID of the next edge
				nextEdgeId = e_id;
				
				// Add the next edge to the edge neighbors of the vertex
				v.edgeNeighbors.push_back(nextEdgeId);
				
				break;
			}
			
			// Update the variables
			currentFaceId = nextFaceId;
			currentEdgeId = nextEdgeId;
		}
		
	}
	
}


///////////////////////////////////////////////////////////////////////////////////

// VERSIONE VECCHIA

/*
// Function which finds the faces and edges adjacent to each vertex of the polyhedron
void getVertexNeighbors(Polyhedron& P)
{
	// Process each vertex in the polyhedron
	for (auto& v : P.vertices)
	{
		// Clear any existing neighbor data
		v.faceNeighbors.clear();
		v.edgeNeighbors.clear();
		
		// Step 1: Find the starting face (the one with lowest ID containing this vertex)
		unsigned int startFaceId = numeric_limits<unsigned int>::max();
		for (const auto& f : P.faces)
		{
			if (find(f.idVertices.begin(), f.idVertices.end(), v.id) != f.idVertices.end())
				startFaceId = min(startFaceId, f.id);
		}
		
		// Skip if vertex has no faces (shouldn't happen in valid polyhedron)
		if (startFaceId == numeric_limits<unsigned int>::max())
			continue;
			
		// Step 2: Initialize with the first face and its corresponding edge
		const Face& startFace = P.faces[startFaceId];
		auto vertexPos = find(startFace.idVertices.begin(), startFace.idVertices.end(), v.id);
		size_t idx = vertexPos - startFace.idVertices.begin();
		
		v.faceNeighbors.push_back(startFaceId);
		v.edgeNeighbors.push_back(startFace.idEdges[idx]);
		
		// Step 3: Set up tracking sets for visited elements
		set<unsigned int> visitedFaces = {startFaceId};
		set<unsigned int> visitedEdges = {startFace.idEdges[idx]};
		
		// Step 4: Process faces around the vertex
		unsigned int currentFaceId = startFaceId;
		unsigned int currentEdgeId = startFace.idEdges[idx];
		bool foundNextFace;
		
		do
		{
			foundNextFace = false;
			const Edge& currentEdge = P.edges[currentEdgeId];
			
			// Step 4a: Try to find next face through current edge
			for (unsigned int neighborFaceId : currentEdge.faceNeighbors)
			{
				// Skip if we've already processed this face
				if (visitedFaces.find(neighborFaceId) != visitedFaces.end())
					continue;
					
				// Check if this face contains our vertex
				const Face& neighborFace = P.faces[neighborFaceId];
				auto vertexPos = find(neighborFace.idVertices.begin(), neighborFace.idVertices.end(), v.id);
				if (vertexPos == neighborFace.idVertices.end())
					continue;
					
				// Found valid next face - get its corresponding edge for this vertex
				size_t idx = vertexPos - neighborFace.idVertices.begin();
				unsigned int nextEdgeId = neighborFace.idEdges[idx];
				
				// Add face and edge to neighbors (if not already visited)
				v.faceNeighbors.push_back(neighborFaceId);
				visitedFaces.insert(neighborFaceId);
				
				if (visitedEdges.find(nextEdgeId) == visitedEdges.end())
				{
					v.edgeNeighbors.push_back(nextEdgeId);
					visitedEdges.insert(nextEdgeId);
				}
				
				// Update current position and mark that we found a face
				currentFaceId = neighborFaceId;
				currentEdgeId = nextEdgeId;
				foundNextFace = true;
				break;
			}
			
			// Step 4b: If no face found through edge, look for any unvisited face
			if (!foundNextFace)
			{
				for (const auto& f : P.faces)
				{
					// Skip faces we've already processed
					if (visitedFaces.find(f.id) != visitedFaces.end())
						continue;
						
					// Check if face contains our vertex
					auto vertexPos = find(f.idVertices.begin(), f.idVertices.end(), v.id);
					if (vertexPos == f.idVertices.end())
						continue;
						
					// Found an unvisited face - add it and its edge
					size_t idx = vertexPos - f.idVertices.begin();
					unsigned int edgeId = f.idEdges[idx];
					
					v.faceNeighbors.push_back(f.id);
					visitedFaces.insert(f.id);
					
					if (visitedEdges.find(edgeId) == visitedEdges.end())
					{
						v.edgeNeighbors.push_back(edgeId);
						visitedEdges.insert(edgeId);
					}
					
					currentFaceId = f.id;
					currentEdgeId = edgeId;
					foundNextFace = true;
					break;
				}
			}
		} while (foundNextFace); // Continue until no more faces can be found
	}
}

*/


///////////////////////////////////////////////////////////////////////////////////

// VERSIONE ANCORA PIU' VECCHIA

/*

// Function which finds the faces and edges adjacent to each vertex of the polyhedron
void getVertexNeighbors(Polyhedron& P)
{
	// Iterate along the vertices of the Polyhedron
	for (auto& v : P.vertices)
	{
		
		// Get all faces that contain this vertex
		vector<unsigned int> connectedFaces;
		for (const auto& f : P.faces)
		{
			if (find(f.idVertices.begin(), f.idVertices.end(), v.id) != f.idVertices.end())
			{
				connectedFaces.push_back(f.id);
			}
		}
		
		// If there are connected faces
		if (!connectedFaces.empty())
		{
			// Get the first face
			unsigned int currentFace = connectedFaces.front();

			// Get the set of remaining faces	
			set<unsigned int> remainingFaces(connectedFaces.begin(), connectedFaces.end());
			
			// Add the first face
			v.faceNeighbors.push_back(currentFace);
			remainingFaces.erase(currentFace);
			
			// Keep track of visited edges in the current face
			set<unsigned int> processedEdges;
			
			// Process faces until we've found them all
			while (!remainingFaces.empty())
			{
				const Face& face = P.faces[currentFace];
				
				// Find the position of current vertex in this face
				auto vertexPos = find(face.idVertices.begin(), face.idVertices.end(), v.id);
				if (vertexPos != face.idVertices.end())
				{
					// Get the index of the vertex in the face
					size_t idx = vertexPos - face.idVertices.begin();
					
					// Get the edges connected to this vertex in this face
					unsigned int edgeId = face.idEdges[idx];

					// If the edge has not been processed yet
					if (processedEdges.find(edgeId) == processedEdges.end())
					{
						// Add the edge to the vector of edge neighbors
						v.edgeNeighbors.push_back(edgeId);

						// Mark the edge as processed
						processedEdges.insert(edgeId);
					}
					
					// Look for next face through the edges
					const Edge& edge = P.edges[edgeId];
					for (unsigned int neighborFace : edge.faceNeighbors)
					{
						// If the neighbor face is in the set of remaining faces
						if (remainingFaces.find(neighborFace) != remainingFaces.end())
						{
							// Add the neighbor face to the vector of face neighbors
							v.faceNeighbors.push_back(neighborFace);

							// Remove the neighbor face from the set of remaining faces
							remainingFaces.erase(neighborFace);
							currentFace = neighborFace;
							break;
						}
					}
				}
			}
		}
	}
}

*/


// Function that creates the dual of a polyhedron
Polyhedron Dual(const Polyhedron& P)
{
	// Initialize the dual polyhedron
	Polyhedron Q;
	Q.id = P.id + 2;
	
	// Reserve space
	Q.vertices.reserve(P.numFaces());
	Q.edges.reserve(P.numEdges());
	Q.faces.reserve(P.numVertices());
	
	// Create vertices of the dual (one for each face of P)
	for (const auto& f : P.faces)
	{
		Vertex v_dual = Barycenter(P, f.id);
		normalizeVertex(v_dual);
		Q.vertices.push_back(v_dual);
	}
	
	// Create edges of the dual (one for each edge of P)
	for (const auto& e : P.edges)
	{
		// The face neighbors of the edge become the vertices of the dual edge
		addEdgeIfMissing(Q, e.faceNeighbors[0], e.faceNeighbors[1], e.id);
	}
	
	// Create faces of the dual (one for each vertex of P)
	for (const auto& v : P.vertices)
	{
		Face f_dual;
		f_dual.id = v.id;
		
		// Add vertices and edges in the order they appear around the vertex
		// This maintains the ordering required by checkFaces
		for (size_t i = 0; i < v.faceNeighbors.size(); ++i)
		{
			f_dual.idVertices.push_back(v.faceNeighbors[i]);
			f_dual.idEdges.push_back(v.edgeNeighbors[i]);
		}
		
		Q.faces.push_back(f_dual);
	}
	
	return Q;
}

