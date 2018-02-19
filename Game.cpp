//
// Created by ita on 30/08/17.
//

#include "Game.h"
#include "FireWeapon.h"
#include "ColdWeapon.h"

Game::Game():window("Blood&Bond", sf::Vector2u(960,480)),jack("Jack",10,10,10,480,240, nullptr),detStatus("Jack HP:",old,25),
enemyStatus("Dragon HP: ",old,25){


    msg.loadFromFile("/home/ita/CLionProjects/BloodBond/Font/BeautyDemo.ttf");
    old.loadFromFile("/home/ita/CLionProjects/BloodBond/Font/1942.ttf");

    detStatus.setPosition(7,2);
    detStatus.setFillColor(sf::Color::Black);
    detStatus.setCharacterSize(25);
    enemyStatus.setPosition(7,33);
    enemyStatus.setFillColor(sf::Color::Black);
    enemyStatus.setCharacterSize(25);

    insertMap(MapType::mansion);   //0
    insertMap(MapType::frontyard); //1
    insertMap(MapType::cemetery);  //2
    insertMap(MapType::courtyard); //3

}

void Game::update() {
    jack.resetRender();
    jack.update();
    for(auto i:enemyFolder)
        i->resetRender();
    currencyMap->update();
    }

void Game::gameLoop() {
    GameStart();
    gameClock.restart();

    sf::RectangleShape rectangle(sf::Vector2f(220, 70));
    rectangle.setFillColor(sf::Color::Red);
    rectangle.setPosition(1, 1);

    currencyMap->create();

    Medicine *potion, *aspirin;
    potion= new Medicine(7,medType::sp);
    aspirin= new Medicine(3, medType::hp);
    Key* MansionKey;
    MansionKey=new Key(keyType::skeleton);
    Message* clue;
    clue= new Message();
    std::string content="The answer is \ninside your heArt";
    clue->setContent(content);
    Weapon *magnum, *ritualKnife;
    magnum=new FireWeapon(fireWeaponType::gun);
    ritualKnife= new ColdWeapon(coldWeaponType::sword);

    jack.setWeapon(magnum);
    jack.getMedicine(*potion);
    jack.getMedicine(*aspirin);
    jack.getKey(*MansionKey);
    jack.getMessage(*clue);
    while (!window.IsDone()){
        window.Update();
        update();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
            jack.throwWeapon();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
            jack.setWeapon(ritualKnife);

        jack.use(window);


        // movement
        window.BeginDraw();
        currencyMap->Render(window);

        jack.move();
        jack.attack();

        auto pos=enemyFolder.cbegin();
        for(auto i: enemyFolder) {
            //check if detective attack works
            if(jack.isFighting()&&!i->hit){//todo use hit with weapon not with enemy
                if(checkCollision(i->getPosition(),i->getCollisionArea(),jack.getAttackPosition(),jack.getAttackRange())){
                    i->damage(jack.getAttackPower());
                    i->hit=true;
                }
            }
            else if(!jack.isFighting())
                    i->hit=false;

            if(checkCollision(jack.getPosition(),jack.getCollisionArea(),i->getPosition(),i->getRange())){
                i->attack(jack);
                if(checkCollision(jack.getPosition(),jack.getCollisionArea(),i->getAttackPosition(),i->getAttackRange()))
                    jack.damage(i->getStrength());
            }
            else
                i->move(jack);


            if(i->getHp()<=0)
                enemyFolder.erase(pos);

            pos++;
        }


        if(currencyMap->getType()==MapType::courtyard) {
            if (jack.getPosition().x < 0) {
                currencyMap = map[2];//cemetery
                if (!currencyMap->isVisited()) {
                    currencyMap->create();
                    deadFactory=new EnemyFactory(EnemyType::skeleton,level ::low,currencyMap->getTilePosition(0,2));


                }
                jack.setPosX(window.getSize().x);
            }
            if(jack.getPosition().y < 0) {
                currencyMap=map[1];//frontyard
                if(!currencyMap->isVisited())
                    currencyMap->create();
                jack.setPosY(window.getSize().y);

            }
        }
        else if(currencyMap->getType()==MapType::cemetery){
            if(deadFactory!= nullptr){
                enemyFolder.push_back(deadFactory->CreateEnemy(Behavior::sniper));
                enemyFolder.push_back(deadFactory->CreateEnemy(Behavior::berserk));
                deadFactory= nullptr;
            }
            if(jack.getPosX()>window.getSize().x) {
                if (enemyFolder.empty()) {
                    currencyMap = map[3];//courtyard
                    if (!currencyMap->isVisited())
                        currencyMap->create();
                }
                else
                    std::cout<<"A strange force doesn't allow you to escape!"<<std::endl;
                jack.setPosX(0);
            }
        }
        else if(currencyMap->getType()==MapType::frontyard){
            if(jack.getPosition().y>window.getSize().y) {
                currencyMap = map[3];//courtyard
                if (!currencyMap->isVisited())
                    currencyMap->create();
                jack.setPosY(0);
            }
            if(jack.getPosition().y-jack.getCollisionArea().y/2<=100){
                currencyMap=map[0];
                if (!currencyMap->isVisited())
                    currencyMap->create();
                jack.setPosY(window.getSize().y);
            }
        }
        else if(currencyMap->getType()==MapType::mansion){
            //fineeee
        }


        gameBound();

        //Render
        for(auto i: currencyMap->getObstacle()){
            if(checkCollision(i->getCenterPosition(),i->getCollisionArea(),jack.getPosition(),jack.getCollisionArea())) {//det & obs
                jack.interact(i);
                if (jack.getPosY() < i->getPosition().y)
                    jack.Render(window);
            }

            for(auto en:enemyFolder)
                if(checkCollision(i->getCenterPosition(),i->getCollisionArea(),en->getPosition(),en->getCollisionArea()))//en & obs
                    if(en->getPosY()<i->getPosition().y)
                        en->Render(window);

            i->Render(window);
        }
        for(auto en:enemyFolder) {
            if (checkCollision(en->getPosition(), en->getCollisionArea(), jack.getPosition(), jack.getCollisionArea()))
                if (jack.getPosY() < en->getPosY()) {
                    if (!jack.getRender())
                        jack.Render(window);
                }

            if(!en->getRender())
                en->Render(window);
        }
        if(!jack.getRender())
            jack.Render(window);
        detStatus.setString("Jack HP: "+toString<int>(jack.getHp()));
        window.Draw(rectangle);
        window.Draw(detStatus);
        jack.RenderInventory(window);
        window.EndDraw();
    }
}

