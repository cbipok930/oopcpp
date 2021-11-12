//
// Created by alex_ on 01.11.2021.
//
#ifndef TASK3_FACTORY_H
#define TASK3_FACTORY_H
#pragma once
#include "workshop/Bench.h"
#include "configuration/Config.h"
typedef std::list<CreatorAbstract*> CreatorsList;
class Factory{
public:
    CreatorsList* creators;
    Config* configuration;
    Factory(CreatorsList* ctrs, Config* cfg);
    std::string produce();
};
#endif //TASK3_FACTORY_H
