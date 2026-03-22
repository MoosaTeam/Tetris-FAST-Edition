cmake_minimum_required(VERSION 3.10)
project(Tetris_FAST_Edition VERSION 1.0)

# SFML 3 strictly requires C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enforce hardware acceleration and strict optimization for your i3 processor
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native")

# Find the SFML 3 library (Note the capitalized components)
find_package(SFML 3 COMPONENTS Graphics Window System Audio REQUIRED)

# List ALL your source files
add_executable(Tetris_FAST_Edition
    main.cpp
    Background.cpp
    Block.cpp
    BlueTile.cpp
    CyanTile.cpp
    Game.cpp
    GameOver.cpp
    Gameplay.cpp
    GreenTile.cpp
    Menu.cpp
    OrangeTile.cpp
    PauseScreen.cpp
    PurpleTile.cpp
    RedTile.cpp
    UI.cpp
    YellowTile.cpp
)

# SFML 3 strictly requires modern target namespaces
target_link_libraries(Tetris_FAST_Edition PRIVATE SFML::Graphics SFML::Window SFML::System SFML::Audio)

# --- ASSET COPYING AUTOMATION ---
add_custom_command(TARGET Tetris_FAST_Edition POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Fonts $<TARGET_FILE_DIR:Tetris_FAST_Edition>/Fonts
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Sounds $<TARGET_FILE_DIR:Tetris_FAST_Edition>/Sounds
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Textures $<TARGET_FILE_DIR:Tetris_FAST_Edition>/Textures
)
