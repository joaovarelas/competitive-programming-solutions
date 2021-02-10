#include <bits/stdc++.h>

#define NMAX 4
#define ALPHA 26

using namespace std;

typedef unsigned long long int ull;
typedef long long int ll;
typedef vector<int> vi;
typedef vector<ull> vu;
typedef vector<ll> vl;
typedef vector<bool> vb;
typedef vector<string> vs;
typedef pair<int,int> Pair;

// string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
// Trie not needed in this case
/*
class Node{
public:
    //Node* children[ALPHA];
    map<char, Node*> children;
    bool is_word;
    
    Node(){
        for(char c : alphabet)
            this->children[c] = NULL;

        this->is_word = false;
    }


    void insert(string key){
        Node* node = this;
        
        for(char c : key){
            if(node->children[c] == NULL)
                node->children[c] = new Node();
            
            node = node->children[c];
        }

        node->is_word = true;
    }
                   
    
};
*/

// get neighbours of a cell 'x' (according to grid limits)
// 1 1 1
// 1 x 1
// 1 1 1
vector<Pair> get_neighbours(vs grid, string word, Pair cell, string path, vector<vb> visited){
    vector<Pair> neighbours;

    int x0 = cell.first,
        y0 = cell.second;

    char next_letter = word[path.size()];

    for(int i = -1; i <= 1; i++){
        for(int j = -1; j <= 1; j++){
            int x = x0 + i;
            int y = y0 + j;
            
            if(x >= 0 && x < NMAX && y >= 0 && y < NMAX)
                if(!visited[x][y] && grid[x][y] == next_letter){
                    //printf("pushed: (%d,%d) = %c\n", x, y, grid[x][y]);
                    neighbours.push_back(Pair(x, y));
                }
        }
    }
    
    return neighbours;
}

// recursive call, build path and test if equals "word"
bool dfs_visit(vs grid, string word, Pair cell, string path, vector<vb> visited){

    visited[cell.first][cell.second] = true;
    
    if(path == word)
        return true;

    if(path.size() > word.size())
        return false;
      
    vector<Pair> neighbours = get_neighbours(grid, word, cell, path, visited);

    if(neighbours.size() == 0)
        return false;

    for(Pair p : neighbours){
        char letter = grid[p.first][p.second];
        if(dfs_visit(grid, word, p, path + letter, visited))
            return true;
    }
    
    
    return false;
}


// initialize DFS, see if we can reach "word" by trying
// all movements on grid (or not)
bool dfs(vs grid, string word){

    vector<vb> visited(NMAX, vb(NMAX, false));

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            if(grid[i][j] == word[0]){
                string w = ""; w += word[0];
                if(dfs_visit(grid, word, Pair(i,j), w, visited))
                    return true;
            }

        
    return false;
}

int calc_score(string word){    
    int n = word.size();

    if(n == 3 || n == 4) return 1;
    if(n == 5)           return 2;
    if(n == 6)           return 3;
    if(n == 7)            return 5;
    if(n >= 8)           return 11;
    
    // short word
    return 0;
}

int main(){
    ll tt;
    cin >> tt;

    for(ll t = 1; t <= tt; t++){

        vs grid;

        int i = 1;
        while(i <= NMAX){

            string s;
            cin >> s;

            grid.push_back(s);
            ++i;
        }

        ll score = 0;
        
        int q;
        cin >> q;

        // read words to query
        while(q--){
            string s;
            cin >> s;
            
            if(dfs(grid, s)){
                score += calc_score(s);
                //cout << "Scored " << calc_score(s) << " for word " << s << endl;
            }
            
        }

        printf("Score for Boggle game #%ld: %ld\n", t, score);

    }

    return 0;
}
