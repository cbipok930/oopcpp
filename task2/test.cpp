#include "HashTable.h"
#include "gtest/gtest.h"
#include <random>
#define NAMES_CNT 15
Key names_dat[NAMES_CNT] = {
        "s.ivanov","a.tarasov","t.shevchenko","j.nikitina", "o.dmitrova",
        "m.evgen","r.nazarova","t.shevchenko","j.nikitina", "v.jmihenko",
        "e.kamarov", "v.pupkin", "g.bazarov", "a.dubovsky", "y.dolgorukov"
};
std::list<Key> boba = {
        "s.ivanov","a.tarasov","t.shevchenko","j.nikitina", "o.dmitrova",
        "m.evgen","r.nazarova","t.shevchenko","j.nikitina", "v.jmihenko",
        "e.kamarov", "v.pupkin", "g.bazarov", "a.dubovsky", "y.dolgorukov"
};
class CreateHT :public ::testing::Test
{
    protected:
    {
        void SetUp()
        {
            HashTable ht1(NAMES_CNT);
            for(int i = 0; i < NAMES_CNT/3; i++){
                size_t key = rand() % (NAMES_CNT  + 1);
                boba.pop_back()
            }
        }
    }
};
TEST(SingleHashtableTest, FillData){
    ASSERT_NO_THROW(HashTable ht1(NAMES_CNT));

}
int main(){
    using namespace std;
    list<Key> names_dat_list;
    for(int i = 0; i < NAMES_CNT; i++)
        names_dat_list.push_back(names_dat[i]);


    return 0;
}