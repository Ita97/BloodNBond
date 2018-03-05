//
// Created by ita on 27/02/18.
//
#include <gtest/gtest.h>
#include "../Detective.h"
#include "../FireWeapon.h"
#include "../EnemyFactory.h"
class RangeAttackFixture : public ::testing::Test {
protected:
    Detective det;
    Weapon *gun;
    EnemyFactory *factory;
    Enemy *enemy;
    virtual void SetUp(){
        gun=new FireWeapon(fireWeaponType::gun);
        factory=new EnemyFactory(EnemyType::skeleton,level::medium,{5,10});
        enemy=factory->CreateEnemy(Behavior::berserk);
        det.setWeapon(gun);
    }

};

TEST_F(RangeAttackFixture,HitTest){
    int i=0;
    det.useWeapon()->startAttack({15,10},3);
    while(i<100){
        det.useWeapon()->use();
        if(det.ready()){
            if(det.useWeapon()->checkCollision(enemy->getPosition(),enemy->getCollisionArea(),det.getAttackPosition(),det.getAttackRange())){
                enemy->damage(det.getAttackPower());
                det.hit();
            }
        }
        i++;
    }
    ASSERT_EQ(20,enemy->getHp());
}
