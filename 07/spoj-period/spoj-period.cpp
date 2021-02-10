#include <bits/stdc++.h>

#define NMAX 1000001

using namespace std; 

typedef unsigned long long int ull;
typedef long long int ll;
typedef vector<int> vi;
typedef vector<ull> vu;
typedef vector<ll> vl;
typedef vector<bool> vb;
typedef vector<string> vs;
typedef pair<int,int> Pair;

// KMP pi function
// p.15 https://www.dcc.fc.up.pt/~pribeiro/aulas/pc2021/material/stringmatching.pdf

int pi[NMAX];

void compute_prefix(/*string p*/ char* p, int n){
    //vi pi(n+1, 0);
    //int pi[n+1];
    //int* pi = (int*)malloc((n+1) * sizeof(int));

    int k = 0;
    for(int q = 2; q <= n; q++){
        
        while(k > 0 && p[k] != p[q-1])
            k = pi[k];
        
        if(p[k] == p[q-1])
            k++;

        pi[q] = k;
    }
    
    //return pi;    
}


int main(){

    int t = 1, tt;
    //cin >> tt;
    scanf("%d", &tt);
    while(t <= tt){
        int n;
        scanf("%d", &n);
        //cin >> n;
        
        //string s;
        //cin >> s;
        char s[n+1];
        scanf("%s", s);

        /*int* pi =*/ compute_prefix(s, n);

        //cout << "Test case #" << t << endl;
        printf("Test case #%d\n", t);
        
        for(int i = 1; i <= n; i++){
            // no pattern
            if(pi[i] == 0)
                continue;

            // if the current prefix size
            // is divisible by the length
            int p = i - pi[i];
            if(i % p == 0)
                printf("%d %d\n", i, i/p);
        }

        //cout << endl;
        putchar('\n');
        ++t;
    }

    return 0;
}
