//
// Created by alex_ on 02.11.2021.
//
#include "../workflow/workshop/Bench.h"
#ifndef TASK3_BLOCK_APPEND_H
#define TASK3_BLOCK_APPEND_H
class BlockAppend : public BlockAbstract{
public:
    BlockAppend(std::string* txt, Args* pargv);
};
class CreatorAppend : public CreatorAbstract{
public:
    CreatorAppend();
    BlockAppend* createBlock(std::string* txt, Args* pargv) override;
};


#endif //TASK3_BLOCK_APPEND_H
