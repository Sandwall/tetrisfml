#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <memory>
#include <string>

#include "block.hpp"
#include "player.hpp"
#include "field.hpp"
#include "game.hpp"

#define BLOCK_SIZE 24

Game::Game() : 
    window(sf::VideoMode(640, 640), "TetriSFML", sf::Style::Close),
    pause(false),
    flashState(false),
    clearedLines(0),
    level(1)
{
    //window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(true);
    font.loadFromFile("data/font.ttf");

    tex.create(640, 640);

    blockTex.loadFromFile("data/block.png");

    //debugText.setFont(font);
    //debugText.setCharacterSize(16);
    //debugText.setFillColor(sf::Color::White);
    //debugText.setPosition(320.0f, 0.0f);

    uiText.setFont(font);
    uiText.setFillColor(sf::Color::White);

    pauseText.setString("Pause");
    pauseText.setFont(font);
    pauseText.setCharacterSize(32);
    pauseText.setFillColor(sf::Color::White);
    pauseText.setPosition(320.0f, 320.0f);
    pauseText.setOrigin(pauseText.getLocalBounds().width / 2.0f, pauseText.getLocalBounds().height / 2.0f);

    loseText = pauseText;
    loseText.setString("You Lost!");
    loseText.setOrigin(loseText.getLocalBounds().width / 2.0f, loseText.getLocalBounds().height / 2.0f);

    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);

    blockShape.setSize(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
    //blockShape.setOutlineThickness(-1.0f);
    blockShape.setOutlineColor(sf::Color::White);
    blockShape.setTexture(&blockTex, true);

    flashShape.setSize(sf::Vector2f(BLOCK_SIZE * FIELD_WIDTH, BLOCK_SIZE));
    flashShape.setOutlineThickness(1.0f);
    flashShape.setOutlineColor(sf::Color::White);
    flashShape.setFillColor(sf::Color::White);

    fieldOffset = sf::Vector2f((640 - (BLOCK_SIZE * FIELD_WIDTH))/2, (640 - (BLOCK_SIZE * FIELD_HEIGHT))/2);
    fieldShape.setPosition(fieldOffset);
    fieldShape.setSize(sf::Vector2f(BLOCK_SIZE * FIELD_WIDTH, BLOCK_SIZE * FIELD_HEIGHT));
    fieldShape.setOutlineColor(sf::Color::White);
    fieldShape.setOutlineThickness(2.0f);
    fieldShape.setFillColor(sf::Color::Black);

    pauseBg.setFillColor(sf::Color(0x00000080));
    pauseBg.setSize(sf::Vector2f(640.0f, 640.0f));

    state = GameState::Playing;

    field = std::make_shared<Field>();
    player.AssignField(field);

    dt = deltaClock.restart();
}

Game::~Game() {
    
}

void Game::Update() {
    
    if(state == GameState::Title) {

    } else if (state == GameState::Playing) {
        if(!pause) {
            if(!player.clearAnim) {

#ifdef INPUT_DEBUG_TEXT
                player.UpdateInputString();
                player.inputStringDelay -= dt.asSeconds();
                if(player.inputStringDelay <= 0.0f) {
                    player.inputString.clear();
                    player.inputStringDelay = 1.0f;
                }
                debugText.setString(player.inputString);
#endif

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
                    clearedLines+= field->numClearedRows;
                }

                flashTimer -= dt.asSeconds();
                if(flashTimer <= 0) {
                    flashState = !flashState;
                    flashTimer = timeBetweenFlash;
                }
            }
        }
    } else if (state == GameState::Lose) {
        
    }
}

