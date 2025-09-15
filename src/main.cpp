#include "core/EventBus.h"
#include "core/World.h"
#include "core/SimClock.h"
#include "physics/ExponentialAirDensityModel.h"
#include "physics/PerlinWindModel.h"
#include "physics/ImpulseCollisionResolver.h"
#include "systems/PhysicsSystem.h"
#include "systems/InputSystem.h"
#include "systems/VehicleControlSystem.h"
#include "platform/WinInputDevice.h"
#include "utils/PugiXmlParser.h"
#include "vehicles/DroneBuilder.h"
#include <iostream>
#include <chrono>
#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

int main()
{
    // SDL Init
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_Window* window = SDL_CreateWindow("Drone Sim", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(window);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 800.0/600.0, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    GLUquadric* quad = gluNewQuadric();
    float angle = 0.0f;

    // Simulation init
    EventBus eventBus;
    SimClock simClock(1.0f / 60.0f); // 60Hz physics
    World world(eventBus);

    // Concrete implementations of physics models
    std::unique_ptr<IAirDensityModel> airDensityModel = std::make_unique<ExponentialAirDensityModel>(1.225f, 8500.0f);
    std::unique_ptr<IWindModel> windModel = std::make_unique<PerlinWindModel>(5.0f, 100.0f, 10.0f, 12345);
    std::unique_ptr<ICollisionResolver> collisionResolver = std::make_unique<ImpulseCollisionResolver>(0.2f, 0.8f);

    // Concrete implementation of input device
    std::unique_ptr<IInputDevice> inputDevice = std::make_unique<WinInputDevice>();

    // Concrete implementation of XML parser
    std::unique_ptr<IXmlParser> xmlParser = std::make_unique<PugiXmlParser>();

    // Instantiate and inject systems
    world.addSystem(std::make_unique<PhysicsSystem>(eventBus, *airDensityModel, *windModel, *collisionResolver));
    world.addSystem(std::make_unique<InputSystem>(eventBus, *inputDevice));
    world.addSystem(std::make_unique<VehicleControlSystem>(eventBus));

    // Use builder to create entity
    // DroneBuilder droneBuilder(*xmlParser);
    // std::unique_ptr<Entity> drone = droneBuilder.build("configs/drone_default.xml", eventBus);
    // world.addEntity(std::move(drone));

    // Main simulation loop
    auto lastFrameTime = std::chrono::high_resolution_clock::now();
    while (true) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) goto end;
        }

        auto currentFrameTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> frameDeltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        simClock.tick(frameDeltaTime.count());
        while (simClock.shouldStepPhysics()) {
            world.update(simClock.getFixedTimestep());
        }

        // Rendering
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, -5.0f);
        glRotatef(angle, 0.0f, 1.0f, 0.0f);
        glColor3f(0.0f, 0.0f, 1.0f);
        gluSphere(quad, 1.0f, 20, 20);
        SDL_GL_SwapWindow(window);

        angle += 1.0f;
        std::cout << "Simulation step" << std::endl;
    }
end:
    gluDeleteQuadric(quad);
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
