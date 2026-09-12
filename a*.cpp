#include <iostream>
#include <queue>
#include <vector>
#include <cmath>

struct Edge {
    int destination_id;
    double length;
};

struct Vertex {
    double x{0.0};
    double y{0.0};
    double lon{0.0};
    double lat{0.0};
    std::vector<Edge> neighbors;
};

// 1. Déclarée avant l'algorithme
double heuristique(int starting_node, int ending_node, const std::vector<Vertex>& vertices) { // fonction pour ajouter une estimation de la distance restante à parcourir du start à l'ending node : distance cartésienne
    double dx = vertices[starting_node].x - vertices[ending_node].x; //xstart-xend =dx
    double dy = vertices[starting_node].y - vertices[ending_node].y; //ystart-yend = dy
    return std::hypot(dx, dy); //racine carrée de dx**2 +dy**2
}

// 2. Passage par référence constante : &
double AstarAlgorithm(int starting_node, int ending_node, 
                      const std::vector<std::vector<Edge>>& graph, 
                      const std::vector<Vertex>& vertices) {

    const double INF = 1e9; //constante pour simuler linfini
    std::vector<int> parents(graph.size(), -1); //tableau de parents de taille graphe.size() et initialisé partout à -1 car pas de parents connus pour lisntant et les id de noeuds démarrent à 0 : hypothese
    std::vector<double> g_score(graph.size(), INF); //tableau des distances des noeuds depuis l'origine appelé distances dans dijkstra, il est appelé g_core ici, puisque f(n)= g(n) + h(n)
    
    using PairElement = std::pair<double, int>; // nouveau type plus simple à écrire
    std::priority_queue<PairElement, std::vector<PairElement>, std::greater<PairElement>> priority_queue; // priority queue min_heap : sortira la valeur de double la plus petite avec un top()

    // 3. Initialisation obligatoire du départ
    g_score[starting_node] = 0.0;  // distance au noeud de départ nulle

    double f_initial_score = /*g_score[starting_node] = 0 +*/ heuristique(starting_node, ending_node, vertices); //initialisation du f_score f(n) = g(n) + h(n) comme  g_score[starting_node] = 0 on ne le met pas
    priority_queue.push({f_initial_score, starting_node}); //attention on a f_initial = heuristique car la distance cumulée au noeud de départ est 0, on initialise lalgo

    while (!priority_queue.empty()) { //tant qu'on a des noeuds à explorer
        auto [f_current_score, current_node] = priority_queue.top(); //on traite le noeud avec le f_score le plus petit en premier puis
        priority_queue.pop(); //on le supprime

        if (current_node == ending_node) { //si le noeuf atteint est celui qu'on voulait atteindre : on retourne g_score la distance reellle depuis le depart
            return g_score[current_node];
        }

        double current_g_score = f_current_score - heuristique(current_node, ending_node, vertices); //f(n) = g(n) + h(n) d'ou g(n) = f(n) - h(n)

        if (current_g_score > g_score[current_node]) { //si on a trouvé un raccourci après avoir inséré un f_score, pour un même noeud, plus élevé dans un premier temps
            continue;
        }

        for (const auto& edge : graph[current_node]) { // on parcourt toutes les arretes du noeud prometteur exploré actuellement, qui mènent à dautres noeuds
            double new_g_score = current_g_score + edge.length; //calcul de la distance reelle pour le noeud qui mène à l'arrete en cours dexplroation
            int neighbor_node_id = edge.destination_id; // id du noeud de l'arrete qu'on traite

            if (new_g_score < g_score[neighbor_node_id]) { //meme logique que dijkstra, si on a trouvé une distance reelle plus petite ici a travers l'arrete et noeud qu'on est en train d'explorer, on met à jour le tableau g_score et parents
                g_score[neighbor_node_id] = new_g_score;
                parents[neighbor_node_id] = current_node;
                double new_f_score = new_g_score + heuristique(neighbor_node_id, ending_node, vertices); //calcul du nouveau f_score = g + h associé à ce noeud voisin, il sera traité en 1er ou non en fonction de si son f_score le plus bas ou non 
                priority_queue.push({new_f_score, neighbor_node_id}); //push du score
            }
        }
    }

    return -1.0; //en cas derreur rencontrée dans le graphe : notamment si on a plus rien dans la priority queue sans etre arrivé au noeud final (passage bloqué/ mauvais noeud/ETC)
}