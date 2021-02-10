#include <iostream>
#include <cmath>

using namespace std;

int a, b, c;

// given function
double fn(double x){
    return a*x + b*sin(x) - c;
}

// find i j such that f(i) * f(j) < 0
// i < 0 || j < 0
pair<double, double> find_interval(){
    for(double i = -a-b-c; i <= a+b+c; i++){
        for(double j = -a-b-c; j <= a+b+c; j++){
            if( fn(i) * fn(j) < 0 )
                return make_pair(i, j);
        }
    }

    return make_pair(-1000, 1000);
}


double bisection(int x0, int x1){
    double y0 = x0, y1 = x1;

    double m = (y0 + y1)/2.0;
    
    while( (y1 - y0)/2.0 >= 0.000001 ){
        
        if( fn(m) == 0.0 )
            break;
        else if( fn(m) < 0 )
            y0 = m;
        else if( fn(m) > 0 )
            y1 = m;
        
        m = (y0 + y1)/2.0;

        //printf("a: %f b: %f m %.6f fn(m): %.6lf \n", y0, y1, m, fn(m));

    }

    return m;
    
}


int main(){

    int n;
    cin >> n;

    while(n--){
        cin >> a >> b >> c;
        pair<double,double> ival = find_interval();
        double
            x0 = ival.first,
            x1 = ival.second;
        
        // bisection method O(log(x0+x1))
        double res = bisection(x0 , x1);

        printf("%.6f\n", res);
    }
    
    return 0;
}

