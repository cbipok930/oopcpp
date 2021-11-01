//
// Created by alex_ on 01.11.2021.
//
#ifndef TASK3_WORKER_H
#define TASK3_WORKER_H
#pragma once
#include "Fabric.h"
#include "Config.h"
typedef std::list<CreatorAbstract*> CreatorsList;
class Worker{
public:
    CreatorsList* creators;
    Config* configuration;
    Worker(CreatorsList* ctrs, Config* cfg);
    std::string produce();
};
#endif //TASK3_WORKER_H
