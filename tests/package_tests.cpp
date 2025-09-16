#include <gtest/gtest.h>
#include "../src/assets/PackageManager.h"
#include "../src/assets/PackageParser.h"
#include "../src/assets/AssetRegistry.h"
#include "../src/core/PackageBootstrap.h"
#include <filesystem>
#include <fstream>

namespace PackageTests {

class PackageSystemTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create test directory structure
        testDir = std::filesystem::temp_directory_path() / "package_tests";
        std::filesystem::create_directories(testDir);
        std::filesystem::create_directories(testDir / "test_package");
        std::filesystem::create_directories(testDir / "test_package" / "assets" / "meshes");
        std::filesystem::create_directories(testDir / "test_package" / "assets" / "materials");
        
        // Create test package.xml
        createTestPackageXml();
        createTestAssetFiles();
    }
    
    void TearDown() override {
        // Cleanup test directory
        std::filesystem::remove_all(testDir);
    }
    
    void createTestPackageXml() {
        std::ofstream packageXml(testDir / "test_package" / "package.xml");
        packageXml << R"(<?xml version="1.0" encoding="UTF-8"?>
<package id="test_package" version="1.0.0" name="Test Package">
    <metadata>
        <description>Test package for unit testing</description>
        <author>Test Framework</author>
    </metadata>
    
    <dependencies>
        <dependency package="core" version="1.0.0" required="true" />
    </dependencies>
    
    <assets>
        <asset id="test_cube" type="mesh" path="assets/meshes/cube.obj" />
        <asset id="red_material" type="material" path="assets/materials/red.mat" />
        <asset id="test_texture" type="texture" path="assets/textures/test.png" />
    </assets>
    
    <scenes>
        <scene id="TestScene" name="Test Scene">
            <entities>
                <entity id="spinning_cube" name="Spinning Cube">
                    <transform position="0,0,0" rotation="0,0,0,1" scale="1,1,1" />
                    <mesh asset="test_cube" />
                    <material asset="red_material" />
                    <behavior codeBehind="CubeSpinBehavior">
                        <param name="speed" value="45.0" />
                        <param name="axisY" value="1.0" />
                    </behavior>
                </entity>
                
                <entity id="moving_object" name="Moving Object">
                    <transform position="5,0,0" rotation="0,0,0,1" scale="0.5,0.5,0.5" />
                    <mesh asset="test_cube" />
                    <behavior codeBehind="MovementBehavior">
                        <param name="type" value="linear" />
                        <param name="speed" value="2.0" />
                        <param name="directionX" value="1.0" />
                    </behavior>
                </entity>
            </entities>
        </scene>
    </scenes>
</package>)";
        packageXml.close();
    }
    
    void createTestAssetFiles() {
        // Create dummy asset files
        std::ofstream(testDir / "test_package" / "assets" / "meshes" / "cube.obj") << "# Test cube mesh\n";
        std::ofstream(testDir / "test_package" / "assets" / "materials" / "red.mat") << "# Test red material\n";
        std::ofstream(testDir / "test_package" / "assets" / "textures" / "test.png") << "# Test texture data\n";
    }
    
    std::filesystem::path testDir;
};

// Test Package Parser
TEST_F(PackageSystemTest, PackageParserLoadsValidPackage) {
    Assets::PackageParser parser;
    auto result = parser.loadPackage((testDir / "test_package" / "package.xml").string());
    
    EXPECT_TRUE(result.success);
    EXPECT_TRUE(result.errors.empty());
    EXPECT_EQ(result.package.metadata.id, "test_package");
    EXPECT_EQ(result.package.metadata.version, "1.0.0");
    EXPECT_EQ(result.package.metadata.name, "Test Package");
    EXPECT_EQ(result.package.assets.size(), 3);
    EXPECT_EQ(result.package.scenes.size(), 1);
    
    // Check asset details
    const auto* cubeAsset = result.package.findAsset("test_cube");
    ASSERT_NE(cubeAsset, nullptr);
    EXPECT_EQ(cubeAsset->type, Assets::AssetType::Mesh);
    EXPECT_EQ(cubeAsset->path, "assets/meshes/cube.obj");
    
    // Check scene details
    const auto* testScene = result.package.findScene("TestScene");
    ASSERT_NE(testScene, nullptr);
    EXPECT_EQ(testScene->entities.size(), 2);
    
    // Check entity with behavior
    const auto& spinningCube = testScene->entities[0];
    EXPECT_EQ(spinningCube.id, "spinning_cube");
    EXPECT_EQ(spinningCube.behaviors.size(), 1);
    EXPECT_EQ(spinningCube.behaviors[0].className, "CubeSpinBehavior");
    EXPECT_EQ(spinningCube.behaviors[0].params.getParameter<float>("speed", 0.0f), 45.0f);
}

TEST_F(PackageSystemTest, PackageParserHandlesInvalidXml) {
    // Create invalid XML file
    std::ofstream invalidXml(testDir / "invalid.xml");
    invalidXml << "<?xml version=\"1.0\"?>\n<invalid><unclosed>";
    invalidXml.close();
    
    Assets::PackageParser parser;
    auto result = parser.loadPackage((testDir / "invalid.xml").string());
    
    EXPECT_FALSE(result.success);
    EXPECT_FALSE(result.errors.empty());
}

