#include <bits/stdc++.h>

#define NMAX 501*4

using namespace std;

class Node;

typedef unsigned int uint;
typedef pair<uint,uint> Pair;
typedef vector<Pair> vp;
typedef vector<uint> vu;

/*
Using 2D vector (matrix) to query  2 different ranges
[x0,x1] ; [y0,y1]
The first coordinates (x_i) serve as "entry point" to perform
queries on the second (y_i).
Nodes are pairs of the form <min, max> to store both min and max
of the population of a region (multiple cities)
*/

// Segment trees
vector<vp>  st(NMAX, vp(NMAX));

// Population matrix
vector<vu> pop(NMAX, vu(NMAX));

Pair merge(Pair p, Pair q){
    return Pair(min(p.first, q.first), max(p.second, q.second));
}

// https://cp-algorithms.com/data_structures/segment_tree.html#toc-tgt-11
void build_region(uint xpos, uint x0, uint x1,
                  uint ypos, uint y0, uint y1,
                  uint n){
    if(y0 == y1){
        if(x0 == x1)
            // leaf
            st[xpos][ypos] = Pair(pop[x0][y0],pop[x0][y0]);
        else
            // [x0, x1] ; y0
            st[xpos][ypos] = merge(st[2*xpos][ypos], st[2*xpos+1][ypos]);

        //printf("build reg | st %d | xpos %d | x0 %d | x1 %d | ypos %d | y0 %d | y1 %d | n %d\n",
        //     st[xpos][ypos], xpos, x0, x1, ypos, y0, y1, n);
        return;
    }

    // [y0, y1]
    uint mid = y0 + (y1-y0)/2;
    build_region(xpos, x0, x1, 2*ypos, y0, mid, n);
    build_region(xpos, x0, x1, 2*ypos+1, mid+1, y1, n);
    st[xpos][ypos] = merge(st[xpos][2*ypos], st[xpos][2*ypos+1]);
    // printf("build reg | st %d | xpos %d | x0 %d | x1 %d | ypos %d | y0 %d | y1 %d | n %d\n",
    //     st[xpos][ypos], xpos, x0, x1, ypos, y0, y1, n);

    return;
}
        
void build_country(uint xpos, uint x0, uint x1, uint n){
    
    if(x0 != x1){
        // not a leaf, keep going
        uint mid = x0 + (x1-x0)/2;
        build_country(2*xpos, x0, mid, n);
        build_country(2*xpos+1, mid+1, x1, n);
    }

    // build the region at the leaf x0
    build_region(xpos, x0, x1, 1, 1, n, n);
    return;
}

void update_region(uint xpos, uint x0, uint x1,
                   uint ypos, uint y0, uint y1,
                   uint a, uint b,
                   uint v, uint n){

    if(y0 == y1){
        if(x0 == x1)
            // Found leaf of a leaf
            st[xpos][ypos] = Pair(v, v);
        else
            // Leaf of a range
            st[xpos][ypos] = merge(st[2*xpos][ypos], st[2*xpos+1][ypos]);

        //printf("build reg | st %d | xpos %d | x0 %d | x1 %d | ypos %d | y0 %d | y1 %d | n %d\n",
        //     st[xpos][ypos], xpos, x0, x1, ypos, y0, y1, n);
        return;
    }
    
    uint mid = y0 + (y1-y0)/2;
    if(b <= mid)
        // Binary search
        update_region(xpos, x0, x1, 2*ypos, y0, mid, a, b, v, n);
    else
        update_region(xpos, x0, x1, 2*ypos+1, mid+1, y1, a, b, v, n);
    
    st[xpos][ypos] = merge(st[xpos][2*ypos], st[xpos][2*ypos+1]);
    return;
}


void update_country(uint xpos, uint x0, uint x1,
                    uint a, uint b,
                    uint v, uint n){

    if(x0 != x1){
        uint mid = x0 + (x1-x0)/2;

        // Binary search
        if(a <= mid)
            update_country(2*xpos, x0, mid, a, b, v, n);
        else
            update_country(2*xpos+1, mid+1, x1, a, b, v, n);
    }
        
    update_region(xpos, x0, x1, 1, 1, n, a, b, v, n);   
    return;
}

Pair query_region(uint xpos, uint ypos,
                  uint a, uint b,
                  uint y0, uint y1){

              
    if(y0 > y1)
        // No limit provided for the population (?)
        return Pair(99999999, 0);

    if(y0 == a && y1 == b)
        // Found
        return Pair(st[xpos][ypos].first, st[xpos][ypos].second);
    

    uint mid = a + (b-a)/2;
    // Bring it back up
    return merge(query_region(xpos, 2*ypos, a, mid, y0, min(y1,mid)),
                 query_region(xpos, 2*ypos+1, mid+1, b, max(y0,mid+1), y1)
                 );
    
}

Pair query_country(uint xpos, uint a, uint b,
                   uint x0, uint x1,
                   uint y0, uint y1,
                   uint n){
    if(x0 > x1)
        return Pair(99999999, 0);
    
    if(x0 == a && x1 == b)
        // Leaf x0, Start searching on [y0, y1]
        return query_region(xpos, 1, 1, n, y0, y1);

                            
    uint mid = a + (b-a)/2;

    return merge(query_country(2*xpos, a, mid, x0, min(x1,mid), y0, y1, n),
                 query_country(2*xpos+1, mid+1, b, max(x0,mid+1), x1, y0, y1, n)
                 );
}



int main(){
    uint n;
    cin >> n;

    uint j = 1, i = 1;    
    while(i <= n){
        j = 1;
        while(j <= n){
            uint x;
            cin >> x;
            pop[i][j] = x;
            ++j;
        }
        ++i;
    }
    
    build_country(1, 1, n, n);

    uint q;
    cin >> q;
    while(q--){
        char c;
        cin >> c;
        if(c == 'q'){
            // query
            uint x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            Pair ans = query_country(1, 1, n, x1, x2, y1, y2, n);
            printf("%d %d\n", ans.second, ans.first);
            
        }else if(c == 'c'){
            // change
            uint x, y;
            int v;
            cin >> x >> y >> v;
            update_country(1, 1, n, x, y, v, n);
        }

    }
    
    return 0;
}
