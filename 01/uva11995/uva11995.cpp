#include <bits/stdc++.h>

using namespace std;
int main(){

    string line;
    while(getline(cin, line)){
        istringstream ss(line);

        // structs to simulate
        stack<int> s;
        queue<int> q;
        priority_queue<int> pq;

        // flag whether is one of them or not
        bool is_s = true,
            is_q = true,
            is_pq = true;
            
        int n;
        ss >> n;
          
        while(n--){
            int op, x;
            getline(cin, line);
            
            istringstream ss2(line);
            ss2 >> op;
            ss2 >> x;

            if(op == 1){
                
                // put x in bag
                if(is_s)  s.push(x);
                if(is_q)  q.push(x);
                if(is_pq) pq.push(x);

            }else if(op == 2){

                // x: took from bag
                // compare with structs behavior
                if(!s.empty() && s.top() == x) s.pop();
                else is_s = false;
                
                if(!q.empty() && q.front() == x) q.pop();
                else is_q = false;

                if(!pq.empty() && pq.top() == x) pq.pop();
                else is_pq = false;
                
            }
            
        }

        // 0 0 0
        // 0 0 1
        // 0 1 0
        // 1 0 0
        if(!is_s && !is_q && !is_pq)
            cout << "impossible" << endl;
        else if(!is_s && !is_q && is_pq)
            cout << "priority queue" << endl;
        else if(!is_s && is_q && !is_pq)
            cout << "queue" << endl;
        else if(is_s && !is_q && !is_pq)
            cout << "stack" << endl;
        else
            cout << "not sure" << endl;
        
        
    }
    
    return 0;
}
