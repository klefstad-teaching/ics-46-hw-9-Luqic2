#include "dijkstras.h"

int main () {
    Graph G;
    file_to_graph("src/small.txt", G);

    vector<int> previous(G.size(), -1);

    vector<int> distances = dijkstra_shortest_path(G, 0, previous);
    
    int destination = 3;
    vector<int> path = extract_shortest_path(distances, previous, destination);
    cout << "Destination : " << destination << endl;
    cout << "\tPath is : ";
    print_path(path, path.size());
    cout << "\n\tTotal Distance is : " << distances[destination] << endl;
}