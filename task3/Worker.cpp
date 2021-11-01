//
// Created by alex_ on 01.11.2021.
//
#include "Worker.h"
#include <algorithm>

Worker::Worker(CreatorsList *ctrs, Config *cfg) {
    this->configuration = cfg;
    this->creators = ctrs;
}

std::string Worker::produce() {
    using namespace std;
    if(this->configuration->descriptions.empty())
        throw invalid_argument("Empty configuration\n");
    DescList descs = this->configuration->descriptions;
    list<size_t> conveyor = this->configuration->id_order;
    CreatorsList ctrs = *(this->creators);
    size_t start = conveyor.front();
    auto it = find_if(descs.begin(), descs.end(), [&start] (const Description& s) {return s.id == start;});
    if (it == descs.end() || it->block != "readfile")
        throw invalid_argument("First block should be \"readfile\"\n");
    string text_content;
    for(auto cv = conveyor.begin(); cv != conveyor.end(); cv++){
        auto cv_block = find_if(descs.begin(), descs.end(), [cv] (const Description& s) {return s.id == *cv;});
        if(cv_block == descs.end())
            throw invalid_argument("No description with id " + to_string(*cv) + "\n");
        string block_string_id = cv_block->block;
        auto creator_it = find_if(ctrs.begin(), ctrs.end(), [&block_string_id] (CreatorAbstract* c) {return c->block == block_string_id;});
        if (creator_it == ctrs.end())
            throw invalid_argument("No such a block \"" + block_string_id + "\"\n");
        if((*creator_it)->list_of_args && (*creator_it)->content){
            Args args_to_block = cv_block->args;
            auto blk = (*creator_it)->createBlock(&text_content, &args_to_block);
            text_content = blk->text;
        } else if((*creator_it)->list_of_args && !(*creator_it)->content){
            Args args_to_block = cv_block->args;
            auto blk = (*creator_it)->createBlock(&args_to_block);
            text_content = blk->text;
        }
        else{
            auto blk = (*creator_it)->createBlock(&text_content);
            text_content = blk->text;
        }
    }
    return text_content;
}