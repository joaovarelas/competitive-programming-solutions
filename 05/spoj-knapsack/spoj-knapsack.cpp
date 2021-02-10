#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

// O(n*cap)
// bottom-up approach
int knapsack(int cap, int n, vi w, vi v){

    vector<vi> k(n+1, vi(cap+1, 0));

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= cap; j++){

            if(w[i] <= j)
                // choose max between adding current item value
                // or selecting previous item (without exceeding weight)
                k[i][j] = max(v[i] + k[i-1][j-w[i]], k[i-1][j]);
            else
                // capacity not enough to consider v[i], assume previous
                // optimal choice with same capacity j
                k[i][j] = k[i-1][j];
        }
    }

    return k[n][cap];
}

int main(){
    // bag capacity and number of items
    int cap, n;
    cin >> cap >> n;

    // store weigth and value
    vi w(n+1, 0);
    vi v(n+1, 0);

    // read each item weight and value
    for(int i = 1; i <= n; i++)
        cin >> w[i] >> v[i];

    cout << knapsack(cap, n, w, v) << endl;
    
    return 0;
}
