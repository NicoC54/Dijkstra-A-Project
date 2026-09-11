#include <unordered_map>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>
#include <iostream>

struct Edge{
    int destination_id;
    double length;
};

struct Node{
    double lon;
    double lat;
    double x;
    double y;
    std::vector<Edge> neighbors;
};

class Graph {

    private:
        std::unordered_map <int,Node> vertices;

        void loadFromFile(const std::string& filepath){
        std::ifstream file (filepath);
        if (!file.is_open()){
            std::cerr << "ERROR : file hasn't been read";
            return;
        }

        std::string line;
        while(std::getline(file,line)){

        if (line.empty()|| line[0]=='#'){
            continue;
        }

        if (line.rfind('V',0)==0){
            
            std::stringstream ss(line);
            std::string buffer;
            std::getline(ss,buffer,',');
            std::getline(ss,buffer,',');
            int id = std::stoi(buffer);
            std::getline(ss,buffer,',');
            double lon = std::stod(buffer);
            std::getline(ss,buffer,',');
            double lat = std::stod(buffer);

            vertices[id].lon = lon;
            vertices[id].lat = lat;
        }

        else if (line.rfind('E',0)==0){
        
            std::stringstream ss(line);
            std::string buffer;
            std::getline(ss, buffer,',');
            std::getline(ss, buffer,',');
            int source_id = std::stoi(buffer);
            std::getline(ss,buffer,',');
            int destination_id = std::stoi(buffer);
            std::getline(ss,buffer,',');
            double length = std::stod(buffer);

            vertices[source_id].neighbors.push_back({destination_id, length});

        }

        }

        }

        void computeMercator() {
        const double R0 = 6378137.0; // Rayon de la Terre en mètres
        const double deg2rad = M_PI / 180.0;

        // 1. Calculer le centre géographique (lambda_c, phi_c) moyen
        double sum_lon = 0.0, sum_lat = 0.0;
        for (const auto& [id, node] : vertices) {
            sum_lon += node.lon;
            sum_lat += node.lat;
        }
        double lambda_c = (sum_lon / vertices.size()) * deg2rad; // en radians
        double phi_c    = (sum_lat / vertices.size()) * deg2rad; // en radians[cite: 2]

        // 2. Convertir chaque sommet (x, y)
        for (auto& [id, node] : vertices) {
            double lambda_p = node.lon * deg2rad;
            double phi_p    = node.lat * deg2rad;
            double delta_phi = phi_p - phi_c; //[cite: 2]

            node.x = R0 * std::cos(phi_c) * (lambda_p - lambda_c); //[cite: 2]
            node.y = R0 * std::log(std::tan(delta_phi / 2.0 + M_PI / 4.0)); //[cite: 2]
        }
        }
    public:
        Graph(const std::string& filepath){
            loadFromFile(filepath);
            computeMercator();


    }

};
