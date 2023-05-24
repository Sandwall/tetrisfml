#pragma once

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

        sf::RenderWindow window;
        sf::Event event;
        sf::Font font;
        sf::Clock deltaClock;
        sf::Time dt;
        
        sf::Text debugText;
        sf::RectangleShape blockShape;
        sf::Vector2f blockPos;

        //std::vector<Tetramino> tetraminos;
        Player player;
        Field field;
        Block bufferBlock;

        bool fall;
        float timeBetweenFall = 0.25f;

        bool pause;
};