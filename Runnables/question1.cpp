#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Structure to represent an edge in the graph
struct Edge {
    int u, v, w; // Source, destination, weight
};

// Function to load the graph from a DIMACS file
vector<Edge> loadGraph(const string& filename) {
    vector<Edge> edges;
    ifstream file(filename);
    string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            // Skip comments
            if (line[0] == 'c') continue;

            // Parse problem line to get number of nodes and edges
            if (line[0] == 'p') {
                int n, m;
                char type[10];
                sscanf(line.c_str(), "%s %*s %d %d", type, &n, &m);
                // Assuming the graph is already known to have 'm' edges
                edges.reserve(m);
            }

            // Parse edge descriptors
            if (line[0] == 'a') {
                int u, v, w;
                sscanf(line.c_str(), "%*s %d %d %d", &u, &v, &w);
                // Adjust node labels to match custom binary format
                u--; v--; 
                edges.push_back({u, v, w});
            }
        }
        file.close();
    } else {
        cerr << "Unable to open file: " << filename << endl;
    }

    return edges;
}

int main() {
    // File path for the DIMACS graph
    string filename = "florida.dimacs";

    // Load the graph
    vector<Edge> graph = loadGraph(filename);

    // Check if the graph loaded successfully
    if (graph.empty()) {
        cerr << "Failed to load graph." << endl;
        return 1;
    }

    // Printing the loaded edges (for testing purposes)
    for (const auto& edge : graph) {
        cout << "Edge: " << edge.u << " - " << edge.v << ", Weight: " << edge.w << endl;
    }

    return 0;
}
