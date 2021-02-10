#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

class Triple{
public:
    int x;
    int count;
    int pos;

    Triple(int x, int count, int pos){
        this->x = x;
        this->count = count;
        this->pos = pos;
    }

    // compare by count
    // compare by pos in case of tie
    bool operator < (Triple other){
        if(this->count > other.count)
            return true;
        else if(this->count == other.count)
            return this->pos < other.pos;
                           
        return false;
    }
};
    

int main(){
    int n, c;
    cin >> n >> c;

    map<int, pair<int,int>> m; // map x -> (n_times, idx)
    
    int i = 1;
    while(i <= n){
        int x;
        cin >> x;
        m[x].first++;
        if(!m[x].second)
            m[x].second = i;

        i++;
    }

    vector<Triple> v;
    for(auto const& it : m){
        int x = it.first;
        pair<int,int> p = it.second;
        //cout << x << " -> " << "(" << p.first << ", " << p.second << ")" << endl;
        Triple t(x, p.first, p.second);
        v.push_back(t);
    }

    // custom sort
    sort(v.begin(), v.end());

    bool first = true;
    for(auto const& it : v){
        //cout << it.x << " -> " << it.count << " " << it.pos << endl;
        int t = it.count;
        while(t--){
            if(first){
                first = false;
            }else{
                cout << " ";
            }
            cout << it.x;
        }
            
    }
        
   
    return 0;
}
