#include <bits/stdc++.h>

#define NMAX 256

using namespace std;

typedef unsigned long long int ull;
typedef long long int ll;
typedef vector<int> vi;
typedef vector<ull> vu;
typedef vector<ll> vl;
typedef vector<bool> vb;
typedef vector<string> vs;
typedef vector<char> vc;
typedef pair<int,int> Pair;


// find all topological sorts of the DAG
bool dfs_topsort(vc vert, vector<vb> edge, vi indegree, vb visited, vc order){

    bool flag = false;
    
    for(char v : vert){
        // only consider unvisited vertices with 0 indegree
        if(indegree[v] != 0 || visited[v])
            continue;

        // add 'v' to order, mark as visited
        // and reduce indegree of adjacent
        order.push_back(v);
        visited[v] = true;
        for(char w : vert)
            if(edge[v][w])
                --indegree[w];

        // recursive
        dfs_topsort(vert, edge, indegree, visited, order);

        // remove 'v' from order, mark as unvisited
        // and increase indegree of adjacent
        // backtrack
        order.erase(order.end()-1);
        visited[v] = false;
        for(char w : vert)
            if(edge[v][w])
                ++indegree[w];

        flag = true;

    }

    // if all vertices visited
    // print this order
    if(!flag && order.size()){
               
        cout << order[0];
        for(int i = 1; i < vert.size(); i++)
            cout << " " << order[i];
        cout << endl;

    }                
     
    return flag;
}


bool topsort(vc vert, vector<vb> edge, vi indegree){
    vb visited(NMAX, false);
    vc order;

    return dfs_topsort(vert, edge, indegree, visited, order);
}

int main(){

    int t;
    cin >> t;

    while(t--){
        
        vc vert;
        vector<vb> edge(NMAX, vb(NMAX, false));
        vi indegree(NMAX, 0);
    
        // read vertices
        string s = "";
        while(s == "") getline(cin, s);

        // push vertices into vert[]
        for(char c : s)
            if(c != ' ')
                vert.push_back(c);

        // sort ascending/alphabetical order
        sort(vert.begin(), vert.end());

        // read precedences
        s = "";
        while(s == "") getline(cin, s);

        // add edges and count indegree of target vert
        for(int i = 0; i < s.size(); i += 4){
            char a = s[i], b = s[i+2];
            edge[a][b] = true;
            ++indegree[b];
        }
        
        // dfs topsort
        bool found = topsort(vert, edge, indegree);

        // no order found
        if(!found)
            cout << "NO" << endl;
       
        if(t) cout << endl;

    }

    return 0;
}
