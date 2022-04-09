//
// Created by neha2 on 16-03-2022.
//

#include "ford_fulkerson.h"

//vector<bool> marked;
//vector<flow_edge> edgeTo;
//double value_;
ford_fulkerson::ford_fulkerson(flow_network &G, int s, int t) {
    value_ = 0.0;
    while (hasAugPath(G, s, t)) {
        double minv = INFINITY;
        for (int v = t; v != s; v = edgeTo[v]->other(v))
            minv = min(minv, edgeTo[v]->residual_capacity(v));

        for (int v = t; v != s; v = edgeTo[v]->other(v))
            edgeTo[v]->add_residual_flow_to(v, minv);

        value_ += minv;
    }
};

bool ford_fulkerson::hasAugPath(flow_network &G, int s, int t) {
    edgeTo = vector<flow_edge *>(G.V());
    marked = vector<bool>(G.V());
    queue<int> q = queue<int>();
    q.push(s);
    marked[s] = true;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        auto neighbors_list_i = G.adj(v);
        auto start = neighbors_list_i.begin();
        auto end = neighbors_list_i.end();
        while (start != end) {
            auto fe = *start;
            int w = fe->other(v);
            if (fe->residual_capacity(w) > 0 and !marked[w]) {
                edgeTo[w] = fe;
                marked[w] = true;
                q.push(w);
            }
            start++;
        }
    }
    return marked[t];
};

double ford_fulkerson::value() {
    return value_;
};

bool ford_fulkerson::inCut(int v) {
    return marked[v];
};
