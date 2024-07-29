#include "framework/engine.h"
#include "framework/entity.h"
#include "framework/renderer.h"
#include "framework/game.h"
#include "framework/light.h"

#include "GLFW/glfw3.h"

#include <iostream>
#include <fstream>
#include <boost/json.hpp>

namespace GhostGame::Framework
{    
    Engine::Engine()
    {
    }

    void Engine::loop()
    {
        // Loop until the user closes the window
        while (!glfwWindowShouldClose(window))
        {
            update();

            // Render here
            glClear(GL_COLOR_BUFFER_BIT);

            // Swap front and back buffers
            glfwSwapBuffers(window);

            // Poll for and process events
            glfwPollEvents();
        }

        glfwTerminate();
    }

    int Engine::setup()
    {
        // Initialize the library
        if (!glfwInit())
        {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            return -1;
        }

        // Create a windowed mode window and its OpenGL context

        std::ifstream file(RES("framework/config.json"));
        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        auto config = boost::json::parse(content);
        screenWidth = config.at("screenWidth").as_int64();
        screenHeight = config.at("screenHeight").as_int64();

        window = glfwCreateWindow(screenWidth, screenHeight, "Ghost Game", NULL, NULL);
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
    }

    void Engine::startGame(std::unique_ptr<IGame>&& game)
    {
        this->game = std::move(game);
        this->game->start(*this);
        this->pointLightMaterial = std::make_unique<Material>(Lights::PointLight::name, RES("framework/shaders/pointLight"));
        this->lambertMaterial = std::make_unique<Material>(Materials::Lambert::name, RES("framework/shaders/lambert"));

        for (auto& [typeidx, sys] : _systems)
        {
            for (auto& [id, entity] : _entities) {

                sys->start(*this, entity);
            }
        }
        for (auto& [id, entity] : _entities) {
            entity.hasStarted = true;
        }
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
        using namespace RenderPasses::Geometry;
        auto& geometryRenderPass = renderer->geometryRenderPass;
        static auto lightType = std::type_index(typeid(PointLightComponent));

        // Bind GBuffer
        glBindFramebuffer(GL_FRAMEBUFFER, renderer->gbuffer->gBuffer);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (auto& [typeidx, sys] : _systems)
        {
            if (typeidx == lightType) continue;
            for (auto& [id, entity] : _entities) {
                geometryRenderPass->material->setUniform(Uniforms::model, entity.transform.getMatrix());
                sys->draw(*this, entity, deltaTime);
            }
        }

        // Unbind GBuffer
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }


    void Engine::drawLights(float deltaTime)
    {
        auto& pointLightSys = getSystem<PointLightComponent>();
        for (auto& [id, entity] : _entities) {
            pointLightSys.draw(*this, entity, deltaTime);
        }
    }

    void Engine::update() {

        float currentTime = glfwGetTime();
        double deltaTime = currentTime - _lastTime;
        _lastTime = currentTime;       

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

        renderer->render(*this, deltaTime);
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
}