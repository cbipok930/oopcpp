//
// Created by alex_ on 19.11.2021.
//

#include "View.h"

bool View::get(DatFromModel *dat) {
    boolDatFromModel* pBoolDat = (boolDatFromModel*)(*dat)[ID_GLOB_BOOL];
    if ((bool)(*pBoolDat)[ID_BOOL_KP]){
        std::cout << *(std::string*)(*dat)[ID_GLOB_KPMSG] << std::endl;
    }
    if ((bool)(*pBoolDat)[ID_BOOL_MM]){
        std::cout << (*((POINT*)(*dat)[ID_GLOB_MMMSG])).y <<" "<<
        (*((POINT*)(*dat)[ID_GLOB_MMMSG])).x<< std::endl;
    }
    return true;
}
