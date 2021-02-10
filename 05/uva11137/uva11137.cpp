#include <bits/stdc++.h>

#define NMAX 21

using namespace std;

typedef unsigned long long int ull;
typedef long long int ll;
typedef vector<int> vi;
typedef vector<ull> vu;
typedef vector<ll> vl;
typedef pair<int,int> Pair;

// O(NMAX * x) // where x is the amount to be paid (exchange)
// NMAX is constant, therefore
// O(21*x) = O(x)
// linear time
ll solve(vi coins, int x){

    vector<vl> change(x+1, vl(NMAX+1, 0));

    for(int j = 1; j <= NMAX; j++)
        change[0][j] = 1;

    for(int i = 1; i <= x; i++){
        for(int j = 1; j <= NMAX; j++){

            // number of ways including coin[j]
            ll a = (i-coins[j] >= 0) ? change[i-coins[j]][j] : 0;

            // number of ways excluding coin[j]
            ll b = (j >= 1) ? change[i][j-1] : 0;

            change[i][j] = a+b;
        }
    }
    
    return change[x][NMAX];
}


int main(){

    // set of cube coins
    vi coins(NMAX+1, 0);
    for(int i = 1; i <= NMAX; i++)
        coins[i] = pow(i, 3);
    
    int x;
    while(cin >> x)
        printf("%lld\n", solve(coins, x));
    

    return 0;
}
