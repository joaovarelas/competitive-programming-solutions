#include <bits/stdc++.h>

#define NMAX 10001

using namespace std;


int bit[NMAX];

int sum(int k, int n){
    int s = 0;
    while(k >= 1){
        s += bit[k];
        k -= (k & -k);
    }
    return s;
}

void update(int k, int x, int n){
    while(k <= n){
        bit[k] += x;
        k += (k & -k);
    }
    
    return;
}

void range_update(int l, int r, int x, int n){
    // update [l,n] with x
    update(l, x, n);

    // un-update [r+1, n] so that
    // only [l, r] is updated
    update(r+1, x*-1, n);
    return;
}


int main(){
    
    int t;
    scanf("%d", &t);

    while(t--){
        int n, u;
        scanf("%d %d", &n, &u);
        memset(bit, 0, sizeof(bit));
        
        // perform range updates
        while(u--){
            int l, r, val;
            scanf("%d %d %d", &l, &r, &val);
            range_update(l+1, r+1, val, n);

        }

         // answer queries
         int q;
         scanf("%d", &q);
         while(q--){
             int k;
             scanf("%d", &k);
             printf("%d\n", sum(k+1, n));
         }
         
    }

    return 0;
}



