#include <bits/stdc++.h>

using namespace std;

#define INF numeric_limits<int>::max()

using ull = unsigned long long int;
using ll =  long long int;
template<class T1, class T2> using u_map = unordered_map<T1, T2>;
template<class T> using vec = vector<T>;
template<class T> using Pair =  pair<T,T>;
template<class T> using heapmin = priority_queue<T, vector<T>, less<T>>;
template<class T> using heapmax = priority_queue<T, vector<T>, greater<T>>;


double distance(Pair<double> p, Pair<double> q){ 
    return sqrt(pow(q.first - p.first, 2) +
                pow(q.second - p.second, 2)); 
}

double slope(Pair<double> p, Pair<double> q){
    double dy = q.second - p.second,
        dx = q.first - p.first;
    return dy / dx;
}

// sum the length of sunniest side of the mountains
// do not consider the shadow length
double sunny_length(vec<Pair<double>> points){
    
    double sunny = 0.0;
    int max_ytop = 0;
    
    for(int i = 0; i < points.size()-1; i += 2){
        Pair<double> p = points[i+1], q = points[i];

        // no sun here, right mountain has higher height
        if(p.second <= max_ytop) continue;
        
        double m = slope(p, q);
        double b = p.second - m * p.first;
   
        /* y = mx + b
           mx = y-b
           x = (y-b)/m
        */

        // find 'x' on the segment _pq_
        double x = (max_ytop - b)/m;

        sunny += distance(p, Pair<double>(x, max_ytop));

        // update the higher mountain height
        max_ytop = p.second;
    }

    return sunny;
}

int main(){
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        
        vec<Pair<double>> points;
        
        for(int i = 1; i <= n; i++){            
            int x, y;
            cin >> x >> y;
            points.push_back(Pair<double>(x, y));
        }

        // start from the sunniest mountain on the left
        sort(points.begin(), points.end(), greater<Pair<double>>());

        //cout << sunny_length(points) << endl;
        printf("%.2f\n", sunny_length(points));
        
    }
    
    return 0;
}
