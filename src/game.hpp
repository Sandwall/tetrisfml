#pragma once

#include <memory>
#include <string>

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
        sf::Text scoreText;

        char clearLinesBuffer[8];
        char levelBuffer[4];

        sf::String scoreSfString;
        std::string scoreString;

        sf::RectangleShape pauseBg;
        
        sf::RectangleShape blockShape;
        sf::RectangleShape flashShape;
        sf::Vector2f blockPos;

        //std::vector<Tetramino> tetraminos;
        Player player;
        Block bufferBlock;
        std::shared_ptr<Field> field;

        int clearedLines;
        int level;

        const float timeBetweenFall = 0.25f;
        const float timeForClearAnim = 0.75f;
        const float timeBetweenFlash = 0.1f;

        float fallTimer = timeBetweenFall;
        float clearAnimTimer = timeForClearAnim;
        float flashTimer = timeBetweenFlash;

        bool pause;
        bool flashState;
};