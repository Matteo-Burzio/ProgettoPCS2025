#include "Utils.hpp"


using namespace std;
using namespace Eigen;


// Function which adds missing vertices
unsigned int addVertexIfMissing(Polyhedron& P, const Vector3d coords_V)
{
	// Get machine precision
	const double eps = numeric_limits<double>::epsilon();

	// Iterate along existing vertices
	for(const auto& existing : P.vertices)
	{
		// Check if the vertex already exists
		if(coords_V.isApprox(existing.coords, eps))
		{
			// If it does, return its ID
			return existing.id;
		}
	}

	// Create the vertex if it doesn't exist yet
	Vertex v_new;
	
	// Set coordinates
	v_new.coords = coords_V;

	// Set correct ID (first available number)
	v_new.id = P.numVertices();

	// Add it to the polyhedron
	P.vertices.push_back(v_new);

	return v_new.id;
}


// Function which adds missing edges
unsigned int addEdgeIfMissing(Polyhedron& P, unsigned int id1, unsigned int id2)
{
	// Check if vertices exists in the polyhedron
	if (id1 >= P.numVertices() || id2 >= P.numVertices())
	{
		cerr << "Error: invalid edge" << endl;
		return -1;
	}
	
	// Check if the edge is valid
	if (id1 == id2)
	{
		cerr << "Error: invalid edge" << endl;
		return -1;
	}
	
	
	// Iterate along existing edges
	for(const auto& existing : P.edges)
	{
		// Check su id1 == id2 e su id1||id2 >= P.numVertices() ??
		
		// Check if the edge already exists
		if(((existing.origin == id1) && (existing.end == id2)) ||
			((existing.origin == id2) && (existing.end == id1)))
		{
			// If it does, return its ID
			return existing.id;
		}
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
	
	return e_new.id;
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
				// Compute new vertex coordinates
				Vector3d coords_V = (i * A.coords + j * B.coords + (val - i - j) * C.coords) / val;

				// If the vertex doesn't exist, add it
				unsigned int id_V = addVertexIfMissing(P, coords_V);
				
				// Save V's ID and indices in the map
				Vij.insert({{i, j}, id_V});
			}
		}
		
		// Create new edges and faces

		for(unsigned int i = 0; i <= val - 1; i++)
		{
			for(unsigned int j = 0; j <= val - 1 - i; j++)
			{
				// Add the "upside triangles"
				
				// Get IDs of the three vertices
				unsigned int id0v = Vij[{i, j}];
				unsigned int id1v = Vij[{i + 1, j}];
				unsigned int id2v = Vij[{i, j + 1}];
				
				// Add edges to the polyhedron
				unsigned int id0e0 = addEdgeIfMissing(P, id0v, id1v);
				unsigned int id1e0 = addEdgeIfMissing(P, id1v, id2v);
				unsigned int id2e0 = addEdgeIfMissing(P, id2v, id0v);

				// Initialize face
				Face f0;

				// ID is first available number
				f0.id = P.numFaces();

				// Add vertices to the face
				f0.idVertices = {id0v, id1v, id2v};

				// Add edges to the face
				f0.idEdges = {id0e0, id1e0, id2e0};
				
				// Add the face to the polyhedron
				P.faces.push_back(f0);
				
				// Check if the polyhedron is still coherent
				if (!P.checkFaces())
				{
					// If not, remove the face from the polyhedron and print error
					P.faces.pop_back();
					cerr << "Error: invalid polyhedron" << endl;

				}
				
				// Add the "downside triangles"
				
				if (i + j <= val - 2)
				{
					// Get ID of the other vertex
					unsigned int id3v = Vij[{i + 1, j + 1}];
				
					// Get IDs of the edges
					unsigned int id0e1 = addEdgeIfMissing(P, id1v, id2v);
					unsigned int id1e1 = addEdgeIfMissing(P, id2v, id3v);
					unsigned int id2e1 = addEdgeIfMissing(P, id3v, id1v);
				
					// Initialize face
					Face f1;
					
					// ID is first available number
					f1.id = P.numFaces();
				
					// Add vertices to the face
					f1.idVertices = {id1v, id2v, id3v};
					
					// Add edges to the face
					f1.idEdges = {id0e1, id1e1, id2e1};
				
					// Add the face to the polyhedron
					P.faces.push_back(f1);
				
					// Check if the polyhedron is still coherent
					if (!P.checkFaces())
					{
						// If not, remove the face from the polyhedron and print error
						P.faces.pop_back();
						cerr << "Error: invalid polyhedron" << endl;

					}
				}
			}
		}
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