//
// Created by alex_ on 31.10.2021.
//
#include "Fabric.h"
CreatorAbstract::CreatorAbstract() {
    this->block = "";
    this->list_of_args = false;
    this->content = false;
}
BlockAbstract *CreatorAbstract::createBlock(...) {
    auto blk = new BlockAbstract();
    return blk;
}
std::string BlockAbstract::block_info() {
    using namespace std;
    const void * address = static_cast<const void*>(this);
    std::stringstream ss;
    ss << address;
    string block_inf = "BlockReadFile " + ss.str() + '\n';
    return block_inf;
}


BlockReadFile::BlockReadFile(Args *pargv){
    using namespace std;
    if(pargv == nullptr)
        throw std::runtime_error(this->block_info() + "Required parameter\n");
    Args argv = *pargv;
    string filename;
//    stringstream arguments(argv);
//    arguments >> filename;
    if (!argv.empty()){
        filename = argv.front();
    }
    else
        throw std::runtime_error(this->block_info() + "Required parameter\n");
    ifstream infile(filename);
    if (!infile.is_open())
        throw std::runtime_error(this->block_info() + "Couldn't open th file \"" + filename + "\"\n");
    string file_content;
    string buffer;
    getline(infile, buffer);
    while (infile){
        file_content.append(buffer + "\n");
        getline(infile, buffer);
    }
    this->text = file_content;
}
CreatorReadFile::CreatorReadFile() {
    this->content = false;
    this->list_of_args = true;
    this->block = "readfile";
}
BlockReadFile *CreatorReadFile::createBlock(...) {
    va_list params;
    va_start(params, this->list_of_args);
    Args* plist = va_arg(params, Args*);
    auto blk = new BlockReadFile(plist);
    return blk;
}

//делать
BlockSort::BlockSort(std::string *text) {
    std::string text_to_sort = *text;
    this->text = text_to_sort;
}
CreatorSort::CreatorSort() {
    this->content = true;
    this->list_of_args = false;
    this->block = "sort";
}
BlockSort *CreatorSort::createBlock(...) {
    va_list params;
    va_start(params, this->list_of_args);
    std::string* pst = va_arg(params, std::string*);
    auto blk = new BlockSort(pst);
    return blk;
}

//делать
BlockReplace::BlockReplace(std::string *text, Args *pargv) {
    using namespace std;
    string txt_content = *text;
    Args argv = *pargv;
    if(argv.size() < 2)
        throw invalid_argument(this->block_info() + "Two arguments expected\n");

    this->text = txt_content;
}
CreatorReplace::CreatorReplace() {
    this->list_of_args = true;
    this->content = true;
    this->block = "replace";
}
BlockReplace *CreatorReplace::createBlock(...) {
    va_list params;
    va_start(params, this->list_of_args);
    std::string * pst = va_arg(params, std::string*);
    Args * pargv = va_arg(params, Args*);
    auto blk = new BlockReplace(pst, pargv);
    return blk;
}

