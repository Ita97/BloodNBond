#include <SFML/Graphics.hpp>
#include "Window.h"
#include "Game.h"
#include <time.h>

#include <iostream>
#include "Medicine.h"
#include "Character.h"
#include "Detective.h"
#include "Enemy.h"


int main() {
    int x = 785, y = 105;
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
    sf::RectangleShape rectangle(sf::Vector2f(120, 40));
    rectangle.setFillColor(sf::Color::Blue);
    rectangle.setPosition(1, 1);
    Enemy dragon(5,x,y, nullptr);
    Detective jack(10,0,0,nullptr,"jack",10,10);
    while (!window.IsDone()){
    window.Update();


    sf::Clock clock;
    float timer=0;



        float time = clock.getElapsedTime().asSeconds(); //time flowing
        clock.restart();
        timer+=time;

        window.BeginDraw();
        window.Draw(rectangle);
        /*sf::Texture t_enemy;
        t_enemy.loadFromFile("/home/ita/CLionProjects/BloodBond/pic/dragon.png");
        sf::Sprite enemy;
        enemy.setTexture(t_enemy);
        enemy.setPosition(x,y);
        enemy.setTextureRect(sf::IntRect(190,250,190,150));
        window.Draw(enemy);*/
        //enemy movement



        dragon.move();
        jack.move();
        jack.Render(window);
        dragon.Render(window);
        window.EndDraw();
    }



    Medicine aspirin(0,5);
    if(aspirin.isPsichic())
        std::cout<<"Aspirin is a psichic medicinal"<<std::endl;
    jack.use(aspirin);
    std::cout<<jack.getSanity()<<std::endl;
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