void Game::GameStart(){
    //screen home
}

void Game::gameBound() {
    //map bound
    if(jack.getPosition().x-jack.getCollisionArea().x/2<=currencyMap->getPosition().x-currencyMap->getSize().x/2)
        jack.setPosX(currencyMap->getPosition().x-currencyMap->getSize().x/2+jack.getCollisionArea().x/2);

    if(jack.getPosition().x+jack.getCollisionArea().x/2>=currencyMap->getPosition().x+currencyMap->getSize().x/2)
        jack.setPosX(currencyMap->getPosition().x+currencyMap->getSize().x/2-jack.getCollisionArea().x/2);

    if(jack.getPosition().y-jack.getCollisionArea().y/2<=currencyMap->getPosition().y-currencyMap->getSize().y/2)
        jack.setPosY(currencyMap->getPosition().y-currencyMap->getSize().y/2+jack.getCollisionArea().y/2);

    if(jack.getPosition().y+jack.getCollisionArea().y>=currencyMap->getPosition().y+currencyMap->getSize().y/2)
        jack.setPosY(currencyMap->getPosition().y+currencyMap->getSize().y/2-jack.getCollisionArea().y);

    for(auto i:enemyFolder){
        if(i->getPosition().x<=currencyMap->getPosition().x-currencyMap->getSize().x/2)
            i->setPosX(currencyMap->getPosition().x-currencyMap->getSize().x/2);
        if(i->getPosition().x>=currencyMap->getPosition().x+currencyMap->getSize().x/2)
            i->setPosX(currencyMap->getPosition().x+currencyMap->getSize().x/2);
        if(i->getPosition().y<=currencyMap->getPosition().y-currencyMap->getSize().y/2)
            i->setPosY(currencyMap->getPosition().y-currencyMap->getSize().y/2);
        if(i->getPosition().y>=currencyMap->getPosition().y+currencyMap->getSize().y/2)
            i->setPosY(currencyMap->getPosition().y+currencyMap->getSize().y/2);
    }

    //obstacle bound
    for(auto obs:currencyMap->getObstacle()){
        if(checkCollision(jack.getFeetPosition(),jack.getWalkingArea(),obs->getPosition(),obs->getArea()))
            if(jack.getDirection()==0){//down
                jack.setPosY(obs->getPosition().y-obs->getArea().y/2-jack.getWalkingArea().y/2-20);
            }else if(jack.getDirection()==1){//right
                jack.setPosX(obs->getPosition().x-obs->getArea().x/2-jack.getWalkingArea().x/2);
            }else if(jack.getDirection()==2){//up
                jack.setPosY(obs->getPosition().y+obs->getArea().y/2+jack.getWalkingArea().y/2-20);
            }else if(jack.getDirection()==3){//left
                jack.setPosX(obs->getPosition().x+obs->getArea().x/2+jack.getWalkingArea().x/2);
            }
        for(auto en:enemyFolder) {
            if (checkCollision(en->getFeetPosition(),en->getWalkingArea(),obs->getPosition(),obs->getArea()))
                if(en->getDirection()==0){//down
                    en->setPosY(obs->getPosition().y-obs->getArea().y/2-en->getWalkingArea().y/2-20);
                }else if(en->getDirection()==1){//right
                    en->setPosX(obs->getPosition().x-obs->getArea().x/2-en->getWalkingArea().x/2);
                }else if(en->getDirection()==2){//up
                    en->setPosY(obs->getPosition().y+obs->getArea().y/2+en->getWalkingArea().y/2-20);
                }else if(en->getDirection()==3){//left
                    en->setPosX(obs->getPosition().x+obs->getArea().x/2+en->getWalkingArea().x/2);
                }
        }
    }
}

bool Game::checkCollision(sf::Vector2f target, sf::Vector2f collisionArea, sf::Vector2f focus, sf::Vector2f range) {
    if(focus.x+range.x/2>target.x-collisionArea.x/2 && focus.x-range.x/2<target.x+collisionArea.x/2)
        if(focus.y+range.y/2>target.y-collisionArea.y/2 && focus.y-range.y/2<target.y+collisionArea.y/2)
            return true;
    return false;

}
