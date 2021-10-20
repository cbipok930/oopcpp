// В этой задаче для простоты не требуется делать контейнер шаблонным,
// это допускается по желанию. Для нешаблонного решения,
// введем типы ключей и значений: ключом будет выступать строка (например, имя
// студента, значением - произвольная структура (например, численные
// характеристики студента.
#include "HashTable.h"
#include <stdexcept>

uint64_t hash_function(const Key& key, size_t cap){
    size_t hash = 5381;
    for (auto & it : key)
        hash = ((hash << 5) + hash) + int(it);
    return hash%cap;
}

bool HashTable::rehash() {
    Datalist tmp;
    for(auto lit: this->data){
        for(auto it = lit.begin(); it != lit.end(); it++){
            tmp.push_back(std::pair<std::string, Student>(it->first, it->second));
        }
    }
    HashTable re(this->cap * 2);
    if(re.cap != (this->cap * 2)){
        std::cout <<"Couldn't rehash hashtable" <<this<<std::flush;
        return false;
    }
    for(auto it: tmp){
        re.insert(it.first, it.second);
    }
    *this = re;
    delete &re;
    tmp.clear();
    return true;
}

HashTable::HashTable(size_t capacity){
    HashTable::cap = capacity;
    HashTable::size_prop = 0;
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
    HashTable::size_prop =0;
    for (int i =0; i < b.cap; i++){
        Datalist blist = b.data[i];
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

    if(a.size_prop != b.size_prop || a.data.size() != b.data.size()){
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
    this->size_prop -=1;
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
    this->size_prop+=1;
    if ((double)this->size_prop / (double)this->cap >= LOAD_FACTOR) {
        bool suc = this->rehash();
        if (!suc)
            return false;
    }
    return true;
}
bool HashTable::contains(const Key &k) const {
    size_t capacity = this->cap;
    uint64_t  hash = hash_function(k, capacity);
    const Datalist* val_list = &(this->data.at(hash));
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
    size_t capacity = HashTable::cap;
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
        throw -1;
    }
}

const Value &HashTable::at(const Key &k) const {
    size_t capacity = HashTable::cap;
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
    return this->size_prop;
}

size_t HashTable::size_max() const{
    return this->cap;
}

bool HashTable::empty() const {
    if(this->size_prop == 0)
        return true;
    else
        return false;
}

void HashTable::get_contents(Datalist& v){
    for(auto lit: this->data){
        for(auto it = lit.begin(); it != lit.end(); it++){
            v.push_back(std::pair<std::string, Student>(it->first, it->second));
        }
    }
}

void HashTable::printHashTable() {
    std::cout <<HashTable::cap <<"  " << this <<'\n'<< std::flush;
    for(int i =0; i < HashTable::cap; i++){
        std::cout <<'['<<i<<']'<<" "<< std::flush;
        for(auto & it : HashTable::data[i]){
            std::cout << it.first << ": " <<'('<<it.second.age <<", "<<it.second.weight <<')' << "   " << std::flush;
        }
        std::cout << '\n'<< std::flush;
    }
}

