#include <iostream>

// #include "Vulkan.h"
#include "Material.h"
#include "catch_amalgamated.hpp"

int main(int argc, const char *const argv[])
{

    Material m("material1.mat");
    std::cout << m.properties[0];

    /*
    HelloTriangleApplication app;

    try
    {
        app.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
    */
    return utest_main(argc, argv);
}
