#include <iostream>
using namespace std;

// Iterative Fibonacci function with step counting
int fibonacci_iter(int n, int &steps) {
    if (n < 0) {
        steps = 1;
        return -1; // Handling invalid input
    }
    if (n == 0 || n == 1) {
        steps = 1;
        return n; // Base cases
    }

    int a = 0, b = 1, c;
    steps = 1; // Initial step count

    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
        steps++;
    }

    return c;
}

// Recursive Fibonacci function with step counting
int fibonacci_recur(int n, int &steps) {
    if (n < 0) {
        steps = 1;
        return -1; // Handling invalid input
    }
    if (n == 0 || n == 1) {
        steps = 1;
        return n; // Base cases
    }

    int steps1 = 0, steps2 = 0;
    int fib1 = fibonacci_recur(n - 1, steps1);
    int fib2 = fibonacci_recur(n - 2, steps2);

    steps = steps1 + steps2 + 1; // Count this function call as a step
    return fib1 + fib2;
}

int main() {
    int n;
    cout << "Enter a number: ";
    cin >> n;

    int steps_iter = 0;
    int fib_iter = fibonacci_iter(n, steps_iter);
    cout << "Iterative: " << fib_iter << "\nSteps: " << steps_iter << endl;

    int steps_recur = 0;
    int fib_recur = fibonacci_recur(n, steps_recur);
    cout << "Recursive: " << fib_recur << "\nSteps: " << steps_recur << endl;

    return 0;
}
