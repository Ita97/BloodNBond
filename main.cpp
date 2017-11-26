
#include <SFML/Graphics.hpp>
#include "Window.h"
#include "Game.h"
#include <ctime>
#include <sstream>
#include <string>

#include <iostream>
#include "Medicine.h"
#include "Character.h"
#include "Detective.h"
#include "Enemy.h"
#include "Weapon.h"
#include "ColdWeapon.h"
#include "FireWeapon.h"

template <typename T>
std::string toString(T arg){
    std::stringstream ss;
    ss << arg;
    return ss.str();
}



int main() {
    int x = 880, y = 205;
    unsigned int w =960 ;
    unsigned int h =480;
    /*Game game;
    while(game.GetWindow()->IsDone()){
        game.HandelInput();
        game.Update();
        game.Render();
    }
    */
    Window window("Enemy move",sf::Vector2u(w,h));
    sf::Font msg, old;
    msg.loadFromFile("/home/ita/CLionProjects/BloodBond/Font/BeautyDemo.ttf");
    old.loadFromFile("/home/ita/CLionProjects/BloodBond/Font/1942.ttf");
    sf::Text status("Enemy HP:",old,25), hp("",old,20);
    hp.setPosition(151,7);
    status.setPosition(7,2);
    status.setFillColor(sf::Color::Black);
    status.setCharacterSize(25);

    sf::RectangleShape rectangle(sf::Vector2f(220, 40));
    rectangle.setFillColor(sf::Color::Red);
    rectangle.setPosition(1, 1);
    Weapon* magnum;
    magnum=new ColdWeapon(coldWeaponType::axe);
    Enemy dragon(10000,x,y, 80, nullptr, EnemyType::dragon);
    Detective jack("Jack",10,10,10,480,240,magnum); //(name, hp, sp, ability, x, y, weapon)

    while (!window.IsDone()){
    window.Update();


    sf::Clock clock;
    float timer=0;



        float time = clock.getElapsedTime().asSeconds(); //time flowing
        clock.restart();
        timer+=time;

        window.BeginDraw();

    // movement
        dragon.move();
        jack.move();
        jack.attack(dragon);
        window.Draw(rectangle);
        window.Draw(status);
        hp.setString(toString<int>(dragon.getHp()));
        window.Draw(hp);
       // magnum->Render(window);
        if(jack.getPosY()<dragon.getPosY()){
            jack.Render(window);
            dragon.Render(window);
        } else {
            dragon.Render(window);
            jack.Render(window);
        }

        window.EndDraw();
    }

    return 0;
}
/*sf::RenderWindow window(sf::VideoMode(w,h), "enemy move!");
    window.setVerticalSyncEnabled(true);

    sf::Texture t_ShortGrass,t_Alleyway,t_Mountain,t_MediumGrass,t_bonfire;

    //load images

    t_ShortGrass.loadFromFile("/home/ita/CLionProjects/BloodBond/sprite/ShortGrass");
    t_Alleyway.loadFromFile("/home/ita/CLionProjects/BloodBond/sprite/alleyway");
    t_Mountain.loadFromFile("/home/ita/CLionProjects/BloodBond/sprite/mountain1");
    t_MediumGrass.loadFromFile("/home/ita/CLionProjects/BloodBond/sprite/MediumGrass");
    t_bonfire.loadFromFile("/home/ita/CLionProjects/BloodBond/sprite/bonfire");


    sf::Sprite ShortGrass(t_ShortGrass),Alleyway(t_Alleyway),Mountain(t_Mountain),MediumGrass(t_MediumGrass),bonfire(t_bonfire);



    sf::Clock clock;
    float timer=0;


    while(window.isOpen()){
        sf::Event event;
        float time = clock.getElapsedTime().asSeconds(); //time flowing
        clock.restart();
        timer+=time;

        while(window.pollEvent(event)){
            if(event.type==sf::Event::Closed)
                window.close();
        }

        //enemy movement
       Enemy dragon(5,x,y, nullptr);

        window.clear();

        //background
        for (int i=0; i<25; i++)
            for (int j=0; j<10; j++) {
                ShortGrass.setPosition(i*t_ShortGrass.getSize().x, j*t_ShortGrass.getSize().y);
                window.draw(ShortGrass);
            }


        for (int i=0; i<25; i++)
            for (int j=0; j<10; j++) {
                MediumGrass.setPosition(i*t_MediumGrass.getSize().x, j*t_MediumGrass.getSize().y);
                window.draw(MediumGrass);
            }



        for (int i=0,j=2; i<35; i++) {
            Alleyway.setPosition(i * t_Alleyway.getSize().x, j * t_Alleyway.getSize().y);
            window.draw(Alleyway);
        }

        Mountain.setPosition(static_cast<float>(4.2 * t_Mountain.getSize().x),
                             static_cast<float>(0.5 * t_Mountain.getSize().y));
        window.draw(Mountain);


        for (int i=0; i<18; i++) {
            bonfire.setPosition(i*t_ShortGrass.getSize().x, static_cast<float>(0.6 * t_Mountain.getSize().y));
            window.draw(bonfire);
        }
        for (int i=0; i<18; i++) {
            bonfire.setPosition(i*t_ShortGrass.getSize().x, static_cast<float>(1.1 * t_Mountain.getSize().y));
            window.draw(bonfire);
        }
        //dragon.move(dragon.getPosX(), dragon.getPosY());
        //window.draw(dragon.getSprite());
        window.display();
    }*/