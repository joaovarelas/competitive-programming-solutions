#include <iostream>
#include <unordered_set>
#include <map>
#include <vector>


using namespace std;

int main(){

    int t;
    cin >> t;

    // O(t*n)
    while(t--){
        
        int n;
        cin >> n;
        
        int max_unique = 0;
        int unique = 0;

        vector<int> vec(n+1, 0); // store contiguous snowflakes
        map<int, int> m; // map snowflake -> index in vector
        int i = 1;
    
        while(n--){
            int s;
            cin >> s;
            
            vec.at(i) = s; // snowflake in vector at pos 's'

            if(!m[s]){ // first occurrence of snowflake 's'
                ++unique;
                
            }else{ // duplicate snowflake 's'

                // get the last known index of snowflake 
                int last_pos = m[s];

                m.clear();

                // re-assign unique snowflakes between 'last_pos' and 'i'
                for(int j = i; j > last_pos; j--)
                    m[vec.at(j)] = j;

                // number of unique snowflakes between 'last_pos' and 'i'
                unique = i - last_pos;

            }

            // update latest index of snowflake
            m[s] = i;

            max_unique = (unique > max_unique) ? unique : max_unique;

            ++i;
        }
        
        cout << max_unique << endl;

  
    }
            
    
    return 0;
}
