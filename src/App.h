#include "Renderer.h"

struct App
{
    Renderer renderer;
public:
    void run();
private:
    void initWindow();
    void initRenderer();
    void mainLoop();
    void cleanup();
};