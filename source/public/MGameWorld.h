#pragma once
// project
#include "Interfaces.h"
// libs
#include "SFML/Graphics.hpp"
// stl
#include <vector>
// incomplete
class WObject;


class MGameWorld : public IUpdatable, public IRenderable
{
public:
    MGameWorld();
    ~MGameWorld();

    virtual void update(float deltaTime) override;
private:
    void render(sf::RenderWindow* renderWindow);

    std::vector<WObject*> worldObjects;
};
