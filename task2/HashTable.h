//
// Created by alex_ on 03.10.2021.
//

#ifndef TASK2_HASHTABLE_H
#define TASK2_HASHTABLE_H
#include<vector>
#include<string>
#include<list>
#include <iostream>
#define LOAD_FACTOR 0.7
struct Student {
    unsigned age;
    unsigned weight;
};
typedef std::string Key;
typedef Student Value;
typedef std::vector<std::list<std::pair<Key,Value>>> Structure;
typedef std::list<std::pair<Key, Value>> Datalist;
typedef std::pair<Key, Value> ListContent;
class HashTable{
private:
    Structure data;
    size_t cap;
    size_t size_prop;
public:
    // расширяет таблицу
    bool rehash();

    HashTable(size_t capacity = 16);
    ~HashTable();

    HashTable(const HashTable& b);
    HashTable(HashTable&& b) noexcept;


    HashTable& operator=(const HashTable& b);
    HashTable& operator=(HashTable&& b) noexcept;

    friend bool operator==(const HashTable& a, const HashTable& b);
    friend bool operator!=(const HashTable& a, const HashTable& b);

    // Обменивает значения двух хэш-таблиц.
    void swap(HashTable& b);

    // Очищает контейнер.
    void clear();
    // Удаляет элемент по заданному ключу.
    bool erase(const Key& k);
    // Вставка в контейнер. Возвращаемое значение - успешность вставки.
    bool insert(const Key& k, const Value& v);

    // Проверка наличия значения по заданному ключу.
    bool contains(const Key& k) const;

    // Возвращает значение по ключу. Небезопасный метод.
    // В случае отсутствия ключа в контейнере, следует вставить в контейнер
    // значение, созданное конструктором по умолчанию и вернуть ссылку на него.
    Value& operator[](const Key& k);

    // Возвращает значение по ключу. Бросает исключение при неудаче.
    Value& at(const Key& k);
    const Value& at(const Key& k) const;

    //Возвращает количество элементов в таблице
    size_t size() const;
    //Возвращает вместимость таблицы
    size_t size_max() const;
    //Проверка на пустоту
    bool empty() const;
    //Заполняет переданный список значениями из таблицы
    void get_contents(Datalist& v);
    //Печатает таблицу
    void printHashTable();
};
#endif //TASK2_HASHTABLE_H
