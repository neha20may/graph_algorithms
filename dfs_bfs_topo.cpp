//
// Created by neha2 on 19-01-2022.
//

using namespace std;

#include <bits/stdc++.h>
#include "graph_2.h"

int main() {
    int N = 3;
    Graph g(10);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);
//    g.DFS(0); //inbuilt is topological order
//    g.topological_sort();
    g.BFS(2);
    return 0;
}