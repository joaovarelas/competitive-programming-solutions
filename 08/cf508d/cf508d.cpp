#include <bits/stdc++.h>

#define NMAX 200001
#define INVALID -1

using namespace std;

typedef unsigned long long int ull;
typedef long long int ll;
typedef vector<int> vi;
typedef vector<ull> vu;
typedef vector<ll> vl;
typedef vector<bool> vb;
typedef vector<string> vs;
typedef pair<int,int> Pair;
typedef vector<Pair> vp;

int path[NMAX];
int idx = 0;

/* Hierholzer's algorithm O(E) 
   Adaptação do pseudocódigo em: 
   http://www.dcc.fc.up.pt/~pribeiro/estagio2008/usaco/3_3_EulerianTour.htm 

   https://www.youtube.com/watch?v=8MpoO2zA2l4 */
void dfs(list<int>* adj, int* outdeg, int v){

    //printf("dfs | v %d | out %d\n", v, outdeg[v]);

    while(adj[v].size()){
        int w = adj[v].front();
        adj[v].pop_front();
        dfs(adj, outdeg, w);
    }
    
    /*
    while(outdeg[v]){
        int w = --outdeg[v];
        dfs(path, adj, outdeg, adj[v][w]); // stack limit on test30
        }*/
    
    path[idx++] = v;
    return;
}


int main(){

    // number of edges
    // pwd size = m+2
    int m;
    cin >> m;

    // map node identifiers to int (and reverse)
    unordered_map<string, int> Map;
    unordered_map<int, string> Pam;

    // store adjs and vertices degree
    list<int> adj[2*m+1];
    int indeg[2*m+1];
    int outdeg[2*m+1];

    // number of nodes
    int n = 0;
    
    int i = 1;
    while(i <= m){
        
        string s; cin >> s;
     
        // abc: ab -> bc
        string a = s.substr(0, 2), b = s.substr(1, 2);
        
        // map string to int
        // map int to string
        if(!Map[a]) Map[a] = ++n, Pam[n] = a, indeg[Map[a]] = 0, outdeg[Map[a]] = 0;
        if(!Map[b]) Map[b] = ++n, Pam[n] = b, indeg[Map[b]] = 0, outdeg[Map[b]] = 0;
        
        int x = Map[a], y = Map[b];

        // add adjacent
        adj[x].push_back(y); //adj[y].push_back(x);

        // count degree of vertices
        outdeg[x]++; indeg[y]++;
        
        ++i;
    }


    // https://cses.fi/book/book.pdf
    // "Eulerian Paths"
    // - all nodes have even degree
    // or
    // - exactly 2 nodes degree differ
    //   by 1 and the rest is even
    int root = 1;
    int in = 0, out = 0;
    bool circuit = true;

    for(i = 1; i <= n; i++){
        if(indeg[i] == outdeg[i])
            continue;

        // not a circutir, could be a path
        circuit = false;
        
        if(indeg[i] - outdeg[i] == 1) ++in;

        // start at the node with which outdeg > indeg
        if(outdeg[i] - indeg[i] == 1) ++out, root = i;
    }

    // impossible
    if(!circuit && in != 1 && out != 1){
        cout << "NO" << endl;
        return 0;
    }

    idx = 0;
    dfs(adj, outdeg, root);

    //for(auto p : path) cout << p << " ";
    
    if(idx != m+1){
        cout << "NO" << endl;
        return 0;
    }

    cout << "YES" << endl;

    // print answer
    i = idx-1;
    cout << Pam[path[i--]];
    while(i >= 0) cout << Pam[path[i--]][1];
    
    
    cout << endl;

    return 0;
}
