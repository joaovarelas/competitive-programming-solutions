#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef vector<string> vs;

vs LCS(vs w1, vs w2){
    int n = w1.size(), m = w2.size();
    
    vector<vi> ed(n+1, vi(m+1, 0));
    
    // edit distance variant
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){

            if(w1[i-1] == w2[j-1])
                ed[i][j] = ed[i-1][j-1] + 1;
            else
                ed[i][j] = max(ed[i-1][j], ed[i][j-1]);
            
        }
    }

    /*
    for(vi& v : ed){
        for(int x : v){
            printf("%d ", x);
        }
        printf("\n");
    }
    

    for(string s : w1)
        cout << s << " ";
    */


    // store the path of the words sequence
    vs backtrack;
    int i = n, j = m;
    while(i > 0 && j > 0){

        if(w1[i-1] == w2[j-1])
            backtrack.push_back(w1[i-1]), --i, --j;

        // follow the max distance between ed[i-1][j] and ed[i][j-1]
        else if(ed[i-1][j] > ed[i][j-1])
            // go back up one line 
            --i;
        
        else if(ed[i-1][j] <= ed[i][j-1])
            // go left one column
            --j;
    }

    reverse(backtrack.begin(), backtrack.end());
    
    //for(string s : backtrack)
    //  cout << s << " ";
        
    return backtrack;
}

int main(){
    vs words1;
    vs words2;
    
    string word;

    int hashtag = 0;
    while(cin >> word){
        if(word == "#"){
            ++hashtag;

            if(hashtag == 1)
                continue;
            if(hashtag > 1){
                // compute
                vs seq = LCS(words1, words2);

                // print the sequence
                bool first = true;
                for(string s : seq)
                    if(first) cout << s, first = false;
                    else cout << " " << s;
                cout << endl;

                // reset
                words1.clear();
                words2.clear();
                hashtag = 0;
                continue;
            }
                
        }

        if(hashtag == 0)
            words1.push_back(word);
        if(hashtag == 1)
            words2.push_back(word);
    }
    
    return 0;
}
