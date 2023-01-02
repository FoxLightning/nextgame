#pragma once
// libs
#include <SFML/System.hpp>
// stl
#include <string>

class MGameInstance;


struct SGameConfig
{
    sf::Vector2i resolution = sf::Vector2i(800, 600);
    std::string windowName = "NextGame";
};

struct SGlobalContext
{
    static MGameInstance* gameInstance;
};
