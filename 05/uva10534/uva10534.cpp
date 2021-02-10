#include <bits/stdc++.h>

#define INF 9999999

using namespace std;

typedef vector<int> vi;

vi LIS(vi& v){

    int n = v.size();
    
    vi L(n);
    vi a(n+1, INF);
    a[0] = -INF;
    
    // pointer of rightmost elem of a[], size of LIS
    int k = 0;
        
    for(int i = 0; i < n; i++){

        // bin search
        int left = 0, right = k;
        while(left <= right){
            
            int m = left + (right-left)/2;

            if(a[m] < v[i])
                left = m+1;
            else
                right = m-1;
        }

        // update a[]
        a[left] = v[i];
        
        // update size if l > k
        k = max(k, left);
        
        // store pos l in L[]
        L[i] = left;

    }

    return L;
    
}


int main(){
   

    int n;
    while(cin >> n){

        // store ints sequence
        vi v(n);
        
        // read sequence of ints
        int i = 0;
        while(i < n)
            cin >> v[i++];
                  

        // LIS this way
        // -------------->
        // v0 v1 v2 ... vn
        vi lis1 = LIS(v);

        
        // LIS this way (LDS)
        // <--------------
        // v0 v1 v2 ... vn
        reverse(v.begin(), v.end());
        vi lis2 = LIS(v);



        // match wavio sequence
        i = 0;
        int j = n-1;
        int wavio = 0;
        while(i < n){
            // leftmost elems sequence, discard multiple LIS
            int m = min(lis1[i], lis2[j]);
            wavio = max(wavio, m);
            ++i;
            --j;
        }

        // ---> <---
        // n + 1 + n
        cout << 2*wavio-1 << endl;
        
    }
    
    return 0;
}
