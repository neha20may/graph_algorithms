//
// Created by neha2 on 16-03-2022.
//

#ifndef GRAPH_ALGORITHMS_FLOW_EDGE_H
#define GRAPH_ALGORITHMS_FLOW_EDGE_H

#include <bits/stdc++.h>

using namespace std;

class flow_edge {
    int from_, to_;
    double capacity_;
    int flow_;
public:
    flow_edge(){};
    flow_edge(int from, int to, double capacity) : from_(from), to_(to), capacity_(capacity) {flow_=0;};

    int from();

    int to();

    int other(int vertex);

    double capacity();

    double flow();

    double residual_capacity(int v) const; //residual capacity towrds v
    void add_residual_flow_to(int v, double delta); //add delta flow towards v
    friend ostream &operator<<(ostream &os, const flow_edge &e);
};

#endif //GRAPH_ALGORITHMS_FLOW_EDGE_H
