#include<bits/stdc++.h>
using namespace std;
class node{
public:
    int index, cost;
    node(int i, int c):index(i), cost(c){}
    // bool operator==(node *b){
    //     if(index==b->index and cost==b->cost)
    //     return 1;
    //     else
    //     return false;
    // }
    // bool operator<(const node*b){
    //     return (cost<b->cost);
    // }
};
class graph{
public:
    int V;
    vector<node*> *adj;
    graph(int v, vector<node*>*a): V(v), adj(a){}
};
void print(graph * g){
    vector<node*> *adj=g->adj;
    int N=g->V;
    for(int i=0;i<N;i++){
        cout<<"vertex i ="<<i<<"-> ";
        for(node* n:adj[i]){
            cout<<n->index<<" ";
        }
        cout<<endl;
    }
}
graph * create_graph(int N, vector<int> &cost, vector<vector<int>> &edges, vector<node*> &vertices){

    for(int i=0;i<N; i++){
        node * n=new node(i, cost[i]);
        vertices.push_back(n);
    }
    // cout<<"checkpoint 1"<<endl;
    vector<node*> *adj=new vector<node*>[N];
    for(auto e:edges){
        int u=e[0]-1, v=e[1]-1;
        // cout<<u<<" " <<v<<endl;
        node*nu=vertices[u];
        node*nv=vertices[v];
        adj[u].push_back(nv);
        adj[v].push_back(nu);
        // cout<<"semi checkpooint "<<endl;
    }
    // cout<<"checkpoint 2"<<endl;
    graph * g= new graph(N,adj);
    // cout<<"checkpoint 3"<<endl;
    return g;
}
struct comp{
    bool operator()(const node* a, const node* b){
        if(a->cost < b->cost);
    }
};
void bfs(graph* g, vector<bool> &visited, set<node*, comp> &pq, long long &ans){
    while(!pq.empty()){
        auto uit=min_element(pq.begin(), pq.end());
        node * u=*uit;
        cout<<"node u ="<<u->index<<" cost ="<<u->cost<<endl;
        visited[u->index]=true;
        // cout<<"cost ="<<u->cost<<endl;
        ans=ans+u->cost;
        pq.erase(uit);
        for(node* v: g->adj[u->index]){
            cout<<"v ="<<v->index<<"cost="<<v->cost<<endl;
            if(!visited[v->index]){
                // cout<<"visit false"<<endl;
                if((u->cost & v->cost)==0){
                    auto vit=pq.find(v);
                    cout<<"cost & v = "<<(*vit)->index<<"cost=" <<(*vit)->cost<<endl;
                    visited[(*vit)->index]=true;
                    pq.erase(vit);
                }
                else{
                    pq.insert(v);
                }
            }
            else{
                // cout<<"visit false"<<endl;
            }
        }
        // cout<<"checkpoint 4"<<endl;
    }
    // copy(visited.begin(), visited.end(), ostream_iterator<bool>(cout, " ")); cout<<endl;
}
long long solve (int N, vector<int> cost, vector<vector<int> > edges) {
    // Write your code here
    vector<node*> vertices;
    graph * g=create_graph(N, cost, edges, vertices);
    print(g);
    vector<bool> visited(N, false);
    // priority_queue<node*, vector<node*>, comp> pq;
    set<node*, comp> pq;
    for(auto v:vertices)
        pq.insert(v);
    long long ans=0;
    copy(visited.begin(), visited.end(), ostream_iterator<bool>(cout, " ")); cout<<endl;
    for(int i=0;i<N; i++){
        if(visited[i]==false)
        {
            cout<<"start i "<<i<<endl;
            pq.insert(vertices[i]);
            bfs(g,visited, pq, ans);
            copy(visited.begin(), visited.end(), ostream_iterator<bool>(cout, " ")); cout<<endl;
        }
    }
    return ans;

}

int main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    for(int t_i = 0; t_i < T; t_i++)
    {
        int N;
        cin >> N;
        vector<int> cost(N);
        for(int i_cost = 0; i_cost < N; i_cost++)
        {
            cin >> cost[i_cost];
        }
        vector<vector<int> > edges(N-1, vector<int>(2));
        for (int i_edges = 0; i_edges < N-1; i_edges++)
        {
            for(int j_edges = 0; j_edges < 2; j_edges++)
            {
                cin >> edges[i_edges][j_edges];
            }
        }

        long long out_;
        out_ = solve(N, cost, edges);
        cout << out_;
        cout << "\n";
    }
}