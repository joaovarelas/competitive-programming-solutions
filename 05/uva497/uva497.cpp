#include <bits/stdc++.h>

using namespace std;

int main(){

    int t;
    cin >> t;
    
    cin.ignore();
    cin.ignore();
    
    while(t--){
        
        vector<int> v;
        string s;

        while(getline(cin, s) && s != ""){
            stringstream ss(s);
            int x;
            ss >> x;
            v.push_back(x);
            //cout << "pushed: " << x << endl;
        }

        int n = v.size();
        //cout << "n: " << n << endl;

        vector<int> best(n, 1);
        vector<int> next(n, -1);
        
        // int idx = -1;

        /* https://www.dcc.fc.up.pt/~pribeiro/aulas/pc2021/material/dp.pdf */
        for(int i = n-1-1; i >= 0; i--){
            for(int j = i+1; j < n; j++){
                
                if(v[j] > v[i] && 1 + best[j] > best[i]){
                    best[i] = 1 + best[j];
                    //cout << "best[i] = " << best[i] << endl;
                    next[i] = j;
                }
            }


        }


        //cout << max_idx.first << ", " << max_idx.second << endl;

        int i = -1, m = -1;
        for(int k = 0; k < n; k++)
            if(best[k] > m)
                m = best[k], i = k;


        vector<int> path;
        // cout << v[i] << endl;
        while(next[i] != -1){
            path.push_back(v[i]);
            i = next[i];
        }
        path.push_back(v[i]);

        cout << "Max hits: " << path.size() << endl;
        for(int x : path)
            cout << x << endl;
       
        if(t > 0)
            cout << endl;
        
    }
    
    return 0;
}