void Game::Render() {
    if(state == GameState::Title) {

    } else if(state == GameState::Playing) {
        if(!pause) {
            tex.clear();

            tex.draw(fieldShape);
            
            //Draw the player
            for(int i = 0; i < 4; i++) {
                blockPos.x = (player.tetramino.blocksPos[i].x + player.x) * BLOCK_SIZE;
                blockPos.y = (player.tetramino.blocksPos[i].y + player.y) * BLOCK_SIZE;
                blockPos += fieldOffset;
                blockShape.setPosition(blockPos);
                blockShape.setFillColor(player.tetramino.color);
                tex.draw(blockShape);        
            }

            //Draw the field
            for(int i = 0; i < FIELD_HEIGHT; i++) {
                for(int j = 0; j < FIELD_WIDTH; j++) {
                    bufferBlock = field->getBlockAt(j, i);
                    if(bufferBlock.active) {
                        blockPos.x = j * BLOCK_SIZE;
                        blockPos.y = i * BLOCK_SIZE;
                        blockPos += fieldOffset;
                        blockShape.setPosition(blockPos);
                        blockShape.setFillColor(bufferBlock.color);
                        tex.draw(blockShape);
                    }
                }
            }

            //Draw the line clear flash
            if(player.clearAnim && flashState) {
                for(int i = 0; i < FIELD_HEIGHT; i++) {
                    flashShape.setPosition(fieldOffset.x, (BLOCK_SIZE * i) + fieldOffset.y);
                    if(field->clearedRows[i]) {
                        tex.draw(flashShape);
                    }
                }
            }

            static const int padding = 20;

            //Draw the score text (# of line clears and current level)
            itoa(clearedLines, clearLinesBuffer, 7);
            scoreString = "Lines Cleared: ";
            scoreString.append(clearLinesBuffer);
            scoreSfString = scoreString;
            scoreText.setString(scoreSfString);
            scoreText.setOrigin(0.0f, scoreText.getLocalBounds().height / 2.0f);
            scoreText.setPosition(padding, (BLOCK_SIZE * FIELD_HEIGHT) + (fieldOffset.y * 1.5));
            tex.draw(scoreText);

            itoa(level, levelBuffer, 3);
            scoreString = "Level ";
            //scoreString.append(levelBuffer);
            scoreString = level;
            scoreSfString = scoreString;
            scoreText.setString(scoreSfString);
            scoreText.setOrigin(0.0f, scoreText.getLocalBounds().height / 2.0f);
            scoreText.setPosition(640 - scoreText.getLocalBounds().width - padding, (BLOCK_SIZE * FIELD_HEIGHT) + (fieldOffset.y * 1.5));
            tex.draw(scoreText);

#ifdef INPUT_DEBUG_TEXT
            tex.draw(debugText);
#endif

            //Draw UI Text
            uiText.setString("Tetris");
            uiText.setCharacterSize(48);
            uiText.setPosition(fieldOffset.x/2.0f, fieldOffset.y/2.0f);
            uiText.setOrigin(uiText.getLocalBounds().width / 2.0f, uiText.getLocalBounds().height / 2.0f);
            tex.draw(uiText);

            uiText.setString("Hold");
            uiText.setCharacterSize(32);
            uiText.setPosition(fieldOffset.x/2.0f, fieldOffset.y * 1.5f);
            uiText.setOrigin(uiText.getLocalBounds().width / 2.0f, uiText.getLocalBounds().height / 2.0f);
            tex.draw(uiText);

            uiText.setString("Next");
            uiText.setPosition((fieldOffset.x * 1.5) + (BLOCK_SIZE * FIELD_WIDTH), fieldOffset.y/2.0f);
            uiText.setOrigin(uiText.getLocalBounds().width / 2.0f, uiText.getLocalBounds().height / 2.0f);
            tex.draw(uiText);

            tex.display();
            texSprite.setTexture(tex.getTexture());
        }
        window.draw(texSprite);
        if(pause) {
            window.draw(pauseBg);
            window.draw(pauseText);
        }
    } else if(state == GameState::Lose) {
        window.draw(texSprite);
        window.draw(pauseBg);
        window.draw(loseText);
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