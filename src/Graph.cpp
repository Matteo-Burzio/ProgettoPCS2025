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
                graph.adjacencyList[v.id].push_back(pol.edges[neighbour_e].end)
            }
            else
            {
                // Add the edge's origin
                graph.adjacencyList[v.id].push_back(pol.edges[neighbour_e].origin)
            }
        }
    }

    return graph;
}

