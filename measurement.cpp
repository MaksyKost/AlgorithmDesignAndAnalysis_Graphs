#include <iostream>
#include <fstream>
#include <chrono>
#include "src/graph.h"
#include "src/dfs.h"
#include "src/dijkstra.h"
#include "src/bellman_ford.h"

using namespace std;
using namespace std::chrono;

template<typename Function>
double measure_time(Function func) {
    auto start = high_resolution_clock::now();
    func();
    auto end = high_resolution_clock::now();
    duration<double> elapsed = end - start;
    return elapsed.count();
}

int main() {
    const int SIZES[] = {10, 50, 100, 200, 500};
    const double DENSITIES[] = {0.25, 0.50, 0.75, 1.0};
    const int TESTS = 100;
    const int SEEDS[] = {250, 300, 350, 400, 450};

    ofstream resultsFile("results/GraphAlgorithmResults.txt");
    if (!resultsFile.is_open()) {
        cerr << "Помилка відкриття файлу для запису!" << endl;
        return 1;
    }

    for (int size : SIZES) {
        for (double density : DENSITIES) {
            cout << "\n📊 Тестування графів: " << size << " вершин, густина " 
                 << density * 100 << "%" << endl;
            resultsFile << "\n📊 Тестування графів: " << size << " вершин, густина " 
                        << density * 100 << "%" << endl;

            double total_dfs_list = 0.0, total_dfs_matrix = 0.0;
            double total_dijkstra_list = 0.0, total_dijkstra_matrix = 0.0;
            double total_bellman_list = 0.0, total_bellman_matrix = 0.0;

            for (int seed : SEEDS) {
                srand(seed);

                AdjacencyListGraph listGraph(size);
                listGraph.createGraph(size, density);

                AdjacencyMatrixGraph matrixGraph(size);
                matrixGraph.createGraph(size, density);

                DFS<AdjacencyListGraph> dfs_list;
                DFS<AdjacencyMatrixGraph> dfs_matrix;

                Dijkstra<AdjacencyListGraph> dijkstra_list;
                Dijkstra<AdjacencyMatrixGraph> dijkstra_matrix;

                BellmanFord<AdjacencyListGraph> bellman_list;
                BellmanFord<AdjacencyMatrixGraph> bellman_matrix;

                double dfs_time_list = 0.0, dfs_time_matrix = 0.0;
                double dijkstra_time_list = 0.0, dijkstra_time_matrix = 0.0;
                double bellman_time_list = 0.0, bellman_time_matrix = 0.0;

                for (int t = 0; t < TESTS; t++) {
                    vector<bool> visited(size, false);

                    // 🏁 ТЕСТ DFS
                    dfs_time_list += measure_time([&]() { dfs_list.run(listGraph, 0, visited); });
                    dfs_time_matrix += measure_time([&]() { dfs_matrix.run(matrixGraph, 0, visited); });

                    // 🏁 ТЕСТ Dijkstra
                    dijkstra_time_list += measure_time([&]() { dijkstra_list.run(listGraph, 0); });
                    dijkstra_time_matrix += measure_time([&]() { dijkstra_matrix.run(matrixGraph, 0); });

                    // 🏁 ТЕСТ Bellman-Ford
                    bellman_time_list += measure_time([&]() { bellman_list.run(listGraph, 0); });
                    bellman_time_matrix += measure_time([&]() { bellman_matrix.run(matrixGraph, 0); });
                }

                total_dfs_list += dfs_time_list / TESTS;
                total_dfs_matrix += dfs_time_matrix / TESTS;

                total_dijkstra_list += dijkstra_time_list / TESTS;
                total_dijkstra_matrix += dijkstra_time_matrix / TESTS;

                total_bellman_list += bellman_time_list / TESTS;
                total_bellman_matrix += bellman_time_matrix / TESTS;
            }

            // ✨ ЗАПИС РЕЗУЛЬТАТІВ
            resultsFile << "\n**DFS**:\n";
            resultsFile << "Список суміжності:  " << (total_dfs_list / 5) << " с\n";
            resultsFile << "Матриця суміжності: " << (total_dfs_matrix / 5) << " с\n";

            resultsFile << "\n**Dijkstra**:\n";
            resultsFile << "Список суміжності:  " << (total_dijkstra_list / 5) << " с\n";
            resultsFile << "Матриця суміжності: " << (total_dijkstra_matrix / 5) << " с\n";

            resultsFile << "\n**Bellman-Ford**:\n";
            resultsFile << "Список суміжності:  " << (total_bellman_list / 5) << " с\n";
            resultsFile << "Матриця суміжності: " << (total_bellman_matrix / 5) << " с\n";
        }
    }

    resultsFile.close();
    cout << "\n✅ Завершено! Результати записані у 'GraphAlgorithmResults.txt'.\n";
    return 0;
}