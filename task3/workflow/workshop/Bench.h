//
// Created by alex_ on 12.11.2021.
//
#pragma once
#ifndef TASK3_BENCH_H
#define TASK3_BENCH_H
#include <string>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdarg>
#include <typeinfo>
#include <vector>
#include <algorithm>
typedef std::list<std::string> Args;
class BlockAbstract{
public:
    //Возвращает строку с адресом объекта и доп.текстом(параметр)
    std::string block_info(std::string str);
    //текст, который хранит блок
    std::string text;
    BlockAbstract() = default;
};
class CreatorAbstract{
public:
    //строковый id блока
    std::string block;
    //необходимо ли блоку приниать параметры
    bool list_of_args;
    //необходимо ли блоку принимать текст
    bool content;
    CreatorAbstract();
    //создаёт блок
    virtual BlockAbstract* createBlock(std::string* txt, Args* pargv);
};
#endif //TASK3_BENCH_H
