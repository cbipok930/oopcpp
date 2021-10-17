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
    size_t hash = 5381;
    for (Key::iterator it = key.begin(); it != key.end(); it++)
        hash = ((hash << 5) + hash) + int(*it);
    return hash%cap;
}

HashTable::HashTable(int capacity){
    HashTable::cap = capacity;
    HashTable::data.resize(HashTable::cap);
}
HashTable::~HashTable(){
    HashTable::data.clear();
    HashTable::data.resize(0);
}

HashTable::HashTable(const HashTable &b) {
    *this = b;
}

HashTable::HashTable(HashTable &&b)  noexcept {
    *this = b;
    delete &b;
}

HashTable &HashTable::operator=(const HashTable &b) {
    HashTable::cap = b.cap;
    HashTable::data.clear();
    HashTable::data.resize(HashTable::cap);
    for (int i =0; i < b.cap; i++){
        Datalist blist = b.data[i];;
        auto itb = blist.begin();
        while(itb != blist.end()){
            (*this).insert(itb->first, {itb->second.age, itb->second.weight});
            itb++;
        }
    }
    return *this;
}

HashTable &HashTable::operator=(HashTable &&b)  noexcept {
    *this = b;
    delete &b;
    return *this;
}

bool operator==(const HashTable& a, const HashTable& b){
    if(a.data.size() != b.data.size()){
       return false;
    }
    else{
        for (int i =0; i < a.cap; i++){
            if (a.data[i].size() != b.data[i].size())
                return false;
            else{
                Datalist alist = a.data[i];
                Datalist blist = b.data[i];
                auto ita = alist.begin();
                auto itb = blist.begin();
                while(ita != alist.end()){
                    if (ita->first != itb->first || ita->second.weight != itb->second.weight ||
                    ita->second.age != itb->second.age)
                        return false;
                    itb++;
                    ita++;
                }
            }
        }
        return true;
    }
}

bool operator!=(const HashTable& a, const HashTable& b){
    return !(a == b);
}

void HashTable::swap(HashTable &b) {
    HashTable tmp(*this);
    *this = b;
    b = tmp;
    delete &tmp;
}

void HashTable::clear() {
    HashTable::data.clear();
    HashTable::data.resize(HashTable::cap);
}

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
        mylist.push_back(std::pair<Key, Value>(k, v));
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

Value  &HashTable::operator[](const Key &k) {
    if(this->contains(k)){
        return this->at(k);
    } else
    {
        this->insert(k, {0 , 0});
        std::cout <<"Couldn't find element by key " <<k <<" in hashtable " <<this <<"\nValue is inserted"
        <<std::flush;
        return this->at(k);
    }
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
        std::cerr << "Couldn't find element by key" << '"' << k << '"'<< std::flush;
        std::exit(-1);
    }
}

const Value &HashTable::at(const Key &k) const {
    int capacity = HashTable::cap;
    uint64_t  hash = hash_function(k, capacity);
    const Datalist* val_list = &(HashTable::data.at(hash));
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
        std::cerr << "Couldn't find element by key" << '"' << k << '"'<< std::flush;
        std::exit(-1);
    }
}

size_t HashTable::size() const {
    size_t size = 0;
    for (auto lst = this->data.begin(); lst != this->data.end(); lst++) {
        size += lst->size();
    }
    return size;
}

bool HashTable::empty() const {
    HashTable tmp(*this);
    tmp.clear();
    if (tmp == *this){
        delete &tmp;
        return true;
    }
    else{
        delete &tmp;
        return false;
    }
}

void HashTable::printHashTable() {
    std::cout <<HashTable::cap <<"  " << this <<'\n'<< std::flush;
    for(int i =0; i < HashTable::cap; i++){
        std::cout <<'['<<i<<']'<<" "<< std::flush;
        for(auto it = HashTable::data[i].begin(); it != HashTable::data[i].end(); it++ ){
            std::cout << it->first << ": " <<'('<<it->second.age <<", "<<it->second.weight <<')' << "   " << std::flush;
        }
        std::cout << '\n'<< std::flush;
    }
}



