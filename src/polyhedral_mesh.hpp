#pragma once

#include <iostream>
#include "Eigen/Eigen"

using namespace std;
using namespace Eigen;

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
		
		vector<int> idEdges;
		vector<int> idVertices;
		int numVertices(const vector<int>& idVertices)
		{
			return idVertices.size();
		}
		int numEdges(const vector<int>& idVertices)
		{
			return idEdges.size();
		}
	};

	// Struct which stores the ID of each Polyhedron,
	struct Polyhedron
	{          
		int id;
		vector<Vertex> vertices;
		vector<Edge> edges;
		vector<Face> faces;
		int numVertices() const {return vertices.size();}
		int numEdges() const {return edges.size();}
		int numFaces() const {return faces.size();}

		bool checkFaces() const {
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
				int currentEdgeEnd = (edge.origin == idVertex) ? edge.end : edge.origin; // scrivi con if else
					// condizione ? valore_se_vero : valore_se_falso
				if (currentEdgeEnd != idVertexNext) {
					cerr << "Error: edge-edge discontinuity" << endl;
					return false;}
			}
		}
		
		return true;
	}
};


}