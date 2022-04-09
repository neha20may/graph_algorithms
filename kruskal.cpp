//
// Created by neha2 on 12-01-2022.
//
//#include "graph.cpp"
#include<bits/stdc++.h>

using namespace std;

struct vertex {
    int id;
    vertex *parent;
    int size;

    vertex() = default;

    vertex(int v, vertex *p, int s) : id(v), parent(p), size(s) {}

    bool operator==(vertex b) {
        return id == b.id ? true : false;
    }
};

struct edge {
    vertex v1;
    vertex v2;
    int weight;

    edge(vertex &a, vertex &b, int w) : v1(a), v2(b), weight(w) {}

    bool operator<(edge a) {
        return a.weight > weight ? true : false;
    }
};

struct graph2 {
    //representation
    vector<list<vertex>> edges;
    vector<vertex> vertices;

    graph2() {}

    graph2(vector<vertex> &v, vector<list<vertex>> &e) : edges(e), vertices(v) {}
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

void add_mat_edges(int node1, int node2, vector<vector<bool>> &edges);

void add_list_edges(int node1, int node2, vector<list<int>> &edges_2);

void add_list_edges2(vertex &node1, vertex &node2, vector<list<vertex>> &edges);

int find_set(vertex &a, vector<int> &u);

bool isCycle(vertex &a, vertex &b);

void fill_first_node(vector<list<vertex>> &edges, int N);

void union_vertex(vertex &a, vertex &b, vector<int> &u);
vector<int > size_array;
int main() {
    ifstream ifile("C:\\Users\\neha2\\CLionProjects\\Coursera_part2\\graph_algorithm\\graph_file.txt");
    int N, vertex_1, vertex_2, weight;
    vector<list<vertex>> edges;
    vector<edge> E;
    vector<int> union_vertices;
    static int i = 0;
    if (ifile.is_open()) {
        ifile >> N;
        edges.resize(N);
//        fill_first_node(edges,N);
        while (ifile.good()) {
            ifile >> vertex_1 >> vertex_2 >> weight;
            vertex *v1 = new vertex(vertex_1, nullptr, 0);
            vertex *v2 = new vertex(vertex_2, nullptr, 0);
            edge e(*v1, *v2, weight);
            add_list_edges2(*v1, *v2, edges);
            E.push_back(e);
        }
    }
    int mst_weight=0;
    vector<list<vertex>> mst_edges(N);
    union_vertices.resize(N);
    for_each(union_vertices.begin(), union_vertices.end(), [](int &vi){vi=i++;});
    size_array.resize(N,0);
    sort(E.begin(), E.end());
    for (edge &e: E) {
        vertex &v1 = e.v1;
        vertex &v2 = e.v2;
        int v1_root = find_set(v1, union_vertices);
        int v2_root = find_set(v2, union_vertices);
        if (!(v1_root == v2_root)) {
            add_list_edges2(v1, v2, mst_edges);
            union_vertex(v1, v2, union_vertices);
            mst_weight+=e.weight;
        }
    }
    vector<vertex> V(N);
    i=0;
    for_each(V.begin(), V.end(), [](vertex &v) { v.id = i++; });
    graph2 graph(V, edges);
    graph2 MST(V, mst_edges);
    cout << "original graph" << endl;
    print_graph(graph);
    cout << "MST of graph" << endl;
    print_graph(MST);
    cout<<"mst edge_weight "<<mst_weight<<endl;
    return 0;
}

void fill_first_node(vector<list<vertex>> &edges, int N) {
    for (int i = 0; i < N; i++) {
        vertex *v = new vertex(i, nullptr, 0);
        v->parent = v;
        edges[i].push_front(*v);
    }
}

//bool isCycle(vertex & a, vertex &b) {
//    //will it copy it right , will it copy the right reference?
//    if (find_set(a) == find_set(b))
//        return true;
//    else
//        return false;
//}

//size constraint makes the complexity of it log n or so.
int find_set(vertex &v, vector<int> &union_array) {
    int i = v.id;
    while (i != union_array[i])
        i = union_array[i];
    return i;

}

void union_vertex(vertex &a, vertex &b, vector<int> &uarray) {
    auto a_p = find_set(a, uarray);
    auto b_p = find_set(b, uarray);
    if (size_array[a_p]<size_array[b_p])
    {
        uarray[a_p]=b_p;
        size_array[a_p]+=size_array[b_p]+1;
    } else {
        uarray[b_p]=a_p;
        size_array[b_p]+=size_array[b_p]+1;

    }
}

void add_list_edges2(vertex &node1, vertex &node2, vector<list<vertex>> &edges) {
    auto n1 = node1.id;
    auto n2 = node2.id;
    edges[n1].push_back(node2);
    edges[n2].push_back(node1); //undirected graph
}

void add_list_edges(int node1, int node2, vector<list<int>> &edges_2) {
//    auto *l = &edges_2[node1];//[] gives segmentation error //no RaNGE CHECK
//    auto m = edges_2[node2];
    auto l = edges_2.begin() + node1;
//    auto m = edges_2.begin() + node2;
    l->push_back(node2);
//    (*m).push_front(node1); //undirected graph

}

void add_mat_edges(int node1, int node2, vector<vector<bool>> &edges) {
    edges[node1][node2] = true;
//    edges[node2][node1] = true;//undirected graph
//how can it be overwritten?
//    auto i = edges.begin() + node1;
//    auto j = (*i).begin() + node2;
//    *j = true;
}


