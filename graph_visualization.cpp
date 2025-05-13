#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <set>
#include <algorithm>
#include "src/graph.h"
#include "src/dfs.h"
#include "src/dijkstra.h"
#include "src/bellman_ford.h"

using namespace std;

void writeEdge(ofstream& file, int u, int v, int w, bool highlight = false) {
    file << "  " << u << " -> " << v << " [label=\"" << w << "\"";
    if (highlight) file << ", color=red, penwidth=2.0";
    file << "];\n";
}

vector<int> reconstructPath(const vector<int>& prev, int target) {
    vector<int> path;
    for (int v = target; v != -1; v = prev[v])
        path.push_back(v);
    reverse(path.begin(), path.end());
    return path;
}

void saveDOT_Dijkstra(const AdjacencyListGraph& graph, const vector<int>& dist, const vector<int>& prev, int target) {
    ofstream file("results/dijkstra.dot");
    file << "digraph Dijkstra {\n";
    file << "  node [shape=circle];\n";

    set<pair<int, int>> pathEdges;
    vector<int> path = reconstructPath(prev, target);
    for (size_t i = 1; i < path.size(); ++i)
        pathEdges.insert({path[i - 1], path[i]});

    for (int u = 0; u < graph.V; ++u) {
        for (const auto& [v, w] : graph.list[u]) {
            bool highlight = pathEdges.count({u, v}) > 0;
            writeEdge(file, u, v, w, highlight);
        }
    }
    file << "}\n";
}

void saveDOT_BellmanFord(const AdjacencyListGraph& graph, const vector<int>& dist, const vector<int>& prev, int target) {
    ofstream file("results/bellman_ford.dot");
    file << "digraph BellmanFord {\n";
    file << "  node [shape=circle];\n";

    set<pair<int, int>> pathEdges;
    vector<int> path = reconstructPath(prev, target);
    for (size_t i = 1; i < path.size(); ++i)
        pathEdges.insert({path[i - 1], path[i]});

    for (int u = 0; u < graph.V; ++u) {
        for (const auto& [v, w] : graph.list[u]) {
            bool highlight = pathEdges.count({u, v}) > 0;
            writeEdge(file, u, v, w, highlight);
        }
    }
    file << "}\n";
}

int main() {
    const int V = 10;
    
    AdjacencyListGraph graph(V);
    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 1);
    graph.addEdge(2, 1, 2);
    graph.addEdge(1, 3, 1);
    graph.addEdge(2, 4, 7);
    graph.addEdge(3, 5, 3);
    graph.addEdge(4, 5, 1);
    graph.addEdge(5, 6, 1);
    graph.addEdge(6, 7, 2);
    graph.addEdge(7, 8, 3);
    graph.addEdge(8, 9, 1);
    graph.addEdge(1, 6, 10);
    graph.addEdge(2, 6, 9);
    graph.addEdge(4, 7, 8);
    graph.addEdge(3, 8, 12);
    graph.addEdge(5, 9, 5);
    

    // DFS
    DFS<AdjacencyListGraph> dfs;
    vector<bool> visited(V, false);
    dfs.run(graph, 0, visited);

    ofstream dfsFile("results/dfs.dot");
    dfsFile << "digraph DFS {\n  node [shape=circle];\n";
    for (int u = 0; u < graph.V; ++u) {
        for (const auto& [v, _] : graph.list[u]) {
            dfsFile << "  " << u << " -> " << v << ";\n";
        }
    }
    int order = 1;
    for (int i = 0; i < visited.size(); ++i) {
        if (visited[i]) dfsFile << "  " << i << " [label=\"" << i << " (" << order++ << ")\"];\n";
    }
    dfsFile << "}\n";

    // Dijkstra
    Dijkstra<AdjacencyListGraph> dijkstra;
    vector<int> distD = dijkstra.run(graph, 0);
    vector<int> prevD(V, -1);
    vector<int> tempD(V, std::numeric_limits<int>::max());
    tempD[0] = 0;
    set<pair<int, int>> visitedSet;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, 0});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (visitedSet.count({d, u})) continue;
        visitedSet.insert({d, u});
        for (const auto& [v, w] : graph.list[u]) {
            if (tempD[u] + w < tempD[v]) {
                tempD[v] = tempD[u] + w;
                prevD[v] = u;
                pq.push({tempD[v], v});
            }
        }
    }
    saveDOT_Dijkstra(graph, distD, prevD, 9);

    // Bellman-Ford
    BellmanFord<AdjacencyListGraph> bellman;
    vector<int> distB(V, numeric_limits<int>::max());
    vector<int> prevB(V, -1);
    distB[0] = 0;

    for (int i = 0; i < V - 1; ++i) {
        for (int u = 0; u < V; ++u) {
            for (const auto& [v, w] : graph.list[u]) {
                if (distB[u] != numeric_limits<int>::max() && distB[u] + w < distB[v]) {
                    distB[v] = distB[u] + w;
                    prevB[v] = u;
                }
            }
        }
    }

    // Sprawdzenie na obecność cyklu ujemnego
    bool hasNegativeCycle = false;
    for (int u = 0; u < V; ++u) {
        for (const auto& [v, w] : graph.list[u]) {
            if (distB[u] != numeric_limits<int>::max() && distB[u] + w < distB[v]) {
                hasNegativeCycle = true;
            }
        }
    }

    if (!hasNegativeCycle && distB[9] != numeric_limits<int>::max()) {
        saveDOT_BellmanFord(graph, distB, prevB, 9);
    } else {
        cout << "Bellman-Ford: brak ścieżki lub wykryto cykl ujemny." << endl;
    }

    saveDOT_BellmanFord(graph, distB, prevB, 9);

    return 0;
}