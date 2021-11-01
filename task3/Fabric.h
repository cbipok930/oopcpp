//
// Created by alex_ on 31.10.2021.
//
#pragma once
#include <string>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdarg>
#include <typeinfo>
#ifndef TASK3_FABRIC_H
#define TASK3_FABRIC_H
typedef std::list<std::string> Args;
class BlockAbstract{
public:
    std::string block_info();
    //текст, который блок хранит блок
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
    virtual BlockAbstract* createBlock(...);
};


class BlockReadFile : public BlockAbstract{
public:
    /*(*pargv) должен содержать имя файла*/
    explicit BlockReadFile(Args* pargv);
};
class CreatorReadFile : public CreatorAbstract{
public:
    CreatorReadFile();
    //необходим указатель на std::list<string>, где хранится имя файла
    BlockReadFile* createBlock(...) override;
};


class BlockSort : public BlockAbstract{
public:
    explicit BlockSort(std::string* text);
};
class CreatorSort : public CreatorAbstract{
public:
    CreatorSort();
    //необходим указатель на std::string
    BlockSort* createBlock(...) override;
};


class BlockReplace : public BlockAbstract{
public:
    BlockReplace(std::string* text, Args* pargv);
};
class CreatorReplace : public CreatorAbstract{
public:
    CreatorReplace();
    BlockReplace* createBlock(...) override;
};
#endif //TASK3_FABRIC_H
