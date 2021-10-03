//
// Created by alex_ on 03.10.2021.
//
#include <iostream>
#include "HashTable.h"

int main(){
    HashTable table;
    Value s;
    s.age =16;
    s.weight =67;
    Key a;
    while(true){
        std::cin >> a;
        table.insert(a,s);
        }
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
