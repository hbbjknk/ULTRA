#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <queue>
#include <set>

using namespace std;

// Structure to represent a stop
struct Stop {
    string id;
    string name;
};

// Structure to represent an edge between stops (route)
struct Edge {
    string routeId;
    string sourceStopId;
    string destinationStopId;
};

// Graph class representing the transportation network
class Graph {
private:
    unordered_map<string, vector<Edge>> adjacencyList;

public:
    // Add an edge to the graph
    void addEdge(const Edge& edge) {
        adjacencyList[edge.sourceStopId].push_back(edge);
    }

    // Get adjacent edges of a stop
    vector<Edge> getAdjacentEdges(const string& stopId) {
        if (adjacencyList.find(stopId) != adjacencyList.end()) {
            return adjacencyList[stopId];
        }
        return {};
    }

    // Find direct journeys from source to destination
    void findDirectJourneys(const string& sourceStopId, const string& destinationStopId) {
        cout << "Direct journeys:" << endl;
        for (const auto& edge : adjacencyList[sourceStopId]) {
            if (edge.destinationStopId == destinationStopId) {
                cout << "Route: " << edge.routeId << "(" << sourceStopId << " > " << destinationStopId << ")" << endl;
            }
        }
    }

    // Find journeys with one transfer
    void findJourneysWithOneTransfer(const string& sourceStopId, const string& destinationStopId) {
        cout << "Journeys with one transfer:" << endl;
        for (const auto& edge1 : adjacencyList[sourceStopId]) {
            for (const auto& edge2 : adjacencyList[edge1.destinationStopId]) {
                if (edge2.destinationStopId == destinationStopId) {
                    cout << "Route: " << edge1.routeId << "(" << sourceStopId << " > " << edge1.destinationStopId << ") - ";
                    cout << "Route: " << edge2.routeId << "(" << edge1.destinationStopId << " > " << destinationStopId << ")" << endl;
                }
            }
        }
    }

    // Find journeys with two transfers
    void findJourneysWithTwoTransfers(const string& sourceStopId, const string& destinationStopId) {
        cout << "Journeys with two transfers:" << endl;
        set<string> visited;
        queue<pair<string, string>> q; // Queue of pairs: (stopId, routeHistory)
        q.push({sourceStopId, ""});
        visited.insert(sourceStopId);

        while (!q.empty()) {
            auto [stopId, routeHistory] = q.front();
            q.pop();

            for (const auto& edge : adjacencyList[stopId]) {
                string nextStopId = edge.destinationStopId;
                string nextRouteHistory = routeHistory + "-" + edge.routeId;

                if (nextStopId == destinationStopId) {
                    cout << "Route: " << nextRouteHistory.substr(1) << "(" << sourceStopId << " > " << destinationStopId << ")" << endl;
                } else {
                    for (const auto& nextEdge : adjacencyList[nextStopId]) {
                        if (visited.find(nextEdge.destinationStopId) == visited.end()) {
                            q.push({nextEdge.destinationStopId, nextRouteHistory + "-" + nextEdge.routeId});
                            visited.insert(nextEdge.destinationStopId);
                        }
                    }
                }
            }
        }
    }
};

int main() {
    // Example edges (routes)
    vector<Edge> edges = {
        {"R1", "so", "s1"},
        {"R1", "s1", "sd"},
        {"R2", "so", "s2"},
        {"R2", "s2", "sd"},
        {"R3", "s1", "sd"},  // Added for testing two transfers
        {"R4", "so", "s3"},
        {"R4", "s3", "sd"},
        // Add more edges/routes as needed
    };

    // Create a graph
    Graph graph;

    // Add edges to the graph
    for (const auto& edge : edges) {
        graph.addEdge(edge);
    }

    // Source and destination stops
    string sourceStopId = "so";
    string destinationStopId = "sd";

    // Find and print direct journeys
    graph.findDirectJourneys(sourceStopId, destinationStopId);

    // Find and print journeys with one transfer
    graph.findJourneysWithOneTransfer(sourceStopId, destinationStopId);

    // Find and print journeys with two transfers (bonus)
    graph.findJourneysWithTwoTransfers(sourceStopId, destinationStopId);

    return 0;
}
