#include <bits/stdc++.h>
#include "cache.h"
#include <fstream>
// #include "final_tree.h"
using namespace std;


int main()
{
    int capacity;
    cin>>capacity;
    LRUCache L(capacity);

    typedef struct Data
    {
        string operation;
        int key;
        string value;
    } Data;


    ifstream file("data.txt");
    if (!file) {
        std::cerr << "Error opening file\n";
        return 1;
    }

    Data d;
    while (file >> d.operation >> d.key) {
        // Check if it's a "put" operation, which requires reading an additional value
        if (d.operation == "put") {
            file >> d.value;
        } else {
            d.value.clear(); // Clear any previous value for "get" operation
        }

        // Output the operation for debugging
        cout << "Operation: " << d.operation << ", Key: " << d.key;
        if (d.operation == "put") {
            cout << ", Value: " << d.value;
        }
        cout << endl;

        // Perform the cache operation
        if (d.operation == "get") {
            L.get(d.key);
        } else if (d.operation == "put") {
            L.put(d.key, d.value);
        }
    }

    file.close();

        // L.put(2,"Kashish");
        // L.put(3,"Sriya");
        // L.put(4,"Krishna");
        // L.put(5,"Ishan");
        // cout<<L.get(5)<<endl;
        // cout<<L.get(-1)<<endl;
        // cout<<L.get(2)<<endl;


    double hit_rate = L.HitRate(), total_access_time = L.AverageAccessTime();
    int eviction_count= L.EvictionCount();

    cout<<hit_rate<<" "<<total_access_time<<" "<<eviction_count;


}