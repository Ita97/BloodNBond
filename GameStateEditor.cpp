//
// Created by ciape on 01/02/18.
//

#include "GameStateEditor.h"


void GameStateEditor::draw(const float dt)
{
    this->game->window.clear(sf::Color::Black);

    this->game->window.setView(this->guiView);
    this->game->window.draw(this->game->background);

    this->game->window.setView(this->gameView);
    this->map.draw(this->game->window, dt);

    this->game->window.setView(this->guiView);
    for(auto gui : this->guiSystem) this->game->window.draw(gui.second);


}

void GameStateEditor::update(const float dt)
{

    this->guiSystem.at("infoBar").setEntryText(4, tileTypeToStr(currentTile->tileType));


}

void GameStateEditor::handleInput()
{
    sf::Event event;

    sf::Vector2f guiPos = this->game->window.mapPixelToCoords(sf::Mouse::getPosition(this->game->window), this->guiView);
    sf::Vector2f gamePos = this->game->window.mapPixelToCoords(sf::Mouse::getPosition(this->game->window), this->gameView);

    while(this->game->window.pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::MouseMoved:
            {
                /* Pan the camera */
                if(this->actionState == ActionState::PANNING)
                {
                    sf::Vector2f pos = sf::Vector2f(sf::Mouse::getPosition(this->game->window) - this->panningAnchor);
                    gameView.move(-1.0f * pos * this->zoomLevel);
                    panningAnchor = sf::Mouse::getPosition(this->game->window);
                }
                    /* Select tiles */
                else if(actionState == ActionState::SELECTING)
                {
                    sf::Vector2f pos = this->game->window.mapPixelToCoords(sf::Mouse::getPosition(this->game->window), this->gameView);
                    selectionEnd.x = pos.y / (this->map.tileSize) + pos.x / (2*this->map.tileSize) - this->map.width * 0.5 - 0.5;
                    selectionEnd.y = pos.y / (this->map.tileSize) - pos.x / (2*this->map.tileSize) + this->map.width * 0.5 + 0.5;

                    this->map.clearSelected();
                    if(this->currentTile->tileType == TileType::GRASS)
                    {
                        this->map.select(selectionStart, selectionEnd, {this->currentTile->tileType, TileType::WATER});
                    }
                    else
                    {
                        this->map.select(selectionStart, selectionEnd,
                                              {
                                                      this->currentTile->tileType,    TileType::FOREST,
                                                      TileType::WATER,                TileType::ROAD,
                                                      TileType::CHEST,          TileType::NOTE,
                                                      TileType::DOOR
                                              });
                    }


                }
                /* Highlight entries of the right click context menu */
                this->guiSystem.at("rightClickMenu").highlight(this->guiSystem.at("rightClickMenu").getEntry(guiPos));
                break;
            }
            case sf::Event::MouseButtonPressed:
            {
                /* Start panning */
                if(event.mouseButton.button == sf::Mouse::Middle)
                {
                    this->guiSystem.at("rightClickMenu").hide();
                    this->guiSystem.at("selectionCostText").hide();

                    if(this->actionState != ActionState::PANNING)
                    {
                        this->actionState = ActionState::PANNING;
                        this->panningAnchor = sf::Mouse::getPosition(this->game->window);
                    }
                }
                else if(event.mouseButton.button == sf::Mouse::Left)
                {
                    /* Select a context menu entry */
                    if(this->guiSystem.at("rightClickMenu").visible)
                    {
                        std::string msg = this->guiSystem.at("rightClickMenu").activate(guiPos);
                        if(msg != "flatten" && msg != "null") this->currentTile = &this->game->tileAtlas.at(msg);

                        this->guiSystem.at("rightClickMenu").hide();
                    }
                        /* Select map tile */
                    else
                    {
                        /* Select map tile */
                        if(this->actionState != ActionState::SELECTING)
                        {
                            this->actionState = ActionState::SELECTING;
                            selectionStart.x = gamePos.y / (this->map.tileSize) + gamePos.x / (2*this->map.tileSize) - this->map.width * 0.5 - 0.5;
                            selectionStart.y = gamePos.y / (this->map.tileSize) - gamePos.x / (2*this->map.tileSize) + this->map.width * 0.5 + 0.5;
                        }
                    }
                }
                else if(event.mouseButton.button == sf::Mouse::Right)
                {
                    /* Stop selecting */
                    if(this->actionState == ActionState::SELECTING)
                    {
                        this->actionState = ActionState::NONE;
                        this->guiSystem.at("selectionCostText").hide();
                        this->map.clearSelected();
                    }
                    else
                    {
                        /* Open the tile select menu */
                        sf::Vector2f pos = guiPos;

                        if(pos.x > this->game->window.getSize().x - this->guiSystem.at("rightClickMenu").getSize().x)
                        {
                            pos -= sf::Vector2f(this->guiSystem.at("rightClickMenu").getSize().x, 0);
                        }
                        if(pos.y > this->game->window.getSize().y - this->guiSystem.at("rightClickMenu").getSize().y)
                        {
                            pos -= sf::Vector2f(0, this->guiSystem.at("rightClickMenu").getSize().y);
                        }
                        this->guiSystem.at("rightClickMenu").setPosition(pos);
                        this->guiSystem.at("rightClickMenu").show();
                    }
                }
                break;
            }
            case sf::Event::MouseButtonReleased:
            {
                /* Stop panning */
                if(event.mouseButton.button == sf::Mouse::Middle)
                {
                    this->actionState = ActionState::NONE;
                }
                    /* Stop selecting */
                else if(event.mouseButton.button == sf::Mouse::Left)
                {
                    if(this->actionState == ActionState::SELECTING)
                    {

                        this->actionState = ActionState::NONE;
                        this->map.clearSelected();
                    }
                }
                break;
            }
                /* Zoom the view */
            case sf::Event::MouseWheelMoved:
            {
                if(event.mouseWheel.delta < 0)
                {
                    gameView.zoom(2.0f);
                    zoomLevel *= 2.0f;
                }
                else
                {
                    gameView.zoom(0.5f);
                    zoomLevel *= 0.5f;
                }
                break;
            }
                /* Close the window */
            case sf::Event::Closed:
            {
                this->game->window.close();
                break;
            }
                /* Resize the window */
            case sf::Event::Resized:
            {
                gameView.setSize(event.size.width, event.size.height);
                gameView.zoom(zoomLevel);
                guiView.setSize(event.size.width, event.size.height);
                this->guiSystem.at("infoBar").setDimensions(sf::Vector2f(event.size.width / this->guiSystem.at("infoBar").entries.size(), 16));
                this->guiSystem.at("infoBar").setPosition(this->game->window.mapPixelToCoords(sf::Vector2i(0, event.size.height - 16), this->guiView));
                this->guiSystem.at("infoBar").show();
                this->game->background.setPosition(this->game->window.mapPixelToCoords(sf::Vector2i(0, 0), this->guiView));
                this->game->background.setScale(
                        float(event.size.width) / float(this->game->background.getTexture()->getSize().x),
                        float(event.size.height) / float(this->game->background.getTexture()->getSize().y));
                break;
            }
            default: break;
        }
    }


}

