//
// Created by neha2 on 16-03-2022.
//

#include <bits/stdc++.h>
#include "flow_network.h"
#include "ford_fulkerson.h"
using  namespace  std;
int main(){
    flow_network G(8);
    int s=0;
    int t=7;
    int v=0;
    flow_edge *e=new flow_edge(0, 1, 10);
    G.add_edge(e);
    e=new flow_edge(0, 2, 5);
    G.add_edge(e);
    e=new flow_edge(0,3,15);
    G.add_edge(e);
    e=new flow_edge(1,4, 9);
    G.add_edge(e);
    e=new flow_edge(1,5,15);
    G.add_edge(e);
    e=new flow_edge(1,2,4);
    G.add_edge(e);
    e=new flow_edge(2,5,8);
    G.add_edge(e);
    e=new flow_edge(2,3,4);
    G.add_edge(e);
    e=new flow_edge(3,6,16);
    G.add_edge(e);
    e=new flow_edge(4,5,15);
    G.add_edge(e);
    e=new flow_edge(4,7,10);
    G.add_edge(e);
    e=new flow_edge(5,6,15);
    G.add_edge(e);
    e=new flow_edge(5,7,10);
    G.add_edge(e);
    e=new flow_edge(6,7,10);
    G.add_edge(e);
    e=new flow_edge(6,2,6);
    G.add_edge(e);
    cout<<G;
    ford_fulkerson ford(G, 0,7);
    int max_flow=ford.value();
    cout<<"max flow "<<max_flow<<endl;

}