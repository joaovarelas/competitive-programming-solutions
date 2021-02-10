#include <iostream>
#include <string>
#include <math.h>

using namespace std;

long long jumps(long long a, long long b, long long k){
    long long j = 0;

    long double f = 2.0;
    f = k/f;
    
    long long x = a*ceil(f);
    long long y = b*floor(f);
    
    j = x - y;
    
    return j;
}

int main(){
    long long t, a, b, k;
    cin >> t;

    while(t-- > 0){
        cin >> a >> b >> k;
        cout << jumps(a, b, k) << endl;
    }
    
    return 0;
}
