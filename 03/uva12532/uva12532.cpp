#include <bits/stdc++.h>

#define NMAX 100001
#define NEUTRAL 1

using namespace std;

typedef unsigned int    uint;
typedef pair<uint,uint> Pair;

class Node{
public:
    Pair range;
    int val;

    Node(Pair range, int val){
        this->range = range;
        this->val = val;
    }

};

vector<int>   v(NMAX);
vector<Node*> segtree(4*NMAX);

uint st_size = 0;

// -1, 0, 1
int get_signal(int x){
    return (x < 0) ? -1 : ((x > 0) ? 1 : 0);
}

char get_signal_char(int x){
    return (x < 0) ? '-' : ((x > 0) ? '+' : '0');
}

int merge(int a, int b){
    return get_signal(a*b);
}


int query(uint pos, uint a, uint b){

    Node* node = segtree[pos];
    if(node == NULL)
        return NEUTRAL;
    
    int start = node->range.first;
    int end = node->range.second;

    //printf("query | pos: %d | start: %d | end: %d | a: %d | b: %d | node->val: %d\n",
    //      pos, start, end, a, b,node->val);

    // invalid range
    if(start > b || end < a)
        return NEUTRAL;

    // in range
    if(start >= a && end <= b){
        return node->val;
    }

    // go left & go right
    int q1 = query(2*pos,   a, b);
    int q2 = query(2*pos+1, a, b);

    return merge(q1, q2);
}




// https://www.dcc.fc.up.pt/~pribeiro/aulas/pc1920/material/12086.html
void update(uint pos, uint x, int val){

    Node* node = segtree[pos];
    if(node == NULL)
        return;

    int start = node->range.first;
    int end = node->range.second;

    //printf("update | pos: %d | start: %d | end: %d\n",
    //     pos, start, end);
    
    // invalid range
    if(start > x || end < x)
        return;
    
    // update our target node 'x'
    if(start == end && start == x){
        segtree[pos]->val = get_signal(val);
        //  printf("updated: segtree[%d]->%d => %d\n", pos, segtree[pos]->val, get_signal(val));
        return;
    }
    
    // go down the tree
    update(2*pos, x, val);
    update(2*pos+1, x, val);
    
    int left =  segtree[2*pos]->val;
    int right = segtree[2*pos+1]->val;
    segtree[pos]->val = merge(left, right);
    // printf("updated: segtree[%d]->%d => %d [merge(%d, %d)]\n",
    //     pos, segtree[pos]->val, merge(left,right), left, right);
    return;
}


void build(uint pos, uint a, uint b){

    if(a == b){
        // leaf
        segtree[pos] = new Node(make_pair(a,b), get_signal(v[a]));
        ++st_size;
        return;
    }
    
    // range
    uint mid = a + (b - a)/2;
    build(2*pos, a, mid);
    build(2*pos+1, mid+1, b);
    int left = segtree[2*pos]->val;
    int right = segtree[2*pos+1]->val;

    // merge childs, store value in current node
    segtree[pos] = new Node(make_pair(a, b), merge(left, right));
    ++st_size;
        
    return;
}


int main(){

    uint n, k;

    bool flag = true;
    
    while(cin >> n >> k){

        // read Xi
        uint i = 1;
        while(i <= n){
            int x;
            cin >> x;
            v[i] = x;
            ++i;
        }

        // build segtree
        build(1, 1, n);


        // print new line between output
        //if(flag) flag = false;
        //else cout << endl;
        
        
        // read operations
        while(k--){
            char op;
            cin >> op;

            switch(op){
            case 'C':
                {
                    // update val in segtree
                    int x, v;
                    cin >> x >> v;

                    //printf("\nC %d %d\n", x, v);
                    update(1, x, v);
                    //print_st();
                    break;
                }
            case 'P':
                {
                    // query the product
                    uint a, b;
                    cin >> a >> b;
                    //printf("\nP %d %d\n", a, b);
                    int ans = query(1, a, b);
                    cout << get_signal_char(ans);                     
                    break;
                }
            }

        }

        cout << endl;
        st_size = 0;
        
    }
    
    return 0;
}
