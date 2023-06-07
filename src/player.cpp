#include <cstdio>
#include <cstdlib>
#include <memory>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "tetramino.hpp"
#include "player.hpp"

Player::Player() : x(5), y(0), placeDelay(false), placeable(false), clearAnim(false) {
    nextBlock.type = static_cast<Tetramino::Type>(rand() % 7);
    this->ClearInput();
}

Player::~Player() {
}

#ifdef INPUT_DEBUG_TEXT
void Player::UpdateInputString() {
    for(int i = 0; i < 7; i++) {
        if(actionVals[i]) {
            inputString += controlString[i];
            inputString += "\n";
        }
    }
}
#endif

void Player::ClearInput() {
    memset(actionVals, false, sizeof(bool) * 7);
}

void Player::UpdateInput(sf::Event e) {
    if(e.type == sf::Event::KeyPressed) {
        switch(e.key.code) {
            case sf::Keyboard::W: {
                actionVals[static_cast<int>(Actions::HardDrop)] = true;
            } break;
            case sf::Keyboard::A: {
                actionVals[static_cast<int>(Actions::Left)] = true;
            } break;
            case sf::Keyboard::S: {
                actionVals[static_cast<int>(Actions::FastFall)] = true;
            } break;
            case sf::Keyboard::D: {
                actionVals[static_cast<int>(Actions::Right)] = true;
            } break;
            case sf::Keyboard::LShift: {
                actionVals[static_cast<int>(Actions::Hold)] = true;
            } break;
            case sf::Keyboard::Left: {
                actionVals[static_cast<int>(Actions::RotLeft)] = true;
            } break;
            case sf::Keyboard::Right: {
                actionVals[static_cast<int>(Actions::RotRight)] = true;
            } break;
        }
    } else if (e.type == sf::Event::MouseButtonPressed) {
        if(e.mouseButton.button == sf::Mouse::Left) {
            actionVals[static_cast<int>(Actions::RotLeft)] = true;
        } else if (e.mouseButton.button == sf::Mouse::Right) {
            actionVals[static_cast<int>(Actions::RotRight)] = true;
        }
    }
}

void Player::Update(sf::Time deltime) {
    if(actionVals[static_cast<int>(Actions::Left)]) {
        x--;
    } else if(actionVals[static_cast<int>(Actions::Right)]) {
        x++;
    }
    if(actionVals[static_cast<int>(Actions::FastFall)]) {
        y++;
        this->CheckBlock();
    }
    if(actionVals[static_cast<int>(Actions::HardDrop)]) {
        this->PerformHardDrop();
    }
    if(actionVals[static_cast<int>(Actions::RotLeft)]) {
        tetramino.rotate(-1);
    } else if (actionVals[static_cast<int>(Actions::RotRight)]) {
        tetramino.rotate(1);
    }
    this->CheckBlock();
}

//TODO
void Player::PerformHardDrop() {

}

void Player::Tick() {
    y++;
    this->CheckBlock();
}

//This is the function to check for collisions
//and place blocks once they fall
void Player::CheckBlock() {
    for(int i = 0; i < 4; i++) {
        //My habit of not initializing temp variables
        //in functions led me to using these two
        //private member variables 
        tempX = tetramino.blocksPos[i].x + x;
        tempY = tetramino.blocksPos[i].y + y;
        if(tempX > 9) {
            x--;
        } else if (tempX < 0) {
            x++;
        }

        //If block has been placed
        if(placeable) {
            if(!placeDelay) {
                placeDelay = true;
            } else {
                y--;
                PlaceBlock();
                placeDelay = false;
                placeable = false;
                if(field->CheckLineClear()) clearAnim = true;
            }
        } else {
            if(tempY >= FIELD_HEIGHT) {
                placeable = true;
            } else if(field->getBlockAt(tempX,tempY).active) {
                placeable = true;
            }
        }
    }
}

void Player::AssignField(std::shared_ptr<Field> f) {
    field = f;
}

void Player::PlaceBlock() {
    for(int i = 0; i < 4; i++) {
        tempX = tetramino.blocksPos[i].x + x;
        tempY = tetramino.blocksPos[i].y + y;
        field->setBlockAt(tempX, tempY, true, tetramino.color);
    }

    CycleBlock();
    y = 0;
    x = 5 - (tetramino.sizeData[static_cast<int>(tetramino.type)] / 2);
    tetramino.initBlock();
}

void Player::CycleBlock() {
    tetramino.type = nextBlock.type;
    nextBlock.type = static_cast<Tetramino::Type>(rand() % 7);
}