#include <cstdlib>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "game.hpp"

int main(int argc, char** argv) {
    srand(time(nullptr));
    
    Game game;
    return game.Run();
}