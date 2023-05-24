#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "block.hpp"
#include "field.hpp"

Field::Field() {
    memset(field, 0, sizeof(Block) * (10 * 20));
}

Field::~Field() {
}

Block Field::getBlockAt(int x, int y) {
    return field[x + (y * 10)];
}

void Field::Clear() {
    memset(field, 0, sizeof(Block) * (10 * 20));
}