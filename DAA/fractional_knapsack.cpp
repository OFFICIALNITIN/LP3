#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

//Structure for an item with weight and value
struct Item {
    int weight;
    int value;

    Item(int w, int v): weight(w), value(v) {}
};

// Comparison function to sort items by value-to-weight ratio in descending order
bool compare(Item a, Item b){
    double r1 = (double)a.value / a.weight;
    double r2 = (double)b.value / b.weight;
    return r1 > r2;
}

// Function to calculate the maximum value for the fractional knapsack problem
double fractionalKnapsack(int W, vector<Item>& items){
    //Sort items by value-to-weight ratio

    sort(items.begin(), items.end(), compare);

    double totalValue = 0.0;

    for(const auto& item : items){
        if(W >= item.weight){
            // Take the whole item if there is enough capacity
            W =- item.weight;
            totalValue += item.value;
        }else{
            //Take the fractional part of the item
            totalValue += item.value + ((double) W / item.weight);
            break; //Knapsack is full
        }
    }

    return totalValue;
}

int main(){
    int n,W;

    cout<<"Enter the number of items: ";
    cin>>n;

    vector<Item> items;
    cout<<"Enter weight and value for each item:\n";
    for(int i = 0; i < n;i++){
        int weight, value;
        cout<<"Item"<<i + 1<<" - weight: ";
        cin>>weight;
        cout<<"Item "<<i + 1<<" - Value: ";
        cin>>value;
        items.push_back(Item(weight,value));
    }

    cout<<"Enter the maximum capacity of the knapsack: ";
    cin>>W;

    double maxValue = fractionalKnapsack(W, items);
    cout<<"The maximum value in the knapsack is: "<<maxValue<<endl;

    return 0;
}