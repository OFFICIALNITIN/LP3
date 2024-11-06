#include<iostream>
using namespace std;

//Iterative Fibonacci function
int fibonacci_iter(int n){
    if(n < 0) return -1;
    if(n == 0) return 0;
    if(n == 1) return 1;

    int a = 0, b = 1, c;
    for(int i = 2; i <= n; i++){
        c = a + b;
        a = b;
        b = c;
    }

    return c;
}

//Recursive Fibonacci function
int fibonaaci_recur(int n){
    if(n < 0) return -1;
    if(n == 0) return 0;
    if(n == 1) return 1;

    return fibonaaci_recur(n - 1) + fibonaaci_recur(n - 2);
}

int main(){
    int n;
    cout<<"Enter a number";
    cin>>n;

    cout<<"Iterative Fibonacci of"<<n<<":"<<fibonacci_iter(n)<<endl;
    cout<<"Recursive Fibonacci of"<<n<<":"<<fibonaaci_recur(n)<<endl;

    return 0;
}