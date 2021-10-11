// В этой задаче для простоты не требуется делать контейнер шаблонным,
// это допускается по желанию. Для нешаблонного решения,
// введем типы ключей и значений: ключом будет выступать строка (например, имя
// студента, значением - произвольная структура (например, численные
// характеристики студента.
#include "HashTable.h"
#include <exception>
#include <stdexcept>
#include <iostream>


uint64_t hash_function(Key key, int cap){
    uint64_t x;
    x = (uint64_t)key.size();
    for(Key::iterator it = key.begin();it != key.end(); it++){
        x+= (uint64_t)*it;
        x|= (uint64_t)*it%cap;
    }
    x &= key.size() * key.front();
    x ^= key.back() - key.back() / 2;
    x%= cap;
    return x;
}

HashTable::HashTable(){
    HashTable::data.resize(16);
    HashTable::cap = 4;
}
HashTable::~HashTable()= default;

bool HashTable::erase(const Key &k) {
    uint64_t index = hash_function(k, HashTable::cap) ;
    Datalist &val_list = HashTable::data.at(index);
    auto it = val_list.begin();
    for (; (*it).first != k; it++) {
        if (it == val_list.end() && (*it).first != k) {
            return false;
        }
    }
    val_list.erase(it);
    return true;
}
bool HashTable::insert(const Key &k, const Value &v) {
    uint64_t index = hash_function(k, HashTable::cap) ;
    Datalist &mylist = HashTable::data.at(index);
    if(mylist.size() == mylist.max_size()){
        mylist.resize(mylist.max_size() * 2);
    }
    try
    {
        mylist.push_front(std::pair<Key, Value>(k, v));
    }
    catch (std::bad_alloc& e) {
        return false;
    }
    return true;
}
bool HashTable::contains(const Key &k) const {
    int capacity = HashTable::cap;
    uint64_t  hash = hash_function(k, capacity);
    const Datalist* val_list = &(HashTable::data.at(hash));
    if(val_list->empty()){
        return false;
    }
    auto it = val_list->begin();
    for (; (*it).first != k; it++) {
        if (it == val_list->end() && (*it).first != k) {
            return false;
        }
    }
    return true;
}

Value&  HashTable::at(const Key& k){
    int capacity = HashTable::cap;
    uint64_t  hash = hash_function(k, capacity);
    Datalist* val_list = &(HashTable::data.at(hash));
    try
    {
        if(val_list->empty()){
            throw -1;
        }
        auto it = val_list->begin();
        for (; (*it).first != k; it++) {
            if (it == val_list->end() && (*it).first != k) {
                throw -1;
            }
        }
        return (*it).second;
    }
    catch (int a)
    {
        std::cerr << "Couldn't find element by key " << '"' << k << '"';
        std::exit(-1);
    }
}

HashTable::HashTable(const HashTable &b) {
    }

HashTable::HashTable(HashTable &&b) {
    }

HashTable &HashTable::operator=(const HashTable &b) {
    return const_cast<HashTable &>(b);
}

HashTable &HashTable::operator=(HashTable &&b) {
    return b;
}


bool operator==(const HashTable& a, const HashTable& b){
    if(a.data.size() != b.data.size()){
        return false;
    }
    auto ita = a.data.begin();
    auto itb = b.data.begin();
    for( ;ita != a.data.end() || itb!= b.data.end(); ){
        if((*itb) != (*ita)){
            return false;
        }
        itb++;
        ita++;
    }
    return true;
}
bool operator!=(const HashTable& a, const HashTable& b){
    if(a.data.size() != b.data.size()){
        return true;
    }
    auto ita = a.data.begin();
    auto itb = b.data.begin();
    for( ;ita != a.data.end() || itb!= b.data.end(); ){
        if((*itb) != (*ita)){
            return true;
        }
        itb++;
        ita++;
    }
    return false;
}



