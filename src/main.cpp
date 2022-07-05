#include <iostream>
#include "Platform.h"
#include "Renderer.h"
#include "GUI.h"
#include "Scene.h"
#include "Model.h"


int main()
{
    Platform platform;
    Renderer renderer;
    GUI gui;
    Scene scene;
    Model model;

    gui.Initialize();

	while (platform.isRunning()) {
        platform.Update();

        renderer.Render();
        gui.Update();
    }
	return 0;
}
