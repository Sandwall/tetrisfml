# TetriSFML
This is an open-source clone of Tetris written for the purpose of working on my game programming skills.

### Controls

- W: Hard Drop
- A: Fastfall
- S: Left
- D: Right
- Shift: Hold
- MB1/Left Arrow Key: Rotate Left
- MB2/Right Arrow Key: Rotate Right

### Rules
The player gets random tetraminos with which they must use to eliminate lines of blocks. The tetraminos can be oriented by rotating them left or right, or moving them left or right. They move down by one block on each game tick. Outside of a tick, they can be moved down with the Fastfall key.

The controls/input is built around the OS-native key repeat. Maybe custom repeat delays will be written later.

The game plays in an "Arcade-style" system based on levels, with increasing difficulty. As the levels go on, the time between the player's blocks' falling (time between game ticks) decreases until it hits a cap. From there it's a battle of stamina.

The game is capped to 60fps through SFML functions.

## Compilation
CMake is the build system generator. Make sure you have a minimum of CMake 3.20 in order to compile.

SFML 2.5.1 is the only dependency. Make sure you have the correct version for your compiler (this can be downloaded from the [sfml website](https://www.sfml-dev.org/download/sfml/2.5.1/)).

1. Clone the repository with ``git clone https://github.com/Sandwall/tetrisfml.git``
2. Enter the ``tetrisfml`` directory, create a ``build`` directory, and enter it. Run ``cmake .. -DSFML_DIR="path/to/SFML/lib/cmake/SFML"`` and replace "path/to/SFML/lib/cmake/SFML" with the directory that contains the SFML*.cmake files. Either this or you can just set the SFML_DIR variable through the CMake GUI. If you have 
3. Run ``cmake --build .``

## Timeline
Things to implement (in order):
- [x] Placing of tetraminos (sort of...)
- [x] Breaking lines of blocks
- [x] Fastfall
- [ ] Hard Drop
- [ ] Levels/Increasing Difficulty
- [ ] Polish?
    - [ ] Music
    - [ ] SFX
    - [ ] Animations
- [ ] Optimizations??
- [ ] Multiplayer/Networking???

## Contributing
I don't plan on taking contributions for this project, because it is a solo/personal project I'm using for learning.

## Credit
The font used is Pixellari, by Zacchary Dempsey-Plante (available on [dafont.com](https://www.dafont.com/pixellari.font)).

The main library used is SFML (Simple and Fast Multimedia Library), written by the SFML authors and community.