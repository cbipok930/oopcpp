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
    int i = 3;
    while(i > 0){
        std::cin >> a;
        table.insert(a,s);
        i--;
        }
    Value uu = table.at("Lol");
    std::cout << uu.age, uu.weight;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
