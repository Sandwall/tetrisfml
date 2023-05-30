#include <cstdio>
#include <cstdlib>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "tetramino.hpp"
#include "player.hpp"

Player::Player() : x(5), y(0) {
    this->ClearInput();
}

Player::~Player() {
}

void Player::UpdateInputString() {
    for(int i = 0; i < 7; i++) {
        if(actionVals[i]) {
            inputString += controlString[i];
            inputString += "\n";
        }
    }
}

void Player::ClearInput() {
    memset(actionVals, false, sizeof(bool) * 7);
}

void Player::UpdateInput(sf::Event e) {
    if(e.type == sf::Event::KeyPressed) {
        switch(e.key.code) {
            case sf::Keyboard::W: {
                actionVals[(int)Actions::HardDrop] = true;
            } break;
            case sf::Keyboard::A: {
                actionVals[(int)Actions::Left] = true;
            } break;
            case sf::Keyboard::S: {
                actionVals[(int)Actions::FastFall] = true;
            } break;
            case sf::Keyboard::D: {
                actionVals[(int)Actions::Right] = true;
            } break;
            case sf::Keyboard::LShift: {
                actionVals[(int)Actions::Hold] = true;
            } break;
            case sf::Keyboard::Left: {
                actionVals[(int)Actions::RotLeft] = true;
            } break;
            case sf::Keyboard::Right: {
                actionVals[(int)Actions::RotRight] = true;
            } break;
        }
    } else if (e.type == sf::Event::MouseButtonPressed) {
        if(e.mouseButton.button == sf::Mouse::Left) {
            actionVals[(int)Actions::RotLeft] = true;
        } else if (e.mouseButton.button == sf::Mouse::Right) {
            actionVals[(int)Actions::RotRight] = true;
        }
    }
}

void Player::Update(sf::Time deltime, Field& field) {
    if(actionVals[(int)Actions::Left]) {
        x--;
    } else if(actionVals[(int)Actions::Right]) {
        x++;
    }
    if(actionVals[(int)Actions::FastFall]) {
        y++;
    }
    if(actionVals[(int)Actions::RotLeft]) {
        tetramino.rotate(-1);
    } else if (actionVals[(int)Actions::RotRight]) {
        tetramino.rotate(1);
    }
    x = std::clamp(x, 0, 9);
    this->CheckAndPlaceBlock();
}

void Player::Tick(Field& field) {
    y++;
    this->CheckAndPlaceBlock();
}

void Player::CheckAndPlaceBlock() {
    if(y >= 20) {
        y = 0;
        x = 5;
        tetramino.initBlockFromType((Tetramino::Type)(rand()%7));
    }
}