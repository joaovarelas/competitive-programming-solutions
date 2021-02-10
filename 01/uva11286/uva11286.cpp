#include <iostream>
#include <map>
#include <set>
#include <functional>

using namespace std;

int main(){

    // store the courses selected by frosh
    set<int, less<int>> s;

    // map selected courses to the number of times
    // chosen by froshes
    map<set<int, less<int>>, int> m;
    
    int n;    
    cin >> n;

    while(n != 0){
        
        int j = n;

        int max = -1;

        // O(j*logk)
        while(j--){
            
            int k = 5;
            while(k--){
                int c;
                cin >> c;
                s.insert(c);
            }                    

            // frosh selected course s
            m[s]++;

            // update the most popular courses combination
            if(m[s] > max)
                max = m[s];

            s.clear();
        }

        int ans = 0;

        // count the number of times the most popular
        // combination was selected by frosh
        for(auto it = m.begin(); it != m.end(); ++it){
            if(it->second == max)
                ans += max;
        }

        cout << ans << endl;
        
        m.clear();
        
        cin >> n;
    }
    
    return 0;
}
