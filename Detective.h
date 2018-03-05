//
// Created by ita on 14/09/17.
//

#ifndef BLOODBOND_DETECTIVE_H
#define BLOODBOND_DETECTIVE_H

#include <string>
#include "Character.h"
#include "Enemy.h"
#include "Inventory.h"
#include "Medicine.h"
#include "Key.h"
#include "Message.h"
#include "Obstacle.h"
#include "Observer.h"
#include <SFML/Graphics.hpp>


class Detective: virtual public Character, virtual public Observer {
public:
    explicit Detective(const std::string &det="", int h=10, int sp=10, int x=0, int y=0, Weapon *w=nullptr);

    Detective(const Detective &original);

    Detective &operator=(const Detective &right);

    void move() override;

    void attack();

    void useInventory(sf::RenderWindow &window);

    void reload() {
        key = keyType::null;
        HP.setSize(sf::Vector2f(115*healtPoint/maxHP,HP.getSize().y));
        SP.setSize(sf::Vector2f(115*sanityPoint/maxSP,SP.getSize().y));
    }

    int getSanity() const {
        return sanityPoint;
    }

    void setSanity(int sp) {
        if(sp>0) {
            sanityPoint += sp;
            if(sanityPoint>maxSP)
                sanityPoint=maxSP;
        }
    }

    void getMad(int sp) {
        if(sp>0) {
            sanityPoint -= sp;
            if(sanityPoint<0)
                sanityPoint=0;
        }
    }

    void heal(int value){
        if(value>0) {
            healtPoint += value;
            if(healtPoint>maxHP)
                healtPoint=maxHP;
        }
    }

    void getMedicine(Medicine &med);

    void openMedikit() {
        medikit.openWindow();
        closeKeychain();
        closeNotebook();
    }

    void closeMedikit() {
        medikit.closeWindow();
    }
    Inventory<Medicine>& getMedikit(){
        return medikit;
    }

    void getMessage(Message &note);

    void openNotebook() {
        notebook.openWindow();
        closeKeychain();
        closeMedikit();
    }

    void closeNotebook() {
        notebook.closeWindow();
    }

    Inventory<Message>& getNotebook(){
        return notebook;
    }

    void getKey(Key &key);

    void openKeychain() {
        keychain.openWindow();
        closeMedikit();
        closeNotebook();
    };

    void closeKeychain() {
        keychain.closeWindow();
    }

    Inventory<Key>& getKeychain(){
        return keychain;
    }

    void useMedicine(Medicine &medication);

    void setWeapon(Weapon *weapon) {
        throwWeapon();
        this->weapon = weapon;
        sprite.setTexture(weapon->getTexture());
    }




    void Render(sf::RenderWindow &l_window) override;

    void RenderInventory(sf::RenderWindow &l_window);

    const Weapon &getWeapon() {
        return *weapon;
    }


    int getAttackPower() {
        if (weapon != nullptr)
            return weapon->getStrength();
        return 1;
    }

    sf::Vector2f getFeetPosition() override;

    void interact(Obstacle *obs);
    void reset(){
        throwWeapon();
        medikit.reset();
        keychain.reset();
        notebook.reset();
        healtPoint=maxHP;
        sanityPoint=maxSP;
    }
    void throwWeapon() {
        sprite.setTexture(texture);
        weapon= nullptr;
    }

    void update() override{
        level++;
        if(level==5){
            star1.setTexture(red_star);
            star1.setOrigin(red_star.getSize().x/2,red_star.getSize().y/2);
            star1.setScale(0.175,0.165);
        }
        else if(level==10){
            star2.setTexture(blue_star);
            star2.setOrigin(blue_star.getSize().x/2,blue_star.getSize().y/2);
            star2.setScale(0.3,0.305);
        }else if(level==20){
            star3.setTexture(yellow_star);
            star3.setOrigin(yellow_star.getSize().x/2,yellow_star.getSize().y/2);
            star3.setScale(0.16,0.159);
        }

    }
    void attach() override{}
    void detach() override{}

    int getLevel(){
        return level;
    }

private:
    int level;
    std::string name;
    int sanityPoint, maxHP, maxSP;
    int abilityPoint;
    float attackFrame;
    Inventory<Medicine> medikit;
    Inventory<Key> keychain;
    Inventory<Message> notebook;
    keyType key;
    sf::Texture state_txt,void_star,blue_star,red_star,yellow_star;
    sf::Sprite state_bar,star1,star2,star3;
    sf::RectangleShape HP,SP;
};
#endif //BLOODBOND_DETECTIVE_H
