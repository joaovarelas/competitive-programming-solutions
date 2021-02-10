#include <bits/stdc++.h>

using namespace std;

int main(){

    int n;
    cin >> n; // 1 <= n <= 5000

    // store the bills in decreasing order
    // b1 > b2 > ...
    multiset<int, greater<int>> urn;
    unsigned long long int prize;


    while(n != 0){
        prize = 0;

        // Reset urn
        urn.clear();

        // O(n*k*logk)
        // days loop * number of bills * inserting in ordered multiset
        for(int i = 1; i <= n; ++i){
            int k;
            cin >> k; // 0 <= k <= 100000

            for(int j = 1; j <= k; ++j){
                int b;
                cin >> b; // 1 <= b <= 1000000
                urn.insert(b);

                //cout << "inserted: " << b << endl;
            }

            // if urn has 2 or more bills
            if(urn.size() > 1){
                multiset<int>::iterator it;

                // select the first (highest)
                it = urn.begin();
                int highest = *it;
                urn.erase(it);

                // select the last (lowest)
                it = prev(urn.end());
                int lowest = *it;
                urn.erase(it);

                // the prize is the difference
                prize += highest - lowest;

                //cout << "prize: " << prize << endl;
            }
        
        }

        cout << prize << endl;

        //cout << "-------------" << endl;
        cin >> n;
    }
    
    return 0;
}
