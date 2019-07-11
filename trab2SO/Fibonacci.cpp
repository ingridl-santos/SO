#include <iostream>

using namespace std;

int main() {
    int n, t1 = 0, t2 = 1, nextTerm = 0;
    cout << "Please Enter the series limit\n";
    cin >> n;
    cout << "Fibonacci Series:\n ";
    for (int i = 1; i <= n; ++i) {
        
        if(i == 1) {
            cout << "\t " << t1;
            continue;
        }
        if(i == 2) {
            cout << t2 << "\t ";
            continue;
        }
        nextTerm = t1 + t2;
        t1 = t2;
        t2 = nextTerm;
        
        cout << nextTerm << "\t ";
    }
    return 0;
}