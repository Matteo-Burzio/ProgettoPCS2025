#include "Utils.hpp"

using namespace std;
using namespace Eigen;


// Function which adds missing vertices
unsigned int addVertexIfMissing(Polyhedron& P, const Vertex& v)
{
	// Get machine precision
	const double eps = numeric_limits<double>::epsilon();

	// Iterate along existing vertices
	for(const auto& existing : P.vertices)
	{
		// Check if the vertex already exists
		if(v.coords.isApprox(existing.coords, eps))
		{
			// If yes, return its ID
			return existing.id;
		}
	}

	// Create the vertex if it doesn't exist yet
	Vertex v_new = v;

	// Set correct ID (first available number)
	v_new.id = P.numVertices();

	// Add it to the polyhedron
	P.vertices.push_back(v_new);

	return v_new.id;
}


// function which add missing edges
void addEdgeIfMissing(Polyhedron& P, unsigned int id1, unsigned int id2)
{
	for(const auto& existing : P.edges)
	{
		if(((existing.origin == id1) && (existing.end == id2)) ||
			((existing.origin == id2) && (existing.end == id1)))
		{
			// Exit from the function (edge already exists)
			return;
		}

		// Create the edge if it doesn't exist yet
		Edge e_new;

		// Set correct ID (first available number)
		e_new.id = P.numEdges();

		// Set origin and end to current vertices
		e_new.origin = id1;
		e_new.end = id2;

		// Add it to the polyhedron
		P.edges.push_back(e_new);
	}
}


// // Function that checks if the new edge already exists in the Polyhedron
// bool checkEdge(const Polyhedron& P, const Edge& e)
// {
// 	// Check if vertices exist
// 	if (e.origin >= P.numVertices() || e.end >= P.numVertices())
// 	{
// 		return false;
// 	}
		
// 	// Check that the edge is valid
// 	if (e.origin == e.end)
// 	{
// 		return false;
// 	}

// 	// Iterate along edges to check if it doesn't exist yet
// 	for(const auto& current : P.edges)
// 	{
// 		// Check if it's the same
// 		if ((current.origin == e.origin && current.end == e.end) ||
// 			(current.origin == e.end && current.end == e.origin))
// 		{
// 			return false; // The new edge already exists
// 		}
// 	}
	
// 	return true;
// }


// // Function that adds a new edge to the polyhedron
// void addEdge(Polyhedron& P, Edge& e)
// {
// 	// ID of new edge is the first available natural number
// 	e.id = P.numEdges();

// 	// Add the new edge to P
// 	P.edges.push_back(e);
// }


// unsigned int findEdge(const Polyhedron& P, const Edge& e)
// {
// 	// Get machine precision
// 	const double eps = numeric_limits<double>::epsilon();

// 	for(const auto& current : P.edges)
// 	{
// 		if(((current.origin == e.origin) && (current.end == e.end)) ||
// 		((current.origin == e.end) && (curren.end == e.origin)))
// 		{
// 			return current.id;
// 		}
// 	}

// 	return 0;
// }

// Function that checks if the new face already exists in the Polyhedron
bool checkFace(const Polyhedron& P, const Face& f)
{
	// Order the vertices ID of f
	vector<unsigned int> id_Vertices = f.idVertices;
	sort(id_Vertices.begin(), id_Vertices.end());
	
	// Iterate along faces to check if it doesn't exist yet
	for (const auto& face : P.faces)
	{
		vector<unsigned int> existingVertices = face.idVertices;
		sort(existingVertices.begin(), existingVertices.end());

		if (existingVertices == id_Vertices)
		{
			return false; // The new face already exists
		}
	}

	return true;
}


// Function that adds a new face to the polyhedron
void addFace(Polyhedron& P, Face& f)
{
	// ID of new face is the first available natural number
	f.id = P.faces.size();
	
	// Add the new face to P
	P.faces.push_back(f);
	
	// Check if the polyhedron is still coherent
	if (!P.checkFaces()) {
		
		// If not, remove the face from the polyhedron and print error
		P.faces.pop_back();
		cerr << "Errore: la faccia aggiunta ha reso il poliedro non valido" << endl;
		
		}
}


