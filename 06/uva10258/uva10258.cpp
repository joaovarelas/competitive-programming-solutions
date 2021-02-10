#include <bits/stdc++.h>

#define NMAX 101

using namespace std;

typedef unsigned long long int ull;
typedef long long int ll;
typedef vector<int> vi;
typedef vector<ull> vu;
typedef vector<ll> vl;
typedef pair<int,int> Pair;

typedef struct _scoreboard{
    int id, solv, score;
} Scoreboard;

int main(){

    int t;
    scanf("%d", &t);

    while(t--){
        int id, solv, time;
        char status;
        
        string line;
        while(getline(line, 100, stdin)){
            //istringstream ss(line);
            //ss >> id >> solv >> time >> status;
            sscanf(line.c_str(), "%d %d %d %c", &id, &solv, &time, &status);
            printf("read: %d %d %d %c\n", id, solv, time, status);
        }
        
        Scoreboard score[NMAX];
        

    }

    

    return 0;
}
