#include <iostream>
#include <GL/glew.h> // Glew before gl to prevent warning
#include <GLFW/glfw3.h>

#include "framework/engine.h"
#include "game/game.h"

int main()
{
    using namespace GhostGame;
    using namespace GhostGame::Framework;

    // Initialize the library
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        // Render here
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Create an instance of the Engine class
    Engine engine;
    std::unique_ptr<Game> game = std::make_unique<Game>();
    engine.start(std::move(game));

    glfwTerminate();
    return 0;
}
