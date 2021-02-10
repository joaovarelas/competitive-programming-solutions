#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int ul;

int main(){
    ul n, x, k;
    cin >> n >> x;
    
    while(n--){
        char c;
        ul d;
        cin >> c >> d;
        
        if(c == '+'){
            x += d;

        }else if(c == '-'){
            if(d > x) ++k;
            else x -= d;
        }
        
    }

    cout << x << " " << k << endl;
    
    return 0;
}
