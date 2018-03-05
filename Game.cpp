//
// Created by ita on 30/08/17.
//

#include "Game.h"
#include "FireWeapon.h"
#include "ColdWeapon.h"

Game::Game():window(sf::VideoMode(960,480),"Blood&Bonds"),jack("Jack",50,50,480,240, nullptr),text("",old){

    msg.loadFromFile("./Font/BeautyDemo.ttf");
    old.loadFromFile("./Font/1942.ttf");

    boxOpen_1=false;
    boxOpen_2=false;
    round_1=false;
    round_2=false;
    text.setPosition(200,0);
    text.setFillColor(sf::Color::Red);
    text.setCharacterSize(25);

    home.loadFromFile("./texture/menù/home.jpg");
    credit.loadFromFile("./texture/menù/cemetery.png");
    sprite.setTexture(home);
    sprite.setOrigin(home.getSize().x/2,home.getSize().y/2);

    sprite.setPosition(window.getSize().x/2,window.getSize().y/2);
    sprite.setScale(0.8,0.6);


    insertMap(MapType::mansion);   //0
    insertMap(MapType::frontyard); //1
    insertMap(MapType::cemetery);  //2
    insertMap(MapType::courtyard); //3

}

void Game::handelInput() {
    sf::Event event;
    while(window.pollEvent(event)){
        if(event.type== sf::Event::Closed)
            window.close();
        else if(event.type==sf::Event::KeyPressed){
            if(event.key.code==sf::Keyboard::Escape)
                window.close();
        }
        else if(event.type==sf::Event::KeyReleased){
            if(event.key.code==sf::Keyboard::M)//use keyboard with inventory
                if (!jack.getMedikit().isOpen())
                    jack.openMedikit();
                else
                    jack.closeMedikit();
            else if(event.key.code==sf::Keyboard::N)
                if(!jack.getNotebook().isOpen())
                    jack.openNotebook();
                else
                    jack.closeNotebook();
            else if(event.key.code==sf::Keyboard::K)
                if(!jack.getKeychain().isOpen())
                    jack.openKeychain();
                else
                    jack.closeKeychain();
        }
        else if(event.type==sf::Event::MouseButtonReleased){
            if(event.mouseButton.button==sf::Mouse::Left){ //use mouse with inventory
                if(checkCollision(jack.getMedikit().getPosition(),jack.getMedikit().getCollisionArea(),
                                          sf::Vector2f(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y))){
                    if (!jack.getMedikit().isOpen()&&!jack.getKeychain().isOpen()&&!jack.getNotebook().isOpen())
                        jack.openMedikit();
                    else
                        jack.closeMedikit();
                }else if(checkCollision(jack.getKeychain().getPosition(),jack.getKeychain().getCollisionArea(),
                                                sf::Vector2f(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y))){
                    if (!jack.getKeychain().isOpen()&&!jack.getNotebook().isOpen())
                        jack.openKeychain();
                    else
                        jack.closeKeychain();
                }else if(checkCollision(jack.getNotebook().getPosition(),jack.getNotebook().getCollisionArea(),
                                                sf::Vector2f(sf::Mouse::getPosition(window).x,sf::Mouse::getPosition(window).y))){
                    if (!jack.getNotebook().isOpen())
                        jack.openNotebook();
                    else
                        jack.closeNotebook();
                }else
                    jack.useInventory(window);

            }

        }
    }
}

void Game::update() {

    jack.resetRender();
    jack.reload();
    for(auto i:enemyFolder)
        i->resetRender();
    currencyMap->update();
    if(gameClock.getElapsedTime()-txtTime>sf::seconds(3)){
        text.setString("");
        text.setPosition(200,0);
        text.setCharacterSize(25);
        text.setFont(old);
    }
}

void Game::GameStart(){
    while(window.isOpen()) {
        handelInput();
        window.clear();
        window.draw(sprite);
        window.display();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            GameLoop();

    }
}

