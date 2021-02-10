#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;


// max sum O(n)
int kadane(vi& arr){
    int g = arr[0],
        c = 0;
    
    for(int i = 0; i < arr.size(); i++){
        c += arr[i];
        g = max(g, c);
        c = max(c, 0);
    }
    
    return g;
}


/*
int compute_sum(vvi& cs, int a, int b, int c, int d){
    return cs[c][d] - cs[a-1][d] - cs[c][b-1] + cs[a-1][b-1];
}
*/


int main(){
    int n;
    while(cin >> n){

        // read matrix
        vvi v(n+1, vi(n+1, 0));
        int i, j;
        for(i = 1; i <= n; i++)
            for(j = 1; j <= n; j++)
                cin >> v[i][j];

        // cumulative sum
        // vertical prefix sum O(n²)
        // https://algorithmist.com/wiki/UVa_108_-_Maximum_Sum
        vvi cs(n+1, vi(n+1, 0));
        for(i = 1; i <= n; i++)
            for(j = 1; j <= n; j++)
                cs[i][j] = v[i][j] + cs[i-1][j];
        
        
        // calc max sum
        int ans = cs[1][1];

        // assume the max subarray is between row 'i' and 'n'
        for(j = 1; j <= n; j++){
            vi arr(n, 0);

            // row 'i' will get closer to lower bound each 'j' iteration
            for(i = j; i <= n; i++){

                // use our cumulative sum (vertical prefix) to generate
                // an array to input in kadane
                for(int k = 1; k <= n; k++)
                    arr[k-1] += cs[i][k] - cs[i-1][k];

                ans = max(ans, kadane(arr));
            }
        }
        

        printf("%d\n", ans);
    }
   
    return 0;
}
