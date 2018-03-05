//
// Created by ita on 27/02/18.
//
#include "gtest/gtest.h"
#include "../Detective.h"

class InventoryFixture : public ::testing::Test {
protected:
    Detective det;
    Medicine *aspirin;
    Key *copperKey;
    virtual void SetUp(){
        aspirin=new Medicine(10,medType::sp);
        copperKey=new Key(keyType::copper);
    }

};

TEST_F(InventoryFixture,Inclusion){
    det.getMedicine(*aspirin);
    det.getKey(*copperKey);
    ASSERT_EQ(1,det.getMedikit().getSize());
    ASSERT_EQ(1,det.getKeychain().getSize());
}

TEST_F(InventoryFixture,MedicineEffect){
    det.getMad(5);
    det.useMedicine(*aspirin);
    ASSERT_EQ(10,det.getSanity());
}