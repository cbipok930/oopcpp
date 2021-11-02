//
// Created by alex_ on 02.11.2021.
//

#include "block_append.h"

BlockAppend::BlockAppend(std::string *txt, Args *pargv) {

}

CreatorAppend::CreatorAppend() {
    this->content = true;
    this->list_of_args = true;
    this->block = "append";
}

BlockAppend *CreatorAppend::createBlock(...) {
    va_list params;
    va_start(params, list_of_args);
    std::string* txt = va_arg(params, std::string*);
    Args *pargv = va_arg(params, Args*);
    auto blk = new BlockAppend(txt, pargv);
    return blk;
}
