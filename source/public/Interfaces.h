#pragma once
// libs
#include <SFML/Graphics.hpp>


class IUpdatable
{
public:
    virtual void update(float deltaTime) = 0;
};


class IRenderable
{
public:
    virtual void render(sf::RenderWindow* renderWindow) = 0;
};
