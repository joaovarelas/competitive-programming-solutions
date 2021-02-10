#include <bits/stdc++.h>

#define NMAX 101

using namespace std;

typedef unsigned long long int ull;
typedef long long int ll;
typedef pair<int,int> Pair;
typedef vector<int> vi;
typedef vector<Pair> vp;
typedef vector<ull> vu;
typedef vector<ll> vl;


//vector<vi> memo(NMAX, vi(NMAX, -1)); // TLE
int memo[NMAX][NMAX];
int max_length = 1;
int height[NMAX][NMAX];


// return adjacent places which height
// is lower than the current place
vp adjacent(int n, int m, Pair p){
 
    vp adj;
    int x = p.first,
        y = p.second;

    int h = height[x][y];

    // up, down
    if(x-1 >= 0 && height[x-1][y] < h) adj.push_back(Pair(x-1, y));
    if(x+1 < n  && height[x+1][y] < h) adj.push_back(Pair(x+1, y));
    // left, right
    if(y-1 >= 0 && height[x][y-1] < h) adj.push_back(Pair(x, y-1));
    if(y+1 < m  && height[x][y+1] < h) adj.push_back(Pair(x, y+1));

    //for(Pair a : adj)
    //cout << "adj of " << height[x][y] <<" "<< a.first << " " << a.second << endl;
    
    return adj;
}


// path in DAG from the highest to lowest point
// increment length by 1 at each recursive call
// top-down fashion
int snowboard(int n, int m, Pair p){
    
    int x = p.first,
        y = p.second;

    if(memo[x][y] != -1)
        return memo[x][y];

    //printf("height[p]: %d | length: %d\n", height[x][y], length);

    vp adj = adjacent(n, m, p);
    
    int l = 0;
    for(Pair a : adj)
        l = max(l, snowboard(n, m, a) + 1);
    
    max_length = max(l, max_length);
    

    memo[x][y] = l;
    return l;
}

// O(n²)
int main(){
    int t;
    cin >> t;
    
    while(t--){
        string s;
        cin >> s;

        int n, m;
        cin >> n >> m;

        //vector<vi> height(n, vi(m, 0));

        // reset
        max_length = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                memo[i][j] = -1;
                height[i][j] = NMAX;
            }
        }

     

        /* int max_h = 0;
        Pair max_p;
        vp starting_points;*/

        // read heights
        // store the maximum/highest height
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                int h;
                cin >> h;
                height[i][j] = h;
                /*if(h > max_h){
                    max_h = h;
                    max_p = Pair(i, j);
                    }*/
            }
        }

        // add possible starting points
        // in order to find optimal (longest) path
        /* wont work as heuristic
        starting_points.push_back(max_p);
        
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                if(Pair(i,j) != max_p && height[i][j] == max_h)
                    starting_points.push_back(Pair(i, j));
        */
        
        //for(Pair root : starting_points){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                //max_length = max(snowboard(height, Pair(i,j), 1), max_length);
                snowboard(n, m, Pair(i,j));
            }

        }

        cout << s << ": " << max_length+1 << endl;
    }
    
    return 0;
}
