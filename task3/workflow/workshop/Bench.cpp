//
// Created by alex_ on 12.11.2021.
//
#include "Bench.h"
CreatorAbstract::CreatorAbstract() {
    this->block = "";
    this->list_of_args = false;
    this->content = false;
}
BlockAbstract *CreatorAbstract::createBlock(std::string* txt, Args* pargv) {
    auto blk = new BlockAbstract();
    return blk;
}
std::string BlockAbstract::block_info(std::string str) {
    using namespace std;
    const void * address = static_cast<const void*>(this);
    std::stringstream ss;
    ss << address;
    string block_inf = str + " " + ss.str() + '\n';
    return block_inf;
}