#pragma once

#include "block.hpp"

class Field {
    public:
        Field();
        ~Field();

        void Clear();
        Block getBlockAt(int x, int y);

        void Update();
        void Render();

    private:
        Block field[10 * 20];

};