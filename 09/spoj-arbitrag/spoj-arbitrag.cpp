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

// Floyd warshall variation 
// Worst case: O(n³)
// Find the most profitable way of exchange considering all paths
// (from any to any)
// If we start with 1.0 coins of currency X and end with > 1.0 coins
// of currency X, then arbitrage is possible (for all currency X)
// https://www.youtube.com/watch?v=4OQeCuLYj-4
bool floyd_warshall(vec<vec<double>>& v, int n){
    for(int k = 1; k <= n; k++)
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++){
                v[i][j] = max(v[i][j], v[i][k] * v[k][j]);
                if(i == j && v[i][j] > 1.0)
                    return true;
            }
    return false;
}

int main(){

    int n;
    cin >> n;
    int t = 1;
    while(n != 0){

        vec<vec<double>> v(n+1, vec<double>(n+1, 0.0));
        int count = 1;
        u_map<string, int> umap;
        
        // read curr
        for(int i = 1; i <= n; i++){
            string s;
            cin >> s;
            umap[s] = count++;
        }

        // no of edges
        int m;
        cin >> m;
        
        // read weighted edges
        for(int i = 1; i <= m; i++){
            string a, b;
            double w;
            cin >> a >> w >> b;
            v[umap[a]][umap[b]] = w;
            // cout << a << " -- " << w << " --> " << b << endl;
        }

        // 
        bool flag = floyd_warshall(v, n);        

        /*
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++)
                cout << v[i][j] << " ";
            cout << endl;
        }
        */

        printf("Case %d: ", t++);
        if(!flag) printf("No\n");
        else printf("Yes\n");
        
        //cout << "-------------------------"<< endl;
        cin >> n;
    }

    return 0;
}
