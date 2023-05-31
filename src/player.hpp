#pragma once

#include "tetramino.hpp"
#include "field.hpp"

class Player {
    public:
        Player();
        ~Player();

        int x;
        int y;

        void UpdateInput(sf::Event e);
        void ClearInput();

        void Update(sf::Time deltime);
        void Tick();

        void AssignField(std::shared_ptr<Field> f);

        Tetramino tetramino;
        
        //Some small debug stuff, not really relevant
        sf::String inputString;
        void UpdateInputString();
        float inputStringDelay = 1.0f;

        bool clearAnim;
    private:
        //left, right, drop, fall, hold, rotleft, rotright
        Tetramino::Type nextBlock;
        std::shared_ptr<Field> field;

        void CheckBlock();
        void PlaceBlock();
        void CycleBlock();

        bool placeable;
        bool placeDelay;
        bool actionVals[7];

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

        int tempx;
        int tempy;
};