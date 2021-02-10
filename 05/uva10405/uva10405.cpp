#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

int LCS(char* s1, char* s2){//string s1, string s2){
    int n = strlen(s1), m = strlen(s2);//s1.size(), m = s2.size();

    vector<vi> ed(n+1, vi(m+1, 0));
    
    //for(int i = 0; i < n; i++) ed[i][0] = i;
    //for(int j = 0; j < m; j++) ed[0][j] = j;

    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            if(s1[i-1] == s2[j-1])
                ed[i][j] = ed[i-1][j-1] + 1;
            else
                ed[i][j] = max(ed[i-1][j], ed[i][j-1]);

    /*
      for(vi& v : ed){
      for(int x : v){
      printf("%d ", x);
      }
      printf("\n");
      }
    */

    return ed[n][m];
}

int main(){
    //string s1; // WA
    //string s2;
    
    char s1[1001]; 
    char s2[1001];

    while(gets(s1)){//cin >> s1){
        gets(s2);//cin >> s2;

        // s1 = a' a (a' = a_0, a_1, ..., a_n-1; a = a_n)
        // s2 = b' b (b' = b_0, b_1, ..., b_n-1; b = b_n)
        cout << LCS(s1, s2) << endl;
    }
        
    
    return 0;
}
