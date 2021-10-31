//
// Created by alex_ on 31.10.2021.
//
#include "Fabric.h"

#include <utility>

std::string BlockAbstract::block_method(Args argv) {
    return "";
}

void BlockAbstract::void_block_method(Args argv) {

}

BlockAbstract *CreatorAbstract::createBlock(std::string text, Args argv) {
    auto blk = new BlockAbstract();
    return blk;
}

std::string BlockReadFile::block_method(Args argv) {
    using namespace std;
    const void * address = static_cast<const void*>(this);
    std::stringstream ss;
    ss << address;
    string block_inf = "BlockReadFile " + ss.str() + '\n';
    string filename;
//    stringstream arguments(argv);
//    arguments >> filename;
    if (!argv.empty()){
        filename = argv.front();
    }
    else
        throw std::runtime_error(block_inf + "Required parameter\n");
    ifstream infile(filename);
    if (!infile.is_open())
        throw std::runtime_error(block_inf + "Couldn't open th file \"" + filename + "\"\n");
    string file_content;
    string buffer;
    getline(infile, buffer);
    while (infile){
        file_content.append(buffer + "\n");
        getline(infile, buffer);
    }
    return file_content;
}

BlockReadFile::BlockReadFile(Args *argvp){
    Args argv = *argvp;
    using namespace std;
    const void * address = static_cast<const void*>(this);
    std::stringstream ss;
    ss << address;
    string block_inf = "BlockReadFile " + ss.str() + '\n';
    string filename;
//    stringstream arguments(argv);
//    arguments >> filename;
    if (!argv.empty()){
        filename = argv.front();
    }
    else
        throw std::runtime_error(block_inf + "Required parameter\n");
    ifstream infile(filename);
    if (!infile.is_open())
        throw std::runtime_error(block_inf + "Couldn't open th file \"" + filename + "\"\n");
    string file_content;
    string buffer;
    getline(infile, buffer);
    while (infile){
        file_content.append(buffer + "\n");
        getline(infile, buffer);
    }
    this->text = file_content;
}
BlockReadFile *CreatorReadFile::createBlock(std::string text, Args argv) {
    Args argv_to_block = std::move(argv);
    auto blk = new BlockReadFile(&argv_to_block);
    return blk;
}

/*параметры:
 *текст
 *имя файла */
void BlockWriteFile::void_block_method(Args argv) {

}

