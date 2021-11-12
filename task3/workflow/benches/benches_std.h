//
// Created by alex_ on 31.10.2021.
//
#pragma once
#ifndef TASK3_FABRIC_H
#define TASK3_FABRIC_H
#include "..\workshop\Bench.h"
class BlockReadFile : public BlockAbstract{
public:
    //pargv: указатель на список, где первый элемент это имя файла
    explicit BlockReadFile(Args* pargv);
};
class CreatorReadFile : public CreatorAbstract{
public:
    CreatorReadFile();
    //необходим указатель на std::list<string>, где хранится имя файла
    BlockReadFile* createBlock(std::string* txt, Args* pargv) override;
};


class BlockSort : public BlockAbstract{
public:
    //text: указатель
    explicit BlockSort(std::string* text);
};
class CreatorSort : public CreatorAbstract{
public:
    CreatorSort();
    //необходим указатель на std::string
    BlockSort* createBlock(std::string* txt, Args* pargv) override;
};


class BlockReplace : public BlockAbstract{
public:
    /*
     * text: указатель
     * pargv: указаетль на список с как минимум двумя параметрами*/
    BlockReplace(std::string* text, Args* pargv);
};
class CreatorReplace : public CreatorAbstract{
public:
    CreatorReplace();
    /*
     * 1 параметром необходим указатель на std::string
     * 2 параметром необходим указатель на std::list<string>
     * */
    BlockReplace* createBlock(std::string* txt, Args* pargv) override;
};


class BlockWriteFile : public BlockAbstract{
public:
    /*
     * text: указатель
     * pargv: указатель на список, где первый элемент это имя файла*/
    BlockWriteFile(std::string* text, Args* pargv);
};
class CreatorWriteFile : public CreatorAbstract{
public:
    CreatorWriteFile();
    /*
     * 1 параметром необходим указатель на std::string
     * 2 параметром необходим указатель на std::list<string>
     * */
    BlockWriteFile* createBlock(std::string* txt, Args* pargv) override;
};


class BlockGrep : public BlockAbstract{
public:
    /*
     * text: указатель
     * pargv: указатель на список, где первый элемент это нужное слово*/
    BlockGrep(std::string* text, Args* pargv);
};
class CreatorGrep : public CreatorAbstract{
public:
    CreatorGrep();
    /*
     * 1 параметром необходим указатель на std::string
     * 2 параметром необходим указатель на std::list<string>
     * */
    BlockGrep* createBlock(std::string* txt, Args* pargv) override;
};


class BlockDump : public BlockAbstract{
public:
    /*
     * text: указатель
     * pargv: указатель на список, где первый элемент это имя файла*/
    BlockDump(std::string* text, Args* pargv);
};
class CreatorDump : public CreatorAbstract{
public:
    CreatorDump();
    /*
     * 1 параметром необходим указатель на std::string
     * 2 параметром необходим указатель на std::list<string>
     * */
    BlockDump* createBlock(std::string* txt, Args* pargv) override;
};
#endif //TASK3_FABRIC_H
