#include <iostream>


#include "graph.h"


int main(){

    std::string filepath = "/home/nconsalvi/robotics_roadmap/dijkstra_astar_project/graph_dc_area.2022-03-11.txt";
    
    std::unordered_map<int,Node> nodes = ParseCVCVertices(filepath);
    std::unordered_map<int,std::vector<Edge>> edges = ParseCSVEdges(filepath);

    /*
    for (const auto& [id,node] : nodes )
        std::cout << "id :" << id << " lon : " <<node.lon << " lat :" << node.lat <<std::endl;
        */

    for (const auto& [source_id, vector_edge] : edges){
        for (Edge edge : vector_edge){
            std::cout << "source_id: " << source_id  << " /dest_id: " << edge.destination_id << " /length: " << edge.length <<std::endl;
        }
        }
}   