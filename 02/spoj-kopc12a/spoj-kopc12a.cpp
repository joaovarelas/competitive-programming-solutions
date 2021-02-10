#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int ull;

vector<int> h; // store heights
vector<int> c; // store costs

// total cost to make all buildings same height k
ull cost(int k){
    ull sum = 0;

    int i = 0;
    while(i < h.size()){
        int height = h.at(i);
        int cost = c.at(i);
        
        sum += cost * abs(k-height); 
        ++i;
    }

    return sum;
}


int search(int a, int b){
    
    // iterate until a,b are close enough
    while(b-a > 0){

        int m1 = a + (b-a)/3,
            m2 = b - (b-a)/3;

        if(cost(m1) > cost(m2))
            a = ++m1;
        else
            b = --m2;
         
        //else
        //return cost(m1);
        //printf("m1=%d | m2=%d | a=%d | b=%d | cost(m1)=%u | cost(m2)=%u\n",
        //m1, m2, a, b,cost(m1),cost(m2));

    }

    return a;
}

int main(){

    int t;
    cin >> t;
    while(t--){

        int n;
        cin >> n;
      
        int h_min = INT_MAX,
            h_max = INT_MIN;
        
        // read heights
        int m = n;
        while(m--){
            int x;
            cin >> x;
            h.push_back(x);

            // define [a,b] interval 
            if(x < h_min) h_min = x;
            if(x > h_max) h_max = x;
        }

        // read costs
        m = n;
        while(m--){
            int x;
            cin >> x;
            c.push_back(x);
        }

        // find optimal (minimum) cost
        // O(h * logh)
        // binary search: log
        // calc costs: h.size (linear) 
        int peak = search(h_min, h_max);
        printf("%llu\n", cost(peak));
        
        h.clear();
        c.clear();
        
    }

    return 0;
}
