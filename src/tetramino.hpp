#pragma once

#include "block.hpp"

class Tetramino {
    public:
        Tetramino();
        ~Tetramino();

        enum class Type {
            I,
            O,
            T,
            S,
            Z,
            J,
            L
        };

        Block blocks[4];
        sf::Vector2i blocksPos[4];

        Type type;

        void rotate(bool right);
    private:

};