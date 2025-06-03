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

// Create the weights matrix
MatrixXi createWeights(const Graph& graph, const Polyhedron& pol)
{
	MatrixXi weights = MatrixXi::Constant(pol.numVertices(), pol.numVertices(), numeric_limits<unsigned int>::max());
	//
	for(const auto& e: pol.edges)
		{
			// Set to 1 the weight
			weights(e.origin, e.end) = 1;
			
			/////////// Alternative: get edge length
			
			// The matrix is symmetric
			weights(e.end, e.origin) = weights(e.origin, e.end);	
		}

    return weights;
}

// Dijkstra algorithm, returns vector of IDs of visited vertices
vector<unsigned int> Dijkstra(const Graph& graph,
                                    unsigned int id_path_start,
                                    unsigned int id_path_end,
                                    MatrixXi weights)
{
    // Initialize vectors 
   vector<unsigned int> pred;
   vector<unsigned int> dist;

    unsigned int N = graph.adjacencyList.size();

   // Reserve correct amount of space
   pred.reserve(N);
   dist.reserve(N);

   // Fill the vectors with initial values
   for (unsigned int i = 0; i < N; i++)
   {
    pred[i] = -1;
    dist[i] = numeric_limits<unsigned int>::max();
   }

   // Initialize source node
   pred[id_path_start] = id_path_start;
   dist[id_path_start] = 0;

   // Initialize a priority queue
   // Each element is a pair (distance, vertex)
   // When .top() is called it returns the pair with shortest distance
    priority_queue<pair<unsigned int, unsigned int>,
                    vector<pair<unsigned int, unsigned int>>,
                    greater<>> PQ;

   for (unsigned int i = 0; i < N; i++)
   {
    PQ.push(dist[i], i);
   }

   while(!PQ.empty())
   {
        // Access element with lowest priority (distance)
        pair<unsigned int, unsigned int> d_v = PQ.top()

        // Get closest node
        unsigned int u = d_v.second;

        // Then, dequeue it
        PQ.pop()

        // For each node adjacent to u
        for (const auto& w : graph.adjacentList[u])
        {
            if (dist[w] > dist[u] + weights(u, w))
            {
                dist[w] = dist[u] + weights(u, w);
                pred[w] = u;
                // decrease key
            }
        }

   }
}


// Versione da integrare

// vector<unsigned int> Dijkstra(const Graph& graph,
//                               unsigned int id_path_start,
//                               unsigned int id_path_end,
//                               const MatrixXi& weights)
// {
//     unsigned int N = graph.adjacencyList.size();

//     // Initialize vectors
//     vector<unsigned int> pred(N, -1);
//     vector<unsigned int> dist(N, numeric_limits<unsigned int>::max());
//     vector<bool> visited(N, false);  // To track processed nodes

//     // Initialize source node
//     pred[id_path_start] = id_path_start;
//     dist[id_path_start] = 0;

//     // Priority queue: (distance, vertex)
//     priority_queue<pair<unsigned int, unsigned int>,
//                    vector<pair<unsigned int, unsigned int>>,
//                    greater<>> PQ;

//     PQ.push({0, id_path_start});

//     while (!PQ.empty()) {
//         auto [curr_dist, u] = PQ.top();
//         PQ.pop();

//         // Skip already visited nodes
//         if (visited[u]) continue;
//         visited[u] = true;

//         // Early exit if we reached the end
//         if (u == id_path_end) break;

//         // For each neighbor w of u
//         for (unsigned int w : graph.adjacencyList[u]) {
//             if (dist[w] > dist[u] + weights(u, w)) {
//                 dist[w] = dist[u] + weights(u, w);
//                 pred[w] = u;
//                 PQ.push({dist[w], w});  // Simulate decrease-key
//             }
//         }
//     }

//     // Reconstruct the path (or just return visited if that's the goal)
//     vector<unsigned int> visited_nodes;
//     for (unsigned int i = 0; i < N; ++i) {
//         if (visited[i]) visited_nodes.push_back(i);
//     }
//     return visited_nodes;
// }