#include <bits/stdc++.h>
#include "0cache.h"
#include <fstream>
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

    ifstream file("0data.txt");
    if (!file) {
        std::cerr << "Error opening file\n";
        return 1;
    }

    Data d;
    string line;

    // Process each line of the file
    while (getline(file, line)) {
        istringstream iss(line);
        iss >> d.operation >> d.key;

        // If the operation is "put", read the rest of the line as the value
        if (d.operation == "put") {
            getline(iss >> ws, d.value);  // Read remaining line as value
        } else {
            d.value.clear(); // Clear any previous value for "get" operation
        }

        // Output the operation for debugging
        cout <<endl<<endl<< "Operation: " << d.operation << ", Key: " << d.key;
        if (d.operation == "put") {
            cout << ", Value: " << d.value;
        }
        cout << endl;

        // Perform the cache operation
        if (d.operation == "get") {
            cout<<L.get(d.key)<<endl;
        } else if (d.operation == "put") {
            L.put(d.key, d.value);
        }
    }

    file.close();



    // ifstream file("0data.txt");
    // if (!file) {
    //     std::cerr << "Error opening file\n";
    //     return 1;
    // }

    // Data d;
    // while (file >> d.operation >> d.key) {
    //     // Check if it's a "put" operation, which requires reading an additional value
    //     if (d.operation == "put") {
    //         file >> d.value;
    //     } else {
    //         d.value.clear(); // Clear any previous value for "get" operation
    //     }

    //     // Output the operation for debugging
    //     cout << "Operation: " << d.operation << ", Key: " << d.key;
    //     if (d.operation == "put") {
    //         cout << ", Value: " << d.value;
    //     }
    //     cout << endl;

    //     // Perform the cache operation
    //     if (d.operation == "get") {
    //         cout<<L.get(d.key)<<endl;
    //     } else if (d.operation == "put") {
    //         L.put(d.key, d.value);
    //     }
    // }

    
    double hit_rate = L.HitRate(), total_access_time = L.AverageAccessTime();
    int eviction_count= L.EvictionCount();

    //final output is here
    cout<<hit_rate<<endl<<total_access_time<<endl<<eviction_count;

}