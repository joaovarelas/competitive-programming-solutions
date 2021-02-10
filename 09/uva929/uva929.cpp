#include <bits/stdc++.h>

using namespace std;

#define INF numeric_limits<int>::max()

using ull = unsigned long long int;
using ll =  long long int;
using vi = vector<int>;
using vu =  vector<ull>;
using vl = vector<ll>;
using vb = vector<bool>;
using vs =  vector<string>;
using Pair = pair<int,int>;
using Triple = pair<Pair, int>;
using Quad = pair<Pair, Pair>;
template<class T> using heapmin = priority_queue<T, vector<T>, less<T>>;
template<class T> using heapmax = priority_queue<T, vector<T>, greater<T>>;

class Node {
public:
    int x, y, cost;

    Node(int x, int y, int c){
        this->x = x;
        this->y = y;
        this->cost = c;
    }

    bool operator < (const Node& other) const{
        return this->cost > other.cost;
    }
};

// get up, down, left, right neighbour cells
vector<Node> get_neighbours(int n, int m, Node v){
    vector<Node> neighbours;

    for(int i : vi{-1,1}){
        int x = max(1, min(n-1, v.x+i));
        neighbours.push_back(Node(x, v.y, v.cost));
    }

    for(int i : vi{-1,1}){
        int y = max(1, min(m-1, v.y+i));
        neighbours.push_back(Node(v.x, y, v.cost));
    }
    
    return neighbours;
}


// Dijkstra algorithm
// path with minimum cost from (1,1) to (n,m)
// Time: ~O(n*m*log(n*m))
int dijkstra(vector<vi> maze){
    int n = maze.size(),
        m = maze[1].size();
    
    Node root(1, 1, maze[1][1]);

    vector<vi> cost(n, vi(m, INF));
    cost[1][1] = root.cost;
  
    heapmin<Node> pq;
    pq.push(root);

    while(!pq.empty()){
        
        Node v = pq.top();
        pq.pop();

        //printf("popped ( (%d,%d), %d )\n", v.x, v.y, v.cost);

        for(Node w : get_neighbours(n, m, v)){
            // update better cost
            if(cost[v.x][v.y] + maze[w.x][w.y] < cost[w.x][w.y]){
                cost[w.x][w.y] = cost[v.x][v.y] + maze[w.x][w.y];
                pq.push(Node(w.x, w.y, cost[w.x][w.y]));
            }
        }
        
    }

    return cost[n-1][m-1];
}


int main(){

    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;

        vector<vi> maze(n+1, vi(m+1, 0));
        
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= m; j++){
                cin >> maze[i][j];
            }
             
        int min_cost = dijkstra(maze);
        cout << min_cost << endl;

    }
    
    return 0;
}
