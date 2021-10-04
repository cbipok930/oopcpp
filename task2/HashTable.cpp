// В этой задаче для простоты не требуется делать контейнер шаблонным,
// это допускается по желанию. Для нешаблонного решения,
// введем типы ключей и значений: ключом будет выступать строка (например, имя
// студента, значением - произвольная структура (например, численные
// характеристики студента.
#include "HashTable.h"

typedef std::list<std::pair<Key, Value>> Datalist;
typedef std::pair<Key, Value> ListContent;
uint64_t hash_function(Key key, int cap){
    uint64_t x;
    x = (uint64_t)key.size();
    for(Key::iterator it = key.begin();it != key.end(); it++){
        x+= (uint64_t)*it;
        x-= (uint64_t)*it%cap;
    }
    x &= key.size() * key.front();
    x ^= key.back() - key.back() / 2;
    x%= cap;
    return x;
}

HashTable::HashTable(){
    HashTable::data.resize(4);
    HashTable::cap = 4;
}
HashTable::~HashTable()= default;
bool HashTable::insert(const Key &k, const Value &v) {
    uint64_t index = hash_function(k, HashTable::cap) ;
    int a = HashTable::data.size();
    int b =HashTable::data.capacity();
    Datalist* mylist = &(HashTable::data.at(index));
    mylist->resize(7);
    mylist->push_back(std::pair<Key, Value>(k, v));
    return true;
}
Value&  HashTable::at(const Key& k){
    int cap = HashTable::cap;
    uint64_t  hash = hash_function(k,cap);
    Datalist* val_list = &(HashTable::data.at(hash));
    for(Datalist::iterator it = val_list->begin(); (*it).first != k; it++){
        return (*it).second;
    }
}
bool operator==(const HashTable& a, const HashTable& b);
bool operator!=(const HashTable& a, const HashTable& b);


