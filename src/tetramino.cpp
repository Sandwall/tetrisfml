#include <SFML/Graphics.hpp>

#include "block.hpp"
#include "tetramino.hpp"

Tetramino::Tetramino() : type(Type::I)
{
    initBlockFromType(type);
}

Tetramino::Tetramino(Type t)
{
    type = t;
    initBlockFromType(type);
}

Tetramino::~Tetramino() {

}

void Tetramino::rotate(short rotations) {
    const char s = sizeData[(int)type];

    //TODO: Implement rotations
    if(s >= 3) {
    }
}

//Because this function just inits the block, 
void Tetramino::initBlockFromType(Type t) {
    color = colorData[(int)t];
    for(int i = 0; i < 4; i++) {
        blocksPos[i].x = blockData[(int)t][i][0];
        blocksPos[i].y = blockData[(int)t][i][1];
    }
}