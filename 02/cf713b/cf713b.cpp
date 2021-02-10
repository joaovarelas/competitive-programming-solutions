#include <bits/stdc++.h>

using namespace std;

int query(int x1, int y1, int x2, int y2){
    printf("? %d %d %d %d\n", x1, y1, x2, y2);
    int ans;
    scanf("&d", &ans);
    return ans;
}

int main(){

    int n;
    scanf("%d", &n);

    int a = 1, b = n;
    int m;

    int x0 = 1, y0 = 1,
        x1 = n, y1 = n;
    
    while(a <= b){
        m = a + (b-a)/2;
        int ans = query(1, 1, m, m);
        if(ans == 2){
            x0 = 1, y0 = 1, x1 = m, y1 = m; 
        }else if(ans == 1){
            
        }else{

        }
    }
    
    fflush(stdout);
    return 0;
}
