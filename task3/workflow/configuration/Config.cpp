//
// Created by alex_ on 30.10.2021.
//

#include "Config.h"

Config::Config() {
    this->descriptions.clear();
    std::cout << "Config is created\n";
}

void parseArgs(ArgList &args,std::string::iterator *itp){
    std::string::iterator it = *itp;
    std::string word;
    for(; *it != 0; it++){
        if(*it == ' '){
            if(!word.empty()){
                args.push_back(word);
                word.clear();
            }
        }
        else{
            word.push_back(*it);
        }
    }
    if(!word.empty()){
        args.push_back(word);
        word.clear();
    }
}
//Заполняет поля класса Config в соответствии с данными в файле
void Config::prepareConfigData(const std::string& config_name) {
    this->id_order.clear();
    this->descriptions.clear();
    using namespace std;
    string word;
    ifstream config(config_name);
    if (!config.is_open())
        throw std::runtime_error("Couldn't open th file \"" + config_name + "\"\n");
    getline(config, word);
    if( !(word == "desc")){
        throw std::runtime_error(config_name +'\n'+"Wrong file format: \"desc\" expected\n");
    }
    word.clear();
    string line;
    size_t line_num = 2;
    /*read
     blocks*/
    while(true){
        Description dc;
        getline(config, line);
        if(line == "csed") {
            line_num++;
            break;
        }
        else if(line.empty())
            throw std::runtime_error(config_name +'\n'+ "Wrong file format: \"csed\" expected");
        string::iterator it = line.begin();
        for(int i =0; i < 3; i++){
            for(; it != line.end() && *it != 32;it++) {
                if ((*it > '9' || *it < '0') && i == 0)
                    throw std::runtime_error(config_name +'\n'+"ID should be a positive number\nline(" + to_string(line_num) + ")\n");
                else if(i == 1 && *it != '=')
                    throw std::runtime_error(config_name +'\n'+"Wrong syntax: \" = \" expected\nline(" + to_string(line_num) + ")\n");
                word.push_back(*it);
            }
            if(i < 2 && it == line.end())
                throw std::runtime_error(config_name +'\n'+"Unpredicted end of the line\nline(" + to_string(line_num)+ ")\n");
            if(i == 0)
                dc.id = stoi(word);
            else if(i == 2){
                dc.block = word;
            }
            if(*it != 0)
                it++;
            word.clear();
        }
        if (dc.block.empty())
            throw std::runtime_error(config_name +'\n'+"Block name expected\nline(" + to_string(line_num) + ")\n");
        parseArgs(dc.args, &it);
        this->descriptions.push_back(dc);
        line_num++;
    }
    /*read
     seq*/
    getline(config, line);
    if(line.empty())
        throw std::runtime_error(config_name +'\n'+"Wrong file format: sequence expected\nline(" + to_string(line_num) +")\n");
    list<size_t> sequenceIds;
    bool is_id = true;
    for(string::iterator it = line.begin(); it != line.end(); it++){
        if(is_id){
            string number;
            for(; *it != ' ' && it !=line.end(); it++) {
                if (*it > '9' || *it < '0')
                    throw std::runtime_error(
                            config_name + '\n' + "ID should be a positive number\nline(" + to_string(line_num) + ")\n");
                number.push_back(*it);
            }
            sequenceIds.push_back(stoi(number));
            is_id = false;
            if(*it == 0)
                break;
        }
        else{
            word.clear();
            for(; *it!= ' ' && it != line.end(); it++){
                word.push_back(*it);
            }
            if(word != "->")
                throw std::runtime_error(config_name +'\n'+"Wrong syntax: \" -> \" expected\nline(" + to_string(line_num) + ")\n");
            is_id = true;
            if(*it == 0)
                throw std::runtime_error(config_name +'\n'+"Wrong syntax: number at the end expected\nline(" + to_string(line_num) + ")\n");
        }
    }
    if(is_id)
        throw std::runtime_error(config_name +'\n'+"Wrong syntax: number at the end expected\nline(" + to_string(line_num) + ")\n");
    this->id_order = sequenceIds;
}
