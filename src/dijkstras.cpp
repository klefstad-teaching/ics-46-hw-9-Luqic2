#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int numVertices = G.size();

    // holds shortest distances from src to i
    vector<int> distances(numVertices, INF);
    
    // distance from source to itself is always 0
    distances[source] = 0;
    previous[source] = -1; // UNDEFINED

    vector<bool> visited(numVertices, false);
    
    struct MinHeap {
        bool operator() (const pair<int, int>& a, const pair<int, int>& b) {
            return a.second > b.second;
        }
    };

    priority_queue<pair<int, int>, vector<pair<int, int>>, MinHeap > minHeap; // pair<vertex, weight>
    minHeap.push({source, 0});

    while ( !minHeap.empty() ) {
        int u = minHeap.top().first; // vertex
        // int w = minHeap.top().second; // weight
        minHeap.pop();

        if (visited[u]) continue;

        visited[u] = true;

        for (Edge edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;

            if ( !visited[v] && distances[u] + weight < distances[v] ) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({v, distances[v]});
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;

    // if no path to destination
    if (distances[destination] == INF) {
        cout << "No path found. " << endl;
        return path;
    }

    // trace from destination to source using previous vector
    for (int v = destination; v != -1; v = previous[v]) {
        path.push_back(v);
    }

    // reverse the order of path from dest -> source TO source -> dest
    reverse(path.begin(), path.end());

    return path;
}

void print_path(const vector<int>& v, int total) {
    for (int i : v)
        cout << i << " ";
    cout << "\nTotal cost is " << total << endl;
}
