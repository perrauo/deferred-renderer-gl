#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
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

    // Create an instance of the Engine class    

    auto renderer = std::make_unique<Renderer>();
    renderer->renderPasses.push_back(std::make_unique<RenderPass>("resources/framework/shaders/geometry.vert", "resources/framework/shaders/geometry.frag"));
    renderer->renderPasses.push_back(std::make_unique < RenderPass>("resources/framework/shaders/lighting.vert", "resources/framework/shaders/lighting.frag"));
    renderer->renderPasses.push_back(std::make_unique < RenderPass>("resources/framework/shaders/postprocess.vert", "resources/framework/shaders/postprocess.frag"));

    Engine engine(std::move(renderer));
    std::unique_ptr<Game> game = std::make_unique<Game>();
    engine.start(std::move(game));

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        engine.update();

        // Render here
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
