#include "Graph.hpp"


using namespace std;
using namespace Eigen;

// Function which creates the graph 
Graph createGraph(const Polyhedron& pol)
{
    // Initialize graph struct
    Graph graph;

    // Allocate correct amount of space
    graph.adjacencyList.reserve(pol.numVertices());

    // Iterate along vertices to fill the adjacency list
    for (const auto& v : pol.vertices)
    {
        // Iterate along the vertex's neighbors
        for (const auto& neighbour_e : v.edgeNeighbors)
        {
            // If the current vertex is the edge's origin
            if (pol.edges[neighbour_e].origin == v.id)
            {
                // Add the edge's end
				unsigned int tmp= pol.edges[neighbour_e].end;
                graph.adjacencyList[v.id].push_back(tmp);
            }
            else
            {
                // Add the edge's origin
                unsigned int tmp=pol.edges[neighbour_e].origin;
				graph.adjacencyList[v.id].push_back(tmp);
            }
        }
    }

    return graph;
}

//Create function that return we
MatrixXi createWeights(const Graph& graph, const Polyhedron& pol)
{
	MatrixXi weights = MatrixXi::Constant(pol.numvertices(), pol.numvertices(), numeric_limits<unsigned int>::max();
	//
	for(const auto& e: pol.edges)
		{
			// Set to 1 the weight
			weights(e.origin, e.end) = 1;
			
			/////////// Alternative: get edge length
			
			// The matrix is symmetric
			weights(e.end, e.origin) = weights(e.origin, e.end);	
		}
}
