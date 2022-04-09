//
// Created by neha2 on 24-01-2022.
//
#include "graph_2.h"

void Graph::addEdge(int u, int v) {
    adj[u].push_back(v); //directed
}

void Graph::DFS(int s) {
    /**
     * take vertex and call dfs on adjacency, check if adj has been visited already
     *           a ( a -> b, c -> a)
     *          / \
     *         b--->c
     *         a, the dfs(b), then dfs(c)-> dfs(a) already visited, ....
     */
    int N = V;
    map<int, int, greater<int>> finish_time;
    vector<bool> closed(N, false);
    cout << "DFS traversal is " << endl;
    DFS_helper(s, closed, finish_time);
    int vertex_traveled = accumulate(closed.begin(), closed.end(), 0);
    if (vertex_traveled != N) {
        for (int i = 0; i < N; i++) {
            if (!closed[i])
                DFS_helper(i, closed, finish_time);
        }
    }
    cout << endl;
    cout << "topological order is " << endl;
//    std::reverse(finish_time.begin(), finish_time.end()); //Error!
//    vector<pair<int, int>>time(finish_time.begin(), finish_time.end()); //Alternative //better uis to use greater<int> or reverse iterator of map.
//    reverse(time.begin(), time.end());
    for (auto x: finish_time) {
        int time = x.first;
        int v = x.second;
        cout << v << " ";
    }
    cout << endl;

}

void Graph::topological_sort() {
    DFS(0); //any random vertex can be taken up.
}

void Graph::BFS(int s) {
    /**
     * level wise traversal;put all adjacent in a Queue
     */
    queue<int> open;
    vector<bool> closed(V, false);
    open.push(s);
    while (!open.empty()) {
        int u = open.front();
        open.pop();
        if (!closed[u]) {
            cout<<u<<" ";
            for (int v: adj[u]) {
                open.push(v);
            }
            closed[u]=true;
        }

    }

}

void Graph::DFS_helper(int v, vector<bool> &closed, map<int, int, greater<int>> &finish_time) {
    if (closed[v] == true)
        return;
    else {
        closed[v] = true;
        cout << v << "  ";
        time += 1;
        for (int v_: adj[v]) {
            DFS_helper(v_, closed, finish_time);
        }
        ++time;
        finish_time[time] = v;//each time is unique, hence bst of map.
    }
}
void Graph::SCC() {

}
