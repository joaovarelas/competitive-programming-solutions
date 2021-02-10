#include <bits/stdc++.h>

#define NUMCOINS 6
#define VMAX 500

using namespace std;

typedef unsigned long long int ull;
typedef long long int ll;
typedef vector<int> vi;
typedef vector<ull> vu;
typedef vector<ll> vl;
typedef pair<int,int> Pair;



vector<vi> N(VMAX, vi(NUMCOINS, -1));
int min_coins;

int solve(vi coins, vi numcoins, int k, int q){

    if(q == 0)
        return 1;

    if(k == 1){
        if(q % coins[1] != 0 || numcoins[1] < q/coins[1])
            return 0;
        return 1;
    }
    
    if(N[q][k] != -1)    
        return N[q][k];
    
    
    int rmax = min(numcoins[k], (int)floor(q/coins[k]));
    int count = 0;
    for(int r = 0; r <= rmax; r++){
        count += solve(coins, numcoins, q-r*coins[k], k-1);
    }
   
    return N[q][k] = count;
}
        

int main(){
    // coins: 5 10 20 50 100 200
    vi coins = {-1, 5, 10, 20, 50, 100, 200};
    vi numcoins(NUMCOINS+1, 0);
    
    cin >> numcoins[1] >> numcoins[2] >> numcoins[3] >> numcoins[4] >> numcoins[5] >> numcoins[6];
    while(numcoins[1] || numcoins[2] || numcoins[3] || numcoins[4] || numcoins[5] || numcoins[6]){
        min_coins = 9999999;
        double v;
        cin >> v;
        int q = v*100;

        cout << solve(coins, numcoins, NUMCOINS, q) << endl;

        cout << min_coins << endl;
        cin >> numcoins[1] >> numcoins[2] >> numcoins[3] >> numcoins[4] >> numcoins[5] >> numcoins[6];
    }
    
    
    return 0;
}
