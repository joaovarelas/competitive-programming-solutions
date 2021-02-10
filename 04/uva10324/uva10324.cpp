#include <bits/stdc++.h>

using namespace std;

typedef unsigned int uint;
typedef vector<uint> vu;


// answer if all chars in [i,j] are all the same
bool query(string* s, vu* sum, uint a, uint b){

    // 1 ... 0 or 0 ... 1 => not true
    if(s->at(a) != s->at(b))
        return false;

    char c = s->at(a);

    if(c == '0'){
        // 0 ... 0
        // => sum at 'a' must be == sum at 'b'
        return sum->at(a) == sum->at(b);
    }

    if(c == '1'){
        // 1 ... 1
        // => sum at 'b' must be == (b-a) + sum[a]
        return sum->at(b) - sum->at(a) == (b-a);
    }
    
    return false;
}

int main(){
    string s;
    uint k = 1;
    
    // read 
    while(cin >> s){
        vu v(s.size());

        uint i = 0;
        
        // calc sums array
        for(char& c : s){
            if(i == 0){
                v[i] = (c == '0') ? 0 : 1;
                ++i;
                continue;
            }
    
            if(c == '0') v[i] = v[i-1];
            else if(c == '1') v[i] = v[i-1] + 1;
            ++i;
        }


        // answer range queries
        printf("Case %d:\n", k++);
        uint q;
        scanf("%d", &q);
        while(q--){
            uint a, b;
            scanf("%d %d", &a, &b);
            printf("%s\n", (query(&s, &v, min(a,b), max(a,b)) ? "Yes" : "No")); 
        }
        
        cin.ignore();
        //cout << "read: " << s << endl;
    }

    return 0;
}
