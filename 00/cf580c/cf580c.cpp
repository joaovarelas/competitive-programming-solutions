#include <bits/stdc++.h>

using namespace std;

class Edge{
public:
    int y;
    Edge(int y){
        this->y = y;
    }
};
    

class Node{
public:
    int v;
    bool cat;
    vector<Edge*> adjs;
    Node(int v, bool cat){
        this->v = v;
        this->cat = cat;
    }

    bool has_cats(){
        return this->cat;
    }

};


class Graph{
public:
    int num_verts;
    int num_edges;
    vector<Node*> verts;
    
    Graph(int n, vector<bool> cats){
        this->num_verts = n;
        this->num_edges = 0;

        verts = vector<Node*>(n+1);
        
        for(int i = 1; i <= n; i++)
            verts[i] = new Node(i, cats[i]);
    }

    Node* get_node(int v){
        return this->verts[v];
    }
    
    vector<Edge*> get_adjs(int v){
        return get_node(v)->adjs;
    }

    void add_edge(int x, int y){
        get_node(x)->adjs.push_back(new Edge(y));
    }

    Edge* find_edge(int x, int y){
        for(Edge* adj : get_adjs(x))
            if(adj->y == y)
                return adj;
        
        return nullptr;
    }

    bool is_leaf(int v, vector<bool>& visited){
        for(Edge* adj : get_adjs(v))
            if(!visited[adj->y])
                return false;
        return true;
    }

    vector<int> unvisited(int v, vector<bool>& visited){
        vector<int> visit;
        for(Edge* adj : get_adjs(v)){
            int w = adj->y;
            if(!visited[w])
                visit.push_back(w);
        }
        return visit;
    }
    
};

int DFS(Graph* g, int v, vector<bool>& visited, int cats, int max){

    visited[v] = true;
    //cout << "Visited: " << v << endl;

    Node* node = g->get_node(v);

    if(node->has_cats())
        ++cats;
    else
        cats = 0;

    if(cats > max)
        return 0;


    if(g->is_leaf(v, visited))
        return 1;
    
    vector<Edge*> adjs = g->get_adjs(v);

    int r = 0;
    /*
    for(Edge* adj : adjs){
        int w = adj->y;
        if(!visited[w]){
            r += DFS(g, w, visited, cats, max);
        }
    }
    */
    vector<int> visit = g->unvisited(v, visited);
    for(int w : visit)
        r += DFS(g, w, visited, cats, max);
    
    return r;
}

int main(){
    int n, m;
    cin >> n >> m;

    vector<bool> cats(n+1);
    int i = 1;
    while(i <= n){
        bool b;
        cin >> b;
        cats[i++] = b;
    }
    
    Graph* g = new Graph(n, cats);

    i = 1;
    while(i <= n-1){
        int x, y;
        cin >> x >> y;
        g->add_edge(x, y);
        g->add_edge(y, x);
        ++i;
    }

    vector<bool> visited(n+1, false);
    int r = DFS(g, 1, visited, 0, m);
    cout << r << endl;
    

    /*
      for(int x = 1; x <= n; x++)
      for(int y = 1; y <= n; y++)
      if(g->find_edge(x,y) != nullptr)
      printf("Found %d -> %d\n", x, g->find_edge(x,y)->y);
    */
                
    return 0;
}
