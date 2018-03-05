//
// Created by ita on 27/02/18.
//
#include "gtest/gtest.h"
#include "../Detective.h"

TEST(Detective, DefaultConstructor) {
    Detective det;
    ASSERT_EQ(0,det.getPosX());
    ASSERT_EQ(10,det.getHp());
    ASSERT_EQ(10,det.getSanity());
}

TEST(Detective,DamageHealHP){
    Detective det;
    det.damage(4);
    det.heal(2);
    ASSERT_EQ(8,det.getHp());
}

TEST(Detective, HealMaxHP){
    Detective det;
    det.heal(20);
    ASSERT_EQ(10,det.getHp());
}

TEST(Detective, DeadCase){
    Detective det;
    det.damage(20);
    ASSERT_EQ(0,det.getHp());
}
