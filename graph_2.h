//
// Created by neha2 on 24-01-2022.
//

#ifndef DYNAMIC_PROGRAMMING_GRAPH_2_H
#define DYNAMIC_PROGRAMMING_GRAPH_2_H

#include <bits/stdc++.h>

using namespace std;

class Graph {
    int V;
    list<int> *adj;
    int time=0;
public:
    Graph(int v) : V(v) {
        adj = new list<int>[V];//array //So imp i messed up here!
    };

    void addEdge(int u, int v);

    void DFS(int s);

    void BFS(int s);

    void topological_sort();
    void SCC();

private:
    void DFS_helper(int v, vector<bool> &, map<int,int, greater<int>>&);
};

#endif //DYNAMIC_PROGRAMMING_GRAPH_2_H
