#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using Edge = std::pair<int, double>;
using AdjacencyList = std::vector<std::vector<Edge>>;

std::pair<double, std::vector<int>> dijkstra_with_path(int start_node, int destination_node, const AdjacencyList& graph) {
    const double INF = std::numeric_limits<double>::infinity();
    std::vector<double> distances(graph.size(), INF);
    
    // -1 signifie qu'un sommet n'a pas encore de parent
    std::vector<int> parent(graph.size(), -1); 

    using QueueElement = std::pair<double, int>;
    std::priority_queue<QueueElement, std::vector<QueueElement>, std::greater<QueueElement>> priority_queue;

    distances[start_node] = 0.0;
    priority_queue.push({0.0, start_node});

    while (!priority_queue.empty()) {
        auto [current_distance, current_node] = priority_queue.top();
        priority_queue.pop();


        if (current_node == destination_node) {
            break; // Cible atteinte avec la distance minimale garantie
        }

        if (current_distance > distances[current_node]) {
            continue;
        }
        for (const auto& [neighbor_node, edge_weight] : graph[current_node]) {
            double new_distance = current_distance + edge_weight;

            if (new_distance < distances[neighbor_node]) {
                distances[neighbor_node] = new_distance;
                parent[neighbor_node] = current_node; // On enregistre d'où on vient
                priority_queue.push({new_distance, neighbor_node});
            }
        }
    }
            // Si la destination est inaccessible
            if (distances[destination_node] == INF) {
                return {-1.0, {}};
            }

            // Reconstruction du chemin à l'envers : de l'arrivée vers le départ
            std::vector<int> path;
            for (int curr = destination_node; curr != -1; curr = parent[curr]) {
                path.push_back(curr);
            }
            std::reverse(path.begin(), path.end());

            return {distances[destination_node], path};
        }