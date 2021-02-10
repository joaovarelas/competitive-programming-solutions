#include <bits/stdc++.h>

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

typedef vector<pair<char,int>> vpci;

// sort by greatest count
// in case of tie, sort by increasing char 
bool state_sort(const pair<char,int>& p1, const pair<char,int>& p2){
    if(p1.second > p2.second)
        return true;

    if(p1.second == p2.second)
        return (p1.first < p2.first);
            
    return false;
} 

// neighbour nodes: up, down, left, right 
vector<Pair> get_neighbours(Pair node, int h, int w){

    vector<Pair> neighbours;
    int offset[2] = {-1, 1};

    // vertical
    for(int o : offset){
        int x = node.first + o;
        int y = node.second;
        if(x >= 1 && x <= h) neighbours.push_back(Pair(x, y));
    }

    // horizontal
    for(int o : offset){
        int x = node.first;
        int y = node.second + o;
        if(y >= 1 && y <= w) neighbours.push_back(Pair(x, y));
    }    

    return neighbours;

}


// recursive call
// mark visited nodes (only of same language, flood fill)
// O(V+E)
// in this case, worst case, O(3*h*w), V = h*w, E ~ 2*h*w 
void dfs_visit(vector<vc> Map, vector<vb>& visited, Pair node, int h, int w){

    int x = node.first,
        y = node.second;

    char c = Map[x][y]; // language spoke in (x,y)
    
    visited[x][y] = true;

    vector<Pair> neighbours = get_neighbours(node, h, w);

    for(Pair p : neighbours){
        int px = p.first,
            py = p.second;
        
        if(!visited[px][py] && Map[px][py] == c)
            dfs_visit(Map, visited, Pair(px, py), h, w);
    }
    
    return;
}

// init depth-first search
// return vector of pairs: (language, no of states that speak that language)
// O(h*w)
vpci dfs(vector<vc> Map, unordered_set<char> lang, int h, int w){

    vector<vb> visited(h+1, vb(w+1, false));
    map<char, int> count;
    for(char c : lang) count[c] = 0;
    
        
    for(int x = 1; x <= h; x++){
        for(int y = 1; y <= w; y++){

            if(visited[x][y])
                continue;

            dfs_visit(Map, visited, Pair(x,y), h, w);
           
            count[Map[x][y]] += 1;
            
        }
    }

    vpci v;
    for(char c : lang)
        v.push_back(pair<char,int>(c, count[c]));

    return v;
}

int main(){
    int t=1, tt;
    cin >> tt;
    
    while(t <= tt){

        int h, w;
        cin >> h >> w;
        
        vector<vc> Map(h+1, vc(w+1, 0));
        unordered_set<char> lang;

        for(int x = 1; x <= h; x++){
            for(int y = 1; y <= w; y++){
                cin >> Map[x][y];
                lang.insert(Map[x][y]);
            }
        }

        vpci count = dfs(Map, lang, h, w);

        // custom sort
        sort(count.begin(), count.end(), state_sort);
        
        printf("World #%d\n", t);
        for(pair<char,int> p : count)
            printf("%c: %d\n", p.first, p.second);
        
        
        ++t;
    }

    return 0;
}
