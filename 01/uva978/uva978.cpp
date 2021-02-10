#include <bits/stdc++.h> 

using namespace std;

int main(){

    int n;
    cin >> n;

    bool first = true;
    
    while(n--){

        if(!first){
            cout << endl;
        }else{
            first = false;
        }
        
        int b, sg, sb;

        cin >> b >> sg >> sb;

        // store teams in two multisets
        multiset<int, greater<int>> green, blue;
                
        for(int i = 0; i < sg; i++){
            int x;
            cin >> x;
            green.insert(x);
        }

        //cout << "green: " << green.size() << endl;

        for(int i = 0; i < sb; i++){
            int x;
            cin >> x;
            blue.insert(x);
        }

        //cout << "blue: " << blue.size() << endl;

        //sort(green.begin(), green.end(), greater<int>());
        //sort(blue.begin(), blue.end(), greater<int>());

        /*
        for(auto it = green.begin(); it != green.end(); ++it){
            cout << *it << " ";
        }
        cout << endl;

        for(auto it = blue.begin(); it != blue.end(); ++it){
            cout << *it << " ";
        }
        cout << endl;
        */

        while(!green.empty() && !blue.empty()){

            // queue of soldiers of each team
            // ready to fight
            queue<int> q_green;
            queue<int> q_blue;

            int rounds = 0;
            
            for(int i = 0; i < b; i++){
                if(!green.size() || !blue.size())
                    break;

                // move green soldier to the queue battle
                q_green.push(*green.begin());
                green.erase(green.begin());

                // move blue soldier to the queue battle
                q_blue.push(*blue.begin());
                blue.erase(blue.begin());

                ++rounds;
            }

            // simulate a round
            while(rounds--){
                
                int g_lem = q_green.front();
                q_green.pop();

                int b_lem = q_blue.front();
                q_blue.pop();

                // green soldier is stronger
                // green survives and goes back to the army (damaged)
                if(g_lem > b_lem)
                    green.insert(g_lem - b_lem);

                // blue soldier is stronger
                // blue survives and goes back to the army (damaged)
                else if(b_lem > g_lem)
                    blue.insert(b_lem - g_lem);
                
            }

            //cout << "END: " << green.size() << " " << blue.size() << endl;

        }

        // check who has more remaining soliders (winner)
        if(green.size() > blue.size()){
            cout << "green wins" << endl;
            for(auto it = green.begin(); it != green.end(); ++it){
                cout << *it << endl;
            }
            
        }else if(blue.size() > green.size()){
            cout << "blue wins" << endl;
            for(auto it = blue.begin(); it != blue.end(); ++it){
                cout << *it << endl;
            }
            
        }else{
            cout << "green and blue died" << endl;
        }
            
 
        
    }
    
    return 0;
}
