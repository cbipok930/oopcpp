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
class Hashtable_FillData: public ::testing::Test{
public:
    Datalist kv_FillData;
    size_t size_FillData = FILL_AMOUNT;
    HashTable *ht;
private:
    void SetUp() override {
        using namespace std;
        ht = new HashTable(1);
        for (int i = 0; i < FILL_AMOUNT; i++) {
            Key key_ = names_dat[i];
            ListContent kv;
            kv.first = key_;
            kv.second = {(unsigned int)((abs(rand()) + 18) % 31), (unsigned int)((abs(rand()) + 50) % 150)};
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

TEST_F(HashTable_CreateHT, HTprops){
    for(int i = 0; i < 5; i++){
       EXPECT_TRUE(ht->insert(names_dat[i], {unsigned(rand() % 150 + 40) , unsigned(rand() % 150 + 40)}));
    }
    EXPECT_TRUE(ht->size() == 5);
    EXPECT_TRUE(ht->size_max() > ht->size());
}

TEST_F(HashTable_CreateHT, HTaddData){
    ht->insert("first", {10, 10});
    ht->insert("second", {23, 17});
    Value sec = ht->at("second");
    EXPECT_EQ(sec.age, 23);
    EXPECT_EQ(sec.weight, 17);
    Value fst = (*ht)["first"];
    EXPECT_EQ(fst.age, fst.weight);
    Value thd = (*ht)["third"];
    EXPECT_TRUE(ht->size() == 3);
}

TEST_F(Hashtable_FillData, ClearHT){
    EXPECT_FALSE(ht->empty());
    ht->clear();
    EXPECT_TRUE(ht->empty());
    Datalist content;
    ht->get_contents(content);
    EXPECT_TRUE(content.empty());
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
TEST_F(Hashtable_FillData, 2HT_test){
    HashTable b = *ht;
    for (int i = 0; i < 4; i++)
        EXPECT_TRUE(b.erase(names_dat[i]));
    EXPECT_FALSE(b.erase("that_key_not_belong"));
    EXPECT_TRUE(b.insert("test_key", {45, 78}));
    EXPECT_TRUE(b != (*ht));
    ht->swap(b);
    EXPECT_TRUE(ht->contains("test_key"));
    EXPECT_GT(b.size(), ht->size());
}
int main(int argc, char** argv){
    testing::InitGoogleTest(&argc, argv);
//    using namespace std;
//    list<Key> names_dat_list;
//    for(int i = 0; i < NAMES_CNT; i++)
//        names_dat_list.push_back(names_dat[i]);

    return RUN_ALL_TESTS();
}