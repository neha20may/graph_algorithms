//
// Created by neha2 on 12-01-2022.
//

#include "graph.h"
#include <bits/stdc++.h>

using namespace std;

class graph {
    typedef vector<int> vt;
    typedef vector<vector<bool>> vvt;
    typedef vector<list<int>> list_edges;
    vt nodes;
    vvt edges;
    list_edges edges_2;
    bool mat_rep;
public:
    graph() = default;

    graph(vt &n, vvt &e, bool rep = true) : nodes(n), edges(e), mat_rep(rep) {}

    graph(vt &n, list_edges &e, bool rep = false) : nodes(n), edges_2(e), mat_rep(rep) {}

    const vvt &get_matrix_edges() const {
        return edges;
    }

    const list_edges &get_list_edges() const {
        return edges_2;
    }

    const vt &get_nodes() const {
        return nodes;
    }

    void set_matrix_edges(vvt &e) {
        edges = move(e);
    }

    void set_list_edges(list_edges &e) {
        edges_2 = move(e);
    }

    void set_nodes(vt &n) {
        nodes = move(n);
    }

//copy constructor
    graph(const graph &t) {
        auto nt = t.get_nodes();
        nodes.resize(nt.size());
        copy(nt.begin(), nt.end(), nodes.begin());
        if (mat_rep) {
            auto et = t.get_matrix_edges();
            edges.resize(et.size());
            copy(et.begin(), et.end(), edges.begin());
            mat_rep= true;
        } else {
            auto et = t.get_list_edges();
            edges_2.resize(et.size());
            copy(et.begin(), et.end(), edges_2.begin());
            mat_rep= false;
        }
        //dont know yet if copy is copy or move! //const should make it copy not move
    }

    graph operator=(const graph &t) {
        auto nt = t.get_nodes();
        nodes.resize(nt.size());
        copy(nt.begin(), nt.end(), nodes.begin());
        if (mat_rep) {
            auto et = t.get_matrix_edges();
            edges.resize(et.size());
            copy(et.begin(), et.end(), edges.begin());
        } else {
            auto et = t.get_list_edges();
            edges_2.resize(et.size());
            copy(et.begin(), et.end(), edges_2.begin());
        }
        return *this;
    }

    graph(graph &&t) {
        nodes = move(t.get_nodes());
        if (mat_rep)
            edges = move(t.get_matrix_edges());
        else
            edges_2 = move(t.get_list_edges());
    }

    graph operator=(graph &&t) {
        nodes = move(t.get_nodes());
        if (mat_rep)
            edges = move(t.get_matrix_edges());
        else
            edges_2 = move(t.get_list_edges());
    }

    friend ostream &print_graph(ostream &o, const graph &t) {
        o << ":: graph is as given below ::" << endl;
        o << "nodes of the graph are" << endl;
        auto n = t.get_nodes();
        copy(n.begin(), n.end(), ostream_iterator<int>(o, " "));
        o << endl;
        if (t.mat_rep) {
            o << "printing matrix representation" << endl;
            auto e = t.get_matrix_edges();
            auto N = t.get_nodes().size();
            for (auto i = 0; i < N; i++) {
                for (auto j = 0; j < N; j++) {
                    o << e[i][j] << " ";
                }
                o << endl;
            }
        } else {
            o<<"printing list representation "<<endl;
            auto e = t.get_list_edges();
            auto N = t.get_nodes().size();
            for (int i = 0; i < N; i++) {
                o << i << "-> ";
                auto l = e[i];
                copy(l.begin(), l.end(), ostream_iterator<int>(o, " "));
                o << endl;
            }

        }
    }


};