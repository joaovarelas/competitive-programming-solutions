#include <bits/stdc++.h>

#define NEUTRAL      0
#define LESS_THAN_K  0
#define GREAT_THAN_K 1

// b_1, b_2, ..., b_n, t.q. b_i = {0, 1}
// b_i = 1 sse a_i > k
// resposta query (i,j,k) ---> b_i + b_i+1 + ... + b_j
// ordernar array a_i
// ordenar queries q1, q2 ... q_n t.q. q1_k <= q2_k

using namespace std;

typedef unsigned long ul;
typedef unsigned int ui;

typedef pair<ul,ui> Pair;
typedef tuple<ui,ui,ul,ui> Quad;

typedef vector<ui> vi;
typedef vector<Pair> vp;
typedef vector<Quad> vq;

// custom compare
bool compare_by_k(const Quad& q1, const Quad& q2){
    return get<2>(q1) < get<2>(q2);
}

// merge fn
int merge(ui x, ui y){
    return x+y;
}

// return sum of elems in [x,y]
int query(vi* st, ui pos, ui a, ui b, ui x, ui y){

    if(a > y || b < x)
        return NEUTRAL;
    
    if(a >= x && b <= y)
        return st->at(pos);

    ui mid = a + (b-a)/2;
    
    return merge(query(st, 2*pos, a, mid, x, y),
                 query(st, 2*pos+1, mid+1, b, x, y));
}


// update target leaf x with value v
void update(vi* st, ui pos, ui a, ui b, ui x, ui v){
    
    if(a > x || b < x)
        return;
    
    if(a == b && a == x){
        st->at(pos) = v;
        return;
    }
    
    ui mid = a + (b-a)/2;
    
    update(st, 2*pos, a, mid, x, v);
    update(st, 2*pos+1, mid+1, b, x, v);

    st->at(pos) = merge(st->at(2*pos), st->at(2*pos+1));
    return;
}

void build(vi* st, ui pos, ui a, ui b){

    // assume that elem at pos is "greater than k"
    // afterwards it will be updated to "less than k"
    if(a == b){
        st->at(pos) = GREAT_THAN_K;
        return;
    }

    int mid = a + (b-a)/2;
    
    build(st, 2*pos, a, mid);
    build(st, 2*pos+1, mid+1, b);
    
    st->at(pos) = merge(st->at(2*pos), st->at(2*pos+1));  
    return;
}

// O(n*logn)
// linearithmic due to sorting & update/querying "less than k"
// segtree operations are O(logn)
int main(){
 
    ui n;
    cin >> n;

    // store pairs <a_i, i>
    vp v(n+1);

    // disposable segtree: only works for one pass
    vi st(4*(n+1));
    
    int i = 1;
    while(i <= n){
        ul x;
        cin >> x;
        v[i] = Pair(x, i);
        ++i;
    }

    // sort v by a_i ascending
    sort(next(v.begin()), v.end());

    // build the segtree with leafs = 1
    build(&st, 1, 1, n);

    ui m;
    cin >> m;

    // store queries and index <i,j,k,idx>
    vq q(m+1);

    // read queries first and process later (offline)
    i = 1;
    while(i <= m){
        ul a, b, k;
        cin >> a >> b >> k;
        q[i] = Quad(a, b, k, i);
        ++i;
    }

    // sort q by k ascending
    sort(next(q.begin()), q.end(), compare_by_k);

    // store answers by original queries order
    vi ans(m+1);
   


    // index of first occurrence of k in v
    // both q[] and v[] are ordered
    // k of query q_i+1 will be greater than k of q_i
    ui j = 1;

    i = 1;
    while(i <= m){
        ui  a = get<0>(q[i]),
            b = get<1>(q[i]),
            idx = get<3>(q[i]);
        
        ul k = get<2>(q[i]);

        // set the elems at [j, x' > k] to "less than k"
        // this will decrease search space during new queries
        // but will also invalidate the segtree for further use
        while(j <= n && v[j].first <= k)
            update(&st, 1, 1, n, v[j++].second, LESS_THAN_K);

        // perform query after updating
        ans[idx] = query(&st, 1, 1, n, a, b);

        ++i;
    }

    // print answers
    i = 1;
    while(i <= m)
        printf("%d\n", ans[i++]);
    
    return 0;
}
