#include "App.h"

void App::run()
{
    initWindow();
    initRenderer();
    mainLoop();
    cleanup();
}

void App::initWindow() {}
void App::initRenderer() {}
void App::mainLoop() {}
void App::cleanup() {}