#include <iostream>
#include <vector>
#include "../src/graph.h"
#include "../src/dfs.h"
#include "../src/dijkstra.h"
#include "../src/bellman_ford.h"

using namespace std;

void testDFS() {
    AdjacencyListGraph graph(5);
    // Tworzymy graf nieskierowany: 0-1-2, 0-3, 3-4
    graph.addEdge(0, 1, 1);
    graph.addEdge(1, 2, 1);
    graph.addEdge(0, 3, 1);
    graph.addEdge(3, 4, 1);

    DFS<AdjacencyListGraph> dfs;
    vector<bool> visited(5, false);
    dfs.run(graph, 0, visited);

    bool correct = visited[0] && visited[1] && visited[2] && visited[3] && visited[4];
    cout << "[TEST DFS] " << (correct ? "OK" : "BŁĄD") << endl;
}

void testDijkstra() {
    AdjacencyListGraph graph(5);
    // Graf skierowany z nieujemnymi wagami
    // 0 -> 1 (1), 0 -> 2 (4), 1 -> 2 (2), 2 -> 3 (1), 3 -> 4 (3)
    graph.addEdge(0, 1, 1);
    graph.addEdge(0, 2, 4);
    graph.addEdge(1, 2, 2);
    graph.addEdge(2, 3, 1);
    graph.addEdge(3, 4, 3);

    Dijkstra<AdjacencyListGraph> dijkstra;
    vector<int> dist = dijkstra.run(graph, 0);

    bool correct = dist[0] == 0 &&
                   dist[1] == 1 &&
                   dist[2] == 3 &&   // przez 0->1->2
                   dist[3] == 4 &&   // przez 0->1->2->3
                   dist[4] == 7;     // przez 0->1->2->3->4

    cout << "[TEST Dijkstra] " << (correct ? "OK" : "BŁĄD") << endl;
}

void testBellmanFord() {
    AdjacencyListGraph graph(5);
    // graf z ujemnymi wagami, bez cykli ujemnych
    graph.addEdge(0, 1, 6);
    graph.addEdge(0, 2, 7);
    graph.addEdge(1, 2, 8);
    graph.addEdge(1, 3, 5);
    graph.addEdge(1, 4, -4);
    graph.addEdge(2, 3, -3);
    graph.addEdge(2, 4, 9);
    graph.addEdge(3, 1, -2);
    graph.addEdge(4, 0, 2);
    graph.addEdge(4, 3, 7);

    BellmanFord<AdjacencyListGraph> bellman;
    vector<int> dist = bellman.run(graph, 0);  

    bool correct = dist[0] == 0 &&
                   dist[1] == 2 &&
                   dist[2] == 7 &&
                   dist[3] == 4 &&
                   dist[4] == -2;

    cout << "[TEST Bellman-Ford] " << (correct ? "OK" : "BŁĄD") << endl;
}

void testDFS_Matrix() {
    AdjacencyMatrixGraph graph(5);
    graph.addEdge(0, 1, 1);
    graph.addEdge(1, 2, 1);
    graph.addEdge(0, 3, 1);
    graph.addEdge(3, 4, 1);

    DFS<AdjacencyMatrixGraph> dfs;
    vector<bool> visited(5, false);
    dfs.run(graph, 0, visited);

    bool correct = visited[0] && visited[1] && visited[2] && visited[3] && visited[4];
    cout << "[TEST DFS (macierz)] " << (correct ? "OK" : "BŁĄD") << endl;
}

void testDijkstra_Matrix() {
    AdjacencyMatrixGraph graph(5);
    graph.addEdge(0, 1, 1);
    graph.addEdge(0, 2, 4);
    graph.addEdge(1, 2, 2);
    graph.addEdge(2, 3, 1);
    graph.addEdge(3, 4, 3);

    Dijkstra<AdjacencyMatrixGraph> dijkstra;
    vector<int> dist = dijkstra.run(graph, 0);

    bool correct = dist[0] == 0 &&
                   dist[1] == 1 &&
                   dist[2] == 3 &&
                   dist[3] == 4 &&
                   dist[4] == 7;

    cout << "[TEST Dijkstra (macierz)] " << (correct ? "OK" : "BŁĄD") << endl;
}

void testBellmanFord_Matrix() {
    AdjacencyMatrixGraph graph(5);
    graph.addEdge(0, 1, 6);
    graph.addEdge(0, 2, 7);
    graph.addEdge(1, 2, 8);
    graph.addEdge(1, 3, 5);
    graph.addEdge(1, 4, -4);
    graph.addEdge(2, 3, -3);
    graph.addEdge(2, 4, 9);
    graph.addEdge(3, 1, -2);
    graph.addEdge(4, 0, 2);
    graph.addEdge(4, 3, 7);

    BellmanFord<AdjacencyMatrixGraph> bellman;
    vector<int> dist = bellman.run(graph, 0);  

    bool correct = dist[0] == 0 &&
                   dist[1] == 2 &&
                   dist[2] == 7 &&
                   dist[3] == 4 &&
                   dist[4] == -2;

    cout << "[TEST Bellman-Ford (macierz)] " << (correct ? "OK" : "BŁĄD") << endl;
}

int main() {
    cout << "=== TESTY - LISTA SASIEDZTWA ===" << endl;
    testDFS();
    testDijkstra();
    testBellmanFord();

    cout << "\n=== TESTY - MACIERZ SASIEDZTWA ===" << endl;
    testDFS_Matrix();
    testDijkstra_Matrix();
    testBellmanFord_Matrix();

    return 0;
}