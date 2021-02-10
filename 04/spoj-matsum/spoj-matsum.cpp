#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int ull;
typedef long long int ll;
typedef vector<int> vi;
typedef vector<ull> vu;
typedef vector<ll> vl;
typedef vector<bool> vb;
typedef vector<string> vs;
typedef pair<int,int> Pair;

// E-maxx 2D Bit Impl. (copy paste)
// https://cp-algorithms.com/data_structures/fenwick.html#toc-tgt-6
struct FenwickTree2D {
    vector<vi> bit;
    int size;

    void init(int n){
        bit = vector<vi>(n+1, vi(n+1, 0));
        size = n+1;
    }

    ll sum(int x, int y) {
        ll ret = 0;
        for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
            for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
                ret += bit[i][j];
        return ret;
    }

    void add(int x, int y, int delta) {
        for (int i = x; i < size; i = i | (i + 1))
            for (int j = y; j < size; j = j | (j + 1))
                bit[i][j] += delta;
    }
};

int main(){
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;

        FenwickTree2D bit;
        bit.init(n);
        
        char buf[4];
        scanf("%s", buf);
        
        while(strcmp(buf, "END") != 0){
        
            if(strcmp(buf, "SET") == 0){
                int x, y, w;
                scanf("%d %d %d", &x, &y, &w);

                // get the current submatrix sum
                // and update the difference between new val
                ll cur = bit.sum(x, y)
                    - bit.sum(x, y-1)
                    - bit.sum(x-1, y)
                    + bit.sum(x-1, y-1);
                
                bit.add(x, y, w-cur);
                
                // https://www.geeksforgeeks.org/two-dimensional-binary-indexed-tree-or-fenwick-tree/
            }else{
                int x0, y0, x1, y1;
                scanf("%d %d %d %d", &x0, &y0, &x1, &y1);

                // sum of the submatrix
                // inclusion-exclusion principle
                printf("%lld\n",
                       bit.sum(x1, y1)
                       - bit.sum(x1, y0-1)
                       - bit.sum(x0-1, y1)
                       + bit.sum(x0-1, y0-1));
            }


            for(vi v : bit.bit){
                for(int x : v)
                    printf("%d ", x);

                putchar('\n');
            }

            cout << "\n------------------------------\n";


        
            scanf("%s", buf);

            
        }
     
        
    }

    return 0;
}
