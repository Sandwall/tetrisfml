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
        enum class GameState {
            Title,
            Playing,
            Lose
        };

        GameState state;

        void Update();
        void Render();

        sf::RenderTexture tex;
        sf::Texture blockTex;
        sf::Sprite texSprite;

        sf::RenderWindow window;
        sf::Event event;
        sf::Font font;
        sf::Clock deltaClock;
        sf::Time dt;

#ifdef INPUT_DEBUG_TEXT
        sf::Text debugText;
#endif
        sf::Text pauseText;
        sf::Text loseText;
        sf::Text scoreText;
        sf::Text uiText;

        char clearLinesBuffer[8];
        char levelBuffer[4];

        sf::String scoreSfString;
        std::string scoreString;

        sf::RectangleShape pauseBg;
        
        sf::RectangleShape blockShape;
        sf::RectangleShape flashShape;
        sf::Vector2f blockPos;
        sf::RectangleShape fieldShape;

        //std::vector<Tetramino> tetraminos;
        Player player;
        Block bufferBlock;
        std::shared_ptr<Field> field;
        
        sf::Vector2f fieldOffset;

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