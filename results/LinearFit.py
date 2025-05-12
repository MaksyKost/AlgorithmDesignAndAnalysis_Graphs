import matplotlib.pyplot as plt
import numpy as np
from sklearn.linear_model import LinearRegression

# Definicja rozmiarów – liczba wierzchołków dla testów przy gęstości 100%
sizes = np.array([10, 50, 100, 200, 500]).reshape(-1, 1)

# --- Dane dla DFS przy gęstości 100% ---
dfs_list = np.array([2.9414e-06, 5.93732e-05, 0.000224915, 0.000915049, 0.00549341])
dfs_matrix = np.array([2.978e-07, 1.0826e-06, 1.957e-06, 4.0076e-06, 9.3822e-06])

# --- Dane dla Dijkstra przy gęstości 100% ---
dj_list = np.array([8.5944e-06, 0.000174949, 0.000625897, 0.00234743, 0.0137155])
dj_matrix = np.array([1.03992e-05, 0.000216671, 0.000887564, 0.0032034, 0.0173248])

# --- Dane dla Bellman-Ford przy gęstości 100% ---
bf_list = np.array([1.288e-05, 0.00173672, 0.0134338, 0.107633, 2.07613])
bf_matrix = np.array([1.1056e-05, 0.00140682, 0.0108224, 0.107505, 1.89223])

# Tworzymy modele regresji liniowej dla każdej serii pomiarów
reg_dfs_list   = LinearRegression().fit(sizes, dfs_list)
reg_dfs_matrix = LinearRegression().fit(sizes, dfs_matrix)
reg_dj_list    = LinearRegression().fit(sizes, dj_list)
reg_dj_matrix  = LinearRegression().fit(sizes, dj_matrix)
reg_bf_list    = LinearRegression().fit(sizes, bf_list)
reg_bf_matrix  = LinearRegression().fit(sizes, bf_matrix)

# Obliczamy przewidywane wartości dla zadanego zbioru rozmiarów
dfs_list_pred   = reg_dfs_list.predict(sizes)
dfs_matrix_pred = reg_dfs_matrix.predict(sizes)
dj_list_pred    = reg_dj_list.predict(sizes)
dj_matrix_pred  = reg_dj_matrix.predict(sizes)
bf_list_pred    = reg_bf_list.predict(sizes)
bf_matrix_pred  = reg_bf_matrix.predict(sizes)

# Funkcja do rysowania wykresów ze znakowanymi punktami i linią dopasowania
def plot_with_fit(x, y, y_pred, title, label, color):
    plt.figure(figsize=(8, 5))
    plt.scatter(x, y, color=color, label=f'Czas ({label})', marker='o')
    plt.plot(x, y_pred, color='black', linestyle='--', label='Dopasowanie liniowe')
    plt.title(title)
    plt.xlabel('Liczba wierzchołków')
    plt.ylabel('Czas [s]')
    plt.grid(True, linestyle='--', alpha=0.6)
    plt.legend()
    plt.tight_layout()
    plt.show()

# Wykresy dla DFS
plot_with_fit(sizes.flatten(), dfs_list, dfs_list_pred,
              'DFS (Lista sąsiedztwa) - Dopasowanie liniowe',
              'DFS - Lista', 'blue')

plot_with_fit(sizes.flatten(), dfs_matrix, dfs_matrix_pred,
              'DFS (Macierz sąsiedztwa) - Dopasowanie liniowe',
              'DFS - Macierz', 'red')

# Wykresy dla Dijkstra
plot_with_fit(sizes.flatten(), dj_list, dj_list_pred,
              'Dijkstra (Lista sąsiedztwa) - Dopasowanie liniowe',
              'Dijkstra - Lista', 'green')

plot_with_fit(sizes.flatten(), dj_matrix, dj_matrix_pred,
              'Dijkstra (Macierz sąsiedztwa) - Dopasowanie liniowe',
              'Dijkstra - Macierz', 'purple')

# Wykresy dla Bellman-Ford
plot_with_fit(sizes.flatten(), bf_list, bf_list_pred,
              'Bellman-Ford (Lista sąsiedztwa) - Dopasowanie liniowe',
              'Bellman-Ford - Lista', 'orange')

plot_with_fit(sizes.flatten(), bf_matrix, bf_matrix_pred,
              'Bellman-Ford (Macierz sąsiedztwa) - Dopasowanie liniowe',
              'Bellman-Ford - Macierz', 'brown')