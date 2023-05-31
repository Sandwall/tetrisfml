#pragma once

#include <memory>

#include "player.hpp"
#include "field.hpp"

class Game {
    public:
        Game();
        ~Game();

        int Run();
    private:
        void Update();
        void Render();

        sf::RenderTexture tex;
        sf::Sprite texSprite;

        sf::RenderWindow window;
        sf::Event event;
        sf::Font font;
        sf::Clock deltaClock;
        sf::Time dt;
        
        sf::Text debugText;
        sf::Text pauseText;
        sf::RectangleShape pauseBg;
        
        sf::RectangleShape blockShape;
        sf::RectangleShape flashShape;
        sf::Vector2f blockPos;

        //std::vector<Tetramino> tetraminos;
        Player player;
        Block bufferBlock;
        std::shared_ptr<Field> field;

        const float timeBetweenFall = 0.25f;
        const float timeForClearAnim = 0.75f;
        const float timeBetweenFlash = 0.1f;

        float fallTimer = timeBetweenFall;
        float clearAnimTimer = timeForClearAnim;
        float flashTimer = timeBetweenFlash;

        bool pause;
        bool flashState;
};