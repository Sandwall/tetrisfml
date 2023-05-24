#pragma once

class Player {
    public:
        Player();
        ~Player();

        int x;
        int y;

        void UpdateInput(sf::Event e);
        void ClearInput();

        void Update();
        void Tick();

        sf::Color color;
        
        //Some small debug stuff, not really relevant
        sf::String inputString;
        void UpdateInputString();
        float inputStringDelay = 1.0f;
    private:
        //left, right, drop, fall, hold, rotleft, rotright
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
};