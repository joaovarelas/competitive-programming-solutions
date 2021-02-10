#include <bits/stdc++.h>

#define NMAX 1000001

using namespace std;

typedef long long ll;

// https://cp-algorithms.com/data_structures/fenwick.html#toc-tgt-11
ll bit1[NMAX];
ll bit2[NMAX];

void update(ll* bit, int k, ll x, int n){
    while(k <= n){
        bit[k] += x;
        k += (k & -k);
    }
    return;
}

void range_update(int l, int r, ll x, int n){
    update(bit1, l, x, n);
    update(bit1, r+1, -x, n);
    update(bit2, l, x*(l-1), n);
    update(bit2, r+1, -x*r, n);
    return;
}

ll sum(ll* bit, int k){
    ll s = 0;
    while(k >= 1){
        s += bit[k];
        k -= (k & -k);
    }
    return s;
}

ll prefix_sum(int k){
    return sum(bit1, k)*k - sum(bit2, k);
}

ll range_sum(int l, int r){
    return prefix_sum(r) - prefix_sum(l-1);
}
  

int main(){
    int t;
    scanf("%d", &t);

    while(t--){
        int n, c;
        scanf("%d %d", &n, &c);

        memset(bit1, 0, sizeof(bit1));
        memset(bit2, 0, sizeof(bit2));

        while(c--){
            int cmd;
            scanf("%d", &cmd);

            int p, q;
            ll v = 0;

            switch(cmd){
            case 0:
                {
                    // range add v to [p,q]
                    scanf("%d %d %lld", &p, &q, &v);
                    range_update(p, q, v, n);

                }
                break;
            case 1:
                {
                    // range sum of [p,q]
                    scanf("%d %d", &p, &q);
                    printf("%lld\n", range_sum(p, q));
                }
                break;
            }

            //print_bit(b1, n);
            //print_bit(b2, n);
        }

    }

    return 0;
}
