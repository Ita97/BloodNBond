//
// Created by ita on 02/03/18.
//

#include <gtest/gtest.h>
#include "../Detective.h"
#include "../EnemyFactory.h"
class ObserverFixture : public ::testing::Test {
protected:
    Detective det;
    EnemyFactory *factory;
    std::vector<Enemy*> enemy;
    virtual void SetUp(){
        factory=new EnemyFactory(EnemyType::skeleton,level::medium,{5,10});
        for(int i=0;i<5;i++){
            enemy.push_back(factory->CreateEnemy(Behavior::berserk));
            enemy[i]->subscribe(&det);
        }
    }

};

TEST_F(ObserverFixture,StarTest){
    for(auto i:enemy){
        delete i;
    }
    ASSERT_EQ(5,det.getLevel()); //print star when level reach 5;
}