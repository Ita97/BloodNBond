//
// Created by ita on 30/08/17.
//

#include "Game.h"
#include "FireWeapon.h"
#include "ColdWeapon.h"

Game::Game():window("Blood&Bond", sf::Vector2u(960,480)),jack("Jack",10,10,10,480,240, nullptr),detStatus("Jack HP:",old,25),
enemyStatus("Dragon HP: ",old,25),map(MapType::courtyard,4,3){


    msg.loadFromFile("/home/ita/CLionProjects/BloodBond/Font/BeautyDemo.ttf");
    old.loadFromFile("/home/ita/CLionProjects/BloodBond/Font/1942.ttf");

    detStatus.setPosition(7,2);
    detStatus.setFillColor(sf::Color::Black);
    detStatus.setCharacterSize(25);
    enemyStatus.setPosition(7,33);
    enemyStatus.setFillColor(sf::Color::Black);
    enemyStatus.setCharacterSize(25);



}

void Game::gameLoop() {
    GameStart();

    sf::RectangleShape rectangle(sf::Vector2f(220, 70));
    rectangle.setFillColor(sf::Color::Red);
    rectangle.setPosition(1, 1);
    map.create(sf::Vector2f(480,240));

    Medicine *potion, *aspirin;
    potion= new Medicine(7,medType::sp);
    aspirin= new Medicine(3, medType::hp);
    Key* CopperKey;
    CopperKey=new Key(keyType::copper);
    Message* clue;
    clue= new Message();
    std::string content="The answer is \ninside your heArt";
    clue->setContent(content);
    Weapon *magnum, *ritualKnife;
    magnum=new FireWeapon(fireWeaponType::gun);
    ritualKnife= new ColdWeapon(coldWeaponType::sword);
    enemy=new Enemy(50,880,205, 80, nullptr, EnemyType::dragon);
    enemyFolder.push_back(enemy);
    jack.setWeapon(magnum);
    jack.getMedicine(*potion);
    jack.getMedicine(*aspirin);
    jack.getKey(*CopperKey);
    jack.getMessage(*clue);
    while (!window.IsDone()){
        window.Update();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
            jack.throwWeapon();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
            jack.setWeapon(ritualKnife);

        jack.use(window);


        // movement
        window.BeginDraw();
        map.Render(window);

        jack.move();
        jack.attack();

        auto pos=enemyFolder.cbegin();
        for(auto i: enemyFolder) {
            //check if detective attack works
            if(jack.isFighting()&&!i->isHitten()){
                if(checkCollision(i->getPosition(),i->getCollisionArea(),jack.getAttackPosition(),jack.getAttackRange())){
                    i->damage(jack.getAttackPower());
                    i->isHitten()=true;
                }
            }
            else if(!jack.isFighting())
                    i->isHitten()=false;


            i->move(jack);//se lo vede fai una cosa, altrimenti continua a fare quello che stavi facendo
            i->attack();
            i->Render(window);
            if(i->getHp()<=0)
                enemyFolder.erase(pos);

            pos++;
        }
        gameBound();

        detStatus.setString("Jack HP: "+toString<int>(jack.getHp()));
        enemyStatus.setString("Enemy HP: "+toString<int>(enemy->getHp()));
        jack.Render(window);
        window.Draw(rectangle);
        window.Draw(enemyStatus);
        window.Draw(detStatus);
        jack.RenderInventory(window);
        window.EndDraw();
    }
}

void Game::GameStart(){
    //screen home
}

void Game::gameBound() {
    //detective
    if(jack.getPosition().x-jack.getCollisionArea().x/2<=map.getPosition().x-map.getSize().x/2)
        jack.setPosX(map.getPosition().x-map.getSize().x/2+jack.getCollisionArea().x/2);

    if(jack.getPosition().x+jack.getCollisionArea().x/2>=map.getPosition().x+map.getSize().x/2)
        jack.setPosX(map.getPosition().x+map.getSize().x/2-jack.getCollisionArea().x/2);

    if(jack.getPosition().y-jack.getCollisionArea().y/2<=map.getPosition().y-map.getSize().y/2)
        jack.setPosY(map.getPosition().y-map.getSize().y/2+jack.getCollisionArea().y/2);

    if(jack.getPosition().y+jack.getCollisionArea().y>=map.getPosition().y+map.getSize().y/2)
        jack.setPosY(map.getPosition().y+map.getSize().y/2-jack.getCollisionArea().y);

    for(auto i:map.getObstacle()){
        if(checkCollision(jack.getPosition(),jack.getCollisionArea(),i->getPosition(),i->getArea()))
            if(jack.getDirection()==0){//down
                jack.setPosY(i->getPosition().y-i->getArea().y/2-jack.getCollisionArea().y/2);
            }else if(jack.getDirection()==1){//right
                jack.setPosX(i->getPosition().x-i->getArea().x/2-jack.getCollisionArea().x/2);
            }else if(jack.getDirection()==2){//up
                jack.setPosY(i->getPosition().y+i->getArea().y/2+jack.getCollisionArea().y/2);
            }else if(jack.getDirection()==3){//left
                jack.setPosX(i->getPosition().x+i->getArea().x/2+jack.getCollisionArea().x/2);
            }
    }
    //enemy
    for(auto i:enemyFolder){
        if(i->getPosition().x<=map.getPosition().x-map.getSize().x/2)
            i->setPosX(map.getPosition().x-map.getSize().x/2);
        if(i->getPosition().x>=map.getPosition().x+map.getSize().x/2)
            i->setPosX(map.getPosition().x+map.getSize().x/2);
        if(i->getPosition().y<=map.getPosition().y-map.getSize().y/2)
            i->setPosY(map.getPosition().y-map.getSize().y/2);
        if(i->getPosition().y>=map.getPosition().y+map.getSize().y/2)
            i->setPosY(map.getPosition().y+map.getSize().y/2);
    }


}
