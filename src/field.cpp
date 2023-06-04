#include <cstdio>
#include <cstdint>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "block.hpp"
#include "field.hpp"

Field::Field() : numClearedRows(0), blocksInRow(0), nullBlock{false, sf::Color::White} {
    memset(clearedRows, false, sizeof(bool) * FIELD_HEIGHT);
    Clear();
}

Field::~Field() {
}

Block Field::getBlockAt(int x, int y) {
    if(x >= 0 && x < FIELD_WIDTH && y >= 0 && y < FIELD_HEIGHT) {
        return field[x + (y * FIELD_WIDTH)];
    } else {
        return nullBlock;
    }
}

void Field::setBlockAt(int x, int y, bool ac, sf::Color col) {
    field[x + (y * FIELD_WIDTH)].active = ac;
    field[x + (y * FIELD_WIDTH)].color = col;
}

void Field::setBlockAt(int x, int y, Block b) {
    field[x + (y * FIELD_WIDTH)] = b;
}

void Field::Clear() {
    memset(field, 0, sizeof(Block) * (FIELD_WIDTH * FIELD_HEIGHT));
}

bool Field::CheckLineClear() {
    bool lc = false;
    //Check for which rows may have been cleared
    memset(clearedRows, false, sizeof(bool) * FIELD_HEIGHT);
    numClearedRows = 0;
    for(int i = 0; i < FIELD_HEIGHT; i++) {
        blocksInRow = 0;
        for(int j = 0; j < FIELD_WIDTH; j++) {
            if(getBlockAt(j, i).active) {
                blocksInRow++;
            }
        }
        if(blocksInRow >= FIELD_WIDTH) {
            clearedRows[i] = true;
            lc = true;
            numClearedRows++;
        }
    }
    return lc;
}

/*  Get rid of every row that was cleared,
    then move all cells above the cleared rows
    down by one for each row that was cleared
*/
void Field::RemoveClearedRows() {
    for(int i = 0; i < FIELD_HEIGHT; i++) {
        if(clearedRows[i]){
            for(int j = 0; j < FIELD_WIDTH; j++) {
                setBlockAt(j, i, nullBlock);
            }
            for(int j = i; j > 0; j--) {
                for(int k = 0; k < FIELD_WIDTH; k++) {
                    setBlockAt(k, j, getBlockAt(k, j - 1));
                }
            }
        }
    }
}