//
// Created by alex_ on 02.11.2021.
//

#include "block_append.h"

BlockAppend::BlockAppend(std::string *txt, Args *pargv) {
    using namespace std;
    string new_text = *txt;
    Args argv = *pargv;
    if (argv.empty())
        this->text = new_text;
    else{
        bool newline = false;
        if (new_text.back() == '\n')
            newline = true;
        for(auto it = argv.begin(); it != argv.end(); it++){
            if(*it == "\\n") {
                new_text.append("\n");
                newline = true;
            }
            else{
                if(newline) {
                    new_text.append(*it);
                    newline = false;
                }
                else
                    new_text.append(" " + *it);
            }
        }
    }
    this->text = new_text;
}

CreatorAppend::CreatorAppend() {
    this->content = true;
    this->list_of_args = true;
    this->block = "append";
}

BlockAppend *CreatorAppend::createBlock(std::string* txt, Args* pargv) {
    auto blk = new BlockAppend(txt, pargv);
    return blk;
}
