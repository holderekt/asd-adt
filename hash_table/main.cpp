#include <iostream>
#include "hash_table.hpp"
#include <string>

using namespace std;

int main(){

    Hash_Table<string, int> table(3);
    table.insert({"a",1});
    table.insert({"b",2});

    /* Lei */
    table["a"] = 5;

    cout << table;
    return 0;
}