#include "framework/engine.h"
#include "framework/entity.h"
#include "framework/renderer.h"
#include "framework/game.h"
#include "framework/light.h"
#include "framework/preprocessor.h"

#include "GLFW/glfw3.h"

#include <iostream>
#include <fstream>
#include <boost/json.hpp>

#include "GL/glew.h"
#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Experiment::Framework
{    
    Engine::Engine()
    {
    }

    void Engine::loop()
    {
        // Loop until the user closes the window
        while (!glfwWindowShouldClose(window))
        {
            float currentTime = glfwGetTime();
            double deltaTime = currentTime - _lastTime;
            _lastTime = currentTime;

            update(deltaTime);

            // Render here
            glClear(GL_COLOR_BUFFER_BIT);

            draw(deltaTime);

            // Swap front and back buffers
            glfwSwapBuffers(window);

            // Poll for and process events
            glfwPollEvents();
        }

        glfwTerminate();
    }

    int Engine::setupGl()
    {
        // Initialize the library
        if (!glfwInit())
        {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            return -1;
        }

        // Set GLFW window hints for OpenGL core profile
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // Request OpenGL version 4.x
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6); // Request OpenGL version 4.6
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Request core profile
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Make MacOS happy

        // Create a windowed mode window and its OpenGL context
        screenSize.x = config.at("screenWidth").as_int64();
        screenSize.y = config.at("screenHeight").as_int64();

        window = glfwCreateWindow(screenSize.x, screenSize.y, "Ghost Game", NULL, NULL);
        if (!window)
        {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return -1;
        }

        // Make the window's context current
        glfwMakeContextCurrent(window);

        // GLEW requires a valid OpenGL context to initialize properly. 
        // Therefore, you should create the window and its OpenGL context first, and then initialize GLEW.
        glewExperimental = GL_TRUE; // Needed for core profile
        if (glewInit() != GLEW_OK) {
            std::cerr << "Failed to initialize GLEW" << std::endl;
            return -1;
        }

        GLenum err = glGetError();
        if (err != GL_NO_ERROR) {
            std::cerr << "OpenGL error: " << err << std::endl;
        }

        const GLubyte* version = glGetString(GL_VERSION);
        if (version != NULL) {
            std::cout << "OpenGL Version: " << version << std::endl;
        }
        else {
            std::cout << "Failed to get OpenGL version." << std::endl;
        }

        // Capture the mouse cursor
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        // Set the key callback function
        glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
        });

        // regain mouse capture if click
        glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
        {
            if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
            {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            }
        });

        return 0;
    }

    int Engine::setup()
    {        
        // setup config
        std::ifstream file(RES("framework/config.json"));
        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        config = boost::json::parse(content);

        if (setupGl() != 0)
        {
            return -1;
        }
        // material setup before the game starts
        pointLightMaterial = std::make_unique<Material>(Lights::PointLight::name, RES("framework/shaders/pointLight"));
        //lambertGeomMaterial = std::make_unique<Material>(Materials::Lambert::name, RES("framework/shaders/lambertGeom"));
        //lambertLightMaterial = std::make_unique<Material>(Materials::Lambert::name, RES("framework/shaders/lambertLight"));
        //finalPassMaterial = std::make_unique<Material>(DeferredShading::FinalPass::name, RES("framework/shaders/finalPass"));
        return 0;
    }

    void Engine::startGame(std::unique_ptr<IGame>&& game)
    {
        this->game = std::move(game);
        programStack.push(0);
        gbuffer = std::make_shared<GBuffer::Resource>(std::make_unique<Material>(GBuffer::name, RES("framework/shaders/gbuffer")), screenSize);
        this->game->start(*this);
    }

    glm::vec2 Engine::getCursorPos() const
    {
        static double lastX = 0, lastY = 0;
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        return glm::vec2(x, y);
    }

    void Engine::drawEntities(float deltaTime)
    {
        using namespace Materials;

        for (auto& [typeidx, sys] : _systems)
        {
            for (auto& [id, entity] : _entities) {
                sys->draw(*this, entity, deltaTime);
            }
        }
    }


    void Engine::drawLights(float deltaTime)
    {
        using namespace Materials;
        
        for (auto& [typeidx, sys] : _systems)
        {
            for (auto& [id, entity] : _entities) {
                sys->drawLight(*this, entity, deltaTime);
            }
        }
    }

    void Engine::endDrawLights(float deltaTime)
    {
        for (auto& [typeidx, sys] : _systems)
        {
            for (auto& [id, entity] : _entities) {
                sys->endDrawLight(*this, entity, deltaTime);
            }
        }
    }

    void Engine::draw(float deltaTime)
    {
        using namespace DeferredShading;

        // Bind the GBuffer        
        using namespace GBuffer;
        
        EXP_SCOPED(FramebufferBinding binding(gbuffer.get()))
        {

            // Clear the color and depth buffers
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS);

            // Draw the entities
            drawEntities(deltaTime);

        }
        EXP_SCOPED(TextureBinding binding(gbuffer.get()))
        {
            // Draw the lights
            drawLights(deltaTime);
        }

        // you don't need to unbind the GBuffer's framebuffer when drawing the light pass, since you're reusing the GBuffer's textures.
        //finalPassMaterial->unbind(*this);

        // Bind the framebuffer you want to read from
        glBindFramebuffer(GL_READ_FRAMEBUFFER, gbuffer->frameBuffer);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); // Bind the default framebuffer (or another framebuffer) to write to
        glBlitFramebuffer(0, 0, screenSize.x, screenSize.y, 0, 0, screenSize.x, screenSize.y, GL_COLOR_BUFFER_BIT, GL_NEAREST); // Copy the content of the framebuffer to the default framebuffer
        glBindTexture(GL_TEXTURE_2D, (int)ReservedTextureSlot::ScreenTexture); // Bind the texture you want to write to
        glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 0, 0, screenSize.x, screenSize.y, 0); // Copy the framebuffer content to the texture

        //finalPassMaterial->setUniform(Uniforms::screenTexture, ReservedTextureSlot::ScreenTexture);
        //finalPassMaterial->bind(*this);        

        // Draw the quad
        drawQuad();

    }

    void Engine::update(float deltaTime) {

        std::vector<EntityId> entitiesToErase;
        std::vector<EntityId> entitiesToStart;


        for (auto& [id, entity] : _entities) {
            if (!entity.hasStarted)
            {
                for (auto& [typeidx, sys] : _systems)
                {
                    sys->start(*this, entity);
                }
                entity.hasStarted = true;
            }
        }
     
        for (auto& [typeidx, sys] : _systems)
        {
            for (auto& [id, entity] : _entities) {
                sys->update(*this, entity, deltaTime);
                if (entity.markedForDeletion) {
                    entitiesToErase.push_back(id);
                }
            }
        }

        game->update(*this, deltaTime);

        for (auto id : entitiesToErase)
        {
            _entities.erase(id);
        }
    }

    void Engine::stop() {
    }

    Entity& Engine::spawnEntity()
    {
        EntityId id = _nextEntityId++;
        auto& ent = _entities[id];
        ent.id = id;
        return ent;
    }

    void Engine::despawnEntity(EntityId id)
    {
        _entities.erase(id);
    }


    Entity& Engine::getEntity(EntityId id)
    {
        static Entity sInvalidEntity;

        auto it = _entities.find(id);
        if (it != _entities.end()) {
            return it->second;
        }
        else {
            return sInvalidEntity;
        }
    }

    void Engine::testDraw(float deltaTime) {
        static GLuint VAO = 0;
        static GLuint VBO;
        static GLuint EBO;
        static GLuint programId;
        static GLuint vertShaderId;
        static GLuint fragShaderId;

        if (!VAO) {
            // Create a Vertex Array Object (VAO)
            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);

            // Create a Vertex Buffer Object (VBO)
            glGenBuffers(1, &VBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

            // Create an Element Buffer Object (EBO)
            glGenBuffers(1, &EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

            // Specify the layout of the vertex data
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
            glEnableVertexAttribArray(0);

            // Create and compile shaders
            programId = glCreateProgram();
            vertShaderId = glCreateShader(GL_VERTEX_SHADER);
            const char* vertexShaderSourcePtr = vertexShaderSource;
            glShaderSource(vertShaderId, 1, &vertexShaderSourcePtr, nullptr);
            glCompileShader(vertShaderId);
            glAttachShader(programId, vertShaderId);

            fragShaderId = glCreateShader(GL_FRAGMENT_SHADER);
            const char* fragmentShaderSourcePtr = fragmentShaderSource;
            glShaderSource(fragShaderId, 1, &fragmentShaderSourcePtr, nullptr);
            glCompileShader(fragShaderId);
            glAttachShader(programId, fragShaderId);

            glLinkProgram(programId);
        }

        // Create a Model matrix
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));

        // Create a Projection matrix
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);

        // Get the locations of the 'model' and 'projection' uniform variables
        GLint modelLoc = glGetUniformLocation(programId, "model");
        GLint projLoc = glGetUniformLocation(programId, "projection");
        GLint viewLoc = glGetUniformLocation(programId, "view");       

        // Pass the matrices to the shader
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

        // Draw the cube
        glUseProgram(programId);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, sizeof(cubeIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
    }
}