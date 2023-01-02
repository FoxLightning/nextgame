#include "MGameWorld.h"
// project
#include "MGameInstance.h"
#include "Helpers.h"
// libs
#include <SFML/Graphics.hpp>


MGameWorld::MGameWorld()
{
}

MGameWorld::~MGameWorld()
{

}

void MGameWorld::update(float deltaTime)
{
    sf::RenderWindow* window = SGlobalContext::gameInstance->getWindow();
}

void MGameWorld::render(sf::RenderWindow* window)
{
    /*
    for (IRenderable* objectToRender : queueToRender)
    {
        objectToRender->render(window);
    }
    */
}