GameStateEditor::GameStateEditor(Game* game)
{
    this->game = game;
    sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
    this->guiView.setSize(pos);
    this->gameView.setSize(pos);
    pos *= 0.5f;
    this->guiView.setCenter(pos);
    this->gameView.setCenter(pos);



    /* Create gui elements */
    this->guiSystem.emplace("rightClickMenu", Gui(sf::Vector2f(196, 16), 2, false, this->game->stylesheets.at("button"),
                                                  {
                                                          std::make_pair("Pick Up" 			, "grass"),
                                                          std::make_pair("Light It Up" 			, "forest" ),
                                                          std::make_pair("Open/Close"   , "chest"),
                                                          std::make_pair("Scan" 	, "note"),
                                                          std::make_pair("Use A Key" 	, "door"),
                                                          std::make_pair("Break" 		, "road")
                                                  }));

    this->guiSystem.emplace("selectionCostText", Gui(sf::Vector2f(196, 16), 0, false, this->game->stylesheets.at("text"),
                                                     { std::make_pair("", "") }));

    this->guiSystem.emplace("infoBar", Gui(sf::Vector2f(this->game->window.getSize().x / 5 , 16), 2, true, this->game->stylesheets.at("button"),
                                           { std::make_pair("time", "time"),
                                             std::make_pair("Healing Potion", "funds"),
                                             std::make_pair("Sanity Potion", "population"),
                                             std::make_pair("Torch", "employment"),
                                             std::make_pair("current tile", "tile") }));
    this->guiSystem.at("infoBar").setPosition(sf::Vector2f(0, this->game->window.getSize().y - 16));
    this->guiSystem.at("infoBar").show();

    map = Map("city_map.dat", 64, 64, game->tileAtlas);
    this->zoomLevel = 1.0f;

    /* Centre the camera on the city.map */
    sf::Vector2f centre(this->map.width, static_cast<float>(this->map.height * 0.5));
    centre *= float(this->map.tileSize);
    gameView.setCenter(centre);

    this->selectionStart = sf::Vector2i(0, 0);
    this->selectionEnd = sf::Vector2i(0, 0);

    this->currentTile = &this->game->tileAtlas.at("grass");
    this->actionState = ActionState::NONE;
}
