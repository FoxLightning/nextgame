#pragma once
// libs
#include <SFML/Graphics.hpp>
// stl
#include <vector>
// incomplete
class IUpdatable;
class IRenderable;
struct SGameConfig;


class MGameInstance
{
public:
    MGameInstance();
    ~MGameInstance();

    void startLoop();

    sf::RenderWindow* getWindow() const;
private:
    void updateQueue(float deltaTime);
    void renderQueue(sf::RenderWindow* renderWindow);

    std::vector<IUpdatable*> queueToUpdate;
    std::vector<IRenderable*> queueToRender;

    SGameConfig* gameConfig;
    sf::RenderWindow* window;
};
