#include <bits/stdc++.h>

using namespace std;

double PI = 2*asin(1.0);

// O(pie * log(pie))
double bin_search(multiset<double, greater<double>> pie, int f){

    auto it = pie.begin();
    double hi = *it;
    double lo = 0;
    
    double m = (hi+lo)/2.0;

    // iterate until enough precision
    while(hi - lo >= 0.00001){
        int slices = 0;

        for(auto it = pie.begin(); it != pie.end(); ++it){
            double vol = *it;
            slices += floor(vol/m); // how many slices can we get with volume vol
        }

        if(slices < f)
            hi = m;
        else
            lo = m;

        m = (hi+lo)/2.0;

    }
    
    return m;
}


int main(){

    int t;
    cin >> t;

    while(t--){
        int n, f;
        cin >> n >> f;

        ++f;

        // store pies in decreasing order by volume
        // largest pies are considered first (heuristic)
        multiset<double, greater<double>> pie;

        int m = n;
        while(m--){
            int r;
            cin >> r;
            double v = PI * r * r * 1; // pi * r^2 * h
            pie.insert(v);
        }

        // O(m * log(m))
        // linearithmic 
        double vol = bin_search(pie, f);

        printf("%.4f\n", vol);
    }
    
    return 0;
}
