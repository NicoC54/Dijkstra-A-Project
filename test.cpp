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


double dijkstra_algorithm(int starting_node, int ending_node, const std::vector<std::vector<Edge>>& graph ){

    const int INF = 10E9; //initialisation des longueurs à l'infini
    std::vector<double> distances(graph.size(), INF); // initialisation du tableau contenant la distance du point dorigine a chaque noeud
    std::vector<int> parents(graph.size(), -1); // initialisation du tableau parent : de quel noeud provient chaque noeud exploré
    using PairElement = std::pair<float,int> ; //simplification du type std::pair<float,int>

    std::priority_queue<PairElement, std::vector<PairElement>, std::greater<PairElement>> priority_queue; // priority queue avec min heap
    distances[starting_node]=0; // initialisation de la distance du noeud de départ
    priority_queue.push({0.0, starting_node}); // exploration du noeud de départ, et donc plus tard dans lalgo de ses voisins prometteurs

    while(!priority_queue.empty()){ // tant qu'il reste des sommets explorables
        auto [current_distance, current_node] = priority_queue.top(); // Le noeud voisin le plus prometteur est choisi comme noeud courant
        priority_queue.pop(); // on supprime ce choix de voisin

        if (current_node == ending_node){ // mathématiquement assure que le résultat est le minimum, car on prend la valeur la plus petite et les poids sont positifs
            return current_distance;
        }

        if (current_distance > distances[current_node]){ // au cas ou on aurait trouvé un chemin au debut plus long (qui était prioritaire au début par rapport à un chemin plus court) mais pas traité et qu'entre temps on trouve un raccourci, ce raccourci sera traité en premier, et viendra à nouveau le cas de ce noeud non prioritaire qu'on supprime avec cette condition
            continue;
        }

        for (const auto& edge : graph[current_node]){ //on explore les voisins (edges) du noeud voisin le plus prometteur qui est actuellement choisi comme noeud courant à partir de graph(current_node) qui donne accès a un vecteur de edges : les edges voisins, et on boucle dessus
            double new_distance = edge.length + current_distance; //on calcule la nouvelle distance à chacun de ces voisins par rapport au noeud d'origine,un part un, qui vaut la distance à l'origine du noeud prometteur choisi l.32 + la distance de ce voisin à ce noeud prometteur
            int neighbor_id = edge.destination_id; // on note le numero du noeud voisin qu'on check actuellement
            if(new_distance<distances[neighbor_id]){ // si la nouvelle distance calculée (current_distance + edge.length est inferieure à toute distance qu'on a enregistré entre lorigine et ce nouveau noeud (distances[neighbor_id]) alors on remplace la distance)
                distances[neighbor_id] = new_distance;
                parents[neighbor_id] = current_node; //on met a jour le parent pour le chemin le plus court
                priority_queue.push({new_distance,neighbor_id}); //on push ce noeud + distance dans la priority queue, parmi tous les voisins du noeud le plus prometteur du départ, la priority queue traitera le plus prometteur (cad avec la ditance cumulée minimale à l'origine ) puis on reboucle
            }


            
        }

    }
    return -1.0f;

}