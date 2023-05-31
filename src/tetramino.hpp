#pragma once

#include "block.hpp"

class Tetramino {
    public:
        enum class Type {
            I = 0,
            J = 1,
            L = 2,
            O = 3,
            S = 4,
            T = 5,
            Z = 6
        };

        Tetramino();
        Tetramino(Type t);
        ~Tetramino();

        sf::Color color;
        sf::Vector2i blocksPos[4];

        Type type;

        void rotate(short rotations);
        void initBlock();
        
        //This is used for calculating rotations on-the-fly
        //and spawn position
        const char sizeData[7] { 4, 3, 3, 2, 3, 3, 3 };

    private:        
        const char blockData[7][4][2] {
            { { 0, 1 }, { 1, 1 }, { 2, 1 }, { 3, 1 }, },    //I
            { { 0, 0 }, { 0, 1 }, { 1, 1 }, { 2, 1 }, },    //J
            { { 0, 1 }, { 1, 1 }, { 2, 1 }, { 2, 0 }, },    //L
            { { 0, 0 }, { 1, 0 }, { 1, 1 }, { 0, 1 }, },    //O
            { { 0, 1 }, { 1, 1 }, { 1, 0 }, { 2, 0 }, },    //S
            { { 0, 1 }, { 1, 1 }, { 2, 1 }, { 1, 0 }, },    //T
            { { 0, 0 }, { 1, 0 }, { 1, 1 }, { 2, 1 }, }     //Z
        };


        const sf::Color colorData[7] {
            sf::Color::Cyan,
            sf::Color::Blue,
            sf::Color::Color(0xFC7E00FF),
            sf::Color::Yellow,
            sf::Color::Green,
            sf::Color::Magenta,
            sf::Color::Red
        };

        void rotate3x3();
        void rotate4x4();
};