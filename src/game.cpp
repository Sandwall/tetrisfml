#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <memory>

#include "block.hpp"
#include "player.hpp"
#include "field.hpp"
#include "game.hpp"

Game::Game() : 
    window(sf::VideoMode(640, 640), "TetriSFML", sf::Style::Close),
    pause(false),
    flashState(false)
{
    //window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(true);
    font.loadFromFile("data/font.ttf");

    tex.create(640, 640);

    debugText.setFont(font);
    debugText.setCharacterSize(16);
    debugText.setFillColor(sf::Color::White);
    debugText.setPosition(320.0f, 0.0f);

    blockShape.setSize(sf::Vector2f(32.0, 32.0));
    blockShape.setOutlineThickness(1.0f);
    blockShape.setOutlineColor(sf::Color::White);

    flashShape.setSize(sf::Vector2f(32.0f * FIELD_WIDTH, 32.0f));
    flashShape.setOutlineThickness(1.0f);
    flashShape.setOutlineColor(sf::Color::White);
    flashShape.setFillColor(sf::Color::White);

    pauseText.setString("Pause");
    pauseText.setFont(font);
    pauseText.setCharacterSize(32);
    pauseText.setFillColor(sf::Color::White);
    pauseText.setPosition(320.0f, 320.0f);
    pauseText.setOrigin(pauseText.getLocalBounds().width / 2.0f, pauseText.getLocalBounds().height / 2.0f);

    pauseBg.setFillColor(sf::Color(0x00000080));
    pauseBg.setSize(sf::Vector2f(640.0f, 640.0f));

    field = std::make_shared<Field>();
    player.AssignField(field);

    dt = deltaClock.restart();
}

Game::~Game() {
    
}

void Game::Update() {
    if(!pause) {
        if(!player.clearAnim) {
            player.UpdateInputString();
            player.inputStringDelay -= dt.asSeconds();
            if(player.inputStringDelay <= 0.0f) {
                player.inputString.clear();
                player.inputStringDelay = 1.0f;
            }
            debugText.setString(player.inputString);
            fallTimer -= dt.asSeconds();

            if(fallTimer <= 0) {
                player.Tick();
                fallTimer = timeBetweenFall;
            }

            player.Update(dt);
        } else {
            clearAnimTimer -= dt.asSeconds();
            if(clearAnimTimer <= 0) {
                player.clearAnim = false;
                flashState = false;
                clearAnimTimer = timeForClearAnim;
                field->RemoveClearedRows();
            }

            flashTimer -= dt.asSeconds();
            if(flashTimer <= 0) {
                flashState = !flashState;
                flashTimer = timeBetweenFlash;
            }
        }
    }
}

void Game::Render() {
    if(!pause) {
        tex.clear();
        //Draw the player
        for(int i = 0; i < 4; i++) {
            blockPos.x = (player.tetramino.blocksPos[i].x + player.x) * 32;
            blockPos.y = (player.tetramino.blocksPos[i].y + player.y) * 32;
            blockShape.setPosition(blockPos);
            blockShape.setFillColor(player.tetramino.color);
            tex.draw(blockShape);        
        }
        for(int i = 0; i < FIELD_HEIGHT; i++) {
            for(int j = 0; j < FIELD_WIDTH; j++) {
                bufferBlock = field->getBlockAt(j, i);
                if(bufferBlock.active) {
                    blockPos.x = j * 32;
                    blockPos.y = i * 32;
                    blockShape.setPosition(blockPos);
                    blockShape.setFillColor(bufferBlock.color);
                    tex.draw(blockShape);
                }
            }
        }

        if(player.clearAnim && flashState) {
            for(int i = 0; i < FIELD_HEIGHT; i++) {
                flashShape.setPosition(0.0f, 32.0f * i);
                if(field->clearedRows[i]) {
                    tex.draw(flashShape);
                }
            }
        }

        tex.draw(debugText);
        tex.display();
        texSprite.setTexture(tex.getTexture());
    }
    window.draw(texSprite);
    if(pause) {
        window.draw(pauseBg);
        window.draw(pauseText);
    }
}

int Game::Run() {
    while (window.isOpen()) {
        player.ClearInput();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            player.UpdateInput(event);
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                pause = !pause;
            }
        }

        this->Update();

        window.clear(sf::Color::Black);
        this->Render();
        window.display();

        dt = deltaClock.restart();
    }

    return 0;
}