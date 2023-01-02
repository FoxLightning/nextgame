#include "MGameInstance.h"
#include "Helpers.h"

MGameInstance* SGlobalContext::gameInstance = nullptr;


int main()
{
    SGlobalContext::gameInstance = new MGameInstance();
    SGlobalContext::gameInstance->startLoop();
    delete SGlobalContext::gameInstance;
    return 0;
}