void Game::GameLoop() {
    initialize();
    Medicine *potion, *elixir;
    potion = new Medicine(7, medType::sp);
    elixir = new Medicine(10, medType::hp);
    Key *MansionKey;
    MansionKey = new Key(keyType::skeleton);
    Weapon *revolver, *oldSword;
    revolver = new FireWeapon(fireWeaponType::gun);
    oldSword = new ColdWeapon(coldWeaponType::sword);
    Message *clue_1;
    clue_1=new Message;
    std::string content="I will waiting you \ninside my house to the \nnorth.\n\nWatch out!\nThe Cemetery to the \n"
            "west is dangerous.\n\nStay Away!\n     -Your Sweet Uncle";
    clue_1->setContent(content);
    jack.getMessage(*clue_1);
    text.setString("Look at your Notebook!\nYou've a message.");
    txtTime=gameClock.getElapsedTime();
    while (window.isOpen()){
        update();
        handelInput();

        jack.move();
        jack.attack();
        if(jack.getSanity()<=0){
            text.setPosition(window.getSize().x/2-120,window.getSize().y/2-50);
            text.setCharacterSize(50);
            sf::sleep(sf::seconds(1));
            text.setString("You lose your\n    mind!");
            end();
        }else if(jack.getHp()<=0){
            text.setPosition(window.getSize().x/2-100,window.getSize().y/2);
            text.setCharacterSize(50);
            sf::sleep(sf::seconds(1));
            text.setString("You died!");
            end();
        }

        // movement
        window.clear();
        currencyMap->Render(window);




        auto pos=enemyFolder.cbegin();
        for(auto i: enemyFolder) {
            //check if detective attack works
            if(jack.ready()){
                if(checkCollision(i->getPosition(),i->getCollisionArea(),jack.getAttackPosition(),jack.getAttackRange())){
                    i->damage(jack.getAttackPower());
                    jack.hit();
                }
            }


            if(checkCollision(jack.getPosition(),jack.getCollisionArea(),i->getPosition(),i->getRange())){
                i->attack(jack);
                if (i->ready()&&checkCollision(jack.getPosition(), jack.getCollisionArea(), i->getAttackPosition(),
                                   i->getAttackRange())) {
                    i->hit();
                    if (i->isSniper())
                        jack.getMad(i->getStrength());
                    else
                        jack.damage(i->getStrength());
                }
            }
            else
                i->move(jack);


            if(i->getHp()<=0){
                delete i;
                enemyFolder.erase(pos);
            }

            pos++;
        }


        if(currencyMap->getType()==MapType::courtyard) {
            if (jack.getPosition().x < 0) {
                currencyMap = map[2];//cemetery
                if (!currencyMap->isVisited()) {
                    currencyMap->create();
                    deadFactory=new EnemyFactory(EnemyType::skeleton,level ::low,currencyMap->getTilePosition(0,2));
                                    //posiziono la factory nel tile[0][2]
                }
                jack.setPosX(window.getSize().x);
            }
            else if(jack.getPosition().y < 0) {
                currencyMap=map[1];//frontyard
                if(!currencyMap->isVisited())
                    currencyMap->create();
                jack.setPosY(window.getSize().y);

            }
            if(currencyMap->getObstacle()[currencyMap->getObstacle().size()-1]->isOpen()&&!boxOpen_1){
                boxOpen_1=true;
                jack.setWeapon(oldSword);
                jack.getMedicine(*potion);
                jack.getMedicine(*elixir);
            }
        }
        else if(currencyMap->getType()==MapType::cemetery){
            if(!round_1){
                enemyFolder.push_back(deadFactory->CreateEnemy(Behavior::sniper));
                enemyFolder.push_back(deadFactory->CreateEnemy(Behavior::berserk));
                round_1=true;
                text.setPosition(window.getSize().x/2,window.getSize().y/2);
                text.setCharacterSize(40);
                text.setString("Round 1");
                txtTime=gameClock.getElapsedTime();
                for(auto en:enemyFolder)
                    en->subscribe(&jack);
            }
            else if(!round_2&&enemyFolder.empty()){
                enemyFolder.push_back(deadFactory->CreateEnemy(Behavior::sniper));
                delete deadFactory;
                deadFactory= nullptr;
                deadFactory=new EnemyFactory(EnemyType::skeleton,level::medium,currencyMap->getTilePosition(3,0));
                enemyFolder.push_back(deadFactory->CreateEnemy(Behavior::berserk));
                enemyFolder.push_back(deadFactory->CreateEnemy(Behavior::sniper));
                round_2=true;
                deadFactory= nullptr;
                text.setPosition(window.getSize().x/2,window.getSize().y/2);
                text.setCharacterSize(40);
                text.setString("Round 2");
                txtTime=gameClock.getElapsedTime();
                for(auto en:enemyFolder)
                    en->subscribe(&jack);
            }

            if(jack.getPosX()>window.getSize().x) {
                if (enemyFolder.empty()) {
                    currencyMap = map[3];//courtyard
                    if (!currencyMap->isVisited())
                        currencyMap->create();
                }
                else {
                    text.setString("A strange force doesn't \n  allow you to escape");
                    txtTime=gameClock.getElapsedTime();
                }
                jack.setPosX(0);
            }

            if(currencyMap->getObstacle()[currencyMap->getObstacle().size()-1]->isOpen()&&!boxOpen_2){
                boxOpen_2=true;
                jack.setWeapon(revolver);
                jack.getKey(*MansionKey);
            }
        }
        else if(currencyMap->getType()==MapType::frontyard){
            if(jack.getPosition().y>window.getSize().y) {
                currencyMap = map[3];//courtyard
                if (!currencyMap->isVisited())
                    currencyMap->create();
                jack.setPosY(0);
            }else if(jack.getPosition().y-jack.getCollisionArea().y/2<=100){
                currencyMap=map[0];//mansion
                if (!currencyMap->isVisited()) {
                    currencyMap->create();
                }
                jack.setPosY(window.getSize().y);
            }
        }
        else if(currencyMap->getType()==MapType::mansion){
            text.setPosition(100,window.getSize().y/2);
            text.setCharacterSize(50);
            text.setString("To be continued..");
            end();
        }


        gameBound();

        //Render
        for(auto i: currencyMap->getObstacle()){
            if(checkCollision(i->getCenterPosition(),i->getCollisionArea(),jack.getPosition(),jack.getCollisionArea())) {//det & obs
                if(i->isUnlockable()) {
                    jack.interact(i);//se entra nella sua collision area può interagire con gli oggetti
                    text.setString(i->getAction());
                    txtTime=gameClock.getElapsedTime();
                }
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
        jack.RenderInventory(window);
        window.draw(text);
        window.display();
    }
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

void Game::initialize() {
    gameClock.restart();
    if(!currencyMap->isVisited())
        currencyMap->create();

}

void Game::end(){
    sprite.setTextureRect(sf::IntRect(0,0,2000,2000));
    sprite.setOrigin(credit.getSize().x/2+20,credit.getSize().y/2);
    sprite.setScale(0.5,0.5);
    sprite.setTexture(credit);
    while(window.isOpen()) {
        handelInput();
        window.clear();
        window.draw(sprite);
        window.draw(text);
        window.display();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            window.close();

    }
}
