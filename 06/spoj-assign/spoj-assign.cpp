#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long int ull;
typedef long long int ll;
typedef vector<int> vi;
typedef vector<ull> vu;
typedef vector<ll> vl;
typedef vector<bool> vb;
typedef pair<int,int> Pair;

/*
  Assume students from 1 to k have been
  assigned to a subject. 
  The rest of students (n-k) remain to be assigned.

  - Keep track of already chosen subjects and students
    by using bitmask.
  
  - Keep track of students which have already assigned
    from variable k.

  * k = nr of 1's in bitmask = ( __builtin_popcount)
  * bitmask 2^n where each 1 is the subject s_i liked 
    by student k 

    https://algowarehouse.blogspot.com/2018/01/bitmask-dp-buildup-to-sos-dp-pt-2.html

 */

// O(n * (2^n))
int main(){

    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;

        // store students preferences
        vector<vb> bitmap(n+1, vb(n+1, false));

        // store the number of diff assignments
        // according to no of bits (possibilites)in bitmask
        vl assign(1 << (n+1), 0);
        assign[0] = 1;

        // read student subj preferences
        bool x;
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                cin >> x, bitmap[i][j] = (bool)x;

        // all possible bitmasks 2^n
        for(int b = 1; b <= (1 << n); b++){
            
            // count number of '1' bits in mask 'b'
            // also the ith student
            int i = __builtin_popcount(b);

            // O(n)
            for(int k = 0; k < n; k++){

                // if student doesnt like subject
                // or
                // k'th bit is not set in bitmask
                if(bitmap[i-1][k] == false || (b & (1 << k)) == 0)
                    continue;

                // e.g. assign[10101] = assign[00101] + assign[10001] + assign[10100]
                // "assign subject k to ith student"
                // unset kth bit from bitmask and sum
                assign[b] += assign[(b & ~(1 << k))];
            }
        }

        cout << assign[(1 << n) - 1] << endl;
        

    }

    return 0;
}
