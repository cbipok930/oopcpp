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
bool is_number(std::string* pstr){
    for(char & it : *pstr) {
        if (it > '9' || it < '0')
            return false;
    }
    return true;
}
//Заполняет поля класса Config в соответствии с данными в файле
void Config::prepareConfigData(const std::string& config_name) {
    this->id_order.clear();
    this->descriptions.clear();
    using namespace std;
    string word;
    ifstream config(config_name);
    if (!config.is_open())
        throw runtime_error("Couldn't open th file \"" + config_name + "\"\n");
    getline(config, word);
    if( !(word == "desc")){
        throw runtime_error(config_name +'\n'+"Wrong file format: \"desc\" expected\n");
    }
    word.clear();
    string line;
    size_t line_num = 2;
    /*read decls*/
    while(true){
        Description dc;
        getline(config, line);
        if(line == "csed") {
            line_num++;
            break;
        }
        else if(line.empty())
            throw runtime_error(config_name +'\n'+ "Wrong file format: \"csed\" expected");
        string::iterator it = line.begin();
        stringstream ss(line);
        vector<string> words_line;
        while (getline(ss, word, ' ')){
            words_line.push_back(word);
        }
        if (words_line.size() < 3)
            throw runtime_error
            (config_name +'\n'+"Unpredicted end of the line\nline(" + to_string(line_num)+ ")\n");
        for(int i = 0; i < words_line.size(); i++){
            if (i == 0) {
                if (is_number(&words_line[i]))
                    dc.id = stoi(words_line[i]);
                else
                    throw runtime_error(
                            config_name + '\n' + "ID should be a positive number\nline(" + to_string(line_num) + ")\n");
            }else
            if (i == 1){
                if (words_line[i] != "=")
                    throw std::runtime_error
                    (config_name +'\n'+"Wrong syntax: \" = \" expected\nline(" + to_string(line_num) + ")\n");
            } else
            if (i == 2)
                dc.block = words_line[i];
            else
                dc.args.push_back(words_line[i]);

        }
        this->descriptions.push_back(dc);
        line_num++;
    }
    /*read seq*/
    getline(config, line);
    if(line.empty())
        throw std::runtime_error(config_name +'\n'+"Wrong file format: sequence expected\nline(" + to_string(line_num) +")\n");
    list<size_t> sequenceIds;
    bool is_id = true;
    stringstream ss(line);
    vector<string> words_line;
    word.clear();
    while (getline(ss, word, ' '))
        words_line.push_back(word);
    for(int i =0; i < words_line.size(); i++){
        if(i % 2 == 0){
            if (is_number(&words_line[i]))
                sequenceIds.push_back(stoi(words_line[i]));
            else
                throw runtime_error(
                        config_name + '\n' + "ID should be a positive number\nline(" + to_string(line_num) + ")\n");
        }
        else{
            if(words_line[i] != "->")
                throw runtime_error
                (config_name +'\n'+"Wrong syntax: \" -> \" expected\nline(" + to_string(line_num) + ")\n");
            else{
                if (words_line.size() == i + 1)
                    throw runtime_error
                    (config_name +'\n'+"Wrong syntax: number at the end expected\nline(" + to_string(line_num) + ")\n");
                else
                    continue;
            }
        }
    }
    this->id_order = sequenceIds;
}
