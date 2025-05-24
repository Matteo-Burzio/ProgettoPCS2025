#include "Utils.hpp"

using namespace std;
using namespace Eigen;


// Function that checks if the new vertex already exists in the Polyhedron
bool checkVertex(const Polyhedron& P, const Vertex& v)
{
	// Get machine precision
	const double eps = numeric_limits<double>::epsilon();
	
	// Iterate along vertices to check if it doesn't exist yet
	for(const auto& existing : P.vertices)
	{
		// Check if it's the same
		if (v.coords.isApprox(existing.coords, eps))
		{
			return false; // The new vertex already exists
		}

	}

	return true;
}


// Function that adds a new vertex to the polyhedron
void addVertex(Polyhedron& P, Vertex& v)
{
	// ID of new vertex is the first available natural number
	v.id = P.numVertices();

	// Add the new vertex to P
	P.vertices.push_back(v);
}


// Function that finds the ID of a vertex in a polyhedron
unsigned int findVertex(const Polyhedron& P, const Vertex& v)
{
	// Get machine precision
	const double eps = numeric_limits<double>::epsilon();

	for(const auto& current : P.vertices)
	{
		if(current.coords.isApprox(v.coords, eps))
		{
			return current.id;
		}
	}

	// for (unsigned int i = 0; i < P.vertices.size(); ++i)
	// {
	// 	if (P.vertices[i].coords.isApprox(v.coords, eps))
	// 	{
	// 		return i;
	// 	}
	// }

	return 0;
}


// Function that checks if the new edge already exists in the Polyhedron
bool checkEdge(const Polyhedron& P, const Edge& e)
{
	// Check if vertices exist
	if (e.origin >= P.numVertices() || e.end >= P.numVertices())
	{
		return false;
	}
		
	// Check that the edge is valid
	if (e.origin == e.end)
	{
		return false;
	}

	// Iterate along edges to check if it doesn't exist yet
	for(const auto& current : P.edges)
	{
		// Check if it's the same
		if ((current.origin == e.origin && current.end == e.end) ||
			(current.origin == e.end && current.end == e.origin))
		{
			return false; // The new edge already exists
		}
	}
	
	return true;
}


// Function that adds a new edge to the polyhedron
void addEdge(Polyhedron& P, Edge& e)
{
	// ID of new edge is the first available natural number
	e.id = P.numEdges();

	// Add the new edge to P
	P.edges.push_back(e);
}


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

		// Map that associates vertices' IDs with (i,j) indices
		map<unsigned int, pair<unsigned int, unsigned int>> Vij;

		for (size_t i = 0; i <= val; i++)
		{
			for (size_t j = 0; j <= val - i; j++)
			{
				// Initialize a vertex
				Vertex V;

				// Set the vertex's coordinates
				V.coords = (i * A.coords + j * B.coords + (val - i - j) * C.coords) / val;

				// Check if the vertex already exists
				if (checkVertex(P,V))
				{
					// If not:
					// Add the vertex to the polyhedron giving it a new ID
					addVertex(P,V);
				}

				// If the vertex already exists, give V its ID
				V.id = findVertex(P, V);

				Vij.insert({V.id, {i, j}});
			}
		}
		
		// Create new edges
		
		for (const auto& [id1, indices1] : Vij)
		{
			for (const auto& [id2, indices2] : Vij)
			{
				// Avoid checking pairs of vertices twice
				if (id1 >= id2) continue;
				
				// Read (i,j) indices for each vertex
				unsigned int i1 = indices1.first;
				unsigned int j1 = indices1.second;
				unsigned int i2 = indices2.first;
				unsigned int j2 = indices2.second;

				// Condizione di adiacenza (sono vicini sulla griglia triangolare)
				if (abs((int)i1 - (int)i2) <= 1 && abs((int)j1 - (int)j2) <= 1)
				{
					Edge E = {0, id1, id2};
					// Crea un edge tra id1 e id2
					if(checkEdge(P, E))
					{
						addEdge(P, E);
					}
				}
			}
		}
		
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