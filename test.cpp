#include <iostream>
#include <vector>
#include <queue>


struct Edge{
    int destination_id;
    double length;
};

struct Vertex {
    double lon{0.0};
    double lat{0.0};
    double x{0.0};
    double y{0.0};
    std::vector<Edge> neighbors;
};



float Dijkstra_Algorithm(int starting_node,int ending_node, const std::vector<std::vector<Edge>>& graph){
    const int INF = 10E9;
    
    std::vector<double> distances(graph.size(),INF);
    std::vector<int> parents(graph.size(),-1);

    using PairValue = std::pair<float,int>;
    std::priority_queue<PairValue,std::vector<PairValue>, std::greater<PairValue>> priority_queue;

    distances[starting_node] = 0;
    priority_queue.push({0.0,starting_node});

    while(!priority_queue.empty()){
        auto [current_distance, current_node] = priority_queue.top();
        priority_queue.pop();


        if (current_node==ending_node){
            return current_distance;
        }
        if (current_distance > distances[current_node]){
            continue;
        }

        for (auto& edge : graph[current_node]){
            int id_new_neighbor = edge.destination_id;
            int new_distance = edge.length + current_distance;

            if(new_distance < distances[id_new_neighbor]){
                distances[id_new_neighbor] = new_distance;
                parents[id_new_neighbor] = current_node;
                priority_queue.push({new_distance,id_new_neighbor});

            }

        }
    }
    return -1.0f;
} 

