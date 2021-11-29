//
// Created by alex_ on 19.11.2021.
//

#include "View.h"
bool View::get(DataModel *dat) {
    if(dat->keyPressed){
        std::cout << dat->msg << std::endl;
    }
    if(dat->updateCords){
        std::cout << dat->mouseCords.x << " " << dat->mouseCords.y << std::endl;
    }
    return true;
}
