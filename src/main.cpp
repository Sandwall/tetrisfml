#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "game.hpp"

int main()
{
    srand(time(nullptr));
    Game game;
    return game.Run();
}