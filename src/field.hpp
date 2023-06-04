#pragma once

#include <bitset>

#include "block.hpp"

#define FIELD_WIDTH 10
#define FIELD_HEIGHT 20

class Field {
    public:
        Field();
        ~Field();

        void Clear();
        Block getBlockAt(int x, int y);
        void setBlockAt(int x, int y, bool ac, sf::Color col);
        void setBlockAt(int x, int y, Block b);

        void Update();
        void Render();

        bool CheckLineClear();
        void RemoveClearedRows();

        bool clearedRows[FIELD_HEIGHT];
    private:
        Block field[FIELD_WIDTH * FIELD_HEIGHT];
        Block nullBlock;
        int blocksInRow;
        int numClearedRows;

};