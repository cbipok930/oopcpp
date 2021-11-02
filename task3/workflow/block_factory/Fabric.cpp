//
// Created by alex_ on 31.10.2021.
//
#include "Fabric.h"
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




BlockReadFile::BlockReadFile(Args *pargv){
    using namespace std;
    if(pargv == nullptr)
        throw std::runtime_error(this->block_info("ReadFile") + "Required parameter\n");
    Args argv = *pargv;
    string filename;
    if (!argv.empty()){
        filename = argv.front();
    }
    else
        throw std::runtime_error(this->block_info("ReadFile") + "Required parameter\n");
    ifstream infile(filename);
    if (!infile.is_open())
        throw std::runtime_error(this->block_info("ReadFile") + "Couldn't open th file \"" + filename + "\"\n");
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
BlockReadFile *CreatorReadFile::createBlock(std::string* txt, Args* pargv) {
    auto blk = new BlockReadFile(pargv);
    return blk;
}




BlockSort::BlockSort(std::string *text) {
    using namespace std;
    string text_to_sort = *text;
    stringstream ss(text_to_sort);
    vector<string> vec_lines;
    string line;
    while(getline(ss, line)){
        vec_lines.push_back(line);
    }
    std::sort(vec_lines.begin(), vec_lines.end());
    text_to_sort.clear();
    for(auto l : vec_lines){
        text_to_sort.append(l + "\n");
    }
    this->text = text_to_sort;
}
CreatorSort::CreatorSort() {
    this->content = true;
    this->list_of_args = false;
    this->block = "sort";
}
BlockSort *CreatorSort::createBlock(std::string* txt, Args* pargv) {
    auto blk = new BlockSort(txt);
    return blk;
}




BlockReplace::BlockReplace(std::string *text, Args *pargv) {
    using namespace std;
    string txt_content = *text;
    Args argv = *pargv;
    if(argv.size() < 2)
        throw invalid_argument(this->block_info("Replace") + "Two arguments expected\n");
    string w_origin = argv.front();
    argv.pop_front();
    string w_new = argv.front();
    argv.pop_front();
    while(txt_content.find(" "+w_origin+" ") !=string::npos){
        auto it = txt_content.find(" "+w_origin+" ");
        txt_content.replace(it,(" "+w_origin+" ").length(),(" "+w_new+" "));
    }
    while(txt_content.find("\n"+w_origin+" ") !=string::npos){
        auto it = txt_content.find("\n"+w_origin+" ");
        txt_content.replace(it,("\n"+w_origin+" ").length(),("\n"+w_new+" "));
    }
    while(txt_content.find(" "+w_origin+"\n") !=string::npos){
        auto it = txt_content.find(" "+w_origin+"\n");
        txt_content.replace(it,(" "+w_origin+"\n").length(),(" "+w_new+"\n"));
    }
    while(txt_content.find(" "+w_origin + *txt_content.end()) !=string::npos){
        auto it = txt_content.find(" "+w_origin+ *txt_content.end());
        txt_content.replace(it,(" "+w_origin+ *txt_content.end()).length(),(" "+w_new+ *txt_content.end()));
    }
    this->text = txt_content;
}
CreatorReplace::CreatorReplace() {
    this->list_of_args = true;
    this->content = true;
    this->block = "replace";
}
BlockReplace *CreatorReplace::createBlock(std::string* txt, Args* pargv) {
    auto blk = new BlockReplace(txt, pargv);
    return blk;
}




BlockWriteFile::BlockWriteFile(std::string *text, Args *pargv) {
    using namespace std;
    this->text = *text;
    if(pargv == nullptr)
        throw std::runtime_error(this->block_info("WriteFile") + "Required parameter\n");
    Args argv = *pargv;
    string filename;
    if (!argv.empty()){
        filename = argv.front();
    }
    else
        throw std::runtime_error(this->block_info("WriteFile") + "Required parameter\n");
    ofstream outfile(filename);
    if (!outfile.is_open())
        throw std::runtime_error(this->block_info("WriteFile") + "Couldn't open th file \"" + filename + "\"\n");
    string file_content = *text;
    outfile << file_content;
}
CreatorWriteFile::CreatorWriteFile() {
    this->list_of_args = true;
    this->content = true;
    this->block = "writefile";
}
BlockWriteFile *CreatorWriteFile::createBlock(std::string* txt, Args* pargv) {
    auto blk = new BlockWriteFile(txt, pargv);
    return blk;
}