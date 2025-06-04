#include "Utils.hpp"
#include "Triangle.hpp"
#include "Geometry.hpp"
#include "Graph.hpp"


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
	if (!checkPolyhedronInput(argc, argv, p, q, b, c, val, flag))
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
		P = TriangleClassII(initial_P, val);
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
	getEdgeNeighbors(P);
	getVertexNeighbors(P);

	//
	Polyhedron P_new;
	P_new = P;


	// Create the dual polyhedron, if needed
	if(p != 3)
	{
		P_new = Dual(P);
	}


	// Shortest path

	// Initialize variables
	unsigned int id_path_start; // ID of starting vertex
	unsigned int id_path_end; // ID of ending vertex


	// Shortest path

	if(argc == 7)
	{
		// Check input
		if (!checkGraphInput(argv, id_path_start, id_path_end, P_new))
		{
			return 1;
		}

		// Initialize graph and weight matrix
		Graph graph = createGraph(P_new);
		MatrixXi weights = createWeights(graph, P_new);

		// Run Dijkstra algorithm
		vector<unsigned int> path = Dijkstra(graph, id_path_start, id_path_end, weights);

		for(unsigned int i = 0; i < path.size(); i++)
		{
			cout << path[i] << " ";
		}
		cout << endl;
	}


	// Export the polyhedron for Paraview
	exportPolyhedron(P_new);
		
	// Write .txt output files
	if(!writeOutput(P_new))
	{
		return 1;
	}

	
	return 0;
	
}