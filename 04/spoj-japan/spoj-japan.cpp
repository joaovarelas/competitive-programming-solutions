#include <bits/stdc++.h>

#define NMAX 1001

using namespace std;

typedef unsigned int uint;
//typedef pair<uint, uint> Pair;
//typedef vector<uint> vu; // TLE 
typedef unsigned long long int ul;

struct _Pair{
    uint x, y;

    bool operator () (const _Pair& p1, const _Pair& p2){
        if(p1.x > p2.x)
            return true;
        if(p1.x == p2.x)
            return p1.y > p2.y;
        
        return false;        
    }
    
};

typedef struct _Pair Pair;


ul sum(/*vu&*/ ul* tree, uint k){
    ul s = 0;
    while(k >= 1){
        s += tree[k];
        k -= k & (-k);
    }
    return s;
}

void update(/*vu&*/ ul* tree, uint k, uint x, uint n){
    while(k <= n){
        tree[k] += x;
        k += k & (-k);
    }
    return;
}

// store the east -> west connections
Pair highways[NMAX*NMAX];

/* BIT */
ul tree[NMAX];

int main(){
    uint t, i = 1;
    //cin >> t;
    scanf("%d", &t);

    while(i <= t){
        uint n, m, k;
        //cin >> n >> m >> k;
        scanf("%d %d %d", &n, &m, &k);
        
        // order desc by pair.first, and pair.second if tie 
        //set<Pair/*, compare_pair*/> highways;
        
        // fenwick tree
        //vu tree(NMAX, 0);
        for(int l = 0; l < NMAX; l++)
            tree[l] = 0;
        
        // read SUPERhighways in japan
        uint j = 0;
        while(j < k){
            //uint east, west; // x, y
            Pair p;
            //cin >> east >> west;
            scanf("%d %d", &p.x, &p.y);
            //highways.insert(make_pair(east, west));
    
            highways[j] = p;//make_pair(east, west);
            ++j;
        }

        // https://www.quora.com/How-do-I-solve-SPOJ-com-Problem-MSE06H-using-BIT
        sort(highways, highways+k, Pair());

        // count number of crossings (sum of index west)
        // for each road and update/add the value of 
        // west index with 1
        ul x = 0;
        //for(const Pair& road : highways){

        //for(auto it = highways.begin(); it != highways.end(); ++it){
        for(j = 0; j < k; j++){
            Pair road = highways[j];
            x += sum(tree, road.y-1);
            update(tree, road.y, 1, m);
        }

        printf("Test case %d: %llu\n", i, x);
        
        //for(auto& p : highways)
        //printf("(%d, %d)\n", p.first, p.second);

        ++i;
    }
    
    return 0;
}
