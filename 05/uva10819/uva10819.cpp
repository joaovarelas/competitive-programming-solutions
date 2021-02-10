#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

// O(n*cap)
int knapsack(int cap, int n, vi w, vi v){

    // bank refund 200 if total credit spent > 2000
    // need at least 1801 budget
    int r = (cap > 1800) ? cap+200 : cap;

    // 0 1 knapsack
    vector<vi> k(n+1, vi(r+1, 0));
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= r ; j++){

            if(w[i] <= j)
                k[i][j] = max(v[i] + k[i-1][j-w[i]], k[i-1][j]);
            else
                k[i][j] = k[i-1][j];
        }
    }

    // https://blog.csdn.net/mobius_strip/article/details/39347923
    int i = lower_bound(k[n].begin(), k[n].end(), k[n][r]) - k[n].begin();

    // dont receive refund if dont exceed 2000
    if(i <= 2000 && r > 2000)
        return k[n][r-200];

    return k[n][r];
}


int main(){
    int m, n;

    while(cin >> m >> n){

        vi cost(n+1, 0);
        vi value(n+1, 0);
    
        int i = 1;
        while(i <= n){
            int p, f;
            cin >> p >> f;
            cost[i] = p;
            value[i] = f;
            ++i;
        }

        cout << knapsack(m, n, cost, value) << endl;
    }
    
    return 0;
}
