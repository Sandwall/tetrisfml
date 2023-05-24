#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "player.hpp"

Player::Player() : x(0), y(0) {
    this->ClearInput();
    color = sf::Color::Cyan;
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

void Player::Update() {
    if(actionVals[(int)Actions::Left]) {
        x--;
    }
    if(actionVals[(int)Actions::Right]) {
        x++;
    }
    if(actionVals[(int)Actions::FastFall]) {
        y++;
    }
    x = std::clamp(x, 0, 9);
    if(y >= 20) {
        y = 0;
    }
}

void Player::Tick() {
    y++;
    if(y >= 20) {
        y = 0;
    }
}