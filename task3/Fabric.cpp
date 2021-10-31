//
// Created by alex_ on 31.10.2021.
//
#include "Fabric.h"

std::string BlockAbstract::block_method(Args argv) {
    return "";
}

void BlockAbstract::void_block_method(Args argv) {

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
/*параметры:
 *текст
 *имя файла */
void BlockWriteFile::void_block_method(Args argv) {

}
