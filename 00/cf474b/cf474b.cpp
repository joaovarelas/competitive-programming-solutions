#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef pair<int,int> pi;
typedef map<int,int> mi;
typedef vector<pi> vp;

int bin_search(vp& arr, int x){
    int l = 0, r = arr.size()-1,
        m;

 
    while(l <= r){
        m = l + (r-l)/2;

        //printf("bin | l %d | m %d | r %d | x %d\n",l, m, r, x);
        
        pi p = arr[m];
        //printf("p: %d %d\n", p.first, p.second);
        
        if(x >= p.first && x <= p.second){
            return p.first;
        }
        else if(x < p.first){
            r = m - 1;
        }
        else if(x > p.second){
            l = m + 1;
        }
    }
    
    return l;
}


int main(){
    int n;
    cin >> n;

    vp arr;
    mi m;

    int sum = 0, prev = 0;
    int i = 1;
    int a = 1, b = 1;
    
    while(i <= n){
        int x;
        cin >> x;

        sum += x;

        a = prev + 1;
        b = sum;

        arr.push_back(pi(a, b));
        m[a] = i;
        m[b] = i;
        
        prev = sum;
        
        //cout << a << " " << b << endl;
        
        ++i;
    }

    int w;
    cin >> w;

    while(w--){
        int q;
        cin >> q;

        cout << m[bin_search(arr, q)] << endl;
    }
    
    return 0;
}
