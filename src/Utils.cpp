#include "Utils.hpp"

using namespace std;
using namespace Eigen;


//Function that checks input values
bool check_input(int argc, char* argv[],
                   unsigned int &p, unsigned int &q,
                   unsigned int &b, unsigned int &c,
                   unsigned int &val, unsigned int &flag)
{

	// Get correct number of in puts
    if((argc != 7) && (argc != 5))
	{
        cerr << "Number of inputs is not compatible with program execution" << endl;
        return false;
    }

	// Get value of p and check if it's allowed
    istringstream convert_p(argv[1]); 
    if(!(convert_p >> p) || (p < 3) || (p > 5))
	{
        cerr << "Wrong value for p" << endl;
        return false;
    }

	// Get value of q and check if it's allowed
    istringstream convert_q(argv[2]);
    if(!(convert_q >> q) || (q < 3) || (q > 5))
	{
        cerr << "Wrong value for q" << endl;
        return false;
    }

	// Check if p and q are compatible
    if((p == 3 && (q == 3 || q == 4 || q == 5)) ||
        (q == 3 && (p == 3 || p == 4 || p == 5)))
		{
        cout << "p: " << p << endl;
        cout << "q: " << q << endl;
    }
	else
	{
        cerr << "p and q are not compatible" << endl;
        return false;
    }

	// Get value of b
    istringstream convert_b(argv[3]);
    if(!(convert_b >> b))
	{
        cerr << "Wrong value for b" << endl;
        return false;
    }

	// Get value of c
    istringstream convert_c(argv[4]);
    if(!(convert_c >> c))
	{
        cerr << "Wrong value for c" << endl;
        return false;
    }

	// Check which triangulation class is requested
    if(((b == 0) && (c != 0)) || ((b != 0) && (c == 0)))
	{
        cout << "b: " << b << endl;
        cout << "c: " << c << endl;
        val = (b != 0) ? b : c; // val is the the non-zero value between b and c
        cout << "Class I with parameter: " << val << endl;
        flag = 1;
    }
    else if((b == c) && (b != 0))
	{
        cout << "b: " << b << endl;
        cout << "c: " << c << endl;
        val = b;
        cout << "Class II with parameter: " << val << endl;
        flag = 2;
    }
    else
	{
        cerr << "b and c are not compatible" << endl;
        return false;
    }

    return true;
}


// Function that constructs a tetrahedron represented as a Polyhedron
Polyhedron Tetrahedron()
{
	// Initialize polyhedron struct and set the ID
	Polyhedron P;
	P.id = 0;

	// Allocate memory for vertices
	P.vertices.reserve(4);

	// Set (non normalized) vertices
	P.vertices = {
		{0,{1,1,1}},
		{1,{-1,-1,1}},
		{2,{-1,1,-1}},
		{3,{1,-1,-1}}
	};

	// Normalize vertices to lie on unit sphere
	for(Vertex& v : P.vertices)
	{
		normalizeVertex(v);
	}

	// Set values of edges
	P.edges = {
		{0,0,1}, {1,1,2}, {2,2,0},
		{3,0,3}, {4,3,1}, {5,3,2}
	};

	// Set values of faces
	P.faces = {
		{0, {0,1,2}, {0,1,2}},
		{1, {0,3,2}, {3,5,2}},
		{2, {0,1,3}, {0,4,3}},
		{3, {1,2,3}, {1,5,4}}
	};

	return P;
}       

// Function that constructs an octahedron represented as a Polyhedron
Polyhedron Octahedron()
{
	// Initialize polyhedron struct and set the ID
	Polyhedron P;
	P.id = 1;

	// Set (already normalized) vertices
	P.vertices = {
		{0,{1,0,0}},
		{1,{-1,0,0}},
		{2,{0,1,0}},
		{3,{0,-1,0}},
		{4,{0,0,1}},
		{5,{0,0,-1}}
	};

	// Set values of edges
	P.edges = {
		{0,0,2}, {1,2,1}, {2,1,3}, {3,3,0},
		{4,0,4}, {5,2,4}, {6,1,4}, {7,3,4},
		{8,0,5}, {9,2,5}, {10,1,5}, {11,3,5}
	};

	// Set values of faces
	P.faces = {
		{0, {0,2,4}, {0,5,4}},
		{1, {0,4,3}, {4,7,3}},
		{2, {4,3,1}, {7,2,6}},
		{3, {4,1,2}, {6,1,5}},
		{4, {5,1,2}, {10,1,9}},
		{5, {5,2,0}, {9,0,8}},
		{6, {0,5,3}, {8,11,3}},
		{7, {3,5,1}, {11,10,2}}
	};

	return P;
}

