// В этой задаче для простоты не требуется делать контейнер шаблонным,
// это допускается по желанию. Для нешаблонного решения,
// введем типы ключей и значений: ключом будет выступать строка (например, имя
// студента, значением - произвольная структура (например, численные
// характеристики студента.
#include "HashTable.h"

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
    HashTable::data.resize(16);
    HashTable::cap = 16;
}
HashTable::~HashTable()= default;
bool HashTable::insert(const Key &k, const Value &v) {
    uint64_t index = hash_function(k, HashTable::cap) ;
    HashTable::data.size();
    HashTable::data.capacity();
    std::list<std::pair<Key, Value>>* mylist = &(HashTable::data.at(index));
    mylist->push_back(std::pair<Key, Value>(k, v));
    return true;
}
bool operator==(const HashTable& a, const HashTable& b);
bool operator!=(const HashTable& a, const HashTable& b);


