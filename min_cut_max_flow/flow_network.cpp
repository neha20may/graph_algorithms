//
// Created by neha2 on 16-03-2022.
//
#include <bits/stdc++.h>
#include "flow_edge.h"
#include "flow_network.h"

using namespace std;

flow_network::flow_network(int V) {
    V_ = V;
    adj_ = vector<list<flow_edge*>>(V);
    for (int i = 0; i < V; i++) {
        auto iv = adj_[i];
        auto bi = list<flow_edge*>();
        iv=bi;
    }
};

flow_network::flow_network(istream &i) {};

void flow_network::add_edge(flow_edge* &e) {
    int f = e->from();
    int t = e->to();
    adj_[f].push_back(e); //same e is pushed
    adj_[t].push_back(e);
};

list<flow_edge *> flow_network::adj(int v) {
   return adj_[v];
};

list<flow_edge *>::iterator flow_network::edges(){
    auto start=adj_.begin();
    auto sst=start->begin();
    return sst;
};

int flow_network::V(){
    return V_;
};

int flow_network::E(){
    int count=0;
    auto  start=adj_.begin();
    while(start!=adj_.end()){
        auto l=*start;
        auto lstart=l.begin();
        while(lstart!=l.end())
        {   count+=1;
            lstart++;
        }
        start++;
    }
    return  count/2;
};

ostream &operator<<(ostream &o, flow_network &f) {
    o<<"flow network "<<endl;
    for(int i=0; i<f.V_; i++){
        o<<"vertex:: "<<i<<endl;
        auto li=f.adj_[i];
        auto bli=li.begin();
        auto eli=li.end();
        while(bli!=eli){
            flow_edge  *e=*bli;
            cout<<" "<<*e;
            bli++;
        }

    }
    return o;
};
