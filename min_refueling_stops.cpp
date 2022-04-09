//
// Created by neha2 on 07-04-2022.
//
#include <bits/stdc++.h>

using namespace std;

class Solution {
    class node {
        int distance;
        int fuel;
        int index;
    public:
        node() {}

        node(int d, int f, int index) : distance(d), fuel(f), index(index) {}

        int getDis() const {
            return distance;
        }

        int getFuel() {
            return fuel;
        }

        void setFuel(int f) {
            fuel = f;
        }

        int getIndex() {
            return index;
        }
    };

    class edge {
        int weight;
        int from;
        int to;
    public:
        edge(int f, int t, int w) : weight(w), from(f), to(t) {}

        int getOther(int v) {
            if (v == from) return to;
            if (v == to) return from;
        }

        int getWeight() { return weight; }
    };

    class graph {
        int V;
        vector<node *> vertices;
        vector<edge *> *adj;
    public:
        graph(vector<node *> v, vector<edge *> *ad) : vertices(v), adj(ad) {
            V = v.size();
        }

        vector<edge *> *getAdj() {
            return adj;
        }

        int getV() {
            return V;
        }

        vector<node *> getVertices() {
            return vertices;
        }
    };

public:
    graph *createGraph(vector<vector<int>> &stations, int startFuel, int target) {
        vector<node *> vertices;
        node *start = new node(0, startFuel, 0);
        vertices.push_back(start);
        int i = 1;
        for (auto p: stations) {
            int dist = p[0], fuel = p[1];
            node *n = new node(dist, fuel, i++);
            vertices.push_back(n);
        }
        vertices.push_back(new node(target, -1, i++));

        int V = vertices.size();
        //vector<edge> *adj[];
        vector<edge *> *adj = new vector<edge *>[V];
        for (int i = 0; i < V - 1; i++) {
            node *a = vertices[i];
            for (int j = i + 1; j < V; j++) {
                node *b = vertices[j];
                edge *e = new edge(i, j, abs(a->getDis() - b->getDis()));
                adj[i].push_back(e);
                adj[j].push_back(e);
            }
        }
        graph *g = new graph(vertices, adj);
        return g;
    }

    void print(graph *g) {
        vector<edge *> *adj = g->getAdj();
        int V = g->getV();
        for (int i = 0; i < V; i++) {
            vector<edge *> edges = adj[i];
            cout << "from vertex =" << i;
            for (edge *e: edges) {
                cout << " to = " << e->getOther(i) << " distance=" << e->getWeight() << "; ";
            }
            cout << endl;
        }

    }

public:
    struct comp {
        bool operator()(const node *a, const node *b) const {
            return (a->getDis() < b->getDis());
        }
    };

    int minRefuelStops(int target, int startFuel, vector<vector<int>> &stations) {
        graph *g = createGraph(stations, startFuel, target);
        print(g);
        vector<node *> vertices = g->getVertices();
        int V = g->getV();
        node *start = vertices[0];
        node *tgt = vertices[V - 1];
        vector<edge *> *adj = g->getAdj();
        int startF = start->getFuel();
        priority_queue<node *, vector<node *>, comp> q;
        q.push(start);
        vector<bool> visited(V, false);
        bool ans = false;
        int stops = 0;
        cout << "BFS / Longest path starting " << endl;
        while (!q.empty()) {
            node *cur = q.top();
            cout << "node =" << cur->getIndex() << " dist =" << cur->getDis() << " fuel =" << cur->getFuel() << endl;
            q.pop();
            stops++;
            visited[cur->getIndex()] = true;
            if (cur == tgt) {
                ans = true;
                break;
            } else {
                vector<node *> neighbors;
                vector<edge *> edges = adj[cur->getIndex()];
//                for(auto e: edges){
//                    if(e->getWeight()<=cur->getFuel()){
//                        neighbors.push_back(vertices[e->getOther(cur->getIndex())]);
//                    }
//                }
//                for(auto neigh: neighbors){
//                    if(visited[neigh->getIndex()]== false)
//                        q.push(neigh);
//                }
                /**
                 * this is pure BFS till now , now edge weights are not negative, this becomes, dijkstra or prim .
                 * Choose edge with max distance
                 *
                 */
                node *nextNode;
                int max_dist = -1;
                int cur_fuel = cur->getFuel();
                int cur_index = cur->getIndex();
                node *next;
                for (auto e: edges) {
                    if (e->getWeight() <= cur->getFuel()) {
                        int dist = e->getWeight();
                        int fuel_left = cur_fuel - dist;
                        int next_index = e->getOther(cur_index);
                        next = vertices[next_index];
                        int next_fuel = fuel_left + next->getFuel();
                        if (!visited[next_index]) {
                            next->setFuel(next_fuel);
                            q.push(next);
                        }
                    }

                }


            }
        }
        if (ans == true)
            return stops;
        else
            return -1;
    }
};

int main() {
    Solution s;
//    stations = [[10,60],[20,30],[30,30],[60,40]]
    vector<vector<int>> v = {{10, 60},
                             {20, 30},
                             {30, 30},
                             {60, 40}};
    s.minRefuelStops(100, 10, v);
}