// Function that constructs an icosahedron represented as a Polyhedron
Polyhedron Icosahedron()
{
	// Initialize polyhedron struct and set the ID
	Polyhedron P;
	P.id = 2;

	using std::numbers::phi;

	// Set (non normalized) vertices
	P.vertices = {
		{0,{-1,phi,0}},
		{1,{1,phi,0}},
		{2,{-1,-phi,0}},
		{3,{1,-phi,0}},
		{4,{0,-1,phi}},
		{5,{0,1,phi}},
		{6,{0,-1,-phi}},
		{7,{0,1,-phi}},
		{8,{phi,0,-1}},
		{9,{phi,0,1}},
		{10,{-phi,0,-1}},
		{11,{-phi,0,1}}
	};

	// Normalize vertices to lie on unit sphere
	for(Vertex& v : P.vertices)
	{
		normalizeVertex(v);
	}

	// Set values of edges
	P.edges = {
		{0,0,5}, {1,0,1}, {2,0,11}, {3,0,10}, {4,0,7},
		{5,1,5}, {6,1,7}, {7,1,8}, {8,1,9}, {9,5,9},
		{10,5,11}, {11,9,8}, {12,8,7}, {13,9,4}, {14,9,3},
		{15,4,3}, {16,5,4}, {17,4,11}, {18,2,4}, {19,2,11},
		{20,2,3}, {21,2,6}, {22,6,3}, {23,8,3}, {24,8,6},
		{25,7,6}, {26,2,10}, {27,10,6}, {28,10,7}, {29,11,10}
	};

	// Set values of faces
	P.faces = {
		{0, {5,0,11}, {0,2,10}},
		{1, {0,5,1}, {0,5,1}},
		{2, {5,1,9}, {5,8,9}},
		{3, {5,4,9}, {16,13,9}},
		{4, {4,5,11}, {16,10,17}},
		{5, {4,3,9}, {15,14,13}},
		{6, {4,11,2}, {17,19,18}},
		{7, {2,3,6}, {20,22,21}},
		{8, {6,2,10}, {21,26,27}},
		{9, {3,8,6}, {23,24,22}},
		{10, {8,9,3}, {11,14,23}},
		{11, {9,8,1}, {11,7,8}},
		{12, {8,7,1}, {12,6,7}},
		{13, {6,7,8}, {25,12,24}},
		{14, {7,10,6}, {28,27,25}},
		{15, {7,10,0}, {28,3,4}},
		{16, {0,10,11}, {3,29,2}},
		{17, {4,2,3}, {18,20,15}},
		{18, {1,0,7}, {1,4,6}},
		{19, {11,2,10}, {19,26,29}}
	};

	return P;
}


// Function which allows to export a polyhedron for Paraview
void exportPolyhedron(const Polyhedron& P)
{
	// Initialize matrix of vertex coordinates
	MatrixXd coordsCell0D;
	coordsCell0D = MatrixXd::Zero(3, P.numVertices());

	// Fill the matrix with the correct values
	for(const auto& v : P.vertices)
	{
		coordsCell0D.col(v.id) << v.coords;
	}

	// Initialize matrix of edge IDs
	MatrixXi extremaCell1D;
	extremaCell1D = MatrixXi::Zero(2, P.numEdges());

	// Fill the matrix with the correct values
	for(const auto& e : P.edges)
	{
		// Use the ID of the edge as the index
		unsigned int id = e.id;

		// Get IDs of extremas
		extremaCell1D(0, id) = e.origin;
		extremaCell1D(1, id) = e.end;
	}

	// Export in the correct format
	Gedim::UCDUtilities utilities;
	utilities.ExportPoints("./Cell0Ds.inp",
						   coordsCell0D);

	utilities.ExportSegments("./Cell1Ds.inp",
							 coordsCell0D,
							 extremaCell1D);

}

