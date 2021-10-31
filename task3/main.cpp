#include "Config.h"
#include "Fabric.h"
int main() {
    auto cfg = new Config;
    cfg->prepareConfigData("..\\mycfg");
    std::cout << "Hello, World!" << std::endl;
    auto blk = new BlockReadFile;
    std::list<std::string> arguments;
    arguments.emplace_back("..\\mycfg");
    std::string ea = blk->block_method(arguments);
    std::cout <<ea;
    return 0;
}
