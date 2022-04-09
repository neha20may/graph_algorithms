//
// Created by neha2 on 16-03-2022.
//

#ifndef GRAPH_ALGORITHMS_FLOW_NETWORK_H
#define GRAPH_ALGORITHMS_FLOW_NETWORK_H
#include "flow_edge.h"
class flow_network{
//    struct hash_edges{
//        size_t operator()(const flow_edge &a)const{
//
//        }
//    };
    int V_;

    //for simplicity you can take vector, list, and any other container if there are no self loops and parallel edges
    vector<list<flow_edge*>> adj_;
public:
//    typedef unordered_multiset<vector<flow_edge>, hash_edges> bag; //this bag is needed for allowing parallel edges
    flow_network(int V);
    flow_network(istream &i);
    void add_edge(flow_edge* &e);
    list<flow_edge*>  adj(int v);
    list<flow_edge*>::iterator edges();
    int V();
    int E();
    friend ostream  & operator<<(ostream &o, flow_network &f);

};
#endif //GRAPH_ALGORITHMS_FLOW_NETWORK_H
