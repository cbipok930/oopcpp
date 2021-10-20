#include "HashTable.h"
#include "gtest/gtest.h"
#include <random>
#include <algorithm>
#define NAMES_CNT 36
#define FILL_AMOUNT 10
Key names_dat[NAMES_CNT] = {
        "s.ivanov","a.tarasov","t.shevchenko","j.nikitina", "o.dmitrova",
        "m.evgen","r.nazarova","e.krid","e.panasenkoff", "v.jmihenko",
        "e.kamarov", "v.pupkin", "e.bazarov", "a.dubrovsky", "y.dolgorukov",
        "j.stathem", "d.jhonson", "o.kirjalov", "v.neumann", "t.klass",
        "t.kartoshkin", "r.medvedev", "i.musk", "g.rasputin", "n.romanov",
        "a.kutalev", "j.dark", "a.kristi", "r.raskolnikoff", "a.mozart",
        "g.kobyakov", "i.bach", "l.beethoven", "a.aboba", "g.richy",
        "d.vilyov"
};
//Пустая таблица с вместимостью 1
class HashTable_CreateHT :public ::testing::Test
{
public:
    HashTable *ht;
private:
    void SetUp() override
    {
        ht = new HashTable(1);

    }
    void TearDown() override{
        delete ht;
    }
};
//Случайно заполняет таблицу FILL_AMOUNT ключами, удаляет их из глобального списка
class Hashtable_FillData: public HashTable_CreateHT{
public:
    Datalist kv_FillData;
    size_t size_FillData = FILL_AMOUNT;
private:
    void SetUp() override {
        using namespace std;
        ht = new HashTable(1);
        for (int i = 0; i < FILL_AMOUNT; i++) {
            Key key_ = names_dat[i];
            ListContent kv;
            kv.first = key_;
            kv.second = {size_t((abs(rand()) + 18) % 31), size_t((abs(rand()) + 50) % 150)};
            bool suc = ht->insert(kv.first, kv.second);
            EXPECT_EQ(true, suc);
            kv_FillData.push_back(ListContent(kv));
        }
    }
    void TearDown() override{
        kv_FillData.clear();
    };
};

TEST_F(HashTable_CreateHT, EmptyHT){
    EXPECT_EQ(1, ht->size_max());
    EXPECT_EQ(0, ht->size());
    EXPECT_TRUE(ht->empty());
    Datalist val_list;
    ht->get_contents(val_list);
    EXPECT_EQ(0, val_list.size());
}

TEST_F(Hashtable_FillData, ComapreEqHTs){
    HashTable ht1 = *ht;
    HashTable ht2 = *ht;
    EXPECT_EQ(true, (ht2 == ht1));
    EXPECT_EQ(false, (ht2 != ht1));
    bool suc = ht1.insert("qwerty", {5,2});
    EXPECT_EQ(true, suc);
    EXPECT_EQ(true, (ht2 != ht1));
    EXPECT_NE(ht2.size(), ht1.size());
}

TEST_F(Hashtable_FillData, CheckHT_LoadFactor){
    size_t size_ = ht->size();
    size_t cap_ = ht->size_max();
    EXPECT_GT(LOAD_FACTOR, double(size_)/double(cap_));
}

TEST_F(Hashtable_FillData, CheckHT_content){
    EXPECT_EQ(size_FillData, ht->size());
    EXPECT_EQ(ht->size(), kv_FillData.size());
    for(const auto& it : kv_FillData){
        EXPECT_TRUE(ht->contains(it.first));
    }
}
int main(int argc, char** argv){
    testing::InitGoogleTest(&argc, argv);
//    using namespace std;
//    list<Key> names_dat_list;
//    for(int i = 0; i < NAMES_CNT; i++)
//        names_dat_list.push_back(names_dat[i]);


    return RUN_ALL_TESTS();
}