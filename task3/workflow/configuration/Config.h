//
// Created by alex_ on 30.10.2021.
//
#ifndef TASK3_CONFIG_H
#define TASK3_CONFIG_H
#pragma once
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <iostream>
#include <sstream>
struct Description;
typedef std::list<std::string> ArgList;
typedef std::string String;
typedef std::list<Description> DescList;
struct Description{
    size_t id;
    String block;
    ArgList args;
};

class Config{
public:
    DescList descriptions;
    std::list<size_t> id_order;
    Config();
    void prepareConfigData(const std::string& config_name);
};
#endif //TASK3_CONFIG_H
