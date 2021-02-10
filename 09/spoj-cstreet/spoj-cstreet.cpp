#include <bits/stdc++.h>

using namespace std;

#define INF numeric_limits<int>::max()

using ull = unsigned long long int;
using ll =  long long int;
template<class T1, class T2> using u_map = unordered_map<T1, T2>;
template<class T> using vec = vector<T>;
template<class T> using Pair =  pair<T,T>;
template<class T> using heapmin = priority_queue<T, vector<T>, less<T>>;
template<class T> using heapmax = priority_queue<T, vector<T>, greater<T>>;

class Node{
public:
    int v, len;

    Node(int v, int w){
        this->v = v;
        this->len = w;
    }
    
    bool operator < (const Node& other) const {
        return this->len > other.len;
    }
};

// Prim algorithm for minimum spanning tree
// Dense graph (possibly too many streets/edges vs. no of vertices)
// Worst case: O(n²)
ll prim(vec<vec<int>> adj, int n){
    ll total = 0;
    int root = 1;
    
    vec<ll> cost(n+1, INF);
    vec<bool> visited(n+1, false);
    cost[root] = 0;

    heapmin<Node> pq;
    pq.push(Node(root, cost[root]));

    while(!pq.empty()){
        Node node = pq.top();
        pq.pop();
        
        int v = node.v;
        int c = node.len;

        if(!visited[v]){
            visited[v] = true;
            total += c;

            for(int w = 1; w <= n; w++){
                if(adj[v][w] == -1) continue;

                pq.push(Node(w, adj[v][w]));                
            }
        }
        
    }
    
    return total;
}

int main(){
    int t;
    cin >> t;
    while(t--){
        // p: price per furlong
        // n: number of vertices
        // m: number of edges
        int p, n, m;
        cin >> p >> n >> m;

        vec<vec<int>> adj(n+1, vec<int>(n+1, -1));

        // read weighted edges
        for(int i = 1; i <= m; i++){
            int a, b, len;
            cin >> a >> b >> len;
            adj[a][b] = len;
            adj[b][a] = len;
        }

        ll min_cost = prim(adj, n);
        cout << p*min_cost << endl;
        
    }
    
    return 0;
}
