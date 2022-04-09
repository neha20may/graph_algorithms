//
// Created by neha2 on 16-03-2022.
//

#ifndef GRAPH_ALGORITHMS_FORD_FULKERSON_H
#define GRAPH_ALGORITHMS_FORD_FULKERSON_H
#include <bits/stdc++.h>
#include "flow_edge.h"
#include "flow_network.h"
using namespace  std;
class ford_fulkerson{
    vector<bool> marked;
    vector<flow_edge*> edgeTo;
    double value_;
public:
    ford_fulkerson(flow_network &G, int s, int t);
    bool hasAugPath(flow_network &G, int s, int t);
    double value();
    bool inCut(int v);

};
#endif //GRAPH_ALGORITHMS_FORD_FULKERSON_H
