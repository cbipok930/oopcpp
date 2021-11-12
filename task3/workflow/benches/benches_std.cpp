//
// Created by alex_ on 31.10.2021.
//
#include "benches_std.h"
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
    for(int i = 0; i <=6; i++){
        pair<string, string> edges;
        switch (i){
            default:
                edges = {" ", " "};
                break;
            case 1:
                edges = {"\n"," "};
                break;
            case 2:
                edges = {" ", "\n"};
                break;
            case 3:
                edges = {"\t"," "};
                break;
            case 4:
                edges = {" ", "\t"};
                break;
            case 5:
                edges = {"\n", "\t"};
                break;
            case 6:
                edges = {"\t", "\n"};
                break;
        }
        while(txt_content.find(edges.first+w_origin+edges.second) !=string::npos){
            auto it = txt_content.find(edges.first+w_origin+edges.second);
            txt_content.replace(it,(edges.first+w_origin+edges.second).length(),(edges.first+w_new+edges.second));
        }
    }
    for(int i =0; i <= 2; i++){
        string edge;
        switch (i){
            default:
                edge = " ";
                break;
            case 1:
                edge = "\n";
                break;
            case 2:
                edge = "\t";
                break;
        }
        while(txt_content.find(edge+w_origin + *txt_content.end()) !=string::npos){
            auto it = txt_content.find(edge+w_origin+ *txt_content.end());
            txt_content.replace(it,(edge+w_origin+ *txt_content.end()).length(),(edge+w_new+ *txt_content.end()));
        }
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




BlockGrep::BlockGrep(std::string *text, Args *pargv) {
    using namespace std;
    string txt_content = *text;
    string new_txt;
    Args argv = *pargv;
    if(argv.empty())
        throw invalid_argument(this->block_info("Grep") + "One argument is expected\n");
    string w_origin = argv.front();
    stringstream ss(txt_content);
    string line;
    while(getline(ss, line)){
        line.append("\n");
        line.insert(0, "\n");
        bool is_find = false;
        while(line.find(" "+w_origin+" ") !=string::npos){
            is_find = true;
            new_txt.append(line.erase(0, 1));
            break;
        }
        if(!is_find){
            while(line.find("\n"+w_origin+" ") !=string::npos){
                is_find = true;
                new_txt.append(line.erase(0, 1));
                break;
            }
            if(!is_find){
                while(line.find(" "+w_origin+"\n") !=string::npos) {
                    is_find = true;
                    new_txt.append(line.erase(0, 1));
                    break;
                }
                if(!is_find){
                    while(line.find(" "+w_origin + *txt_content.end()) !=string::npos){
                        is_find = true;
                        new_txt.append(line.erase(0, 1));
                    }
                }
            }
        }
    }
    this->text = new_txt;
}
CreatorGrep::CreatorGrep() {
    list_of_args = true;
    content = true;
    block = "grep";
}
BlockGrep *CreatorGrep::createBlock(std::string *txt, Args *pargv) {
    auto blk = new BlockGrep(txt, pargv);
    return blk;
}




BlockDump::BlockDump(std::string *text, Args *pargv) {
    auto blk = new BlockWriteFile(text, pargv);
    this->text = blk->text;
    delete blk;
}
CreatorDump::CreatorDump() {
    list_of_args = true;
    content = true;
    block = "dump";
}
BlockDump *CreatorDump::createBlock(std::string *txt, Args *pargv) {
    auto blk = new BlockDump(txt, pargv);
    return blk;
}
