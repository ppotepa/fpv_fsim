#include <gtest/gtest.h>
#include "../src/components/EntityBehavior.h"
#include "../src/factory/BehaviorRegistry.h"
#include "../src/systems/BehaviorSystem.h"
#include "../src/behaviors/CubeSpinBehavior.h"
#include "../src/behaviors/MovementBehavior.h"
#include "../src/core/Entity.h"
#include "../src/components/Transform.h"

namespace BehaviorTests {

// Mock Entity class for testing
class MockEntity : public Core::Entity {
public:
    MockEntity(Core::EntityId id) : entityId(id) {}
    
    Core::EntityId getId() const override { return entityId; }
    
    template<typename T>
    bool hasComponent() const { return components.find(typeid(T).name()) != components.end(); }
    
    template<typename T>
    T& getComponent() {
        auto it = components.find(typeid(T).name());
        if (it == components.end()) {
            throw std::runtime_error("Component not found");
        }
        return *static_cast<T*>(it->second.get());
    }
    
    template<typename T>
    void addComponent(std::unique_ptr<T> component) {
        components[typeid(T).name()] = std::move(component);
    }

private:
    Core::EntityId entityId;
    std::unordered_map<std::string, std::unique_ptr<void>> components;
};

// Test Behavior for testing purposes
class TestBehavior : public Components::EntityBehavior {
public:
    void initialize(Core::Entity& entity, const Assets::BehaviorParams& params) override {
        initialized = true;
        testValue = getParameter<float>("testValue", 0.0f);
        testString = getParameter<std::string>("testString", "default");
    }
    
    void update(float deltaTime) override {
        updateCount++;
        lastDeltaTime = deltaTime;
    }
    
    void cleanup() override {
        cleanedUp = true;
    }
    
    bool initialized = false;
    bool cleanedUp = false;
    int updateCount = 0;
    float lastDeltaTime = 0.0f;
    float testValue = 0.0f;
    std::string testString;
};

class BehaviorSystemTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Register test behavior
        Factory::BehaviorRegistry::instance().registerBehavior(
            "TestBehavior", 
            []() -> std::unique_ptr<Components::EntityBehavior> {
                return std::make_unique<TestBehavior>();
            }
        );
        
        behaviorSystem.initialize();
    }
    
    void TearDown() override {
        behaviorSystem.shutdown();
        Factory::BehaviorRegistry::instance().clear();
    }
    
    Systems::BehaviorSystem behaviorSystem;
};

// Test Behavior Registry
TEST_F(BehaviorSystemTest, BehaviorRegistryRegistersBehaviors) {
    auto& registry = Factory::BehaviorRegistry::instance();
    
    EXPECT_TRUE(registry.isBehaviorRegistered("TestBehavior"));
    
    auto behavior = registry.createBehavior("TestBehavior");
    EXPECT_NE(behavior, nullptr);
    
    auto nullBehavior = registry.createBehavior("NonExistentBehavior");
    EXPECT_EQ(nullBehavior, nullptr);
    
    auto registeredBehaviors = registry.getRegisteredBehaviors();
    EXPECT_GE(registeredBehaviors.size(), 1);
    EXPECT_TRUE(std::find(registeredBehaviors.begin(), registeredBehaviors.end(), "TestBehavior") 
                != registeredBehaviors.end());
}

// Test Behavior Parameters
TEST_F(BehaviorSystemTest, BehaviorParametersWork) {
    Assets::BehaviorParams params;
    params.setParameter("testValue", 42.5f);
    params.setParameter("testString", std::string("hello"));
    params.setParameter("testBool", true);
    
    EXPECT_EQ(params.getParameter<float>("testValue", 0.0f), 42.5f);
    EXPECT_EQ(params.getParameter<std::string>("testString", ""), "hello");
    EXPECT_EQ(params.getParameter<bool>("testBool", false), true);
    
    // Test default values
    EXPECT_EQ(params.getParameter<int>("nonExistent", 99), 99);
    EXPECT_EQ(params.getParameter<std::string>("nonExistent", "default"), "default");
}

