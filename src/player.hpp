#pragma once

#include "tetramino.hpp"

class Field;

class Player {
    public:
        Player();
        ~Player();

        int x;
        int y;

        void UpdateInput(sf::Event e);
        void ClearInput();

        void Update(sf::Time deltime, Field& field);
        void Tick(Field& field);

        Tetramino tetramino;
        
        //Some small debug stuff, not really relevant
        sf::String inputString;
        void UpdateInputString();
        float inputStringDelay = 1.0f;
    private:
        //left, right, drop, fall, hold, rotleft, rotright
        bool actionVals[7];

        void CheckAndPlaceBlock();

        enum class Actions {
            Left = 0,
            Right = 1,
            HardDrop = 2,
            FastFall = 3,
            Hold = 4,
            RotLeft = 5,
            RotRight = 6
        };

        const char* controlString[7] = {"Left", "Right", "HardDrop", "FastFall", "Hold", "RotLeft", "RotRight"};
};