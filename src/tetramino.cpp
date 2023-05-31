#include <iostream>
#include <SFML/Graphics.hpp>

#include "block.hpp"
#include "tetramino.hpp"

Tetramino::Tetramino() : type(Type::I)
{
    initBlock();
}

Tetramino::Tetramino(Type t)
{
    type = t;
    initBlock();
}

Tetramino::~Tetramino() {

}

//The rotations parameter is 
void Tetramino::rotate(short rotations) {
    const char s = sizeData[static_cast<int>(type)];

    //This rotation code is really clunky,
    //considering it doesn't just pull
    //the orientations from a data source
    if(s == 2) {
    } else if(s == 3) {
        if(rotations > 0) {
            rotate3x3();
        } else if (rotations < 0) {
            rotate3x3();
            rotate3x3();
            rotate3x3();
        }
    } else if (s == 4) {
        if(rotations > 0) {
            rotate4x4();
        } else if (rotations < 0) {
            rotate4x4();
            rotate4x4();
            rotate4x4();
        }
    } else {
        std::cout << "Rotations not implemented for this size." << std::endl;
    }
}

void Tetramino::initBlock() {
    color = colorData[(int)type];
    for(int i = 0; i < 4; i++) {
        blocksPos[i].x = blockData[(int)type][i][0];
        blocksPos[i].y = blockData[(int)type][i][1];
    }
}

void Tetramino::rotate3x3() {
    for(int i = 0; i < 4; i++) {
        if(blocksPos[i].x == 0) {
            if(blocksPos[i].y == 0) {
                //0, 0
                blocksPos[i].x = 2;
                blocksPos[i].y = 0;
            } else if (blocksPos[i].y == 1) {
                //0, 1
                blocksPos[i].x = 1;
                blocksPos[i].y = 0;
            } else if (blocksPos[i].y == 2) {
                //0, 2
                blocksPos[i].x = 0;
                blocksPos[i].y = 0;
            }
        } else if(blocksPos[i].x == 1) {
            if(blocksPos[i].y == 0) {
                //1, 0
                blocksPos[i].x = 2;
                blocksPos[i].y = 1;
            } else if(blocksPos[i].y == 2) {
                //1, 2
                blocksPos[i].x = 0;
                blocksPos[i].y = 1;
            }
        } else if(blocksPos[i].x == 2) {
            if(blocksPos[i].y == 0) {
                //2, 0
                blocksPos[i].x = 2;
                blocksPos[i].y = 2;
            } else if (blocksPos[i].y == 1) {
                //2, 1
                blocksPos[i].x = 1;
                blocksPos[i].y = 2;
            } else if (blocksPos[i].y == 2) {
                //2, 2
                blocksPos[i].x = 0;
                blocksPos[i].y = 2;
            }
        }
    }
}

void Tetramino::rotate4x4() {
    for(int i = 0; i < 4; i++) {
        switch(blocksPos[i].x) {
            case 0: {
            switch(blocksPos[i].y) {
                case 0: {
                    //0, 0
                    blocksPos[i].x = 3; blocksPos[i].y = 0;
                } break;
                case 1: {
                    //0, 1
                    blocksPos[i].x = 2; blocksPos[i].y = 0;
                } break;
                case 2: {
                    //0, 2
                    blocksPos[i].x = 1; blocksPos[i].y = 0;
                } break;
                case 3: {
                    //0, 3
                    blocksPos[i].x = 0; blocksPos[i].y = 0;
                } break;
            }
            } break;
            case 1: {
            switch(blocksPos[i].y) {
                case 0: {
                    //1, 0
                    blocksPos[i].x = 3; blocksPos[i].y = 1;
                } break;
                case 1: {
                    //1, 1 
                    blocksPos[i].x = 2; blocksPos[i].y = 1;
                } break;
                case 2: {
                    //1, 2
                    blocksPos[i].x = 1; blocksPos[i].y = 1;
                } break;
                case 3: {
                    //1, 3
                    blocksPos[i].x = 0; blocksPos[i].y = 1;
                } break;
            }
            } break;
            case 2: {
            switch(blocksPos[i].y) {
                case 0: {
                    //2, 0
                    blocksPos[i].x = 3; blocksPos[i].y = 2;
                } break;
                case 1: {
                    //2, 1
                    blocksPos[i].x = 2; blocksPos[i].y = 2;
                } break;
                case 2: {
                    //2, 2
                    blocksPos[i].x = 1; blocksPos[i].y = 2;
                } break;
                case 3: {
                    //2, 3
                    blocksPos[i].x = 0; blocksPos[i].y = 2;
                } break;
            }
            } break;
            case 3: {
            switch(blocksPos[i].y) {
                case 0: {
                    //3, 0
                    blocksPos[i].x = 3; blocksPos[i].y = 3;
                } break;
                case 1: {
                    //3, 1
                    blocksPos[i].x = 2; blocksPos[i].y = 3;
                } break;
                case 2: {
                    //3, 2
                    blocksPos[i].x = 1; blocksPos[i].y = 3;
                } break;
                case 3: {
                    //3, 3
                    blocksPos[i].x = 0; blocksPos[i].y = 3;
                } break;
            }
            } break;
        }
    }
}