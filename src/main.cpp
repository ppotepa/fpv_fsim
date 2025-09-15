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
#include <thread>

int main()
{
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
    float angle = 0.0f;
    while (true) {
        auto currentFrameTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> frameDeltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        simClock.tick(frameDeltaTime.count());
        while (simClock.shouldStepPhysics()) {
            world.update(simClock.getFixedTimestep());
        }

        // Rendering simulation of rotating Earth sphere
        std::cout << "Earth sphere rotating at angle " << angle << " degrees" << std::endl;
        angle += 1.0f;

        std::this_thread::sleep_for(std::chrono::milliseconds(16)); // ~60 FPS
    }
    return 0;
}
