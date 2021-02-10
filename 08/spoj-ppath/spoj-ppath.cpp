#include <bits/stdc++.h>

#define NMAX 10001
#define INF 9999999

using namespace std;

typedef unsigned long long int ull;
typedef long long int ll;
typedef vector<int> vi;
typedef vector<ull> vu;
typedef vector<ll> vl;
typedef vector<bool> vb;
typedef vector<string> vs;
typedef pair<int,int> Pair;

// Calc primes 
vb sieve(){
    vb prime(NMAX, true);
    
    for(int i = 2; i < NMAX; i++)
        for(int j = i * i; j < NMAX; j += i) 
            prime[j] = false;
    
    return prime;
}

vi generate_next(vb prime, int v);

// worst case ~ O(40^4) = O(b^d)
int bfs(vb prime, int a, int b){
    vb visited(NMAX, false);
    vi cost(NMAX, INF);
    //vi parent(NMAX, -1);
   
    queue<int> q;

    bool found = false;
    int v = a;

    cost[v] = 0;
    q.push(v);

    // while queue has elements
    while(!q.empty()){
        v = q.front();
        q.pop();

        //printf("pop: %d\n", v);
        
        visited[v] = true;

        // generate adjacents (primes that differ 1 digit from 'v')
        for(int adj : generate_next(prime, v)){

            // found target node
            // update cost and exit loop
            if(adj == b){
                found = true;
                cost[adj] = cost[v] + 1;
                v = adj;
                break;
            }

            // push adjacent into queue
            if(!visited[adj] && adj != v){
                q.push(adj);
                cost[adj] = min(cost[adj], cost[v] + 1);
            }
        }

        if(found)
            break;

    }

    if(!found)
        return INF;

    return cost[v];
}


int main(){

    vb prime = sieve();
    
    int t;
    cin >> t;
    while(t--){

        // 4 digit primes, from 'a' to 'b'
        int a, b; 
        cin >> a >> b;
        
        // no cost, already at the target node
        if(a == b){
            cout << "0" << endl;
            continue;
        }

        // try to find path from a -> b
        // path of primes
        int cost = bfs(prime, a, b);

        // no path found
        if(cost == INF){
            cout << "Impossible" << endl;
            continue;
        }

        // path found, print optimal cost (min depth) 
        cout << cost << endl;
        
    }

    return 0;
}







// Really bad adjacent generator (hardcoded)
vi generate_next(vb prime, int v){

    vb pushed(NMAX, false);
    vi adj;

    int d, r;

    d = v / 1;
    r = v % 1;
    //printf("d %d, r %d\n", d, r);
    for(int i = 0; i <= 9; i++){
        //printf("%d\n", d/1000*1000 + ((d/100)%10)*100 + ((d/10)%10)*10 + i);
        int n = d/1000*1000 + ((d/100)%10)*100 + ((d/10)%10)*10 + i;
        if(prime[n] && !pushed[n] && n > 999)
            adj.push_back(n);
    }

    d = v / 10;
    r = v % 10;
    //printf("d %d, r %d\n", d, r);
    for(int i = 0; i <= 9; i++){
        //printf("%d\n", d/100*1000 + ((d/10)%10)*100 + i*10 + r);
        int n = d/100*1000 + ((d/10)%10)*100 + i*10 + r;
        if(prime[n] && !pushed[n] && n > 999)
            adj.push_back(n);
    }
    
    
    d = v / 100;
    r = v % 100;
    //printf("d %d, r %d\n", d, r);
    for(int i = 0; i <= 9; i++){
        //printf("%d\n", d/10*1000 + i*100 + r);
        int n = d/10*1000 + i*100 + r;
         if(prime[n] && !pushed[n] && n > 999)
            adj.push_back(n);
    }

    d = v / 1000;
    r = v % 1000;
    //printf("d %d, r %d\n", d, r);
    for(int i = 0; i <= 9; i++){
        //printf("%d\n", i*1000 + r);
        int n = i*1000 + r;
        if(prime[n] && !pushed[n] && n > 999)
            adj.push_back(n);
    }

    /*
    printf("generated for %d: ", v);
    for(int x : adj)
        cout << x << " ";
    cout << endl << "----------" << endl;
    */
    
    return adj;
}
