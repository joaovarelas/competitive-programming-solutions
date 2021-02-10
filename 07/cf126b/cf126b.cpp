#include <bits/stdc++.h>

#define NMAX 1000001

using namespace std;

typedef unsigned long long int ull;
typedef long long int ll;
typedef vector<int> vi;
typedef vector<ull> vu;
typedef vector<ll> vl;
typedef pair<int,int> Pair;

// prefix that is also a suffix
// https://www.dcc.fc.up.pt/~pribeiro/aulas/pc2021/material/stringmatching.pdf
vi compute_prefix(char* p, int n){
    vi pi(n+1, 0);

    int k = 0;
    for(int q = 2; q <= n; q++){
        
        while(k > 0 && p[k+1-1] != p[q-1])
            k = pi[k];
        
        if(p[k+1-1] == p[q-1])
            k++;

        pi[q] = k;
    }

    // the longest will be pi[n]
    return pi;    
}


int main(){

    //string s;
    //cin >> s;

    char s[NMAX];
    scanf("%s", s);
    
    int n = strlen(s);
    vi pi = compute_prefix(s, n);

    // for(int i : pi)
    //     cout << i << " ";
    // cout << endl;

    // impossible, no prefix that is also a suffix
    if(pi[n] == 0){
        cout << "Just a legend" << endl;
        return 0;
    }

    
    for(int i = n-1; i >= 1; i--){

        // found occurrence of the largest prefix
        // that is also a suffix in the middle of the string
        if(pi[i] == pi[n]){
            int j = 0;
            while(j < pi[i])
                cout << s[j++];
            cout << endl;
            
            return 0;
        }
        
    }
    
    // if no occurrence found, then the answer must
    // be < than the prefix
    // e.g.: fixfixfix, p[n] = 6
    // but the pattern size = 3
    // pi[pi[6]] = 3
    
    if(pi[pi[n]] == 0){
        // No pattern strictly smaller than the prefix found
        cout << "Just a legend" << endl;
        return 0;
    }
    
    // Found a smaller pattern, print it
    int j = 0;
    while(j < pi[pi[n]])
        cout << s[j++];
    cout << endl;
    
    return 0;
}
