#include "Utils.hpp"
#include "Geometry.hpp"

using namespace std;
using namespace Eigen;


//Function that checks polyhedron input values
bool checkPolyhedronInput(int argc, char* argv[],
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


// Function that checks graph input values
bool checkGraphInput(char* argv[],
					unsigned int& id_path_start, 
					unsigned int& id_path_end, 
					const Polyhedron& P)
{
	// Get value of id_path_start
	istringstream convert_start(argv[5]);
	if(!(convert_start >> id_path_start))
	{
		cerr << "Wrong value for starting ID" << endl;
		return false;
	}

	// Get value of id_path_end
	istringstream convert_end(argv[6]);
	if(!(convert_end >> id_path_end))
	{
		cerr << "Wrong value for ending ID" << endl;
		return false;
	}

	// Check if inputs are coherent
	if ((id_path_start > P.numVertices()) || (id_path_end > P.numVertices()))
	{
		cerr << "Out of bounds IDs" << endl;
		return false;
	}
	else if(id_path_start == id_path_end)
	{
		cerr << "Error: starting and ending IDs are equal" << endl;
		return false;
	}

	// Print input values
	cout << "Starting ID: " << id_path_start <<endl;
	cout << "Ending ID: " << id_path_end << endl;


	return true;
}


// Function that constructs a tetrahedron represented as a Polyhedron
Polyhedron Tetrahedron()
{
	// Initialize polyhedron struct and set the ID
	Polyhedron P;
	P.id = 0;

	// Set (non normalized) vertices
	P.vertices = {
		{0,{1,1,1}, {0,0,0}, {0,0,0}},
		{1,{-1,-1,1}, {0,0,0}, {0,0,0}},
		{2,{-1,1,-1}, {0,0,0}, {0,0,0}},
		{3,{1,-1,-1}, {0,0,0}, {0,0,0}}
	};

	// Normalize vertices to lie on unit sphere
	for(Vertex& v : P.vertices)
	{
		normalizeVertex(v);
	}

	// Set values of edges
	P.edges = {
		{0,0,1, {0,0}}, {1,1,2, {0,0}}, {2,2,0, {0,0}},
		{3,0,3, {0,0}}, {4,3,1, {0,0}}, {5,3,2, {0,0}}
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
		{0,{1,0,0}, {0,0,0,0}, {0,0,0,0}},
		{1,{-1,0,0}, {0,0,0,0}, {0,0,0,0}},
		{2,{0,1,0}, {0,0,0,0}, {0,0,0,0}},
		{3,{0,-1,0}, {0,0,0,0}, {0,0,0,0}},
		{4,{0,0,1}, {0,0,0,0}, {0,0,0,0}},
		{5,{0,0,-1}, {0,0,0,0}, {0,0,0,0}}
	};

	// Set values of edges
	P.edges = {
		{0,0,2, {0,0}}, {1,2,1, {0,0}}, {2,1,3, {0,0}}, {3,3,0, {0,0}},
		{4,0,4, {0,0}}, {5,2,4, {0,0}}, {6,1,4, {0,0}}, {7,3,4, {0,0}},
		{8,0,5, {0,0}}, {9,2,5, {0,0}}, {10,1,5, {0,0}}, {11,3,5, {0,0}}
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
		{0,{-1,phi,0}, {0,0,0,0,0}, {0,0,0,0,0}},
		{1,{1,phi,0}, {0,0,0,0,0}, {0,0,0,0,0}},
		{2,{-1,-phi,0}, {0,0,0,0,0}, {0,0,0,0,0}},
		{3,{1,-phi,0}, {0,0,0,0,0}, {0,0,0,0,0}},
		{4,{0,-1,phi}, {0,0,0,0,0}, {0,0,0,0,0}},
		{5,{0,1,phi}, {0,0,0,0,0}, {0,0,0,0,0}},
		{6,{0,-1,-phi}, {0,0,0,0,0}, {0,0,0,0,0}},
		{7,{0,1,-phi}, {0,0,0,0,0}, {0,0,0,0,0}},
		{8,{phi,0,-1}, {0,0,0,0,0}, {0,0,0,0,0}},
		{9,{phi,0,1}, {0,0,0,0,0}, {0,0,0,0,0}},
		{10,{-phi,0,-1}, {0,0,0,0,0}, {0,0,0,0,0}},
		{11,{-phi,0,1}, {0,0,0,0,0}, {0,0,0,0,0}}
	};

	// Normalize vertices to lie on unit sphere
	for(Vertex& v : P.vertices)
	{
		normalizeVertex(v);
	}

	// Set values of edges
	P.edges = {
		{0,0,5, {0,0}}, {1,0,1, {0,0}}, {2,0,11, {0,0}}, {3,0,10, {0,0}}, {4,0,7, {0,0}},
		{5,1,5, {0,0}}, {6,1,7, {0,0}}, {7,1,8, {0,0}}, {8,1,9, {0,0}}, {9,5,9, {0,0}},
		{10,5,11, {0,0}}, {11,9,8, {0,0}}, {12,8,7, {0,0}}, {13,9,4, {0,0}}, {14,9,3, {0,0}},
		{15,4,3, {0,0}}, {16,5,4, {0,0}}, {17,4,11, {0,0}}, {18,2,4, {0,0}}, {19,2,11, {0,0}},
		{20,2,3, {0,0}}, {21,2,6, {0,0}}, {22,6,3, {0,0}}, {23,8,3, {0,0}}, {24,8,6, {0,0}},
		{25,7,6, {0,0}}, {26,2,10, {0,0}}, {27,10,6, {0,0}}, {28,10,7, {0,0}}, {29,11,10, {0,0}}
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
	MatrixXd coordsCell0D = MatrixXd::Zero(3, P.numVertices());
	

	// Fill the matrix with the correct values
	for(const auto& v : P.vertices)
	{
		coordsCell0D.col(v.id) << v.coords;
	}

	// Initialize matrix of edge IDs
	MatrixXi extremaCell1D = MatrixXi::Zero(2, P.numEdges());
	

	// Fill the matrix with the correct values
	for(const auto& e : P.edges)
	{
		// Use the ID of the edge as the index
		unsigned int id = e.id;

		// Get IDs of extremas
		extremaCell1D(0, id) = e.origin;
		extremaCell1D(1, id) = e.end;
	}

	// Highlight path on the polyhedron

	// Create a vector containing for each vertex the value of shortPath
	vector<bool> visitedNodes;

	// Allocate correct amount of memory
	visitedNodes.reserve(P.numVertices());

	// Iterate along vertices
	for (unsigned int i = 0; i < P.numVertices(); i++)
	{
		visitedNodes[i] = P.vertices[i].shortPath;
	}

	// Initialize vector of UCDProperty struct and the struct itself
	vector<Gedim::UCDProperty<double>> points_properties;

	//UCDProperty.Data = 
	

	// Add prop
	//points_properties.push_back();



	// Export in the correct format
	Gedim::UCDUtilities utilities
	utilities.ExportPoints("./aaaCell0Ds.inp",
						   coordsCell0D);

	utilities.ExportSegments("./aaaCell1Ds.inp",
							 coordsCell0D,
							 extremaCell1D);

}


// Function which writes output files in the requested format
bool writeOutput(const Polyhedron& P)
{
	// Cells 0D

	// Initialize output file stream
	ofstream ofs_cell0D("Cell0Ds.txt");

	// Check if it was created correctly
	if(ofs_cell0D.fail())
	{
		cerr << "File \"Cell0Ds.txt\" cannot be created." << endl;
		return false;
	}

	// Write first line in the file
	ofs_cell0D << "id;X;Y;Z" << endl;

	// Iterate along vertices of the polyhedron
	for(const auto& v : P.vertices)
	{
		ofs_cell0D << v.id << ";"
					<< v.coords[0] << ";"
					<< v.coords[1] << ";"
					<< v.coords[2] << endl;
	}

	// Close file
	ofs_cell0D.close();


	// Cells 1D

	// Initialize output file stream
	ofstream ofs_cell1D("Cell1Ds.txt");

	// Check if it was created correctly
	if(ofs_cell1D.fail())
	{
		cerr << "File \"Cell1Ds.txt\" cannot be created." << endl;
		return false;
	}

	// Write first line in the file
	ofs_cell1D << "id;origin;end" << endl;

	// Iterate along edges of the polyhedron
	for(const auto& e : P.edges)
	{
		ofs_cell1D << e.id << ";"
					<< e.origin << ";"
					<< e.end << endl;
	}
	
	// Close file
	ofs_cell1D.close();


	//Cells 2D

	// Initialize output file stream
	ofstream ofs_cell2D("Cell2Ds.txt");

	// Check if it was created correctly
	if(ofs_cell2D.fail())
	{
		cerr << "File \"Cell2Ds.txt\" cannot be created." << endl;
		return false;
	}

	// Write first line in the file
	ofs_cell2D << "id;NumVertices;Vertices;NumEdges;Edges" << endl;

	// Iterate along faces of the polyhedron
	for(const auto& f : P.faces)
	{
		ofs_cell2D << f.id << ";"
					<< f.numVertices() << ";";
		
		for(unsigned int i = 0; i < f.numVertices(); i++)
		{
			ofs_cell2D << f.idVertices[i] << ";";
		}

		ofs_cell2D << f.numEdges() << ";";

		for(unsigned int i = 0; i < f.numEdges() - 1; i++)
		{
			ofs_cell2D << f.idEdges[i] << ";";
		}

		// Last one is inserted separately to not put ";" afterwards
		ofs_cell2D << f.idEdges[f.numEdges() - 1] << endl;
	}

	// Close file
	ofs_cell2D.close();


	//Cells 3D

	// Initialize output file stream
	ofstream ofs_cell3D("Cell3Ds.txt");

	// Check if it was created correctly
	if(ofs_cell3D.fail())
	{
		cerr << "File \"Cell3Ds.txt\" cannot be created." << endl;
		return false;
	}

	// Write first line in the file
	ofs_cell3D << "id;NumVertices;Vertices;NumEdges;Edges;NumFaces;Faces" << endl;

	// Iterate along the polyhedron
	ofs_cell3D << P.id << ";"
				<< P.numVertices() << ";";
	
	for(unsigned int i = 0; i < P.numVertices(); i++)
	{
		ofs_cell3D << P.vertices[i].id << ";";
	}

	ofs_cell3D << P.numEdges() << ";";

	for(unsigned int i = 0; i < P.numEdges(); i++)
	{
		ofs_cell3D << P.edges[i].id << ";";
	}
	
	ofs_cell3D << P.numFaces() << ";";

	for(unsigned int i = 0; i < P.numFaces() - 1; i++)
	{
		ofs_cell3D << P.faces[i].id << ";";
	}

	// Last one is inserted separately to not put ";" afterwards
	ofs_cell3D << P.faces[P.numFaces() - 1].id << endl;

	// Close file
	ofs_cell3D.close();
	

	return true;

}