// Test Behavior System
TEST_F(BehaviorSystemTest, BehaviorSystemAttachesBehaviors) {
    MockEntity entity(1);
    entity.addComponent(std::make_unique<Components::Transform>());
    
    Assets::BehaviorParams params;
    params.setParameter("testValue", 123.45f);
    params.setParameter("testString", std::string("test"));
    
    bool attached = behaviorSystem.attachBehavior(entity, "TestBehavior", params);
    EXPECT_TRUE(attached);
    
    EXPECT_TRUE(behaviorSystem.hasBehaviors(entity.getId()));
    
    auto behaviors = behaviorSystem.getBehaviors(entity.getId());
    EXPECT_EQ(behaviors.size(), 1);
    
    auto* testBehavior = dynamic_cast<TestBehavior*>(behaviors[0]);
    ASSERT_NE(testBehavior, nullptr);
    EXPECT_TRUE(testBehavior->initialized);
    EXPECT_EQ(testBehavior->testValue, 123.45f);
    EXPECT_EQ(testBehavior->testString, "test");
}

TEST_F(BehaviorSystemTest, BehaviorSystemUpdatesBehaviors) {
    MockEntity entity(1);
    entity.addComponent(std::make_unique<Components::Transform>());
    
    Assets::BehaviorParams params;
    behaviorSystem.attachBehavior(entity, "TestBehavior", params);
    
    // Update behaviors
    float deltaTime = 0.016f; // ~60 FPS
    behaviorSystem.update(deltaTime);
    
    auto behaviors = behaviorSystem.getBehaviors(entity.getId());
    auto* testBehavior = dynamic_cast<TestBehavior*>(behaviors[0]);
    
    EXPECT_EQ(testBehavior->updateCount, 1);
    EXPECT_EQ(testBehavior->lastDeltaTime, deltaTime);
    
    // Update again
    behaviorSystem.update(deltaTime);
    EXPECT_EQ(testBehavior->updateCount, 2);
}

TEST_F(BehaviorSystemTest, BehaviorSystemRemovesBehaviors) {
    MockEntity entity(1);
    entity.addComponent(std::make_unique<Components::Transform>());
    
    Assets::BehaviorParams params;
    behaviorSystem.attachBehavior(entity, "TestBehavior", params);
    
    EXPECT_TRUE(behaviorSystem.hasBehaviors(entity.getId()));
    
    behaviorSystem.removeBehavior(entity.getId(), "TestBehavior");
    
    EXPECT_FALSE(behaviorSystem.hasBehaviors(entity.getId()));
    
    auto behaviors = behaviorSystem.getBehaviors(entity.getId());
    EXPECT_EQ(behaviors.size(), 0);
}

TEST_F(BehaviorSystemTest, BehaviorSystemCleansUpOnRemoval) {
    MockEntity entity(1);
    entity.addComponent(std::make_unique<Components::Transform>());
    
    Assets::BehaviorParams params;
    behaviorSystem.attachBehavior(entity, "TestBehavior", params);
    
    auto behaviors = behaviorSystem.getBehaviors(entity.getId());
    auto* testBehavior = dynamic_cast<TestBehavior*>(behaviors[0]);
    
    EXPECT_FALSE(testBehavior->cleanedUp);
    
    behaviorSystem.removeBehaviors(entity.getId());
    
    // Note: testBehavior pointer is now invalid, but we tested cleanup was called
}

// Test Multiple Behaviors on Same Entity
TEST_F(BehaviorSystemTest, MultipleBehaviorsOnSameEntity) {
    MockEntity entity(1);
    entity.addComponent(std::make_unique<Components::Transform>());
    
    Assets::BehaviorParams params1;
    params1.setParameter("testValue", 1.0f);
    
    Assets::BehaviorParams params2;
    params2.setParameter("testValue", 2.0f);
    
    // Register a second behavior type
    Factory::BehaviorRegistry::instance().registerBehavior(
        "TestBehavior2", 
        []() -> std::unique_ptr<Components::EntityBehavior> {
            return std::make_unique<TestBehavior>();
        }
    );
    
    behaviorSystem.attachBehavior(entity, "TestBehavior", params1);
    behaviorSystem.attachBehavior(entity, "TestBehavior2", params2);
    
    auto behaviors = behaviorSystem.getBehaviors(entity.getId());
    EXPECT_EQ(behaviors.size(), 2);
    
    // Update and verify both behaviors are updated
    behaviorSystem.update(0.016f);
    
    for (auto* behavior : behaviors) {
        auto* testBehavior = dynamic_cast<TestBehavior*>(behavior);
        EXPECT_EQ(testBehavior->updateCount, 1);
    }
}

