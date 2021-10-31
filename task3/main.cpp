#include "Config.h"
#include "Fabric.h"
int main() {
    auto cfg = new Config;
    cfg->prepareConfigData("..\\mycfg");
    std::cout << "Hello, World!" << std::endl;
    std::list<std::string> arguments;
    arguments.emplace_back("..\\mycfg");
    auto ct = CreatorReadFile();
    auto blk = ct.createBlock("", arguments);
    std::string ea = blk->text;
    std::cout <<ea;
    return 0;
}
