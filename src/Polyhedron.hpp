#pragma once

#include <iostream>
#include <vector>

using namespace std;


namespace PolyhedralLibrary {


	// Struct which stores the ID of each vertex and its coordinates
	struct Vertex
	{
		int id;
		double x;
		double y;
		double z;
		int shortPath = 0;
	};

	// Struct which stores the ID of each edge and the IDs of its extrema
	struct Edge
	{
		int id;
		int origin;
		int end;
		int shortPath = 0;
	};

	// Struct which stores the ID of each polygon, the IDs of its vertices and edges,
		// and the number of vertices and edges
	struct Face
	{
		int id;
		vector<int> idVertices;
		vector<int> idEdges;
		int numVertices() const
		{
			return idVertices.size();
		}
		int numEdges() const
		{
			return idEdges.size();
		}
	};

	// Struct which stores the ID of each Polyhedron
	struct Polyhedron
	{
		int id;
		vector<Vertex> vertices;
		vector<Edge> edges;
		vector<Face> faces;
		int numVertices() const
		{
			return vertices.size();
		}
		int numEdges() const{
			return edges.size();
		}
		int numFaces() const
		{
			return faces.size();
		}
	
		bool checkFaces() const
		{
			for (const Face& face : faces) {
				int E = face.numEdges(); // = 3
				for (int e = 0; e < E; ++e) {
					int idEdge = face.idEdges[e];
					int idVertex = face.idVertices[e];
					const Edge& edge = edges[idEdge];
					// vertice = inizio o fine del lato
					if (edge.origin != idVertex && edge.end != idVertex) {
						cerr << "Error: vertex-edge mismatch" << endl;
						return false;}
					// connesione tra 2 edge consecutivi
					int idVertexNext = face.idVertices[(e + 1) % E];
					int currentEdgeEnd;
					if (edge.origin == idVertex) {
						currentEdgeEnd = edge.end;
					} else {
						currentEdgeEnd = edge.origin;
					}
					if (currentEdgeEnd != idVertexNext) {
						cerr << "Error: edge-edge discontinuity" << endl;
						return false;}
				}
			}
			return true;
		}
	};

}