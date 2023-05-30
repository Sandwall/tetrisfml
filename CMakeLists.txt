cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)
project(tetrisfml)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

set(SFML_STATIC_LIBRARIES TRUE)

# Either uncomment this and change the path or 
# set it in the CMake cache or CMake GUI
# set(SFML_DIR "path/to/SFML/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS system window graphics audio network REQUIRED)

add_executable(tetrisfml
    "src/main.cpp" 
    "src/game.cpp"
    "src/player.cpp"
    "src/field.cpp"
    "src/tetramino.cpp"
)

target_link_libraries(tetrisfml sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/data $<TARGET_FILE_DIR:${PROJECT_NAME}>/data
)