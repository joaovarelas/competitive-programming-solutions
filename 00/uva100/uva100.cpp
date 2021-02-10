#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

#define EVEN(n) (n%2==0)
#define ODD(n)  (n%2!=0)

using namespace std;

int cycles(int n){
    int c = 1;

    while(n != 1){
        if(ODD(n)) n = 3*n+1;
        else n = n/2;
        ++c;
    }
    return c;
}

int solve(int i, int j){
    int m = 1;
    for(int k = i; k <= j; ++k){
        int c = cycles(k);
        m = c > m ? c : m;
    }
    return m;
}

int main(){
    
    string line;
    int i, j;
    while(getline(cin, line)){
        stringstream(line) >> i >> j;
        int m = solve(min(i,j), max(i,j));
        cout << i << " " << j << " " << m << endl;
    }
    
    return 0;
}
