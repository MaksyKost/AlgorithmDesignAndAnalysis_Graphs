#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <utility>

using namespace std;

// Definicja nieskończoności - używamy maksymalnej wartości dla typu int
const int INF = numeric_limits<int>::max();

// Alias dla pary: <dystans, wierzchołek>
typedef pair<int, int> pii;

// Funkcja dijkstra oblicza najkrótsze ścieżki od wierzchołka startowego do wszystkich pozostałych.
// Parametry:
//   start   - wierzchołek początkowy,
//   graph   - reprezentacja grafu (lista sąsiedztwa),
//   distance - wektor wynikowy przechowujący minimalny dystans do każdego wierzchołka,
//   parent  - wektor, który umożliwia odtworzenie ścieżki (dla każdego wierzchołka zapamiętywany jest poprzednik).
void dijkstra(int start, const vector<vector<pii>>& graph, vector<int>& distance, vector<int>& parent) {
    int n = graph.size();
    distance.assign(n, INF);
    parent.assign(n, -1); // -1 oznacza, że wierzchołek nie ma rodzica

    // Kolejka priorytetowa, która przechowuje pary <dystans, wierzchołek>
    // Dzięki użyciu greater<pii> kolejka zawsze zwraca wierzchołek o najmniejszym dystansie.
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    
    // Inicjalizujemy wierzchołek startowy: dystans = 0
    distance[start] = 0;
    pq.push({0, start});

    while (!pq.empty()){
        int u = pq.top().second;
        int current_distance = pq.top().first;
        pq.pop();

        // Sprawdzamy, czy znaleziony dystans jest już nieaktualny
        if (current_distance > distance[u])
            continue;

        // Relaksacja krawędzi wychodzących z wierzchołka u
        for (const auto &edge : graph[u]) {
            int v = edge.first;   // wierzchołek sąsiadujący
            int weight = edge.second; // waga krawędzi u -> v
            if (distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                parent[v] = u; // zapisujemy poprzednika wierzchołka v
                pq.push({distance[v], v});
            }
        }
    }
}

// Rekurencyjna funkcja do wyświetlenia ścieżki ze źródła do wierzchołka v, korzystając z tablicy parent
void printPath(int v, const vector<int>& parent) {
    if (parent[v] == -1) {
        cout << v;
        return;
    }
    printPath(parent[v], parent);
    cout << " -> " << v;
}

int main() {
    int n, m;
    cout << "Podaj liczbę wierzchołków i krawędzi: ";
    cin >> n >> m;

    // Inicjalizacja grafu jako lista sąsiedztwa. Wierzchołki numerujemy od 0 do n - 1.
    vector<vector<pii>> graph(n);

    cout << "Podaj krawędzie w formacie: początek koniec waga" << endl;
    for (int i = 0; i < m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        // Dodajemy krawędź skierowaną z u do v
        graph[u].push_back({v, w});
        // Jeśli graf jest nieskierowany, można dodać również:
        // graph[v].push_back({u, w});
    }

    int start;
    cout << "Podaj wierzchołek startowy: ";
    cin >> start;

    vector<int> distance, parent;
    dijkstra(start, graph, distance, parent);

    cout << "\nNajkrótsze odległości od wierzchołka " << start << ":\n";
    for (int i = 0; i < n; i++){
        cout << "Wierzchołek " << i << ": ";
        if (distance[i] == INF) {
            cout << "Brak ścieżki" << endl;
        } else {
            cout << distance[i] << "\tŚcieżka: ";
            printPath(i, parent);
            cout << endl;
        }
    }
    
    return 0;
}