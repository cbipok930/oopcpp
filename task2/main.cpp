//
// Created by alex_ on 03.10.2021.
//
#include "HashTable.h"

int main(int argc, char** argv){
    HashTable table(20);
    for(int i = 0; i <6; i++){
        table.insert(argv[i +1],{(unsigned int)argv[i + 1][0] / 3, (unsigned int)argv[i + 1][0] * 2});
        }
    table.printHashTable();
    auto *tbl2p = new HashTable(10);
    for (unsigned int i = 4; i > 1; i--){
        tbl2p->insert(argv[i], {28 - i, 75 + i * 2});
    }
        tbl2p->printHashTable();
    HashTable tbl3(table);
        tbl3.printHashTable();
    tbl3.insert("Net",{25, 74});
        tbl3.printHashTable();
    table.swap(tbl3);
    table = std::move(tbl3);
        table.printHashTable();
    std::cout <<table.size() <<'\n' <<std::flush;
    table = *tbl2p;
    std::cout <<(table == *tbl2p) << '\n' <<std::flush;
    tbl2p->insert("Rata", {21, 87});
        table.printHashTable();
        tbl2p->printHashTable();
    Value a = table["Net"];
    *tbl2p = table;
    table.insert("Meh", {17,57});
    tbl2p->printHashTable();
    table.printHashTable();
    table.clear();
        table.printHashTable();
    std::cout <<(table.empty()) <<std::flush;
    delete &table;
    delete &tbl2p;
    return 0;
}