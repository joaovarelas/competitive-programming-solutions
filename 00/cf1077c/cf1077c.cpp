#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

int main(){

    int n;
    cin >> n;

    vector<int> vec;
    vector<int> nice;
    
    int k;
    long long sum = 0;
    
    pair<int, int> m1(-1,-1); // <value, idx> (1st maximum)
    pair<int, int> m2(-1,-1);//  <value, idx> (2nd maximum)

    // Read array elements & find 1st max
    for(int i = 0; i < n; i++){
        cin >> k;
        vec.push_back(k);
        sum += k;
        
        if(k > m1.first){
            m1.first = k;
            m1.second = i;
        }
    }

    // Find 2nd max
    for(int i = 0; i < n; i++){
        if(i == m1.second) continue;
        k = vec.at(i);
        
        if(k > m2.first){
            m2.first = k;
            m2.second = i;
        }    
    }

    // Remove bad indices
    for(int i = 0; i < n; i++){
        k = vec.at(i);
        
        if(i != m1.second){
            if(sum-k-m1.first == m1.first)
                nice.push_back(i+1);
                    
        }else{
            if(sum-k-m2.first == m2.first)
                nice.push_back(i+1);
        }
        
    }

    // Print size
    cout << nice.size() << endl;

    // Print bad indices (if any)
    if(nice.size()){
        for(size_t i = 0; i < nice.size(); i++){
            if(i != 0)
                cout << " ";
            cout << nice.at(i);
        }
    }
    
    return 0;
}
