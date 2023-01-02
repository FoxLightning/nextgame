#include "MGameInstance.h"
// project
#include "Helpers.h"
#include "Interfaces.h"
#include "MGameWorld.h"


MGameInstance::MGameInstance()
{
    gameConfig = new SGameConfig();
}

MGameInstance::~MGameInstance()
{
    delete gameConfig;
}

void MGameInstance::startLoop()
{
    MGameWorld* gameWorld = new MGameWorld();

    queueToUpdate.push_back(gameWorld);

    window = new sf::RenderWindow(sf::VideoMode(gameConfig->resolution.x, gameConfig->resolution.y), gameConfig->windowName);
    while (window->isOpen())
    {
        updateQueue(1.f);

        window->clear();
        renderQueue(window);
        window->display();
    }

    delete gameWorld;
}

sf::RenderWindow* MGameInstance::getWindow() const
{
    return window;
}

void MGameInstance::updateQueue(float deltaTime)
{
    for (IUpdatable* objectToUpdate : queueToUpdate)
    {
        objectToUpdate->update(0.f);
    }
}

void MGameInstance::renderQueue(sf::RenderWindow* renderWindow)
{
    for (IRenderable* objectToRender : queueToRender)
    {
        objectToRender->render(renderWindow);
    }
}
