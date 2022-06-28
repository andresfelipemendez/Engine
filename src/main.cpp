#include <iostream>
#include "Platform.h"
#include "Renderer.h"
#include "GUI.h"

int main()
{
    Platform platform;
    Renderer renderer;
    GUI gui;
    gui.Initialize();

	while (platform.isRunning()) {
        platform.Update();

        renderer.Render();
        gui.Update();
    }
	return 0;
}
