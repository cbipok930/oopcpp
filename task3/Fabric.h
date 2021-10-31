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
#ifndef TASK3_FABRIC_H
#define TASK3_FABRIC_H
typedef std::list<std::string> Args;
class BlockAbstract{
public:
    virtual std::string block_method(Args argv);
    virtual void void_block_method(Args argv);
};
class BlockReadFile : public BlockAbstract{
public:
    std::string block_method(Args argv) override;
};
class BlockWriteFile : public BlockAbstract{
public:
    void void_block_method(Args argv) override;
};
#endif //TASK3_FABRIC_H
