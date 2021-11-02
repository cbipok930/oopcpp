#include "Worker.h"
int main() {
    auto cfg = new Config;
    cfg->prepareConfigData("..\\mycfg");
    CreatorsList crts;
    for(int i = 0; i <= 3; i++){
        CreatorAbstract *c;
        int k = i;
        switch(k)
        {
            default:
                c = new CreatorReadFile;
                break;
            case 1:
                c = new CreatorSort;
                break;
            case 2:
                c = new CreatorReplace;
                break;
            case 3:
                c = new CreatorWriteFile;
                break;
        }
        crts.push_back(c);
    }
    auto wk = Worker(&crts, cfg);
    std::string  ea = wk.produce();
//    auto blk = ct.createBlock(&arguments);
//    std::string ea = blk->text;
    std::cout <<ea;
    return 0;
}
