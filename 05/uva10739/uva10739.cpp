#include <bits/stdc++.h>

#define NMAX 1001

using namespace std;

typedef vector<int> vi;

// top-down approach
vector<vi> memo(NMAX, vi(NMAX, -1));
int distance(string s, int i, int j){

    // return memoized result
    if(memo[i][j] != -1)
        return memo[i][j];

    // if substr has 1 char or invalid range
    if(j <= i){
        memo[i][j] = 0;
        return 0;
    }

    // solve a smaller instance of the problem
    // _xyzwx_ -> yzw
    if(s[i-1] == s[j-1]){
        memo[i][j] = distance(s, i+1, j-1);
        return memo[i][j];
    }

    // xyzw: find min operations required on yzw, xyz, yz
    // +1 because x != w thus 1 operation is already required
    // https://algorithmist.com/wiki/UVa_10739_-_String_to_Palindrome
    memo[i][j] = 1 + min(distance(s, i+1, j),
                         min(distance(s, i, j-1),
                             distance(s, i+1, j-1)));
    return memo[i][j];
}


int main(){
    int t;
    cin >> t;

    int c = 1;
    while(t--){
        string s;
        cin >> s;
      
        printf("Case %d: %d\n", c++, distance(s, 1, s.size()));
        // reset memoization
        for(auto& v : memo)
            for(int i = 0; i <= s.size(); i++)
                v[i] = -1;

        
    }
    
    return 0;
}
