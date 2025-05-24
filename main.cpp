#include "Utils.hpp"


using namespace std;


// To pass parameters to main the standard syntax is:
// argc: number of arguments
// argv: array of arguments
// The first argument is always the executable file's name

int main(int argc, char *argv[])
{

	
	// // Initialize variables
	// unsigned int p; // number of edges of each face of the chosen platonic solid
	// unsigned int q; // number of faces which meet in each vertex of the solid
	// unsigned int b; // subdivision parameter
	// unsigned int c; // subdivision parameter
	// unsigned int id_path_start; // ID of starting vertex
	// unsigned int id_path_end; // ID of ending vertex
	unsigned int p, q, b, c, val, flag;
	unsigned int id_path_start, id_path_end; 
	if (!check_input(argc, argv, p, q, b, c, val, flag))
		{
        return 1;
		}

	// Initialize the polyhedron
	Polyhedron P;

	// Create the correct platonic solid to start from
	if((p == 3) && (q == 3))
	{
		P = Tetrahedron();
	} 
	else if(((p == 3) && (q == 4)) || ((p == 4) && (q == 3)))
	{
		P = Octahedron();
	} 
	else if(((p == 3) && (q == 5)) || ((p == 5) && (q == 3)))
	{
		P = Icosahedron();
	}

	// Triangulate the faces of the polyhedron 
	if(flag == 1)
	{
		// TriangleClassI(P, val);
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


	// Create the dual polyhedron
	if(p != 3)
	{
		// dual function
	}
	

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


	// Export for Paraview
	exportPolyhedron(P);


	return 0;
	
}