#pragma once

#include <iostream>
#include <vector>

using namespace std;


namespace PolyhedralLibrary {


	// Struct which stores the ID of each vertex and its coordinates
	struct Vertex
	{
		unsigned int id;
		double x;
		double y;
		double z;
		bool shortPath = 0;
	};

	// Struct which stores the ID of each edge and the IDs of its extrema
	struct Edge
	{
		unsigned int id;
		unsigned int origin;
		unsigned int end;
		bool shortPath = 0;
	};

	// Struct which stores the ID of each polygon, the IDs of its vertices and edges,
		// and the number of vertices and edges
	struct Face
	{
		unsigned int id;
		vector<int> idVertices;
		vector<int> idEdges;

		// Method which returns number of vertices of a face
		int numVertices() const
		{
			return idVertices.size();
		}

		// Method which returns number of edges of a face
		int numEdges() const
		{
			return idEdges.size();
		}
	};

	// Struct which stores the ID of each Polyhedron
	struct Polyhedron
	{
		unsigned int id;
		vector<Vertex> vertices;
		vector<Edge> edges;
		vector<Face> faces;

		// Method which returns number of vertices of a polyhedron
		int numVertices() const
		{
			return vertices.size();
		}

		// Method which returns number of edges of a polyhedron
		int numEdges() const{
			return edges.size();
		}

		// Method which returns number of faces of a polyhedron
		int numFaces() const
		{
			return faces.size();
		}
	
		// Method which checks if the vertices and edges of the faces are coherent
		bool checkFaces() const
		{
			// Iterate for all of the polyhedron's faces
			for (const Face& face : faces)
			{
				// Get number of edges and vertices
				// (for this project we expect this value to be always 3)
				int E = face.numEdges();
				int V = face.numVertices();

				// Check if they are the same
				if(E != V)
				{
					cerr << "Mismatch number of edges and vertices" << endl;
					return false;
				}

				// Iterate along each vector of IDs
				for (size_t e = 0; e < E; ++e)
				{
					// Get IDs of first edge and vertex
					int idEdge = face.idEdges[e];
					int idVertex = face.idVertices[e];

					// Cosa fa questo?
					const Edge& edge = edges[idEdge];

					// The ID of the first vertex must be either the origin or end
					// of the first edge
					if (edge.origin != idVertex && edge.end != idVertex)
					{
						cerr << "Error: vertex-edge mismatch" << endl;
						return false;
					}

					// Temporary variables to store IDs
					int idVertexNext = face.idVertices[(e + 1) % E];
					int currentEdgeEnd;

					//
					if (edge.origin == idVertex)
					{
						currentEdgeEnd = edge.end;
					}
					else
					{
						currentEdgeEnd = edge.origin;
					}

					//
					if (currentEdgeEnd != idVertexNext)
					{
						cerr << "Error: edge-edge discontinuity" << endl;
						return false;
					}
				}
			}
			return true;
		}
	};

}