// Function for Class I triangulation of a polyhedron with parameter val (val > 0)
Polyhedron TriangleClassI(const Polyhedron& P_old, const unsigned int& val)
{
	// Initialize a new polyhedron
	Polyhedron P;
	
	// Allocate the correct amount of space for the polyhedron

	// Temporary variable
	unsigned int T = val * val;

	// Tetrahedron
	if(P_old.numVertices() == 4)
	{
		P.vertices.reserve(2 * T + 2);
		P.edges.reserve(6 * T);
		P.faces.reserve(4 * T);
	}
	// Octahedron
	else if (P_old.numVertices() == 6)
	{
		P.vertices.reserve(4 * T + 2);
		P.edges.reserve(12 * T);
		P.faces.reserve(8 * T);
	}
	// Icosahedron
	else
	{
		P.vertices.reserve(10 * T + 2);
		P.edges.reserve(30 * T);
		P.faces.reserve(20 * T);
	}


	// Iterate along faces of the platonic solid
	for(const auto& face : P_old.faces)
	{
		// We expect all faces to be triangles
		// Get IDs and a reference of each vertex of the face
		unsigned int id_A = face.idVertices[0];
		const Vertex& A = P_old.vertices[id_A];
		
		unsigned int id_B = face.idVertices[1];
		const Vertex& B = P_old.vertices[id_B];
		
		unsigned int id_C = face.idVertices[2];
		const Vertex& C = P_old.vertices[id_C];
		
		
		// Create new vertices

		// Map that associates (i,j) indices with vertices' IDs
		map<pair<unsigned int, unsigned int>, unsigned int> Vij;

		// (i,j) are the barycentric coordinates
		for(unsigned int i = 0; i <= val; i++)
		{
			for(unsigned int j = 0; j <= val - i; j++)
			{
				// Initialize a vertex
				Vertex V;

				// Set the vertex's coordinates
				V.coords = (i * A.coords + j * B.coords + (val - i - j) * C.coords) / val;

				// If the vertex doesn't exist, add it
				V.id = addVertexIfMissing(P, V);
				
				// Save V's ID and indices
				Vij.insert({{i, j}, V.id});
			}
		}
		
		// Create new edges

		for(unsigned int i = 0; i <= val; i++)
		{
			for(unsigned int j = 0; j <= val - i; j++)
			{
				// Get IDs of the three vertices
				unsigned int id0 = Vij[{i, j}];
				unsigned int id1 = Vij[{i + 1, j}];
				unsigned int id2 = Vij[{i, j + 1}];

				// Initialize face
				Face f1;

				// ID is first available number
				f1.id = P.numFaces();

				// Add vertices
				f1.idVertices = {id0, id1, id2};

				P.faces.push_back(f1);

				// Add the three edges
				addEdgeIfMissing(P, id0, id1);
				addEdgeIfMissing(P, id1, id2);
				addEdgeIfMissing(P, id2, id0);

				if (i + j < val - 1)
				{
					// Get ID of the vertex
					unsigned int id3 = Vij[{i + 1, j + 1}];

					// Initialize face
					Face f2;

					f2.id = P.numFaces();

					f2.idVertices = {id1, id3, id2};

					P.faces.push_back(f2);
					addEdgeIfMissing(P, id1, id3);
					addEdgeIfMissing(P, id3, id2);
					addEdgeIfMissing(P, id2, id1);

					// da sistemare/capire... 
				}
			}
		}

















		
		// for (const auto& [id1, indices1] : Vij)
		// {
		// 	for (const auto& [id2, indices2] : Vij)
		// 	{
		// 		// Avoid checking pairs of vertices twice
		// 		if (id1 >= id2) continue;
				
		// 		// Read (i,j) indices for each vertex
		// 		unsigned int i1 = indices1.first;
		// 		unsigned int j1 = indices1.second;
		// 		unsigned int i2 = indices2.first;
		// 		unsigned int j2 = indices2.second;

		// 		// Check if the vertices are adjacent on the triangular grid
		// 		if (abs((int)i1 - (int)i2) <= 1 && abs((int)j1 - (int)j2) <= 1)
		// 		{
		// 			// Initialize an edge
		// 			Edge E;

		// 			// Set its origin and end as current pair of vertices
		// 			E.origin = id1;
		// 			E.end = id2;

		// 			// // Check if the edge already exists
		// 			// if(checkEdge(P, E))
		// 			// {
		// 			// 	// If not:
		// 			// 	// Add the edge to the polyhedron giving it a new ID
		// 			// 	addEdge(P, E);
		// 			// }


		// 			// Check if the edge already exists
	
		// 			// valid? end == origin?
		
		// 			// Iterate along edges to check if it doesn't exist yet
		// 			for(const auto& current : P.edges)
		// 			{
		// 				// Check if it's the same
		// 				if (!((current.origin == E.origin && current.end == E.end) ||
		// 					(current.origin == E.end && current.end == E.origin)))
		// 				{
		// 					//If not:
		// 					// ID of new edge is the first available natural number
		// 					E.id = P.numEdges();
							
		// 					// Add the new edge to P
		// 					P.edges.push_back(E);
		// 				}
		// 			}
		// 		}
		// 	}
		// }
		
		// Create new faces
				
				
				

				

			
		
	}

	return P;

}





/*


// Function for Class II triangulation of a polyhedron with parameter a (b = c =: a > 0)
Polyhedron TriangleClassII(const Polyhedron& P_old, const unsigned int& val)
{

	return P;
}



*/