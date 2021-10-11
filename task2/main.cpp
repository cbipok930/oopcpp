//
// Created by alex_ on 03.10.2021.
//
#include <iostream>
#include "HashTable.h"

int main(int argc, char** argv){
    auto *table = new HashTable();
    Value s;
    s.age =16;
    s.weight =67;
    Key a;
    for(int i = 0; i <2; i++){
        a = argv[i +1];
        table->insert(a,s);
        }
    bool meh = table->contains("Lol");
    std::cout << meh <<'\n';
    Value ee = table->at("Lol");
    std::cout << ee.weight<<' '<< ee.age << '\n';
//    std::cout << table->contains("DKDOFdsjofjsdfosdjfsd")<<'\n';
//    Value none = table->at("DKDOFdsjofjsdfosdjfsd");
    std::cout << "Hello, World!" << std::endl;
//    table->erase("Lol");
//    table->erase("Lol");
//    table->erase("DKDOFdsjofjsdfosdjfsd");
    auto *bla = new HashTable();
    for(int i = 0; i <2; i++){
        a = argv[i +1];
        table->insert(a,s);
    }
    meh = ((*bla) == (*table));
    delete table;
    return 0;
}
