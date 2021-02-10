#include <bits/stdc++.h>

using namespace std;

class Query{
public:
    int id;
    int period;
    int next;

    bool operator() (Query q1, Query q2){
        if(q1.next == q2.next)
            return q1.id > q2.id;
        
        return q1.next > q2.next;
    }

};


int main(){

    string str;
    cin >> str;

    priority_queue<Query, vector<Query>, Query> pq;

    while(str != "#"){

        int id; // 1 <= id <= 3000
        int p; // 1 <= period <= 3000

        cin >> id >> p;

        Query q;
        q.id = id;
        q.period = p;
        q.next = p;

        pq.push(q);
        //cout << "pushed: " << q.id << " " << q.period << " " << q.next << endl;
        
        cin >> str;
    }

    
    int k;
    cin >> k; // 1 <= k <= 10000

    while(k--){

        // pop the first element of pq
        Query q = pq.top();
        pq.pop();

        //cout << "popped: " << q.id << " " << q.period << " " << q.next << endl;

        // print popped elem id
        cout << q.id << endl;

        // adjust period for the next time
        q.next += q.period;

        // put it back in pq
        pq.push(q);
        
        //cout << "pushed: " << q.id << " " << q.period << " " << q.next << endl;
    }
    
    
    return 0;
}
