#include "Utils.hpp"
#include "Triangle.hpp"
#include "Geometry.hpp"


using namespace std;


// To pass parameters to main the standard syntax is:
// argc: number of arguments
// argv: array of arguments
// The first argument is always the executable file's name

int main(int argc, char *argv[])
{

	// Initialize variables
	unsigned int p; // number of edges of each face of the chosen platonic solid
	unsigned int q; // number of faces which meet in each vertex of the solid
	unsigned int b; // subdivision parameter
	unsigned int c; // subdivision parameter

	// Auxiliary variables
	unsigned int val;
	unsigned int flag;

	// Check input
	if (!check_input(argc, argv, p, q, b, c, val, flag))
	{
        return 1;
	}


	// Initialize the polyhedron
	Polyhedron initial_P;
	Polyhedron P;

	// Create the correct platonic solid to start from
	if((p == 3) && (q == 3))
	{
		initial_P = Tetrahedron();
	} 
	else if(((p == 3) && (q == 4)) || ((p == 4) && (q == 3)))
	{
		initial_P = Octahedron();
	} 
	else if(((p == 3) && (q == 5)) || ((p == 5) && (q == 3)))
	{
		initial_P = Icosahedron();
	}


	// Triangulate the faces of the polyhedron 
	if(flag == 1)
	{
		P = TriangleClassI(initial_P, val);
	}
	else if (flag == 2)
	{
		// TriangleClassII(P, val);
	}
	else
	{
		cerr << "Something went wrong... (flag error)" << endl;
		return 1;
	}
	
	// Projection on the sphere
	for(auto& v : P.vertices)
	{
		normalizeVertex(v);
	}
	
	// Get neighbors of each vertex and edge
	getVertexNeighbors(P);
	getEdgeNeighbors(P);

	

	// Shortest path
	
	// Create graph
	
	

	// Initialize variables
	unsigned int id_path_start; // ID of starting vertex
	unsigned int id_path_end; // ID of ending vertex
	
	// (da spostare dentro la funzione)

	// Get ID of starting vertex for shortest path
	if(argc == 7)
	{
		// Get value of id_path_start
		istringstream convert_start(argv[5]);
		if(!(convert_start >> id_path_start))
		{
			cerr << "Wrong value for starting ID" << endl;
			return 1;
		}

		// Get value of id_path_end
		istringstream convert_end(argv[6]);
		if(!(convert_end >> id_path_end))
		{
			cerr << "Wrong value for ending ID" << endl;
			return 1;
		}

		// Check if the IDs are valid
		// (da completare)

	}


	// Create the dual polyhedron, if needed
	if(p != 3)
	{
		Polyhedron Q = Dual(P);
		exportPolyhedron(Q);
	}
	else
	{
		// Export the polyhedron
		exportPolyhedron(P);
	}



	// Write output files
	if(!writeOutput(P))
	{
		return 1;
	}

	return 0;
	
}