// Test Package Manager
TEST_F(PackageSystemTest, PackageManagerLoadsPackage) {
    Assets::PackageManager manager;
    auto result = manager.loadPackage((testDir / "test_package" / "package.xml").string());
    
    EXPECT_TRUE(result.success);
    EXPECT_TRUE(manager.isPackageLoaded("test_package"));
    
    const auto* package = manager.getPackage("test_package");
    ASSERT_NE(package, nullptr);
    EXPECT_EQ(package->metadata.id, "test_package");
}

TEST_F(PackageSystemTest, PackageManagerDiscovery) {
    Assets::PackageManager manager;
    auto discoveryResult = manager.discoverPackages(testDir.string());
    
    EXPECT_TRUE(discoveryResult.errors.empty());
    EXPECT_EQ(discoveryResult.packagePaths.size(), 1);
    EXPECT_EQ(discoveryResult.packagePaths[0], (testDir / "test_package" / "package.xml").string());
}

TEST_F(PackageSystemTest, PackageManagerUnloadsPackage) {
    Assets::PackageManager manager;
    auto result = manager.loadPackage((testDir / "test_package" / "package.xml").string());
    EXPECT_TRUE(result.success);
    
    bool unloaded = manager.unloadPackage("test_package");
    EXPECT_TRUE(unloaded);
    EXPECT_FALSE(manager.isPackageLoaded("test_package"));
}

// Test Asset Registry
TEST_F(PackageSystemTest, AssetRegistryRegistersPackageAssets) {
    // Load package first
    Assets::PackageParser parser;
    auto parseResult = parser.loadPackage((testDir / "test_package" / "package.xml").string());
    ASSERT_TRUE(parseResult.success);
    
    // Register assets
    Assets::AssetRegistry registry;
    registry.initialize();
    registry.registerPackageAssets(parseResult.package);
    
    // Check if assets are registered
    auto assetsByPackage = registry.getAssetsByPackage("test_package");
    EXPECT_EQ(assetsByPackage.size(), 3);
    
    auto meshAssets = registry.getAssetsByType(Assets::AssetType::Mesh);
    EXPECT_GE(meshAssets.size(), 1);
    
    // Test asset resolution
    auto assetId = registry.resolveAssetReference("test_package", "test_cube");
    EXPECT_TRUE(assetId.has_value());
    
    const auto* assetInfo = registry.getAssetInfo(assetId.value());
    ASSERT_NE(assetInfo, nullptr);
    EXPECT_EQ(assetInfo->assetName, "test_cube");
    EXPECT_EQ(assetInfo->type, Assets::AssetType::Mesh);
    
    registry.shutdown();
}

// Test Bootstrap System
TEST_F(PackageSystemTest, BootstrapInitializesSuccessfully) {
    Core::PackageBootstrap bootstrap;
    Core::PackageBootstrap::BootstrapConfig config;
    config.packagesDirectory = testDir.string();
    config.requiredPackages = {"test_package"};
    config.enableHotReload = false;
    config.preloadAssets = false;
    
    bool initialized = bootstrap.initialize(config);
    EXPECT_TRUE(initialized);
    
    auto stats = bootstrap.getStats();
    EXPECT_EQ(stats.packagesLoaded, 1);
    
    // Test container access
    auto& container = bootstrap.getContainer();
    auto packageManager = container.resolve<Assets::PackageManager>();
    EXPECT_NE(packageManager, nullptr);
    EXPECT_TRUE(packageManager->isPackageLoaded("test_package"));
    
    bootstrap.shutdown();
}

// Test Asset ID Generation
TEST_F(PackageSystemTest, AssetIdGenerationIsConsistent) {
    std::string packageId = "test_package";
    std::string assetName = "test_cube";
    
    Assets::AssetId id1 = Assets::AssetIdGenerator::generateAssetId(packageId, assetName);
    Assets::AssetId id2 = Assets::AssetIdGenerator::generateAssetId(packageId, assetName);
    
    EXPECT_EQ(id1, id2); // Same inputs should produce same ID
    
    Assets::AssetId id3 = Assets::AssetIdGenerator::generateAssetId(packageId, "different_asset");
    EXPECT_NE(id1, id3); // Different inputs should produce different IDs
}

// Test Dependency Resolution
TEST_F(PackageSystemTest, DependencyValidationWorks) {
    // Create a package with dependencies
    std::filesystem::create_directories(testDir / "dependent_package");
    
    std::ofstream depPackageXml(testDir / "dependent_package" / "package.xml");
    depPackageXml << R"(<?xml version="1.0" encoding="UTF-8"?>
<package id="dependent_package" version="1.0.0" name="Dependent Package">
    <dependencies>
        <dependency package="test_package" version="1.0.0" required="true" />
    </dependencies>
    <assets></assets>
    <scenes></scenes>
</package>)";
    depPackageXml.close();
    
    Assets::PackageManager manager;
    
    // Load dependency first
    auto result1 = manager.loadPackage((testDir / "test_package" / "package.xml").string());
    EXPECT_TRUE(result1.success);
    
    // Load dependent package
    auto result2 = manager.loadPackage((testDir / "dependent_package" / "package.xml").string());
    EXPECT_TRUE(result2.success);
    
    // Test load order calculation
    auto loadOrder = manager.getLoadOrder({"test_package", "dependent_package"});
    EXPECT_EQ(loadOrder.size(), 2);
    EXPECT_EQ(loadOrder[0], "test_package"); // Dependency should come first
    EXPECT_EQ(loadOrder[1], "dependent_package");
}

} // namespace PackageTests