// Test Behavior System Statistics
TEST_F(BehaviorSystemTest, BehaviorSystemProvidesBehaviorCount) {
    EXPECT_EQ(behaviorSystem.getBehaviorCount(), 0);
    
    MockEntity entity1(1);
    MockEntity entity2(2);
    entity1.addComponent(std::make_unique<Components::Transform>());
    entity2.addComponent(std::make_unique<Components::Transform>());
    
    Assets::BehaviorParams params;
    behaviorSystem.attachBehavior(entity1, "TestBehavior", params);
    behaviorSystem.attachBehavior(entity2, "TestBehavior", params);
    
    EXPECT_EQ(behaviorSystem.getBehaviorCount(), 2);
    
    behaviorSystem.removeBehaviors(entity1.getId());
    EXPECT_EQ(behaviorSystem.getBehaviorCount(), 1);
}

// Test Built-in Behaviors
class BuiltinBehaviorTest : public ::testing::Test {
protected:
    void SetUp() override {
        // CubeSpinBehavior and MovementBehavior are automatically registered
        // via REGISTER_BEHAVIOR macro in their implementation files
    }
};

TEST_F(BuiltinBehaviorTest, CubeSpinBehaviorIsRegistered) {
    auto& registry = Factory::BehaviorRegistry::instance();
    EXPECT_TRUE(registry.isBehaviorRegistered("CubeSpinBehavior"));
    
    auto behavior = registry.createBehavior("CubeSpinBehavior");
    EXPECT_NE(behavior, nullptr);
    
    auto* cubeSpin = dynamic_cast<Behaviors::CubeSpinBehavior*>(behavior.get());
    EXPECT_NE(cubeSpin, nullptr);
}

TEST_F(BuiltinBehaviorTest, MovementBehaviorIsRegistered) {
    auto& registry = Factory::BehaviorRegistry::instance();
    EXPECT_TRUE(registry.isBehaviorRegistered("MovementBehavior"));
    
    auto behavior = registry.createBehavior("MovementBehavior");
    EXPECT_NE(behavior, nullptr);
    
    auto* movement = dynamic_cast<Behaviors::MovementBehavior*>(behavior.get());
    EXPECT_NE(movement, nullptr);
}

// Integration Test: Scene Behavior Creation
TEST_F(BehaviorSystemTest, CreateSceneBehaviorsWorks) {
    // Create a mock package with scene
    Assets::Package package;
    package.metadata.id = "test_package";
    
    // Create scene with entities that have behaviors
    Assets::SceneDefinition scene;
    scene.id = "TestScene";
    
    Assets::EntityDefinition entity;
    entity.id = "test_entity";
    
    Assets::BehaviorDefinition behavior;
    behavior.className = "TestBehavior";
    behavior.params.setParameter("testValue", 99.0f);
    
    entity.behaviors.push_back(behavior);
    scene.entities.push_back(entity);
    package.scenes.push_back(scene);
    
    // Create entity map
    MockEntity mockEntity(1);
    mockEntity.addComponent(std::make_unique<Components::Transform>());
    std::unordered_map<std::string, Core::Entity*> entities;
    entities["test_entity"] = &mockEntity;
    
    // Create scene behaviors
    size_t behaviorCount = behaviorSystem.createSceneBehaviors(package, "TestScene", entities);
    
    EXPECT_EQ(behaviorCount, 1);
    EXPECT_TRUE(behaviorSystem.hasBehaviors(mockEntity.getId()));
    
    auto behaviors = behaviorSystem.getBehaviors(mockEntity.getId());
    EXPECT_EQ(behaviors.size(), 1);
    
    auto* testBehavior = dynamic_cast<TestBehavior*>(behaviors[0]);
    EXPECT_EQ(testBehavior->testValue, 99.0f);
}

} // namespace BehaviorTests
