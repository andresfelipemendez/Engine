//
// Created by Andres on 27/06/22.
//

#ifndef ENGINE_GUI_H
#define ENGINE_GUI_H


#include <GLFW/glfw3.h>

class GUI {
public:
    bool show_demo_window = false;
    bool show_another_window = false;
    GUI();
    ~GUI();

    void Initialize();

    void Update();
};


#endif //ENGINE_GUI_H
