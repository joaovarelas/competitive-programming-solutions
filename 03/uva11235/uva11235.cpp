#include <bits/stdc++.h>

#define MAX_N 100001

using namespace std;

class Node {
public:
    pair<int,int> range;
    int val;

    Node(pair<int,int> range, int val){
        this->range = range;
        this->val = val;
    }

    bool is_leaf(){
        return range.first == range.second;
    }
};

vector<int> v(MAX_N);
vector<Node*> segtree(4*MAX_N);
vector<int> freq(MAX_N);
unordered_map<int,pair<int,int>> ranges;
unordered_map<int,int> counts;


// merge function: max of elem occurrence in childs
int merge(int a, int b){
    return max(segtree[a]->val, segtree[b]->val);
}


// build the segtree
void build(int pos, int a, int b){
    
    if(a == b){
        // leaf
        segtree[pos] = new Node(make_pair(a,b), freq[a]);
        
    }else{
        // range
        int mid = a + (b - a)/2;
        build(pos*2, a, mid);
        build(pos*2+1, mid+1, b);
        segtree[pos] = new Node(make_pair(a,b), merge(pos*2, pos*2+1));
    }

    return;
}

int rmq(int pos, int a, int b, int n){

    //printf("pos %d | a %d | b %d\n", pos, a, b);
    
    int range_a = segtree[pos]->range.first;
    int range_b = segtree[pos]->range.second;

    // in range
    if(range_a >= a && range_b <= b)
        return segtree[pos]->val;

    // invalid range
    if(range_a > b || range_b < a)
        return 1;

    // recursion child nodes
    return max(rmq(2*pos, a, b, n),
               rmq(2*pos+1, a, b, n));

}

int query(int pos, int a, int b, int n){
    
    if(a == 1 && b == n)
        return segtree[pos]->val;
    
    if(a == b)
        return 1;

    if(ranges[v[a]] == ranges[v[b]])
        return b - a + 1;
  
    bool adjust_a = (a != ranges[v[a]].first);
    bool adjust_b = (b != ranges[v[b]].second);

    int dist_a = abs(a - ranges[v[a]].second) + 1;
    int dist_b = abs(b - ranges[v[b]].first) + 1;

    if(adjust_a && !adjust_b){
        return max(dist_a, rmq(pos, a+dist_a, b, n));
        
    }else if(!adjust_a && adjust_b){
        return max(rmq(pos, a, b-dist_b, n), dist_b);

    }else if(adjust_a && adjust_b){
        return max(dist_a, max(dist_b,
                               rmq(pos, a+dist_a, b-dist_b, n)));
    }
    
    return rmq(pos, a, b, n);
}

// O(n*logn)
// answering multiple queries in O(logn)
int main(){

    int n, q;
    cin >> n;
    
    while(n){
        cin >> q;

        // build initial array
        int i = 1, j = 1;
        int x, y;

        while(i <= n){
            int x;
            cin >> x;
            v[i] = x;
            counts[x]++;

            // save [a,b] of contiguous elems
            // useful to process partial range queries
            if(i > 1){
                if(y != x){
                    ranges[v[i-1]] = make_pair(j, i-1);
                    //printf("ranges[%d] = (%d,%d)\n", v[i-1], j, i-1);
                    j = i;
                }
            }

            y = x;
            
            ++i;
        }
        ranges[v[i-1]] = make_pair(j, n);
        //printf("ranges[%d] = (%d,%d)\n", v[i-1], j, n);

        i = 1;
        // frequency sequence
        // https://algorithmist.com/wiki/UVa_11235_-_Frequent_values
        while(i <= n){
            freq[i] = counts[v[i]];
            ++i;
        }
        
        // build segtree
        build(1, 1, n);
        
        // answer queries
        while(q--){
            int a, b;
            cin >> a >> b;
            cout << query(1, a, b, n) << endl;
        }
               
        cin >> n;

        // reset structures for next test cases
        //v.clear();
        //segtree.clear();
        //freq.clear();
        counts.clear();
    }
    
    return 0;
}
