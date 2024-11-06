#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

//Function to slove 0-1 knapsack problem using dynamic programming
int knapsack(int W, vector<int>& weights, vector<int>& values, int n){
    //DP table to store maximum values for each capacity and items considered

    vector<vector<int>> dp(n+1, vector<int>(W+1,0));

    //Build the table in bottom-up manner
    for(int i = 1; i <= n; i++){
        for(int w = 0; w <= W; w++){
            if(weights[i-1] <= w){
                //Max of including or excluding the current item
                dp[i][w] = max(dp[i - 1][w], values[i -  1] + dp[i - 1][w - weights[i - 1]]);
            }else{
                //If item cannot be included, use the previous value
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[n][W]; // The maximum value that can be put in knapsack of capacity w
}

int main(){
    int n,W;

    cout<<"Enter the number of items: ";
    cin>>n;

    vector<int> weights(n), values(n);
    cout<<"Enter weight and value for each item:\n";
    for(int i = 0; i < n;i++){
        cout<<"Item "<< i + 1<<" - Weight: ";
        cin>>weights[i];
        cout<<"Item "<< i + 1<<" - Value: ";
        cin>>values[i];
    }

    cout<<"Enter the maximum capacity of the knapsack: ";
    cin>>W;

    int maxValue = knapsack(W, weights, values, n);
    cout<<"The maximum value is the knapsack is: "<<maxValue<<endl;

    return 0;
}