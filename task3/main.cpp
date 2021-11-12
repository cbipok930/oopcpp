#include "workflow/Factory.h"
#include "workflow/benches/benches_std.h"
#include "addons/block_append.h"
int main() {
    auto cfg = new Config;
    cfg->prepareConfigData("..\\mycfg");
    CreatorsList crts;
    //быстро заполняем список необходимыми creator'ами
    for(int i = 0; i <= 6; i++){
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
            case 4:
                c = new CreatorAppend;
                break;
            case 5:
                c = new CreatorGrep;
                break;
            case 6:
                c = new CreatorDump;
                break;
        }
        crts.push_back(c);
    }
    auto wk = Factory(&crts, cfg);
    std::string  ea = wk.produce();
//    auto blk = ct.createBlock(&arguments);
//    std::string ea = blk->text;
    std::cout <<ea;
    return 0;
}
