//
// Created by neha2 on 17-01-2022.
//
#include <bits/stdc++.h>

using namespace std;

struct vertex {
    int id;
    int dist;
    /**
     * TODO: can i use reference here instead of a pointer?
     * The problem is to use both pointer and iterator (cpp and C concepts), its better to use one, and I am choosing cpp over c, hence iterator.
     * */
    unordered_map<int, bool>::iterator parent;
    int edge_weight;

    vertex(int v, int k, unordered_map<int, bool>::iterator p, int w) : id(v), dist(k), parent(p), edge_weight(w) {}

    bool operator<(const vertex &b) const {
        if (dist < b.dist)
            return true;
        else if (id < b.id)
            return true;
        else
            return false;
    }

    bool operator==(const vertex &b) const {
        return id == b.id ? true : false;
    }

    friend ostream &operator<<(ostream &o, const vertex &b) {
        o << "<id=" << b.id << " dist=" << b.dist << ">";
        return o;
    }
};


struct graph2 {
    //representation
    vector<list<vertex>> edges;
    vector<vertex> vertices;

    graph2() {}

    graph2(vector<vertex> &v, vector<list<vertex>> &e) : edges(e), vertices(v) {}
};

struct AddValues {
    template<class Value, class Pair>
    Value operator()(Value value, const Pair &pair) const {
        return value + pair.second;
    }
};


void print_graph(graph2 &g) {
    cout << "graph is " << endl;
    for (vertex v: g.vertices) {
        cout << v.id << " ";
        auto list = g.edges[v.id];
        for (auto e: list) {
            cout << "-> " << e.id;
        }
        cout << endl;
    }
}

int read_input(vector<list<vertex>> &edges, unordered_map<int, bool>::iterator);

void relax_mst(set<pair<int, int>> &pq, vertex &v, int u,
               unordered_map<int, int> &parent_pointers, unordered_map<int, int> &keys);

void relax_dijkstra(set<pair<int, int>> &pq, vertex &v, int u,
                    unordered_map<int, int> &parents_pointer, unordered_map<int, int> &keys);

int main() {
    /**
     * 1. Instead of set, it is better to use std::map<dist, id>; dist is node id and id is its id(dist).
     * 2. The priority queue of cpp does not provide the decrease-dist operation, hence set is used.
     * 3. The complexity of both heap and BST is: find_min(bst)=logn; find_min(heap)=O(1); however, to extract the min, extract_min(bst)=log n( find lg n+ delete o(1)); extract_min(heap)=log n(delete first element and replace with last and heapify O(H) i.e., lgn);
     */
    vector<list<vertex>> edges;
    set<pair<int, int>> Q;
    unordered_map<int, bool> S; //it could be simply vector<bool>; where indices work like ids.
    unordered_map<int, int> parent_pointers;
    unordered_map<int, int> keys;
    int N = read_input(edges, S.end());
    vector<list<vertex>> &adj_list = edges;
    //mst take some random vertex as start
    //vertex start= some vertex for dijkstra
    //vertex target= some vertex for dijkstra; if no target is specified, dijkstra finfs path from src to all nodes in the graph.
    int src = 0;
    Q.insert(make_pair(0, src));
    for (int i = 0; i < N; i++) {
        keys[i] = INFINITY;
    }
    keys[0] = 0; //insert does not again insert the values;
    while (!Q.empty()) {
        auto ui = std::min_element(Q.begin(), Q.end());
        int u = ui->second;
        S[u] = true;
        Q.erase(ui);
        /**
         * TODO: what is the better way to represent graph, adj list and edges in the weighted graph?
         * All need to be maintained separately, and connected through ids.
         * Keep in mind, it is all id semantics, unless specified otherwise.
         */
        for (vertex &v: adj_list[u]) {
            auto vi = S.find(v.id); //only if v is not in S, relax (u,v)
            if (vi == S.end()) {
                relax_mst(Q, v, u, parent_pointers, keys);
//                relax_dijkstra(Q, v, u, parent_pointers, keys);
            }

        }
    }
    /**
     * MST printing
     */
    cout << "vertex  in order are " << endl;
    for (int i = 0; i < N; i++) {
        cout << i << " <- " << parent_pointers[i] << endl;
    }
    AddValues a;
    auto D = accumulate(keys.begin(), keys.end(), 0, a);
    cout << "minimum spanning weight is" << D << endl;

    /**
    * Dijkstra printing
    */
//    auto t = 0;
//    while (t++ < 8) {
//        cout << "Target " << t << ". Path from source to target is :: ";
//        int i = t;
//        cout << i;
//        while (i != src) {
//            cout << " <- " << parent_pointers[i];
//            i = parent_pointers[i];
//        }
//        cout << endl;
//        cout << "distance :: " << keys[t] << endl;
//    }


}

void relax_dijkstra(set<pair<int, int>> &pq, vertex &v, int u,
                    unordered_map<int, int> &parent_pointers, unordered_map<int, int> &keys) {
    if (keys[v.id] > v.edge_weight + keys[u]) {
        keys[v.id] = v.edge_weight + keys[u];
        parent_pointers[v.id] = u;
        pq.insert(make_pair(keys[v.id],
                            v.id)); //ideally we need to update key here, but not possible so allowing duplicates and filtering it from S.
    }
}

void relax_mst(set<pair<int, int>> &pq, vertex &v, int u,
               unordered_map<int, int> &parent_pointers, unordered_map<int, int> &keys) {
    if (keys[v.id] > v.edge_weight) {
        keys[v.id] = v.edge_weight;
        parent_pointers[v.id] = u;
        pq.insert(make_pair(keys[v.id],
                            v.id));
    }
}

void add_list_edges2(vertex &node1, vertex &node2, vector<list<vertex>> &edges) {
    auto n1 = node1.id;
    auto n2 = node2.id;
    edges[n1].push_back(node2);
    edges[n2].push_back(node1); //undirected graph
}

int read_input(vector<list<vertex>> &edges, unordered_map<int, bool>::iterator it) {
    ifstream ifile("C:\\Users\\neha2\\CLionProjects\\Coursera_part2\\graph_algorithm\\graph_file.txt");
    int N;
    int vertex1, vertex2, weight;
    if (ifile.is_open()) {
        ifile >> N;
        edges.resize(N);
        while (ifile.good()) {
            ifile >> vertex1 >> vertex2 >> weight;
            vertex *v1 = new vertex(vertex1, INFINITY, it, weight);
            vertex *v2 = new vertex(vertex2, INFINITY, it, weight);
            add_list_edges2(*v1, *v2, edges);
        }
    }
    return N;
}

