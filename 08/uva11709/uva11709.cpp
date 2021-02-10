#include <bits/stdc++.h>

#define NMAX 1001

using namespace std;

typedef unsigned long long int ull;
typedef long long int ll;
typedef vector<int> vi;
typedef vector<ull> vu;
typedef vector<ll> vl;
typedef vector<bool> vb;
typedef vector<string> vs;
typedef pair<int,int> Pair;

// build stack pos-order
void dfs_visit(vector<vb> G, int n, int v, stack<int>& Stack, vb& visited){

    visited[v] = true;

    for(int w = 1; w <= n; w++)
        if(G[v][w] && !visited[w])
            dfs_visit(G, n, w, Stack, visited);
            
    Stack.push(v);
    return;
}

// init DFS
void dfs(vector<vb> G, int n, stack<int>& Stack){
    
    vb visited(NMAX, false);

    for(int v = 1; v <= n; v++)
        if(!visited[v])
            dfs_visit(G, n, v, Stack, visited);
        
    return;
}

// kosaraju algorithm to find SCC
int kosaraju(vector<vb> G, vector<vb> Gt, int n){

    int scc = 0;
    stack<int> Stack, dummy;

    // perform DFS on graph G to build stack in pos-order
    dfs(G, n, Stack);


    vb visited(NMAX, false);

    // perform DFS on transpose Gt by popping elems of stack
    while(!Stack.empty()){
        
        int v = Stack.top();
        Stack.pop();
        
        if(!visited[v]){
            dfs_visit(Gt, n, v, dummy, visited);
            ++scc;
        }
        
    }

    return scc;
}


int main(){

    int n, e;
    cin >> n >> e;

    while(n != 0){


        // read names and assign an integer (map)
        string s1, s2;
        map<string,int> Map;
        getline(cin, s1); // ignore empty line
        for(int i = 1; i <= n; i++){
            getline(cin, s1);
            Map[s1] = i;
        }

        // graph G and transpose Gt
        vector<vb> G(NMAX, vb(NMAX, false));
        vector<vb> Gt(NMAX, vb(NMAX, false));

        // read edges (trust)
        for(int i = 1; i <= e; i++){
            getline(cin, s1);
            getline(cin, s2);

            G[Map[s1]][Map[s2]] = true;
            Gt[Map[s2]][Map[s1]] = true;
        }


        // execute kosaraju algorithm to find SCC
        int scc = kosaraju(G, Gt, n);
        cout << scc << endl;
            
        cin >> n >> e;
    }
   

    return 0;
}
