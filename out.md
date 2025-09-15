#include &lt; iostream & gt;

int main(int argc, char *argv[])
{
    std::cout &lt;
    &lt;
    "Asset Compiler CLI Tool" & lt;
    &lt;
    std::endl;
    // TODO: Implement XML -&gt; IR -&gt; cooked binaries
    return 0;
}
#include &lt; iostream & gt;

int main(int argc, char *argv[])
{
    std::cout &lt;
    &lt;
    "Codegen Tool for Asset IDs" & lt;
    &lt;
    std::endl;
    // TODO: Generate headers/tables for AssetId mappings
    return 0;
}
<?xml version="1.0" encoding="UTF-8"?>
<unified-flight-vehicle schema-version="1.0" units="si"
    xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
    xsi:noNamespaceSchemaLocation="unified-flight-vehicle.xsd">

  <vehicles>
    <flywoo-explorer-lr4-o4-pro>
      <name>Flywoo Explorer LR4 O4 PRO</name>
      <vehicle-type>multirotor</vehicle-type>
      <subtype>quad-x</subtype>
      <mass-kg>0.178</mass-kg>
      <mass-properties>
        <cg-location-m>0.0 0.0 0.0</cg-location-m>
        <inertia-tensor-kg-m2>
          <row>0.0032 0.0 0.0</row>
          <row>0.0 0.0032 0.0</row>
          <row>0.0 0.0 0.0055</row>
        </inertia-tensor-kg-m2>
      </mass-properties>
      <structure-ref>lr4-frame</structure-ref>
      <energy>
        <mount ref="xt30-4s-lipo-850" id="battery-top">
          <location-m>0.0 0.0 -0.02</location-m>
        </mount>
      </energy>
      <propulsion-group>
        <propulsion id="front-left">
          <rotor-ref>lr4-rotor-unit</rotor-ref>
          <rotation-direction>cw</rotation-direction>
          <location-m>0.09 -0.09 0.0</location-m>
        </propulsion>
        <propulsion id="front-right">
          <rotor-ref>lr4-rotor-unit</rotor-ref>
          <rotation-direction>ccw</rotation-direction>
          <location-m>0.09 0.09 0.0</location-m>
        </propulsion>
        <propulsion id="rear-left">
          <rotor-ref>lr4-rotor-unit</rotor-ref>
          <rotation-direction>ccw</rotation-direction>
          <location-m>-0.09 -0.09 0.0</location-m>
        </propulsion>
        <propulsion id="rear-right">
          <rotor-ref>lr4-rotor-unit</rotor-ref>
          <rotation-direction>cw</rotation-direction>
          <location-m>-0.09 0.09 0.0</location-m>
        </propulsion>
      </propulsion-group>
      <avionics>
        <fc-ref>goku-f722-mini</fc-ref>
      </avionics>
      <sensors>
        <sensor-ref>imu-basic</sensor-ref>
        <sensor-ref>mag-compass</sensor-ref>
        <sensor-ref>baro-press</sensor-ref>
        <sensor-ref>gm10-mini-v3</sensor-ref>
      </sensors>
      <landing-gear-ref>quad-skids</landing-gear-ref>
      <performance-envelope>
        <vne-ms>40</vne-ms>
        <service-ceiling-m>4500</service-ceiling-m>
        <max-wind-mps>12</max-wind-mps>
      </performance-envelope>
      <control-map>
        <map input="roll">
          <effector target="front-left" type="throttle" scale="-1"/>
          <effector target="front-right" type="throttle" scale="1"/>
          <effector target="rear-left" type="throttle" scale="-1"/>
          <effector target="rear-right" type="throttle" scale="1"/>
        </map>
        <map input="pitch">
          <effector target="front-left" type="throttle" scale="-1"/>
          <effector target="front-right" type="throttle" scale="-1"/>
          <effector target="rear-left" type="throttle" scale="1"/>
          <effector target="rear-right" type="throttle" scale="1"/>
        </map>
        <map input="yaw">
          <effector target="front-left" type="throttle" scale="1"/>
          <effector target="front-right" type="throttle" scale="-1"/>
          <effector target="rear-left" type="throttle" scale="-1"/>
          <effector target="rear-right" type="throttle" scale="1"/>
        </map>
        <map input="throttle">
          <effector target="front-left" type="throttle" scale="1"/>
          <effector target="front-right" type="throttle" scale="1"/>
          <effector target="rear-left" type="throttle" scale="1"/>
          <effector target="rear-right" type="throttle" scale="1"/>
        </map>
      </control-map>
    </flywoo-explorer-lr4-o4-pro>
  </vehicles>
</unified-flight-vehicle>
<?xml version="1.0" encoding="UTF-8"?>
<unified-flight-vehicle schema-version="1.0" units="si"
    xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
    xsi:noNamespaceSchemaLocation="unified-flight-vehicle.xsd">

  <vehicles>
    <generic-airliner>
      <name>Twin-Engine Airliner (Generic)</name>
      <vehicle-type>fixed-wing</vehicle-type>
      <mass-kg>65000</mass-kg>
      <mass-properties>
        <cg-location-m>15.0 0.0 0.0</cg-location-m>
        <inertia-tensor-kg-m2>
          <row>4800000 0 0</row>
          <row>0 29000000 0</row>
          <row>0 0 33000000</row>
        </inertia-tensor-kg-m2>
      </mass-properties>
      <reference-geometry>
        <s-ref-m2>122.6</s-ref-m2>
        <b-ref-m>35.8</b-ref-m>
        <c-ref-m>3.6</c-ref-m>
      </reference-geometry>
      <surfaces>
        <surface id="aileron-left" surface-ref="aileron-small" actuator-ref="hydraulic-jack-large">
          <location-m>10.0 -16.0 0.5</location-m>
        </surface>
        <surface id="aileron-right" surface-ref="aileron-small" actuator-ref="hydraulic-jack-large">
          <location-m>10.0 16.0 0.5</location-m>
        </surface>
        <surface id="elevator" surface-ref="elevator-medium" actuator-ref="hydraulic-jack-large">
          <location-m>-20.0 0.0 2.0</location-m>
        </surface>
        <surface id="rudder" surface-ref="rudder-medium" actuator-ref="hydraulic-jack-large">
          <location-m>-19.0 0.0 5.0</location-m>
        </surface>
      </surfaces>
      <engines>
        <engine id="left-engine" propulsion-ref="turbofan-120kn">
          <location-m>3.0 -6.0 -1.5</location-m>
          <gimbal-deg>0 0</gimbal-deg>
        </engine>
        <engine id="right-engine" propulsion-ref="turbofan-120kn">
          <location-m>3.0 6.0 -1.5</location-m>
          <gimbal-deg>0 0</gimbal-deg>
        </engine>
      </engines>
      <landing-gear-ref>tricycle-retract</landing-gear-ref>
      <avionics>
        <fcc-ref>airliner-fcc</fcc-ref>
      </avionics>
      <performance-envelope>
        <vne-ms>250</vne-ms>
        <mach-max>0.86</mach-max>
        <service-ceiling-m>13000</service-ceiling-m>
      </performance-envelope>
      <drag-polar>
        <cd0>0.022</cd0>
        <k>0.045</k>
      </drag-polar>
      <lift-curve>
        <cl-alpha-per-rad>5.5</cl-alpha-per-rad>
        <cl0>0.2</cl0>
      </lift-curve>
      <control-map>
        <map input="roll">
          <effector target="aileron-left" type="deflection-deg" scale="-1"/>
          <effector target="aileron-right" type="deflection-deg" scale="1"/>
        </map>
        <map input="pitch">
          <effector target="elevator" type="deflection-deg" scale="1"/>
        </map>
        <map input="yaw">
          <effector target="rudder" type="deflection-deg" scale="1"/>
        </map>
        <map input="throttle">
          <effector target="left-engine" type="throttle" scale="1"/>
          <effector target="right-engine" type="throttle" scale="1"/>
        </map>
      </control-map>
    </generic-airliner>
  </vehicles>
</unified-flight-vehicle>
<?xml version="1.0" encoding="UTF-8"?>
<unified-flight-vehicle schema-version="1.0" units="si"
    xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
    xsi:noNamespaceSchemaLocation="unified-flight-vehicle.xsd">

  <vehicles>
    <generic-airliner>
      <name>Twin-Engine Airliner (Generic)</name>
      <vehicle-type>fixed-wing</vehicle-type>
      <mass-kg>65000</mass-kg>
      <mass-properties>
        <cg-location-m>15.0 0.0 0.0</cg-location-m>
        <inertia-tensor-kg-m2>
          <row>4800000 0 0</row>
          <row>0 29000000 0</row>
          <row>0 0 33000000</row>
        </inertia-tensor-kg-m2>
      </mass-properties>
      <reference-geometry>
        <s-ref-m2>122.6</s-ref-m2>
        <b-ref-m>35.8</b-ref-m>
        <c-ref-m>3.6</c-ref-m>
      </reference-geometry>
      <surfaces>
        <surface id="aileron-left" surface-ref="aileron-small" actuator-ref="hydraulic-jack-large">
          <location-m>10.0 -16.0 0.5</location-m>
        </surface>
        <surface id="aileron-right" surface-ref="aileron-small" actuator-ref="hydraulic-jack-large">
          <location-m>10.0 16.0 0.5</location-m>
        </surface>
        <surface id="elevator" surface-ref="elevator-medium" actuator-ref="hydraulic-jack-large">
          <location-m>-20.0 0.0 2.0</location-m>
        </surface>
        <surface id="rudder" surface-ref="rudder-medium" actuator-ref="hydraulic-jack-large">
          <location-m>-19.0 0.0 5.0</location-m>
        </surface>
      </surfaces>
      <engines>
        <engine id="left-engine" propulsion-ref="turbofan-120kn">
          <location-m>3.0 -6.0 -1.5</location-m>
          <gimbal-deg>0 0</gimbal-deg>
        </engine>
        <engine id="right-engine" propulsion-ref="turbofan-120kn">
          <location-m>3.0 6.0 -1.5</location-m>
          <gimbal-deg>0 0</gimbal-deg>
        </engine>
      </engines>
      <landing-gear-ref>tricycle-retract</landing-gear-ref>
      <avionics>
        <fcc-ref>airliner-fcc</fcc-ref>
      </avionics>
      <performance-envelope>
        <vne-ms>250</vne-ms>
        <mach-max>0.86</mach-max>
        <service-ceiling-m>13000</service-ceiling-m>
      </performance-envelope>
      <drag-polar>
        <cd0>0.022</cd0>
        <k>0.045</k>
      </drag-polar>
      <lift-curve>
        <cl-alpha-per-rad>5.5</cl-alpha-per-rad>
        <cl0>0.2</cl0>
      </lift-curve>
      <control-map>
        <map input="roll">
          <effector target="aileron-left" type="deflection-deg" scale="-1"/>
          <effector target="aileron-right" type="deflection-deg" scale="1"/>
        </map>
        <map input="pitch">
          <effector target="elevator" type="deflection-deg" scale="1"/>
        </map>
        <map input="yaw">
          <effector target="rudder" type="deflection-deg" scale="1"/>
        </map>
        <map input="throttle">
          <effector target="left-engine" type="throttle" scale="1"/>
          <effector target="right-engine" type="throttle" scale="1"/>
        </map>
      </control-map>
    </generic-airliner>
  </vehicles>
</unified-flight-vehicle>
&lt;?xml version="1.0" encoding="UTF-8"?&gt;
&lt;Package name="city_01"&gt;
    &lt;Assets&gt;
        &lt;Mesh id="building" path="meshes/building.obj" /&gt;
        &lt;Texture id="concrete" path="textures/concrete.png" /&gt;
        &lt;Parametric id="building_block" path="params/building_city_block.xml" /&gt;
    &lt;/Assets&gt;
    &lt;Dependencies&gt;
        &lt;Package ref="core" /&gt;
    &lt;/Dependencies&gt;
&lt;/Package&gt;
&lt;?xml version="1.0" encoding="UTF-8"?&gt;
&lt;ParametricAsset type="Building"&gt;
    &lt;Parameters&gt;
        &lt;Height value="50" /&gt;
        &lt;Width value="20" /&gt;
        &lt;Depth value="15" /&gt;
    &lt;/Parameters&gt;
    &lt;Material&gt;
        &lt;Diffuse r="0.5" g="0.5" b="0.5" /&gt;
    &lt;/Material&gt;
&lt;/ParametricAsset&gt;
<?xml version="1.0" encoding="UTF-8"?>
<materials>
    <!-- Earth Material - Blue ocean world -->
    <material id="EarthSurfaceMaterial" type="earth">
        <properties>
            <albedo r="0.2" g="0.4" b="0.9" a="1.0" />
            <roughness>0.8</roughness>
            <metallic>0.0</metallic>
            <toonSteps>6</toonSteps>
            <enableRimLighting>true</enableRimLighting>
            <rimColor r="0.8" g="0.9" b="1.0" />
            <rimStrength>1.0</rimStrength>
        </properties>
    </material>

    <!-- Atmosphere Material -->
    <material id="AtmosphereMaterial" type="atmosphere">
        <properties>
            <albedo r="0.5" g="0.7" b="1.0" a="0.3" />
            <roughness>0.0</roughness>
            <metallic>0.0</metallic>
            <toonSteps>3</toonSteps>
        </properties>
    </material>

    <!-- Cloud Material -->
    <material id="CloudMaterial" type="cloud">
        <properties>
            <albedo r="1.0" g="1.0" b="1.0" a="0.8" />
            <roughness>0.1</roughness>
            <metallic>0.0</metallic>
            <toonSteps>4</toonSteps>
        </properties>
    </material>

    <!-- Contrail Material -->
    <material id="ContrailMaterial" type="contrail">
        <properties>
            <albedo r="1.0" g="1.0" b="1.0" a="0.6" />
            <emission r="0.1" g="0.1" b="0.1" />
            <roughness>0.0</roughness>
            <metallic>0.0</metallic>
            <toonSteps>2</toonSteps>
        </properties>
    </material>
</materials>
<?xml version="1.0" encoding="UTF-8"?>
<!--
    Developer Package XML Configuration — SIMPLIFIED
    Adds a lightweight loading indicator scene using voxel cubes as the base primitive:
    - Globe made from voxel spheres with procedural textures
    - Six small procedural 32×32 textures (water, land, rock, cloud, aircraft body, aircraft wings)
    - Single directional light
    - Fixed cinematic camera
    - Aircraft made from voxel cubes orbiting on inclined elliptic path
    - Cloud groups made from voxel cubes that orbit and fade with lifecycle
    - ~1 MiB target memory footprint (tiny meshes, tiny textures, procedural animation)
-->
<package name="DeveloperPackage" version="1.2" description="Core developer debug assets and loading indicator scene.">

    <!--
        Dependencies:
        Basic engine systems and shader library assumed to be built into runtime.
    -->
    <dependencies>
        <!-- No additional deps; assumes core shader library + ECS components exist. -->
    </dependencies>

    <!--
        Asset Declarations:
        Simplified naming scheme using voxel cubes as base primitive.
        All shapes are constructed from voxel building blocks.
    -->
    <assets>
        <!-- ==== CONSOLE ASSETS (unchanged) =================================================== -->
        <asset type="font" id="ConsoleFont">
            <path>console/console_font.ttf</path>
            <properties size="16" antialiasing="true" />
        </asset>
        <asset type="texture" id="ConsoleBackgroundTexture">
            <path>console/console_background.png</path>
            <properties format="PNG" mipmaps="false" filter="linear" />
        </asset>

        <!-- ==== DEFAULT SPHERE SCENE ASSETS (unchanged) ================================== -->
        <asset type="material" id="EarthSurfaceMaterial">
            <shader_id>BasicShader</shader_id>
            <params>
                <albedo_texture>textures/earth_albedo.ktx2</albedo_texture>
                <normal_map>textures/earth_normal.ktx2</normal_map>
                <roughness>0.8</roughness>
                <metallic>0.0</metallic>
            </params>
        </asset>
        <asset type="material" id="AtmosphereLayer1Material">
            <shader_id>BasicShader</shader_id>
            <params>
                <albedo_color>0.6 0.8 1.0 0.3</albedo_color>
                <transparency>true</transparency>
            </params>
        </asset>
        <asset type="material" id="AtmosphereLayer2Material">
            <shader_id>BasicShader</shader_id>
            <params>
                <albedo_color>0.4 0.6 0.9 0.2</albedo_color>
                <transparency>true</transparency>
            </params>
        </asset>
        <asset type="material" id="CloudLayerMaterial">
            <shader_id>BasicShader</shader_id>
            <params>
                <albedo_color>1.0 1.0 1.0 0.8</albedo_color>
                <transparency>true</transparency>
            </params>
        </asset>
        <asset type="mesh_recipe" id="SphereRecipe">
            <generator>VoxelGenerator</generator>
            <params>
                <type>sphere</type>
                <subdivisions>3</subdivisions>
                <radius>1.0</radius>
            </params>
        </asset>
        <asset type="mesh_recipe" id="CloudRecipe">
            <generator>VoxelGenerator</generator>
            <params>
                <type>cube</type>
                <size>1.0</size>
                <subdivisions>1</subdivisions>
            </params>
        </asset>

        <!-- ==== SIMPLIFIED SHADERS ======================================================= -->
        <asset type="shader" id="BasicShader">
            <vertex_shader>shaders/basic.vert</vertex_shader>
            <fragment_shader>shaders/basic.frag</fragment_shader>
            <parameters>
                <uniform name="albedo_color" type="vec4" default="1.0 1.0 1.0 1.0"/>
                <uniform name="roughness" type="float" default="0.5"/>
                <uniform name="metallic" type="float" default="0.0"/>
            </parameters>
        </asset>
        <asset type="shader" id="CelShader">
            <vertex_shader>shaders/cel.vert</vertex_shader>
            <fragment_shader>shaders/cel.frag</fragment_shader>
            <parameters>
                <uniform name="band_count" type="int" default="4"/>
                <uniform name="band_smoothness" type="float" default="0.1"/>
                <uniform name="rim_power" type="float" default="2.0"/>
            </parameters>
        </asset>

        <!-- ==== SIMPLIFIED PROCEDURAL TEXTURES =========================================== -->
        <asset type="texture_generator" id="WaterTexture">
            <generator>ProceduralTextureGenerator</generator>
            <params>
                <type>flat_noise</type>
                <size>32</size>
                <seed>1001</seed>
                <color_primary>#0066CC</color_primary>
                <color_secondary>#004499</color_secondary>
                <noise_scale>4.0</noise_scale>
            </params>
        </asset>
        <asset type="texture_generator" id="LandTexture">
            <generator>ProceduralTextureGenerator</generator>
            <params>
                <type>flat_noise</type>
                <size>32</size>
                <seed>1002</seed>
                <color_primary>#228B22</color_primary>
                <color_secondary>#006400</color_secondary>
                <noise_scale>6.0</noise_scale>
            </params>
        </asset>
        <asset type="texture_generator" id="RockTexture">
            <generator>ProceduralTextureGenerator</generator>
            <params>
                <type>speckle</type>
                <size>32</size>
                <seed>1003</seed>
                <color_primary>#696969</color_primary>
                <color_secondary>#2F2F2F</color_secondary>
                <noise_scale>8.0</noise_scale>
            </params>
        </asset>
        <asset type="texture_generator" id="CloudTexture">
            <generator>ProceduralTextureGenerator</generator>
            <params>
                <type>dither</type>
                <size>32</size>
                <seed>1004</seed>
                <color_primary>#FFFFFF</color_primary>
                <color_secondary>#E0E0E0</color_secondary>
                <noise_scale>2.0</noise_scale>
            </params>
        </asset>
        <asset type="texture_generator" id="AircraftBodyTexture">
            <generator>ProceduralTextureGenerator</generator>
            <params>
                <type>solid_color</type>
                <size>32</size>
                <color_primary>#CC3333</color_primary>
            </params>
        </asset>
        <asset type="texture_generator" id="AircraftWingTexture">
            <generator>ProceduralTextureGenerator</generator>
            <params>
                <type>solid_color</type>
                <size>32</size>
                <color_primary>#808080</color_primary>
            </params>
        </asset>

        <!-- ==== SIMPLIFIED MATERIALS ===================================================== -->
        <asset type="material" id="WaterMaterial">
            <shader_id>CelShader</shader_id>
            <textures>
                <texture slot="diffuse" asset_id="WaterTexture"/>
            </textures>
            <params>
                <band_count>3</band_count>
                <band_smoothness>0.15</band_smoothness>
            </params>
        </asset>
        <asset type="material" id="LandMaterial">
            <shader_id>CelShader</shader_id>
            <textures>
                <texture slot="diffuse" asset_id="LandTexture"/>
            </textures>
            <params>
                <band_count>4</band_count>
                <band_smoothness>0.1</band_smoothness>
            </params>
        </asset>
        <asset type="material" id="RockMaterial">
            <shader_id>CelShader</shader_id>
            <textures>
                <texture slot="diffuse" asset_id="RockTexture"/>
            </textures>
            <params>
                <band_count>3</band_count>
                <band_smoothness>0.2</band_smoothness>
            </params>
        </asset>
        <asset type="material" id="CloudMaterial">
            <shader_id>CelShader</shader_id>
            <textures>
                <texture slot="diffuse" asset_id="CloudTexture"/>
            </textures>
            <params>
                <band_count>2</band_count>
                <band_smoothness>0.3</band_smoothness>
                <transparency>true</transparency>
            </params>
        </asset>
        <asset type="material" id="AircraftBodyMaterial">
            <shader_id>CelShader</shader_id>
            <textures>
                <texture slot="diffuse" asset_id="AircraftBodyTexture"/>
            </textures>
            <params>
                <band_count>2</band_count>
                <band_smoothness>0.05</band_smoothness>
            </params>
        </asset>
        <asset type="material" id="AircraftWingMaterial">
            <shader_id>CelShader</shader_id>
            <textures>
                <texture slot="diffuse" asset_id="AircraftWingTexture"/>
            </textures>
            <params>
                <band_count>2</band_count>
                <band_smoothness>0.05</band_smoothness>
            </params>
        </asset>

        <!-- ==== SIMPLIFIED MESH RECIPES (All Voxel Based) ================================ -->
        <asset type="mesh_recipe" id="GlobeRecipe">
            <generator>VoxelGenerator</generator>
            <params>
                <type>sphere</type>
                <subdivisions>4</subdivisions>
                <radius>2.0</radius>
            </params>
        </asset>
        <asset type="mesh_recipe" id="CubeRecipe">
            <generator>VoxelGenerator</generator>
            <params>
                <type>cube</type>
                <size>1.0</size>
                <subdivisions>1</subdivisions>
            </params>
        </asset>
        <asset type="mesh_recipe" id="AircraftRecipe">
            <generator>VoxelGenerator</generator>
            <params>
                <type>compound</type>
                <parts>
                    <!-- Fuselage -->
                    <part name="body">
                        <primitive type="cube"/>
                        <scale x="0.3" y="0.3" z="1.2"/>
                        <offset x="0.0" y="0.0" z="0.0"/>
                    </part>
                    <!-- Wings -->
                    <part name="wings">
                        <primitive type="cube"/>
                        <scale x="1.5" y="0.1" z="0.4"/>
                        <offset x="0.0" y="0.0" z="-0.2"/>
                    </part>
                    <!-- Tail -->
                    <part name="tail">
                        <primitive type="cube"/>
                        <scale x="0.1" y="0.4" z="0.2"/>
                        <offset x="0.0" y="0.0" z="0.5"/>
                    </part>
                </parts>
            </params>
        </asset>
    </assets>

    <!--
        Scene Configurations:
        Simplified to use "loading_indicator" type instead of "voxel_busy_indicator"
    -->
    <configurations>
        <scenes>
            <!-- Default Earth-like sphere scene (unchanged functionality) -->
            <scene name="DefaultSphereScene" type="default_sphere" budget_memory_mb="2">
                <description>A simple Earth-like sphere with atmospheric layers for basic world visualization.</description>
                
                <camera>
                    <position x="0" y="0" z="8"/>
                    <target x="0" y="0" z="0"/>
                    <fov>45</fov>
                </camera>
                
                <lighting>
                    <directional_light intensity="1.0">
                        <direction x="-0.5" y="-1.0" z="-0.3"/>
                        <color r="1.0" g="0.95" b="0.8" a="1.0"/>
                    </directional_light>
                    <ambient_light intensity="0.2">
                        <color r="0.3" g="0.4" z="0.6" a="1.0"/>
                    </ambient_light>
                </lighting>
                
                <entities>
                    <entity id="earth_sphere" name="Earth">
                        <transform>
                            <position x="0" y="0" z="0"/>
                            <scale x="2.0" y="2.0" z="2.0"/>
                        </transform>
                        <mesh>
                            <voxel_primitive type="sphere" subdivisions="4" radius="1.0"/>
                        </mesh>
                        <material shader="basic">
                            <texture slot="diffuse" file="textures/earth_albedo.ktx2"/>
                            <parameters>
                                <parameter name="roughness" value="0.8" type="float"/>
                            </parameters>
                        </material>
                        <components>
                            <rotation>
                                <axis x="0" y="1" z="0"/>
                                <speed>0.1</speed>
                            </rotation>
                        </components>
                    </entity>
                </entities>
            </scene>

            <!-- Simplified Loading Indicator Scene -->
            <scene name="LoadingIndicatorScene" type="loading_indicator" budget_memory_mb="1">
                <description>Lightweight loading indicator with orbiting aircraft and cloud groups using voxel primitives.</description>
                
                <camera>
                    <position x="4.5" y="3.2" z="6.8"/>
                    <target x="0" y="0" z="0"/>
                    <fov>35</fov>
                </camera>
                
                <lighting>
                    <directional_light intensity="1.2">
                        <direction x="-0.6" y="-0.8" z="-0.4"/>
                        <color r="1.0" g="0.95" b="0.85" a="1.0"/>
                    </directional_light>
                    <ambient_light intensity="0.3">
                        <color r="0.4" g="0.5" b="0.7" a="1.0"/>
                    </ambient_light>
                </lighting>
                
                <entities>
                    <!-- Central Globe -->
                    <entity id="globe" name="Globe">
                        <transform>
                            <position x="0" y="0" z="0"/>
                        </transform>
                        <mesh>
                            <voxel_primitive type="sphere" subdivisions="3" radius="2.0"/>
                        </mesh>
                        <material shader="cel">
                            <texture slot="diffuse" asset_id="LandTexture"/>
                            <parameters>
                                <parameter name="band_count" value="4" type="int"/>
                                <parameter name="band_smoothness" value="0.1" type="float"/>
                            </parameters>
                        </material>
                        <components>
                            <rotation>
                                <axis x="0" y="1" z="0"/>
                                <speed>0.05</speed>
                            </rotation>
                        </components>
                    </entity>

                    <!-- Orbiting Aircraft 1 -->
                    <entity id="aircraft1" name="Aircraft1">
                        <mesh>
                            <voxel_compound name="aircraft">
                                <part name="body">
                                    <primitive type="cube"/>
                                    <scale x="0.3" y="0.3" z="1.2"/>
                                </part>
                                <part name="wings">
                                    <primitive type="cube"/>
                                    <scale x="1.5" y="0.1" z="0.4"/>
                                    <offset x="0.0" y="0.0" z="-0.2"/>
                                </part>
                            </voxel_compound>
                        </mesh>
                        <material shader="cel">
                            <texture slot="diffuse" asset_id="AircraftBodyTexture"/>
                        </material>
                        <components>
                            <orbital radius="4.5" speed="0.3" eccentricity="0.15" inclination="15.0" enable_banking="true" max_bank_angle="25.0">
                                <center x="0" y="0" z="0"/>
                                <axis x="0" y="1" z="0"/>
                            </orbital>
                            <trail particle_count="30" lifetime="1.5" spawn_rate="15.0"/>
                        </components>
                    </entity>

                    <!-- Orbiting Aircraft 2 -->
                    <entity id="aircraft2" name="Aircraft2">
                        <mesh>
                            <voxel_compound name="aircraft">
                                <part name="body">
                                    <primitive type="cube"/>
                                    <scale x="0.3" y="0.3" z="1.2"/>
                                </part>
                                <part name="wings">
                                    <primitive type="cube"/>
                                    <scale x="1.5" y="0.1" z="0.4"/>
                                    <offset x="0.0" y="0.0" z="-0.2"/>
                                </part>
                            </voxel_compound>
                        </mesh>
                        <material shader="cel">
                            <texture slot="diffuse" asset_id="AircraftBodyTexture"/>
                        </material>
                        <components>
                            <orbital radius="5.2" speed="0.25" eccentricity="0.1" inclination="-20.0" phase_offset="180.0" enable_banking="true">
                                <center x="0" y="0" z="0"/>
                                <axis x="0" y="1" z="0"/>
                            </orbital>
                            <trail particle_count="25" lifetime="1.8" spawn_rate="12.0"/>
                        </components>
                    </entity>

                    <!-- Cloud Group Spawner -->
                    <entity id="cloud_spawner" name="CloudSpawner">
                        <transform>
                            <position x="0" y="0" z="0"/>
                        </transform>
                        <components>
                            <spawner spawn_rate="0.08" max_entities="8" entity_lifetime="25.0" spawn_radius="7.0"/>
                        </components>
                    </entity>
                </entities>
            </scene>
        </scenes>
    </configurations>
</package>
                <roughness value="0.8" />
                <metallic value="0.0" />
            </params>
        </asset>
        <asset type="material" id="AtmosphereLayer1Material">
            <shader_id>AtmosphereShader</shader_id> <!-- Assumes a dedicated atmospheric shader -->
            <params>
                <color r="0.2" g="0.4" b="0.7" a="0.15" /> <!-- Blueish, slightly transparent -->
                <blend_mode>AlphaBlend</blend_mode>
            </params>
        </asset>
        <asset type="material" id="AtmosphereLayer2Material">
            <shader_id>AtmosphereShader</shader_id>
            <params>
                <color r="0.3" g="0.5" b="0.8" a="0.05" /> <!-- Lighter blue, more transparent -->
                <blend_mode>AlphaBlend</blend_mode>
            </params>
        </asset>
        <asset type="material" id="CloudLayerMaterial">
            <shader_id>CloudVolumeShader</shader_id> <!-- Assumes a shader capable of rendering volumetric clouds -->
            <params>
                <color r="1.0" g="1.0" b="1.0" a="0.7" /> <!-- White, semi-transparent -->
                <!-- Placeholder for a pre-baked noise texture for clouds, located under /assets/packages/DeveloperPackage/textures/ -->
                <texture_id>textures/perlin_noise_cloud.ktx2</texture_id>
                <scroll_speed u="0.01" v="0.005" /> <!-- Simulates cloud movement -->
            </params>
        </asset>

        <!--
            Procedural Mesh Recipes. These define parameters for "param generators"
            that the asset compiler executes to produce final geometry or runtime procedural recipes.

        -->
        <asset type="mesh_recipe" id="SphereRecipe">
            <generator>ProceduralSphereGenerator</generator> <!-- Refers to a C++ generator function -->
            <params>
                <param name="radius_param" type="float" default_value="1.0" />
                <param name="segments_param" type="int" default_value="32" />
                <param name="invert_normals_param" type="bool" default_value="false" /> <!-- For rendering atmospheric layers from inside -->
            </params>
        </asset>
        <asset type="mesh_recipe" id="VoxelCloudRecipe">
            <generator>ProceduralVoxelCloudGenerator</generator> <!-- Refers to a C++ generator function -->
            <params>
                <param name="base_radius_param" type="float" default_value="1.0" />
                <param name="height_range_param" type="float" default_value="0.1" />
                <param name="noise_scale_param" type="float" default_value="0.01" />
                <param name="density_threshold_param" type="float" default_value="0.5" />
            </params>
        </asset>

        <!-- ==== NEW: CEL SHADER + RANDOM 32×32 TEXTURES ======================================= -->

        <!-- Minimal cel band shader (no outlines) -->
        <asset type="shader" id="CelBandShader">
            <path>shaders/cel_band_no_outline.shader</path>
            <params>
                <bands value="4"/>
                <outline_enabled value="false"/>
                <specular_mode value="off"/>
            </params>
        </asset>

        <!-- Six tiny textures generated at build/load (seed auto/random) -->
        <asset type="texture_generator" id="RndTex_Water32">
            <generator>FlatNoiseTextureGen</generator>
            <params width="32" height="32" base="#2B6FEA" noise_amp="0.05" seed="auto"/>
        </asset>
        <asset type="texture_generator" id="RndTex_Land32">
            <generator>FlatNoiseTextureGen</generator>
            <params width="32" height="32" base="#3BA15A" noise_amp="0.06" seed="auto"/>
        </asset>
        <asset type="texture_generator" id="RndTex_Rock32">
            <generator>SpeckleTextureGen</generator>
            <params width="32" height="32" base="#7C5B3A" speckle="#5F4A32" density="0.15" seed="auto"/>
        </asset>
        <asset type="texture_generator" id="RndTex_Cloud32">
            <generator>DitherTextureGen</generator>
            <params width="32" height="32" base="#F2F2F2" dither="0.04" seed="auto"/>
        </asset>
        <asset type="texture_generator" id="RndTex_Fuselage32">
            <generator>FlatNoiseTextureGen</generator>
            <params width="32" height="32" base="#E11D2E" noise_amp="0.03" seed="auto"/>
        </asset>
        <asset type="texture_generator" id="RndTex_Wings32">
            <generator>FlatNoiseTextureGen</generator>
            <params width="32" height="32" base="#B3B3B3" noise_amp="0.02" seed="auto"/>
        </asset>

        <!-- Cel materials that bind the tiny textures -->
        <asset type="material" id="Mat_Cel_Water">
            <shader_id>CelBandShader</shader_id>
            <params><albedo_texture>RndTex_Water32</albedo_texture></params>
        </asset>
        <asset type="material" id="Mat_Cel_Land">
            <shader_id>CelBandShader</shader_id>
            <params><albedo_texture>RndTex_Land32</albedo_texture></params>
        </asset>
        <asset type="material" id="Mat_Cel_Rock">
            <shader_id>CelBandShader</shader_id>
            <params><albedo_texture>RndTex_Rock32</albedo_texture></params>
        </asset>
        <asset type="material" id="Mat_Cel_Cloud">
            <shader_id>CelBandShader</shader_id>
            <params>
                <albedo_texture>RndTex_Cloud32</albedo_texture>
                <alpha_mode>Premultiplied</alpha_mode>
            </params>
        </asset>
        <asset type="material" id="Mat_Cel_Fuselage">
            <shader_id>CelBandShader</shader_id>
            <params><albedo_texture>RndTex_Fuselage32</albedo_texture></params>
        </asset>
        <asset type="material" id="Mat_Cel_Wings">
            <shader_id>CelBandShader</shader_id>
            <params><albedo_texture>RndTex_Wings32</albedo_texture></params>
        </asset>

        <!-- ==== NEW: TINY MESH RECIPES (low memory) ========================================== -->

        <!-- Low-poly globe (icosphere/cubesphere) -->
        <asset type="mesh_recipe" id="LowPolyGlobeRecipe">
            <generator>IcoSphereGenerator</generator>
            <params>
                <param name="radius" type="float" default_value="1.0" />
                <param name="subdiv" type="int" default_value="2" /> <!-- ~320 tris -->
                <param name="flat_shading" type="bool" default_value="true" />
            </params>
        </asset>

        <!-- Unit cube reused for voxel clouds & contrail -->
        <asset type="mesh_recipe" id="UnitCubeRecipe">
            <generator>CubeGenerator</generator>
            <params>
                <param name="size" type="float" default_value="1.0"/>
            </params>
        </asset>

        <!-- Low-poly aircraft (simple fuselage + wings + tail) -->
        <asset type="mesh_recipe" id="LowPolyAircraftRecipe">
            <generator>ProceduralAircraftGenerator</generator>
            <params>
                <param name="length" type="float" default_value="0.25" />
                <param name="fuselage_segments" type="int" default_value="6" />
                <param name="wing_span" type="float" default_value="0.22" />
                <param name="tail_span" type="float" default_value="0.12" />
                <param name="flat_shading" type="bool" default_value="true" />
            </params>
        </asset>

        <!-- Optional: procedural "land bumps" overlay using the same globe mesh with jitter mask -->
        <asset type="mesh_recipe" id="GlobeLandBumpsRecipe">
            <generator>SphericalPatchDisplaceGenerator</generator>
            <params>
                <param name="base_radius" type="float" default_value="1.0" />
                <param name="subdiv" type="int" default_value="2" />
                <param name="patch_count" type="int" default_value="24" />
                <param name="min_height" type="float" default_value="0.03" />
                <param name="max_height" type="float" default_value="0.06" />
                <param name="seed" type="int" default_value="-1" /> <!-- -1 = random -->
            </params>
        </asset>

        <!-- Paper Plane Materials & Mesh Recipe -->
        <asset type="material" id="PlaneFuselageMaterial">
            <shader_id>CelFlatShader</shader_id>
            <params>
                <color r="0.88" g="0.15" b="0.20" a="1.0" />
                <roughness value="0.9" />
                <metallic value="0.0" />
            </params>
        </asset>
        <asset type="material" id="PlaneWingMaterial">
            <shader_id>CelFlatShader</shader_id>
            <params>
                <color r="0.70" g="0.70" b="0.72" a="1.0" />
                <roughness value="0.95" />
                <metallic value="0.0" />
            </params>
        </asset>
        <asset type="mesh_recipe" id="PaperPlaneRecipe">
            <generator>ProceduralPaperPlaneGenerator</generator>
            <params>
                <param name="length_param" type="float" default_value="0.25" />
                <param name="wing_span_param" type="float" default_value="0.22" />
                <param name="fin_height_param" type="float" default_value="0.05" />
            </params>
        </asset>
    </assets>

    <!--
        Configuration Declarations:
        These define higher-level structures and system configurations, often referencing AssetIds.
        In release builds, these are prebaked into the .pak's PARAMS section.
    -->
    <configurations>
        <!-- ==== EXISTING CONFIGURATION (unchanged) =========================================== -->
        <!--
            Default Scene Configuration: The "Earth-like" sphere world.
            This SceneConfig would be provided to the WorldGenSystem if no other packages are found
            during the BootstrapSystem's initialization [previous conversation].
            The WorldGenSystem then instantiates entities and components based on this data.
            [previous conversation, BootstrapSystem, WorldGenSystem code examples]
        -->
        <scene_config id="DefaultSphereWorldScene" type="procedural_earth_like">
            <description>A basic Earth-like sphere with atmospheric layers and orbiting voxel clouds.</description>

            <!-- Earth Entity -->
            <entity name="Earth" entity_id="EarthEntityId">
                <component type="TransformC">
                    <position x="0.0" y="-6371000.0" z="0.0" /> <!-- Approximated Earth radius offset [previous conversation] -->
                    <orientation x="0.0" y="0.0" z="0.0" w="1.0" /> <!-- Identity quaternion -->
                </component>
                <component type="RenderableC">
                    <mesh_recipe_ref id="SphereRecipe">
                        <param name="radius_param" value="6371000.0" />
                        <param name="segments_param" value="64" />
                        <param name="invert_normals_param" value="false" />
                    </mesh_recipe_ref>
                    <material_ref id="EarthSurfaceMaterial" />
                </component>
            </entity>

            <!-- Atmospheric Layers -->
            <entity name="AtmosphereLayer1" entity_id="AtmosphereLayer1EntityId">
                <component type="TransformC">
                    <position x="0.0" y="-6371000.0" z="0.0" />
                    <orientation x="0.0" y="0.0" z="0.0" w="1.0" />
                </component>
                <component type="RenderableC">
                    <mesh_recipe_ref id="SphereRecipe">
                        <param name="radius_param" value="6371000.0 + 10000.0" /> <!-- 10km above surface [previous conversation] -->
                        <param name="segments_param" value="32" />
                        <param name="invert_normals_param" value="true" /> <!-- Render from inside the sphere -->
                    </mesh_recipe_ref>
                    <material_ref id="AtmosphereLayer1Material" />
                </component>
            </entity>
            <entity name="AtmosphereLayer2" entity_id="AtmosphereLayer2EntityId">
                <component type="TransformC">
                    <position x="0.0" y="-6371000.0" z="0.0" />
                    <orientation x="0.0" y="0.0" z="0.0" w="1.0" />
                </component>
                <component type="RenderableC">
                    <mesh_recipe_ref id="SphereRecipe">
                        <param name="radius_param" value="6371000.0 + 20000.0" /> <!-- 20km above surface [previous conversation] -->
                        <param name="segments_param" value="32" />
                        <param name="invert_normals_param" value="true" />
                    </mesh_recipe_ref>
                    <material_ref id="AtmosphereLayer2Material" />
                </component>
            </entity>

            <!-- Voxel Clouds orbiting Earth -->
            <entity name="VoxelClouds" entity_id="VoxelCloudsEntityId">
                <component type="TransformC">
                    <position x="0.0" y="-6371000.0" z="0.0" />
                    <orientation x="0.0" y="0.0" z="0.0" w="1.0" />
                </component>
                <component type="RenderableC">
                    <mesh_recipe_ref id="VoxelCloudRecipe">
                        <param name="base_radius_param" value="6371000.0 + 5000.0" /> <!-- Clouds start at 5km altitude [previous conversation] -->
                        <param name="height_range_param" value="5000.0" /> <!-- Clouds span 5km vertically [previous conversation] -->
                        <param name="noise_scale_param" value="0.0001" />
                        <param name="density_threshold_param" value="0.55" />
                    </mesh_recipe_ref>
                    <material_ref id="CloudLayerMaterial" />
                </component>
                <!-- Further components could define cloud movement/animation logic -->
            </entity>

            <!-- Low-Poly Paper Plane Entity (orbiting indicator) -->
            <entity name="PaperPlane" entity_id="PaperPlaneEntityId">
                <component type="TransformC">
                    <position x="0.0" y="-6371000.0" z="0.0" />
                    <orientation x="0.0" y="0.0" z="0.0" w="1.0" />
                </component>
                <component type="RenderableC">
                    <mesh_recipe_ref id="PaperPlaneRecipe">
                        <param name="length_param" value="0.25" />
                        <param name="wing_span_param" value="0.22" />
                        <param name="fin_height_param" value="0.05" />
                    </mesh_recipe_ref>
                    <material_ref id="PlaneFuselageMaterial" />
                    <!-- Wing material could be assigned by multi-material system in future; placeholder single material now -->
                </component>
            </entity>

            <!-- Environmental Physics Parameters for WorldGenSystem [30, 31, previous conversation] -->
            <env_physics_params>
                <gravity x="0.0" y="-9.81" z="0.0" /> <!-- Constant Earth gravity -->
                <air_density_model type="exponential">
                    <rho_0 value="1.225" /> <!-- Sea level density -->
                    <scale_height value="8500.0" /> <!-- Scale height for exponential approximation -->
                </air_density_model>
                <!-- Default Wind Model -->
                <wind_model type="constant">
                    <velocity x="5.0" y="0.0" z="0.0" /> <!-- Gentle constant wind in X direction -->
                </wind_model>
            </env_physics_params>
        </scene_config>

        <!-- ==== NEW: VOXEL BUSY INDICATOR SCENE CONFIGURATION ============================== -->
        <!--
            Compact busy indicator scene featuring low-poly voxel globe with cel-shaded 32×32 textures,
            orbital aircraft groups with procedural contrails, and voxel cloud patches.
            Memory budget: ~1MB total (texture + mesh + misc).
        -->
        <scene_config id="VoxelBusyIndicatorScene" type="voxel_busy_indicator">
            <description>Low-poly voxel busy indicator with orbiting aircraft and clouds</description>
            
            <!-- Performance constraints for busy indicator use case -->
            <memory_budget max_mb="1.0"/>
            <performance_targets>
                <max_draw_calls>25</max_draw_calls>
                <max_triangles>2000</max_triangles>
                <target_fps>60</target_fps>
            </performance_targets>

            <!-- ==== CORE GLOBE ENTITIES ================================================= -->
            <!-- Primary globe: water regions (base layer) -->
            <entity name="GlobeWater" entity_id="GlobeWaterEntityId">
                <component type="TransformC">
                    <position x="0.0" y="0.0" z="0.0" />
                    <orientation x="0.0" y="0.0" z="0.0" w="1.0" />
                </component>
                <component type="RenderableC">
                    <mesh_recipe_ref id="LowPolyGlobeRecipe">
                        <param name="radius" value="1.0" />
                        <param name="subdiv" value="2" /> <!-- ~320 triangles -->
                        <param name="flat_shading" value="true" />
                    </mesh_recipe_ref>
                    <material_ref id="Mat_Cel_Water" />
                </component>
                <component type="VoxelRegionC">
                    <param name="type" value="water" />
                    <param name="coverage" value="0.65" />
                </component>
            </entity>

            <!-- Land overlay: procedural land patches -->
            <entity name="GlobeLand" entity_id="GlobeLandEntityId">
                <component type="TransformC">
                    <position x="0.0" y="0.0" z="0.0" />
                    <orientation x="0.0" y="0.0" z="0.0" w="1.0" />
                    <scale x="1.001" y="1.001" z="1.001" /> <!-- Slight offset to avoid z-fighting -->
                </component>
                <component type="RenderableC">
                    <mesh_recipe_ref id="GlobeLandBumpsRecipe">
                        <param name="base_radius" value="1.0" />
                        <param name="subdiv" value="2" />
                        <param name="patch_count" value="24" />
                        <param name="min_height" value="0.03" />
                        <param name="max_height" value="0.06" />
                        <param name="seed" value="-1" /> <!-- Random -->
                    </mesh_recipe_ref>
                    <material_ref id="Mat_Cel_Land" />
                </component>
                <component type="VoxelRegionC">
                    <param name="type" value="land" />
                    <param name="coverage" value="0.30" />
                </component>
            </entity>

            <!-- Rock/mountain patches (smaller scale) -->
            <entity name="GlobeRocks" entity_id="GlobeRocksEntityId">
                <component type="TransformC">
                    <position x="0.0" y="0.0" z="0.0" />
                    <orientation x="0.0" y="0.0" z="0.0" w="1.0" />
                    <scale x="1.002" y="1.002" z="1.002" /> <!-- Slightly higher layer -->
                </component>
                <component type="RenderableC">
                    <mesh_recipe_ref id="GlobeLandBumpsRecipe">
                        <param name="base_radius" value="1.0" />
                        <param name="subdiv" value="2" />
                        <param name="patch_count" value="12" /> <!-- Fewer patches for rocks -->
                        <param name="min_height" value="0.05" />
                        <param name="max_height" value="0.08" />
                        <param name="seed" value="-1" />
                    </mesh_recipe_ref>
                    <material_ref id="Mat_Cel_Rock" />
                </component>
                <component type="VoxelRegionC">
                    <param name="type" value="rock" />
                    <param name="coverage" value="0.05" />
                </component>
            </entity>

            <!-- ==== ORBITAL AIRCRAFT GROUP 1 (high-speed outer orbit) ==================== -->
            <entity name="Aircraft_Group1_A" entity_id="Aircraft_Group1_A_Id">
                <component type="TransformC">
                    <position x="1.8" y="0.3" z="0.0" />
                    <orientation x="0.0" y="0.0" z="0.0" w="1.0" />
                    <scale x="0.6" y="0.6" z="0.6" />
                </component>
                <component type="RenderableC">
                    <mesh_recipe_ref id="LowPolyAircraftRecipe">
                        <param name="length" value="0.25" />
                        <param name="fuselage_segments" value="6" />
                        <param name="wing_span" value="0.22" />
                        <param name="tail_span" value="0.12" />
                        <param name="flat_shading" value="true" />
                    </mesh_recipe_ref>
                    <material_ref id="Mat_Cel_Fuselage" />
                </component>
                <component type="OrbitalC">
                    <param name="center_x" value="0.0" />
                    <param name="center_y" value="0.0" />
                    <param name="center_z" value="0.0" />
                    <param name="radius" value="1.8" />
                    <param name="speed" value="1.2" />
                    <param name="axis_x" value="0.1" />
                    <param name="axis_y" value="1.0" />
                    <param name="axis_z" value="0.05" />
                    <param name="phase_offset" value="0.0" />
                </component>
                <component type="ContrailC">
                    <param name="length" value="0.4" />
                    <param name="fade_time" value="2.0" />
                    <param name="material_ref" value="Mat_Cel_Cloud" />
                    <param name="cube_asset_ref" value="UnitCubeRecipe" />
                </component>
            </entity>

            <entity name="Aircraft_Group1_B" entity_id="Aircraft_Group1_B_Id">
                <component type="TransformC">
                    <position x="1.8" y="0.3" z="0.0" />
                    <orientation x="0.0" y="0.0" z="0.0" w="1.0" />
                    <scale x="0.55" y="0.55" z="0.55" />
                </component>
                <component type="RenderableC">
                    <mesh_recipe_ref id="LowPolyAircraftRecipe" />
                    <material_ref id="Mat_Cel_Wings" />
                </component>
                <component type="OrbitalC">
                    <param name="center_x" value="0.0" />
                    <param name="center_y" value="0.0" />
                    <param name="center_z" value="0.0" />
                    <param name="radius" value="1.8" />
                    <param name="speed" value="1.2" />
                    <param name="axis_x" value="0.1" />
                    <param name="axis_y" value="1.0" />
                    <param name="axis_z" value="0.05" />
                    <param name="phase_offset" value="0.33" />
                </component>
                <component type="ContrailC">
                    <param name="length" value="0.35" />
                    <param name="fade_time" value="1.8" />
                    <param name="material_ref" value="Mat_Cel_Cloud" />
                    <param name="cube_asset_ref" value="UnitCubeRecipe" />
                </component>
            </entity>

            <entity name="Aircraft_Group1_C" entity_id="Aircraft_Group1_C_Id">
                <component type="TransformC">
                    <position x="1.8" y="0.3" z="0.0" />
                    <orientation x="0.0" y="0.0" z="0.0" w="1.0" />
                    <scale x="0.5" y="0.5" z="0.5" />
                </component>
                <component type="RenderableC">
                    <mesh_recipe_ref id="LowPolyAircraftRecipe" />
                    <material_ref id="Mat_Cel_Fuselage" />
                </component>
                <component type="OrbitalC">
                    <param name="center_x" value="0.0" />
                    <param name="center_y" value="0.0" />
                    <param name="center_z" value="0.0" />
                    <param name="radius" value="1.8" />
                    <param name="speed" value="1.2" />
                    <param name="axis_x" value="0.1" />
                    <param name="axis_y" value="1.0" />
                    <param name="axis_z" value="0.05" />
                    <param name="phase_offset" value="0.66" />
                </component>
                <component type="ContrailC">
                    <param name="length" value="0.3" />
                    <param name="fade_time" value="1.5" />
                    <param name="material_ref" value="Mat_Cel_Cloud" />
                    <param name="cube_asset_ref" value="UnitCubeRecipe" />
                </component>
            </entity>

            <!-- ==== ORBITAL AIRCRAFT GROUP 2 (mid-speed middle orbit) ===================== -->
            <entity name="Aircraft_Group2_A" entity_id="Aircraft_Group2_A_Id">
                <component type="TransformC">
                    <position x="1.5" y="0.0" z="0.0" />
                    <orientation x="0.0" y="0.0" z="0.0" w="1.0" />
                    <scale x="0.7" y="0.7" z="0.7" />
                </component>
                <component type="RenderableC">
                    <mesh_recipe_ref id="LowPolyAircraftRecipe" />
                    <material_ref id="Mat_Cel_Wings" />
                </component>
                <component type="OrbitalC">
                    <param name="center_x" value="0.0" />
                    <param name="center_y" value="0.0" />
                    <param name="center_z" value="0.0" />
                    <param name="radius" value="1.5" />
                    <param name="speed" value="0.8" />
                    <param name="axis_x" value="0.05" />
                    <param name="axis_y" value="1.0" />
                    <param name="axis_z" value="0.2" />
                    <param name="phase_offset" value="0.25" />
                </component>
                <component type="ContrailC">
                    <param name="length" value="0.5" />
                    <param name="fade_time" value="2.5" />
                    <param name="material_ref" value="Mat_Cel_Cloud" />
                    <param name="cube_asset_ref" value="UnitCubeRecipe" />
                </component>
            </entity>

            <entity name="Aircraft_Group2_B" entity_id="Aircraft_Group2_B_Id">
                <component type="TransformC">
                    <position x="1.5" y="0.0" z="0.0" />
                    <orientation x="0.0" y="0.0" z="0.0" w="1.0" />
                    <scale x="0.65" y="0.65" z="0.65" />
                </component>
                <component type="RenderableC">
                    <mesh_recipe_ref id="LowPolyAircraftRecipe" />
                    <material_ref id="Mat_Cel_Fuselage" />
                </component>
                <component type="OrbitalC">
                    <param name="center_x" value="0.0" />
                    <param name="center_y" value="0.0" />
                    <param name="center_z" value="0.0" />
                    <param name="radius" value="1.5" />
                    <param name="speed" value="0.8" />
                    <param name="axis_x" value="0.05" />
                    <param name="axis_y" value="1.0" />
                    <param name="axis_z" value="0.2" />
                    <param name="phase_offset" value="0.75" />
                </component>
                <component type="ContrailC">
                    <param name="length" value="0.45" />
                    <param name="fade_time" value="2.2" />
                    <param name="material_ref" value="Mat_Cel_Cloud" />
                    <param name="cube_asset_ref" value="UnitCubeRecipe" />
                </component>
            </entity>

            <!-- ==== ORBITAL CLOUD GROUPS ============================================ -->
            <!-- Sparse voxel cloud patches on various orbits -->
            <entity name="CloudGroup_A1" entity_id="CloudGroup_A1_Id">
                <component type="TransformC">
                    <position x="1.3" y="0.4" z="0.2" />
                    <orientation x="0.0" y="0.0" z="0.0" w="1.0" />
                    <scale x="0.15" y="0.1" z="0.15" />
                </component>
                <component type="RenderableC">
                    <mesh_recipe_ref id="UnitCubeRecipe" />
                    <material_ref id="Mat_Cel_Cloud" />
                </component>
                <component type="OrbitalC">
                    <param name="center_x" value="0.0" />
                    <param name="center_y" value="0.0" />
                    <param name="center_z" value="0.0" />
                    <param name="radius" value="1.3" />
                    <param name="speed" value="0.3" />
                    <param name="axis_x" value="0.2" />
                    <param name="axis_y" value="1.0" />
                    <param name="axis_z" value="0.1" />
                    <param name="phase_offset" value="0.1" />
                </component>
                <component type="VoxelCloudC">
                    <param name="density" value="0.6" />
                    <param name="drift_speed" value="0.02" />
                </component>
            </entity>

            <entity name="CloudGroup_A2" entity_id="CloudGroup_A2_Id">
                <component type="TransformC">
                    <position x="1.3" y="0.4" z="0.2" />
                    <orientation x="0.0" y="0.0" z="0.0" w="1.0" />
                    <scale x="0.12" y="0.08" z="0.12" />
                </component>
                <component type="RenderableC">
                    <mesh_recipe_ref id="UnitCubeRecipe" />
                    <material_ref id="Mat_Cel_Cloud" />
                </component>
                <component type="OrbitalC">
                    <param name="center_x" value="0.0" />
                    <param name="center_y" value="0.0" />
                    <param name="center_z" value="0.0" />
                    <param name="radius" value="1.3" />
                    <param name="speed" value="0.3" />
                    <param name="axis_x" value="0.2" />
                    <param name="axis_y" value="1.0" />
                    <param name="axis_z" value="0.1" />
                    <param name="phase_offset" value="0.4" />
                </component>
                <component type="VoxelCloudC">
                    <param name="density" value="0.5" />
                    <param name="drift_speed" value="0.015" />
                </component>
            </entity>

            <entity name="CloudGroup_A3" entity_id="CloudGroup_A3_Id">
                <component type="TransformC">
                    <position x="1.3" y="0.4" z="0.2" />
                    <orientation x="0.0" y="0.0" z="0.0" w="1.0" />
                    <scale x="0.18" y="0.12" z="0.18" />
                </component>
                <component type="RenderableC">
                    <mesh_recipe_ref id="UnitCubeRecipe" />
                    <material_ref id="Mat_Cel_Cloud" />
                </component>
                <component type="OrbitalC">
                    <param name="center_x" value="0.0" />
                    <param name="center_y" value="0.0" />
                    <param name="center_z" value="0.0" />
                    <param name="radius" value="1.3" />
                    <param name="speed" value="0.3" />
                    <param name="axis_x" value="0.2" />
                    <param name="axis_y" value="1.0" />
                    <param name="axis_z" value="0.1" />
                    <param name="phase_offset" value="0.7" />
                </component>
                <component type="VoxelCloudC">
                    <param name="density" value="0.7" />
                    <param name="drift_speed" value="0.025" />
                </component>
            </entity>

            <entity name="CloudGroup_B1" entity_id="CloudGroup_B1_Id">
                <component type="TransformC">
                    <position x="1.6" y="-0.3" z="0.4" />
                    <orientation x="0.0" y="0.0" z="0.0" w="1.0" />
                    <scale x="0.2" y="0.14" z="0.16" />
                </component>
                <component type="RenderableC">
                    <mesh_recipe_ref id="UnitCubeRecipe" />
                    <material_ref id="Mat_Cel_Cloud" />
                </component>
                <component type="OrbitalC">
                    <param name="center_x" value="0.0" />
                    <param name="center_y" value="0.0" />
                    <param name="center_z" value="0.0" />
                    <param name="radius" value="1.6" />
                    <param name="speed" value="0.45" />
                    <param name="axis_x" value="0.15" />
                    <param name="axis_y" value="1.0" />
                    <param name="axis_z" value="-0.1" />
                    <param name="phase_offset" value="0.2" />
                </component>
                <component type="VoxelCloudC">
                    <param name="density" value="0.65" />
                    <param name="drift_speed" value="0.018" />
                </component>
            </entity>

            <entity name="CloudGroup_B2" entity_id="CloudGroup_B2_Id">
                <component type="TransformC">
                    <position x="1.6" y="-0.3" z="0.4" />
                    <orientation x="0.0" y="0.0" z="0.0" w="1.0" />
                    <scale x="0.14" y="0.1" z="0.14" />
                </component>
                <component type="RenderableC">
                    <mesh_recipe_ref id="UnitCubeRecipe" />
                    <material_ref id="Mat_Cel_Cloud" />
                </component>
                <component type="OrbitalC">
                    <param name="center_x" value="0.0" />
                    <param name="center_y" value="0.0" />
                    <param name="center_z" value="0.0" />
                    <param name="radius" value="1.6" />
                    <param name="speed" value="0.45" />
                    <param name="axis_x" value="0.15" />
                    <param name="axis_y" value="1.0" />
                    <param name="axis_z" value="-0.1" />
                    <param name="phase_offset" value="0.6" />
                </component>
                <component type="VoxelCloudC">
                    <param name="density" value="0.55" />
                    <param name="drift_speed" value="0.012" />
                </component>
            </entity>

            <!-- ==== CAMERA & LIGHTING ========================================== -->
            <!-- Slightly off-center camera for dynamic perspective -->
            <camera_config>
                <position x="0.5" y="1.8" z="3.2" />
                <look_at x="0.0" y="0.0" z="0.0" />
                <fov_degrees>45</fov_degrees>
                <near_plane>0.1</near_plane>
                <far_plane>50.0</far_plane>
                <!-- Optional: gentle camera sway for "floating" effect -->
                <auto_orbit enabled="true" speed="0.08" radius="3.5" axis_x="0" axis_y="1" axis_z="0" />
            </camera_config>

            <!-- Cel-friendly lighting: strong directional + minimal ambient -->
            <lighting_config>
                <primary_light type="directional">
                    <direction x="-0.6" y="-1.0" z="-0.4" />
                    <color r="1.0" g="0.95" b="0.85" />
                    <intensity>1.2</intensity>
                    <cast_shadows>false</cast_shadows> <!-- Keep performance high -->
                </primary_light>
                <ambient_light>
                    <color r="0.25" g="0.35" b="0.5" />
                    <intensity>0.15</intensity>
                </ambient_light>
                <!-- Optional: secondary rim light for better shape definition -->
                <rim_light type="directional">
                    <direction x="0.8" y="0.3" z="0.5" />
                    <color r="0.4" g="0.6" b="0.9" />
                    <intensity>0.3</intensity>
                </rim_light>
            </lighting_config>

            <!-- ==== RENDER ENVIRONMENT & PERFORMANCE ========================== -->
            <render_environment>
                <background_color r="0.08" g="0.12" b="0.18" a="1.0" />
                <fog enabled="false" /> <!-- Minimal overhead for busy indicator -->
                <post_processing enabled="false" /> <!-- Raw cel output -->
                <vsync enabled="true" />
            </render_environment>

            <!-- ==== ANIMATION SYSTEM ============================================ -->
            <!-- Global animation controller for orbital mechanics and effects -->
            <animation_system>
                <orbital_manager>
                    <!-- Manages all OrbitalC components -->
                    <global_time_scale>1.0</global_time_scale>
                    <pause_on_background>true</pause_on_background>
                </orbital_manager>
                <contrail_manager>
                    <!-- Manages all ContrailC components -->
                    <max_contrail_segments>8</max_contrail_segments>
                    <update_frequency_hz>30</update_frequency_hz>
                </contrail_manager>
                <cloud_drift_manager>
                    <!-- Manages VoxelCloudC drift effects -->
                    <global_wind_factor>1.0</global_wind_factor>
                    <turbulence_scale>0.1</turbulence_scale>
                </cloud_drift_manager>
            </animation_system>
        </scene_config>

        <!--
            Global Input Configuration (supporting overlay input):
            Defines key bindings relevant to the developer package.
            This configuration is processed by the InputSystem.
        -->
        <input_config id="GlobalDeveloperInput">
            <key_bindings>
                <binding action="ToggleDebugConsole" key_code="TILDE" device="Keyboard" /> <!-- Tilde key for console [previous conversation] -->
                <!-- Other debug-specific key bindings could be defined here -->
            </key_bindings>
        </input_config>

        <!--
            Overlay Configuration:
            Defines the debug console UI and other visual overlays.
            This configuration is consumed by the VisualizationSystem.
        -->
        <overlay_config id="DeveloperOverlay">
            <ui_element type="DebugConsole" visible_by_default="false">
                <font_asset_ref id="ConsoleFont" />
                <background_texture_asset_ref id="ConsoleBackgroundTexture" />
                <dimensions width_percent="80" height_percent="40" />
                <position x_percent="10" y_percent="5" />
                <color background="0x000000A0" text="0xFFFFFFFF" cursor="0xFF00FF" />
            </ui_element>

            <!-- Message displayed when no other packages are loaded [previous conversation, VisualizationSystem] -->
            <ui_element type="TextMessageOverlay" id="NoPackagesFoundDisplay" visible_by_default="false">
                <text_content>No packages found. Displaying default sphere world.</text_content>
                <font_asset_ref id="ConsoleFont" />
                <color text="0xFFFFAA00" background="0x00000080" />
                <position x_percent="50" y_percent="95" alignment="Center" />
            </ui_element>
        </overlay_config>

        <!-- Debug Component Configuration -->
        <component_config id="GlobalDebugComponent">
            <component type="DebugC">
                <param name="show_physics_wireframe" value="false" />
                <param name="show_wind_vectors" value="false" />
                <!-- Add other debug toggles here -->
            </component>
        </component_config>

    </configurations>

    <!--
        main.cpp Communication:
        The `main.cpp` (your application's entry point) does NOT directly parse this XML at runtime.
        Instead, it orchestrates the initialization of core systems that then consume the data defined here.
        This follows the principles of IoC and a "thin runtime, fat tools" approach.

        Here's how `main.cpp` facilitates the communication and utilizes this package's definitions:

        1.  Initializes Core Infrastructure: `main.cpp` first sets up the global IoC Container and EventBus.
            These are fundamental for Dependency Injection and Event-Driven Communication.

        2.  Invokes BootstrapSystem: `main.cpp` then creates and calls `BootstrapSystem::Init()`.
            This is the one-shot system responsible for initial world construction and asset loading.

        3.  Asset Loading Decision:
            *   In a **Release Build**: `BootstrapSystem` (via `AssetPackLoader`) attempts to memory-map
                pre-compiled `.pak` files (e.g., `DeveloperPackage.pak`, which is the binary representation of this XML).
                The data (assets, scene, input, overlay configs) are loaded into the `AssetRegistry`.
            *   In a **Debug Build**: `BootstrapSystem` configures the `AssetHotReloadSystem` to watch this XML file
                (and others) for changes. If changes occur, the XML is parsed, converted to an Intermediate
                Representation (IR), and built into a staging registry, which is atomically swapped at the
                end of the frame.

        4.  Default Scene Fallback:
            *   `BootstrapSystem` queries the `AssetRegistry`. **If no other packages are successfully loaded**,
                `BootstrapSystem` then instructs the `WorldGenSystem` (which receives the `DefaultSphereWorldScene`
                configuration from this package via IoC) to generate the "Earth-like" sphere world [previous conversation].
                It also emits a `NoPackagesFoundEvent` [previous conversation].

        5.  Input and Overlay Activation:
            *   The `InputSystem` (configured by `GlobalDeveloperInput` from this package) detects the **Tilde** (~) key press
                and publishes a `ConsoleToggleEvent` to the `EventBus` [previous conversation, 11].
            *   The `ConsoleSystem` and `VisualizationSystem` (configured by `DeveloperOverlay` from this package)
                subscribe to this `ConsoleToggleEvent`. When triggered, `VisualizationSystem` renders the debug console UI
                using the `ConsoleFont` and `ConsoleBackgroundTexture` assets. It also renders the "No packages found" message
                if the corresponding event was received [previous conversation, 12, 135].

        In essence, this XML is the **declarative source of truth** for configuration and asset definitions that drives
        the runtime behavior of the C++ systems and components, allowing for modularity and extensibility without
        modifying core C++ logic.
    -->
</package>
<?xml version="1.0" encoding="UTF-8"?>
<!--
  unified-flight-vehicle.xsd
  Full XSD for the "unified-flight-vehicle" XML format (SI units, kebab-case IDs)
-->
<xs:schema xmlns:xs="http://www.w3.org/2001/XMLSchema"
           elementFormDefault="qualified"
           attributeFormDefault="unqualified"
           version="1.0">

  <!-- ========= Common simple types ========= -->

  <!-- kebab-case identifier -->
  <xs:simpleType name="kebabIdType">
    <xs:restriction base="xs:string">
      <xs:pattern value="[a-z0-9]+(?:-[a-z0-9]+)*"/>
    </xs:restriction>
  </xs:simpleType>

  <!-- version pattern: e.g., 1.0 -->
  <xs:simpleType name="versionString">
    <xs:restriction base="xs:string">
      <xs:pattern value="[0-9]+\.[0-9]+"/>
    </xs:restriction>
  </xs:simpleType>

  <!-- whitespace-separated numeric vectors -->
  <xs:simpleType name="vector2Type">
    <xs:restriction base="xs:string">
      <xs:pattern value="\s*[-+0-9.eE]+\s+[-+0-9.eE]+\s*"/>
    </xs:restriction>
  </xs:simpleType>

  <xs:simpleType name="vector3Type">
    <xs:restriction base="xs:string">
      <xs:pattern value="\s*[-+0-9.eE]+\s+[-+0-9.eE]+\s+[-+0-9.eE]+\s*"/>
    </xs:restriction>
  </xs:simpleType>

  <!-- 3×3 matrix as three rows (each a vector3) -->
  <xs:complexType name="matrix3Type">
    <xs:sequence>
      <xs:element name="row" type="vector3Type" minOccurs="3" maxOccurs="3"/>
    </xs:sequence>
  </xs:complexType>

  <!-- ========= Enumerations ========= -->

  <xs:simpleType name="vehicleTypeEnum">
    <xs:restriction base="xs:string">
      <xs:enumeration value="multirotor"/>
      <xs:enumeration value="helicopter"/>
      <xs:enumeration value="fixed-wing"/>
      <xs:enumeration value="vtol-tiltrotor"/>
      <xs:enumeration value="vtol-tiltwing"/>
      <xs:enumeration value="vtol-lift-cruise"/>
      <xs:enumeration value="ornithopter"/>
      <xs:enumeration value="airship"/>
      <xs:enumeration value="rocket"/>
      <xs:enumeration value="spaceplane"/>
      <xs:enumeration value="glider"/>
    </xs:restriction>
  </xs:simpleType>

  <xs:simpleType name="propulsionTypeEnum">
    <xs:restriction base="xs:string">
      <xs:enumeration value="electric-motor"/>
      <xs:enumeration value="piston-prop"/>
      <xs:enumeration value="turboprop"/>
      <xs:enumeration value="turbofan"/>
      <xs:enumeration value="turbojet"/>
      <xs:enumeration value="ramjet"/>
      <xs:enumeration value="scramjet"/>
      <xs:enumeration value="solid-rocket"/>
      <xs:enumeration value="liquid-rocket"/>
      <xs:enumeration value="hybrid-rocket"/>
      <xs:enumeration value="propeller"/>
    </xs:restriction>
  </xs:simpleType>

  <xs:simpleType name="effectorTypeEnum">
    <xs:restriction base="xs:string">
      <xs:enumeration value="propeller"/>
      <xs:enumeration value="rotor"/>
      <xs:enumeration value="ducted-fan"/>
      <xs:enumeration value="control-surface"/>
      <xs:enumeration value="thrust-vector"/>
      <xs:enumeration value="reaction-control-jet"/>
      <xs:enumeration value="throttle"/>
      <xs:enumeration value="gimbal"/>
      <xs:enumeration value="flap"/>
      <xs:enumeration value="slat"/>
      <xs:enumeration value="spoiler"/>
      <xs:enumeration value="airbrake"/>
      <xs:enumeration value="speedbrake"/>
      <xs:enumeration value="thrust-reverser"/>
      <xs:enumeration value="collective"/>
      <xs:enumeration value="swashplate"/>
    </xs:restriction>
  </xs:simpleType>

  <xs:simpleType name="actuatorTypeEnum">
    <xs:restriction base="xs:string">
      <xs:enumeration value="servo"/>
      <xs:enumeration value="electric-linear"/>
      <xs:enumeration value="hydraulic"/>
      <xs:enumeration value="pneumatic"/>
      <xs:enumeration value="mechanical-linkage"/>
    </xs:restriction>
  </xs:simpleType>

  <xs:simpleType name="gearTypeEnum">
    <xs:restriction base="xs:string">
      <xs:enumeration value="nose-wheel"/>
      <xs:enumeration value="tail-wheel"/>
      <xs:enumeration value="skid"/>
      <xs:enumeration value="skate"/>
      <xs:enumeration value="float"/>
      <xs:enumeration value="skis"/>
      <xs:enumeration value="retractable"/>
      <xs:enumeration value="fixed"/>
    </xs:restriction>
  </xs:simpleType>

  <xs:simpleType name="rotationDirectionEnum">
    <xs:restriction base="xs:string">
      <xs:enumeration value="cw"/>
      <xs:enumeration value="ccw"/>
    </xs:restriction>
  </xs:simpleType>

  <xs:simpleType name="orientationEnum">
    <xs:restriction base="xs:string">
      <xs:enumeration value="horizontal"/>
      <xs:enumeration value="vertical"/>
      <xs:enumeration value="forward"/>
      <xs:enumeration value="aft"/>
      <xs:enumeration value="left"/>
      <xs:enumeration value="right"/>
      <xs:enumeration value="custom-axis"/>
    </xs:restriction>
  </xs:simpleType>

  <xs:simpleType name="sensorCategoryEnum">
    <xs:restriction base="xs:string">
      <xs:enumeration value="accel-gyro"/>
      <xs:enumeration value="magnetic-field"/>
      <xs:enumeration value="gnss-time"/>
      <xs:enumeration value="pressure-baro"/>
      <xs:enumeration value="airspeed-diff-pressure"/>
      <xs:enumeration value="ranging-lidar"/>
      <xs:enumeration value="ranging-sonar"/>
      <xs:enumeration value="ranging-radar"/>
      <xs:enumeration value="ranging-tof"/>
      <xs:enumeration value="imaging-rgb"/>
      <xs:enumeration value="imaging-optical-flow"/>
      <xs:enumeration value="imaging-event"/>
      <xs:enumeration value="thermal-ir"/>
      <xs:enumeration value="spectral-multispectral"/>
      <xs:enumeration value="spectral-hyperspectral"/>
      <xs:enumeration value="spectral-polarization"/>
      <xs:enumeration value="rf-adsb-uwb"/>
      <xs:enumeration value="acoustic"/>
      <xs:enumeration value="chemical-gas"/>
      <xs:enumeration value="particulate"/>
      <xs:enumeration value="temp-humidity"/>
      <xs:enumeration value="radiation"/>
      <xs:enumeration value="structural-vibration-strain"/>
      <xs:enumeration value="electrical-telemetry"/>
    </xs:restriction>
  </xs:simpleType>

  <!-- ========= Reusable complex types ========= -->

  <xs:complexType name="referenceGeometryType">
    <xs:sequence>
      <xs:element name="s-ref-m2" type="xs:double" minOccurs="0"/>
      <xs:element name="b-ref-m" type="xs:double" minOccurs="0"/>
      <xs:element name="c-ref-m" type="xs:double" minOccurs="0"/>
    </xs:sequence>
  </xs:complexType>

  <xs:complexType name="hardpointType">
    <xs:sequence>
      <xs:element name="location-m" type="vector3Type"/>
      <xs:element name="orientation-axis" type="vector3Type" minOccurs="0"/>
      <xs:element name="description" type="xs:string" minOccurs="0"/>
    </xs:sequence>
    <xs:attribute name="id" type="kebabIdType" use="required"/>
  </xs:complexType>

  <xs:complexType name="hardpointsListType">
    <xs:sequence>
      <xs:element name="hardpoint" type="hardpointType" maxOccurs="unbounded"/>
    </xs:sequence>
  </xs:complexType>

  <!-- 1D table: one input label + (x,y) pairs -->
  <xs:complexType name="table1dType">
    <xs:sequence>
      <xs:element name="inputs">
        <xs:complexType>
          <xs:sequence>
            <xs:element name="input" type="xs:string"/>
          </xs:sequence>
        </xs:complexType>
      </xs:element>
      <xs:element name="table">
        <xs:complexType>
          <xs:sequence>
            <xs:element name="pair" maxOccurs="unbounded">
              <xs:complexType>
                <xs:attribute name="x" type="xs:double" use="required"/>
                <xs:attribute name="y" type="xs:double" use="required"/>
              </xs:complexType>
            </xs:element>
          </xs:sequence>
        </xs:complexType>
      </xs:element>
    </xs:sequence>
  </xs:complexType>

  <!-- 2D table: two input labels + points (u,v,value) -->
  <xs:complexType name="table2dType">
    <xs:sequence>
      <xs:element name="inputs">
        <xs:complexType>
          <xs:sequence>
            <xs:element name="input" type="xs:string" minOccurs="2" maxOccurs="2"/>
          </xs:sequence>
        </xs:complexType>
      </xs:element>
      <xs:element name="table">
        <xs:complexType>
          <xs:sequence>
            <xs:element name="point" maxOccurs="unbounded">
              <xs:complexType>
                <xs:attribute name="u" type="xs:double" use="required"/>
                <xs:attribute name="v" type="xs:double" use="required"/>
                <xs:attribute name="value" type="xs:double" use="required"/>
              </xs:complexType>
            </xs:element>
          </xs:sequence>
        </xs:complexType>
      </xs:element>
    </xs:sequence>
  </xs:complexType>

  <!-- ========= Components ========= -->

  <!-- Structures -->
  <xs:complexType name="structureType">
    <xs:sequence>
      <xs:element name="name" type="xs:string"/>
      <xs:element name="material" type="xs:string" minOccurs="0"/>
      <xs:element name="reference-geometry" type="referenceGeometryType" minOccurs="0"/>
      <xs:element name="hardpoints" type="hardpointsListType" minOccurs="0"/>
    </xs:sequence>
    <xs:attribute name="id" type="kebabIdType" use="required"/>
  </xs:complexType>

  <xs:complexType name="structuresType">
    <xs:sequence>
      <xs:element name="structure" type="structureType" maxOccurs="unbounded"/>
    </xs:sequence>
  </xs:complexType>

  <!-- Energy -->
  <xs:complexType name="batteryType">
    <xs:sequence>
      <xs:element name="name" type="xs:string"/>
      <xs:element name="type" fixed="battery"/>
      <xs:element name="nominal-voltage-v" type="xs:double"/>
      <xs:element name="capacity-ah" type="xs:double"/>
      <xs:element name="mass-kg" type="xs:double" minOccurs="0"/>
      <xs:element name="max-discharge-c" type="xs:double" minOccurs="0"/>
      <xs:element name="connector" type="xs:string" minOccurs="0"/>
    </xs:sequence>
    <xs:attribute name="id" type="kebabIdType" use="required"/>
  </xs:complexType>

  <xs:complexType name="fuelTankType">
    <xs:sequence>
      <xs:element name="name" type="xs:string"/>
      <xs:element name="type" fixed="fuel-tank"/>
      <xs:element name="fuel" type="xs:string"/>
      <xs:element name="volume-l" type="xs:double" minOccurs="0"/>
      <xs:element name="capacity-kg" type="xs:double" minOccurs="0"/>
      <xs:element name="mass-empty-kg" type="xs:double" minOccurs="0"/>
      <xs:element name="max-pressure-kpa" type="xs:double" minOccurs="0"/>
      <xs:element name="ullage-fraction" type="xs:double" minOccurs="0"/>
    </xs:sequence>
    <xs:attribute name="id" type="kebabIdType" use="required"/>
  </xs:complexType>

  <xs:complexType name="oxidizerTankType">
    <xs:sequence>
      <xs:element name="name" type="xs:string"/>
      <xs:element name="type" fixed="oxidizer-tank"/>
      <xs:element name="propellant" type="xs:string"/>
      <xs:element name="capacity-kg" type="xs:double" minOccurs="0"/>
      <xs:element name="mass-empty-kg" type="xs:double" minOccurs="0"/>
      <xs:element name="max-pressure-kpa" type="xs:double" minOccurs="0"/>
    </xs:sequence>
    <xs:attribute name="id" type="kebabIdType" use="required"/>
  </xs:complexType>

  <xs:complexType name="energyType">
    <xs:sequence>
      <xs:choice maxOccurs="unbounded">
        <xs:element name="battery" type="batteryType"/>
        <xs:element name="fuel-tank" type="fuelTankType"/>
        <xs:element name="oxidizer-tank" type="oxidizerTankType"/>
      </xs:choice>
    </xs:sequence>
  </xs:complexType>

  <!-- Propulsion -->
  <xs:complexType name="electricMotorType">
    <xs:sequence>
      <xs:element name="name" type="xs:string"/>
      <xs:element name="type" fixed="electric-motor"/>
      <xs:element name="kv" type="xs:double" minOccurs="0"/>
      <xs:element name="max-current-a" type="xs:double" minOccurs="0"/>
      <xs:element name="voltage-range-v" type="vector2Type" minOccurs="0"/>
      <xs:element name="torque-curve" type="table1dType" minOccurs="0"/>
    </xs:sequence>
    <xs:attribute name="id" type="kebabIdType" use="required"/>
  </xs:complexType>

  <xs:complexType name="propellerType">
    <xs:sequence>
      <xs:element name="name" type="xs:string"/>
      <xs:element name="type" fixed="propeller"/>
      <xs:element name="diameter-m" type="xs:double"/>
      <xs:element name="blades" type="xs:int"/>
      <xs:element name="pitch-in" type="xs:double" minOccurs="0"/>
      <xs:element name="thrust-curve" type="table2dType" minOccurs="0"/>
    </xs:sequence>
    <xs:attribute name="id" type="kebabIdType" use="required"/>
  </xs:complexType>

  <xs:complexType name="turbofanType">
    <xs:sequence>
      <xs:element name="name" type="xs:string"/>
      <xs:element name="type" fixed="turbofan"/>
      <xs:element name="max-static-thrust-n" type="xs:double"/>
      <xs:element name="tsfc-kg-per-nh" type="xs:double" minOccurs="0"/>
      <xs:element name="bypass-ratio" type="xs:double" minOccurs="0"/>
      <xs:element name="max-mach" type="xs:double" minOccurs="0"/>
    </xs:sequence>
    <xs:attribute name="id" type="kebabIdType" use="required"/>
  </xs:complexType>

  <xs:complexType name="solidRocketType">
    <xs:sequence>
      <xs:element name="name" type="xs:string"/>
      <xs:element name="type" fixed="solid-rocket"/>
      <xs:element name="thrust-n-curve" type="table1dType"/>
      <xs:element name="propellant-mass-kg" type="xs:double"/>
      <xs:element name="grain-geometry" type="xs:string" minOccurs="0"/>
    </xs:sequence>
    <xs:attribute name="id" type="kebabIdType" use="required"/>
  </xs:complexType>

  <xs:complexType name="liquidRocketType">
    <xs:sequence>
      <xs:element name="name" type="xs:string"/>
      <xs:element name="type" fixed="liquid-rocket"/>
      <xs:element name="max-thrust-n" type="xs:double"/>
      <xs:element name="isp-sea-s" type="xs:double" minOccurs="0"/>
      <xs:element name="isp-vac-s" type="xs:double"/>
      <xs:element name="mixture-ratio-ox-fuel" type="xs:double" minOccurs="0"/>
      <xs:element name="gimbal-deg" type="xs:double" minOccurs="0"/>
    </xs:sequence>
    <xs:attribute name="id" type="kebabIdType" use="required"/>
  </xs:complexType>

  <xs:complexType name="propulsionType">
    <xs:sequence>
      <xs:choice maxOccurs="unbounded">
        <xs:element name="electric-motor" type="electricMotorType"/>
        <xs:element name="propeller" type="propellerType"/>
        <xs:element name="turbofan" type="turbofanType"/>
        <xs:element name="solid-rocket" type="solidRocketType"/>
        <xs:element name="liquid-rocket" type="liquidRocketType"/>
      </xs:choice>
    </xs:sequence>
  </xs:complexType>

  <!-- Rotors & Nozzles -->
  <xs:complexType name="rotorUnitType">
    <xs:sequence>
      <xs:element name="name" type="xs:string"/>
      <!-- const "rotor" to mirror JSON const -->
      <xs:element name="effector-type">
        <xs:simpleType>
          <xs:restriction base="xs:string">
            <xs:enumeration value="rotor"/>
          </xs:restriction>
        </xs:simpleType>
      </xs:element>
      <xs:element name="motor-ref" type="kebabIdType" minOccurs="0"/>
      <xs:element name="prop-ref" type="kebabIdType" minOccurs="0"/>
      <xs:element name="axis-body" type="vector3Type"/>
      <xs:element name="rotation-direction" type="rotationDirectionEnum" minOccurs="0"/>
      <xs:element name="static-thrust-n" type="xs:double" minOccurs="0"/>
    </xs:sequence>
    <xs:attribute name="id" type="kebabIdType" use="required"/>
  </xs:complexType>

  <xs:complexType name="rcsNozzleType">
    <xs:sequence>
      <xs:element name="name" type="xs:string"/>
      <!-- const "reaction-control-jet" -->
      <xs:element name="effector-type">
        <xs:simpleType>
          <xs:restriction base="xs:string">
            <xs:enumeration value="reaction-control-jet"/>
          </xs:restriction>
        </xs:simpleType>
      </xs:element>
      <xs:element name="max-thrust-n" type="xs:double"/>
      <xs:element name="isp-s" type="xs:double" minOccurs="0"/>
      <xs:element name="axis-body" type="vector3Type"/>
    </xs:sequence>
    <xs:attribute name="id" type="kebabIdType" use="required"/>
  </xs:complexType>

  <xs:complexType name="rotorsNozzlesType">
    <xs:sequence>
      <xs:choice maxOccurs="unbounded">
        <xs:element name="rotor-unit" type="rotorUnitType"/>
        <xs:element name="rcs-nozzle" type="rcsNozzleType"/>
      </xs:choice>
    </xs:sequence>
  </xs:complexType>

  <!-- Aero surfaces -->
  <xs:complexType name="controlSurfaceType">
    <xs:sequence>
      <xs:element name="name" type="xs:string"/>
      <!-- const "control-surface" -->
      <xs:element name="effector-type">
        <xs:simpleType>
          <xs:restriction base="xs:string">
            <xs:enumeration value="control-surface"/>
          </xs:restriction>
        </xs:simpleType>
      </xs:element>
      <xs:element name="area-m2" type="xs:double"/>
      <xs:element name="max-deflection-deg" type="xs:double"/>
      <xs:element name="rate-deg-per-s" type="xs:double" minOccurs="0"/>
      <xs:element name="d-cl-per-deg" type="xs:double" minOccurs="0"/>
      <xs:element name="d-cm-per-deg" type="xs:double" minOccurs="0"/>
      <xs:element name="d-cn-per-deg" type="xs:double" minOccurs="0"/>
    </xs:sequence>
    <xs:attribute name="id" type="kebabIdType" use="required"/>
  </xs:complexType>

  <xs:complexType name="aeroSurfacesType">
    <xs:sequence>
      <xs:element name="control-surface" type="controlSurfaceType" maxOccurs="unbounded"/>
    </xs:sequence>
  </xs:complexType>

  <!-- Actuators -->
  <xs:complexType name="servoActuatorType">
    <xs:sequence>
      <xs:element name="name" type="xs:string"/>
      <xs:element name="actuator-type">
        <xs:simpleType>
          <xs:restriction base="xs:string">
            <xs:enumeration value="servo"/>
          </xs:restriction>
        </xs:simpleType>
      </xs:element>
      <xs:element name="max-torque-nm" type="xs:double" minOccurs="0"/>
      <xs:element name="max-speed-deg-per-s" type="xs:double" minOccurs="0"/>
      <xs:element name="travel-deg" type="xs:double" minOccurs="0"/>
    </xs:sequence>
    <xs:attribute name="id" type="kebabIdType" use="required"/>
  </xs:complexType>

  <xs:complexType name="hydraulicActuatorType">
    <xs:sequence>
      <xs:element name="name" type="xs:string"/>
      <xs:element name="actuator-type">
        <xs:simpleType>
          <xs:restriction base="xs:string">
            <xs:enumeration value="hydraulic"/>
          </xs:restriction>
        </xs:simpleType>
      </xs:element>
      <xs:element name="max-force-n" type="xs:double"/>
      <xs:element name="stroke-m" type="xs:double"/>
      <xs:element name="max-speed-m-per-s" type="xs:double" minOccurs="0"/>
    </xs:sequence>
    <xs:attribute name="id" type="kebabIdType" use="required"/>
  </xs:complexType>

  <xs:complexType name="genericActuatorType">
    <xs:sequence>
      <xs:element name="name" type="xs:string"/>
      <xs:element name="actuator-type" type="actuatorTypeEnum"/>
      <!-- extensible -->
      <xs:any minOccurs="0" maxOccurs="unbounded" processContents="lax"/>
    </xs:sequence>
    <xs:attribute name="id" type="kebabIdType" use="required"/>
  </xs:complexType>

  <xs:complexType name="actuatorsType">
    <xs:sequence>
      <xs:choice maxOccurs="unbounded">
        <xs:element name="servo" type="servoActuatorType"/>
        <xs:element name="hydraulic" type="hydraulicActuatorType"/>
        <xs:element name="generic-actuator" type="genericActuatorType"/>
      </xs:choice>
    </xs:sequence>
  </xs:complexType>

  <!-- Avionics -->
  <xs:complexType name="avionicsType">
    <xs:sequence>
      <xs:element name="name" type="xs:string"/>
      <xs:element name="cpu" type="xs:string" minOccurs="0"/>
      <xs:element name="firmware" minOccurs="0">
        <xs:complexType>
          <xs:sequence>
            <xs:element name="item" type="xs:string" maxOccurs="unbounded"/>
          </xs:sequence>
        </xs:complexType>
      </xs:element>
      <xs:element name="uart-ports" type="xs:int" minOccurs="0"/>
      <xs:element name="redundancy" type="xs:string" minOccurs="0"/>
      <xs:element name="standards" minOccurs="0">
        <xs:complexType>
          <xs:sequence>
            <xs:element name="item" type="xs:string" maxOccurs="unbounded"/>
          </xs:sequence>
        </xs:complexType>
      </xs:element>
      <!-- allow extra vendor fields -->
      <xs:any minOccurs="0" maxOccurs="unbounded" processContents="lax"/>
    </xs:sequence>
    <xs:attribute name="id" type="kebabIdType" use="required"/>
  </xs:complexType>

  <xs:complexType name="avionicsBankType">
    <xs:sequence>
      <xs:element name="avionics" type="avionicsType" maxOccurs="unbounded"/>
    </xs:sequence>
  </xs:complexType>

  <!-- Sensors -->
  <xs:complexType name="sensorType">
    <xs:sequence>
      <xs:element name="name" type="xs:string"/>
      <xs:element name="category" type="sensorCategoryEnum"/>
      <xs:element name="constellations" minOccurs="0">
        <xs:complexType>
          <xs:sequence>
            <xs:element name="item" type="xs:string" maxOccurs="unbounded"/>
          </xs:sequence>
        </xs:complexType>
      </xs:element>
      <!-- allow extra fields -->
      <xs:any minOccurs="0" maxOccurs="unbounded" processContents="lax"/>
    </xs:sequence>
    <xs:attribute name="id" type="kebabIdType" use="required"/>
  </xs:complexType>

  <xs:complexType name="sensorsType">
    <xs:sequence>
      <xs:element name="sensor" type="sensorType" maxOccurs="unbounded"/>
    </xs:sequence>
  </xs:complexType>

  <!-- Landing gear -->
  <xs:complexType name="landingGearItemType">
    <xs:sequence>
      <xs:element name="name" type="xs:string"/>
      <xs:element name="gear-type" type="gearTypeEnum" maxOccurs="unbounded"/>
      <xs:any minOccurs="0" maxOccurs="unbounded" processContents="lax"/>
    </xs:sequence>
    <xs:attribute name="id" type="kebabIdType" use="required"/>
  </xs:complexType>

  <xs:complexType name="landingGearType">
    <xs:sequence>
      <xs:element name="landing-gear" type="landingGearItemType" maxOccurs="unbounded"/>
    </xs:sequence>
  </xs:complexType>

  <!-- Recovery & safety -->
  <xs:complexType name="recoveryItemType">
    <xs:sequence>
      <xs:element name="name" type="xs:string"/>
      <xs:element name="canopy-area-m2" type="xs:double" minOccurs="0"/>
      <xs:element name="deploy-speed-max-mps" type="xs:double" minOccurs="0"/>
      <xs:any minOccurs="0" maxOccurs="unbounded" processContents="lax"/>
    </xs:sequence>
    <xs:attribute name="id" type="kebabIdType" use="required"/>
  </xs:complexType>

  <xs:complexType name="recoverySafetyType">
    <xs:sequence>
      <xs:element name="recovery-item" type="recoveryItemType" maxOccurs="unbounded"/>
    </xs:sequence>
  </xs:complexType>

  <!-- Payloads -->
  <xs:complexType name="payloadItemType">
    <xs:sequence>
      <xs:element name="name" type="xs:string"/>
      <xs:element name="mass-kg" type="xs:double" minOccurs="0"/>
      <xs:element name="power-w" type="xs:double" minOccurs="0"/>
      <xs:any minOccurs="0" maxOccurs="unbounded" processContents="lax"/>
    </xs:sequence>
    <xs:attribute name="id" type="kebabIdType" use="required"/>
  </xs:complexType>

  <xs:complexType name="payloadsType">
    <xs:sequence>
      <xs:element name="payload" type="payloadItemType" maxOccurs="unbounded"/>
    </xs:sequence>
  </xs:complexType>

  <!-- Components container -->
  <xs:complexType name="componentsType">
    <xs:sequence>
      <xs:element name="structures" type="structuresType"/>
      <xs:element name="energy" type="energyType"/>
      <xs:element name="propulsion" type="propulsionType"/>
      <xs:element name="rotors-and-nozzles" type="rotorsNozzlesType"/>
      <xs:element name="aero-surfaces" type="aeroSurfacesType"/>
      <xs:element name="actuators" type="actuatorsType"/>
      <xs:element name="avionics" type="avionicsBankType"/>
      <xs:element name="sensors" type="sensorsType"/>
      <xs:element name="landing-gear" type="landingGearType"/>
      <xs:element name="recovery-and-safety" type="recoverySafetyType"/>
      <xs:element name="payloads" type="payloadsType"/>
    </xs:sequence>
  </xs:complexType>

  <!-- ========= Vehicle substructures ========= -->

  <xs:complexType name="massPropertiesType">
    <xs:sequence>
      <xs:element name="cg-location-m" type="vector3Type"/>
      <xs:element name="inertia-tensor-kg-m2" type="matrix3Type"/>
    </xs:sequence>
  </xs:complexType>

  <xs:complexType name="performanceEnvelopeType">
    <xs:sequence>
      <xs:element name="vne-ms" type="xs:double" minOccurs="0"/>
      <xs:element name="mach-max" type="xs:double" minOccurs="0"/>
      <xs:element name="service-ceiling-m" type="xs:double" minOccurs="0"/>
      <xs:element name="max-wind-mps" type="xs:double" minOccurs="0"/>
      <xs:element name="max-q-pa" type="xs:double" minOccurs="0"/>
      <xs:element name="max-dynamic-pressure-event-s" type="xs:double" minOccurs="0"/>
    </xs:sequence>
  </xs:complexType>

  <xs:complexType name="dragPolarType">
    <xs:sequence>
      <xs:element name="cd0" type="xs:double"/>
      <xs:element name="k" type="xs:double"/>
    </xs:sequence>
  </xs:complexType>

  <xs:complexType name="liftCurveType">
    <xs:sequence>
      <xs:element name="cl-alpha-per-rad" type="xs:double"/>
      <xs:element name="cl0" type="xs:double"/>
    </xs:sequence>
  </xs:complexType>

  <xs:complexType name="effectorCommandType">
    <xs:attribute name="target" type="kebabIdType" use="required"/>
    <xs:attribute name="type" type="xs:string" use="required"/>
    <xs:attribute name="scale" type="xs:double" use="required"/>
    <xs:attribute name="offset" type="xs:double" use="optional"/>
    <xs:attribute name="min" type="xs:double" use="optional"/>
    <xs:attribute name="max" type="xs:double" use="optional"/>
  </xs:complexType>

  <xs:complexType name="controlMapItemType">
    <xs:sequence>
      <xs:element name="effector" type="effectorCommandType" maxOccurs="unbounded"/>
    </xs:sequence>
    <xs:attribute name="input" type="xs:string" use="required"/>
  </xs:complexType>

  <xs:complexType name="controlMapType">
    <xs:sequence>
      <xs:element name="map" type="controlMapItemType" maxOccurs="unbounded"/>
    </xs:sequence>
  </xs:complexType>

  <xs:complexType name="vehicleEnergyMountType">
    <xs:sequence>
      <xs:element name="location-m" type="vector3Type" minOccurs="0"/>
    </xs:sequence>
    <!-- Prefer "mount" (matches JSON). "id" accepted for leniency. -->
    <xs:attribute name="mount" type="kebabIdType" use="optional"/>
    <xs:attribute name="id" type="kebabIdType" use="optional"/>
    <xs:attribute name="ref" type="kebabIdType" use="required"/>
  </xs:complexType>

  <xs:complexType name="vehicleEnergyType">
    <xs:sequence>
      <xs:element name="mount" type="vehicleEnergyMountType" maxOccurs="unbounded"/>
    </xs:sequence>
  </xs:complexType>

  <xs:complexType name="propulsionGroupUnitType">
    <xs:sequence>
      <xs:element name="rotor-ref" type="kebabIdType" minOccurs="0"/>
      <xs:element name="propulsion-ref" type="kebabIdType" minOccurs="0"/>
      <xs:element name="rotation-direction" type="rotationDirectionEnum" minOccurs="0"/>
      <xs:element name="location-m" type="vector3Type" minOccurs="0"/>
      <xs:element name="gimbal-deg" type="vector2Type" minOccurs="0"/>
    </xs:sequence>
    <xs:attribute name="id" type="kebabIdType" use="required"/>
  </xs:complexType>

  <xs:complexType name="propulsionGroupType">
    <xs:sequence>
      <xs:element name="unit" type="propulsionGroupUnitType" maxOccurs="unbounded"/>
    </xs:sequence>
  </xs:complexType>

  <xs:complexType name="surfaceMountType">
    <xs:sequence>
      <xs:element name="surface-ref" type="kebabIdType"/>
      <xs:element name="actuator-ref" type="kebabIdType" minOccurs="0"/>
      <xs:element name="location-m" type="vector3Type"/>
    </xs:sequence>
    <xs:attribute name="id" type="kebabIdType" use="required"/>
  </xs:complexType>

  <xs:complexType name="surfacesType">
    <xs:sequence>
      <xs:element name="surface" type="surfaceMountType" maxOccurs="unbounded"/>
    </xs:sequence>
  </xs:complexType>

  <xs:complexType name="engineMountType">
    <xs:sequence>
      <xs:element name="propulsion-ref" type="kebabIdType"/>
      <xs:element name="location-m" type="vector3Type"/>
      <xs:element name="gimbal-deg" type="vector2Type" minOccurs="0"/>
    </xs:sequence>
    <xs:attribute name="id" type="kebabIdType" use="required"/>
  </xs:complexType>

  <xs:complexType name="enginesType">
    <xs:sequence>
      <xs:element name="engine" type="engineMountType" maxOccurs="unbounded"/>
    </xs:sequence>
  </xs:complexType>

  <xs:complexType name="vehicleAvionicsRefsType">
    <xs:sequence>
      <xs:element name="fc-ref" type="kebabIdType" minOccurs="0"/>
      <xs:element name="fcc-ref" type="kebabIdType" minOccurs="0"/>
    </xs:sequence>
  </xs:complexType>

  <xs:complexType name="vehicleSensorsRefsType">
    <xs:sequence>
      <xs:element name="sensor-ref" type="kebabIdType" maxOccurs="unbounded"/>
    </xs:sequence>
  </xs:complexType>

  <!-- Rocket/spaceplane stages -->
  <xs:complexType name="rcsThrusterType">
    <xs:sequence>
      <xs:element name="nozzle-ref" type="kebabIdType"/>
      <xs:element name="location-m" type="vector3Type" minOccurs="0"/>
      <xs:element name="axis-body" type="vector3Type" minOccurs="0"/>
    </xs:sequence>
    <xs:attribute name="id" type="kebabIdType" use="required"/>
  </xs:complexType>

  <xs:complexType name="rcsArrayType">
    <xs:sequence>
      <xs:element name="rcs" type="rcsThrusterType" maxOccurs="unbounded"/>
    </xs:sequence>
  </xs:complexType>

  <!-- flexible propellant map (name, kg) -->
  <xs:complexType name="propellantsKgType">
    <xs:sequence>
      <xs:element name="propellant" maxOccurs="unbounded">
        <xs:complexType>
          <xs:attribute name="name" type="kebabIdType" use="required"/>
          <xs:attribute name="kg" type="xs:double" use="required"/>
        </xs:complexType>
      </xs:element>
    </xs:sequence>
  </xs:complexType>

  <xs:complexType name="separationEventType">
    <xs:sequence>
      <xs:element name="type" type="xs:string"/>
      <xs:element name="time-s" type="xs:double" minOccurs="0"/>
    </xs:sequence>
  </xs:complexType>

  <xs:complexType name="stageEngineType">
    <xs:sequence>
      <xs:element name="propulsion-ref" type="kebabIdType"/>
      <xs:element name="gimbal-deg" type="vector2Type" minOccurs="0"/>
      <xs:element name="location-m" type="vector3Type" minOccurs="0"/>
    </xs:sequence>
    <xs:attribute name="id" type="kebabIdType" use="required"/>
  </xs:complexType>

  <xs:complexType name="stageEnginesType">
    <xs:sequence>
      <xs:element name="engine" type="stageEngineType" maxOccurs="unbounded"/>
    </xs:sequence>
  </xs:complexType>

  <xs:complexType name="stagePayloadMountType">
    <xs:sequence>
      <xs:element name="location-m" type="vector3Type" minOccurs="0"/>
    </xs:sequence>
    <xs:attribute name="ref" type="kebabIdType" use="required"/>
  </xs:complexType>

  <xs:complexType name="stagePayloadsType">
    <xs:sequence>
      <xs:element name="payload" type="stagePayloadMountType" maxOccurs="unbounded"/>
    </xs:sequence>
  </xs:complexType>

  <xs:complexType name="stageRecoveryType">
    <xs:sequence>
      <xs:element name="parachute-ref" type="kebabIdType" minOccurs="0"/>
      <xs:any minOccurs="0" maxOccurs="unbounded" processContents="lax"/>
    </xs:sequence>
  </xs:complexType>

  <xs:complexType name="vehicleStageType">
    <xs:sequence>
      <xs:element name="dry-mass-kg" type="xs:double"/>
      <xs:element name="propellants-kg" type="propellantsKgType" minOccurs="0"/>
      <xs:element name="engines" type="stageEnginesType" minOccurs="0"/>
      <xs:element name="rcs-array" type="rcsArrayType" minOccurs="0"/>
      <xs:element name="payloads" type="stagePayloadsType" minOccurs="0"/>
      <xs:element name="recovery" type="stageRecoveryType" minOccurs="0"/>
      <xs:element name="separation-event" type="separationEventType" minOccurs="0"/>
    </xs:sequence>
    <xs:attribute name="id" type="kebabIdType" use="required"/>
  </xs:complexType>

  <xs:complexType name="vehicleStagesType">
    <xs:sequence>
      <xs:element name="stage" type="vehicleStageType" maxOccurs="unbounded"/>
    </xs:sequence>
  </xs:complexType>

  <xs:complexType name="vehicleRecoveryType">
    <xs:sequence>
      <xs:element name="parachute-ref" type="kebabIdType" minOccurs="0"/>
      <xs:any minOccurs="0" maxOccurs="unbounded" processContents="lax"/>
    </xs:sequence>
  </xs:complexType>

  <xs:complexType name="guidanceType">
    <xs:sequence>
      <xs:element name="avionics-ref" type="kebabIdType"/>
    </xs:sequence>
  </xs:complexType>

  <!-- Full vehicle -->
  <xs:complexType name="vehicleTypeFull">
    <xs:sequence>
      <xs:element name="name" type="xs:string"/>
      <xs:element name="vehicle-type" type="vehicleTypeEnum"/>
      <xs:element name="subtype" type="xs:string" minOccurs="0"/>
      <xs:element name="mass-kg" type="xs:double"/>
      <xs:element name="mass-properties" type="massPropertiesType" minOccurs="0"/>
      <xs:element name="structure-ref" type="kebabIdType" minOccurs="0"/>
      <xs:element name="reference-geometry" type="referenceGeometryType" minOccurs="0"/>
      <xs:element name="energy" type="vehicleEnergyType" minOccurs="0"/>
      <xs:element name="propulsion-group" type="propulsionGroupType" minOccurs="0"/>
      <xs:element name="surfaces" type="surfacesType" minOccurs="0"/>
      <xs:element name="engines" type="enginesType" minOccurs="0"/>
      <xs:element name="landing-gear-ref" type="kebabIdType" minOccurs="0"/>
      <xs:element name="avionics" type="vehicleAvionicsRefsType" minOccurs="0"/>
      <xs:element name="sensors" type="vehicleSensorsRefsType" minOccurs="0"/>
      <xs:element name="stages" type="vehicleStagesType" minOccurs="0"/>
      <xs:element name="guidance" type="guidanceType" minOccurs="0"/>
      <xs:element name="recovery" type="vehicleRecoveryType" minOccurs="0"/>
      <xs:element name="performance-envelope" type="performanceEnvelopeType" minOccurs="0"/>
      <xs:element name="drag-polar" type="dragPolarType" minOccurs="0"/>
      <xs:element name="lift-curve" type="liftCurveType" minOccurs="0"/>
      <xs:element name="control-map" type="controlMapType" minOccurs="0"/>
    </xs:sequence>
    <xs:attribute name="id" type="kebabIdType" use="required"/>
  </xs:complexType>

  <xs:complexType name="vehiclesType">
    <xs:sequence>
      <!-- Generic vehicle entries. Each has a kebab-case id attribute. -->
      <xs:element name="vehicle" type="vehicleTypeFull" maxOccurs="unbounded"/>
    </xs:sequence>
  </xs:complexType>

  <!-- ========= Conventions & Enums (as data blocks) ========= -->

  <xs:complexType name="framesType">
    <xs:sequence>
      <xs:element name="body" type="xs:string"/>
      <xs:element name="world" type="xs:string"/>
    </xs:sequence>
  </xs:complexType>

  <xs:complexType name="conventionsType">
    <xs:sequence>
      <xs:element name="frames" type="framesType"/>
      <xs:element name="angles" type="xs:string"/>
      <xs:element name="vectors" type="xs:string"/>
    </xs:sequence>
  </xs:complexType>

  <xs:complexType name="enumsType">
    <xs:sequence>
      <xs:element name="vehicle-type" type="vehicleTypeEnum" maxOccurs="unbounded" minOccurs="0"/>
      <xs:element name="propulsion-type" type="propulsionTypeEnum" maxOccurs="unbounded" minOccurs="0"/>
      <xs:element name="effector-type" type="effectorTypeEnum" maxOccurs="unbounded" minOccurs="0"/>
      <xs:element name="actuator-type" type="actuatorTypeEnum" maxOccurs="unbounded" minOccurs="0"/>
      <xs:element name="gear-type" type="gearTypeEnum" maxOccurs="unbounded" minOccurs="0"/>
      <xs:element name="rotation-direction" type="rotationDirectionEnum" maxOccurs="unbounded" minOccurs="0"/>
      <xs:element name="orientation" type="orientationEnum" maxOccurs="unbounded" minOccurs="0"/>
    </xs:sequence>
  </xs:complexType>

  <!-- ========= Root element ========= -->

  <xs:element name="unified-flight-vehicle">
    <xs:complexType>
      <xs:sequence>
        <xs:element name="conventions" type="conventionsType" minOccurs="0"/>
        <xs:element name="enums" type="enumsType" minOccurs="0"/>
        <xs:element name="components" type="componentsType" minOccurs="0"/>
        <xs:element name="vehicles" type="vehiclesType" minOccurs="1"/>
      </xs:sequence>
      <xs:attribute name="schema-version" type="versionString" use="required"/>
      <xs:attribute name="units" use="required" fixed="si"/>
    </xs:complexType>
  </xs:element>

</xs:schema>
<?xml version="1.0" encoding="UTF-8"?>
<xs:schema xmlns:xs="http://www.w3.org/2001/XMLSchema"
           targetNamespace="http://fpv-fsim.dev/schemas/scene"
           xmlns:tns="http://fpv-fsim.dev/schemas/scene"
           elementFormDefault="qualified">

    <!-- Root Scene Element -->
    <xs:element name="scene" type="tns:SceneType"/>

    <!-- Scene Type Definition -->
    <xs:complexType name="SceneType">
        <xs:sequence>
            <xs:element name="metadata" type="tns:MetadataType" minOccurs="0"/>
            <xs:element name="camera" type="tns:CameraType" minOccurs="0"/>
            <xs:element name="lighting" type="tns:LightingType" minOccurs="0"/>
            <xs:element name="entities" type="tns:EntitiesType" minOccurs="0"/>
        </xs:sequence>
        <xs:attribute name="name" type="xs:string" use="required"/>
        <xs:attribute name="type" type="tns:SceneTypeEnum" use="required"/>
        <xs:attribute name="budget_memory_mb" type="xs:positiveInteger" default="1"/>
    </xs:complexType>

    <!-- Scene Type Enumeration -->
    <xs:simpleType name="SceneTypeEnum">
        <xs:restriction base="xs:string">
            <xs:enumeration value="default_sphere"/>
            <xs:enumeration value="loading_indicator"/>
            <xs:enumeration value="debug"/>
        </xs:restriction>
    </xs:simpleType>

    <!-- Metadata -->
    <xs:complexType name="MetadataType">
        <xs:sequence>
            <xs:element name="description" type="xs:string" minOccurs="0"/>
            <xs:element name="author" type="xs:string" minOccurs="0"/>
            <xs:element name="version" type="xs:string" minOccurs="0"/>
        </xs:sequence>
    </xs:complexType>

    <!-- Camera Configuration -->
    <xs:complexType name="CameraType">
        <xs:sequence>
            <xs:element name="position" type="tns:Vector3Type"/>
            <xs:element name="target" type="tns:Vector3Type"/>
            <xs:element name="up" type="tns:Vector3Type" minOccurs="0"/>
        </xs:sequence>
        <xs:attribute name="fov" type="xs:float" default="45.0"/>
        <xs:attribute name="near_plane" type="xs:float" default="0.1"/>
        <xs:attribute name="far_plane" type="xs:float" default="1000.0"/>
    </xs:complexType>

    <!-- Lighting Configuration -->
    <xs:complexType name="LightingType">
        <xs:sequence>
            <xs:element name="directional_light" type="tns:DirectionalLightType" minOccurs="0" maxOccurs="unbounded"/>
            <xs:element name="ambient_light" type="tns:AmbientLightType" minOccurs="0"/>
        </xs:sequence>
    </xs:complexType>

    <xs:complexType name="DirectionalLightType">
        <xs:sequence>
            <xs:element name="direction" type="tns:Vector3Type"/>
            <xs:element name="color" type="tns:ColorType"/>
        </xs:sequence>
        <xs:attribute name="intensity" type="xs:float" default="1.0"/>
        <xs:attribute name="cast_shadows" type="xs:boolean" default="false"/>
    </xs:complexType>

    <xs:complexType name="AmbientLightType">
        <xs:sequence>
            <xs:element name="color" type="tns:ColorType"/>
        </xs:sequence>
        <xs:attribute name="intensity" type="xs:float" default="0.2"/>
    </xs:complexType>

    <!-- Entities Container -->
    <xs:complexType name="EntitiesType">
        <xs:sequence>
            <xs:element name="entity" type="tns:EntityType" minOccurs="0" maxOccurs="unbounded"/>
        </xs:sequence>
    </xs:complexType>

    <!-- Entity Definition -->
    <xs:complexType name="EntityType">
        <xs:sequence>
            <xs:element name="transform" type="tns:TransformType" minOccurs="0"/>
            <xs:element name="mesh" type="tns:MeshType" minOccurs="0"/>
            <xs:element name="material" type="tns:MaterialType" minOccurs="0"/>
            <xs:element name="components" type="tns:ComponentsType" minOccurs="0"/>
        </xs:sequence>
        <xs:attribute name="id" type="xs:string" use="required"/>
        <xs:attribute name="name" type="xs:string"/>
        <xs:attribute name="visible" type="xs:boolean" default="true"/>
    </xs:complexType>

    <!-- Transform Component -->
    <xs:complexType name="TransformType">
        <xs:sequence>
            <xs:element name="position" type="tns:Vector3Type" minOccurs="0"/>
            <xs:element name="rotation" type="tns:Vector3Type" minOccurs="0"/>
            <xs:element name="scale" type="tns:Vector3Type" minOccurs="0"/>
        </xs:sequence>
    </xs:complexType>

    <!-- Mesh Definition (Simplified - All Voxel Based) -->
    <xs:complexType name="MeshType">
        <xs:choice>
            <xs:element name="voxel_primitive" type="tns:VoxelPrimitiveType"/>
            <xs:element name="voxel_compound" type="tns:VoxelCompoundType"/>
        </xs:choice>
    </xs:complexType>

    <!-- Voxel Primitive (Base building block) -->
    <xs:complexType name="VoxelPrimitiveType">
        <xs:attribute name="type" type="tns:VoxelTypeEnum" use="required"/>
        <xs:attribute name="subdivisions" type="xs:positiveInteger" default="1"/>
        <xs:attribute name="size" type="xs:float" default="1.0"/>
        <xs:attribute name="radius" type="xs:float"/> <!-- For sphere-like voxels -->
    </xs:complexType>

    <!-- Voxel Compound (Multiple primitives) -->
    <xs:complexType name="VoxelCompoundType">
        <xs:sequence>
            <xs:element name="part" type="tns:VoxelPartType" maxOccurs="unbounded"/>
        </xs:sequence>
        <xs:attribute name="name" type="xs:string"/>
    </xs:complexType>

    <xs:complexType name="VoxelPartType">
        <xs:sequence>
            <xs:element name="primitive" type="tns:VoxelPrimitiveType"/>
            <xs:element name="offset" type="tns:Vector3Type" minOccurs="0"/>
            <xs:element name="scale" type="tns:Vector3Type" minOccurs="0"/>
        </xs:sequence>
        <xs:attribute name="name" type="xs:string"/>
    </xs:complexType>

    <!-- Voxel Types Enumeration -->
    <xs:simpleType name="VoxelTypeEnum">
        <xs:restriction base="xs:string">
            <xs:enumeration value="cube"/>
            <xs:enumeration value="sphere"/>
            <xs:enumeration value="cylinder"/>
            <xs:enumeration value="plane"/>
        </xs:restriction>
    </xs:simpleType>

    <!-- Material Definition (Simplified) -->
    <xs:complexType name="MaterialType">
        <xs:sequence>
            <xs:element name="texture" type="tns:TextureType" minOccurs="0" maxOccurs="unbounded"/>
            <xs:element name="parameters" type="tns:MaterialParametersType" minOccurs="0"/>
        </xs:sequence>
        <xs:attribute name="shader" type="tns:ShaderTypeEnum" default="basic"/>
        <xs:attribute name="name" type="xs:string"/>
    </xs:complexType>

    <xs:complexType name="TextureType">
        <xs:choice>
            <xs:element name="procedural" type="tns:ProceduralTextureType"/>
            <xs:element name="file" type="xs:string"/>
        </xs:choice>
        <xs:attribute name="slot" type="tns:TextureSlotEnum" default="diffuse"/>
        <xs:attribute name="size" type="xs:positiveInteger" default="32"/>
    </xs:complexType>

    <xs:complexType name="ProceduralTextureType">
        <xs:attribute name="type" type="tns:TextureGenTypeEnum" use="required"/>
        <xs:attribute name="seed" type="xs:int" default="0"/>
        <xs:attribute name="noise_scale" type="xs:float" default="1.0"/>
        <xs:attribute name="color_primary" type="xs:string"/> <!-- Hex color -->
        <xs:attribute name="color_secondary" type="xs:string"/> <!-- Hex color -->
    </xs:complexType>

    <xs:simpleType name="TextureGenTypeEnum">
        <xs:restriction base="xs:string">
            <xs:enumeration value="flat_noise"/>
            <xs:enumeration value="speckle"/>
            <xs:enumeration value="dither"/>
            <xs:enumeration value="solid_color"/>
        </xs:restriction>
    </xs:simpleType>

    <xs:simpleType name="TextureSlotEnum">
        <xs:restriction base="xs:string">
            <xs:enumeration value="diffuse"/>
            <xs:enumeration value="normal"/>
            <xs:enumeration value="roughness"/>
            <xs:enumeration value="metallic"/>
        </xs:restriction>
    </xs:simpleType>

    <xs:simpleType name="ShaderTypeEnum">
        <xs:restriction base="xs:string">
            <xs:enumeration value="basic"/>
            <xs:enumeration value="cel"/>
            <xs:enumeration value="unlit"/>
        </xs:restriction>
    </xs:simpleType>

    <xs:complexType name="MaterialParametersType">
        <xs:sequence>
            <xs:element name="parameter" type="tns:ParameterType" minOccurs="0" maxOccurs="unbounded"/>
        </xs:sequence>
    </xs:complexType>

    <xs:complexType name="ParameterType">
        <xs:attribute name="name" type="xs:string" use="required"/>
        <xs:attribute name="value" type="xs:string" use="required"/>
        <xs:attribute name="type" type="tns:ParameterTypeEnum" default="float"/>
    </xs:complexType>

    <xs:simpleType name="ParameterTypeEnum">
        <xs:restriction base="xs:string">
            <xs:enumeration value="float"/>
            <xs:enumeration value="int"/>
            <xs:enumeration value="bool"/>
            <xs:enumeration value="vector3"/>
            <xs:enumeration value="color"/>
        </xs:restriction>
    </xs:simpleType>

    <!-- Components Container -->
    <xs:complexType name="ComponentsType">
        <xs:sequence>
            <xs:element name="orbital" type="tns:OrbitalComponentType" minOccurs="0"/>
            <xs:element name="rotation" type="tns:RotationComponentType" minOccurs="0"/>
            <xs:element name="trail" type="tns:TrailComponentType" minOccurs="0"/>
            <xs:element name="spawner" type="tns:SpawnerComponentType" minOccurs="0"/>
        </xs:sequence>
    </xs:complexType>

    <!-- Component Definitions -->
    <xs:complexType name="OrbitalComponentType">
        <xs:sequence>
            <xs:element name="center" type="tns:Vector3Type"/>
            <xs:element name="axis" type="tns:Vector3Type" minOccurs="0"/>
        </xs:sequence>
        <xs:attribute name="radius" type="xs:float" use="required"/>
        <xs:attribute name="speed" type="xs:float" default="1.0"/>
        <xs:attribute name="eccentricity" type="xs:float" default="0.0"/>
        <xs:attribute name="inclination" type="xs:float" default="0.0"/>
        <xs:attribute name="phase_offset" type="xs:float" default="0.0"/>
        <xs:attribute name="enable_banking" type="xs:boolean" default="false"/>
        <xs:attribute name="max_bank_angle" type="xs:float" default="30.0"/>
    </xs:complexType>

    <xs:complexType name="RotationComponentType">
        <xs:sequence>
            <xs:element name="axis" type="tns:Vector3Type"/>
        </xs:sequence>
        <xs:attribute name="speed" type="xs:float" default="1.0"/>
        <xs:attribute name="random_variation" type="xs:float" default="0.0"/>
    </xs:complexType>

    <xs:complexType name="TrailComponentType">
        <xs:attribute name="particle_count" type="xs:positiveInteger" default="50"/>
        <xs:attribute name="lifetime" type="xs:float" default="2.0"/>
        <xs:attribute name="spawn_rate" type="xs:float" default="20.0"/>
        <xs:attribute name="enable_physics" type="xs:boolean" default="true"/>
    </xs:complexType>

    <xs:complexType name="SpawnerComponentType">
        <xs:attribute name="spawn_rate" type="xs:float" default="0.1"/>
        <xs:attribute name="max_entities" type="xs:positiveInteger" default="10"/>
        <xs:attribute name="entity_lifetime" type="xs:float" default="30.0"/>
        <xs:attribute name="spawn_radius" type="xs:float" default="5.0"/>
    </xs:complexType>

    <!-- Common Types -->
    <xs:complexType name="Vector3Type">
        <xs:attribute name="x" type="xs:float" default="0.0"/>
        <xs:attribute name="y" type="xs:float" default="0.0"/>
        <xs:attribute name="z" type="xs:float" default="0.0"/>
    </xs:complexType>

    <xs:complexType name="ColorType">
        <xs:attribute name="r" type="xs:float" default="1.0"/>
        <xs:attribute name="g" type="xs:float" default="1.0"/>
        <xs:attribute name="b" type="xs:float" default="1.0"/>
        <xs:attribute name="a" type="xs:float" default="1.0"/>
    </xs:complexType>

</xs:schema>/* This source file must have a .cpp extension so that all C++ compilers
   recognize the extension without flags.  Borland does not know .cxx for
   example.  */
#ifndef __cplusplus
# error "A C compiler has been selected for C++."
#endif

#if !defined(__has_include)
/* If the compiler does not have __has_include, pretend the answer is
   always no.  */
#  define __has_include(x) 0
#endif


/* Version number components: V=Version, R=Revision, P=Patch
   Version date components:   YYYY=Year, MM=Month,   DD=Day  */

#if defined(__INTEL_COMPILER) || defined(__ICC)
# define COMPILER_ID "Intel"
# if defined(_MSC_VER)
#  define SIMULATE_ID "MSVC"
# endif
# if defined(__GNUC__)
#  define SIMULATE_ID "GNU"
# endif
  /* __INTEL_COMPILER = VRP prior to 2021, and then VVVV for 2021 and later,
     except that a few beta releases use the old format with V=2021.  */
# if __INTEL_COMPILER < 2021 || __INTEL_COMPILER == 202110 || __INTEL_COMPILER == 202111
#  define COMPILER_VERSION_MAJOR DEC(__INTEL_COMPILER/100)
#  define COMPILER_VERSION_MINOR DEC(__INTEL_COMPILER/10 % 10)
#  if defined(__INTEL_COMPILER_UPDATE)
#   define COMPILER_VERSION_PATCH DEC(__INTEL_COMPILER_UPDATE)
#  else
#   define COMPILER_VERSION_PATCH DEC(__INTEL_COMPILER   % 10)
#  endif
# else
#  define COMPILER_VERSION_MAJOR DEC(__INTEL_COMPILER)
#  define COMPILER_VERSION_MINOR DEC(__INTEL_COMPILER_UPDATE)
   /* The third version component from --version is an update index,
      but no macro is provided for it.  */
#  define COMPILER_VERSION_PATCH DEC(0)
# endif
# if defined(__INTEL_COMPILER_BUILD_DATE)
   /* __INTEL_COMPILER_BUILD_DATE = YYYYMMDD */
#  define COMPILER_VERSION_TWEAK DEC(__INTEL_COMPILER_BUILD_DATE)
# endif
# if defined(_MSC_VER)
   /* _MSC_VER = VVRR */
#  define SIMULATE_VERSION_MAJOR DEC(_MSC_VER / 100)
#  define SIMULATE_VERSION_MINOR DEC(_MSC_VER % 100)
# endif
# if defined(__GNUC__)
#  define SIMULATE_VERSION_MAJOR DEC(__GNUC__)
# elif defined(__GNUG__)
#  define SIMULATE_VERSION_MAJOR DEC(__GNUG__)
# endif
# if defined(__GNUC_MINOR__)
#  define SIMULATE_VERSION_MINOR DEC(__GNUC_MINOR__)
# endif
# if defined(__GNUC_PATCHLEVEL__)
#  define SIMULATE_VERSION_PATCH DEC(__GNUC_PATCHLEVEL__)
# endif

#elif (defined(__clang__) && defined(__INTEL_CLANG_COMPILER)) || defined(__INTEL_LLVM_COMPILER)
# define COMPILER_ID "IntelLLVM"
#if defined(_MSC_VER)
# define SIMULATE_ID "MSVC"
#endif
#if defined(__GNUC__)
# define SIMULATE_ID "GNU"
#endif
/* __INTEL_LLVM_COMPILER = VVVVRP prior to 2021.2.0, VVVVRRPP for 2021.2.0 and
 * later.  Look for 6 digit vs. 8 digit version number to decide encoding.
 * VVVV is no smaller than the current year when a version is released.
 */
#if __INTEL_LLVM_COMPILER < 1000000L
# define COMPILER_VERSION_MAJOR DEC(__INTEL_LLVM_COMPILER/100)
# define COMPILER_VERSION_MINOR DEC(__INTEL_LLVM_COMPILER/10 % 10)
# define COMPILER_VERSION_PATCH DEC(__INTEL_LLVM_COMPILER    % 10)
#else
# define COMPILER_VERSION_MAJOR DEC(__INTEL_LLVM_COMPILER/10000)
# define COMPILER_VERSION_MINOR DEC(__INTEL_LLVM_COMPILER/100 % 100)
# define COMPILER_VERSION_PATCH DEC(__INTEL_LLVM_COMPILER     % 100)
#endif
#if defined(_MSC_VER)
  /* _MSC_VER = VVRR */
# define SIMULATE_VERSION_MAJOR DEC(_MSC_VER / 100)
# define SIMULATE_VERSION_MINOR DEC(_MSC_VER % 100)
#endif
#if defined(__GNUC__)
# define SIMULATE_VERSION_MAJOR DEC(__GNUC__)
#elif defined(__GNUG__)
# define SIMULATE_VERSION_MAJOR DEC(__GNUG__)
#endif
#if defined(__GNUC_MINOR__)
# define SIMULATE_VERSION_MINOR DEC(__GNUC_MINOR__)
#endif
#if defined(__GNUC_PATCHLEVEL__)
# define SIMULATE_VERSION_PATCH DEC(__GNUC_PATCHLEVEL__)
#endif

#elif defined(__PATHCC__)
# define COMPILER_ID "PathScale"
# define COMPILER_VERSION_MAJOR DEC(__PATHCC__)
# define COMPILER_VERSION_MINOR DEC(__PATHCC_MINOR__)
# if defined(__PATHCC_PATCHLEVEL__)
#  define COMPILER_VERSION_PATCH DEC(__PATHCC_PATCHLEVEL__)
# endif

#elif defined(__BORLANDC__) && defined(__CODEGEARC_VERSION__)
# define COMPILER_ID "Embarcadero"
# define COMPILER_VERSION_MAJOR HEX(__CODEGEARC_VERSION__>>24 & 0x00FF)
# define COMPILER_VERSION_MINOR HEX(__CODEGEARC_VERSION__>>16 & 0x00FF)
# define COMPILER_VERSION_PATCH DEC(__CODEGEARC_VERSION__     & 0xFFFF)

#elif defined(__BORLANDC__)
# define COMPILER_ID "Borland"
  /* __BORLANDC__ = 0xVRR */
# define COMPILER_VERSION_MAJOR HEX(__BORLANDC__>>8)
# define COMPILER_VERSION_MINOR HEX(__BORLANDC__ & 0xFF)

#elif defined(__WATCOMC__) && __WATCOMC__ < 1200
# define COMPILER_ID "Watcom"
   /* __WATCOMC__ = VVRR */
# define COMPILER_VERSION_MAJOR DEC(__WATCOMC__ / 100)
# define COMPILER_VERSION_MINOR DEC((__WATCOMC__ / 10) % 10)
# if (__WATCOMC__ % 10) > 0
#  define COMPILER_VERSION_PATCH DEC(__WATCOMC__ % 10)
# endif

#elif defined(__WATCOMC__)
# define COMPILER_ID "OpenWatcom"
   /* __WATCOMC__ = VVRP + 1100 */
# define COMPILER_VERSION_MAJOR DEC((__WATCOMC__ - 1100) / 100)
# define COMPILER_VERSION_MINOR DEC((__WATCOMC__ / 10) % 10)
# if (__WATCOMC__ % 10) > 0
#  define COMPILER_VERSION_PATCH DEC(__WATCOMC__ % 10)
# endif

#elif defined(__SUNPRO_CC)
# define COMPILER_ID "SunPro"
# if __SUNPRO_CC >= 0x5100
   /* __SUNPRO_CC = 0xVRRP */
#  define COMPILER_VERSION_MAJOR HEX(__SUNPRO_CC>>12)
#  define COMPILER_VERSION_MINOR HEX(__SUNPRO_CC>>4 & 0xFF)
#  define COMPILER_VERSION_PATCH HEX(__SUNPRO_CC    & 0xF)
# else
   /* __SUNPRO_CC = 0xVRP */
#  define COMPILER_VERSION_MAJOR HEX(__SUNPRO_CC>>8)
#  define COMPILER_VERSION_MINOR HEX(__SUNPRO_CC>>4 & 0xF)
#  define COMPILER_VERSION_PATCH HEX(__SUNPRO_CC    & 0xF)
# endif

#elif defined(__HP_aCC)
# define COMPILER_ID "HP"
  /* __HP_aCC = VVRRPP */
# define COMPILER_VERSION_MAJOR DEC(__HP_aCC/10000)
# define COMPILER_VERSION_MINOR DEC(__HP_aCC/100 % 100)
# define COMPILER_VERSION_PATCH DEC(__HP_aCC     % 100)

#elif defined(__DECCXX)
# define COMPILER_ID "Compaq"
  /* __DECCXX_VER = VVRRTPPPP */
# define COMPILER_VERSION_MAJOR DEC(__DECCXX_VER/10000000)
# define COMPILER_VERSION_MINOR DEC(__DECCXX_VER/100000  % 100)
# define COMPILER_VERSION_PATCH DEC(__DECCXX_VER         % 10000)

#elif defined(__IBMCPP__) && defined(__COMPILER_VER__)
# define COMPILER_ID "zOS"
  /* __IBMCPP__ = VRP */
# define COMPILER_VERSION_MAJOR DEC(__IBMCPP__/100)
# define COMPILER_VERSION_MINOR DEC(__IBMCPP__/10 % 10)
# define COMPILER_VERSION_PATCH DEC(__IBMCPP__    % 10)

#elif defined(__open_xl__) && defined(__clang__)
# define COMPILER_ID "IBMClang"
# define COMPILER_VERSION_MAJOR DEC(__open_xl_version__)
# define COMPILER_VERSION_MINOR DEC(__open_xl_release__)
# define COMPILER_VERSION_PATCH DEC(__open_xl_modification__)
# define COMPILER_VERSION_TWEAK DEC(__open_xl_ptf_fix_level__)
# define COMPILER_VERSION_INTERNAL_STR  __clang_version__


#elif defined(__ibmxl__) && defined(__clang__)
# define COMPILER_ID "XLClang"
# define COMPILER_VERSION_MAJOR DEC(__ibmxl_version__)
# define COMPILER_VERSION_MINOR DEC(__ibmxl_release__)
# define COMPILER_VERSION_PATCH DEC(__ibmxl_modification__)
# define COMPILER_VERSION_TWEAK DEC(__ibmxl_ptf_fix_level__)


#elif defined(__IBMCPP__) && !defined(__COMPILER_VER__) && __IBMCPP__ >= 800
# define COMPILER_ID "XL"
  /* __IBMCPP__ = VRP */
# define COMPILER_VERSION_MAJOR DEC(__IBMCPP__/100)
# define COMPILER_VERSION_MINOR DEC(__IBMCPP__/10 % 10)
# define COMPILER_VERSION_PATCH DEC(__IBMCPP__    % 10)

#elif defined(__IBMCPP__) && !defined(__COMPILER_VER__) && __IBMCPP__ < 800
# define COMPILER_ID "VisualAge"
  /* __IBMCPP__ = VRP */
# define COMPILER_VERSION_MAJOR DEC(__IBMCPP__/100)
# define COMPILER_VERSION_MINOR DEC(__IBMCPP__/10 % 10)
# define COMPILER_VERSION_PATCH DEC(__IBMCPP__    % 10)

#elif defined(__NVCOMPILER)
# define COMPILER_ID "NVHPC"
# define COMPILER_VERSION_MAJOR DEC(__NVCOMPILER_MAJOR__)
# define COMPILER_VERSION_MINOR DEC(__NVCOMPILER_MINOR__)
# if defined(__NVCOMPILER_PATCHLEVEL__)
#  define COMPILER_VERSION_PATCH DEC(__NVCOMPILER_PATCHLEVEL__)
# endif

#elif defined(__PGI)
# define COMPILER_ID "PGI"
# define COMPILER_VERSION_MAJOR DEC(__PGIC__)
# define COMPILER_VERSION_MINOR DEC(__PGIC_MINOR__)
# if defined(__PGIC_PATCHLEVEL__)
#  define COMPILER_VERSION_PATCH DEC(__PGIC_PATCHLEVEL__)
# endif

#elif defined(__clang__) && defined(__cray__)
# define COMPILER_ID "CrayClang"
# define COMPILER_VERSION_MAJOR DEC(__cray_major__)
# define COMPILER_VERSION_MINOR DEC(__cray_minor__)
# define COMPILER_VERSION_PATCH DEC(__cray_patchlevel__)
# define COMPILER_VERSION_INTERNAL_STR __clang_version__


#elif defined(_CRAYC)
# define COMPILER_ID "Cray"
# define COMPILER_VERSION_MAJOR DEC(_RELEASE_MAJOR)
# define COMPILER_VERSION_MINOR DEC(_RELEASE_MINOR)

#elif defined(__TI_COMPILER_VERSION__)
# define COMPILER_ID "TI"
  /* __TI_COMPILER_VERSION__ = VVVRRRPPP */
# define COMPILER_VERSION_MAJOR DEC(__TI_COMPILER_VERSION__/1000000)
# define COMPILER_VERSION_MINOR DEC(__TI_COMPILER_VERSION__/1000   % 1000)
# define COMPILER_VERSION_PATCH DEC(__TI_COMPILER_VERSION__        % 1000)

#elif defined(__CLANG_FUJITSU)
# define COMPILER_ID "FujitsuClang"
# define COMPILER_VERSION_MAJOR DEC(__FCC_major__)
# define COMPILER_VERSION_MINOR DEC(__FCC_minor__)
# define COMPILER_VERSION_PATCH DEC(__FCC_patchlevel__)
# define COMPILER_VERSION_INTERNAL_STR __clang_version__


#elif defined(__FUJITSU)
# define COMPILER_ID "Fujitsu"
# if defined(__FCC_version__)
#   define COMPILER_VERSION __FCC_version__
# elif defined(__FCC_major__)
#   define COMPILER_VERSION_MAJOR DEC(__FCC_major__)
#   define COMPILER_VERSION_MINOR DEC(__FCC_minor__)
#   define COMPILER_VERSION_PATCH DEC(__FCC_patchlevel__)
# endif
# if defined(__fcc_version)
#   define COMPILER_VERSION_INTERNAL DEC(__fcc_version)
# elif defined(__FCC_VERSION)
#   define COMPILER_VERSION_INTERNAL DEC(__FCC_VERSION)
# endif


#elif defined(__ghs__)
# define COMPILER_ID "GHS"
/* __GHS_VERSION_NUMBER = VVVVRP */
# ifdef __GHS_VERSION_NUMBER
# define COMPILER_VERSION_MAJOR DEC(__GHS_VERSION_NUMBER / 100)
# define COMPILER_VERSION_MINOR DEC(__GHS_VERSION_NUMBER / 10 % 10)
# define COMPILER_VERSION_PATCH DEC(__GHS_VERSION_NUMBER      % 10)
# endif

#elif defined(__TASKING__)
# define COMPILER_ID "Tasking"
  # define COMPILER_VERSION_MAJOR DEC(__VERSION__/1000)
  # define COMPILER_VERSION_MINOR DEC(__VERSION__ % 100)
# define COMPILER_VERSION_INTERNAL DEC(__VERSION__)

#elif defined(__ORANGEC__)
# define COMPILER_ID "OrangeC"
# define COMPILER_VERSION_MAJOR DEC(__ORANGEC_MAJOR__)
# define COMPILER_VERSION_MINOR DEC(__ORANGEC_MINOR__)
# define COMPILER_VERSION_PATCH DEC(__ORANGEC_PATCHLEVEL__)

#elif defined(__RENESAS__)
# define COMPILER_ID "Renesas"
/* __RENESAS_VERSION__ = 0xVVRRPP00 */
# define COMPILER_VERSION_MAJOR HEX(__RENESAS_VERSION__ >> 24 & 0xFF)
# define COMPILER_VERSION_MINOR HEX(__RENESAS_VERSION__ >> 16 & 0xFF)
# define COMPILER_VERSION_PATCH HEX(__RENESAS_VERSION__ >> 8  & 0xFF)

#elif defined(__SCO_VERSION__)
# define COMPILER_ID "SCO"

#elif defined(__ARMCC_VERSION) && !defined(__clang__)
# define COMPILER_ID "ARMCC"
#if __ARMCC_VERSION >= 1000000
  /* __ARMCC_VERSION = VRRPPPP */
  # define COMPILER_VERSION_MAJOR DEC(__ARMCC_VERSION/1000000)
  # define COMPILER_VERSION_MINOR DEC(__ARMCC_VERSION/10000 % 100)
  # define COMPILER_VERSION_PATCH DEC(__ARMCC_VERSION     % 10000)
#else
  /* __ARMCC_VERSION = VRPPPP */
  # define COMPILER_VERSION_MAJOR DEC(__ARMCC_VERSION/100000)
  # define COMPILER_VERSION_MINOR DEC(__ARMCC_VERSION/10000 % 10)
  # define COMPILER_VERSION_PATCH DEC(__ARMCC_VERSION    % 10000)
#endif


#elif defined(__clang__) && defined(__apple_build_version__)
# define COMPILER_ID "AppleClang"
# if defined(_MSC_VER)
#  define SIMULATE_ID "MSVC"
# endif
# define COMPILER_VERSION_MAJOR DEC(__clang_major__)
# define COMPILER_VERSION_MINOR DEC(__clang_minor__)
# define COMPILER_VERSION_PATCH DEC(__clang_patchlevel__)
# if defined(_MSC_VER)
   /* _MSC_VER = VVRR */
#  define SIMULATE_VERSION_MAJOR DEC(_MSC_VER / 100)
#  define SIMULATE_VERSION_MINOR DEC(_MSC_VER % 100)
# endif
# define COMPILER_VERSION_TWEAK DEC(__apple_build_version__)

#elif defined(__clang__) && defined(__ARMCOMPILER_VERSION)
# define COMPILER_ID "ARMClang"
  # define COMPILER_VERSION_MAJOR DEC(__ARMCOMPILER_VERSION/1000000)
  # define COMPILER_VERSION_MINOR DEC(__ARMCOMPILER_VERSION/10000 % 100)
  # define COMPILER_VERSION_PATCH DEC(__ARMCOMPILER_VERSION/100   % 100)
# define COMPILER_VERSION_INTERNAL DEC(__ARMCOMPILER_VERSION)

#elif defined(__clang__) && defined(__ti__)
# define COMPILER_ID "TIClang"
  # define COMPILER_VERSION_MAJOR DEC(__ti_major__)
  # define COMPILER_VERSION_MINOR DEC(__ti_minor__)
  # define COMPILER_VERSION_PATCH DEC(__ti_patchlevel__)
# define COMPILER_VERSION_INTERNAL DEC(__ti_version__)

#elif defined(__clang__)
# define COMPILER_ID "Clang"
# if defined(_MSC_VER)
#  define SIMULATE_ID "MSVC"
# endif
# define COMPILER_VERSION_MAJOR DEC(__clang_major__)
# define COMPILER_VERSION_MINOR DEC(__clang_minor__)
# define COMPILER_VERSION_PATCH DEC(__clang_patchlevel__)
# if defined(_MSC_VER)
   /* _MSC_VER = VVRR */
#  define SIMULATE_VERSION_MAJOR DEC(_MSC_VER / 100)
#  define SIMULATE_VERSION_MINOR DEC(_MSC_VER % 100)
# endif

#elif defined(__LCC__) && (defined(__GNUC__) || defined(__GNUG__) || defined(__MCST__))
# define COMPILER_ID "LCC"
# define COMPILER_VERSION_MAJOR DEC(__LCC__ / 100)
# define COMPILER_VERSION_MINOR DEC(__LCC__ % 100)
# if defined(__LCC_MINOR__)
#  define COMPILER_VERSION_PATCH DEC(__LCC_MINOR__)
# endif
# if defined(__GNUC__) && defined(__GNUC_MINOR__)
#  define SIMULATE_ID "GNU"
#  define SIMULATE_VERSION_MAJOR DEC(__GNUC__)
#  define SIMULATE_VERSION_MINOR DEC(__GNUC_MINOR__)
#  if defined(__GNUC_PATCHLEVEL__)
#   define SIMULATE_VERSION_PATCH DEC(__GNUC_PATCHLEVEL__)
#  endif
# endif

#elif defined(__GNUC__) || defined(__GNUG__)
# define COMPILER_ID "GNU"
# if defined(__GNUC__)
#  define COMPILER_VERSION_MAJOR DEC(__GNUC__)
# else
#  define COMPILER_VERSION_MAJOR DEC(__GNUG__)
# endif
# if defined(__GNUC_MINOR__)
#  define COMPILER_VERSION_MINOR DEC(__GNUC_MINOR__)
# endif
# if defined(__GNUC_PATCHLEVEL__)
#  define COMPILER_VERSION_PATCH DEC(__GNUC_PATCHLEVEL__)
# endif

#elif defined(_MSC_VER)
# define COMPILER_ID "MSVC"
  /* _MSC_VER = VVRR */
# define COMPILER_VERSION_MAJOR DEC(_MSC_VER / 100)
# define COMPILER_VERSION_MINOR DEC(_MSC_VER % 100)
# if defined(_MSC_FULL_VER)
#  if _MSC_VER >= 1400
    /* _MSC_FULL_VER = VVRRPPPPP */
#   define COMPILER_VERSION_PATCH DEC(_MSC_FULL_VER % 100000)
#  else
    /* _MSC_FULL_VER = VVRRPPPP */
#   define COMPILER_VERSION_PATCH DEC(_MSC_FULL_VER % 10000)
#  endif
# endif
# if defined(_MSC_BUILD)
#  define COMPILER_VERSION_TWEAK DEC(_MSC_BUILD)
# endif

#elif defined(_ADI_COMPILER)
# define COMPILER_ID "ADSP"
#if defined(__VERSIONNUM__)
  /* __VERSIONNUM__ = 0xVVRRPPTT */
#  define COMPILER_VERSION_MAJOR DEC(__VERSIONNUM__ >> 24 & 0xFF)
#  define COMPILER_VERSION_MINOR DEC(__VERSIONNUM__ >> 16 & 0xFF)
#  define COMPILER_VERSION_PATCH DEC(__VERSIONNUM__ >> 8 & 0xFF)
#  define COMPILER_VERSION_TWEAK DEC(__VERSIONNUM__ & 0xFF)
#endif

#elif defined(__IAR_SYSTEMS_ICC__) || defined(__IAR_SYSTEMS_ICC)
# define COMPILER_ID "IAR"
# if defined(__VER__) && defined(__ICCARM__)
#  define COMPILER_VERSION_MAJOR DEC((__VER__) / 1000000)
#  define COMPILER_VERSION_MINOR DEC(((__VER__) / 1000) % 1000)
#  define COMPILER_VERSION_PATCH DEC((__VER__) % 1000)
#  define COMPILER_VERSION_INTERNAL DEC(__IAR_SYSTEMS_ICC__)
# elif defined(__VER__) && (defined(__ICCAVR__) || defined(__ICCRX__) || defined(__ICCRH850__) || defined(__ICCRL78__) || defined(__ICC430__) || defined(__ICCRISCV__) || defined(__ICCV850__) || defined(__ICC8051__) || defined(__ICCSTM8__))
#  define COMPILER_VERSION_MAJOR DEC((__VER__) / 100)
#  define COMPILER_VERSION_MINOR DEC((__VER__) - (((__VER__) / 100)*100))
#  define COMPILER_VERSION_PATCH DEC(__SUBVERSION__)
#  define COMPILER_VERSION_INTERNAL DEC(__IAR_SYSTEMS_ICC__)
# endif

#elif defined(__DCC__) && defined(_DIAB_TOOL)
# define COMPILER_ID "Diab"
  # define COMPILER_VERSION_MAJOR DEC(__VERSION_MAJOR_NUMBER__)
  # define COMPILER_VERSION_MINOR DEC(__VERSION_MINOR_NUMBER__)
  # define COMPILER_VERSION_PATCH DEC(__VERSION_ARCH_FEATURE_NUMBER__)
  # define COMPILER_VERSION_TWEAK DEC(__VERSION_BUG_FIX_NUMBER__)



/* These compilers are either not known or too old to define an
  identification macro.  Try to identify the platform and guess that
  it is the native compiler.  */
#elif defined(__hpux) || defined(__hpua)
# define COMPILER_ID "HP"

#else /* unknown compiler */
# define COMPILER_ID ""
#endif

/* Construct the string literal in pieces to prevent the source from
   getting matched.  Store it in a pointer rather than an array
   because some compilers will just produce instructions to fill the
   array rather than assigning a pointer to a static array.  */
char const* info_compiler = "INFO" ":" "compiler[" COMPILER_ID "]";
#ifdef SIMULATE_ID
char const* info_simulate = "INFO" ":" "simulate[" SIMULATE_ID "]";
#endif

#ifdef __QNXNTO__
char const* qnxnto = "INFO" ":" "qnxnto[]";
#endif

#if defined(__CRAYXT_COMPUTE_LINUX_TARGET)
char const *info_cray = "INFO" ":" "compiler_wrapper[CrayPrgEnv]";
#endif

#define STRINGIFY_HELPER(X) #X
#define STRINGIFY(X) STRINGIFY_HELPER(X)

/* Identify known platforms by name.  */
#if defined(__linux) || defined(__linux__) || defined(linux)
# define PLATFORM_ID "Linux"

#elif defined(__MSYS__)
# define PLATFORM_ID "MSYS"

#elif defined(__CYGWIN__)
# define PLATFORM_ID "Cygwin"

#elif defined(__MINGW32__)
# define PLATFORM_ID "MinGW"

#elif defined(__APPLE__)
# define PLATFORM_ID "Darwin"

#elif defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
# define PLATFORM_ID "Windows"

#elif defined(__FreeBSD__) || defined(__FreeBSD)
# define PLATFORM_ID "FreeBSD"

#elif defined(__NetBSD__) || defined(__NetBSD)
# define PLATFORM_ID "NetBSD"

#elif defined(__OpenBSD__) || defined(__OPENBSD)
# define PLATFORM_ID "OpenBSD"

#elif defined(__sun) || defined(sun)
# define PLATFORM_ID "SunOS"

#elif defined(_AIX) || defined(__AIX) || defined(__AIX__) || defined(__aix) || defined(__aix__)
# define PLATFORM_ID "AIX"

#elif defined(__hpux) || defined(__hpux__)
# define PLATFORM_ID "HP-UX"

#elif defined(__HAIKU__)
# define PLATFORM_ID "Haiku"

#elif defined(__BeOS) || defined(__BEOS__) || defined(_BEOS)
# define PLATFORM_ID "BeOS"

#elif defined(__QNX__) || defined(__QNXNTO__)
# define PLATFORM_ID "QNX"

#elif defined(__tru64) || defined(_tru64) || defined(__TRU64__)
# define PLATFORM_ID "Tru64"

#elif defined(__riscos) || defined(__riscos__)
# define PLATFORM_ID "RISCos"

#elif defined(__sinix) || defined(__sinix__) || defined(__SINIX__)
# define PLATFORM_ID "SINIX"

#elif defined(__UNIX_SV__)
# define PLATFORM_ID "UNIX_SV"

#elif defined(__bsdos__)
# define PLATFORM_ID "BSDOS"

#elif defined(_MPRAS) || defined(MPRAS)
# define PLATFORM_ID "MP-RAS"

#elif defined(__osf) || defined(__osf__)
# define PLATFORM_ID "OSF1"

#elif defined(_SCO_SV) || defined(SCO_SV) || defined(sco_sv)
# define PLATFORM_ID "SCO_SV"

#elif defined(__ultrix) || defined(__ultrix__) || defined(_ULTRIX)
# define PLATFORM_ID "ULTRIX"

#elif defined(__XENIX__) || defined(_XENIX) || defined(XENIX)
# define PLATFORM_ID "Xenix"

#elif defined(__WATCOMC__)
# if defined(__LINUX__)
#  define PLATFORM_ID "Linux"

# elif defined(__DOS__)
#  define PLATFORM_ID "DOS"

# elif defined(__OS2__)
#  define PLATFORM_ID "OS2"

# elif defined(__WINDOWS__)
#  define PLATFORM_ID "Windows3x"

# elif defined(__VXWORKS__)
#  define PLATFORM_ID "VxWorks"

# else /* unknown platform */
#  define PLATFORM_ID
# endif

#elif defined(__INTEGRITY)
# if defined(INT_178B)
#  define PLATFORM_ID "Integrity178"

# else /* regular Integrity */
#  define PLATFORM_ID "Integrity"
# endif

# elif defined(_ADI_COMPILER)
#  define PLATFORM_ID "ADSP"

#else /* unknown platform */
# define PLATFORM_ID

#endif

/* For windows compilers MSVC and Intel we can determine
   the architecture of the compiler being used.  This is because
   the compilers do not have flags that can change the architecture,
   but rather depend on which compiler is being used
*/
#if defined(_WIN32) && defined(_MSC_VER)
# if defined(_M_IA64)
#  define ARCHITECTURE_ID "IA64"

# elif defined(_M_ARM64EC)
#  define ARCHITECTURE_ID "ARM64EC"

# elif defined(_M_X64) || defined(_M_AMD64)
#  define ARCHITECTURE_ID "x64"

# elif defined(_M_IX86)
#  define ARCHITECTURE_ID "X86"

# elif defined(_M_ARM64)
#  define ARCHITECTURE_ID "ARM64"

# elif defined(_M_ARM)
#  if _M_ARM == 4
#   define ARCHITECTURE_ID "ARMV4I"
#  elif _M_ARM == 5
#   define ARCHITECTURE_ID "ARMV5I"
#  else
#   define ARCHITECTURE_ID "ARMV" STRINGIFY(_M_ARM)
#  endif

# elif defined(_M_MIPS)
#  define ARCHITECTURE_ID "MIPS"

# elif defined(_M_SH)
#  define ARCHITECTURE_ID "SHx"

# else /* unknown architecture */
#  define ARCHITECTURE_ID ""
# endif

#elif defined(__WATCOMC__)
# if defined(_M_I86)
#  define ARCHITECTURE_ID "I86"

# elif defined(_M_IX86)
#  define ARCHITECTURE_ID "X86"

# else /* unknown architecture */
#  define ARCHITECTURE_ID ""
# endif

#elif defined(__IAR_SYSTEMS_ICC__) || defined(__IAR_SYSTEMS_ICC)
# if defined(__ICCARM__)
#  define ARCHITECTURE_ID "ARM"

# elif defined(__ICCRX__)
#  define ARCHITECTURE_ID "RX"

# elif defined(__ICCRH850__)
#  define ARCHITECTURE_ID "RH850"

# elif defined(__ICCRL78__)
#  define ARCHITECTURE_ID "RL78"

# elif defined(__ICCRISCV__)
#  define ARCHITECTURE_ID "RISCV"

# elif defined(__ICCAVR__)
#  define ARCHITECTURE_ID "AVR"

# elif defined(__ICC430__)
#  define ARCHITECTURE_ID "MSP430"

# elif defined(__ICCV850__)
#  define ARCHITECTURE_ID "V850"

# elif defined(__ICC8051__)
#  define ARCHITECTURE_ID "8051"

# elif defined(__ICCSTM8__)
#  define ARCHITECTURE_ID "STM8"

# else /* unknown architecture */
#  define ARCHITECTURE_ID ""
# endif

#elif defined(__ghs__)
# if defined(__PPC64__)
#  define ARCHITECTURE_ID "PPC64"

# elif defined(__ppc__)
#  define ARCHITECTURE_ID "PPC"

# elif defined(__ARM__)
#  define ARCHITECTURE_ID "ARM"

# elif defined(__x86_64__)
#  define ARCHITECTURE_ID "x64"

# elif defined(__i386__)
#  define ARCHITECTURE_ID "X86"

# else /* unknown architecture */
#  define ARCHITECTURE_ID ""
# endif

#elif defined(__clang__) && defined(__ti__)
# if defined(__ARM_ARCH)
#  define ARCHITECTURE_ID "ARM"

# else /* unknown architecture */
#  define ARCHITECTURE_ID ""
# endif

#elif defined(__TI_COMPILER_VERSION__)
# if defined(__TI_ARM__)
#  define ARCHITECTURE_ID "ARM"

# elif defined(__MSP430__)
#  define ARCHITECTURE_ID "MSP430"

# elif defined(__TMS320C28XX__)
#  define ARCHITECTURE_ID "TMS320C28x"

# elif defined(__TMS320C6X__) || defined(_TMS320C6X)
#  define ARCHITECTURE_ID "TMS320C6x"

# else /* unknown architecture */
#  define ARCHITECTURE_ID ""
# endif

# elif defined(__ADSPSHARC__)
#  define ARCHITECTURE_ID "SHARC"

# elif defined(__ADSPBLACKFIN__)
#  define ARCHITECTURE_ID "Blackfin"

#elif defined(__TASKING__)

# if defined(__CTC__) || defined(__CPTC__)
#  define ARCHITECTURE_ID "TriCore"

# elif defined(__CMCS__)
#  define ARCHITECTURE_ID "MCS"

# elif defined(__CARM__) || defined(__CPARM__)
#  define ARCHITECTURE_ID "ARM"

# elif defined(__CARC__)
#  define ARCHITECTURE_ID "ARC"

# elif defined(__C51__)
#  define ARCHITECTURE_ID "8051"

# elif defined(__CPCP__)
#  define ARCHITECTURE_ID "PCP"

# else
#  define ARCHITECTURE_ID ""
# endif

#elif defined(__RENESAS__)
# if defined(__CCRX__)
#  define ARCHITECTURE_ID "RX"

# elif defined(__CCRL__)
#  define ARCHITECTURE_ID "RL78"

# elif defined(__CCRH__)
#  define ARCHITECTURE_ID "RH850"

# else
#  define ARCHITECTURE_ID ""
# endif

#else
#  define ARCHITECTURE_ID
#endif

/* Convert integer to decimal digit literals.  */
#define DEC(n)                   \
  ('0' + (((n) / 10000000)%10)), \
  ('0' + (((n) / 1000000)%10)),  \
  ('0' + (((n) / 100000)%10)),   \
  ('0' + (((n) / 10000)%10)),    \
  ('0' + (((n) / 1000)%10)),     \
  ('0' + (((n) / 100)%10)),      \
  ('0' + (((n) / 10)%10)),       \
  ('0' +  ((n) % 10))

/* Convert integer to hex digit literals.  */
#define HEX(n)             \
  ('0' + ((n)>>28 & 0xF)), \
  ('0' + ((n)>>24 & 0xF)), \
  ('0' + ((n)>>20 & 0xF)), \
  ('0' + ((n)>>16 & 0xF)), \
  ('0' + ((n)>>12 & 0xF)), \
  ('0' + ((n)>>8  & 0xF)), \
  ('0' + ((n)>>4  & 0xF)), \
  ('0' + ((n)     & 0xF))

/* Construct a string literal encoding the version number. */
#ifdef COMPILER_VERSION
char const* info_version = "INFO" ":" "compiler_version[" COMPILER_VERSION "]";

/* Construct a string literal encoding the version number components. */
#elif defined(COMPILER_VERSION_MAJOR)
char const info_version[] = {
  'I', 'N', 'F', 'O', ':',
  'c','o','m','p','i','l','e','r','_','v','e','r','s','i','o','n','[',
  COMPILER_VERSION_MAJOR,
# ifdef COMPILER_VERSION_MINOR
  '.', COMPILER_VERSION_MINOR,
#  ifdef COMPILER_VERSION_PATCH
   '.', COMPILER_VERSION_PATCH,
#   ifdef COMPILER_VERSION_TWEAK
    '.', COMPILER_VERSION_TWEAK,
#   endif
#  endif
# endif
  ']','\0'};
#endif

/* Construct a string literal encoding the internal version number. */
#ifdef COMPILER_VERSION_INTERNAL
char const info_version_internal[] = {
  'I', 'N', 'F', 'O', ':',
  'c','o','m','p','i','l','e','r','_','v','e','r','s','i','o','n','_',
  'i','n','t','e','r','n','a','l','[',
  COMPILER_VERSION_INTERNAL,']','\0'};
#elif defined(COMPILER_VERSION_INTERNAL_STR)
char const* info_version_internal = "INFO" ":" "compiler_version_internal[" COMPILER_VERSION_INTERNAL_STR "]";
#endif

/* Construct a string literal encoding the version number components. */
#ifdef SIMULATE_VERSION_MAJOR
char const info_simulate_version[] = {
  'I', 'N', 'F', 'O', ':',
  's','i','m','u','l','a','t','e','_','v','e','r','s','i','o','n','[',
  SIMULATE_VERSION_MAJOR,
# ifdef SIMULATE_VERSION_MINOR
  '.', SIMULATE_VERSION_MINOR,
#  ifdef SIMULATE_VERSION_PATCH
   '.', SIMULATE_VERSION_PATCH,
#   ifdef SIMULATE_VERSION_TWEAK
    '.', SIMULATE_VERSION_TWEAK,
#   endif
#  endif
# endif
  ']','\0'};
#endif

/* Construct the string literal in pieces to prevent the source from
   getting matched.  Store it in a pointer rather than an array
   because some compilers will just produce instructions to fill the
   array rather than assigning a pointer to a static array.  */
char const* info_platform = "INFO" ":" "platform[" PLATFORM_ID "]";
char const* info_arch = "INFO" ":" "arch[" ARCHITECTURE_ID "]";



#define CXX_STD_98 199711L
#define CXX_STD_11 201103L
#define CXX_STD_14 201402L
#define CXX_STD_17 201703L
#define CXX_STD_20 202002L
#define CXX_STD_23 202302L

#if defined(__INTEL_COMPILER) && defined(_MSVC_LANG)
#  if _MSVC_LANG > CXX_STD_17
#    define CXX_STD _MSVC_LANG
#  elif _MSVC_LANG == CXX_STD_17 && defined(__cpp_aggregate_paren_init)
#    define CXX_STD CXX_STD_20
#  elif _MSVC_LANG > CXX_STD_14 && __cplusplus > CXX_STD_17
#    define CXX_STD CXX_STD_20
#  elif _MSVC_LANG > CXX_STD_14
#    define CXX_STD CXX_STD_17
#  elif defined(__INTEL_CXX11_MODE__) && defined(__cpp_aggregate_nsdmi)
#    define CXX_STD CXX_STD_14
#  elif defined(__INTEL_CXX11_MODE__)
#    define CXX_STD CXX_STD_11
#  else
#    define CXX_STD CXX_STD_98
#  endif
#elif defined(_MSC_VER) && defined(_MSVC_LANG)
#  if _MSVC_LANG > __cplusplus
#    define CXX_STD _MSVC_LANG
#  else
#    define CXX_STD __cplusplus
#  endif
#elif defined(__NVCOMPILER)
#  if __cplusplus == CXX_STD_17 && defined(__cpp_aggregate_paren_init)
#    define CXX_STD CXX_STD_20
#  else
#    define CXX_STD __cplusplus
#  endif
#elif defined(__INTEL_COMPILER) || defined(__PGI)
#  if __cplusplus == CXX_STD_11 && defined(__cpp_namespace_attributes)
#    define CXX_STD CXX_STD_17
#  elif __cplusplus == CXX_STD_11 && defined(__cpp_aggregate_nsdmi)
#    define CXX_STD CXX_STD_14
#  else
#    define CXX_STD __cplusplus
#  endif
#elif (defined(__IBMCPP__) || defined(__ibmxl__)) && defined(__linux__)
#  if __cplusplus == CXX_STD_11 && defined(__cpp_aggregate_nsdmi)
#    define CXX_STD CXX_STD_14
#  else
#    define CXX_STD __cplusplus
#  endif
#elif __cplusplus == 1 && defined(__GXX_EXPERIMENTAL_CXX0X__)
#  define CXX_STD CXX_STD_11
#else
#  define CXX_STD __cplusplus
#endif

const char* info_language_standard_default = "INFO" ":" "standard_default["
#if CXX_STD > CXX_STD_23
  "26"
#elif CXX_STD > CXX_STD_20
  "23"
#elif CXX_STD > CXX_STD_17
  "20"
#elif CXX_STD > CXX_STD_14
  "17"
#elif CXX_STD > CXX_STD_11
  "14"
#elif CXX_STD >= CXX_STD_11
  "11"
#else
  "98"
#endif
"]";

const char* info_language_extensions_default = "INFO" ":" "extensions_default["
#if (defined(__clang__) || defined(__GNUC__) || defined(__xlC__) ||           \
     defined(__TI_COMPILER_VERSION__) || defined(__RENESAS__)) &&             \
  !defined(__STRICT_ANSI__)
  "ON"
#else
  "OFF"
#endif
"]";

/*--------------------------------------------------------------------------*/

int main(int argc, char* argv[])
{
  int require = 0;
  require += info_compiler[argc];
  require += info_platform[argc];
  require += info_arch[argc];
#ifdef COMPILER_VERSION_MAJOR
  require += info_version[argc];
#endif
#if defined(COMPILER_VERSION_INTERNAL) || defined(COMPILER_VERSION_INTERNAL_STR)
  require += info_version_internal[argc];
#endif
#ifdef SIMULATE_ID
  require += info_simulate[argc];
#endif
#ifdef SIMULATE_VERSION_MAJOR
  require += info_simulate_version[argc];
#endif
#if defined(__CRAYXT_COMPUTE_LINUX_TARGET)
  require += info_cray[argc];
#endif
  require += info_language_standard_default[argc];
  require += info_language_extensions_default[argc];
  (void)argv;
  return require;
}

/* This source file must have a .cpp extension so that all C++ compilers
   recognize the extension without flags.  Borland does not know .cxx for
   example.  */
#ifndef __cplusplus
# error "A C compiler has been selected for C++."
#endif

#if !defined(__has_include)
/* If the compiler does not have __has_include, pretend the answer is
   always no.  */
#  define __has_include(x) 0
#endif


/* Version number components: V=Version, R=Revision, P=Patch
   Version date components:   YYYY=Year, MM=Month,   DD=Day  */

#if defined(__INTEL_COMPILER) || defined(__ICC)
# define COMPILER_ID "Intel"
# if defined(_MSC_VER)
#  define SIMULATE_ID "MSVC"
# endif
# if defined(__GNUC__)
#  define SIMULATE_ID "GNU"
# endif
  /* __INTEL_COMPILER = VRP prior to 2021, and then VVVV for 2021 and later,
     except that a few beta releases use the old format with V=2021.  */
# if __INTEL_COMPILER < 2021 || __INTEL_COMPILER == 202110 || __INTEL_COMPILER == 202111
#  define COMPILER_VERSION_MAJOR DEC(__INTEL_COMPILER/100)
#  define COMPILER_VERSION_MINOR DEC(__INTEL_COMPILER/10 % 10)
#  if defined(__INTEL_COMPILER_UPDATE)
#   define COMPILER_VERSION_PATCH DEC(__INTEL_COMPILER_UPDATE)
#  else
#   define COMPILER_VERSION_PATCH DEC(__INTEL_COMPILER   % 10)
#  endif
# else
#  define COMPILER_VERSION_MAJOR DEC(__INTEL_COMPILER)
#  define COMPILER_VERSION_MINOR DEC(__INTEL_COMPILER_UPDATE)
   /* The third version component from --version is an update index,
      but no macro is provided for it.  */
#  define COMPILER_VERSION_PATCH DEC(0)
# endif
# if defined(__INTEL_COMPILER_BUILD_DATE)
   /* __INTEL_COMPILER_BUILD_DATE = YYYYMMDD */
#  define COMPILER_VERSION_TWEAK DEC(__INTEL_COMPILER_BUILD_DATE)
# endif
# if defined(_MSC_VER)
   /* _MSC_VER = VVRR */
#  define SIMULATE_VERSION_MAJOR DEC(_MSC_VER / 100)
#  define SIMULATE_VERSION_MINOR DEC(_MSC_VER % 100)
# endif
# if defined(__GNUC__)
#  define SIMULATE_VERSION_MAJOR DEC(__GNUC__)
# elif defined(__GNUG__)
#  define SIMULATE_VERSION_MAJOR DEC(__GNUG__)
# endif
# if defined(__GNUC_MINOR__)
#  define SIMULATE_VERSION_MINOR DEC(__GNUC_MINOR__)
# endif
# if defined(__GNUC_PATCHLEVEL__)
#  define SIMULATE_VERSION_PATCH DEC(__GNUC_PATCHLEVEL__)
# endif

#elif (defined(__clang__) && defined(__INTEL_CLANG_COMPILER)) || defined(__INTEL_LLVM_COMPILER)
# define COMPILER_ID "IntelLLVM"
#if defined(_MSC_VER)
# define SIMULATE_ID "MSVC"
#endif
#if defined(__GNUC__)
# define SIMULATE_ID "GNU"
#endif
/* __INTEL_LLVM_COMPILER = VVVVRP prior to 2021.2.0, VVVVRRPP for 2021.2.0 and
 * later.  Look for 6 digit vs. 8 digit version number to decide encoding.
 * VVVV is no smaller than the current year when a version is released.
 */
#if __INTEL_LLVM_COMPILER < 1000000L
# define COMPILER_VERSION_MAJOR DEC(__INTEL_LLVM_COMPILER/100)
# define COMPILER_VERSION_MINOR DEC(__INTEL_LLVM_COMPILER/10 % 10)
# define COMPILER_VERSION_PATCH DEC(__INTEL_LLVM_COMPILER    % 10)
#else
# define COMPILER_VERSION_MAJOR DEC(__INTEL_LLVM_COMPILER/10000)
# define COMPILER_VERSION_MINOR DEC(__INTEL_LLVM_COMPILER/100 % 100)
# define COMPILER_VERSION_PATCH DEC(__INTEL_LLVM_COMPILER     % 100)
#endif
#if defined(_MSC_VER)
  /* _MSC_VER = VVRR */
# define SIMULATE_VERSION_MAJOR DEC(_MSC_VER / 100)
# define SIMULATE_VERSION_MINOR DEC(_MSC_VER % 100)
#endif
#if defined(__GNUC__)
# define SIMULATE_VERSION_MAJOR DEC(__GNUC__)
#elif defined(__GNUG__)
# define SIMULATE_VERSION_MAJOR DEC(__GNUG__)
#endif
#if defined(__GNUC_MINOR__)
# define SIMULATE_VERSION_MINOR DEC(__GNUC_MINOR__)
#endif
#if defined(__GNUC_PATCHLEVEL__)
# define SIMULATE_VERSION_PATCH DEC(__GNUC_PATCHLEVEL__)
#endif

#elif defined(__PATHCC__)
# define COMPILER_ID "PathScale"
# define COMPILER_VERSION_MAJOR DEC(__PATHCC__)
# define COMPILER_VERSION_MINOR DEC(__PATHCC_MINOR__)
# if defined(__PATHCC_PATCHLEVEL__)
#  define COMPILER_VERSION_PATCH DEC(__PATHCC_PATCHLEVEL__)
# endif

#elif defined(__BORLANDC__) && defined(__CODEGEARC_VERSION__)
# define COMPILER_ID "Embarcadero"
# define COMPILER_VERSION_MAJOR HEX(__CODEGEARC_VERSION__>>24 & 0x00FF)
# define COMPILER_VERSION_MINOR HEX(__CODEGEARC_VERSION__>>16 & 0x00FF)
# define COMPILER_VERSION_PATCH DEC(__CODEGEARC_VERSION__     & 0xFFFF)

#elif defined(__BORLANDC__)
# define COMPILER_ID "Borland"
  /* __BORLANDC__ = 0xVRR */
# define COMPILER_VERSION_MAJOR HEX(__BORLANDC__>>8)
# define COMPILER_VERSION_MINOR HEX(__BORLANDC__ & 0xFF)

#elif defined(__WATCOMC__) && __WATCOMC__ < 1200
# define COMPILER_ID "Watcom"
   /* __WATCOMC__ = VVRR */
# define COMPILER_VERSION_MAJOR DEC(__WATCOMC__ / 100)
# define COMPILER_VERSION_MINOR DEC((__WATCOMC__ / 10) % 10)
# if (__WATCOMC__ % 10) > 0
#  define COMPILER_VERSION_PATCH DEC(__WATCOMC__ % 10)
# endif

#elif defined(__WATCOMC__)
# define COMPILER_ID "OpenWatcom"
   /* __WATCOMC__ = VVRP + 1100 */
# define COMPILER_VERSION_MAJOR DEC((__WATCOMC__ - 1100) / 100)
# define COMPILER_VERSION_MINOR DEC((__WATCOMC__ / 10) % 10)
# if (__WATCOMC__ % 10) > 0
#  define COMPILER_VERSION_PATCH DEC(__WATCOMC__ % 10)
# endif

#elif defined(__SUNPRO_CC)
# define COMPILER_ID "SunPro"
# if __SUNPRO_CC >= 0x5100
   /* __SUNPRO_CC = 0xVRRP */
#  define COMPILER_VERSION_MAJOR HEX(__SUNPRO_CC>>12)
#  define COMPILER_VERSION_MINOR HEX(__SUNPRO_CC>>4 & 0xFF)
#  define COMPILER_VERSION_PATCH HEX(__SUNPRO_CC    & 0xF)
# else
   /* __SUNPRO_CC = 0xVRP */
#  define COMPILER_VERSION_MAJOR HEX(__SUNPRO_CC>>8)
#  define COMPILER_VERSION_MINOR HEX(__SUNPRO_CC>>4 & 0xF)
#  define COMPILER_VERSION_PATCH HEX(__SUNPRO_CC    & 0xF)
# endif

#elif defined(__HP_aCC)
# define COMPILER_ID "HP"
  /* __HP_aCC = VVRRPP */
# define COMPILER_VERSION_MAJOR DEC(__HP_aCC/10000)
# define COMPILER_VERSION_MINOR DEC(__HP_aCC/100 % 100)
# define COMPILER_VERSION_PATCH DEC(__HP_aCC     % 100)

#elif defined(__DECCXX)
# define COMPILER_ID "Compaq"
  /* __DECCXX_VER = VVRRTPPPP */
# define COMPILER_VERSION_MAJOR DEC(__DECCXX_VER/10000000)
# define COMPILER_VERSION_MINOR DEC(__DECCXX_VER/100000  % 100)
# define COMPILER_VERSION_PATCH DEC(__DECCXX_VER         % 10000)

#elif defined(__IBMCPP__) && defined(__COMPILER_VER__)
# define COMPILER_ID "zOS"
  /* __IBMCPP__ = VRP */
# define COMPILER_VERSION_MAJOR DEC(__IBMCPP__/100)
# define COMPILER_VERSION_MINOR DEC(__IBMCPP__/10 % 10)
# define COMPILER_VERSION_PATCH DEC(__IBMCPP__    % 10)

#elif defined(__open_xl__) && defined(__clang__)
# define COMPILER_ID "IBMClang"
# define COMPILER_VERSION_MAJOR DEC(__open_xl_version__)
# define COMPILER_VERSION_MINOR DEC(__open_xl_release__)
# define COMPILER_VERSION_PATCH DEC(__open_xl_modification__)
# define COMPILER_VERSION_TWEAK DEC(__open_xl_ptf_fix_level__)
# define COMPILER_VERSION_INTERNAL_STR  __clang_version__


#elif defined(__ibmxl__) && defined(__clang__)
# define COMPILER_ID "XLClang"
# define COMPILER_VERSION_MAJOR DEC(__ibmxl_version__)
# define COMPILER_VERSION_MINOR DEC(__ibmxl_release__)
# define COMPILER_VERSION_PATCH DEC(__ibmxl_modification__)
# define COMPILER_VERSION_TWEAK DEC(__ibmxl_ptf_fix_level__)


#elif defined(__IBMCPP__) && !defined(__COMPILER_VER__) && __IBMCPP__ >= 800
# define COMPILER_ID "XL"
  /* __IBMCPP__ = VRP */
# define COMPILER_VERSION_MAJOR DEC(__IBMCPP__/100)
# define COMPILER_VERSION_MINOR DEC(__IBMCPP__/10 % 10)
# define COMPILER_VERSION_PATCH DEC(__IBMCPP__    % 10)

#elif defined(__IBMCPP__) && !defined(__COMPILER_VER__) && __IBMCPP__ < 800
# define COMPILER_ID "VisualAge"
  /* __IBMCPP__ = VRP */
# define COMPILER_VERSION_MAJOR DEC(__IBMCPP__/100)
# define COMPILER_VERSION_MINOR DEC(__IBMCPP__/10 % 10)
# define COMPILER_VERSION_PATCH DEC(__IBMCPP__    % 10)

#elif defined(__NVCOMPILER)
# define COMPILER_ID "NVHPC"
# define COMPILER_VERSION_MAJOR DEC(__NVCOMPILER_MAJOR__)
# define COMPILER_VERSION_MINOR DEC(__NVCOMPILER_MINOR__)
# if defined(__NVCOMPILER_PATCHLEVEL__)
#  define COMPILER_VERSION_PATCH DEC(__NVCOMPILER_PATCHLEVEL__)
# endif

#elif defined(__PGI)
# define COMPILER_ID "PGI"
# define COMPILER_VERSION_MAJOR DEC(__PGIC__)
# define COMPILER_VERSION_MINOR DEC(__PGIC_MINOR__)
# if defined(__PGIC_PATCHLEVEL__)
#  define COMPILER_VERSION_PATCH DEC(__PGIC_PATCHLEVEL__)
# endif

#elif defined(__clang__) && defined(__cray__)
# define COMPILER_ID "CrayClang"
# define COMPILER_VERSION_MAJOR DEC(__cray_major__)
# define COMPILER_VERSION_MINOR DEC(__cray_minor__)
# define COMPILER_VERSION_PATCH DEC(__cray_patchlevel__)
# define COMPILER_VERSION_INTERNAL_STR __clang_version__


#elif defined(_CRAYC)
# define COMPILER_ID "Cray"
# define COMPILER_VERSION_MAJOR DEC(_RELEASE_MAJOR)
# define COMPILER_VERSION_MINOR DEC(_RELEASE_MINOR)

#elif defined(__TI_COMPILER_VERSION__)
# define COMPILER_ID "TI"
  /* __TI_COMPILER_VERSION__ = VVVRRRPPP */
# define COMPILER_VERSION_MAJOR DEC(__TI_COMPILER_VERSION__/1000000)
# define COMPILER_VERSION_MINOR DEC(__TI_COMPILER_VERSION__/1000   % 1000)
# define COMPILER_VERSION_PATCH DEC(__TI_COMPILER_VERSION__        % 1000)

#elif defined(__CLANG_FUJITSU)
# define COMPILER_ID "FujitsuClang"
# define COMPILER_VERSION_MAJOR DEC(__FCC_major__)
# define COMPILER_VERSION_MINOR DEC(__FCC_minor__)
# define COMPILER_VERSION_PATCH DEC(__FCC_patchlevel__)
# define COMPILER_VERSION_INTERNAL_STR __clang_version__


#elif defined(__FUJITSU)
# define COMPILER_ID "Fujitsu"
# if defined(__FCC_version__)
#   define COMPILER_VERSION __FCC_version__
# elif defined(__FCC_major__)
#   define COMPILER_VERSION_MAJOR DEC(__FCC_major__)
#   define COMPILER_VERSION_MINOR DEC(__FCC_minor__)
#   define COMPILER_VERSION_PATCH DEC(__FCC_patchlevel__)
# endif
# if defined(__fcc_version)
#   define COMPILER_VERSION_INTERNAL DEC(__fcc_version)
# elif defined(__FCC_VERSION)
#   define COMPILER_VERSION_INTERNAL DEC(__FCC_VERSION)
# endif


#elif defined(__ghs__)
# define COMPILER_ID "GHS"
/* __GHS_VERSION_NUMBER = VVVVRP */
# ifdef __GHS_VERSION_NUMBER
# define COMPILER_VERSION_MAJOR DEC(__GHS_VERSION_NUMBER / 100)
# define COMPILER_VERSION_MINOR DEC(__GHS_VERSION_NUMBER / 10 % 10)
# define COMPILER_VERSION_PATCH DEC(__GHS_VERSION_NUMBER      % 10)
# endif

#elif defined(__TASKING__)
# define COMPILER_ID "Tasking"
  # define COMPILER_VERSION_MAJOR DEC(__VERSION__/1000)
  # define COMPILER_VERSION_MINOR DEC(__VERSION__ % 100)
# define COMPILER_VERSION_INTERNAL DEC(__VERSION__)

#elif defined(__ORANGEC__)
# define COMPILER_ID "OrangeC"
# define COMPILER_VERSION_MAJOR DEC(__ORANGEC_MAJOR__)
# define COMPILER_VERSION_MINOR DEC(__ORANGEC_MINOR__)
# define COMPILER_VERSION_PATCH DEC(__ORANGEC_PATCHLEVEL__)

#elif defined(__RENESAS__)
# define COMPILER_ID "Renesas"
/* __RENESAS_VERSION__ = 0xVVRRPP00 */
# define COMPILER_VERSION_MAJOR HEX(__RENESAS_VERSION__ >> 24 & 0xFF)
# define COMPILER_VERSION_MINOR HEX(__RENESAS_VERSION__ >> 16 & 0xFF)
# define COMPILER_VERSION_PATCH HEX(__RENESAS_VERSION__ >> 8  & 0xFF)

#elif defined(__SCO_VERSION__)
# define COMPILER_ID "SCO"

#elif defined(__ARMCC_VERSION) && !defined(__clang__)
# define COMPILER_ID "ARMCC"
#if __ARMCC_VERSION >= 1000000
  /* __ARMCC_VERSION = VRRPPPP */
  # define COMPILER_VERSION_MAJOR DEC(__ARMCC_VERSION/1000000)
  # define COMPILER_VERSION_MINOR DEC(__ARMCC_VERSION/10000 % 100)
  # define COMPILER_VERSION_PATCH DEC(__ARMCC_VERSION     % 10000)
#else
  /* __ARMCC_VERSION = VRPPPP */
  # define COMPILER_VERSION_MAJOR DEC(__ARMCC_VERSION/100000)
  # define COMPILER_VERSION_MINOR DEC(__ARMCC_VERSION/10000 % 10)
  # define COMPILER_VERSION_PATCH DEC(__ARMCC_VERSION    % 10000)
#endif


#elif defined(__clang__) && defined(__apple_build_version__)
# define COMPILER_ID "AppleClang"
# if defined(_MSC_VER)
#  define SIMULATE_ID "MSVC"
# endif
# define COMPILER_VERSION_MAJOR DEC(__clang_major__)
# define COMPILER_VERSION_MINOR DEC(__clang_minor__)
# define COMPILER_VERSION_PATCH DEC(__clang_patchlevel__)
# if defined(_MSC_VER)
   /* _MSC_VER = VVRR */
#  define SIMULATE_VERSION_MAJOR DEC(_MSC_VER / 100)
#  define SIMULATE_VERSION_MINOR DEC(_MSC_VER % 100)
# endif
# define COMPILER_VERSION_TWEAK DEC(__apple_build_version__)

#elif defined(__clang__) && defined(__ARMCOMPILER_VERSION)
# define COMPILER_ID "ARMClang"
  # define COMPILER_VERSION_MAJOR DEC(__ARMCOMPILER_VERSION/1000000)
  # define COMPILER_VERSION_MINOR DEC(__ARMCOMPILER_VERSION/10000 % 100)
  # define COMPILER_VERSION_PATCH DEC(__ARMCOMPILER_VERSION/100   % 100)
# define COMPILER_VERSION_INTERNAL DEC(__ARMCOMPILER_VERSION)

#elif defined(__clang__) && defined(__ti__)
# define COMPILER_ID "TIClang"
  # define COMPILER_VERSION_MAJOR DEC(__ti_major__)
  # define COMPILER_VERSION_MINOR DEC(__ti_minor__)
  # define COMPILER_VERSION_PATCH DEC(__ti_patchlevel__)
# define COMPILER_VERSION_INTERNAL DEC(__ti_version__)

#elif defined(__clang__)
# define COMPILER_ID "Clang"
# if defined(_MSC_VER)
#  define SIMULATE_ID "MSVC"
# endif
# define COMPILER_VERSION_MAJOR DEC(__clang_major__)
# define COMPILER_VERSION_MINOR DEC(__clang_minor__)
# define COMPILER_VERSION_PATCH DEC(__clang_patchlevel__)
# if defined(_MSC_VER)
   /* _MSC_VER = VVRR */
#  define SIMULATE_VERSION_MAJOR DEC(_MSC_VER / 100)
#  define SIMULATE_VERSION_MINOR DEC(_MSC_VER % 100)
# endif

#elif defined(__LCC__) && (defined(__GNUC__) || defined(__GNUG__) || defined(__MCST__))
# define COMPILER_ID "LCC"
# define COMPILER_VERSION_MAJOR DEC(__LCC__ / 100)
# define COMPILER_VERSION_MINOR DEC(__LCC__ % 100)
# if defined(__LCC_MINOR__)
#  define COMPILER_VERSION_PATCH DEC(__LCC_MINOR__)
# endif
# if defined(__GNUC__) && defined(__GNUC_MINOR__)
#  define SIMULATE_ID "GNU"
#  define SIMULATE_VERSION_MAJOR DEC(__GNUC__)
#  define SIMULATE_VERSION_MINOR DEC(__GNUC_MINOR__)
#  if defined(__GNUC_PATCHLEVEL__)
#   define SIMULATE_VERSION_PATCH DEC(__GNUC_PATCHLEVEL__)
#  endif
# endif

#elif defined(__GNUC__) || defined(__GNUG__)
# define COMPILER_ID "GNU"
# if defined(__GNUC__)
#  define COMPILER_VERSION_MAJOR DEC(__GNUC__)
# else
#  define COMPILER_VERSION_MAJOR DEC(__GNUG__)
# endif
# if defined(__GNUC_MINOR__)
#  define COMPILER_VERSION_MINOR DEC(__GNUC_MINOR__)
# endif
# if defined(__GNUC_PATCHLEVEL__)
#  define COMPILER_VERSION_PATCH DEC(__GNUC_PATCHLEVEL__)
# endif

#elif defined(_MSC_VER)
# define COMPILER_ID "MSVC"
  /* _MSC_VER = VVRR */
# define COMPILER_VERSION_MAJOR DEC(_MSC_VER / 100)
# define COMPILER_VERSION_MINOR DEC(_MSC_VER % 100)
# if defined(_MSC_FULL_VER)
#  if _MSC_VER >= 1400
    /* _MSC_FULL_VER = VVRRPPPPP */
#   define COMPILER_VERSION_PATCH DEC(_MSC_FULL_VER % 100000)
#  else
    /* _MSC_FULL_VER = VVRRPPPP */
#   define COMPILER_VERSION_PATCH DEC(_MSC_FULL_VER % 10000)
#  endif
# endif
# if defined(_MSC_BUILD)
#  define COMPILER_VERSION_TWEAK DEC(_MSC_BUILD)
# endif

#elif defined(_ADI_COMPILER)
# define COMPILER_ID "ADSP"
#if defined(__VERSIONNUM__)
  /* __VERSIONNUM__ = 0xVVRRPPTT */
#  define COMPILER_VERSION_MAJOR DEC(__VERSIONNUM__ >> 24 & 0xFF)
#  define COMPILER_VERSION_MINOR DEC(__VERSIONNUM__ >> 16 & 0xFF)
#  define COMPILER_VERSION_PATCH DEC(__VERSIONNUM__ >> 8 & 0xFF)
#  define COMPILER_VERSION_TWEAK DEC(__VERSIONNUM__ & 0xFF)
#endif

#elif defined(__IAR_SYSTEMS_ICC__) || defined(__IAR_SYSTEMS_ICC)
# define COMPILER_ID "IAR"
# if defined(__VER__) && defined(__ICCARM__)
#  define COMPILER_VERSION_MAJOR DEC((__VER__) / 1000000)
#  define COMPILER_VERSION_MINOR DEC(((__VER__) / 1000) % 1000)
#  define COMPILER_VERSION_PATCH DEC((__VER__) % 1000)
#  define COMPILER_VERSION_INTERNAL DEC(__IAR_SYSTEMS_ICC__)
# elif defined(__VER__) && (defined(__ICCAVR__) || defined(__ICCRX__) || defined(__ICCRH850__) || defined(__ICCRL78__) || defined(__ICC430__) || defined(__ICCRISCV__) || defined(__ICCV850__) || defined(__ICC8051__) || defined(__ICCSTM8__))
#  define COMPILER_VERSION_MAJOR DEC((__VER__) / 100)
#  define COMPILER_VERSION_MINOR DEC((__VER__) - (((__VER__) / 100)*100))
#  define COMPILER_VERSION_PATCH DEC(__SUBVERSION__)
#  define COMPILER_VERSION_INTERNAL DEC(__IAR_SYSTEMS_ICC__)
# endif

#elif defined(__DCC__) && defined(_DIAB_TOOL)
# define COMPILER_ID "Diab"
  # define COMPILER_VERSION_MAJOR DEC(__VERSION_MAJOR_NUMBER__)
  # define COMPILER_VERSION_MINOR DEC(__VERSION_MINOR_NUMBER__)
  # define COMPILER_VERSION_PATCH DEC(__VERSION_ARCH_FEATURE_NUMBER__)
  # define COMPILER_VERSION_TWEAK DEC(__VERSION_BUG_FIX_NUMBER__)



/* These compilers are either not known or too old to define an
  identification macro.  Try to identify the platform and guess that
  it is the native compiler.  */
#elif defined(__hpux) || defined(__hpua)
# define COMPILER_ID "HP"

#else /* unknown compiler */
# define COMPILER_ID ""
#endif

/* Construct the string literal in pieces to prevent the source from
   getting matched.  Store it in a pointer rather than an array
   because some compilers will just produce instructions to fill the
   array rather than assigning a pointer to a static array.  */
char const* info_compiler = "INFO" ":" "compiler[" COMPILER_ID "]";
#ifdef SIMULATE_ID
char const* info_simulate = "INFO" ":" "simulate[" SIMULATE_ID "]";
#endif

#ifdef __QNXNTO__
char const* qnxnto = "INFO" ":" "qnxnto[]";
#endif

#if defined(__CRAYXT_COMPUTE_LINUX_TARGET)
char const *info_cray = "INFO" ":" "compiler_wrapper[CrayPrgEnv]";
#endif

#define STRINGIFY_HELPER(X) #X
#define STRINGIFY(X) STRINGIFY_HELPER(X)

/* Identify known platforms by name.  */
#if defined(__linux) || defined(__linux__) || defined(linux)
# define PLATFORM_ID "Linux"

#elif defined(__MSYS__)
# define PLATFORM_ID "MSYS"

#elif defined(__CYGWIN__)
# define PLATFORM_ID "Cygwin"

#elif defined(__MINGW32__)
# define PLATFORM_ID "MinGW"

#elif defined(__APPLE__)
# define PLATFORM_ID "Darwin"

#elif defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
# define PLATFORM_ID "Windows"

#elif defined(__FreeBSD__) || defined(__FreeBSD)
# define PLATFORM_ID "FreeBSD"

#elif defined(__NetBSD__) || defined(__NetBSD)
# define PLATFORM_ID "NetBSD"

#elif defined(__OpenBSD__) || defined(__OPENBSD)
# define PLATFORM_ID "OpenBSD"

#elif defined(__sun) || defined(sun)
# define PLATFORM_ID "SunOS"

#elif defined(_AIX) || defined(__AIX) || defined(__AIX__) || defined(__aix) || defined(__aix__)
# define PLATFORM_ID "AIX"

#elif defined(__hpux) || defined(__hpux__)
# define PLATFORM_ID "HP-UX"

#elif defined(__HAIKU__)
# define PLATFORM_ID "Haiku"

#elif defined(__BeOS) || defined(__BEOS__) || defined(_BEOS)
# define PLATFORM_ID "BeOS"

#elif defined(__QNX__) || defined(__QNXNTO__)
# define PLATFORM_ID "QNX"

#elif defined(__tru64) || defined(_tru64) || defined(__TRU64__)
# define PLATFORM_ID "Tru64"

#elif defined(__riscos) || defined(__riscos__)
# define PLATFORM_ID "RISCos"

#elif defined(__sinix) || defined(__sinix__) || defined(__SINIX__)
# define PLATFORM_ID "SINIX"

#elif defined(__UNIX_SV__)
# define PLATFORM_ID "UNIX_SV"

#elif defined(__bsdos__)
# define PLATFORM_ID "BSDOS"

#elif defined(_MPRAS) || defined(MPRAS)
# define PLATFORM_ID "MP-RAS"

#elif defined(__osf) || defined(__osf__)
# define PLATFORM_ID "OSF1"

#elif defined(_SCO_SV) || defined(SCO_SV) || defined(sco_sv)
# define PLATFORM_ID "SCO_SV"

#elif defined(__ultrix) || defined(__ultrix__) || defined(_ULTRIX)
# define PLATFORM_ID "ULTRIX"

#elif defined(__XENIX__) || defined(_XENIX) || defined(XENIX)
# define PLATFORM_ID "Xenix"

#elif defined(__WATCOMC__)
# if defined(__LINUX__)
#  define PLATFORM_ID "Linux"

# elif defined(__DOS__)
#  define PLATFORM_ID "DOS"

# elif defined(__OS2__)
#  define PLATFORM_ID "OS2"

# elif defined(__WINDOWS__)
#  define PLATFORM_ID "Windows3x"

# elif defined(__VXWORKS__)
#  define PLATFORM_ID "VxWorks"

# else /* unknown platform */
#  define PLATFORM_ID
# endif

#elif defined(__INTEGRITY)
# if defined(INT_178B)
#  define PLATFORM_ID "Integrity178"

# else /* regular Integrity */
#  define PLATFORM_ID "Integrity"
# endif

# elif defined(_ADI_COMPILER)
#  define PLATFORM_ID "ADSP"

#else /* unknown platform */
# define PLATFORM_ID

#endif

/* For windows compilers MSVC and Intel we can determine
   the architecture of the compiler being used.  This is because
   the compilers do not have flags that can change the architecture,
   but rather depend on which compiler is being used
*/
#if defined(_WIN32) && defined(_MSC_VER)
# if defined(_M_IA64)
#  define ARCHITECTURE_ID "IA64"

# elif defined(_M_ARM64EC)
#  define ARCHITECTURE_ID "ARM64EC"

# elif defined(_M_X64) || defined(_M_AMD64)
#  define ARCHITECTURE_ID "x64"

# elif defined(_M_IX86)
#  define ARCHITECTURE_ID "X86"

# elif defined(_M_ARM64)
#  define ARCHITECTURE_ID "ARM64"

# elif defined(_M_ARM)
#  if _M_ARM == 4
#   define ARCHITECTURE_ID "ARMV4I"
#  elif _M_ARM == 5
#   define ARCHITECTURE_ID "ARMV5I"
#  else
#   define ARCHITECTURE_ID "ARMV" STRINGIFY(_M_ARM)
#  endif

# elif defined(_M_MIPS)
#  define ARCHITECTURE_ID "MIPS"

# elif defined(_M_SH)
#  define ARCHITECTURE_ID "SHx"

# else /* unknown architecture */
#  define ARCHITECTURE_ID ""
# endif

#elif defined(__WATCOMC__)
# if defined(_M_I86)
#  define ARCHITECTURE_ID "I86"

# elif defined(_M_IX86)
#  define ARCHITECTURE_ID "X86"

# else /* unknown architecture */
#  define ARCHITECTURE_ID ""
# endif

#elif defined(__IAR_SYSTEMS_ICC__) || defined(__IAR_SYSTEMS_ICC)
# if defined(__ICCARM__)
#  define ARCHITECTURE_ID "ARM"

# elif defined(__ICCRX__)
#  define ARCHITECTURE_ID "RX"

# elif defined(__ICCRH850__)
#  define ARCHITECTURE_ID "RH850"

# elif defined(__ICCRL78__)
#  define ARCHITECTURE_ID "RL78"

# elif defined(__ICCRISCV__)
#  define ARCHITECTURE_ID "RISCV"

# elif defined(__ICCAVR__)
#  define ARCHITECTURE_ID "AVR"

# elif defined(__ICC430__)
#  define ARCHITECTURE_ID "MSP430"

# elif defined(__ICCV850__)
#  define ARCHITECTURE_ID "V850"

# elif defined(__ICC8051__)
#  define ARCHITECTURE_ID "8051"

# elif defined(__ICCSTM8__)
#  define ARCHITECTURE_ID "STM8"

# else /* unknown architecture */
#  define ARCHITECTURE_ID ""
# endif

#elif defined(__ghs__)
# if defined(__PPC64__)
#  define ARCHITECTURE_ID "PPC64"

# elif defined(__ppc__)
#  define ARCHITECTURE_ID "PPC"

# elif defined(__ARM__)
#  define ARCHITECTURE_ID "ARM"

# elif defined(__x86_64__)
#  define ARCHITECTURE_ID "x64"

# elif defined(__i386__)
#  define ARCHITECTURE_ID "X86"

# else /* unknown architecture */
#  define ARCHITECTURE_ID ""
# endif

#elif defined(__clang__) && defined(__ti__)
# if defined(__ARM_ARCH)
#  define ARCHITECTURE_ID "ARM"

# else /* unknown architecture */
#  define ARCHITECTURE_ID ""
# endif

#elif defined(__TI_COMPILER_VERSION__)
# if defined(__TI_ARM__)
#  define ARCHITECTURE_ID "ARM"

# elif defined(__MSP430__)
#  define ARCHITECTURE_ID "MSP430"

# elif defined(__TMS320C28XX__)
#  define ARCHITECTURE_ID "TMS320C28x"

# elif defined(__TMS320C6X__) || defined(_TMS320C6X)
#  define ARCHITECTURE_ID "TMS320C6x"

# else /* unknown architecture */
#  define ARCHITECTURE_ID ""
# endif

# elif defined(__ADSPSHARC__)
#  define ARCHITECTURE_ID "SHARC"

# elif defined(__ADSPBLACKFIN__)
#  define ARCHITECTURE_ID "Blackfin"

#elif defined(__TASKING__)

# if defined(__CTC__) || defined(__CPTC__)
#  define ARCHITECTURE_ID "TriCore"

# elif defined(__CMCS__)
#  define ARCHITECTURE_ID "MCS"

# elif defined(__CARM__) || defined(__CPARM__)
#  define ARCHITECTURE_ID "ARM"

# elif defined(__CARC__)
#  define ARCHITECTURE_ID "ARC"

# elif defined(__C51__)
#  define ARCHITECTURE_ID "8051"

# elif defined(__CPCP__)
#  define ARCHITECTURE_ID "PCP"

# else
#  define ARCHITECTURE_ID ""
# endif

#elif defined(__RENESAS__)
# if defined(__CCRX__)
#  define ARCHITECTURE_ID "RX"

# elif defined(__CCRL__)
#  define ARCHITECTURE_ID "RL78"

# elif defined(__CCRH__)
#  define ARCHITECTURE_ID "RH850"

# else
#  define ARCHITECTURE_ID ""
# endif

#else
#  define ARCHITECTURE_ID
#endif

/* Convert integer to decimal digit literals.  */
#define DEC(n)                   \
  ('0' + (((n) / 10000000)%10)), \
  ('0' + (((n) / 1000000)%10)),  \
  ('0' + (((n) / 100000)%10)),   \
  ('0' + (((n) / 10000)%10)),    \
  ('0' + (((n) / 1000)%10)),     \
  ('0' + (((n) / 100)%10)),      \
  ('0' + (((n) / 10)%10)),       \
  ('0' +  ((n) % 10))

/* Convert integer to hex digit literals.  */
#define HEX(n)             \
  ('0' + ((n)>>28 & 0xF)), \
  ('0' + ((n)>>24 & 0xF)), \
  ('0' + ((n)>>20 & 0xF)), \
  ('0' + ((n)>>16 & 0xF)), \
  ('0' + ((n)>>12 & 0xF)), \
  ('0' + ((n)>>8  & 0xF)), \
  ('0' + ((n)>>4  & 0xF)), \
  ('0' + ((n)     & 0xF))

/* Construct a string literal encoding the version number. */
#ifdef COMPILER_VERSION
char const* info_version = "INFO" ":" "compiler_version[" COMPILER_VERSION "]";

/* Construct a string literal encoding the version number components. */
#elif defined(COMPILER_VERSION_MAJOR)
char const info_version[] = {
  'I', 'N', 'F', 'O', ':',
  'c','o','m','p','i','l','e','r','_','v','e','r','s','i','o','n','[',
  COMPILER_VERSION_MAJOR,
# ifdef COMPILER_VERSION_MINOR
  '.', COMPILER_VERSION_MINOR,
#  ifdef COMPILER_VERSION_PATCH
   '.', COMPILER_VERSION_PATCH,
#   ifdef COMPILER_VERSION_TWEAK
    '.', COMPILER_VERSION_TWEAK,
#   endif
#  endif
# endif
  ']','\0'};
#endif

/* Construct a string literal encoding the internal version number. */
#ifdef COMPILER_VERSION_INTERNAL
char const info_version_internal[] = {
  'I', 'N', 'F', 'O', ':',
  'c','o','m','p','i','l','e','r','_','v','e','r','s','i','o','n','_',
  'i','n','t','e','r','n','a','l','[',
  COMPILER_VERSION_INTERNAL,']','\0'};
#elif defined(COMPILER_VERSION_INTERNAL_STR)
char const* info_version_internal = "INFO" ":" "compiler_version_internal[" COMPILER_VERSION_INTERNAL_STR "]";
#endif

/* Construct a string literal encoding the version number components. */
#ifdef SIMULATE_VERSION_MAJOR
char const info_simulate_version[] = {
  'I', 'N', 'F', 'O', ':',
  's','i','m','u','l','a','t','e','_','v','e','r','s','i','o','n','[',
  SIMULATE_VERSION_MAJOR,
# ifdef SIMULATE_VERSION_MINOR
  '.', SIMULATE_VERSION_MINOR,
#  ifdef SIMULATE_VERSION_PATCH
   '.', SIMULATE_VERSION_PATCH,
#   ifdef SIMULATE_VERSION_TWEAK
    '.', SIMULATE_VERSION_TWEAK,
#   endif
#  endif
# endif
  ']','\0'};
#endif

/* Construct the string literal in pieces to prevent the source from
   getting matched.  Store it in a pointer rather than an array
   because some compilers will just produce instructions to fill the
   array rather than assigning a pointer to a static array.  */
char const* info_platform = "INFO" ":" "platform[" PLATFORM_ID "]";
char const* info_arch = "INFO" ":" "arch[" ARCHITECTURE_ID "]";



#define CXX_STD_98 199711L
#define CXX_STD_11 201103L
#define CXX_STD_14 201402L
#define CXX_STD_17 201703L
#define CXX_STD_20 202002L
#define CXX_STD_23 202302L

#if defined(__INTEL_COMPILER) && defined(_MSVC_LANG)
#  if _MSVC_LANG > CXX_STD_17
#    define CXX_STD _MSVC_LANG
#  elif _MSVC_LANG == CXX_STD_17 && defined(__cpp_aggregate_paren_init)
#    define CXX_STD CXX_STD_20
#  elif _MSVC_LANG > CXX_STD_14 && __cplusplus > CXX_STD_17
#    define CXX_STD CXX_STD_20
#  elif _MSVC_LANG > CXX_STD_14
#    define CXX_STD CXX_STD_17
#  elif defined(__INTEL_CXX11_MODE__) && defined(__cpp_aggregate_nsdmi)
#    define CXX_STD CXX_STD_14
#  elif defined(__INTEL_CXX11_MODE__)
#    define CXX_STD CXX_STD_11
#  else
#    define CXX_STD CXX_STD_98
#  endif
#elif defined(_MSC_VER) && defined(_MSVC_LANG)
#  if _MSVC_LANG > __cplusplus
#    define CXX_STD _MSVC_LANG
#  else
#    define CXX_STD __cplusplus
#  endif
#elif defined(__NVCOMPILER)
#  if __cplusplus == CXX_STD_17 && defined(__cpp_aggregate_paren_init)
#    define CXX_STD CXX_STD_20
#  else
#    define CXX_STD __cplusplus
#  endif
#elif defined(__INTEL_COMPILER) || defined(__PGI)
#  if __cplusplus == CXX_STD_11 && defined(__cpp_namespace_attributes)
#    define CXX_STD CXX_STD_17
#  elif __cplusplus == CXX_STD_11 && defined(__cpp_aggregate_nsdmi)
#    define CXX_STD CXX_STD_14
#  else
#    define CXX_STD __cplusplus
#  endif
#elif (defined(__IBMCPP__) || defined(__ibmxl__)) && defined(__linux__)
#  if __cplusplus == CXX_STD_11 && defined(__cpp_aggregate_nsdmi)
#    define CXX_STD CXX_STD_14
#  else
#    define CXX_STD __cplusplus
#  endif
#elif __cplusplus == 1 && defined(__GXX_EXPERIMENTAL_CXX0X__)
#  define CXX_STD CXX_STD_11
#else
#  define CXX_STD __cplusplus
#endif

const char* info_language_standard_default = "INFO" ":" "standard_default["
#if CXX_STD > CXX_STD_23
  "26"
#elif CXX_STD > CXX_STD_20
  "23"
#elif CXX_STD > CXX_STD_17
  "20"
#elif CXX_STD > CXX_STD_14
  "17"
#elif CXX_STD > CXX_STD_11
  "14"
#elif CXX_STD >= CXX_STD_11
  "11"
#else
  "98"
#endif
"]";

const char* info_language_extensions_default = "INFO" ":" "extensions_default["
#if (defined(__clang__) || defined(__GNUC__) || defined(__xlC__) ||           \
     defined(__TI_COMPILER_VERSION__) || defined(__RENESAS__)) &&             \
  !defined(__STRICT_ANSI__)
  "ON"
#else
  "OFF"
#endif
"]";

/*--------------------------------------------------------------------------*/

int main(int argc, char* argv[])
{
  int require = 0;
  require += info_compiler[argc];
  require += info_platform[argc];
  require += info_arch[argc];
#ifdef COMPILER_VERSION_MAJOR
  require += info_version[argc];
#endif
#if defined(COMPILER_VERSION_INTERNAL) || defined(COMPILER_VERSION_INTERNAL_STR)
  require += info_version_internal[argc];
#endif
#ifdef SIMULATE_ID
  require += info_simulate[argc];
#endif
#ifdef SIMULATE_VERSION_MAJOR
  require += info_simulate_version[argc];
#endif
#if defined(__CRAYXT_COMPUTE_LINUX_TARGET)
  require += info_cray[argc];
#endif
  require += info_language_standard_default[argc];
  require += info_language_extensions_default[argc];
  (void)argv;
  return require;
}
<ProjectMap>
  <File path="CMakeLists.txt">
    <Description>Main CMake build configuration file for the C++ project, setting up compilation and linking with SDL2, OpenGL, pugixml, and Windows-specific libraries for the flight simulation with asset management system.</Description>
    <Constructors />
    <Methods />
  </File>
  <File path="README.md">
    <Description>Project README file containing build instructions, toolchain setup, and project overview.</Description>
    <Constructors />
    <Methods />
  </File>
  <File path="toolchain-arm64.cmake">
    <Description>CMake toolchain file for cross-compilation to ARM64 Linux platform.</Description>
    <Constructors />
    <Methods />
  </File>
  <File path=".gitignore">
    <Description>Git ignore file for excluding build artifacts, temporary files, and IDE-specific files from version control.</Description>
    <Constructors />
    <Methods />
  </File>
  <File path="build.ps1">
    <Description>PowerShell script to build the project in debug or release mode based on -r flag.</Description>
    <Constructors />
    <Methods />
  </File>
  <File path="build.sh">
    <Description>Bash script to build the project in debug or release mode based on -r flag.</Description>
    <Constructors />
    <Methods />
  </File>
  <File path="run.ps1">
    <Description>PowerShell script to run the built executable in debug or release mode based on -r flag.</Description>
    <Constructors />
    <Methods />
  </File>
  <File path="run.sh">
    <Description>Bash script to run the built executable in debug or release mode based on -r flag.</Description>
    <Constructors />
    <Methods />
  </File>
  <Folder name="docs">
    <File path="docs/1.0-structure.md">
      <Description>Documentation outlining the proposed C++ project structure for vehicle simulation.</Description>
      <Constructors />
      <Methods />
    </File>
    <File path="docs/1.1-toolchain.md">
      <Description>Documentation on the minimal toolchain for C++ development and cross-compilation.</Description>
      <Constructors />
      <Methods />
    </File>
    <File path="docs/1.2-IoC.md">
      <Description>Documentation on Inversion of Control implementation in the project.</Description>
      <Constructors />
      <Methods />
    </File>
    <File path="docs/2.0-assets-and-packages.md">
      <Description>Documentation on assets, packages, and configuration for the C++ vehicle simulation.</Description>
      <Constructors />
      <Methods />
    </File>
    <File path="docs/2.1-assets-logic.md">
      <Description>Documentation on asset and package logic, including principles, structure, and integration.</Description>
      <Constructors />
      <Methods />
    </File>
    <File path="docs/prompt.md">
      <Description>Prompt file for generating the project code map.</Description>
      <Constructors />
      <Methods />
    </File>
  </Folder>
  <Folder name="src">
    <File path="src/main.cpp">
      <Description>Main application entry point. Initializes World, SimClock, EventBus, asset systems (AssetRegistry, AssetPackLoader), and registers all Systems including BootstrapSystem, WorldGenSystem, ConsoleSystem, VisualizationSystem, and AssetHotReloadSystem. Creates proper Windows window for visualization. Contains the main simulation loop with fixed timestep coordination and Windows message handling.</Description>
      <Constructors />
      <Methods>
        <Method name="main" returnType="int" params="" />
        <Method name="CreateSimulationWindow" returnType="HWND" params="" />
        <Method name="WindowProc" returnType="LRESULT" params="HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam" />
      </Methods>
    </File>
    <Folder name="core">
      <File path="src/core/IEvent.h">
        <Description>Base interface for all system events (e.g., BatteryLowEvent, CollisionEvent).</Description>
        <Constructors />
        <Methods>
          <Method name="getType" returnType="EventType" params="" />
        </Methods>
      </File>
      <File path="src/core/EventBus.h">
        <Description>Event-based communication (Observer pattern).</Description>
        <Constructors>
          <Constructor name="EventBus" params="" />
        </Constructors>
        <Methods>
          <Method name="subscribe" returnType="void" params="EventType type, std::function&lt;void(const IEvent&amp;)&gt; handler" />
          <Method name="publish" returnType="void" params="const IEvent&amp; event" />
        </Methods>
      </File>
      <File path="src/core/EventBus.cpp">
        <Description>Implementation of EventBus class.</Description>
        <Constructors />
        <Methods />
      </File>
      <File path="src/core/IComponent.h">
        <Description>Base interface for ECS components. Pure data structures.</Description>
        <Constructors />
        <Methods />
      </File>
      <File path="src/core/Entity.h">
        <Description>Represents a simulation object (drone, building, etc.).</Description>
        <Constructors>
          <Constructor name="Entity" params="unsigned int id" />
        </Constructors>
        <Methods>
          <Method name="addComponent" returnType="" params="" />
          <Method name="getComponent" returnType="" params="" />
        </Methods>
      </File>
      <File path="src/core/Entity.cpp">
        <Description>Implementation of Entity class.</Description>
        <Constructors />
        <Methods />
      </File>
      <File path="src/core/ISystem.h">
        <Description>Base interface for ECS systems.</Description>
        <Constructors />
        <Methods>
          <Method name="update" returnType="void" params="World&amp; world, float dt" />
        </Methods>
      </File>
      <File path="src/core/World.h">
        <Description>Manages all entities and systems. Orchestrates simulation loop.</Description>
        <Constructors>
          <Constructor name="World" params="EventBus&amp; eventBus" />
        </Constructors>
        <Methods>
          <Method name="addEntity" returnType="void" params="std::unique_ptr&lt;Entity&gt; entity" />
          <Method name="addSystem" returnType="void" params="std::unique_ptr&lt;ISystem&gt; system" />
          <Method name="update" returnType="void" params="float dt" />
        </Methods>
      </File>
      <File path="src/core/World.cpp">
        <Description>Implementation of World class.</Description>
        <Constructors />
        <Methods />
      </File>
      <File path="src/core/SimClock.h">
        <Description>Handles simulation time and fixed timestep logic.</Description>
        <Constructors>
          <Constructor name="SimClock" params="float fixedTimestep" />
        </Constructors>
        <Methods>
          <Method name="tick" returnType="void" params="float deltaTime" />
          <Method name="shouldStepPhysics" returnType="bool" params="" />
          <Method name="getFixedTimestep" returnType="float" params="" />
        </Methods>
      </File>
      <File path="src/core/SimClock.cpp">
        <Description>Implementation of SimClock class.</Description>
        <Constructors />
        <Methods />
      </File>
      <File path="src/core/AssetRegistry.h">
        <Description>Central registry for managing all asset types (fonts, textures, materials, mesh recipes) and scene configurations. Provides asset storage, retrieval, package management, and default scene configuration support.</Description>
        <Constructors>
          <Constructor name="AssetRegistry" params="" />
        </Constructors>
        <Methods>
          <Method name="registerFont" returnType="void" params="AssetId id, std::unique_ptr&lt;FontAsset&gt; asset" />
          <Method name="registerTexture" returnType="void" params="AssetId id, std::unique_ptr&lt;TextureAsset&gt; asset" />
          <Method name="registerMaterial" returnType="void" params="AssetId id, std::unique_ptr&lt;MaterialAsset&gt; asset" />
          <Method name="registerMeshRecipe" returnType="void" params="AssetId id, std::unique_ptr&lt;MeshRecipeAsset&gt; asset" />
          <Method name="registerSceneConfig" returnType="void" params="AssetId id, const std::string&amp; sceneXml" />
          <Method name="getFont" returnType="const FontAsset*" params="AssetId id" />
          <Method name="getTexture" returnType="const TextureAsset*" params="AssetId id" />
          <Method name="getMaterial" returnType="const MaterialAsset*" params="AssetId id" />
          <Method name="getMeshRecipe" returnType="const MeshRecipeAsset*" params="AssetId id" />
          <Method name="getSceneConfig" returnType="const std::string*" params="AssetId id" />
          <Method name="setDefaultScene" returnType="void" params="AssetId id" />
          <Method name="getDefaultScene" returnType="const std::string*" params="" />
          <Method name="getDefaultSceneId" returnType="AssetId" params="" />
          <Method name="markPackageLoaded" returnType="void" params="const std::string&amp; packageName" />
          <Method name="getLoadedPackages" returnType="const std::vector&lt;std::string&gt;&amp;" params="" />
          <Method name="clear" returnType="void" params="" />
        </Methods>
      </File>
      <File path="src/core/AssetRegistry.cpp">
        <Description>Implementation of AssetRegistry class with support for asset storage, scene configuration management, and package tracking.</Description>
        <Constructors />
        <Methods />
      </File>
      <File path="src/core/AssetPackLoader.h">
        <Description>Loads and parses XML package files, extracting assets and configurations into the AssetRegistry. Supports parsing of assets, scene configurations, input configs, and overlay configs.</Description>
        <Constructors>
          <Constructor name="AssetPackLoader" params="AssetRegistry&amp; registry" />
        </Constructors>
        <Methods>
          <Method name="loadPackage" returnType="bool" params="const std::string&amp; packagePath" />
          <Method name="loadDeveloperPackage" returnType="bool" params="" />
          <Method name="parseAssets" returnType="bool" params="const std::string&amp; xmlContent, const std::string&amp; packageName" />
          <Method name="parseConfigurations" returnType="bool" params="const std::string&amp; xmlContent, const std::string&amp; packageName" />
          <Method name="parseFontAsset" returnType="std::unique_ptr&lt;FontAsset&gt;" params="const std::string&amp; xmlNode" />
        </Methods>
      </File>
      <File path="src/core/AssetPackLoader.cpp">
        <Description>Implementation of AssetPackLoader class with XML parsing for DeveloperPackage and scene configuration extraction.</Description>
        <Constructors />
        <Methods />
      </File>
    </Folder>
    <Folder name="components">
    </Folder>
    <Folder name="events">
      <File path="src/events/WorldGenEvents.h">
        <Description>Event definitions for world generation workflow including NoPackagesFoundEvent and DefaultWorldGeneratedEvent.</Description>
        <Constructors />
        <Methods />
      </File>
      <File path="src/events/InputEvents.h">
        <Description>Event definitions for input system including ConsoleToggleEvent and ConsoleVisibilityChangedEvent.</Description>
        <Constructors />
        <Methods />
      </File>
    </Folder>
    <Folder name="systems">
      <File path="src/systems/PhysicsSystem.h">
        <Description>ECS system responsible for physics simulation updates.</Description>
        <Constructors>
          <Constructor name="PhysicsSystem" params="EventBus&amp; eventBus, IAirDensityModel&amp; airDensityModel, IWindModel&amp; windModel, ICollisionResolver&amp; collisionResolver" />
        </Constructors>
        <Methods />
      </File>
      <File path="src/systems/PhysicsSystem.cpp">
        <Description>Implementation of PhysicsSystem class.</Description>
        <Constructors />
        <Methods />
      </File>
      <File path="src/systems/InputSystem.h">
        <Description>ECS system handling user input and translating to simulation events.</Description>
        <Constructors>
          <Constructor name="InputSystem" params="EventBus&amp; eventBus, IInputDevice&amp; inputDevice" />
        </Constructors>
        <Methods />
      </File>
      <File path="src/systems/InputSystem.cpp">
        <Description>Implementation of InputSystem class.</Description>
        <Constructors />
        <Methods />
      </File>
      <File path="src/systems/VehicleControlSystem.h">
        <Description>ECS system managing vehicle control logic and responses.</Description>
        <Constructors>
          <Constructor name="VehicleControlSystem" params="EventBus&amp; eventBus" />
        </Constructors>
        <Methods />
      </File>
      <File path="src/systems/VehicleControlSystem.cpp">
        <Description>Implementation of VehicleControlSystem class.</Description>
        <Constructors />
        <Methods />
      </File>
      <File path="src/systems/BootstrapSystem.h">
        <Description>One-shot system responsible for initial world construction and asset loading. Checks for available packages, loads them via AssetPackLoader, and triggers appropriate world generation events.</Description>
        <Constructors>
          <Constructor name="BootstrapSystem" params="EventBus&amp; eventBus, World&amp; world, AssetRegistry&amp; assetRegistry, AssetPackLoader&amp; assetLoader" />
        </Constructors>
        <Methods>
          <Method name="Init" returnType="void" params="" />
          <Method name="CheckForAssetPackages" returnType="bool" params="" />
          <Method name="LoadAvailablePackages" returnType="bool" params="" />
          <Method name="PostFrameUpdate" returnType="void" params="" />
        </Methods>
      </File>
      <File path="src/systems/BootstrapSystem.cpp">
        <Description>Implementation of BootstrapSystem class with package discovery, XML loading, and default scene fallback logic.</Description>
        <Constructors />
        <Methods />
      </File>
      <File path="src/systems/WorldGenSystem.h">
        <Description>ECS system for creating procedural worlds and default scenes. Supports both XML-driven world generation from scene configurations and fallback default world generation.</Description>
        <Constructors>
          <Constructor name="WorldGenSystem" params="EventBus&amp; eventBus, World&amp; world, AssetRegistry&amp; assetRegistry" />
        </Constructors>
        <Methods>
          <Method name="GenerateDefaultSphereWorld" returnType="void" params="" />
          <Method name="GenerateWorldFromXMLScene" returnType="void" params="const std::string&amp; sceneXml" />
          <Method name="OnNoPackagesFound" returnType="void" params="const NoPackagesFoundEvent&amp; event" />
          <Method name="OnDefaultWorldRequested" returnType="void" params="const DefaultWorldGeneratedEvent&amp; event" />
          <Method name="GenerateProceduralSphereMesh" returnType="AssetId" params="float radius, int segments" />
          <Method name="GetEarthMaterialId" returnType="AssetId" params="" />
          <Method name="GetAtmosphereMaterialId" returnType="AssetId" params="int layer" />
          <Method name="GetCloudMaterialId" returnType="AssetId" params="" />
        </Methods>
      </File>
      <File path="src/systems/WorldGenSystem.cpp">
        <Description>Implementation of WorldGenSystem class with XML scene parsing and Earth-like sphere world generation including atmosphere layers and clouds.</Description>
        <Constructors />
        <Methods />
      </File>
      <File path="src/systems/ConsoleSystem.h">
        <Description>ECS system managing developer console state, command processing, and visibility toggle via tilde key.</Description>
        <Constructors>
          <Constructor name="ConsoleSystem" params="EventBus&amp; eventBus" />
        </Constructors>
        <Methods>
          <Method name="IsVisible" returnType="bool" params="" />
          <Method name="OnConsoleToggle" returnType="void" params="const ConsoleToggleEvent&amp; event" />
          <Method name="ProcessCommand" returnType="void" params="const std::string&amp; command" />
        </Methods>
      </File>
      <File path="src/systems/ConsoleSystem.cpp">
        <Description>Implementation of ConsoleSystem class with console visibility management and event handling.</Description>
        <Constructors />
        <Methods />
      </File>
      <File path="src/systems/VisualizationSystem.h">
        <Description>ECS system responsible for rendering the 3D scene, HUD, debug overlays, and developer console UI. Supports Windows GDI rendering and entity visualization.</Description>
        <Constructors>
          <Constructor name="VisualizationSystem" params="EventBus&amp; eventBus, World&amp; world, HWND windowHandle" />
        </Constructors>
        <Methods>
          <Method name="RenderEntities" returnType="void" params="" />
          <Method name="RenderConsole" returnType="void" params="" />
          <Method name="RenderNoPackagesMessage" returnType="void" params="" />
          <Method name="DrawSphere" returnType="void" params="float x, float y, float radius, COLORREF color" />
          <Method name="DrawText" returnType="void" params="float x, float y, const std::string&amp; text, COLORREF color" />
          <Method name="OnNoPackagesFound" returnType="void" params="const NoPackagesFoundEvent&amp; event" />
          <Method name="OnConsoleVisibilityChanged" returnType="void" params="const ConsoleVisibilityChangedEvent&amp; event" />
        </Methods>
      </File>
      <File path="src/systems/VisualizationSystem.cpp">
        <Description>Implementation of VisualizationSystem class with Windows GDI rendering, entity visualization, and console UI rendering.</Description>
        <Constructors />
        <Methods />
      </File>
      <File path="src/systems/AssetHotReloadSystem.h">
        <Description>ECS system for development-time hot-reloading of asset packages. Watches XML files for changes and triggers reloading.</Description>
        <Constructors>
          <Constructor name="AssetHotReloadSystem" params="AssetRegistry&amp; assetRegistry, AssetPackLoader&amp; assetLoader" />
        </Constructors>
        <Methods>
          <Method name="watchPackage" returnType="void" params="const std::string&amp; packagePath" />
          <Method name="checkForChanges" returnType="void" params="" />
        </Methods>
      </File>
      <File path="src/systems/AssetHotReloadSystem.cpp">
        <Description>Implementation of AssetHotReloadSystem class with file watching and hot-reload capabilities.</Description>
        <Constructors />
        <Methods />
      </File>
    </Folder>
    <Folder name="physics">
      <File path="src/physics/IAirDensityModel.h">
        <Description>Interface for air density models used in physics calculations.</Description>
        <Constructors />
        <Methods>
          <Method name="getDensity" returnType="float" params="float altitude" />
        </Methods>
      </File>
      <File path="src/physics/ExponentialAirDensityModel.h">
        <Description>Concrete implementation of IAirDensityModel using exponential decay formula.</Description>
        <Constructors>
          <Constructor name="ExponentialAirDensityModel" params="float seaLevelDensity, float scaleHeight" />
        </Constructors>
        <Methods />
      </File>
      <File path="src/physics/ExponentialAirDensityModel.cpp">
        <Description>Implementation of ExponentialAirDensityModel class.</Description>
        <Constructors />
        <Methods />
      </File>
      <File path="src/physics/IWindModel.h">
        <Description>Interface for wind models used in physics simulations.</Description>
        <Constructors />
        <Methods>
          <Method name="getWindVector" returnType="Vector3" params="const Vector3&amp; position" />
        </Methods>
      </File>
      <File path="src/physics/PerlinWindModel.h">
        <Description>Concrete implementation of IWindModel using Perlin noise for wind simulation.</Description>
        <Constructors>
          <Constructor name="PerlinWindModel" params="float baseSpeed, float turbulenceScale, float heightScale, int seed" />
        </Constructors>
        <Methods />
      </File>
      <File path="src/physics/PerlinWindModel.cpp">
        <Description>Implementation of PerlinWindModel class.</Description>
        <Constructors />
        <Methods />
      </File>
      <File path="src/physics/ICollisionResolver.h">
        <Description>Interface for collision resolution strategies in physics.</Description>
        <Constructors />
        <Methods>
          <Method name="resolveCollision" returnType="void" params="Entity&amp; entityA, Entity&amp; entityB, const CollisionEvent&amp; event" />
        </Methods>
      </File>
      <File path="src/physics/ImpulseCollisionResolver.h">
        <Description>Concrete implementation of ICollisionResolver using impulse-based collision response.</Description>
        <Constructors>
          <Constructor name="ImpulseCollisionResolver" params="float restitution, float friction" />
        </Constructors>
        <Methods />
      </File>
      <File path="src/physics/ImpulseCollisionResolver.cpp">
        <Description>Implementation of ImpulseCollisionResolver class.</Description>
        <Constructors />
        <Methods />
      </File>
    </Folder>
    <Folder name="vehicles">
      <File path="src/vehicles/IVehicleBuilder.h">
        <Description>Interface for vehicle builders that construct entities from configuration files.</Description>
        <Constructors />
        <Methods>
          <Method name="build" returnType="std::unique_ptr&lt;Entity&gt;" params="const std::string&amp; configPath, EventBus&amp; eventBus" />
        </Methods>
      </File>
      <File path="src/vehicles/DroneBuilder.h">
        <Description>Concrete implementation of IVehicleBuilder for creating drone entities.</Description>
        <Constructors>
          <Constructor name="DroneBuilder" params="IXmlParser&amp; xmlParser" />
        </Constructors>
        <Methods />
      </File>
      <File path="src/vehicles/DroneBuilder.cpp">
        <Description>Implementation of DroneBuilder class.</Description>
        <Constructors />
        <Methods />
      </File>
    </Folder>
    <Folder name="utils">
      <File path="src/utils/IXmlParser.h">
        <Description>Interface for XML parsing utilities.</Description>
        <Constructors />
        <Methods>
          <Method name="parse" returnType="std::unique_ptr&lt;pugi::xml_document&gt;" params="const std::string&amp; filePath" />
        </Methods>
      </File>
      <File path="src/utils/PugiXmlParser.h">
        <Description>Concrete implementation of IXmlParser using pugixml library.</Description>
        <Constructors>
          <Constructor name="PugiXmlParser" params="" />
        </Constructors>
        <Methods />
      </File>
      <File path="src/utils/PugiXmlParser.cpp">
        <Description>Implementation of PugiXmlParser class.</Description>
        <Constructors />
        <Methods />
      </File>
    </Folder>
    <Folder name="platform">
      <File path="src/platform/IInputDevice.h">
        <Description>Interface for platform-specific input devices.</Description>
        <Constructors />
        <Methods>
          <Method name="isKeyPressed" returnType="bool" params="int keyCode" />
          <Method name="getMousePosition" returnType="std::pair&lt;int, int&gt;" params="" />
        </Methods>
      </File>
      <File path="src/platform/WinInputDevice.h">
        <Description>Concrete implementation of IInputDevice for Windows platform.</Description>
        <Constructors>
          <Constructor name="WinInputDevice" params="" />
        </Constructors>
        <Methods />
      </File>
      <File path="src/platform/WinInputDevice.cpp">
        <Description>Implementation of WinInputDevice class.</Description>
        <Constructors />
        <Methods />
      </File>
    </Folder>
  </Folder>
  <Folder name="assets">
    <Folder name="packages">
      <Folder name="city_01">
        <File path="assets/packages/city_01/package.xml">
          <Description>XML file declaring assets and dependencies for the city_01 package.</Description>
          <Constructors />
          <Methods />
        </File>
        <Folder name="meshes">
        </Folder>
        <Folder name="textures">
        </Folder>
        <Folder name="params">
          <File path="assets/packages/city_01/params/building_city_block.xml">
            <Description>XML file defining parametric parameters for a city building block.</Description>
            <Constructors />
            <Methods />
          </File>
        </Folder>
        <Folder name="code">
        </Folder>
      </Folder>
      <Folder name="DeveloperPackage">
        <File path="assets/packages/DeveloperPackage/package.xml">
          <Description>Core developer debug assets and default scene XML configuration. Defines console UI assets, Earth-like sphere world materials, procedural mesh recipes, scene configuration, input bindings, and overlay UI for the default development environment.</Description>
          <Constructors />
          <Methods />
        </File>
        <Folder name="console">
        </Folder>
        <Folder name="textures">
        </Folder>
      </Folder>
    </Folder>
    <Folder name="build_tools">
      <Folder name="asset_compiler">
        <File path="assets/build_tools/asset_compiler/CMakeLists.txt">
          <Description>CMake build configuration for the asset compiler CLI tool.</Description>
          <Constructors />
          <Methods />
        </File>
        <File path="assets/build_tools/asset_compiler/main.cpp">
          <Description>Main entry point for the asset compiler tool that processes XML to binary packs.</Description>
          <Constructors />
          <Methods>
            <Method name="main" returnType="int" params="int argc, char* argv[]" />
          </Methods>
        </File>
      </Folder>
      <Folder name="codegen">
        <File path="assets/build_tools/codegen/CMakeLists.txt">
          <Description>CMake build configuration for the codegen tool.</Description>
          <Constructors />
          <Methods />
        </File>
        <File path="assets/build_tools/codegen/main.cpp">
          <Description>Main entry point for the codegen tool that generates asset ID headers.</Description>
          <Constructors />
          <Methods>
            <Method name="main" returnType="int" params="int argc, char* argv[]" />
          </Methods>
        </File>
      </Folder>
    </Folder>
    <Folder name="runtime">
      <Folder name="data">
        <Folder name="packs">
        </Folder>
        <Folder name="plugins">
        </Folder>
        <Folder name="cache">
          <Folder name="shader_cache">
          </Folder>
          <Folder name="geom_cache">
          </Folder>
          <Folder name="thumb_index">
          </Folder>
        </Folder>
      </Folder>
    </Folder>
  </Folder>
  <Folder name="packages">
    <Folder name="core">
      <File path="packages/core/CMakeLists.txt">
        <Description>CMake build configuration for the core package.</Description>
        <Constructors />
        <Methods />
      </File>
      <Folder name="src">
      </Folder>
      <Folder name="include">
      </Folder>
    </Folder>
    <Folder name="physics">
      <File path="packages/physics/CMakeLists.txt">
        <Description>CMake build configuration for the physics package.</Description>
        <Constructors />
        <Methods />
      </File>
      <Folder name="src">
      </Folder>
      <Folder name="include">
      </Folder>
    </Folder>
    <Folder name="vehicles">
      <Folder name="drone-x1">
        <File path="packages/vehicles/drone-x1/CMakeLists.txt">
          <Description>CMake build configuration for the drone-x1 vehicle package.</Description>
          <Constructors />
          <Methods />
        </File>
        <Folder name="assets">
          <Folder name="models">
          </Folder>
          <Folder name="textures">
          </Folder>
        </Folder>
        <Folder name="config">
          <File path="packages/vehicles/drone-x1/config/drone_x1_components.xml">
            <Description>XML configuration file defining components for the drone-x1 vehicle.</Description>
            <Constructors />
            <Methods />
          </File>
        </Folder>
        <Folder name="src">
        </Folder>
        <Folder name="include">
        </Folder>
      </Folder>
      <Folder name="fixed-wing-alpha">
        <File path="packages/vehicles/fixed-wing-alpha/CMakeLists.txt">
          <Description>CMake build configuration for the fixed-wing-alpha vehicle package.</Description>
          <Constructors />
          <Methods />
        </File>
        <Folder name="assets">
          <Folder name="models">
          </Folder>
        </Folder>
        <Folder name="config">
        </Folder>
        <Folder name="src">
        </Folder>
        <Folder name="include">
        </Folder>
      </Folder>
    </Folder>
    <Folder name="environment">
      <File path="packages/environment/CMakeLists.txt">
        <Description>CMake build configuration for the environment package.</Description>
        <Constructors />
        <Methods />
      </File>
      <Folder name="world_gen">
        <File path="packages/environment/world_gen/CMakeLists.txt">
          <Description>CMake build configuration for the world generation package.</Description>
          <Constructors />
          <Methods />
        </File>
        <Folder name="scenes">
          <File path="packages/environment/world_gen/scenes/city_day_scene.xml">
            <Description>XML scene definition for a city day environment with procedural generation parameters.</Description>
            <Constructors />
            <Methods />
          </File>
        </Folder>
        <Folder name="furniture">
          <File path="packages/environment/world_gen/furniture/office_table_basic.xml">
            <Description>XML definition for a parametric office table furniture asset.</Description>
            <Constructors />
            <Methods />
          </File>
        </Folder>
        <Folder name="textures">
        </Folder>
      </Folder>
      <Folder name="assets">
        <Folder name="models">
        </Folder>
        <Folder name="textures">
        </Folder>
        <Folder name="sounds">
        </Folder>
        <Folder name="shaders">
        </Folder>
      </Folder>
    </Folder>
    <Folder name="ui">
      <File path="packages/ui/CMakeLists.txt">
        <Description>CMake build configuration for the UI package.</Description>
        <Constructors />
        <Methods />
      </File>
      <Folder name="assets">
        <Folder name="sounds">
        </Folder>
        <Folder name="images">
        </Folder>
      </Folder>
      <Folder name="config">
      </Folder>
      <Folder name="src">
      </Folder>
      <Folder name="include">
      </Folder>
    </Folder>
  </Folder>
  <Folder name="configs">
  </Folder>
</ProjectMap>
<?xml version="1.0" encoding="UTF-8"?>
<world_generation>
    <!-- Earth parameters -->
    <earth>
        <radius>6371000.0</radius>
        <detail_level>2</detail_level>
        <position>
            <x>0.0</x>
            <y>-6371000.0</y>
            <z>0.0</z>
        </position>
        <orientation>
            <x>0.0</x>
            <y>0.0</y>
            <z>0.0</z>
            <w>1.0</w>
        </orientation>
        <scale>
            <x>1.0</x>
            <y>1.0</y>
            <z>1.0</z>
        </scale>
    </earth>
    
    <!-- Atmosphere parameters -->
    <atmosphere>
        <layer id="1">
            <density>0.1</density>
        </layer>
    </atmosphere>
    
    <!-- Cloud parameters -->
    <clouds>
        <coverage>0.6</coverage>
        <density>0.3</density>
    </clouds>
    
    <!-- Scene parameters -->
    <scenes>
        <default_scene>loading_indicator</default_scene>
    </scenes>
</world_generation>
#include "ShaderAsset.h"
#include <sstream>

std::string BasicShaderGenerator::generateCelVertexShader(int bands)
{
    std::ostringstream ss;

    ss << "#version 330 core\n";
    ss << getCommonAttributes();
    ss << getCommonUniforms();
    ss << "\n";
    ss << "out vec3 FragPos;\n";
    ss << "out vec3 Normal;\n";
    ss << "out vec2 TexCoord;\n";
    ss << "out vec3 WorldPos;\n";
    ss << "\n";
    ss << "void main()\n";
    ss << "{\n";
    ss << "    FragPos = vec3(uModel * vec4(aPos, 1.0));\n";
    ss << "    Normal = mat3(transpose(inverse(uModel))) * aNormal;\n";
    ss << "    TexCoord = aTexCoord;\n";
    ss << "    WorldPos = FragPos;\n";
    ss << "\n";
    ss << "    gl_Position = uProjection * uView * vec4(FragPos, 1.0);\n";
    ss << "}\n";

    return ss.str();
}

std::string BasicShaderGenerator::generateCelFragmentShader(int bands, bool outlineEnabled)
{
    std::ostringstream ss;

    ss << "#version 330 core\n";
    ss << "in vec3 FragPos;\n";
    ss << "in vec3 Normal;\n";
    ss << "in vec2 TexCoord;\n";
    ss << "in vec3 WorldPos;\n";
    ss << "\n";
    ss << "out vec4 FragColor;\n";
    ss << "\n";
    ss << "uniform sampler2D uAlbedoTexture;\n";
    ss << "uniform vec3 uLightDirection;\n";
    ss << "uniform vec3 uLightColor;\n";
    ss << "uniform float uAmbientStrength;\n";
    ss << "uniform int uCelBands;\n";
    ss << "uniform bool uOutlineEnabled;\n";
    ss << "\n";
    ss << "void main()\n";
    ss << "{\n";
    ss << "    // Sample albedo texture\n";
    ss << "    vec4 albedo = texture(uAlbedoTexture, TexCoord);\n";
    ss << "    \n";
    ss << "    // Calculate lighting\n";
    ss << "    vec3 norm = normalize(Normal);\n";
    ss << "    vec3 lightDir = normalize(-uLightDirection);\n";
    ss << "    \n";
    ss << "    // Cel-shading calculation\n";
    ss << "    float NdotL = max(dot(norm, lightDir), 0.0);\n";
    ss << "    \n";
    ss << "    // Quantize lighting into bands\n";
    ss << "    float celFactor = floor(NdotL * float(uCelBands)) / float(uCelBands);\n";
    ss << "    \n";
    ss << "    // Apply ambient and diffuse lighting\n";
    ss << "    vec3 ambient = uAmbientStrength * uLightColor;\n";
    ss << "    vec3 diffuse = celFactor * uLightColor;\n";
    ss << "    \n";
    ss << "    vec3 result = (ambient + diffuse) * albedo.rgb;\n";
    ss << "    \n";
    ss << "    FragColor = vec4(result, albedo.a);\n";
    ss << "}\n";

    return ss.str();
}

std::string BasicShaderGenerator::generateUnlitVertexShader()
{
    std::ostringstream ss;

    ss << "#version 330 core\n";
    ss << getCommonAttributes();
    ss << getCommonUniforms();
    ss << "\n";
    ss << "out vec2 TexCoord;\n";
    ss << "\n";
    ss << "void main()\n";
    ss << "{\n";
    ss << "    TexCoord = aTexCoord;\n";
    ss << "    gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);\n";
    ss << "}\n";

    return ss.str();
}

std::string BasicShaderGenerator::generateUnlitFragmentShader()
{
    std::ostringstream ss;

    ss << "#version 330 core\n";
    ss << "in vec2 TexCoord;\n";
    ss << "\n";
    ss << "out vec4 FragColor;\n";
    ss << "\n";
    ss << "uniform sampler2D uAlbedoTexture;\n";
    ss << "uniform vec4 uColor;\n";
    ss << "\n";
    ss << "void main()\n";
    ss << "{\n";
    ss << "    vec4 texColor = texture(uAlbedoTexture, TexCoord);\n";
    ss << "    FragColor = texColor * uColor;\n";
    ss << "}\n";

    return ss.str();
}

std::unique_ptr<ShaderAsset> BasicShaderGenerator::createCelBandShader(const std::string &id,
                                                                       int bands,
                                                                       bool outlineEnabled)
{
    auto shader = std::make_unique<ShaderAsset>();

    shader->id = id;
    shader->path = "procedural://" + id; // Mark as procedurally generated
    shader->vertexSource = generateCelVertexShader(bands);
    shader->fragmentSource = generateCelFragmentShader(bands, outlineEnabled);

    // Set parameters
    shader->parameters["bands"] = std::to_string(bands);
    shader->parameters["outline_enabled"] = outlineEnabled ? "true" : "false";
    shader->parameters["specular_mode"] = "off";

    // Note: Actual compilation would happen in a rendering system
    shader->isCompiled = false;
    shader->programId = 0;

    return shader;
}

std::string BasicShaderGenerator::getCommonUniforms()
{
    std::ostringstream ss;
    ss << "uniform mat4 uModel;\n";
    ss << "uniform mat4 uView;\n";
    ss << "uniform mat4 uProjection;\n";
    return ss.str();
}

std::string BasicShaderGenerator::getCommonAttributes()
{
    std::ostringstream ss;
    ss << "layout (location = 0) in vec3 aPos;\n";
    ss << "layout (location = 1) in vec3 aNormal;\n";
    ss << "layout (location = 2) in vec2 aTexCoord;\n";
    return ss.str();
}
#pragma once
#include <string>
#include <map>
#include <memory>

/**
 * @file ShaderAsset.h
 * @brief Asset structure for shader resources.
 *
 * Defines the basic shader asset structure for loading and managing
 * shaders in the asset system. Supports vertex and fragment shader
 * sources with parameter definitions.
 */

/**
 * @struct ShaderAsset
 * @brief Asset data structure for shader resources.
 *
 * Contains shader source code, compilation state, and parameter definitions
 * for use in the rendering pipeline.
 */
struct ShaderAsset
{
    /** @brief Shader asset identifier */
    std::string id;

    /** @brief Path to the shader file */
    std::string path;

    /** @brief Vertex shader source code */
    std::string vertexSource;

    /** @brief Fragment shader source code */
    std::string fragmentSource;

    /** @brief Shader parameters and their default values */
    std::map<std::string, std::string> parameters;

    /** @brief Whether the shader has been compiled successfully */
    bool isCompiled;

    /** @brief Compilation error messages (if any) */
    std::string compilationErrors;

    /** @brief OpenGL shader program ID (if compiled) */
    unsigned int programId;

    /**
     * @brief Construct a new ShaderAsset.
     */
    ShaderAsset()
        : isCompiled(false), programId(0)
    {
    }

    /**
     * @brief Get parameter value with fallback.
     *
     * @param paramName Name of the parameter
     * @param defaultValue Default value if parameter not found
     * @return Parameter value or default
     */
    std::string getParameter(const std::string &paramName, const std::string &defaultValue = "") const
    {
        auto it = parameters.find(paramName);
        return (it != parameters.end()) ? it->second : defaultValue;
    }

    /**
     * @brief Check if parameter exists.
     *
     * @param paramName Name of the parameter to check
     * @return True if parameter exists
     */
    bool hasParameter(const std::string &paramName) const
    {
        return parameters.find(paramName) != parameters.end();
    }
};

/**
 * @class BasicShaderGenerator
 * @brief Generates basic shader source code for common materials.
 *
 * Provides factory methods for creating simple shaders including
 * the cel-shading shader used in the voxel busy indicator scene.
 */
class BasicShaderGenerator
{
public:
    /**
     * @brief Generate a cel-shading vertex shader.
     *
     * @param bands Number of cel-shading bands
     * @return Vertex shader source code
     */
    static std::string generateCelVertexShader(int bands = 4);

    /**
     * @brief Generate a cel-shading fragment shader.
     *
     * @param bands Number of cel-shading bands
     * @param outlineEnabled Whether outline rendering is enabled
     * @return Fragment shader source code
     */
    static std::string generateCelFragmentShader(int bands = 4, bool outlineEnabled = false);

    /**
     * @brief Generate a simple unlit vertex shader.
     *
     * @return Basic vertex shader source code
     */
    static std::string generateUnlitVertexShader();

    /**
     * @brief Generate a simple unlit fragment shader.
     *
     * @return Basic fragment shader source code
     */
    static std::string generateUnlitFragmentShader();

    /**
     * @brief Create a complete cel-shading shader asset.
     *
     * @param id Asset identifier
     * @param bands Number of cel-shading bands
     * @param outlineEnabled Whether outlines are enabled
     * @return Complete shader asset
     */
    static std::unique_ptr<ShaderAsset> createCelBandShader(const std::string &id,
                                                            int bands = 4,
                                                            bool outlineEnabled = false);

private:
    static std::string getCommonUniforms();
    static std::string getCommonAttributes();
};
/**
 * @file ContrailC.h
 * @brief Contrail component for particle trail effects behind aircraft
 *
 * The ContrailC component creates and manages particle-based trail effects
 * that follow aircraft in orbital motion. Features include:
 * - Physics-based particle lifecycle with fade curves
 * - Velocity-based particle spawning
 * - Configurable trail length and density
 * - Smooth particle interpolation for visual continuity
 * - Integration with orbital motion systems
 *
 * @author Generated for Voxel Busy Indicator Scene
 * @date 2024
 */

#pragma once

#include "../math/MathUtils.h"
#include <vector>
#include <cstdint>

/**
 * @brief Component for particle-based contrail effects
 *
 * Creates trailing particle effects behind moving aircraft with realistic
 * physics simulation and smooth visual transitions. Particles are spawned
 * based on velocity and fade over time using configurable curves.
 */
class ContrailC
{
public:
    /**
     * @brief Individual particle in the contrail system
     */
    struct Particle
    {
        Math::float3 position; /**< Current particle position */
        Math::float3 velocity; /**< Current particle velocity */
        float age;             /**< Particle age in seconds */
        float maxAge;          /**< Maximum particle lifetime */
        float size;            /**< Current particle size */
        float alpha;           /**< Current particle alpha/opacity */
        bool active;           /**< Whether particle is active */

        Particle() : position{0, 0, 0}, velocity{0, 0, 0}, age(0), maxAge(1), size(1), alpha(1), active(false) {}
    };

    /**
     * @brief Contrail configuration parameters
     */
    struct ContrailParams
    {
        float spawnRate;           /**< Particles per second */
        float particleLifetime;    /**< Max particle age in seconds */
        float initialSize;         /**< Starting particle size */
        float finalSize;           /**< Ending particle size */
        float velocityInheritance; /**< How much parent velocity particles inherit [0,1] */
        float gravityStrength;     /**< Downward gravity acceleration */
        float dragCoefficient;     /**< Air resistance factor */
        Math::float3 windVelocity; /**< Environmental wind vector */

        ContrailParams()
            : spawnRate(20.0f), particleLifetime(3.0f), initialSize(0.1f), finalSize(0.05f), velocityInheritance(0.3f), gravityStrength(0.5f), dragCoefficient(0.8f), windVelocity{0, 0, 0}
        {
        }
    };

private:
    /** @brief Current contrail configuration */
    ContrailParams params;

    /** @brief Active particle pool */
    std::vector<Particle> particles;

    /** @brief Maximum number of particles */
    size_t maxParticles;

    /** @brief Time accumulator for particle spawning */
    float spawnAccumulator;

    /** @brief Random state for particle variation */
    uint32_t randomState;

    /** @brief Whether contrail emission is enabled */
    bool emissionEnabled;

    /** @brief Last position for velocity calculation */
    Math::float3 lastPosition;

    /** @brief Whether last position is valid */
    bool hasLastPosition;

public:
    /**
     * @brief Construct a new ContrailC component
     *
     * @param maxParticleCount Maximum number of particles in the system
     * @param emitParticles Whether to start emitting particles immediately
     */
    ContrailC(size_t maxParticleCount = 100, bool emitParticles = true)
        : maxParticles(maxParticleCount), spawnAccumulator(0.0f), randomState(42), emissionEnabled(emitParticles), lastPosition{0, 0, 0}, hasLastPosition(false)
    {
        particles.reserve(maxParticles);
    }

    /**
     * @brief Set contrail parameters
     *
     * @param newParams New configuration parameters
     */
    void setParams(const ContrailParams &newParams)
    {
        params = newParams;
    }

    /**
     * @brief Get current contrail parameters
     *
     * @return Current configuration parameters
     */
    const ContrailParams &getParams() const
    {
        return params;
    }

    /**
     * @brief Enable or disable particle emission
     *
     * @param enabled Whether to emit new particles
     */
    void setEmissionEnabled(bool enabled)
    {
        emissionEnabled = enabled;
    }

    /**
     * @brief Check if particle emission is enabled
     *
     * @return True if emitting particles
     */
    bool isEmissionEnabled() const
    {
        return emissionEnabled;
    }

    /**
     * @brief Update contrail simulation
     *
     * @param deltaTime Time step in seconds
     * @param currentPosition Current emitter position
     */
    void update(float deltaTime, const Math::float3 &currentPosition)
    {
        // Calculate velocity from position change
        Math::float3 velocity = {0, 0, 0};
        if (hasLastPosition)
        {
            velocity = Math::scale(Math::sub(currentPosition, lastPosition), 1.0f / deltaTime);
        }

        // Update existing particles
        updateParticles(deltaTime);

        // Spawn new particles if emission is enabled
        if (emissionEnabled)
        {
            spawnParticles(deltaTime, currentPosition, velocity);
        }

        // Update last position
        lastPosition = currentPosition;
        hasLastPosition = true;
    }

    /**
     * @brief Get all active particles
     *
     * @return Vector of active particles
     */
    std::vector<Particle> getActiveParticles() const
    {
        std::vector<Particle> active;
        for (const auto &particle : particles)
        {
            if (particle.active)
            {
                active.push_back(particle);
            }
        }
        return active;
    }

    /**
     * @brief Get number of active particles
     *
     * @return Count of active particles
     */
    size_t getActiveParticleCount() const
    {
        size_t count = 0;
        for (const auto &particle : particles)
        {
            if (particle.active)
                count++;
        }
        return count;
    }

    /**
     * @brief Clear all particles
     */
    void clearParticles()
    {
        for (auto &particle : particles)
        {
            particle.active = false;
        }
    }

private:
    /**
     * @brief Update all active particles
     *
     * @param deltaTime Time step in seconds
     */
    void updateParticles(float deltaTime)
    {
        for (auto &particle : particles)
        {
            if (!particle.active)
                continue;

            // Age the particle
            particle.age += deltaTime;

            // Check if particle should die
            if (particle.age >= particle.maxAge)
            {
                particle.active = false;
                continue;
            }

            // Calculate age ratio for fade curves
            float ageRatio = particle.age / particle.maxAge;

            // Apply physics forces
            Math::float3 forces = {0, 0, 0};

            // Gravity
            forces = Math::add(forces, {0, -params.gravityStrength, 0});

            // Drag (air resistance)
            Math::float3 dragForce = Math::scale(particle.velocity, -params.dragCoefficient);
            forces = Math::add(forces, dragForce);

            // Wind
            Math::float3 windForce = Math::scale(
                Math::sub(params.windVelocity, particle.velocity),
                params.dragCoefficient * 0.5f);
            forces = Math::add(forces, windForce);

            // Update velocity and position
            particle.velocity = Math::add(particle.velocity, Math::scale(forces, deltaTime));
            particle.position = Math::add(particle.position, Math::scale(particle.velocity, deltaTime));

            // Update visual properties using fade curves
            particle.size = Math::lerp(params.initialSize, params.finalSize, ageRatio);
            particle.alpha = Math::fadeOut(ageRatio); // Smooth fade out over lifetime
        }
    }

    /**
     * @brief Spawn new particles based on emission rate
     *
     * @param deltaTime Time step in seconds
     * @param position Current emitter position
     * @param velocity Current emitter velocity
     */
    void spawnParticles(float deltaTime, const Math::float3 &position, const Math::float3 &velocity)
    {
        spawnAccumulator += deltaTime;

        float spawnInterval = 1.0f / params.spawnRate;
        while (spawnAccumulator >= spawnInterval)
        {
            spawnParticle(position, velocity);
            spawnAccumulator -= spawnInterval;
        }
    }

    /**
     * @brief Spawn a single particle
     *
     * @param position Spawn position
     * @param velocity Emitter velocity
     */
    void spawnParticle(const Math::float3 &position, const Math::float3 &velocity)
    {
        // Find inactive particle slot
        Particle *particle = nullptr;
        for (auto &p : particles)
        {
            if (!p.active)
            {
                particle = &p;
                break;
            }
        }

        // If no slot available and under max count, add new particle
        if (!particle && particles.size() < maxParticles)
        {
            particles.emplace_back();
            particle = &particles.back();
        }

        // If still no slot, skip spawning
        if (!particle)
            return;

        // Initialize particle
        particle->active = true;
        particle->age = 0.0f;
        particle->maxAge = params.particleLifetime * (0.8f + 0.4f * Math::rand01(randomState));

        // Position with small random offset
        Math::float3 offset = {
            (Math::rand01(randomState) - 0.5f) * 0.02f,
            (Math::rand01(randomState) - 0.5f) * 0.02f,
            (Math::rand01(randomState) - 0.5f) * 0.02f};
        particle->position = Math::add(position, offset);

        // Velocity inheritance with random variation
        Math::float3 inheritedVel = Math::scale(velocity, params.velocityInheritance);
        Math::float3 randomVel = {
            (Math::rand01(randomState) - 0.5f) * 0.1f,
            (Math::rand01(randomState) - 0.5f) * 0.1f,
            (Math::rand01(randomState) - 0.5f) * 0.1f};
        particle->velocity = Math::add(inheritedVel, randomVel);

        // Visual properties
        particle->size = params.initialSize;
        particle->alpha = 1.0f;
    }
};
#pragma once
#include "../core/IComponent.h"
#include <unordered_map>
#include <string>

/**
 * @file DebugC.h
 * @brief Component for entities that require debug visualization or information.
 *
 * The DebugC component provides debugging capabilities for entities,
 * including debug names, visualization options, and debug data storage.
 * This component is typically used during development and debugging phases.
 */

/**
 * @struct DebugC
 * @brief Component that provides debugging information and visualization for an entity.
 *
 * This component inherits from IComponent and adds debugging capabilities
 * such as entity naming, debug rendering options, and custom debug data.
 * Debug components are usually processed by debug rendering systems.
 */
struct DebugC : public IComponent
{
    /** @brief Human-readable name for the entity (for debugging purposes) */
    std::string debugName;

    /** @brief Whether to show debug visualization for this entity */
    bool showDebugInfo;

    /** @brief Whether to render debug bounding boxes or wireframes */
    bool showBoundingBox;

    /** @brief Custom debug data as key-value pairs */
    std::unordered_map<std::string, std::string> debugData;

    /**
     * @brief Construct a new DebugC component.
     *
     * @param name Debug name for the entity (default: empty string)
     * @param showInfo Whether to show debug information (default: false)
     * @param showBox Whether to show bounding box (default: false)
     */
    DebugC(std::string name = "", bool showInfo = false, bool showBox = false)
        : debugName(name), showDebugInfo(showInfo), showBoundingBox(showBox) {}
};
#pragma once
#include "../core/IComponent.h"
#include "../math/MathUtils.h"

/**
 * @file OrbitalC.h
 * @brief Component for entities that follow orbital motion around a center point
 *
 * The OrbitalC component defines orbital motion parameters including center point,
 * orbital radius, angular speed, orbital axis, and phase offset. Entities with this
 * component will be updated by the OrbitalSystem to follow elliptical orbital paths
 * with proper velocity-based orientation and banking for aircraft.
 */

/**
 * @struct OrbitalC
 * @brief Component that defines orbital motion properties for an entity
 *
 * This component inherits from IComponent and provides all necessary parameters
 * for realistic orbital motion including elliptical orbits, inclination, and
 * coordinated banking for aircraft entities.
 */
struct OrbitalC : public IComponent
{
    /** @brief Center point of orbital motion in world space */
    Math::float3 center;

    /** @brief Orbital parameters for elliptical motion */
    Math::OrbitParams orbitParams;

    /** @brief Current time accumulator for orbit calculation */
    float currentTime;

    /** @brief Whether to apply banking for aircraft-like entities */
    bool enableBanking;

    /** @brief Maximum banking angle in radians (for aircraft) */
    float maxBankAngle;

    /** @brief Speed jitter percentage for natural variation */
    float speedJitter;

    /** @brief Random seed for deterministic jitter */
    uint32_t randomSeed;

    /** @brief Current banking angle (internal state) */
    float currentBankAngle;

    /** @brief Current banking rate (internal state) */
    float currentBankRate;

    /**
     * @brief Construct a new OrbitalC component
     *
     * @param centerPoint Center of orbital motion (default: origin)
     * @param radius Orbital radius (default: 1.0)
     * @param speed Angular speed in rad/s (default: 1.0)
     * @param axis Orbital axis (default: Y-axis)
     * @param phase Initial phase offset (default: 0.0)
     * @param banking Enable banking for aircraft (default: false)
     */
    OrbitalC(const Math::float3 &centerPoint = {0, 0, 0},
             float radius = 1.0f,
             float speed = 1.0f,
             const Math::float3 &axis = {0, 1, 0},
             float phase = 0.0f,
             bool banking = false)
        : center(centerPoint), currentTime(0.0f), enableBanking(banking), maxBankAngle(15.0f * Math::DegToRad), speedJitter(0.0f), randomSeed(12345), currentBankAngle(0.0f), currentBankRate(0.0f)
    {
        // Initialize orbital parameters
        orbitParams.semiMajorAxis = radius;
        orbitParams.eccentricity = 0.0f; // circular by default
        orbitParams.angularRate = speed;
        orbitParams.phaseOffset = phase;

        // Calculate inclination from axis (assume axis is rotation axis)
        Math::float3 worldY = {0, 1, 0};
        Math::float3 normalizedAxis = Math::norm(axis);
        orbitParams.inclination = std::acos(Math::clamp(Math::dot(normalizedAxis, worldY), -1.0f, 1.0f));
    }

    /**
     * @brief Get current orbital position
     *
     * @return Current 3D position on orbit relative to center
     */
    Math::float3 getCurrentPosition() const
    {
        // Apply speed jitter if enabled
        float jitteredTime = currentTime;
        if (speedJitter > 0.0f)
        {
            uint32_t state = randomSeed;
            float jitter = 1.0f + speedJitter * (2.0f * Math::rand01(state) - 1.0f);
            jitteredTime *= jitter;
        }

        Math::float3 localPos = Math::calculateOrbitPosition(orbitParams, jitteredTime);
        return Math::add(center, localPos);
    }

    /**
     * @brief Get current orbital velocity
     *
     * @return Current 3D velocity vector
     */
    Math::float3 getCurrentVelocity() const
    {
        return Math::calculateOrbitVelocity(orbitParams, currentTime);
    }

    /**
     * @brief Get current orientation quaternion (for aircraft with banking)
     *
     * @return Orientation quaternion with velocity alignment and banking
     */
    Math::quat getCurrentOrientation() const
    {
        Math::float3 velocity = getCurrentVelocity();
        Math::float3 position = getCurrentPosition();

        if (Math::len(velocity) < 1e-4f)
        {
            return Math::quat::identity();
        }

        // Forward direction aligned with velocity
        Math::float3 forward = Math::norm(velocity);

        if (enableBanking)
        {
            // Calculate banking angle for coordinated turn
            float bankAngle = Math::calculateBankingAngle(velocity, Math::sub(position, center), maxBankAngle);

            // Apply banking to up vector
            Math::float3 worldUp = {0, 1, 0};
            Math::float3 right = Math::norm(Math::cross(worldUp, forward));
            Math::float3 up = Math::cross(forward, right);

            // Roll around forward axis for banking
            Math::quat bankRotation = Math::q_from_axis_angle(forward, bankAngle);
            Math::float3 bankedUp = Math::q_rotate(bankRotation, up);

            return Math::q_look_rotation(forward, bankedUp);
        }
        else
        {
            // Simple velocity alignment without banking
            Math::float3 worldUp = {0, 1, 0};
            return Math::q_look_rotation(forward, worldUp);
        }
    }

    /**
     * @brief Set elliptical orbit parameters
     *
     * @param semiMajor Semi-major axis length
     * @param eccentricity Orbital eccentricity [0,1)
     */
    void setEllipticalOrbit(float semiMajor, float eccentricity)
    {
        orbitParams.semiMajorAxis = semiMajor;
        orbitParams.eccentricity = Math::clamp(eccentricity, 0.0f, 0.99f);
    }

    /**
     * @brief Set orbital inclination angle
     *
     * @param inclinationDegrees Inclination angle in degrees
     */
    void setInclination(float inclinationDegrees)
    {
        orbitParams.inclination = inclinationDegrees * Math::DegToRad;
    }

    /**
     * @brief Enable speed jitter for natural orbital variation
     *
     * @param jitterPercent Jitter percentage (e.g., 0.05 for ±5%)
     * @param seed Random seed for deterministic jitter
     */
    void setSpeedJitter(float jitterPercent, uint32_t seed)
    {
        speedJitter = jitterPercent;
        randomSeed = seed;
    }

    /**
     * @brief Update orbital motion by time step
     *
     * @param deltaTime Time step in seconds
     */
    void update(float deltaTime)
    {
        currentTime += deltaTime;
    }

    /**
     * @brief Reset orbital time to specific value
     *
     * @param time New time value
     */
    void setTime(float time)
    {
        currentTime = time;
    }
};
#pragma once
#include "../core/IComponent.h"

/**
 * @file RenderableC.h
 * @brief Component for entities that can be visually rendered in the scene.
 *
 * The RenderableC component defines the visual properties of an entity,
 * including mesh geometry, material appearance, and visibility state.
 * Entities with this component can be processed by rendering systems.
 */

/**
 * @struct RenderableC
 * @brief Component that defines visual rendering properties for an entity.
 *
 * This component inherits from IComponent and provides the necessary
 * information for rendering systems to display the entity. It references
 * mesh and material assets by ID and controls visibility.
 */
struct RenderableC : public IComponent
{
    /** @brief ID of the mesh asset used for rendering geometry */
    std::string meshId;

    /** @brief ID of the material asset used for surface appearance */
    std::string materialId;

    /** @brief Whether the entity should be rendered (true) or hidden (false) */
    bool isVisible;

    /**
     * @brief Construct a new RenderableC component.
     *
     * @param mesh ID of the mesh asset (empty string for no mesh)
     * @param material ID of the material asset (empty string for no material)
     * @param visible Initial visibility state (default: true)
     */
    RenderableC(std::string mesh = "", std::string material = "", bool visible = true)
        : meshId(mesh), materialId(material), isVisible(visible) {}
};
#pragma once
#include "../core/IComponent.h"
#include "../math/Vector3D.h"
#include "../math/Quaternion.h"

/**
 * @file TransformC.h
 * @brief Component for entities that have spatial positioning and orientation.
 *
 * The TransformC component defines the spatial properties of an entity in 3D space,
 * including position, rotation, and scale. This is a fundamental component used
 * by most entities in the simulation for positioning and transformation.
 */

/**
 * @struct TransformC
 * @brief Component that defines the spatial transformation of an entity.
 *
 * This component inherits from IComponent and provides 3D transformation
 * properties including position, rotation (as quaternion), and scale.
 * Transform components are processed by transformation and rendering systems.
 */
struct TransformC : public IComponent
{
    /** @brief Position of the entity in 3D world space */
    Vector3D position;

    /** @brief Rotation of the entity as a quaternion */
    Quaternion rotation;

    /** @brief Scale of the entity in each axis */
    Vector3D scale;

    /**
     * @brief Construct a new TransformC component.
     *
     * @param pos Initial position (default: origin)
     * @param rot Initial rotation (default: identity quaternion)
     * @param scl Initial scale (default: unit scale)
     */
    TransformC(Vector3D pos = Vector3D(), Quaternion rot = Quaternion(), Vector3D scl = Vector3D(1.0f, 1.0f, 1.0f))
        : position(pos), rotation(rot), scale(scl) {}
};
/**
 * @file VoxelCloudC.h
 * @brief Voxel cloud component for orbital cloud systems
 *
 * The VoxelCloudC component manages large-scale orbital cloud formations
 * that consist of multiple voxel elements. Features include:
 * - Orbital precession with slow rotation around multiple axes
 * - Procedural cloud density and lifecycle management
 * - Fade curves for natural appearance and disappearance
 * - Integration with orbital mechanics for realistic motion
 * - Hierarchical cloud structure with multiple detail levels
 *
 * @author Generated for Voxel Busy Indicator Scene
 * @date 2024
 */

#pragma once

#include "../math/MathUtils.h"
#include <vector>
#include <cstdint>

/**
 * @brief Component for large-scale orbital voxel cloud systems
 *
 * Manages collections of voxel elements that move in complex orbital
 * patterns with precession and hierarchical organization. Clouds can
 * have multiple detail levels and smooth lifecycle transitions.
 */
class VoxelCloudC
{
public:
    /**
     * @brief Individual voxel element in the cloud
     */
    struct VoxelElement
    {
        Math::float3 localPosition; /**< Position relative to cloud center */
        Math::float3 velocity;      /**< Current velocity vector */
        float density;              /**< Voxel density/opacity [0,1] */
        float size;                 /**< Voxel size multiplier */
        float age;                  /**< Element age in seconds */
        float maxAge;               /**< Maximum element lifetime */
        bool active;                /**< Whether element is active */

        VoxelElement() : localPosition{0, 0, 0}, velocity{0, 0, 0}, density(1), size(1), age(0), maxAge(10), active(false) {}
    };

    /** @brief Phase offset for density animation uniqueness */
    float densityPhase;

    /**
     * @brief Cloud configuration parameters
     */
    struct CloudParams
    {
        Math::OrbitParams primaryOrbit;    /**< Primary orbital motion */
        Math::OrbitParams precessionOrbit; /**< Precession orbital motion */
        float cloudRadius;                 /**< Maximum cloud extent */
        float elementCount;                /**< Target number of voxel elements */
        float densityVariation;            /**< Random density variation [0,1] */
        float sizeVariation;               /**< Random size variation [0,1] */
        float turbulenceStrength;          /**< Internal turbulence factor */
        float cohesionStrength;            /**< Element attraction to center */
        float fadeInTime;                  /**< Time to fade in from spawn */
        float fadeOutTime;                 /**< Time to fade out before death */

        CloudParams()
            : cloudRadius(2.0f), elementCount(50.0f), densityVariation(0.3f), sizeVariation(0.4f), turbulenceStrength(0.1f), cohesionStrength(0.5f), fadeInTime(2.0f), fadeOutTime(3.0f)
        {
            // Default primary orbit (large, slow)
            primaryOrbit.semiMajorAxis = 8.0f;
            primaryOrbit.eccentricity = 0.1f;
            primaryOrbit.angularRate = 0.1f;
            primaryOrbit.inclination = 0.2f;
            primaryOrbit.phaseOffset = 0.0f;

            // Default precession orbit (slow rotation)
            precessionOrbit.semiMajorAxis = 1.0f;
            precessionOrbit.eccentricity = 0.0f;
            precessionOrbit.angularRate = 0.02f;
            precessionOrbit.inclination = 0.1f;
            precessionOrbit.phaseOffset = 0.0f;
        }
    };

private:
    /** @brief Current cloud configuration */
    CloudParams params;

    /** @brief Cloud center position in world space */
    Math::float3 worldPosition;

    /** @brief Current cloud orientation quaternion */
    Math::quat worldOrientation;

    /** @brief Active voxel elements */
    std::vector<VoxelElement> elements;

    /** @brief Current primary orbital time */
    float primaryTime;

    /** @brief Current precession orbital time */
    float precessionTime;

    /** @brief Random state for procedural generation */
    uint32_t randomState;

    /** @brief Cloud lifecycle state */
    enum LifecycleState
    {
        SPAWNING,  /**< Cloud is fading in */
        ACTIVE,    /**< Cloud is fully active */
        DESPAWNING /**< Cloud is fading out */
    } lifecycleState;

    /** @brief Current lifecycle time */
    float lifecycleTime;

    /** @brief Total cloud lifetime (0 = infinite) */
    float totalLifetime;

public:
    /**
     * @brief Construct a new VoxelCloudC component
     *
     * @param cloudLifetime Total cloud lifetime (0 for infinite)
     * @param seed Random seed for procedural generation
     */
    VoxelCloudC(float cloudLifetime = 0.0f, uint32_t seed = 12345)
        : worldPosition{0, 0, 0}, worldOrientation(Math::quat::identity()), primaryTime(0.0f), precessionTime(0.0f), randomState(seed), lifecycleState(SPAWNING), lifecycleTime(0.0f), totalLifetime(cloudLifetime)
    {
        generateElements();
    }

    /**
     * @brief Set cloud parameters
     *
     * @param newParams New configuration parameters
     */
    void setParams(const CloudParams &newParams)
    {
        params = newParams;
        generateElements(); // Regenerate with new parameters
    }

    /**
     * @brief Get current cloud parameters
     *
     * @return Current configuration parameters
     */
    const CloudParams &getParams() const
    {
        return params;
    }

    /**
     * @brief Update cloud simulation
     *
     * @param deltaTime Time step in seconds
     * @param globalCenter Global center point for orbital motion
     */
    void update(float deltaTime, const Math::float3 &globalCenter)
    {
        // Update orbital times
        primaryTime += deltaTime;
        precessionTime += deltaTime;

        // Update lifecycle
        updateLifecycle(deltaTime);

        // Calculate orbital positions
        updateOrbitalMotion(globalCenter);

        // Update individual elements
        updateElements(deltaTime);
    }

    /**
     * @brief Get current world position of cloud center
     *
     * @return World space position
     */
    Math::float3 getWorldPosition() const
    {
        return worldPosition;
    }

    /**
     * @brief Get current world orientation of cloud
     *
     * @return World space orientation quaternion
     */
    Math::quat getWorldOrientation() const
    {
        return worldOrientation;
    }

    /**
     * @brief Get all active voxel elements
     *
     * @return Vector of active elements
     */
    std::vector<VoxelElement> getActiveElements() const
    {
        std::vector<VoxelElement> active;
        for (const auto &element : elements)
        {
            if (element.active && element.density > 0.01f)
            {
                active.push_back(element);
            }
        }
        return active;
    }

    /**
     * @brief Get element world positions
     *
     * @return Vector of world space positions for all active elements
     */
    std::vector<Math::float3> getElementWorldPositions() const
    {
        std::vector<Math::float3> positions;
        for (const auto &element : elements)
        {
            if (element.active && element.density > 0.01f)
            {
                // Transform local position to world space
                Math::float3 rotatedPos = Math::q_rotate(worldOrientation, element.localPosition);
                Math::float3 worldPos = Math::add(worldPosition, rotatedPos);
                positions.push_back(worldPos);
            }
        }
        return positions;
    }

    /**
     * @brief Check if cloud is in despawning state
     *
     * @return True if cloud is fading out
     */
    bool isDespawning() const
    {
        return lifecycleState == DESPAWNING;
    }

    /**
     * @brief Check if cloud should be destroyed
     *
     * @return True if cloud lifecycle is complete
     */
    bool shouldDestroy() const
    {
        return lifecycleState == DESPAWNING && lifecycleTime >= params.fadeOutTime;
    }

    /**
     * @brief Force cloud to start despawning
     */
    void startDespawning()
    {
        if (lifecycleState != DESPAWNING)
        {
            lifecycleState = DESPAWNING;
            lifecycleTime = 0.0f;
        }
    }

private:
    /**
     * @brief Generate voxel elements based on current parameters
     */
    void generateElements()
    {
        elements.clear();
        elements.reserve(static_cast<size_t>(params.elementCount));

        for (int i = 0; i < static_cast<int>(params.elementCount); ++i)
        {
            VoxelElement element;

            // Generate random position within cloud radius using sphere distribution
            float radius = params.cloudRadius * std::pow(Math::rand01(randomState), 1.0f / 3.0f);
            float theta = 2.0f * Math::Pi * Math::rand01(randomState);
            float phi = std::acos(2.0f * Math::rand01(randomState) - 1.0f);

            element.localPosition.x = radius * std::sin(phi) * std::cos(theta);
            element.localPosition.y = radius * std::sin(phi) * std::sin(theta);
            element.localPosition.z = radius * std::cos(phi);

            // Random velocity for internal motion
            element.velocity.x = (Math::rand01(randomState) - 0.5f) * params.turbulenceStrength;
            element.velocity.y = (Math::rand01(randomState) - 0.5f) * params.turbulenceStrength;
            element.velocity.z = (Math::rand01(randomState) - 0.5f) * params.turbulenceStrength;

            // Random properties
            element.density = 1.0f - params.densityVariation * Math::rand01(randomState);
            element.size = 1.0f - params.sizeVariation * (Math::rand01(randomState) - 0.5f);
            element.age = 0.0f;
            element.maxAge = 20.0f + 40.0f * Math::rand01(randomState); // Variable lifetime
            element.active = true;

            elements.push_back(element);
        }
    }

    /**
     * @brief Update cloud lifecycle state
     *
     * @param deltaTime Time step in seconds
     */
    void updateLifecycle(float deltaTime)
    {
        lifecycleTime += deltaTime;

        switch (lifecycleState)
        {
        case SPAWNING:
            if (lifecycleTime >= params.fadeInTime)
            {
                lifecycleState = ACTIVE;
                lifecycleTime = 0.0f;
            }
            break;

        case ACTIVE:
            if (totalLifetime > 0.0f && lifecycleTime >= totalLifetime)
            {
                lifecycleState = DESPAWNING;
                lifecycleTime = 0.0f;
            }
            break;

        case DESPAWNING:
            // Handled in shouldDestroy()
            break;
        }
    }

    /**
     * @brief Update orbital motion calculation
     *
     * @param globalCenter Global center for orbital motion
     */
    void updateOrbitalMotion(const Math::float3 &globalCenter)
    {
        // Calculate primary orbital position
        Math::float3 primaryPos = Math::calculateOrbitPosition(params.primaryOrbit, primaryTime);

        // Calculate precession rotation
        Math::float3 precessionAxis = {0, 1, 0}; // Default vertical axis
        float precessionAngle = precessionTime * params.precessionOrbit.angularRate;
        Math::quat precessionQuat = Math::q_from_axis_angle(precessionAxis, precessionAngle);

        // Apply inclination to precession
        Math::float3 inclinationAxis = {1, 0, 0};
        Math::quat inclinationQuat = Math::q_from_axis_angle(inclinationAxis, params.precessionOrbit.inclination);

        // Combine rotations
        worldOrientation = Math::q_mul(inclinationQuat, precessionQuat);

        // Calculate final world position
        worldPosition = Math::add(globalCenter, primaryPos);
    }

    /**
     * @brief Update individual voxel elements
     *
     * @param deltaTime Time step in seconds
     */
    void updateElements(float deltaTime)
    {
        float globalAlpha = 1.0f;

        // Calculate global alpha based on lifecycle
        switch (lifecycleState)
        {
        case SPAWNING:
            globalAlpha = Math::fadeIn(lifecycleTime / params.fadeInTime);
            break;
        case ACTIVE:
            globalAlpha = 1.0f;
            break;
        case DESPAWNING:
            globalAlpha = Math::fadeOut(lifecycleTime / params.fadeOutTime);
            break;
        }

        for (auto &element : elements)
        {
            if (!element.active)
                continue;

            // Age the element
            element.age += deltaTime;

            // Apply cohesion force (attraction to center)
            Math::float3 toCenter = Math::scale(element.localPosition, -1.0f);
            float distance = Math::len(toCenter);
            if (distance > 0.01f)
            {
                Math::float3 cohesionForce = Math::scale(
                    Math::norm(toCenter),
                    params.cohesionStrength / (1.0f + distance));
                element.velocity = Math::add(element.velocity, Math::scale(cohesionForce, deltaTime));
            }

            // Apply velocity damping
            element.velocity = Math::scale(element.velocity, std::pow(0.9f, deltaTime));

            // Update position
            element.localPosition = Math::add(element.localPosition, Math::scale(element.velocity, deltaTime));

            // Keep elements within cloud radius
            float distanceFromCenter = Math::len(element.localPosition);
            if (distanceFromCenter > params.cloudRadius)
            {
                element.localPosition = Math::scale(
                    Math::norm(element.localPosition),
                    params.cloudRadius);
            }

            // Update density based on age and global lifecycle
            float ageFactor = 1.0f;
            if (element.age > element.maxAge * 0.8f)
            {
                ageFactor = Math::fadeOut((element.age - element.maxAge * 0.8f) / (element.maxAge * 0.2f));
            }

            element.density = (1.0f - params.densityVariation * Math::rand01(randomState)) * globalAlpha * ageFactor;

            // Deactivate old elements
            if (element.age > element.maxAge || element.density < 0.01f)
            {
                element.active = false;
            }
        }
    }
};
#include "SceneConfigParser.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <regex>
#include <iostream>

namespace SceneConfig
{

    // ============================================================================
    // SceneConfigParser Implementation
    // ============================================================================

    SceneConfigParser::SceneConfigParser(const ParserConfig &config) : config_(config)
    {
        // Initialize default values and lookup tables
    }

    ParseResult SceneConfigParser::parseSceneFile(const std::string &filePath)
    {
        currentResult_ = ParseResult{};
        auto startTime = std::chrono::high_resolution_clock::now();

        // Read file content
        std::ifstream file(filePath);
        if (!file.is_open())
        {
            currentResult_.success = false;
            currentResult_.errorMessage = "Failed to open file: " + filePath;
            return currentResult_;
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string xmlContent = buffer.str();
        file.close();

        // Parse the XML content
        auto result = parseSceneString(xmlContent);

        // If successful and asset resolution is enabled, resolve paths relative to the scene file
        if (result.success && config_.loadExternalAssets && result.scene)
        {
            // Simple base directory resolution - just get directory from file path
            size_t lastSlash = filePath.find_last_of("/\\");
            if (lastSlash != std::string::npos)
            {
                std::string baseDirectory = filePath.substr(0, lastSlash + 1);
                resolveAssetPaths(*result.scene, baseDirectory);
            }
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        result.parseTimeMs = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

        return result;
    }

    ParseResult SceneConfigParser::parseSceneString(const std::string &xmlContent)
    {
        currentResult_ = ParseResult{};

        try
        {
            // For now, create a minimal scene for loading_indicator type
            auto scene = std::make_shared<Scene>();

            // Simple XML attribute extraction - basic implementation
            scene->id = extractAttributeSimple(xmlContent, "scene", "id", "default_scene");
            scene->name = extractAttributeSimple(xmlContent, "scene", "name", scene->id);
            scene->type = extractAttributeSimple(xmlContent, "scene", "type", "loading_indicator");
            scene->version = extractAttributeSimple(xmlContent, "scene", "version", "1.0");

            // For loading_indicator scenes, we don't need complex parsing
            // Just set up basic structure
            currentResult_.scene = scene;
            currentResult_.success = true;
            currentResult_.errorMessage = "";
        }
        catch (const std::exception &e)
        {
            currentResult_.success = false;
            currentResult_.errorMessage = std::string("Parse error: ") + e.what();
        }

        return currentResult_;
    }

    // Simple helper method for basic attribute extraction
    std::string SceneConfigParser::extractAttributeSimple(const std::string &xmlContent,
                                                          const std::string &elementName,
                                                          const std::string &attributeName,
                                                          const std::string &defaultValue)
    {
        // Simple regex-based attribute extraction
        std::string pattern = "<" + elementName + "[^>]*" + attributeName + "=\"([^\"]*?)\"";
        std::regex re(pattern);
        std::smatch match;

        if (std::regex_search(xmlContent, match, re))
        {
            return match[1].str();
        }

        return defaultValue;
    }

    bool SceneConfigParser::resolveAssetPaths(Scene &scene, const std::string &baseDirectory)
    {
        // Simple implementation - just return true for now
        // In a full implementation, this would resolve all asset paths relative to baseDirectory
        return true;
    }

} // namespace SceneConfig
#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <variant>
#include <optional>

// Forward declarations for ECS components
namespace ECS
{
    class Entity;
    class World;
}

namespace SceneConfig
{

    // ============================================================================
    // Scene Data Structures
    // ============================================================================

    struct Transform
    {
        struct Position
        {
            float x, y, z;
        };
        struct Rotation
        {
            float x, y, z, w;
        }; // Quaternion
        struct Scale
        {
            float x, y, z;
        };

        Position position = {0.0f, 0.0f, 0.0f};
        Rotation rotation = {0.0f, 0.0f, 0.0f, 1.0f};
        Scale scale = {1.0f, 1.0f, 1.0f};
    };

    struct VoxelPrimitive
    {
        enum class Type
        {
            Cube,
            Sphere,
            Cylinder,
            Plane
        };

        Type type = Type::Cube;
        float size = 1.0f;
        float radius = 0.5f;
        float height = 1.0f;
        uint32_t subdivisions = 1;
        Transform transform;
        std::string materialId;

        // Animation properties
        bool animated = false;
        std::string animationType;
        std::map<std::string, std::string> animationParams;
    };

    struct CompoundMesh
    {
        std::string id;
        std::string name;
        std::vector<VoxelPrimitive> parts;
        Transform baseTransform;
        std::string materialId;

        // Animation properties
        bool animated = false;
        std::string animationType;
        std::map<std::string, std::string> animationParams;
    };

    struct Material
    {
        std::string id;
        std::string name;
        std::string shader = "standard";

        // Basic material properties
        struct Color
        {
            float r, g, b, a;
        };
        Color diffuse = {1.0f, 1.0f, 1.0f, 1.0f};
        Color ambient = {0.2f, 0.2f, 0.2f, 1.0f};
        Color specular = {1.0f, 1.0f, 1.0f, 1.0f};
        Color emissive = {0.0f, 0.0f, 0.0f, 1.0f};

        float metallic = 0.0f;
        float roughness = 0.5f;
        float shininess = 32.0f;
        float opacity = 1.0f;

        // Texture references
        std::string diffuseTexture;
        std::string normalTexture;
        std::string specularTexture;
        std::string emissiveTexture;

        // Cel-shading specific
        bool celShading = false;
        uint32_t celLevels = 3;
        float celThreshold = 0.5f;
        Color celOutlineColor = {0.0f, 0.0f, 0.0f, 1.0f};
        float celOutlineWidth = 0.01f;

        // Additional properties
        std::map<std::string, std::string> customProperties;
    };

    struct ProceduralTexture
    {
        std::string id;
        std::string name;
        std::string type; // "noise", "gradient", "pattern", "composite"
        uint32_t width = 256;
        uint32_t height = 256;
        std::string format = "RGBA";

        // Generation parameters
        std::map<std::string, std::string> parameters;
    };

    struct Animation
    {
        std::string id;
        std::string name;
        std::string type; // "orbital", "rotation", "scale", "transform", "compound"
        float duration = 1.0f;
        bool loop = true;
        bool autoStart = true;

        // Target specification
        std::string targetType; // "entity", "component", "material"
        std::string targetId;

        // Animation parameters
        std::map<std::string, std::string> parameters;

        // Keyframes (optional, for complex animations)
        struct Keyframe
        {
            float time;
            std::map<std::string, std::string> values;
        };
        std::vector<Keyframe> keyframes;
    };

    struct Camera
    {
        std::string id = "main_camera";
        Transform transform;

        enum class Type
        {
            Perspective,
            Orthographic
        };
        Type type = Type::Perspective;

        // Perspective parameters
        float fov = 45.0f;
        float nearPlane = 0.1f;
        float farPlane = 1000.0f;

        // Orthographic parameters
        float left = -10.0f, right = 10.0f;
        float bottom = -10.0f, top = 10.0f;

        // Animation
        bool animated = false;
        std::string animationId;
    };

    struct Light
    {
        std::string id;
        std::string name;

        enum class Type
        {
            Directional,
            Point,
            Spot,
            Ambient
        };
        Type type = Type::Directional;

        Transform transform;
        Material::Color color = {1.0f, 1.0f, 1.0f, 1.0f};
        float intensity = 1.0f;

        // Point/Spot light parameters
        float range = 10.0f;
        float constantAttenuation = 1.0f;
        float linearAttenuation = 0.09f;
        float quadraticAttenuation = 0.032f;

        // Spot light parameters
        float innerCone = 30.0f; // degrees
        float outerCone = 45.0f; // degrees

        // Animation
        bool animated = false;
        std::string animationId;
    };

    struct Entity
    {
        std::string id;
        std::string name;
        std::string type; // "mesh", "light", "camera", "compound"
        Transform transform;

        // Component references
        std::string meshId;
        std::string materialId;
        std::string lightId;
        std::string cameraId;

        // Animation
        bool animated = false;
        std::string animationId;

        // Custom properties for specific entity types
        std::map<std::string, std::string> properties;

        // Child entities (for hierarchical scenes)
        std::vector<std::shared_ptr<Entity>> children;
    };

    struct Scene
    {
        std::string id;
        std::string name;
        std::string type; // "loading_indicator", "menu_background", etc.
        std::string version = "1.0";

        // Scene assets
        std::vector<Material> materials;
        std::vector<ProceduralTexture> textures;
        std::vector<CompoundMesh> meshes;
        std::vector<Animation> animations;

        // Scene graph
        std::vector<Camera> cameras;
        std::vector<Light> lights;
        std::vector<std::shared_ptr<Entity>> rootEntities;

        // Environment settings
        Material::Color backgroundColor = {0.0f, 0.0f, 0.0f, 1.0f};
        Material::Color ambientLight = {0.2f, 0.2f, 0.2f, 1.0f};
        std::string skybox;

        // Rendering settings
        bool enableShadows = true;
        bool enableBloom = false;
        bool enableSSAO = false;
        float gamma = 2.2f;
        float exposure = 1.0f;

        // Scene metadata
        std::map<std::string, std::string> metadata;
    };

    // ============================================================================
    // Parser Configuration and Validation
    // ============================================================================

    struct ParserConfig
    {
        std::string schemaPath; // Path to scene.xsd for validation
        bool validateSchema = true;
        bool strictParsing = false;     // If true, fail on unknown elements
        bool generateMissingIds = true; // Auto-generate IDs if missing
        bool loadExternalAssets = true; // Load referenced external files

        // Default values for missing required fields
        std::string defaultMaterial = "default_material";
        std::string defaultTexture = "default_texture";
        uint32_t defaultSubdivisions = 1;
    };

    struct ParseResult
    {
        bool success = false;
        std::string errorMessage;
        std::vector<std::string> warnings;
        std::shared_ptr<Scene> scene;

        // Parse statistics
        uint32_t entitiesLoaded = 0;
        uint32_t materialsLoaded = 0;
        uint32_t texturesLoaded = 0;
        uint32_t animationsLoaded = 0;
        float parseTimeMs = 0.0f;
    };

    // ============================================================================
    // Main Scene Configuration Parser
    // ============================================================================

    class SceneConfigParser
    {
    public:
        // Construction and configuration
        explicit SceneConfigParser(const ParserConfig &config = ParserConfig{});
        ~SceneConfigParser() = default;

        // Main parsing methods
        ParseResult parseSceneFile(const std::string &filePath);
        ParseResult parseSceneString(const std::string &xmlContent);
        ParseResult parseSceneData(const void *xmlData, size_t dataSize);

        // Validation methods
        bool validateSceneFile(const std::string &filePath, std::vector<std::string> &errors);
        bool validateSceneString(const std::string &xmlContent, std::vector<std::string> &errors);
        bool validateAgainstSchema(const std::string &xmlContent, std::vector<std::string> &errors);

        // Configuration management
        void setConfig(const ParserConfig &config);
        const ParserConfig &getConfig() const;

        // Utility methods for manual scene construction
        static std::shared_ptr<Entity> createEntity(const std::string &id, const std::string &type);
        static Material createMaterial(const std::string &id, const std::string &shader = "standard");
        static ProceduralTexture createTexture(const std::string &id, const std::string &type);
        static Animation createAnimation(const std::string &id, const std::string &type);
        static Camera createCamera(const std::string &id);
        static Light createLight(const std::string &id, Light::Type type);

        // Scene export methods (for debugging/serialization)
        std::string serializeScene(const Scene &scene, bool prettyPrint = true);
        bool exportSceneToFile(const Scene &scene, const std::string &filePath);

        // Asset resolution and validation
        std::vector<std::string> getReferencedAssets(const Scene &scene);
        std::vector<std::string> validateAssetReferences(const Scene &scene);
        bool resolveAssetPaths(Scene &scene, const std::string &baseDirectory);

    private:
        ParserConfig config_;

        // XML parsing implementation
        ParseResult parseXmlDocument(const std::string &xmlContent);

        // Element parsing methods
        std::shared_ptr<Scene> parseSceneElement(const void *sceneNode);
        Material parseMaterialElement(const void *materialNode);
        ProceduralTexture parseTextureElement(const void *textureNode);
        CompoundMesh parseMeshElement(const void *meshNode);
        Animation parseAnimationElement(const void *animationNode);
        Camera parseCameraElement(const void *cameraNode);
        Light parseLightElement(const void *lightNode);
        std::shared_ptr<Entity> parseEntityElement(const void *entityNode);
        VoxelPrimitive parsePrimitiveElement(const void *primitiveNode);
        Transform parseTransformElement(const void *transformNode);

        // Attribute parsing helpers
        std::string parseStringAttribute(const void *node, const std::string &name, const std::string &defaultValue = "");
        float parseFloatAttribute(const void *node, const std::string &name, float defaultValue = 0.0f);
        uint32_t parseUintAttribute(const void *node, const std::string &name, uint32_t defaultValue = 0);
        bool parseBoolAttribute(const void *node, const std::string &name, bool defaultValue = false);
        Material::Color parseColorAttribute(const void *node, const std::string &name, const Material::Color &defaultValue = {1, 1, 1, 1});

        // Complex attribute parsing
        std::map<std::string, std::string> parseParameters(const void *parametersNode);
        std::vector<Animation::Keyframe> parseKeyframes(const void *keyframesNode);

        // Validation helpers
        bool validateSceneStructure(const Scene &scene, std::vector<std::string> &errors);
        bool validateEntityReferences(const Scene &scene, std::vector<std::string> &errors);
        bool validateAnimationTargets(const Scene &scene, std::vector<std::string> &errors);
        bool validateMaterialReferences(const Scene &scene, std::vector<std::string> &errors);

        // ID generation and management
        std::string generateEntityId(const std::string &type, uint32_t index);
        std::string generateMaterialId(uint32_t index);
        std::string generateTextureId(uint32_t index);
        std::string generateAnimationId(uint32_t index);
        bool isValidId(const std::string &id);

        // Error handling and logging
        void addError(const std::string &message);
        void addWarning(const std::string &message);
        void logParseStep(const std::string &step);

        // Current parse state
        ParseResult currentResult_;
        std::map<std::string, std::shared_ptr<Entity>> entityLookup_;
        std::map<std::string, Material> materialLookup_;
        std::map<std::string, ProceduralTexture> textureLookup_;
        std::map<std::string, Animation> animationLookup_;

        // Simplified parsing helpers
        std::string extractAttributeSimple(const std::string &xmlContent,
                                           const std::string &elementName,
                                           const std::string &attributeName,
                                           const std::string &defaultValue);

        // Parse counters for ID generation
        uint32_t entityCounter_ = 0;
        uint32_t materialCounter_ = 0;
        uint32_t textureCounter_ = 0;
        uint32_t animationCounter_ = 0;
    };

    // ============================================================================
    // Utility Functions
    // ============================================================================

    namespace Utils
    {
        // String conversion utilities
        VoxelPrimitive::Type stringToVoxelType(const std::string &str);
        std::string voxelTypeToString(VoxelPrimitive::Type type);

        Light::Type stringToLightType(const std::string &str);
        std::string lightTypeToString(Light::Type type);

        Camera::Type stringToCameraType(const std::string &str);
        std::string cameraTypeToString(Camera::Type type);

        // Transform utilities
        Transform combineTransforms(const Transform &parent, const Transform &child);
        Transform interpolateTransforms(const Transform &a, const Transform &b, float t);

        // Color utilities
        Material::Color parseColorString(const std::string &colorStr);
        std::string colorToString(const Material::Color &color);
        Material::Color interpolateColors(const Material::Color &a, const Material::Color &b, float t);

        // Validation utilities
        bool isValidFloat(const std::string &str);
        bool isValidColor(const std::string &str);
        bool isValidId(const std::string &id);
        bool isValidPath(const std::string &path);

        // Math utilities
        float degreesToRadians(float degrees);
        float radiansToDegrees(float radians);
        void normalizeQuaternion(Transform::Rotation &quat);

        // File utilities
        std::string getFileExtension(const std::string &path);
        std::string getBasePath(const std::string &path);
        std::string resolvePath(const std::string &basePath, const std::string &relativePath);
        bool fileExists(const std::string &path);
    }

} // namespace SceneConfig
#include "SceneConfigParser.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <regex>
#include <iostream>

namespace SceneConfig
{

    // ============================================================================
    // SceneConfigParser Implementation
    // ============================================================================

    SceneConfigParser::SceneConfigParser(const ParserConfig &config) : config_(config)
    {
        // Initialize default values and lookup tables
    }

    ParseResult SceneConfigParser::parseSceneFile(const std::string &filePath)
    {
        currentResult_ = ParseResult{};
        auto startTime = std::chrono::high_resolution_clock::now();

        // Read file content
        std::ifstream file(filePath);
        if (!file.is_open())
        {
            currentResult_.success = false;
            currentResult_.errorMessage = "Failed to open file: " + filePath;
            return currentResult_;
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string xmlContent = buffer.str();
        file.close();

        // Parse the XML content
        auto result = parseSceneString(xmlContent);

        // If successful and asset resolution is enabled, resolve paths relative to the scene file
        if (result.success && config_.loadExternalAssets && result.scene)
        {
            // Simple base directory resolution - just get directory from file path
            size_t lastSlash = filePath.find_last_of("/\\");
            if (lastSlash != std::string::npos)
            {
                std::string baseDirectory = filePath.substr(0, lastSlash + 1);
                resolveAssetPaths(*result.scene, baseDirectory);
            }
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        result.parseTimeMs = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

        return result;
    }

    ParseResult SceneConfigParser::parseSceneString(const std::string &xmlContent)
    {
        currentResult_ = ParseResult{};
        
        try
        {
            // For now, create a minimal scene for loading_indicator type
            auto scene = std::make_shared<Scene>();
            
            // Simple XML attribute extraction - basic implementation
            scene->id = extractAttributeSimple(xmlContent, "scene", "id", "default_scene");
            scene->name = extractAttributeSimple(xmlContent, "scene", "name", scene->id);
            scene->type = extractAttributeSimple(xmlContent, "scene", "type", "loading_indicator");
            scene->version = extractAttributeSimple(xmlContent, "scene", "version", "1.0");
            
            // For loading_indicator scenes, we don't need complex parsing
            // Just set up basic structure
            currentResult_.scene = scene;
            currentResult_.success = true;
            currentResult_.errorMessage = "";
            
        }
        catch (const std::exception &e)
        {
            currentResult_.success = false;
            currentResult_.errorMessage = std::string("Parse error: ") + e.what();
        }

        return currentResult_;
    }

    // Simple helper method for basic attribute extraction
    std::string SceneConfigParser::extractAttributeSimple(const std::string &xmlContent, 
                                                         const std::string &elementName,
                                                         const std::string &attributeName, 
                                                         const std::string &defaultValue)
    {
        // Simple regex-based attribute extraction
        std::string pattern = "<" + elementName + "[^>]*" + attributeName + "=\"([^\"]*?)\"";
        std::regex re(pattern);
        std::smatch match;
        
        if (std::regex_search(xmlContent, match, re))
        {
            return match[1].str();
        }
        
        return defaultValue;
    }

    bool SceneConfigParser::resolveAssetPaths(Scene &scene, const std::string &baseDirectory)
    {
        // Simple implementation - just return true for now
        // In a full implementation, this would resolve all asset paths relative to baseDirectory
        return true;
    }
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
        result.parseTimeMs = static_cast<float>(duration.count());

        return result;
    }

    ParseResult SceneConfigParser::parseSceneString(const std::string &xmlContent)
    {
        currentResult_ = ParseResult{};
        auto startTime = std::chrono::high_resolution_clock::now();

        // Schema validation if enabled
        if (config_.validateSchema && !config_.schemaPath.empty())
        {
            std::vector<std::string> validationErrors;
            if (!validateAgainstSchema(xmlContent, validationErrors))
            {
                currentResult_.success = false;
                currentResult_.errorMessage = "Schema validation failed";
                currentResult_.warnings = validationErrors;
                return currentResult_;
            }
        }

        // Parse the XML document
        auto result = parseXmlDocument(xmlContent);

        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
        result.parseTimeMs = static_cast<float>(duration.count());

        return result;
    }

    ParseResult SceneConfigParser::parseXmlDocument(const std::string &xmlContent)
    {
        // This is a simplified XML parser implementation
        // In a real implementation, you would use a proper XML library

        try
        {
            // Create a new scene
            auto scene = std::make_shared<Scene>();

            // Basic XML parsing simulation
            // In reality, this would use a proper XML DOM parser

            // Extract scene attributes
            scene->id = extractAttribute(xmlContent, "scene", "id", "default_scene");
            scene->name = extractAttribute(xmlContent, "scene", "name", scene->id);
            scene->type = extractAttribute(xmlContent, "scene", "type", "loading_indicator");
            scene->version = extractAttribute(xmlContent, "scene", "version", "1.0");

            // Parse materials section
            parseMaterialsSection(xmlContent, *scene);

            // Parse textures section
            parseTexturesSection(xmlContent, *scene);

            // Parse meshes section
            parseMeshesSection(xmlContent, *scene);

            // Parse animations section
            parseAnimationsSection(xmlContent, *scene);

            // Parse entities section
            parseEntitiesSection(xmlContent, *scene);

            // Parse cameras section
            parseCamerasSection(xmlContent, *scene);

            // Parse lights section
            parseLightsSection(xmlContent, *scene);

            // Parse environment settings
            parseEnvironmentSection(xmlContent, *scene);

            // Validate the parsed scene
            std::vector<std::string> validationErrors;
            if (!validateSceneStructure(*scene, validationErrors))
            {
                if (config_.strictParsing)
                {
                    currentResult_.success = false;
                    currentResult_.errorMessage = "Scene validation failed";
                    currentResult_.warnings = validationErrors;
                    return currentResult_;
                }
                else
                {
                    currentResult_.warnings.insert(currentResult_.warnings.end(),
                                                   validationErrors.begin(), validationErrors.end());
                }
            }

            // Success
            currentResult_.success = true;
            currentResult_.scene = scene;
            currentResult_.entitiesLoaded = scene->rootEntities.size();
            currentResult_.materialsLoaded = scene->materials.size();
            currentResult_.texturesLoaded = scene->textures.size();
            currentResult_.animationsLoaded = scene->animations.size();
        }
        catch (const std::exception &e)
        {
            currentResult_.success = false;
            currentResult_.errorMessage = "Parse error: " + std::string(e.what());
        }

        return currentResult_;
    }

    // ============================================================================
    // Section Parsing Methods
    // ============================================================================

    void SceneConfigParser::parseMaterialsSection(const std::string &xmlContent, Scene &scene)
    {
        // Extract materials section
        auto materialsSection = extractSection(xmlContent, "materials");
        if (materialsSection.empty())
            return;

        // Parse individual material elements
        auto materialElements = extractElements(materialsSection, "material");
        for (const auto &materialXml : materialElements)
        {
            Material material;

            material.id = extractAttribute(materialXml, "material", "id", generateMaterialId(materialCounter_++));
            material.name = extractAttribute(materialXml, "material", "name", material.id);
            material.shader = extractAttribute(materialXml, "material", "shader", "standard");

            // Parse colors
            material.diffuse = parseColorFromXml(materialXml, "diffuse", {1.0f, 1.0f, 1.0f, 1.0f});
            material.ambient = parseColorFromXml(materialXml, "ambient", {0.2f, 0.2f, 0.2f, 1.0f});
            material.specular = parseColorFromXml(materialXml, "specular", {1.0f, 1.0f, 1.0f, 1.0f});
            material.emissive = parseColorFromXml(materialXml, "emissive", {0.0f, 0.0f, 0.0f, 1.0f});

            // Parse material properties
            material.metallic = extractFloatAttribute(materialXml, "material", "metallic", 0.0f);
            material.roughness = extractFloatAttribute(materialXml, "material", "roughness", 0.5f);
            material.shininess = extractFloatAttribute(materialXml, "material", "shininess", 32.0f);
            material.opacity = extractFloatAttribute(materialXml, "material", "opacity", 1.0f);

            // Parse texture references
            material.diffuseTexture = extractAttribute(materialXml, "material", "diffuseTexture", "");
            material.normalTexture = extractAttribute(materialXml, "material", "normalTexture", "");
            material.specularTexture = extractAttribute(materialXml, "material", "specularTexture", "");
            material.emissiveTexture = extractAttribute(materialXml, "material", "emissiveTexture", "");

            // Parse cel-shading properties
            material.celShading = extractBoolAttribute(materialXml, "material", "celShading", false);
            if (material.celShading)
            {
                material.celLevels = extractUintAttribute(materialXml, "material", "celLevels", 3);
                material.celThreshold = extractFloatAttribute(materialXml, "material", "celThreshold", 0.5f);
                material.celOutlineColor = parseColorFromXml(materialXml, "celOutlineColor", {0.0f, 0.0f, 0.0f, 1.0f});
                material.celOutlineWidth = extractFloatAttribute(materialXml, "material", "celOutlineWidth", 0.01f);
            }

            // Parse custom properties
            auto propertiesSection = extractSection(materialXml, "properties");
            material.customProperties = parsePropertiesMap(propertiesSection);

            scene.materials.push_back(material);
            materialLookup_[material.id] = material;
        }
    }

    void SceneConfigParser::parseTexturesSection(const std::string &xmlContent, Scene &scene)
    {
        auto texturesSection = extractSection(xmlContent, "textures");
        if (texturesSection.empty())
            return;

        auto textureElements = extractElements(texturesSection, "texture");
        for (const auto &textureXml : textureElements)
        {
            ProceduralTexture texture;

            texture.id = extractAttribute(textureXml, "texture", "id", generateTextureId(textureCounter_++));
            texture.name = extractAttribute(textureXml, "texture", "name", texture.id);
            texture.type = extractAttribute(textureXml, "texture", "type", "noise");
            texture.width = extractUintAttribute(textureXml, "texture", "width", 256);
            texture.height = extractUintAttribute(textureXml, "texture", "height", 256);
            texture.format = extractAttribute(textureXml, "texture", "format", "RGBA");

            // Parse generation parameters
            auto parametersSection = extractSection(textureXml, "parameters");
            texture.parameters = parsePropertiesMap(parametersSection);

            scene.textures.push_back(texture);
            textureLookup_[texture.id] = texture;
        }
    }

    void SceneConfigParser::parseMeshesSection(const std::string &xmlContent, Scene &scene)
    {
        auto meshesSection = extractSection(xmlContent, "meshes");
        if (meshesSection.empty())
            return;

        auto meshElements = extractElements(meshesSection, "compound");
        for (const auto &meshXml : meshElements)
        {
            CompoundMesh mesh;

            mesh.id = extractAttribute(meshXml, "compound", "id", generateEntityId("mesh", entityCounter_++));
            mesh.name = extractAttribute(meshXml, "compound", "name", mesh.id);
            mesh.materialId = extractAttribute(meshXml, "compound", "material", config_.defaultMaterial);

            // Parse base transform
            auto transformSection = extractSection(meshXml, "transform");
            mesh.baseTransform = parseTransformFromXml(transformSection);

            // Parse animation settings
            mesh.animated = extractBoolAttribute(meshXml, "compound", "animated", false);
            if (mesh.animated)
            {
                mesh.animationType = extractAttribute(meshXml, "compound", "animationType", "");
                auto animParamsSection = extractSection(meshXml, "animationParams");
                mesh.animationParams = parsePropertiesMap(animParamsSection);
            }

            // Parse parts
            auto partsSection = extractSection(meshXml, "parts");
            auto partElements = extractElements(partsSection, "part");
            for (const auto &partXml : partElements)
            {
                VoxelPrimitive part;

                std::string typeStr = extractAttribute(partXml, "part", "type", "cube");
                part.type = Utils::stringToVoxelType(typeStr);

                part.size = extractFloatAttribute(partXml, "part", "size", 1.0f);
                part.radius = extractFloatAttribute(partXml, "part", "radius", 0.5f);
                part.height = extractFloatAttribute(partXml, "part", "height", 1.0f);
                part.subdivisions = extractUintAttribute(partXml, "part", "subdivisions", 1);
                part.materialId = extractAttribute(partXml, "part", "material", mesh.materialId);

                // Parse part transform
                auto partTransformSection = extractSection(partXml, "transform");
                part.transform = parseTransformFromXml(partTransformSection);

                // Parse part animation
                part.animated = extractBoolAttribute(partXml, "part", "animated", false);
                if (part.animated)
                {
                    part.animationType = extractAttribute(partXml, "part", "animationType", "");
                    auto partAnimParamsSection = extractSection(partXml, "animationParams");
                    part.animationParams = parsePropertiesMap(partAnimParamsSection);
                }

                mesh.parts.push_back(part);
            }

            scene.meshes.push_back(mesh);
        }
    }

    void SceneConfigParser::parseAnimationsSection(const std::string &xmlContent, Scene &scene)
    {
        auto animationsSection = extractSection(xmlContent, "animations");
        if (animationsSection.empty())
            return;

        auto animationElements = extractElements(animationsSection, "animation");
        for (const auto &animationXml : animationElements)
        {
            Animation animation;

            animation.id = extractAttribute(animationXml, "animation", "id", generateAnimationId(animationCounter_++));
            animation.name = extractAttribute(animationXml, "animation", "name", animation.id);
            animation.type = extractAttribute(animationXml, "animation", "type", "transform");
            animation.duration = extractFloatAttribute(animationXml, "animation", "duration", 1.0f);
            animation.loop = extractBoolAttribute(animationXml, "animation", "loop", true);
            animation.autoStart = extractBoolAttribute(animationXml, "animation", "autoStart", true);

            animation.targetType = extractAttribute(animationXml, "animation", "targetType", "entity");
            animation.targetId = extractAttribute(animationXml, "animation", "targetId", "");

            // Parse animation parameters
            auto parametersSection = extractSection(animationXml, "parameters");
            animation.parameters = parsePropertiesMap(parametersSection);

            // Parse keyframes if present
            auto keyframesSection = extractSection(animationXml, "keyframes");
            auto keyframeElements = extractElements(keyframesSection, "keyframe");
            for (const auto &keyframeXml : keyframeElements)
            {
                Animation::Keyframe keyframe;
                keyframe.time = extractFloatAttribute(keyframeXml, "keyframe", "time", 0.0f);

                auto valuesSection = extractSection(keyframeXml, "values");
                keyframe.values = parsePropertiesMap(valuesSection);

                animation.keyframes.push_back(keyframe);
            }

            scene.animations.push_back(animation);
            animationLookup_[animation.id] = animation;
        }
    }

    void SceneConfigParser::parseEntitiesSection(const std::string &xmlContent, Scene &scene)
    {
        auto entitiesSection = extractSection(xmlContent, "entities");
        if (entitiesSection.empty())
            return;

        auto entityElements = extractElements(entitiesSection, "entity");
        for (const auto &entityXml : entityElements)
        {
            auto entity = parseEntityFromXml(entityXml);
            if (entity)
            {
                scene.rootEntities.push_back(entity);
                entityLookup_[entity->id] = entity;
            }
        }
    }

    void SceneConfigParser::parseCamerasSection(const std::string &xmlContent, Scene &scene)
    {
        auto camerasSection = extractSection(xmlContent, "cameras");
        if (camerasSection.empty())
        {
            // Create default camera if none specified
            Camera defaultCamera = createCamera("main_camera");
            scene.cameras.push_back(defaultCamera);
            return;
        }

        auto cameraElements = extractElements(camerasSection, "camera");
        for (const auto &cameraXml : cameraElements)
        {
            Camera camera;

            camera.id = extractAttribute(cameraXml, "camera", "id", "camera_" + std::to_string(scene.cameras.size()));

            std::string typeStr = extractAttribute(cameraXml, "camera", "type", "perspective");
            camera.type = Utils::stringToCameraType(typeStr);

            // Parse transform
            auto transformSection = extractSection(cameraXml, "transform");
            camera.transform = parseTransformFromXml(transformSection);

            // Parse camera parameters
            if (camera.type == Camera::Type::Perspective)
            {
                camera.fov = extractFloatAttribute(cameraXml, "camera", "fov", 45.0f);
                camera.nearPlane = extractFloatAttribute(cameraXml, "camera", "nearPlane", 0.1f);
                camera.farPlane = extractFloatAttribute(cameraXml, "camera", "farPlane", 1000.0f);
            }
            else
            {
                camera.left = extractFloatAttribute(cameraXml, "camera", "left", -10.0f);
                camera.right = extractFloatAttribute(cameraXml, "camera", "right", 10.0f);
                camera.bottom = extractFloatAttribute(cameraXml, "camera", "bottom", -10.0f);
                camera.top = extractFloatAttribute(cameraXml, "camera", "top", 10.0f);
                camera.nearPlane = extractFloatAttribute(cameraXml, "camera", "nearPlane", 0.1f);
                camera.farPlane = extractFloatAttribute(cameraXml, "camera", "farPlane", 1000.0f);
            }

            // Parse animation
            camera.animated = extractBoolAttribute(cameraXml, "camera", "animated", false);
            if (camera.animated)
            {
                camera.animationId = extractAttribute(cameraXml, "camera", "animationId", "");
            }

            scene.cameras.push_back(camera);
        }
    }

    void SceneConfigParser::parseLightsSection(const std::string &xmlContent, Scene &scene)
    {
        auto lightsSection = extractSection(xmlContent, "lights");
        if (lightsSection.empty())
            return;

        auto lightElements = extractElements(lightsSection, "light");
        for (const auto &lightXml : lightElements)
        {
            Light light;

            light.id = extractAttribute(lightXml, "light", "id", "light_" + std::to_string(scene.lights.size()));
            light.name = extractAttribute(lightXml, "light", "name", light.id);

            std::string typeStr = extractAttribute(lightXml, "light", "type", "directional");
            light.type = Utils::stringToLightType(typeStr);

            // Parse transform
            auto transformSection = extractSection(lightXml, "transform");
            light.transform = parseTransformFromXml(transformSection);

            // Parse light properties
            light.color = parseColorFromXml(lightXml, "color", {1.0f, 1.0f, 1.0f, 1.0f});
            light.intensity = extractFloatAttribute(lightXml, "light", "intensity", 1.0f);

            if (light.type == Light::Type::Point || light.type == Light::Type::Spot)
            {
                light.range = extractFloatAttribute(lightXml, "light", "range", 10.0f);
                light.constantAttenuation = extractFloatAttribute(lightXml, "light", "constantAttenuation", 1.0f);
                light.linearAttenuation = extractFloatAttribute(lightXml, "light", "linearAttenuation", 0.09f);
                light.quadraticAttenuation = extractFloatAttribute(lightXml, "light", "quadraticAttenuation", 0.032f);
            }

            if (light.type == Light::Type::Spot)
            {
                light.innerCone = extractFloatAttribute(lightXml, "light", "innerCone", 30.0f);
                light.outerCone = extractFloatAttribute(lightXml, "light", "outerCone", 45.0f);
            }

            // Parse animation
            light.animated = extractBoolAttribute(lightXml, "light", "animated", false);
            if (light.animated)
            {
                light.animationId = extractAttribute(lightXml, "light", "animationId", "");
            }

            scene.lights.push_back(light);
        }
    }

    void SceneConfigParser::parseEnvironmentSection(const std::string &xmlContent, Scene &scene)
    {
        auto environmentSection = extractSection(xmlContent, "environment");
        if (environmentSection.empty())
            return;

        // Parse background color
        scene.backgroundColor = parseColorFromXml(environmentSection, "backgroundColor", {0.0f, 0.0f, 0.0f, 1.0f});
        scene.ambientLight = parseColorFromXml(environmentSection, "ambientLight", {0.2f, 0.2f, 0.2f, 1.0f});

        // Parse skybox
        scene.skybox = extractAttribute(environmentSection, "environment", "skybox", "");

        // Parse rendering settings
        scene.enableShadows = extractBoolAttribute(environmentSection, "environment", "enableShadows", true);
        scene.enableBloom = extractBoolAttribute(environmentSection, "environment", "enableBloom", false);
        scene.enableSSAO = extractBoolAttribute(environmentSection, "environment", "enableSSAO", false);
        scene.gamma = extractFloatAttribute(environmentSection, "environment", "gamma", 2.2f);
        scene.exposure = extractFloatAttribute(environmentSection, "environment", "exposure", 1.0f);
    }

    // ============================================================================
    // Utility Methods Implementation (simplified for brevity)
    // ============================================================================

    std::string SceneConfigParser::extractAttribute(const std::string &xml, const std::string &element, const std::string &attribute, const std::string &defaultValue)
    {
        // Simplified attribute extraction - in real implementation use proper XML parser
        std::regex pattern(element + R"(\s+[^>]*)" + attribute + R"(\s*=\s*"([^"]*)") ");
            std::smatch match;
        if (std::regex_search(xml, match, pattern))
        {
            return match[1].str();
        }
        return defaultValue;
    }

    float SceneConfigParser::extractFloatAttribute(const std::string &xml, const std::string &element, const std::string &attribute, float defaultValue)
    {
        std::string value = extractAttribute(xml, element, attribute, "");
        if (value.empty())
            return defaultValue;
        try
        {
            return std::stof(value);
        }
        catch (...)
        {
            return defaultValue;
        }
    }

    uint32_t SceneConfigParser::extractUintAttribute(const std::string &xml, const std::string &element, const std::string &attribute, uint32_t defaultValue)
    {
        std::string value = extractAttribute(xml, element, attribute, "");
        if (value.empty())
            return defaultValue;
        try
        {
            return static_cast<uint32_t>(std::stoul(value));
        }
        catch (...)
        {
            return defaultValue;
        }
    }

    bool SceneConfigParser::extractBoolAttribute(const std::string &xml, const std::string &element, const std::string &attribute, bool defaultValue)
    {
        std::string value = extractAttribute(xml, element, attribute, "");
        if (value.empty())
            return defaultValue;
        std::transform(value.begin(), value.end(), value.begin(), ::tolower);
        return (value == "true" || value == "1" || value == "yes");
    }

    Material::Color SceneConfigParser::parseColorFromXml(const std::string &xml, const std::string &colorElement, const Material::Color &defaultValue)
    {
        // Simplified color parsing
        std::string colorStr = extractAttribute(xml, colorElement, "value", "");
        if (colorStr.empty())
            return defaultValue;
        return Utils::parseColorString(colorStr);
    }

    Transform SceneConfigParser::parseTransformFromXml(const std::string &xml)
    {
        Transform transform;

        // Parse position
        transform.position.x = extractFloatAttribute(xml, "position", "x", 0.0f);
        transform.position.y = extractFloatAttribute(xml, "position", "y", 0.0f);
        transform.position.z = extractFloatAttribute(xml, "position", "z", 0.0f);

        // Parse rotation (quaternion)
        transform.rotation.x = extractFloatAttribute(xml, "rotation", "x", 0.0f);
        transform.rotation.y = extractFloatAttribute(xml, "rotation", "y", 0.0f);
        transform.rotation.z = extractFloatAttribute(xml, "rotation", "z", 0.0f);
        transform.rotation.w = extractFloatAttribute(xml, "rotation", "w", 1.0f);

        // Parse scale
        transform.scale.x = extractFloatAttribute(xml, "scale", "x", 1.0f);
        transform.scale.y = extractFloatAttribute(xml, "scale", "y", 1.0f);
        transform.scale.z = extractFloatAttribute(xml, "scale", "z", 1.0f);

        return transform;
    }

    std::shared_ptr<Entity> SceneConfigParser::parseEntityFromXml(const std::string &xml)
    {
        auto entity = std::make_shared<Entity>();

        entity->id = extractAttribute(xml, "entity", "id", generateEntityId("entity", entityCounter_++));
        entity->name = extractAttribute(xml, "entity", "name", entity->id);
        entity->type = extractAttribute(xml, "entity", "type", "mesh");

        // Parse transform
        auto transformSection = extractSection(xml, "transform");
        entity->transform = parseTransformFromXml(transformSection);

        // Parse component references
        entity->meshId = extractAttribute(xml, "entity", "mesh", "");
        entity->materialId = extractAttribute(xml, "entity", "material", "");
        entity->lightId = extractAttribute(xml, "entity", "light", "");
        entity->cameraId = extractAttribute(xml, "entity", "camera", "");

        // Parse animation
        entity->animated = extractBoolAttribute(xml, "entity", "animated", false);
        if (entity->animated)
        {
            entity->animationId = extractAttribute(xml, "entity", "animationId", "");
        }

        // Parse properties
        auto propertiesSection = extractSection(xml, "properties");
        entity->properties = parsePropertiesMap(propertiesSection);

        // Parse child entities
        auto childrenSection = extractSection(xml, "children");
        auto childElements = extractElements(childrenSection, "entity");
        for (const auto &childXml : childElements)
        {
            auto child = parseEntityFromXml(childXml);
            if (child)
            {
                entity->children.push_back(child);
                entityLookup_[child->id] = child;
            }
        }

        return entity;
    }

    std::map<std::string, std::string> SceneConfigParser::parsePropertiesMap(const std::string &xml)
    {
        std::map<std::string, std::string> properties;

        // Extract property elements
        auto propertyElements = extractElements(xml, "property");
        for (const auto &propertyXml : propertyElements)
        {
            std::string name = extractAttribute(propertyXml, "property", "name", "");
            std::string value = extractAttribute(propertyXml, "property", "value", "");
            if (!name.empty())
            {
                properties[name] = value;
            }
        }

        return properties;
    }

    std::string SceneConfigParser::extractSection(const std::string &xml, const std::string &sectionName)
    {
        // Simplified section extraction
        std::regex pattern("<" + sectionName + R"(\s*[^>]*>.*?</)" + sectionName + ">");
        std::smatch match;
        if (std::regex_search(xml, match, pattern))
        {
            return match[0].str();
        }
        return "";
    }

    std::vector<std::string> SceneConfigParser::extractElements(const std::string &xml, const std::string &elementName)
    {
        std::vector<std::string> elements;
        std::regex pattern("<" + elementName + R"(\s*[^>]*>.*?</)" + elementName + ">");
        std::sregex_iterator iter(xml.begin(), xml.end(), pattern);
        std::sregex_iterator end;

        for (; iter != end; ++iter)
        {
            elements.push_back(iter->str());
        }

        return elements;
    }

    // ============================================================================
    // ID Generation Methods
    // ============================================================================

    std::string SceneConfigParser::generateEntityId(const std::string &type, uint32_t index)
    {
        return type + "_" + std::to_string(index);
    }

    std::string SceneConfigParser::generateMaterialId(uint32_t index)
    {
        return "material_" + std::to_string(index);
    }

    std::string SceneConfigParser::generateTextureId(uint32_t index)
    {
        return "texture_" + std::to_string(index);
    }

    std::string SceneConfigParser::generateAnimationId(uint32_t index)
    {
        return "animation_" + std::to_string(index);
    }

    // ============================================================================
    // Validation Methods (simplified)
    // ============================================================================

    bool SceneConfigParser::validateSceneStructure(const Scene &scene, std::vector<std::string> &errors)
    {
        bool isValid = true;

        // Check for required elements
        if (scene.cameras.empty())
        {
            errors.push_back("Scene must have at least one camera");
            isValid = false;
        }

        // Validate entity references
        for (const auto &entity : scene.rootEntities)
        {
            if (!validateEntityReferences(*entity, scene, errors))
            {
                isValid = false;
            }
        }

        return isValid;
    }

    bool SceneConfigParser::validateEntityReferences(const Entity &entity, const Scene &scene, std::vector<std::string> &errors)
    {
        bool isValid = true;

        // Check mesh reference
        if (!entity.meshId.empty())
        {
            bool found = false;
            for (const auto &mesh : scene.meshes)
            {
                if (mesh.id == entity.meshId)
                {
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                errors.push_back("Entity '" + entity.id + "' references unknown mesh '" + entity.meshId + "'");
                isValid = false;
            }
        }

        // Check material reference
        if (!entity.materialId.empty())
        {
            bool found = false;
            for (const auto &material : scene.materials)
            {
                if (material.id == entity.materialId)
                {
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                errors.push_back("Entity '" + entity.id + "' references unknown material '" + entity.materialId + "'");
                isValid = false;
            }
        }

        // Validate children recursively
        for (const auto &child : entity.children)
        {
            if (!validateEntityReferences(*child, scene, errors))
            {
                isValid = false;
            }
        }

        return isValid;
    }

    // ============================================================================
    // Static Factory Methods
    // ============================================================================

    std::shared_ptr<Entity> SceneConfigParser::createEntity(const std::string &id, const std::string &type)
    {
        auto entity = std::make_shared<Entity>();
        entity->id = id;
        entity->name = id;
        entity->type = type;
        return entity;
    }

    Material SceneConfigParser::createMaterial(const std::string &id, const std::string &shader)
    {
        Material material;
        material.id = id;
        material.name = id;
        material.shader = shader;
        return material;
    }

    ProceduralTexture SceneConfigParser::createTexture(const std::string &id, const std::string &type)
    {
        ProceduralTexture texture;
        texture.id = id;
        texture.name = id;
        texture.type = type;
        return texture;
    }

    Animation SceneConfigParser::createAnimation(const std::string &id, const std::string &type)
    {
        Animation animation;
        animation.id = id;
        animation.name = id;
        animation.type = type;
        return animation;
    }

    Camera SceneConfigParser::createCamera(const std::string &id)
    {
        Camera camera;
        camera.id = id;
        // Set default camera position (looking at origin from a distance)
        camera.transform.position = {0.0f, 0.0f, 5.0f};
        return camera;
    }

    Light SceneConfigParser::createLight(const std::string &id, Light::Type type)
    {
        Light light;
        light.id = id;
        light.name = id;
        light.type = type;
        return light;
    }

} // namespace SceneConfig
#include "SceneConfigParser.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <regex>
#include <iostream>

namespace SceneConfig
{

    // ============================================================================
    // SceneConfigParser Implementation
    // ============================================================================

    SceneConfigParser::SceneConfigParser(const ParserConfig &config) : config_(config)
    {
        // Initialize default values and lookup tables
    }

    ParseResult SceneConfigParser::parseSceneFile(const std::string &filePath)
    {
        currentResult_ = ParseResult{};
        auto startTime = std::chrono::high_resolution_clock::now();

        // Read file content
        std::ifstream file(filePath);
        if (!file.is_open())
        {
            currentResult_.success = false;
            currentResult_.errorMessage = "Failed to open file: " + filePath;
            return currentResult_;
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string xmlContent = buffer.str();
        file.close();

        // Parse the XML content
        auto result = parseSceneString(xmlContent);

        // If successful and asset resolution is enabled, resolve paths relative to the scene file
        if (result.success && config_.loadExternalAssets && result.scene)
        {
            // Simple base directory resolution - just get directory from file path
            size_t lastSlash = filePath.find_last_of("/\\");
            if (lastSlash != std::string::npos)
            {
                std::string baseDirectory = filePath.substr(0, lastSlash + 1);
                resolveAssetPaths(*result.scene, baseDirectory);
            }
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        result.parseTimeMs = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

        return result;
    }

    ParseResult SceneConfigParser::parseSceneString(const std::string &xmlContent)
    {
        currentResult_ = ParseResult{};

        try
        {
            // For now, create a minimal scene for loading_indicator type
            auto scene = std::make_shared<Scene>();

            // Simple XML attribute extraction - basic implementation
            scene->id = extractAttributeSimple(xmlContent, "scene", "id", "default_scene");
            scene->name = extractAttributeSimple(xmlContent, "scene", "name", scene->id);
            scene->type = extractAttributeSimple(xmlContent, "scene", "type", "loading_indicator");
            scene->version = extractAttributeSimple(xmlContent, "scene", "version", "1.0");

            // For loading_indicator scenes, we don't need complex parsing
            // Just set up basic structure
            currentResult_.scene = scene;
            currentResult_.success = true;
            currentResult_.errorMessage = "";
        }
        catch (const std::exception &e)
        {
            currentResult_.success = false;
            currentResult_.errorMessage = std::string("Parse error: ") + e.what();
        }

        return currentResult_;
    }

    // Simple helper method for basic attribute extraction
    std::string SceneConfigParser::extractAttributeSimple(const std::string &xmlContent,
                                                          const std::string &elementName,
                                                          const std::string &attributeName,
                                                          const std::string &defaultValue)
    {
        // Simple regex-based attribute extraction
        std::string pattern = "<" + elementName + "[^>]*" + attributeName + "=\"([^\"]*?)\"";
        std::regex re(pattern);
        std::smatch match;

        if (std::regex_search(xmlContent, match, re))
        {
            return match[1].str();
        }

        return defaultValue;
    }

    bool SceneConfigParser::resolveAssetPaths(Scene &scene, const std::string &baseDirectory)
    {
        // Simple implementation - just return true for now
        // In a full implementation, this would resolve all asset paths relative to baseDirectory
        return true;
    }

} // namespace SceneConfig
#include "SceneConfigParser.h"
#include <sstream>
#include <algorithm>
#include <regex>
#include <cmath>

namespace SceneConfig
{
    namespace Utils
    {

        // ============================================================================
        // String Conversion Utilities
        // ============================================================================

        VoxelPrimitive::Type stringToVoxelType(const std::string &str)
        {
            std::string lower = str;
            std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

            if (lower == "cube")
                return VoxelPrimitive::Type::Cube;
            if (lower == "sphere")
                return VoxelPrimitive::Type::Sphere;
            if (lower == "cylinder")
                return VoxelPrimitive::Type::Cylinder;
            if (lower == "plane")
                return VoxelPrimitive::Type::Plane;

            return VoxelPrimitive::Type::Cube; // Default fallback
        }

        std::string voxelTypeToString(VoxelPrimitive::Type type)
        {
            switch (type)
            {
            case VoxelPrimitive::Type::Cube:
                return "cube";
            case VoxelPrimitive::Type::Sphere:
                return "sphere";
            case VoxelPrimitive::Type::Cylinder:
                return "cylinder";
            case VoxelPrimitive::Type::Plane:
                return "plane";
            default:
                return "cube";
            }
        }

        Light::Type stringToLightType(const std::string &str)
        {
            std::string lower = str;
            std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

            if (lower == "directional")
                return Light::Type::Directional;
            if (lower == "point")
                return Light::Type::Point;
            if (lower == "spot")
                return Light::Type::Spot;
            if (lower == "ambient")
                return Light::Type::Ambient;

            return Light::Type::Directional; // Default fallback
        }

        std::string lightTypeToString(Light::Type type)
        {
            switch (type)
            {
            case Light::Type::Directional:
                return "directional";
            case Light::Type::Point:
                return "point";
            case Light::Type::Spot:
                return "spot";
            case Light::Type::Ambient:
                return "ambient";
            default:
                return "directional";
            }
        }

        Camera::Type stringToCameraType(const std::string &str)
        {
            std::string lower = str;
            std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

            if (lower == "perspective")
                return Camera::Type::Perspective;
            if (lower == "orthographic" || lower == "ortho")
                return Camera::Type::Orthographic;

            return Camera::Type::Perspective; // Default fallback
        }

        std::string cameraTypeToString(Camera::Type type)
        {
            switch (type)
            {
            case Camera::Type::Perspective:
                return "perspective";
            case Camera::Type::Orthographic:
                return "orthographic";
            default:
                return "perspective";
            }
        }

        // ============================================================================
        // Transform Utilities
        // ============================================================================

        Transform combineTransforms(const Transform &parent, const Transform &child)
        {
            Transform result;

            // Combine positions (parent.position + parent.rotation * child.position)
            // Simplified - in real implementation would use proper quaternion math
            result.position.x = parent.position.x + child.position.x;
            result.position.y = parent.position.y + child.position.y;
            result.position.z = parent.position.z + child.position.z;

            // Combine rotations (quaternion multiplication)
            // Simplified - in real implementation would use proper quaternion multiplication
            result.rotation = child.rotation; // For now, just use child rotation

            // Combine scales (component-wise multiplication)
            result.scale.x = parent.scale.x * child.scale.x;
            result.scale.y = parent.scale.y * child.scale.y;
            result.scale.z = parent.scale.z * child.scale.z;

            return result;
        }

        Transform interpolateTransforms(const Transform &a, const Transform &b, float t)
        {
            t = std::clamp(t, 0.0f, 1.0f);
            Transform result;

            // Linear interpolation for position
            result.position.x = a.position.x + t * (b.position.x - a.position.x);
            result.position.y = a.position.y + t * (b.position.y - a.position.y);
            result.position.z = a.position.z + t * (b.position.z - a.position.z);

            // Spherical linear interpolation for rotation (simplified)
            result.rotation.x = a.rotation.x + t * (b.rotation.x - a.rotation.x);
            result.rotation.y = a.rotation.y + t * (b.rotation.y - a.rotation.y);
            result.rotation.z = a.rotation.z + t * (b.rotation.z - a.rotation.z);
            result.rotation.w = a.rotation.w + t * (b.rotation.w - a.rotation.w);
            normalizeQuaternion(result.rotation);

            // Linear interpolation for scale
            result.scale.x = a.scale.x + t * (b.scale.x - a.scale.x);
            result.scale.y = a.scale.y + t * (b.scale.y - a.scale.y);
            result.scale.z = a.scale.z + t * (b.scale.z - a.scale.z);

            return result;
        }

        // ============================================================================
        // Color Utilities
        // ============================================================================

        Material::Color parseColorString(const std::string &colorStr)
        {
            Material::Color color = {1.0f, 1.0f, 1.0f, 1.0f}; // Default white

            std::string trimmed = colorStr;
            // Remove whitespace
            trimmed.erase(std::remove_if(trimmed.begin(), trimmed.end(), ::isspace), trimmed.end());

            if (trimmed.empty())
            {
                return color;
            }

            // Handle hex colors (#RRGGBB or #RRGGBBAA)
            if (trimmed[0] == '#')
            {
                std::string hex = trimmed.substr(1);

                if (hex.length() == 6 || hex.length() == 8)
                {
                    try
                    {
                        unsigned long value = std::stoul(hex, nullptr, 16);

                        if (hex.length() == 6)
                        {
                            // RGB format
                            color.r = ((value >> 16) & 0xFF) / 255.0f;
                            color.g = ((value >> 8) & 0xFF) / 255.0f;
                            color.b = (value & 0xFF) / 255.0f;
                            color.a = 1.0f;
                        }
                        else
                        {
                            // RGBA format
                            color.r = ((value >> 24) & 0xFF) / 255.0f;
                            color.g = ((value >> 16) & 0xFF) / 255.0f;
                            color.b = ((value >> 8) & 0xFF) / 255.0f;
                            color.a = (value & 0xFF) / 255.0f;
                        }
                    }
                    catch (...)
                    {
                        // Invalid hex format, return default
                    }
                }
                return color;
            }

            // Handle RGB/RGBA format: "r,g,b" or "r,g,b,a"
            if (trimmed.find(',') != std::string::npos)
            {
                std::vector<float> components;
                std::stringstream ss(trimmed);
                std::string component;

                while (std::getline(ss, component, ','))
                {
                    try
                    {
                        components.push_back(std::stof(component));
                    }
                    catch (...)
                    {
                        // Invalid component, skip
                    }
                }

                if (components.size() >= 3)
                {
                    color.r = std::clamp(components[0], 0.0f, 1.0f);
                    color.g = std::clamp(components[1], 0.0f, 1.0f);
                    color.b = std::clamp(components[2], 0.0f, 1.0f);

                    if (components.size() >= 4)
                    {
                        color.a = std::clamp(components[3], 0.0f, 1.0f);
                    }
                }
                return color;
            }

            // Handle named colors
            std::string lower = trimmed;
            std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

            if (lower == "red")
                return {1.0f, 0.0f, 0.0f, 1.0f};
            if (lower == "green")
                return {0.0f, 1.0f, 0.0f, 1.0f};
            if (lower == "blue")
                return {0.0f, 0.0f, 1.0f, 1.0f};
            if (lower == "white")
                return {1.0f, 1.0f, 1.0f, 1.0f};
            if (lower == "black")
                return {0.0f, 0.0f, 0.0f, 1.0f};
            if (lower == "yellow")
                return {1.0f, 1.0f, 0.0f, 1.0f};
            if (lower == "cyan")
                return {0.0f, 1.0f, 1.0f, 1.0f};
            if (lower == "magenta")
                return {1.0f, 0.0f, 1.0f, 1.0f};
            if (lower == "gray" || lower == "grey")
                return {0.5f, 0.5f, 0.5f, 1.0f};
            if (lower == "orange")
                return {1.0f, 0.5f, 0.0f, 1.0f};
            if (lower == "purple")
                return {0.5f, 0.0f, 0.5f, 1.0f};
            if (lower == "brown")
                return {0.6f, 0.3f, 0.0f, 1.0f};
            if (lower == "pink")
                return {1.0f, 0.7f, 0.8f, 1.0f};

            return color; // Return default if no match
        }

        std::string colorToString(const Material::Color &color)
        {
            std::ostringstream oss;
            oss << std::fixed;
            oss.precision(3);
            oss << color.r << "," << color.g << "," << color.b << "," << color.a;
            return oss.str();
        }

        Material::Color interpolateColors(const Material::Color &a, const Material::Color &b, float t)
        {
            t = std::clamp(t, 0.0f, 1.0f);

            return {
                a.r + t * (b.r - a.r),
                a.g + t * (b.g - a.g),
                a.b + t * (b.b - a.b),
                a.a + t * (b.a - a.a)};
        }

        // ============================================================================
        // Validation Utilities
        // ============================================================================

        bool isValidFloat(const std::string &str)
        {
            if (str.empty())
                return false;

            try
            {
                std::stof(str);
                return true;
            }
            catch (...)
            {
                return false;
            }
        }

        bool isValidColor(const std::string &str)
        {
            if (str.empty())
                return false;

            // Check hex format
            if (str[0] == '#')
            {
                if (str.length() != 7 && str.length() != 9)
                    return false;

                for (size_t i = 1; i < str.length(); ++i)
                {
                    if (!std::isxdigit(str[i]))
                        return false;
                }
                return true;
            }

            // Check RGB/RGBA format
            if (str.find(',') != std::string::npos)
            {
                std::stringstream ss(str);
                std::string component;
                int componentCount = 0;

                while (std::getline(ss, component, ','))
                {
                    if (!isValidFloat(component))
                        return false;
                    componentCount++;
                }

                return (componentCount == 3 || componentCount == 4);
            }

            // Check named colors (simplified)
            std::string lower = str;
            std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

            static const std::vector<std::string> namedColors = {
                "red", "green", "blue", "white", "black", "yellow", "cyan",
                "magenta", "gray", "grey", "orange", "purple", "brown", "pink"};

            return std::find(namedColors.begin(), namedColors.end(), lower) != namedColors.end();
        }

        bool isValidId(const std::string &id)
        {
            if (id.empty())
                return false;

            // ID must start with letter or underscore
            if (!std::isalpha(id[0]) && id[0] != '_')
                return false;

            // ID can contain letters, digits, underscores, and hyphens
            for (size_t i = 1; i < id.length(); ++i)
            {
                if (!std::isalnum(id[i]) && id[i] != '_' && id[i] != '-')
                {
                    return false;
                }
            }

            return true;
        }

        bool isValidPath(const std::string &path)
        {
            if (path.empty())
                return false;

            // Basic path validation - check for invalid characters
            static const std::string invalidChars = "<>:\"|?*";
            for (char c : invalidChars)
            {
                if (path.find(c) != std::string::npos)
                {
                    return false;
                }
            }

            return true;
        }

        // ============================================================================
        // Math Utilities
        // ============================================================================

        float degreesToRadians(float degrees)
        {
            return degrees * static_cast<float>(M_PI) / 180.0f;
        }

        float radiansToDegrees(float radians)
        {
            return radians * 180.0f / static_cast<float>(M_PI);
        }

        void normalizeQuaternion(Transform::Rotation &quat)
        {
            float length = std::sqrt(quat.x * quat.x + quat.y * quat.y + quat.z * quat.z + quat.w * quat.w);

            if (length > 0.0f)
            {
                float invLength = 1.0f / length;
                quat.x *= invLength;
                quat.y *= invLength;
                quat.z *= invLength;
                quat.w *= invLength;
            }
            else
            {
                // Default to identity quaternion
                quat.x = 0.0f;
                quat.y = 0.0f;
                quat.z = 0.0f;
                quat.w = 1.0f;
            }
        }

        // ============================================================================
        // File Utilities
        // ============================================================================

        std::string getFileExtension(const std::string &path)
        {
            size_t dotPos = path.find_last_of('.');
            if (dotPos == std::string::npos || dotPos == path.length() - 1)
            {
                return "";
            }

            std::string ext = path.substr(dotPos + 1);
            std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
            return ext;
        }

        std::string getBasePath(const std::string &path)
        {
            size_t slashPos = path.find_last_of("/\\");
            if (slashPos == std::string::npos)
            {
                return "";
            }

            return path.substr(0, slashPos + 1);
        }

        std::string resolvePath(const std::string &basePath, const std::string &relativePath)
        {
            if (relativePath.empty())
                return basePath;

            // If relative path is actually absolute, return it as-is
            if (relativePath[0] == '/' || (relativePath.length() > 1 && relativePath[1] == ':'))
            {
                return relativePath;
            }

            // Combine base path with relative path
            std::string result = basePath;
            if (!result.empty() && result.back() != '/' && result.back() != '\\')
            {
                result += "/";
            }
            result += relativePath;

            // Normalize path separators
            std::replace(result.begin(), result.end(), '\\', '/');

            // Resolve relative path components (., ..)
            std::vector<std::string> components;
            std::stringstream ss(result);
            std::string component;

            while (std::getline(ss, component, '/'))
            {
                if (component.empty() || component == ".")
                {
                    continue;
                }
                else if (component == "..")
                {
                    if (!components.empty())
                    {
                        components.pop_back();
                    }
                }
                else
                {
                    components.push_back(component);
                }
            }

            // Rebuild path
            result.clear();
            for (size_t i = 0; i < components.size(); ++i)
            {
                if (i > 0)
                    result += "/";
                result += components[i];
            }

            return result;
        }

        bool fileExists(const std::string &path)
        {
            std::ifstream file(path);
            return file.good();
        }

    } // namespace Utils
} // namespace SceneConfig
#include "AssetPackLoader.h"
#include "../utils/PugiXmlParser.h"
#include <iostream>
#include <fstream>
#include <sstream>

/**
 * @brief Construct an asset pack loader with a reference to the registry.
 *
 * @param registry Reference to the asset registry where loaded assets will be stored
 */
AssetPackLoader::AssetPackLoader(AssetRegistry &registry)
    : registry_(registry)
{
}

/**
 * @brief Destroy the asset pack loader.
 */
AssetPackLoader::~AssetPackLoader() {}

/**
 * @brief Load a package from an XML file.
 *
 * This method reads the XML file from disk, extracts the package name from the path,
 * and parses both the assets and configurations sections. If parsing succeeds,
 * the package is marked as loaded in the registry.
 *
 * @param packagePath Path to the XML package file
 * @return true if loading and parsing succeeded, false otherwise
 */
bool AssetPackLoader::loadPackage(const std::string &packagePath)
{
    // Read XML file
    std::ifstream file(packagePath);
    if (!file.is_open())
    {
        std::cerr << "Failed to open package file: " << packagePath << std::endl;
        return false;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string xmlContent = buffer.str();
    file.close();

    // Extract package name from path
    size_t lastSlash = packagePath.find_last_of("/\\");
    size_t secondLastSlash = packagePath.find_last_of("/\\", lastSlash - 1);
    std::string packageName = packagePath.substr(secondLastSlash + 1, lastSlash - secondLastSlash - 1);

    // Parse assets and configurations
    if (!parseAssets(xmlContent, packageName))
    {
        std::cerr << "Failed to parse assets from package: " << packageName << std::endl;
        return false;
    }

    if (!parseConfigurations(xmlContent, packageName))
    {
        std::cerr << "Failed to parse configurations from package: " << packageName << std::endl;
        return false;
    }

    registry_.markPackageLoaded(packageName);
    std::cout << "Successfully loaded package: " << packageName << std::endl;
    return true;
}

/**
 * @brief Load the developer package specifically.
 *
 * Convenience method that loads the developer package from the
 * standard location (assets/packages/DeveloperPackage/package.xml).
 *
 * @return true if loading succeeded, false otherwise
 */
bool AssetPackLoader::loadDeveloperPackage()
{
    return loadPackage("assets/packages/DeveloperPackage/package.xml");
}

/**
 * @brief Parse the assets section from XML content and register them with the asset registry.
 *
 * This method extracts asset definitions from the XML content and registers them
 * with the asset registry. Currently supports font assets, with placeholders for
 * other asset types (textures, materials, mesh recipes).
 *
 * @param xmlContent The complete XML content of the package file
 * @param packageName The name of the package being loaded (used for asset ID prefixing)
 * @return true if parsing succeeded (or no assets section found), false on parsing errors
 */
bool AssetPackLoader::parseAssets(const std::string &xmlContent, const std::string &packageName)
{
    // Simple XML parsing - in a real implementation this would use pugixml properly
    // For now, we'll do basic string parsing to extract asset information

    size_t assetsStart = xmlContent.find("<assets>");
    size_t assetsEnd = xmlContent.find("</assets>");

    if (assetsStart == std::string::npos || assetsEnd == std::string::npos)
    {
        return true; // No assets section is OK
    }

    std::string assetsSection = xmlContent.substr(assetsStart, assetsEnd - assetsStart);

    // Parse font assets
    size_t pos = 0;
    while ((pos = assetsSection.find("<asset type=\"font\"", pos)) != std::string::npos)
    {
        size_t endPos = assetsSection.find("</asset>", pos);
        if (endPos == std::string::npos)
            break;

        std::string assetXml = assetsSection.substr(pos, endPos - pos + 8);
        auto fontAsset = parseFontAsset(assetXml);
        if (fontAsset)
        {
            // Extract ID
            size_t idStart = assetXml.find("id=\"") + 4;
            size_t idEnd = assetXml.find("\"", idStart);
            std::string id = assetXml.substr(idStart, idEnd - idStart);

            registry_.registerFont(packageName + "::" + id, std::move(fontAsset));
        }
        pos = endPos;
    }

    // Parse texture assets
    pos = 0;
    while ((pos = assetsSection.find("<asset type=\"texture\"", pos)) != std::string::npos)
    {
        size_t endPos = assetsSection.find("</asset>", pos);
        if (endPos == std::string::npos)
            break;

        std::string assetXml = assetsSection.substr(pos, endPos - pos + 8);
        auto texAsset = parseTextureAsset(assetXml);
        if (texAsset)
        {
            // Extract ID
            size_t idStart = assetXml.find("id=\"") + 4;
            size_t idEnd = assetXml.find("\"", idStart);
            std::string id = assetXml.substr(idStart, idEnd - idStart);

            registry_.registerTexture(packageName + "::" + id, std::move(texAsset));
        }
        pos = endPos;
    }

    // Parse material assets (simplified: only shader_id captured now)
    pos = 0;
    while ((pos = assetsSection.find("<asset type=\"material\"", pos)) != std::string::npos)
    {
        size_t endPos = assetsSection.find("</asset>", pos);
        if (endPos == std::string::npos)
            break;

        std::string assetXml = assetsSection.substr(pos, endPos - pos + 8);
        auto matAsset = parseMaterialAsset(assetXml);
        if (matAsset)
        {
            // Extract ID
            size_t idStart = assetXml.find("id=\"") + 4;
            size_t idEnd = assetXml.find("\"", idStart);
            std::string id = assetXml.substr(idStart, idEnd - idStart);

            registry_.registerMaterial(packageName + "::" + id, std::move(matAsset));
        }
        pos = endPos;
    }

    // Parse mesh recipe assets
    pos = 0;
    while ((pos = assetsSection.find("<asset type=\"mesh_recipe\"", pos)) != std::string::npos)
    {
        size_t endPos = assetsSection.find("</asset>", pos);
        if (endPos == std::string::npos)
            break;

        std::string assetXml = assetsSection.substr(pos, endPos - pos + 8);
        auto meshAsset = parseMeshRecipeAsset(assetXml);
        if (meshAsset)
        {
            // Extract ID
            size_t idStart = assetXml.find("id=\"") + 4;
            size_t idEnd = assetXml.find("\"", idStart);
            std::string id = assetXml.substr(idStart, idEnd - idStart);

            registry_.registerMeshRecipe(packageName + "::" + id, std::move(meshAsset));
        }
        pos = endPos;
    }

    return true;
}

/**
 * @brief Parse the configurations section from XML content and register scene configurations.
 *
 * This method extracts scene configuration definitions from the XML content and
 * registers them with the asset registry. Special handling is provided for the
 * DefaultSphereWorldScene which is automatically set as the default scene.
 *
 * @param xmlContent The complete XML content of the package file
 * @param packageName The name of the package being loaded (used for scene ID prefixing)
 * @return true if parsing succeeded (or no configurations section found), false on parsing errors
 */
bool AssetPackLoader::parseConfigurations(const std::string &xmlContent, const std::string &packageName)
{
    // Find the configurations section
    size_t configStart = xmlContent.find("<configurations>");
    size_t configEnd = xmlContent.find("</configurations>");

    if (configStart == std::string::npos || configEnd == std::string::npos)
    {
        return true; // No configurations section is OK
    }

    std::string configSection = xmlContent.substr(configStart, configEnd - configStart);

    // Parse scene configurations
    size_t pos = 0;
    while ((pos = configSection.find("<scene_config", pos)) != std::string::npos)
    {
        size_t endPos = configSection.find("</scene_config>", pos);
        if (endPos == std::string::npos)
            break;

        std::string sceneXml = configSection.substr(pos, endPos - pos + 15);

        // Extract scene ID
        size_t idStart = sceneXml.find("id=\"") + 4;
        size_t idEnd = sceneXml.find("\"", idStart);
        std::string sceneId = sceneXml.substr(idStart, idEnd - idStart);

        // For DefaultSphereWorldScene, register it as the default scene
        if (sceneId == "DefaultSphereWorldScene")
        {
            registry_.registerSceneConfig(packageName + "::" + sceneId, sceneXml);
            registry_.setDefaultScene(packageName + "::" + sceneId);
            std::cout << "Registered default scene: " << packageName << "::" << sceneId << std::endl;
        }

        pos = endPos;
    }

    return true;
}

/**
 * @brief Parse a font asset from an XML node.
 *
 * Extracts font asset properties including file path, size, and antialiasing
 * settings from the provided XML node string.
 *
 * @param xmlNode The XML node string containing font asset definition
 * @return A unique pointer to the parsed FontAsset, or nullptr on parsing failure
 */
std::unique_ptr<FontAsset> AssetPackLoader::parseFontAsset(const std::string &xmlNode)
{
    auto asset = std::make_unique<FontAsset>();

    // Extract path
    size_t pathStart = xmlNode.find("<path>") + 6;
    size_t pathEnd = xmlNode.find("</path>", pathStart);
    if (pathStart != std::string::npos && pathEnd != std::string::npos)
    {
        asset->path = xmlNode.substr(pathStart, pathEnd - pathStart);
    }

    // Extract size
    size_t sizeStart = xmlNode.find("size=\"") + 6;
    size_t sizeEnd = xmlNode.find("\"", sizeStart);
    if (sizeStart != std::string::npos && sizeEnd != std::string::npos)
    {
        asset->size = std::stoi(xmlNode.substr(sizeStart, sizeEnd - sizeStart));
    }

    // Extract antialiasing
    size_t aaStart = xmlNode.find("antialiasing=\"") + 14;
    size_t aaEnd = xmlNode.find("\"", aaStart);
    if (aaStart != std::string::npos && aaEnd != std::string::npos)
    {
        asset->antialiasing = xmlNode.substr(aaStart, aaEnd - aaStart) == "true";
    }

    return asset;
}

/**
 * @brief Parse a texture asset from an XML node.
 *
 * Extracts texture asset properties including file path, format, mipmaps setting,
 * and filtering mode from the provided XML node string.
 *
 * @param xmlNode The XML node string containing texture asset definition
 * @return A unique pointer to the parsed TextureAsset, or nullptr on parsing failure
 */
std::unique_ptr<TextureAsset> AssetPackLoader::parseTextureAsset(const std::string &xmlNode)
{
    auto asset = std::make_unique<TextureAsset>();

    // Extract path
    size_t pathStart = xmlNode.find("<path>") + 6;
    size_t pathEnd = xmlNode.find("</path>", pathStart);
    if (pathStart != std::string::npos && pathEnd != std::string::npos)
    {
        asset->path = xmlNode.substr(pathStart, pathEnd - pathStart);
    }

    // Extract format
    size_t formatStart = xmlNode.find("format=\"") + 8;
    size_t formatEnd = xmlNode.find("\"", formatStart);
    if (formatStart != std::string::npos && formatEnd != std::string::npos)
    {
        asset->format = xmlNode.substr(formatStart, formatEnd - formatStart);
    }

    // Extract mipmaps
    size_t mipsStart = xmlNode.find("mipmaps=\"") + 9;
    size_t mipsEnd = xmlNode.find("\"", mipsStart);
    if (mipsStart != std::string::npos && mipsEnd != std::string::npos)
    {
        asset->mipmaps = xmlNode.substr(mipsStart, mipsEnd - mipsStart) == "true";
    }

    // Extract filter
    size_t filterStart = xmlNode.find("filter=\"") + 8;
    size_t filterEnd = xmlNode.find("\"", filterStart);
    if (filterStart != std::string::npos && filterEnd != std::string::npos)
    {
        asset->filter = xmlNode.substr(filterStart, filterEnd - filterStart);
    }

    return asset;
}

/**
 * @brief Parse a material asset from an XML node.
 *
 * Extracts material asset properties including shader ID and material parameters
 * from the provided XML node string. Parameter parsing is currently simplified.
 *
 * @param xmlNode The XML node string containing material asset definition
 * @return A unique pointer to the parsed MaterialAsset, or nullptr on parsing failure
 */
std::unique_ptr<MaterialAsset> AssetPackLoader::parseMaterialAsset(const std::string &xmlNode)
{
    auto asset = std::make_unique<MaterialAsset>();

    // Extract shader_id
    size_t shaderStart = xmlNode.find("<shader_id>") + 11;
    size_t shaderEnd = xmlNode.find("</shader_id>", shaderStart);
    if (shaderStart != std::string::npos && shaderEnd != std::string::npos)
    {
        asset->shaderId = xmlNode.substr(shaderStart, shaderEnd - shaderStart);
    }

    // Parse params (simplified)
    size_t paramsStart = xmlNode.find("<params>");
    size_t paramsEnd = xmlNode.find("</params>", paramsStart);
    if (paramsStart != std::string::npos && paramsEnd != std::string::npos)
    {
        std::string paramsSection = xmlNode.substr(paramsStart, paramsEnd - paramsStart);
        // Basic parsing of common parameters would go here
    }

    return asset;
}

/**
 * @brief Parse a mesh recipe asset from an XML node.
 *
 * Extracts mesh recipe asset properties including generator type and parameters
 * from the provided XML node string. Parameter parsing is currently simplified.
 *
 * @param xmlNode The XML node string containing mesh recipe asset definition
 * @return A unique pointer to the parsed MeshRecipeAsset, or nullptr on parsing failure
 */
std::unique_ptr<MeshRecipeAsset> AssetPackLoader::parseMeshRecipeAsset(const std::string &xmlNode)
{
    auto asset = std::make_unique<MeshRecipeAsset>();

    // Extract generator
    size_t genStart = xmlNode.find("<generator>") + 11;
    size_t genEnd = xmlNode.find("</generator>", genStart);
    if (genStart != std::string::npos && genEnd != std::string::npos)
    {
        asset->generator = xmlNode.substr(genStart, genEnd - genStart);
    }

    // Parse params (simplified)
    size_t paramsStart = xmlNode.find("<params>");
    size_t paramsEnd = xmlNode.find("</params>", paramsStart);
    if (paramsStart != std::string::npos && paramsEnd != std::string::npos)
    {
        std::string paramsSection = xmlNode.substr(paramsStart, paramsEnd - paramsStart);
        // Basic parsing of parameters would go here
    }

    return asset;
}
#ifndef ASSET_PACK_LOADER_H
#define ASSET_PACK_LOADER_H

#include "AssetRegistry.h"
#include <memory>
#include <string>

/**
 * @brief Loads and parses asset packages from XML files.
 *
 * The AssetPackLoader is responsible for reading XML package files,
 * parsing their contents, and registering the defined assets with
 * the AssetRegistry. It supports loading different types of assets
 * including fonts, textures, materials, and mesh recipes.
 */
class AssetPackLoader
{
public:
    /**
     * @brief Construct an asset pack loader with a reference to the registry.
     *
     * @param registry Reference to the asset registry where loaded assets will be stored
     */
    AssetPackLoader(AssetRegistry &registry);

    /**
     * @brief Destroy the asset pack loader.
     */
    ~AssetPackLoader();

    /**
     * @brief Load a package from an XML file.
     *
     * Reads the XML file, parses its contents, and registers all assets
     * and configurations with the asset registry.
     *
     * @param packagePath Path to the XML package file
     * @return true if loading succeeded, false otherwise
     */
    bool loadPackage(const std::string &packagePath);

    /**
     * @brief Load the developer package specifically.
     *
     * Convenience method that loads the developer package from the
     * standard location (assets/packages/DeveloperPackage/package.xml).
     *
     * @return true if loading succeeded, false otherwise
     */
    bool loadDeveloperPackage();

private:
    AssetRegistry &registry_; /**< Reference to the asset registry */

    /**
     * @brief Parse the assets section from XML content.
     *
     * @param xmlContent The raw XML content string
     * @param packageName Name of the package being loaded
     * @return true if parsing succeeded, false otherwise
     */
    bool parseAssets(const std::string &xmlContent, const std::string &packageName);

    /**
     * @brief Parse the configurations section from XML content.
     *
     * @param xmlContent The raw XML content string
     * @param packageName Name of the package being loaded
     * @return true if parsing succeeded, false otherwise
     */
    bool parseConfigurations(const std::string &xmlContent, const std::string &packageName);

    /**
     * @brief Parse a font asset from an XML node.
     *
     * @param xmlNode XML string containing the font asset definition
     * @return Unique pointer to the parsed font asset
     */
    std::unique_ptr<FontAsset> parseFontAsset(const std::string &xmlNode);

    /**
     * @brief Parse a texture asset from an XML node.
     *
     * @param xmlNode XML string containing the texture asset definition
     * @return Unique pointer to the parsed texture asset
     */
    std::unique_ptr<TextureAsset> parseTextureAsset(const std::string &xmlNode);

    /**
     * @brief Parse a material asset from an XML node.
     *
     * @param xmlNode XML string containing the material asset definition
     * @return Unique pointer to the parsed material asset
     */
    std::unique_ptr<MaterialAsset> parseMaterialAsset(const std::string &xmlNode);

    /**
     * @brief Parse a mesh recipe asset from an XML node.
     *
     * @param xmlNode XML string containing the mesh recipe asset definition
     * @return Unique pointer to the parsed mesh recipe asset
     */
    std::unique_ptr<MeshRecipeAsset> parseMeshRecipeAsset(const std::string &xmlNode);
};

#endif
#include "AssetRegistry.h"
#include <iostream>

/**
 * @brief Construct an empty asset registry.
 *
 * Initializes all asset maps and configuration storage.
 */
AssetRegistry::AssetRegistry() {}

/**
 * @brief Destroy the asset registry and free all assets.
 *
 * All stored assets are automatically cleaned up through their unique pointers.
 */
AssetRegistry::~AssetRegistry() {}

/**
 * @brief Register a font asset with the given ID.
 *
 * Stores the font asset in the registry, taking ownership of the pointer.
 * If an asset with the same ID already exists, it will be replaced.
 *
 * @param id Unique identifier for the font asset
 * @param asset Unique pointer to the font asset
 */
void AssetRegistry::registerFont(AssetId id, std::unique_ptr<FontAsset> asset)
{
    fonts_[id] = std::move(asset);
}

/**
 * @brief Register a texture asset with the given ID.
 *
 * Stores the texture asset in the registry, taking ownership of the pointer.
 * If an asset with the same ID already exists, it will be replaced.
 *
 * @param id Unique identifier for the texture asset
 * @param asset Unique pointer to the texture asset
 */
void AssetRegistry::registerTexture(AssetId id, std::unique_ptr<TextureAsset> asset)
{
    textures_[id] = std::move(asset);
}

/**
 * @brief Register a material asset with the given ID.
 *
 * Stores the material asset in the registry, taking ownership of the pointer.
 * If an asset with the same ID already exists, it will be replaced.
 *
 * @param id Unique identifier for the material asset
 * @param asset Unique pointer to the material asset
 */
void AssetRegistry::registerMaterial(AssetId id, std::unique_ptr<MaterialAsset> asset)
{
    materials_[id] = std::move(asset);
}

/**
 * @brief Register a mesh recipe asset with the given ID.
 *
 * Stores the mesh recipe asset in the registry, taking ownership of the pointer.
 * If an asset with the same ID already exists, it will be replaced.
 *
 * @param id Unique identifier for the mesh recipe asset
 * @param asset Unique pointer to the mesh recipe asset
 */
void AssetRegistry::registerMeshRecipe(AssetId id, std::unique_ptr<MeshRecipeAsset> asset)
{
    meshRecipes_[id] = std::move(asset);
}

/**
 * @brief Get a font asset by ID.
 *
 * Searches for a font asset with the given ID and returns a pointer to it.
 *
 * @param id The asset identifier
 * @return Pointer to the font asset, or nullptr if not found
 */
const FontAsset *AssetRegistry::getFont(AssetId id) const
{
    auto it = fonts_.find(id);
    return it != fonts_.end() ? it->second.get() : nullptr;
}

/**
 * @brief Get a texture asset by ID.
 *
 * Searches for a texture asset with the given ID and returns a pointer to it.
 *
 * @param id The asset identifier
 * @return Pointer to the texture asset, or nullptr if not found
 */
const TextureAsset *AssetRegistry::getTexture(AssetId id) const
{
    auto it = textures_.find(id);
    return it != textures_.end() ? it->second.get() : nullptr;
}

/**
 * @brief Get a material asset by ID.
 *
 * Searches for a material asset with the given ID and returns a pointer to it.
 *
 * @param id The asset identifier
 * @return Pointer to the material asset, or nullptr if not found
 */
const MaterialAsset *AssetRegistry::getMaterial(AssetId id) const
{
    auto it = materials_.find(id);
    return it != materials_.end() ? it->second.get() : nullptr;
}

/**
 * @brief Get a mesh recipe asset by ID.
 *
 * Searches for a mesh recipe asset with the given ID and returns a pointer to it.
 *
 * @param id The asset identifier
 * @return Pointer to the mesh recipe asset, or nullptr if not found
 */
const MeshRecipeAsset *AssetRegistry::getMeshRecipe(AssetId id) const
{
    auto it = meshRecipes_.find(id);
    return it != meshRecipes_.end() ? it->second.get() : nullptr;
}

/**
 * @brief Check if a package has been loaded.
 *
 * Searches the list of loaded packages for the given package name.
 *
 * @param packageName Name of the package to check
 * @return true if the package is loaded, false otherwise
 */
bool AssetRegistry::hasPackage(const std::string &packageName) const
{
    return std::find(loadedPackages_.begin(), loadedPackages_.end(), packageName) != loadedPackages_.end();
}

/**
 * @brief Mark a package as loaded.
 *
 * Adds the package name to the list of loaded packages if it's not already there.
 * This prevents duplicate loading of the same package.
 *
 * @param packageName Name of the package to mark as loaded
 */
void AssetRegistry::markPackageLoaded(const std::string &packageName)
{
    if (!hasPackage(packageName))
    {
        loadedPackages_.push_back(packageName);
    }
}

/**
 * @brief Get the list of all loaded packages.
 *
 * Returns a reference to the internal vector of loaded package names.
 *
 * @return Const reference to the vector of loaded package names
 */
const std::vector<std::string> &AssetRegistry::getLoadedPackages() const
{
    return loadedPackages_;
}

/**
 * @brief Clear all assets and configurations.
 *
 * Removes all registered assets, scene configurations, and package information.
 * Used during hot reloading to reset the registry to a clean state.
 */
void AssetRegistry::clear()
{
    fonts_.clear();
    textures_.clear();
    materials_.clear();
    meshRecipes_.clear();
    sceneConfigs_.clear();
    defaultSceneId_.clear();
    loadedPackages_.clear();
}

// Scene configuration methods

/**
 * @brief Register a scene configuration with the given ID.
 *
 * Stores the XML scene configuration string for later retrieval.
 * Scene configurations define how worlds should be generated.
 *
 * @param id Unique identifier for the scene configuration
 * @param sceneXml XML string containing the scene configuration
 */
void AssetRegistry::registerSceneConfig(AssetId id, const std::string &sceneXml)
{
    sceneConfigs_[id] = sceneXml;
}

/**
 * @brief Get a scene configuration by ID.
 *
 * Retrieves the XML string for a scene configuration.
 *
 * @param id The scene configuration identifier
 * @return Pointer to the XML string, or nullptr if not found
 */
const std::string *AssetRegistry::getSceneConfig(AssetId id) const
{
    auto it = sceneConfigs_.find(id);
    return (it != sceneConfigs_.end()) ? &it->second : nullptr;
}

/**
 * @brief Set the default scene configuration.
 *
 * Marks a scene configuration as the default one to use when no specific
 * scene is requested.
 *
 * @param id The scene configuration identifier to set as default
 */
void AssetRegistry::setDefaultScene(AssetId id)
{
    defaultSceneId_ = id;
}

/**
 * @brief Get the default scene configuration XML.
 *
 * Returns the XML string of the default scene configuration.
 *
 * @return Pointer to the default scene XML string, or nullptr if not set
 */
const std::string *AssetRegistry::getDefaultScene() const
{
    if (defaultSceneId_.empty())
        return nullptr;
    return getSceneConfig(defaultSceneId_);
}

/**
 * @brief Get the ID of the default scene configuration.
 *
 * Returns the identifier of the scene configuration marked as default.
 *
 * @return The default scene configuration ID
 */
AssetId AssetRegistry::getDefaultSceneId() const
{
    return defaultSceneId_;
}
#ifndef ASSET_REGISTRY_H
#define ASSET_REGISTRY_H

#include <unordered_map>
#include <string>
#include <memory>
#include <variant>

// Forward declarations for asset types
struct FontAsset;
struct TextureAsset;
struct MaterialAsset;
struct MeshRecipeAsset;

/** Type alias for asset identifiers */
using AssetId = std::string;

/**
 * @brief Central registry for managing all game assets.
 *
 * The AssetRegistry stores and provides access to all types of assets used
 * in the simulation, including fonts, textures, materials, and mesh recipes.
 * It also manages package loading state and scene configurations for
 * data-driven world generation.
 */
class AssetRegistry
{
public:
    /**
     * @brief Construct an empty asset registry.
     */
    AssetRegistry();

    /**
     * @brief Destroy the asset registry and free all assets.
     */
    ~AssetRegistry();

    // Asset storage and retrieval

    /**
     * @brief Register a font asset with the given ID.
     *
     * @param id Unique identifier for the font asset
     * @param asset Unique pointer to the font asset
     */
    void registerFont(AssetId id, std::unique_ptr<FontAsset> asset);

    /**
     * @brief Register a texture asset with the given ID.
     *
     * @param id Unique identifier for the texture asset
     * @param asset Unique pointer to the texture asset
     */
    void registerTexture(AssetId id, std::unique_ptr<TextureAsset> asset);

    /**
     * @brief Register a material asset with the given ID.
     *
     * @param id Unique identifier for the material asset
     * @param asset Unique pointer to the material asset
     */
    void registerMaterial(AssetId id, std::unique_ptr<MaterialAsset> asset);

    /**
     * @brief Register a mesh recipe asset with the given ID.
     *
     * @param id Unique identifier for the mesh recipe asset
     * @param asset Unique pointer to the mesh recipe asset
     */
    void registerMeshRecipe(AssetId id, std::unique_ptr<MeshRecipeAsset> asset);

    /**
     * @brief Get a font asset by ID.
     *
     * @param id The asset identifier
     * @return Pointer to the font asset, or nullptr if not found
     */
    const FontAsset *getFont(AssetId id) const;

    /**
     * @brief Get a texture asset by ID.
     *
     * @param id The asset identifier
     * @return Pointer to the texture asset, or nullptr if not found
     */
    const TextureAsset *getTexture(AssetId id) const;

    /**
     * @brief Get a material asset by ID.
     *
     * @param id The asset identifier
     * @return Pointer to the material asset, or nullptr if not found
     */
    const MaterialAsset *getMaterial(AssetId id) const;

    /**
     * @brief Get a mesh recipe asset by ID.
     *
     * @param id The asset identifier
     * @return Pointer to the mesh recipe asset, or nullptr if not found
     */
    const MeshRecipeAsset *getMeshRecipe(AssetId id) const;

    // Package management

    /**
     * @brief Check if a package has been loaded.
     *
     * @param packageName Name of the package to check
     * @return true if the package is loaded, false otherwise
     */
    bool hasPackage(const std::string &packageName) const;

    /**
     * @brief Mark a package as loaded.
     *
     * @param packageName Name of the package to mark as loaded
     */
    void markPackageLoaded(const std::string &packageName);

    /**
     * @brief Get the list of all loaded packages.
     *
     * @return Const reference to the vector of loaded package names
     */
    const std::vector<std::string> &getLoadedPackages() const;

    // Scene configuration management

    /**
     * @brief Register a scene configuration with the given ID.
     *
     * @param id Unique identifier for the scene configuration
     * @param sceneXml XML string containing the scene configuration
     */
    void registerSceneConfig(AssetId id, const std::string &sceneXml);

    /**
     * @brief Get a scene configuration by ID.
     *
     * @param id The scene configuration identifier
     * @return Pointer to the XML string, or nullptr if not found
     */
    const std::string *getSceneConfig(AssetId id) const;

    /**
     * @brief Set the default scene configuration.
     *
     * @param id The scene configuration identifier to set as default
     */
    void setDefaultScene(AssetId id);

    /**
     * @brief Get the default scene configuration XML.
     *
     * @return Pointer to the default scene XML string, or nullptr if not set
     */
    const std::string *getDefaultScene() const;

    /**
     * @brief Get the ID of the default scene configuration.
     *
     * @return The default scene configuration ID
     */
    AssetId getDefaultSceneId() const;

    /**
     * @brief Clear all assets and configurations.
     *
     * Used for hot reloading to reset the registry state.
     */
    void clear();

private:
    std::unordered_map<AssetId, std::unique_ptr<FontAsset>> fonts_;             /**< Registered font assets */
    std::unordered_map<AssetId, std::unique_ptr<TextureAsset>> textures_;       /**< Registered texture assets */
    std::unordered_map<AssetId, std::unique_ptr<MaterialAsset>> materials_;     /**< Registered material assets */
    std::unordered_map<AssetId, std::unique_ptr<MeshRecipeAsset>> meshRecipes_; /**< Registered mesh recipe assets */

    // Scene configurations
    std::unordered_map<AssetId, std::string> sceneConfigs_; /**< Registered scene configurations */
    AssetId defaultSceneId_;                                /**< ID of the default scene configuration */

    std::vector<std::string> loadedPackages_; /**< List of loaded package names */
};

// Asset type definitions

/**
 * @brief Font asset data structure.
 *
 * Contains information needed to load and render fonts.
 */
struct FontAsset
{
    std::string path;  /**< File path to the font file */
    int size;          /**< Font size in points */
    bool antialiasing; /**< Whether to use antialiasing */
};

/**
 * @brief Texture asset data structure.
 *
 * Contains information needed to load and configure textures.
 */
struct TextureAsset
{
    std::string path;   /**< File path to the texture file */
    std::string format; /**< Texture format (e.g., "RGBA", "RGB") */
    bool mipmaps;       /**< Whether to generate mipmaps */
    std::string filter; /**< Texture filtering mode */
};

/**
 * @brief Material asset data structure.
 *
 * Contains shader and parameter information for materials.
 */
struct MaterialAsset
{
    std::string shaderId;                                                                /**< ID of the shader to use */
    std::unordered_map<std::string, std::variant<std::string, float, int, bool>> params; /**< Material parameters */
};

/**
 * @brief Mesh recipe asset data structure.
 *
 * Contains procedural generation parameters for meshes.
 */
struct MeshRecipeAsset
{
    std::string generator;                                                  /**< Name of the generator to use */
    std::unordered_map<std::string, std::variant<float, int, bool>> params; /**< Generation parameters */
};

#endif
#include "Entity.h"

/**
 * @brief Construct an entity with a unique identifier.
 *
 * Initializes the entity with the provided ID and prepares the component storage.
 *
 * @param id The unique identifier for this entity
 */
Entity::Entity(unsigned int id) : id_(id) {}
#ifndef ENTITY_H
#define ENTITY_H

#include "IComponent.h"
#include <memory>
#include <unordered_map>
#include <typeindex>

/**
 * @brief Represents an entity in the Entity Component System (ECS).
 *
 * An entity is a container for components that define its properties and behavior.
 * Entities are identified by a unique ID and can have multiple components attached
 * to them. The entity itself contains no logic - all behavior is implemented
 * through systems that operate on entities with specific component combinations.
 */
class Entity
{
public:
    /**
     * @brief Construct an entity with a unique identifier.
     *
     * @param id The unique identifier for this entity
     */
    Entity(unsigned int id);

    /**
     * @brief Add a component to this entity.
     *
     * Components define the properties and capabilities of an entity.
     * Each component type can only be added once per entity.
     *
     * @tparam T The type of component to add
     * @param component Unique pointer to the component instance
     */
    template <typename T>
    void addComponent(std::unique_ptr<T> component)
    {
        components_[std::type_index(typeid(T))] = std::move(component);
    }

    /**
     * @brief Get a component from this entity.
     *
     * @tparam T The type of component to retrieve
     * @return Pointer to the component if it exists, nullptr otherwise
     */
    template <typename T>
    T *getComponent()
    {
        auto it = components_.find(std::type_index(typeid(T)));
        if (it != components_.end())
        {
            return static_cast<T *>(it->second.get());
        }
        return nullptr;
    }

private:
    unsigned int id_;                                                             /**< Unique identifier for this entity */
    std::unordered_map<std::type_index, std::unique_ptr<IComponent>> components_; /**< Map of component types to component instances */
};

#endif
#include "EventBus.h"

/**
 * @brief Construct an empty event bus.
 *
 * Initializes the event bus with no registered handlers.
 */
EventBus::EventBus() {}

/**
 * @brief Subscribe a handler function to a specific event type.
 *
 * Adds the handler to the list of functions that will be called when
 * events of the specified type are published. If this is the first
 * handler for this event type, a new entry is created in the handlers map.
 *
 * @param type The event type to subscribe to
 * @param handler Function to call when events of this type are published
 */
void EventBus::subscribe(EventType type, std::function<void(const IEvent &)> handler)
{
    handlers_[type].push_back(handler);
}

/**
 * @brief Publish an event to all subscribed handlers.
 *
 * Looks up all handlers registered for the event's type and calls each
 * one with a reference to the event. If no handlers are registered for
 * this event type, the function returns without doing anything.
 *
 * @param event The event to publish
 */
void EventBus::publish(const IEvent &event)
{
    auto it = handlers_.find(event.getType());
    if (it != handlers_.end())
    {
        for (auto &handler : it->second)
        {
            handler(event);
        }
    }
}
#ifndef EVENTBUS_H
#define EVENTBUS_H

#include "IEvent.h"
#include <functional>
#include <unordered_map>
#include <vector>

/**
 * @brief Central event management system for inter-system communication.
 *
 * The EventBus implements a publish-subscribe pattern where systems can
 * subscribe to specific event types and receive notifications when those
 * events are published. This enables decoupled communication between
 * different parts of the simulation.
 */
class EventBus
{
public:
    /**
     * @brief Construct an empty event bus.
     */
    EventBus();

    /**
     * @brief Subscribe a handler function to a specific event type.
     *
     * Multiple handlers can subscribe to the same event type. When an
     * event of that type is published, all subscribed handlers will be called.
     *
     * @param type The event type to subscribe to
     * @param handler Function to call when events of this type are published
     */
    void subscribe(EventType type, std::function<void(const IEvent &)> handler);

    /**
     * @brief Publish an event to all subscribed handlers.
     *
     * All handlers subscribed to the event's type will be called with
     * a reference to the event object.
     *
     * @param event The event to publish
     */
    void publish(const IEvent &event);

private:
    /** Map of event types to lists of handler functions */
    std::unordered_map<EventType, std::vector<std::function<void(const IEvent &)>>> handlers_;
};

#endif
#ifndef ICOMPONENT_H
#define ICOMPONENT_H

/**
 * @brief Base interface for all components in the Entity Component System (ECS).
 *
 * Components are data structures that can be attached to entities to give them
 * specific properties or behaviors. This interface provides the basic contract
 * that all components must follow, primarily for proper memory management.
 */
class IComponent
{
public:
    /**
     * @brief Virtual destructor to ensure proper cleanup of derived components.
     *
     * This allows components to be properly deleted through base class pointers,
     * enabling polymorphic component management in the ECS.
     */
    virtual ~IComponent() = default;
};

#endif
#ifndef IEVENT_H
#define IEVENT_H

/**
 * @brief Enumeration of all possible event types in the simulation.
 *
 * Event types are used to categorize different kinds of events that can occur
 * during simulation execution, enabling systems to subscribe to specific event types.
 */
enum class EventType
{
    BatteryLow,               /**< Low battery warning event */
    Collision,                /**< Collision detection event */
    ConsoleToggle,            /**< Console visibility toggle event */
    ConsoleVisibilityChanged, /**< Console visibility state change event */
    NoPackagesFound,          /**< No asset packages found during bootstrap */
    DefaultWorldGenerated,    /**< Default world generation completed */
    // Add more as needed
};

/**
 * @brief Base interface for all events in the event-driven architecture.
 *
 * Events are used for communication between different systems in the simulation.
 * Each event must provide its type for proper routing and handling.
 */
class IEvent
{
public:
    /**
     * @brief Virtual destructor to ensure proper cleanup of derived events.
     */
    virtual ~IEvent() = default;

    /**
     * @brief Get the type of this event.
     *
     * @return EventType The specific type of this event instance.
     */
    virtual EventType getType() const = 0;
};

#endif
#ifndef ISYSTEM_H
#define ISYSTEM_H

class World;

/**
 * @brief Base interface for all systems in the Entity Component System (ECS).
 *
 * Systems contain the logic that operates on entities and their components.
 * Each system is updated every frame with the current world state and delta time.
 */
class ISystem
{
public:
    /**
     * @brief Virtual destructor to ensure proper cleanup of derived systems.
     */
    virtual ~ISystem() = default;

    /**
     * @brief Update the system with the current world state.
     *
     * This method is called once per frame for each system, allowing it to
     * process entities, update components, and perform game logic.
     *
     * @param world Reference to the world containing all entities and systems.
     * @param dt Time elapsed since the last update in seconds.
     */
    virtual void update(World &world, float dt) = 0;
};

#endif
#pragma once

/**
 * @brief Simple quaternion class for representing 3D rotations.
 *
 * Quaternions provide a mathematically robust way to represent rotations
 * in 3D space, avoiding issues like gimbal lock that can occur with
 * Euler angles. This implementation provides basic quaternion operations
 * needed for the simulation.
 */
struct Quaternion
{
    float w, x, y, z; /**< Quaternion components: w (real part), x,y,z (imaginary parts) */

    /**
     * @brief Construct a quaternion with specified components.
     *
     * @param w The real component (default: 1.0f for identity rotation)
     * @param x The i component (default: 0.0f)
     * @param y The j component (default: 0.0f)
     * @param z The k component (default: 0.0f)
     */
    Quaternion(float w = 1.0f, float x = 0.0f, float y = 0.0f, float z = 0.0f) : w(w), x(x), y(y), z(z) {}

    /**
     * @brief Create an identity quaternion representing no rotation.
     *
     * @return Quaternion The identity quaternion (1, 0, 0, 0)
     */
    static Quaternion identity()
    {
        return Quaternion(1.0f, 0.0f, 0.0f, 0.0f);
    }
};
#include "SimClock.h"

/**
 * @brief Construct a simulation clock with a fixed timestep.
 *
 * Initializes the clock with the specified fixed timestep and resets
 * the accumulator to zero.
 *
 * @param fixedTimestep The fixed time step for physics simulation in seconds
 */
SimClock::SimClock(float fixedTimestep) : fixedTimestep_(fixedTimestep), accumulator_(0.0f) {}

/**
 * @brief Advance the simulation clock by the given delta time.
 *
 * This method accumulates the real time that has passed, which will be
 * used to determine when physics steps should occur.
 *
 * @param deltaTime Time elapsed since the last tick in seconds
 */
void SimClock::tick(float deltaTime)
{
    accumulator_ += deltaTime;
}

/**
 * @brief Check if a physics step should be performed.
 *
 * This implements the fixed timestep logic. If enough time has accumulated
 * (at least one fixed timestep), it consumes that time and returns true.
 * This ensures physics simulation runs at a consistent rate.
 *
 * @return true if physics should step, false otherwise
 */
bool SimClock::shouldStepPhysics()
{
    if (accumulator_ >= fixedTimestep_)
    {
        accumulator_ -= fixedTimestep_;
        return true;
    }
    return false;
}

/**
 * @brief Get the fixed timestep value.
 *
 * Returns the fixed timestep that was set during construction.
 *
 * @return The fixed timestep in seconds
 */
float SimClock::getFixedTimestep()
{
    return fixedTimestep_;
}
#ifndef SIMCLOCK_H
#define SIMCLOCK_H

/**
 * @brief Simulation clock for managing fixed timestep physics updates.
 *
 * The SimClock implements a fixed timestep system for physics simulation,
 * accumulating real time and determining when physics steps should occur.
 * This ensures consistent physics behavior regardless of frame rate.
 */
class SimClock
{
public:
    /**
     * @brief Construct a simulation clock with a fixed timestep.
     *
     * @param fixedTimestep The fixed time step for physics simulation in seconds
     */
    SimClock(float fixedTimestep);

    /**
     * @brief Advance the simulation clock by the given delta time.
     *
     * Adds the delta time to the accumulator, which tracks how much time
     * has passed since the last physics step.
     *
     * @param deltaTime Time elapsed since the last tick in seconds
     */
    void tick(float deltaTime);

    /**
     * @brief Check if a physics step should be performed.
     *
     * Returns true if enough time has accumulated for a physics step.
     * If true, the accumulated time is reduced by one fixed timestep.
     *
     * @return true if physics should step, false otherwise
     */
    bool shouldStepPhysics();

    /**
     * @brief Get the fixed timestep value.
     *
     * @return The fixed timestep in seconds
     */
    float getFixedTimestep();

private:
    float fixedTimestep_; /**< The fixed time step for physics simulation */
    float accumulator_;   /**< Accumulated time since last physics step */
};

#endif
#pragma once

/**
 * @brief Simple 3D vector class for representing positions, scales, and other 3D quantities.
 *
 * This class provides basic 3D vector operations needed for the simulation,
 * including component-wise arithmetic operations. It's used throughout the
 * ECS for positioning entities, scaling, and other spatial calculations.
 */
struct Vector3D
{
    float x, y, z; /**< The x, y, and z components of the vector */

    /**
     * @brief Construct a 3D vector with specified components.
     *
     * @param x The x component (default: 0.0f)
     * @param y The y component (default: 0.0f)
     * @param z The z component (default: 0.0f)
     */
    Vector3D(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z) {}

    /**
     * @brief Add two vectors component-wise.
     *
     * @param other The vector to add to this one
     * @return Vector3D The result of the addition
     */
    Vector3D operator+(const Vector3D &other) const
    {
        return Vector3D(x + other.x, y + other.y, z + other.z);
    }

    /**
     * @brief Subtract two vectors component-wise.
     *
     * @param other The vector to subtract from this one
     * @return Vector3D The result of the subtraction
     */
    Vector3D operator-(const Vector3D &other) const
    {
        return Vector3D(x - other.x, y - other.y, z - other.z);
    }

    /**
     * @brief Multiply this vector by a scalar value.
     *
     * @param scalar The scalar value to multiply by
     * @return Vector3D The scaled vector
     */
    Vector3D operator*(float scalar) const
    {
        return Vector3D(x * scalar, y * scalar, z * scalar);
    }
};
#include "World.h"

/**
 * @brief Construct a world with an event bus for communication.
 *
 * Initializes the world with a reference to the event bus that will be used
 * for inter-system communication throughout the simulation.
 *
 * @param eventBus Reference to the event bus used for inter-system communication
 */
World::World(EventBus &eventBus) : eventBus_(eventBus) {}

/**
 * @brief Add an entity to the world.
 *
 * The world takes ownership of the entity through the unique pointer,
 * ensuring proper memory management and lifetime control.
 *
 * @param entity Unique pointer to the entity to add
 */
void World::addEntity(std::unique_ptr<Entity> entity)
{
    entities_.push_back(std::move(entity));
}

/**
 * @brief Add a system to the world.
 *
 * Systems are stored in the order they are added and will be updated
 * in that same order during the world's update cycle.
 *
 * @param system Unique pointer to the system to add
 */
void World::addSystem(std::unique_ptr<ISystem> system)
{
    systems_.push_back(std::move(system));
}

/**
 * @brief Update all systems in the world.
 *
 * Iterates through all registered systems and calls their update methods,
 * passing the world reference and delta time. This is the main simulation
 * loop that drives all game logic.
 *
 * @param dt Time elapsed since the last update in seconds
 */
void World::update(float dt)
{
    for (auto &system : systems_)
    {
        system->update(*this, dt);
    }
}
#ifndef WORLD_H
#define WORLD_H

#include "EventBus.h"
#include "ISystem.h"
#include "Entity.h"
#include <vector>
#include <memory>

/**
 * @brief The central world class that manages all entities and systems in the ECS.
 *
 * The World acts as the container and coordinator for all entities, components,
 * and systems in the simulation. It provides methods to add entities and systems,
 * and coordinates their updates each frame. The World also provides access to
 * the event bus for inter-system communication.
 */
class World
{
public:
    /**
     * @brief Construct a world with an event bus for communication.
     *
     * @param eventBus Reference to the event bus used for inter-system communication
     */
    World(EventBus &eventBus);

    /**
     * @brief Add an entity to the world.
     *
     * The world takes ownership of the entity and will manage its lifetime.
     *
     * @param entity Unique pointer to the entity to add
     */
    void addEntity(std::unique_ptr<Entity> entity);

    /**
     * @brief Add a system to the world.
     *
     * Systems are updated in the order they are added. The world takes
     * ownership of the system and will manage its lifetime.
     *
     * @param system Unique pointer to the system to add
     */
    void addSystem(std::unique_ptr<ISystem> system);

    /**
     * @brief Update all systems in the world.
     *
     * This method iterates through all registered systems and calls their
     * update methods with the current delta time.
     *
     * @param dt Time elapsed since the last update in seconds
     */
    void update(float dt);

    /**
     * @brief Get read-only access to all systems in the world.
     *
     * @return Const reference to the vector of systems
     */
    const std::vector<std::unique_ptr<ISystem>> &getSystems() const { return systems_; }

    /**
     * @brief Get read-only access to all entities in the world.
     *
     * @return Const reference to the vector of entities
     */
    const std::vector<std::unique_ptr<Entity>> &getEntities() const { return entities_; }

private:
    EventBus &eventBus_;                            /**< Reference to the event bus for communication */
    std::vector<std::unique_ptr<Entity>> entities_; /**< All entities in the world */
    std::vector<std::unique_ptr<ISystem>> systems_; /**< All systems in the world, updated in order */
};

#endif
#pragma once
#include "../core/IEvent.h"

/**
 * @file InputEvents.h
 * @brief Event definitions for user input and console interactions.
 *
 * This file defines events related to user input handling, including
 * console toggling and visibility changes. These events are used
 * by input systems and UI management systems.
 */

/**
 * @struct ConsoleToggleEvent
 * @brief Event triggered when the console toggle key is pressed.
 *
 * This event is fired when the user presses the key combination
 * that toggles the developer console visibility. It contains no
 * additional data beyond the event type.
 */
struct ConsoleToggleEvent : public IEvent
{
    /** @brief Default constructor for ConsoleToggleEvent */
    ConsoleToggleEvent() = default;

    /**
     * @brief Get the event type identifier.
     * @return EventType::ConsoleToggle
     */
    EventType getType() const override { return EventType::ConsoleToggle; }
};

/**
 * @struct ConsoleVisibilityChangedEvent
 * @brief Event triggered when console visibility changes.
 *
 * This event is fired whenever the console visibility state changes,
 * either due to user input or programmatic control. It includes
 * the new visibility state.
 */
struct ConsoleVisibilityChangedEvent : public IEvent
{
    /**
     * @brief Construct a new ConsoleVisibilityChangedEvent.
     * @param visible The new visibility state of the console
     */
    ConsoleVisibilityChangedEvent(bool visible) : isVisible(visible) {}

    /**
     * @brief Get the event type identifier.
     * @return EventType::ConsoleVisibilityChanged
     */
    EventType getType() const override { return EventType::ConsoleVisibilityChanged; }

    /** @brief The current visibility state of the console */
    bool isVisible;
};
#pragma once
#include "../core/IEvent.h"

/**
 * @file WorldGenEvents.h
 * @brief Event definitions for world generation and asset loading processes.
 *
 * This file defines events related to world generation, asset package loading,
 * and bootstrap processes. These events are used by world generation systems
 * and asset management systems to communicate state changes.
 */

/**
 * @struct NoPackagesFoundEvent
 * @brief Event triggered when no asset packages are found during bootstrap.
 *
 * This event is fired when the asset loading system cannot find any
 * valid asset packages during the initial bootstrap process. This
 * typically indicates a missing or corrupted asset directory.
 */
struct NoPackagesFoundEvent : public IEvent
{
    /** @brief Default constructor for NoPackagesFoundEvent */
    NoPackagesFoundEvent() = default;

    /**
     * @brief Get the event type identifier.
     * @return EventType::NoPackagesFound
     */
    EventType getType() const override { return EventType::NoPackagesFound; }
};

/**
 * @struct DefaultWorldGeneratedEvent
 * @brief Event triggered when the default world has been generated.
 *
 * This event is fired after the default world scene has been successfully
 * generated and loaded. It signals that the basic world setup is complete
 * and the simulation can begin.
 */
struct DefaultWorldGeneratedEvent : public IEvent
{
    /** @brief Default constructor for DefaultWorldGeneratedEvent */
    DefaultWorldGeneratedEvent() = default;

    /**
     * @brief Get the event type identifier.
     * @return EventType::DefaultWorldGenerated
     */
    EventType getType() const override { return EventType::DefaultWorldGenerated; }
};
/**
 * @file CubeGenerator.h
 * @brief Procedural cube mesh generator with variations
 *
 * The CubeGenerator creates cube meshes with configurable variations
 * for voxel-style rendering. Features include:
 * - Basic cube generation with proper normals and UVs
 * - Size variations for organic feel
 * - Corner rounding for softer appearance
 * - Texture coordinate mapping options
 * - Integration with Math utilities for calculations
 *
 * @author Generated for Voxel Busy Indicator Scene
 * @date 2024
 */

#pragma once

#include "../math/MathUtils.h"
#include <vector>
#include <cstdint>

/**
 * @brief Procedural cube mesh generator
 *
 * Generates cube meshes with various modifications for voxel-style
 * rendering including size variations and corner rounding.
 */
class CubeGenerator
{
public:
    /**
     * @brief Vertex data structure
     */
    struct Vertex
    {
        Math::float3 position; /**< Vertex position */
        Math::float3 normal;   /**< Vertex normal */
        Math::float2 uv;       /**< Texture coordinates */

        Vertex() : position{0, 0, 0}, normal{0, 0, 0}, uv{0, 0} {}
        Vertex(const Math::float3 &pos, const Math::float3 &norm, const Math::float2 &texCoord)
            : position(pos), normal(norm), uv(texCoord) {}
    };

    /**
     * @brief Generated mesh data
     */
    struct MeshData
    {
        std::vector<Vertex> vertices;  /**< Vertex array */
        std::vector<uint32_t> indices; /**< Triangle indices */
        uint32_t triangleCount;        /**< Number of triangles */
        uint32_t vertexCount;          /**< Number of vertices */

        MeshData() : triangleCount(0), vertexCount(0) {}
    };

    /**
     * @brief UV mapping mode for cube faces
     */
    enum class UVMode
    {
        PerFace,  /**< Each face gets full UV space [0,1] */
        Atlas,    /**< All faces share UV space in atlas layout */
        Projected /**< Projected mapping from one direction */
    };

private:
    /** @brief Cube size */
    Math::float3 size;

    /** @brief Corner rounding radius (0 = sharp corners) */
    float cornerRadius;

    /** @brief Corner rounding subdivision level */
    int cornerSubdivisions;

    /** @brief UV mapping mode */
    UVMode uvMode;

    /** @brief Random seed for variations */
    uint32_t randomSeed;

public:
    /**
     * @brief Construct a new CubeGenerator
     *
     * @param cubeSize Size of the cube (can be non-uniform)
     * @param rounding Corner rounding radius
     * @param subdivisions Corner subdivision level for rounding
     * @param uvMapping UV mapping mode
     * @param seed Random seed for variations
     */
    CubeGenerator(const Math::float3 &cubeSize = {1, 1, 1},
                  float rounding = 0.0f,
                  int subdivisions = 1,
                  UVMode uvMapping = UVMode::PerFace,
                  uint32_t seed = 12345)
        : size(cubeSize), cornerRadius(rounding), cornerSubdivisions(subdivisions), uvMode(uvMapping), randomSeed(seed)
    {
    }

    /**
     * @brief Generate cube mesh
     *
     * @return Generated mesh data
     */
    MeshData generate()
    {
        MeshData mesh;

        if (cornerRadius > 0.0f)
        {
            generateRoundedCube(mesh);
        }
        else
        {
            generateBasicCube(mesh);
        }

        // Update counts
        mesh.vertexCount = static_cast<uint32_t>(mesh.vertices.size());
        mesh.triangleCount = static_cast<uint32_t>(mesh.indices.size()) / 3;

        return mesh;
    }

    /**
     * @brief Generate basic cube with random variations
     *
     * @param variations Amount of random size variation per vertex
     * @return Generated mesh data with variations
     */
    MeshData generateWithVariations(float variations = 0.1f)
    {
        MeshData mesh = generate();

        // Apply random variations to vertices
        uint32_t state = randomSeed;
        for (auto &vertex : mesh.vertices)
        {
            float variation = 1.0f + variations * (Math::rand01(state) - 0.5f);
            vertex.position = Math::scale(vertex.position, variation);
        }

        // Recalculate normals after variation
        recalculateNormals(mesh);

        return mesh;
    }

    /**
     * @brief Set cube size
     *
     * @param cubeSize New cube size
     */
    void setSize(const Math::float3 &cubeSize)
    {
        size = cubeSize;
    }

    /**
     * @brief Set corner rounding
     *
     * @param radius Rounding radius
     * @param subdivisions Subdivision level
     */
    void setCornerRounding(float radius, int subdivisions = 1)
    {
        cornerRadius = Math::clamp(radius, 0.0f, Math::min({size.x, size.y, size.z}) * 0.5f);
        cornerSubdivisions = Math::clamp(subdivisions, 1, 5);
    }

    /**
     * @brief Set UV mapping mode
     *
     * @param mode New UV mapping mode
     */
    void setUVMode(UVMode mode)
    {
        uvMode = mode;
    }

private:
    /**
     * @brief Generate basic cube mesh
     *
     * @param mesh Output mesh data
     */
    void generateBasicCube(MeshData &mesh)
    {
        // Half sizes for convenience
        float hx = size.x * 0.5f;
        float hy = size.y * 0.5f;
        float hz = size.z * 0.5f;

        // Face vertices (position, normal, uv)
        std::vector<std::vector<Vertex>> faces = {
            // Front face (+Z)
            {{{{-hx, -hy, hz}, {0, 0, 1}, {0, 0}},
              {{hx, -hy, hz}, {0, 0, 1}, {1, 0}},
              {{hx, hy, hz}, {0, 0, 1}, {1, 1}},
              {{-hx, hy, hz}, {0, 0, 1}, {0, 1}}}},
            // Back face (-Z)
            {{{{hx, -hy, -hz}, {0, 0, -1}, {0, 0}},
              {{-hx, -hy, -hz}, {0, 0, -1}, {1, 0}},
              {{-hx, hy, -hz}, {0, 0, -1}, {1, 1}},
              {{hx, hy, -hz}, {0, 0, -1}, {0, 1}}}},
            // Left face (-X)
            {{{{-hx, -hy, -hz}, {-1, 0, 0}, {0, 0}},
              {{-hx, -hy, hz}, {-1, 0, 0}, {1, 0}},
              {{-hx, hy, hz}, {-1, 0, 0}, {1, 1}},
              {{-hx, hy, -hz}, {-1, 0, 0}, {0, 1}}}},
            // Right face (+X)
            {{{{hx, -hy, hz}, {1, 0, 0}, {0, 0}},
              {{hx, -hy, -hz}, {1, 0, 0}, {1, 0}},
              {{hx, hy, -hz}, {1, 0, 0}, {1, 1}},
              {{hx, hy, hz}, {1, 0, 0}, {0, 1}}}},
            // Bottom face (-Y)
            {{{{-hx, -hy, -hz}, {0, -1, 0}, {0, 0}},
              {{hx, -hy, -hz}, {0, -1, 0}, {1, 0}},
              {{hx, -hy, hz}, {0, -1, 0}, {1, 1}},
              {{-hx, -hy, hz}, {0, -1, 0}, {0, 1}}}},
            // Top face (+Y)
            {{{{-hx, hy, hz}, {0, 1, 0}, {0, 0}},
              {{hx, hy, hz}, {0, 1, 0}, {1, 0}},
              {{hx, hy, -hz}, {0, 1, 0}, {1, 1}},
              {{-hx, hy, -hz}, {0, 1, 0}, {0, 1}}}}};

        // Add vertices and indices for each face
        for (size_t faceIndex = 0; faceIndex < faces.size(); ++faceIndex)
        {
            uint32_t baseIndex = static_cast<uint32_t>(mesh.vertices.size());

            // Add face vertices with UV mapping
            for (size_t vertIndex = 0; vertIndex < 4; ++vertIndex)
            {
                Vertex vertex = faces[faceIndex][vertIndex];
                vertex.uv = calculateUV(vertex.position, faceIndex, vertIndex);
                mesh.vertices.push_back(vertex);
            }

            // Add face indices (two triangles per face)
            mesh.indices.insert(mesh.indices.end(), {baseIndex, baseIndex + 1, baseIndex + 2,
                                                     baseIndex, baseIndex + 2, baseIndex + 3});
        }
    }

    /**
     * @brief Generate rounded cube mesh
     *
     * @param mesh Output mesh data
     */
    void generateRoundedCube(MeshData &mesh)
    {
        // For rounded cubes, we create a more complex mesh
        // This is a simplified version - full implementation would be quite complex

        // Start with basic cube
        generateBasicCube(mesh);

        // Apply corner rounding by moving vertices towards sphere
        float maxRadius = Math::min({size.x, size.y, size.z}) * 0.5f;
        float clampedRadius = Math::clamp(cornerRadius, 0.0f, maxRadius);

        for (auto &vertex : mesh.vertices)
        {
            // Calculate distance from center
            float distance = Math::len(vertex.position);
            if (distance > clampedRadius)
            {
                // Blend between cube and sphere based on corner radius
                Math::float3 spherePos = Math::scale(Math::norm(vertex.position), clampedRadius);
                float blendFactor = cornerRadius / maxRadius;
                vertex.position = Math::lerp3(vertex.position, spherePos, blendFactor);
            }
        }

        // Recalculate normals after rounding
        recalculateNormals(mesh);
    }

    /**
     * @brief Calculate UV coordinates based on mapping mode
     *
     * @param position Vertex position
     * @param faceIndex Face index (0-5)
     * @param vertexIndex Vertex index within face (0-3)
     * @return UV coordinates
     */
    Math::float2 calculateUV(const Math::float3 &position, size_t faceIndex, size_t vertexIndex)
    {
        switch (uvMode)
        {
        case UVMode::PerFace:
            return calculatePerFaceUV(vertexIndex);

        case UVMode::Atlas:
            return calculateAtlasUV(faceIndex, vertexIndex);

        case UVMode::Projected:
            return calculateProjectedUV(position);

        default:
            return {0, 0};
        }
    }

    /**
     * @brief Calculate per-face UV coordinates
     *
     * @param vertexIndex Vertex index within face
     * @return UV coordinates
     */
    Math::float2 calculatePerFaceUV(size_t vertexIndex)
    {
        switch (vertexIndex)
        {
        case 0:
            return {0, 0};
        case 1:
            return {1, 0};
        case 2:
            return {1, 1};
        case 3:
            return {0, 1};
        default:
            return {0, 0};
        }
    }

    /**
     * @brief Calculate atlas UV coordinates
     *
     * @param faceIndex Face index
     * @param vertexIndex Vertex index within face
     * @return UV coordinates
     */
    Math::float2 calculateAtlasUV(size_t faceIndex, size_t vertexIndex)
    {
        // Simple 3x2 atlas layout
        float faceWidth = 1.0f / 3.0f;
        float faceHeight = 1.0f / 2.0f;

        int atlasX = static_cast<int>(faceIndex % 3);
        int atlasY = static_cast<int>(faceIndex / 3);

        Math::float2 localUV = calculatePerFaceUV(vertexIndex);

        return {
            atlasX * faceWidth + localUV.x * faceWidth,
            atlasY * faceHeight + localUV.y * faceHeight};
    }

    /**
     * @brief Calculate projected UV coordinates
     *
     * @param position Vertex position
     * @return UV coordinates
     */
    Math::float2 calculateProjectedUV(const Math::float3 &position)
    {
        // Simple planar projection from top
        float hx = size.x * 0.5f;
        float hz = size.z * 0.5f;

        return {
            (position.x + hx) / size.x,
            (position.z + hz) / size.z};
    }

    /**
     * @brief Recalculate normals for the mesh
     *
     * @param mesh Mesh to recalculate normals for
     */
    void recalculateNormals(MeshData &mesh)
    {
        // Reset all normals
        for (auto &vertex : mesh.vertices)
        {
            vertex.normal = {0, 0, 0};
        }

        // Calculate face normals and accumulate
        for (size_t i = 0; i < mesh.indices.size(); i += 3)
        {
            uint32_t i0 = mesh.indices[i];
            uint32_t i1 = mesh.indices[i + 1];
            uint32_t i2 = mesh.indices[i + 2];

            const Math::float3 &p0 = mesh.vertices[i0].position;
            const Math::float3 &p1 = mesh.vertices[i1].position;
            const Math::float3 &p2 = mesh.vertices[i2].position;

            // Calculate face normal
            Math::float3 edge1 = Math::sub(p1, p0);
            Math::float3 edge2 = Math::sub(p2, p0);
            Math::float3 faceNormal = Math::norm(Math::cross(edge1, edge2));

            // Accumulate to vertex normals
            mesh.vertices[i0].normal = Math::add(mesh.vertices[i0].normal, faceNormal);
            mesh.vertices[i1].normal = Math::add(mesh.vertices[i1].normal, faceNormal);
            mesh.vertices[i2].normal = Math::add(mesh.vertices[i2].normal, faceNormal);
        }

        // Normalize all vertex normals
        for (auto &vertex : mesh.vertices)
        {
            vertex.normal = Math::norm(vertex.normal);
        }
    }
};
/**
 * @file IcoSphereGenerator.h
 * @brief Procedural icosphere mesh generator
 *
 * The IcoSphereGenerator creates geodesic sphere meshes with uniform
 * triangle distribution using iterative subdivision of an icosahedron.
 * Features include:
 * - Configurable subdivision levels for detail control
 * - Proper UV mapping for texture application
 * - Normal calculation for lighting
 * - Vertex deduplication for efficiency
 * - Integration with Math utilities for calculations
 *
 * @author Generated for Voxel Busy Indicator Scene
 * @date 2024
 */

#pragma once

#include "../math/MathUtils.h"
#include <vector>
#include <map>
#include <cstdint>

/**
 * @brief Procedural icosphere mesh generator
 *
 * Generates geodesic sphere meshes by subdividing an icosahedron.
 * Provides more uniform triangle distribution than UV spheres.
 */
class IcoSphereGenerator
{
public:
    /**
     * @brief Vertex data structure
     */
    struct Vertex
    {
        Math::float3 position; /**< Vertex position */
        Math::float3 normal;   /**< Vertex normal */
        Math::float2 uv;       /**< Texture coordinates */

        Vertex() : position{0, 0, 0}, normal{0, 0, 0}, uv{0, 0} {}
        Vertex(const Math::float3 &pos, const Math::float3 &norm, const Math::float2 &texCoord)
            : position(pos), normal(norm), uv(texCoord) {}
    };

    /**
     * @brief Generated mesh data
     */
    struct MeshData
    {
        std::vector<Vertex> vertices;  /**< Vertex array */
        std::vector<uint32_t> indices; /**< Triangle indices */
        uint32_t triangleCount;        /**< Number of triangles */
        uint32_t vertexCount;          /**< Number of vertices */

        MeshData() : triangleCount(0), vertexCount(0) {}
    };

private:
    /** @brief Subdivision level (0 = icosahedron, higher = more detail) */
    int subdivisionLevel;

    /** @brief Sphere radius */
    float radius;

    /** @brief Whether to smooth normals */
    bool smoothNormals;

    /** @brief Vertex deduplication map */
    std::map<uint64_t, uint32_t> vertexMap;

    /** @brief Current mesh being generated */
    MeshData *currentMesh;

public:
    /**
     * @brief Construct a new IcoSphereGenerator
     *
     * @param subdivisions Number of subdivision levels (0-6 recommended)
     * @param sphereRadius Radius of the generated sphere
     * @param smooth Whether to smooth normals across faces
     */
    IcoSphereGenerator(int subdivisions = 2, float sphereRadius = 1.0f, bool smooth = true)
        : subdivisionLevel(subdivisions), radius(sphereRadius), smoothNormals(smooth), currentMesh(nullptr)
    {
    }

    /**
     * @brief Generate icosphere mesh
     *
     * @return Generated mesh data
     */
    MeshData generate()
    {
        MeshData mesh;
        currentMesh = &mesh;
        vertexMap.clear();

        // Create base icosahedron
        createIcosahedron();

        // Subdivide to desired level
        for (int i = 0; i < subdivisionLevel; ++i)
        {
            subdivide();
        }

        // Project vertices to sphere surface and calculate normals
        projectToSphere();

        // Generate UV coordinates
        generateUVCoordinates();

        // Update counts
        mesh.vertexCount = static_cast<uint32_t>(mesh.vertices.size());
        mesh.triangleCount = static_cast<uint32_t>(mesh.indices.size()) / 3;

        currentMesh = nullptr;
        return mesh;
    }

    /**
     * @brief Set subdivision level
     *
     * @param level New subdivision level (0-6 recommended)
     */
    void setSubdivisionLevel(int level)
    {
        subdivisionLevel = Math::clamp(level, 0, 6);
    }

    /**
     * @brief Set sphere radius
     *
     * @param sphereRadius New radius
     */
    void setRadius(float sphereRadius)
    {
        radius = sphereRadius;
    }

    /**
     * @brief Set normal smoothing
     *
     * @param smooth Whether to smooth normals
     */
    void setSmoothNormals(bool smooth)
    {
        smoothNormals = smooth;
    }

private:
    /**
     * @brief Create base icosahedron
     */
    void createIcosahedron()
    {
        if (!currentMesh)
            return;

        // Golden ratio
        const float phi = (1.0f + std::sqrt(5.0f)) * 0.5f;
        const float a = 1.0f;
        const float b = 1.0f / phi;

        // Create 12 vertices of icosahedron
        std::vector<Math::float3> positions = {
            {0, b, -a}, {b, a, 0}, {-b, a, 0}, {0, b, a}, {0, -b, a}, {-a, 0, b}, {0, -b, -a}, {a, 0, -b}, {a, 0, b}, {-a, 0, -b}, {b, -a, 0}, {-b, -a, 0}};

        // Add vertices
        for (const auto &pos : positions)
        {
            addVertex(pos);
        }

        // Create 20 triangular faces
        std::vector<std::vector<uint32_t>> faces = {
            {2, 1, 0}, {1, 2, 3}, {5, 4, 3}, {4, 8, 3}, {7, 6, 0}, {6, 9, 0}, {11, 10, 4}, {10, 11, 6}, {9, 5, 2}, {5, 9, 11}, {8, 7, 1}, {7, 8, 10}, {2, 5, 3}, {8, 1, 3}, {9, 2, 0}, {1, 7, 0}, {11, 9, 6}, {7, 10, 6}, {5, 11, 4}, {10, 8, 4}};

        // Add faces
        for (const auto &face : faces)
        {
            currentMesh->indices.push_back(face[0]);
            currentMesh->indices.push_back(face[1]);
            currentMesh->indices.push_back(face[2]);
        }
    }

    /**
     * @brief Subdivide current mesh
     */
    void subdivide()
    {
        if (!currentMesh)
            return;

        std::vector<uint32_t> newIndices;

        // Process each triangle
        for (size_t i = 0; i < currentMesh->indices.size(); i += 3)
        {
            uint32_t v0 = currentMesh->indices[i];
            uint32_t v1 = currentMesh->indices[i + 1];
            uint32_t v2 = currentMesh->indices[i + 2];

            // Get midpoint vertices
            uint32_t m01 = getMidpointVertex(v0, v1);
            uint32_t m12 = getMidpointVertex(v1, v2);
            uint32_t m20 = getMidpointVertex(v2, v0);

            // Create 4 new triangles
            newIndices.insert(newIndices.end(), {v0, m01, m20});
            newIndices.insert(newIndices.end(), {v1, m12, m01});
            newIndices.insert(newIndices.end(), {v2, m20, m12});
            newIndices.insert(newIndices.end(), {m01, m12, m20});
        }

        currentMesh->indices = std::move(newIndices);
    }

    /**
     * @brief Project all vertices to sphere surface
     */
    void projectToSphere()
    {
        if (!currentMesh)
            return;

        for (auto &vertex : currentMesh->vertices)
        {
            // Normalize position to unit sphere
            vertex.position = Math::norm(vertex.position);

            // Scale to desired radius
            vertex.position = Math::scale(vertex.position, radius);

            // Normal is the same as normalized position for a sphere
            vertex.normal = Math::norm(vertex.position);
        }
    }

    /**
     * @brief Generate UV coordinates for vertices
     */
    void generateUVCoordinates()
    {
        if (!currentMesh)
            return;

        for (auto &vertex : currentMesh->vertices)
        {
            // Convert 3D position to spherical coordinates
            Math::float3 normalized = Math::norm(vertex.position);

            // Calculate UV from spherical coordinates
            float u = 0.5f + std::atan2(normalized.z, normalized.x) / (2.0f * Math::Pi);
            float v = 0.5f - std::asin(normalized.y) / Math::Pi;

            vertex.uv = {u, v};
        }

        // Fix UV seam issues
        fixUVSeams();
    }

    /**
     * @brief Fix UV coordinate seams at the sphere wrap-around
     */
    void fixUVSeams()
    {
        if (!currentMesh)
            return;

        // Process each triangle to fix UV discontinuities
        for (size_t i = 0; i < currentMesh->indices.size(); i += 3)
        {
            Vertex &v0 = currentMesh->vertices[currentMesh->indices[i]];
            Vertex &v1 = currentMesh->vertices[currentMesh->indices[i + 1]];
            Vertex &v2 = currentMesh->vertices[currentMesh->indices[i + 2]];

            // Check for UV wrap-around
            fixTriangleUVs(v0, v1, v2);
        }
    }

    /**
     * @brief Fix UV coordinates for a single triangle
     *
     * @param v0 First vertex
     * @param v1 Second vertex
     * @param v2 Third vertex
     */
    void fixTriangleUVs(Vertex &v0, Vertex &v1, Vertex &v2)
    {
        // Check for horizontal wrap-around (U coordinate)
        if (std::abs(v0.uv.x - v1.uv.x) > 0.5f)
        {
            if (v0.uv.x > v1.uv.x)
                v1.uv.x += 1.0f;
            else
                v0.uv.x += 1.0f;
        }
        if (std::abs(v1.uv.x - v2.uv.x) > 0.5f)
        {
            if (v1.uv.x > v2.uv.x)
                v2.uv.x += 1.0f;
            else
                v1.uv.x += 1.0f;
        }
        if (std::abs(v2.uv.x - v0.uv.x) > 0.5f)
        {
            if (v2.uv.x > v0.uv.x)
                v0.uv.x += 1.0f;
            else
                v2.uv.x += 1.0f;
        }
    }

    /**
     * @brief Add vertex to mesh with deduplication
     *
     * @param position Vertex position
     * @return Vertex index
     */
    uint32_t addVertex(const Math::float3 &position)
    {
        if (!currentMesh)
            return 0;

        // Create hash for vertex deduplication
        uint64_t hash = hashVertex(position);

        auto it = vertexMap.find(hash);
        if (it != vertexMap.end())
        {
            return it->second;
        }

        // Add new vertex
        uint32_t index = static_cast<uint32_t>(currentMesh->vertices.size());
        currentMesh->vertices.emplace_back(position, Math::float3{0, 0, 0}, Math::float2{0, 0});
        vertexMap[hash] = index;

        return index;
    }

    /**
     * @brief Get or create midpoint vertex between two vertices
     *
     * @param v0 First vertex index
     * @param v1 Second vertex index
     * @return Midpoint vertex index
     */
    uint32_t getMidpointVertex(uint32_t v0, uint32_t v1)
    {
        if (!currentMesh)
            return 0;

        // Calculate midpoint position
        const Math::float3 &pos0 = currentMesh->vertices[v0].position;
        const Math::float3 &pos1 = currentMesh->vertices[v1].position;
        Math::float3 midpoint = Math::scale(Math::add(pos0, pos1), 0.5f);

        return addVertex(midpoint);
    }

    /**
     * @brief Create hash for vertex position
     *
     * @param position Vertex position
     * @return Hash value
     */
    uint64_t hashVertex(const Math::float3 &position)
    {
        // Simple hash combining x, y, z coordinates
        const float precision = 1000000.0f;
        uint32_t x = static_cast<uint32_t>(position.x * precision);
        uint32_t y = static_cast<uint32_t>(position.y * precision);
        uint32_t z = static_cast<uint32_t>(position.z * precision);

        return (static_cast<uint64_t>(x) << 32) | (static_cast<uint64_t>(y) << 16) | z;
    }
};
/**
 * @file ProceduralAircraftGenerator.h
 * @brief Procedural low-poly aircraft mesh generator
 *
 * The ProceduralAircraftGenerator creates simple low-poly aircraft meshes
 * suitable for orbital motion display. Features include:
 * - Basic aircraft shapes with wings, fuselage, and tail
 * - Configurable proportions and style variations
 * - Low-poly aesthetic for performance and voxel style
 * - Proper normals and UV mapping
 * - Integration with Math utilities for calculations
 *
 * @author Generated for Voxel Busy Indicator Scene
 * @date 2024
 */

#pragma once

#include "../math/MathUtils.h"
#include <vector>
#include <cstdint>

/**
 * @brief Procedural low-poly aircraft mesh generator
 *
 * Generates simple aircraft meshes with configurable styles and
 * proportions suitable for voxel-style orbital animations.
 */
class ProceduralAircraftGenerator
{
public:
    /**
     * @brief Vertex data structure
     */
    struct Vertex
    {
        Math::float3 position; /**< Vertex position */
        Math::float3 normal;   /**< Vertex normal */
        Math::float2 uv;       /**< Texture coordinates */

        Vertex() : position{0, 0, 0}, normal{0, 0, 0}, uv{0, 0} {}
        Vertex(const Math::float3 &pos, const Math::float3 &norm, const Math::float2 &texCoord)
            : position(pos), normal(norm), uv(texCoord) {}
    };

    /**
     * @brief Generated mesh data
     */
    struct MeshData
    {
        std::vector<Vertex> vertices;  /**< Vertex array */
        std::vector<uint32_t> indices; /**< Triangle indices */
        uint32_t triangleCount;        /**< Number of triangles */
        uint32_t vertexCount;          /**< Number of vertices */

        MeshData() : triangleCount(0), vertexCount(0) {}
    };

    /**
     * @brief Aircraft style variations
     */
    enum class AircraftStyle
    {
        Fighter,   /**< Fighter jet style */
        Civilian,  /**< Civil aircraft style */
        Transport, /**< Transport aircraft style */
        Simple     /**< Simple abstract aircraft */
    };

    /**
     * @brief Aircraft configuration parameters
     */
    struct AircraftParams
    {
        float length;        /**< Overall aircraft length */
        float wingspan;      /**< Wing span */
        float height;        /**< Overall height */
        float fuselageWidth; /**< Fuselage width */
        float wingThickness; /**< Wing thickness */
        float tailSize;      /**< Tail size factor */
        AircraftStyle style; /**< Aircraft style */
        uint32_t randomSeed; /**< Random seed for variations */

        AircraftParams()
            : length(2.0f), wingspan(2.5f), height(0.5f), fuselageWidth(0.3f), wingThickness(0.1f), tailSize(0.8f), style(AircraftStyle::Simple), randomSeed(12345)
        {
        }
    };

private:
    /** @brief Current aircraft parameters */
    AircraftParams params;

public:
    /**
     * @brief Construct a new ProceduralAircraftGenerator
     *
     * @param aircraftParams Aircraft configuration
     */
    ProceduralAircraftGenerator(const AircraftParams &aircraftParams = AircraftParams())
        : params(aircraftParams)
    {
    }

    /**
     * @brief Generate aircraft mesh
     *
     * @return Generated mesh data
     */
    MeshData generate()
    {
        MeshData mesh;

        switch (params.style)
        {
        case AircraftStyle::Fighter:
            generateFighterAircraft(mesh);
            break;
        case AircraftStyle::Civilian:
            generateCivilianAircraft(mesh);
            break;
        case AircraftStyle::Transport:
            generateTransportAircraft(mesh);
            break;
        case AircraftStyle::Simple:
        default:
            generateSimpleAircraft(mesh);
            break;
        }

        // Calculate normals
        calculateNormals(mesh);

        // Update counts
        mesh.vertexCount = static_cast<uint32_t>(mesh.vertices.size());
        mesh.triangleCount = static_cast<uint32_t>(mesh.indices.size()) / 3;

        return mesh;
    }

    /**
     * @brief Set aircraft parameters
     *
     * @param aircraftParams New parameters
     */
    void setParams(const AircraftParams &aircraftParams)
    {
        params = aircraftParams;
    }

    /**
     * @brief Get current aircraft parameters
     *
     * @return Current parameters
     */
    const AircraftParams &getParams() const
    {
        return params;
    }

private:
    /**
     * @brief Generate simple abstract aircraft
     *
     * @param mesh Output mesh data
     */
    void generateSimpleAircraft(MeshData &mesh)
    {
        // Aircraft is oriented along +X axis (forward)
        float halfLength = params.length * 0.5f;
        float halfWingspan = params.wingspan * 0.5f;
        float halfHeight = params.height * 0.5f;
        float halfWidth = params.fuselageWidth * 0.5f;
        float wingThick = params.wingThickness * 0.5f;

        // Fuselage vertices (simplified box with tapered ends)
        addFuselageVertices(mesh, halfLength, halfWidth, halfHeight);

        // Wing vertices
        addWingVertices(mesh, halfLength * 0.3f, halfWingspan, wingThick);

        // Tail vertices
        addTailVertices(mesh, halfLength, halfWingspan * params.tailSize, halfHeight);

        // Generate UV coordinates
        generateUVCoordinates(mesh);
    }

    /**
     * @brief Generate fighter-style aircraft
     *
     * @param mesh Output mesh data
     */
    void generateFighterAircraft(MeshData &mesh)
    {
        // Fighter has more angular design and swept wings
        float halfLength = params.length * 0.5f;
        float halfWingspan = params.wingspan * 0.5f;
        float halfHeight = params.height * 0.5f;
        float halfWidth = params.fuselageWidth * 0.5f;

        // Pointed fuselage
        addPointedFuselage(mesh, halfLength, halfWidth, halfHeight);

        // Swept wings
        addSweptWings(mesh, halfLength * 0.2f, halfWingspan, params.wingThickness);

        // Vertical tail
        addVerticalTail(mesh, halfLength * -0.8f, halfHeight * params.tailSize);

        generateUVCoordinates(mesh);
    }

    /**
     * @brief Generate civilian aircraft
     *
     * @param mesh Output mesh data
     */
    void generateCivilianAircraft(MeshData &mesh)
    {
        // Civilian has rounded design and straight wings
        generateSimpleAircraft(mesh); // Use simple as base

        // Add engines under wings (simple cylinders)
        addEngines(mesh, params.length * 0.1f, params.wingspan * 0.3f);

        generateUVCoordinates(mesh);
    }

    /**
     * @brief Generate transport aircraft
     *
     * @param mesh Output mesh data
     */
    void generateTransportAircraft(MeshData &mesh)
    {
        // Transport is larger and more boxy
        AircraftParams originalParams = params;
        params.fuselageWidth *= 1.5f;
        params.height *= 1.2f;

        generateSimpleAircraft(mesh);

        params = originalParams; // Restore original params
        generateUVCoordinates(mesh);
    }

    /**
     * @brief Add fuselage vertices to mesh
     *
     * @param mesh Output mesh
     * @param halfLength Half length of fuselage
     * @param halfWidth Half width of fuselage
     * @param halfHeight Half height of fuselage
     */
    void addFuselageVertices(MeshData &mesh, float halfLength, float halfWidth, float halfHeight)
    {
        uint32_t baseIndex = static_cast<uint32_t>(mesh.vertices.size());

        // Simplified fuselage as tapered box
        // Front (pointed)
        mesh.vertices.push_back({{halfLength, 0, 0}, {0, 0, 0}, {0.5f, 0.5f}});

        // Middle section (8 vertices for box)
        float midX = 0.0f;
        mesh.vertices.push_back({{midX, -halfWidth, -halfHeight}, {0, 0, 0}, {0.3f, 0.2f}});
        mesh.vertices.push_back({{midX, halfWidth, -halfHeight}, {0, 0, 0}, {0.7f, 0.2f}});
        mesh.vertices.push_back({{midX, halfWidth, halfHeight}, {0, 0, 0}, {0.7f, 0.8f}});
        mesh.vertices.push_back({{midX, -halfWidth, halfHeight}, {0, 0, 0}, {0.3f, 0.8f}});

        // Rear section (4 vertices, smaller)
        float rearX = -halfLength * 0.8f;
        float rearScale = 0.5f;
        mesh.vertices.push_back({{rearX, -halfWidth * rearScale, -halfHeight * rearScale}, {0, 0, 0}, {0.4f, 0.3f}});
        mesh.vertices.push_back({{rearX, halfWidth * rearScale, -halfHeight * rearScale}, {0, 0, 0}, {0.6f, 0.3f}});
        mesh.vertices.push_back({{rearX, halfWidth * rearScale, halfHeight * rearScale}, {0, 0, 0}, {0.6f, 0.7f}});
        mesh.vertices.push_back({{rearX, -halfWidth * rearScale, halfHeight * rearScale}, {0, 0, 0}, {0.4f, 0.7f}});

        // Tail point
        mesh.vertices.push_back({{-halfLength, 0, 0}, {0, 0, 0}, {0.1f, 0.5f}});

        // Connect sections with triangles
        // Front to middle
        addQuad(mesh, baseIndex + 0, baseIndex + 1, baseIndex + 2, baseIndex + 0); // Front triangle
        addQuad(mesh, baseIndex + 0, baseIndex + 2, baseIndex + 3, baseIndex + 0); // Front triangle
        addQuad(mesh, baseIndex + 0, baseIndex + 3, baseIndex + 4, baseIndex + 0); // Front triangle
        addQuad(mesh, baseIndex + 0, baseIndex + 4, baseIndex + 1, baseIndex + 0); // Front triangle

        // Middle to rear
        addQuad(mesh, baseIndex + 1, baseIndex + 5, baseIndex + 6, baseIndex + 2);
        addQuad(mesh, baseIndex + 2, baseIndex + 6, baseIndex + 7, baseIndex + 3);
        addQuad(mesh, baseIndex + 3, baseIndex + 7, baseIndex + 8, baseIndex + 4);
        addQuad(mesh, baseIndex + 4, baseIndex + 8, baseIndex + 5, baseIndex + 1);

        // Rear to tail
        addTriangle(mesh, baseIndex + 5, baseIndex + 9, baseIndex + 6);
        addTriangle(mesh, baseIndex + 6, baseIndex + 9, baseIndex + 7);
        addTriangle(mesh, baseIndex + 7, baseIndex + 9, baseIndex + 8);
        addTriangle(mesh, baseIndex + 8, baseIndex + 9, baseIndex + 5);
    }

    /**
     * @brief Add wing vertices to mesh
     *
     * @param mesh Output mesh
     * @param centerX Center X position of wings
     * @param halfSpan Half wingspan
     * @param thickness Wing thickness
     */
    void addWingVertices(MeshData &mesh, float centerX, float halfSpan, float thickness)
    {
        uint32_t baseIndex = static_cast<uint32_t>(mesh.vertices.size());

        // Wing root (near fuselage)
        float rootChord = params.length * 0.3f;
        float rootX1 = centerX + rootChord * 0.5f;
        float rootX2 = centerX - rootChord * 0.5f;

        // Wing tip
        float tipChord = rootChord * 0.5f;
        float tipX1 = centerX + tipChord * 0.5f;
        float tipX2 = centerX - tipChord * 0.5f;

        // Wing vertices (top and bottom for each position)
        // Left wing
        mesh.vertices.push_back({{rootX1, 0, thickness}, {0, 0, 0}, {0.8f, 0.2f}});         // Root leading top
        mesh.vertices.push_back({{rootX2, 0, thickness}, {0, 0, 0}, {0.2f, 0.2f}});         // Root trailing top
        mesh.vertices.push_back({{tipX1, -halfSpan, thickness}, {0, 0, 0}, {0.8f, 0.0f}});  // Tip leading top
        mesh.vertices.push_back({{tipX2, -halfSpan, thickness}, {0, 0, 0}, {0.2f, 0.0f}});  // Tip trailing top
        mesh.vertices.push_back({{rootX1, 0, -thickness}, {0, 0, 0}, {0.8f, 0.4f}});        // Root leading bottom
        mesh.vertices.push_back({{rootX2, 0, -thickness}, {0, 0, 0}, {0.2f, 0.4f}});        // Root trailing bottom
        mesh.vertices.push_back({{tipX1, -halfSpan, -thickness}, {0, 0, 0}, {0.8f, 0.6f}}); // Tip leading bottom
        mesh.vertices.push_back({{tipX2, -halfSpan, -thickness}, {0, 0, 0}, {0.2f, 0.6f}}); // Tip trailing bottom

        // Right wing (mirror)
        mesh.vertices.push_back({{rootX1, 0, thickness}, {0, 0, 0}, {0.8f, 0.2f}});        // Root leading top
        mesh.vertices.push_back({{rootX2, 0, thickness}, {0, 0, 0}, {0.2f, 0.2f}});        // Root trailing top
        mesh.vertices.push_back({{tipX1, halfSpan, thickness}, {0, 0, 0}, {0.8f, 1.0f}});  // Tip leading top
        mesh.vertices.push_back({{tipX2, halfSpan, thickness}, {0, 0, 0}, {0.2f, 1.0f}});  // Tip trailing top
        mesh.vertices.push_back({{rootX1, 0, -thickness}, {0, 0, 0}, {0.8f, 0.4f}});       // Root leading bottom
        mesh.vertices.push_back({{rootX2, 0, -thickness}, {0, 0, 0}, {0.2f, 0.4f}});       // Root trailing bottom
        mesh.vertices.push_back({{tipX1, halfSpan, -thickness}, {0, 0, 0}, {0.8f, 0.8f}}); // Tip leading bottom
        mesh.vertices.push_back({{tipX2, halfSpan, -thickness}, {0, 0, 0}, {0.2f, 0.8f}}); // Tip trailing bottom

        // Wing surface triangles
        // Left wing top
        addQuad(mesh, baseIndex + 0, baseIndex + 2, baseIndex + 3, baseIndex + 1);
        // Left wing bottom
        addQuad(mesh, baseIndex + 4, baseIndex + 5, baseIndex + 7, baseIndex + 6);

        // Right wing top
        addQuad(mesh, baseIndex + 8, baseIndex + 9, baseIndex + 11, baseIndex + 10);
        // Right wing bottom
        addQuad(mesh, baseIndex + 12, baseIndex + 14, baseIndex + 15, baseIndex + 13);
    }

    /**
     * @brief Add tail vertices to mesh
     *
     * @param mesh Output mesh
     * @param rearX X position of tail
     * @param halfSpan Half span of tail
     * @param height Height of vertical tail
     */
    void addTailVertices(MeshData &mesh, float rearX, float halfSpan, float height)
    {
        uint32_t baseIndex = static_cast<uint32_t>(mesh.vertices.size());

        // Simple vertical tail
        float tailX1 = rearX * 0.8f;
        float tailX2 = rearX * 1.0f;
        float tailThickness = params.wingThickness * 0.5f;

        // Vertical tail vertices
        mesh.vertices.push_back({{tailX1, 0, height}, {0, 0, 0}, {0.9f, 0.9f}});
        mesh.vertices.push_back({{tailX2, 0, height * 0.5f}, {0, 0, 0}, {1.0f, 0.7f}});
        mesh.vertices.push_back({{tailX1, 0, 0}, {0, 0, 0}, {0.9f, 0.5f}});

        // Simple triangle
        addTriangle(mesh, baseIndex + 0, baseIndex + 1, baseIndex + 2);
    }

    /**
     * @brief Add pointed fuselage for fighter aircraft
     */
    void addPointedFuselage(MeshData &mesh, float halfLength, float halfWidth, float halfHeight)
    {
        // Similar to regular fuselage but more pointed
        addFuselageVertices(mesh, halfLength, halfWidth, halfHeight);
    }

    /**
     * @brief Add swept wings for fighter aircraft
     */
    void addSweptWings(MeshData &mesh, float centerX, float halfSpan, float thickness)
    {
        // Similar to regular wings but with sweep angle
        addWingVertices(mesh, centerX, halfSpan, thickness);
    }

    /**
     * @brief Add vertical tail for fighter aircraft
     */
    void addVerticalTail(MeshData &mesh, float rearX, float height)
    {
        addTailVertices(mesh, rearX, height * 0.3f, height);
    }

    /**
     * @brief Add engines for civilian aircraft
     */
    void addEngines(MeshData &mesh, float engineX, float engineY)
    {
        // Simple cylindrical engines under wings
        uint32_t baseIndex = static_cast<uint32_t>(mesh.vertices.size());

        float engineLength = params.length * 0.2f;
        float engineRadius = params.fuselageWidth * 0.3f;

        // Simple box engines
        for (int side = -1; side <= 1; side += 2)
        {
            float y = engineY * side;

            // Engine box vertices
            mesh.vertices.push_back({{engineX + engineLength, y - engineRadius, -engineRadius}, {0, 0, 0}, {0.1f, 0.1f}});
            mesh.vertices.push_back({{engineX + engineLength, y + engineRadius, -engineRadius}, {0, 0, 0}, {0.2f, 0.1f}});
            mesh.vertices.push_back({{engineX + engineLength, y + engineRadius, engineRadius}, {0, 0, 0}, {0.2f, 0.2f}});
            mesh.vertices.push_back({{engineX + engineLength, y - engineRadius, engineRadius}, {0, 0, 0}, {0.1f, 0.2f}});

            mesh.vertices.push_back({{engineX - engineLength, y - engineRadius, -engineRadius}, {0, 0, 0}, {0.0f, 0.1f}});
            mesh.vertices.push_back({{engineX - engineLength, y + engineRadius, -engineRadius}, {0, 0, 0}, {0.3f, 0.1f}});
            mesh.vertices.push_back({{engineX - engineLength, y + engineRadius, engineRadius}, {0, 0, 0}, {0.3f, 0.2f}});
            mesh.vertices.push_back({{engineX - engineLength, y - engineRadius, engineRadius}, {0, 0, 0}, {0.0f, 0.2f}});
        }
    }

    /**
     * @brief Add a quad (4 vertices) as two triangles
     */
    void addQuad(MeshData &mesh, uint32_t v0, uint32_t v1, uint32_t v2, uint32_t v3)
    {
        mesh.indices.insert(mesh.indices.end(), {v0, v1, v2});
        mesh.indices.insert(mesh.indices.end(), {v0, v2, v3});
    }

    /**
     * @brief Add a triangle
     */
    void addTriangle(MeshData &mesh, uint32_t v0, uint32_t v1, uint32_t v2)
    {
        mesh.indices.insert(mesh.indices.end(), {v0, v1, v2});
    }

    /**
     * @brief Calculate normals for all vertices
     */
    void calculateNormals(MeshData &mesh)
    {
        // Reset all normals
        for (auto &vertex : mesh.vertices)
        {
            vertex.normal = {0, 0, 0};
        }

        // Calculate face normals and accumulate
        for (size_t i = 0; i < mesh.indices.size(); i += 3)
        {
            uint32_t i0 = mesh.indices[i];
            uint32_t i1 = mesh.indices[i + 1];
            uint32_t i2 = mesh.indices[i + 2];

            const Math::float3 &p0 = mesh.vertices[i0].position;
            const Math::float3 &p1 = mesh.vertices[i1].position;
            const Math::float3 &p2 = mesh.vertices[i2].position;

            // Calculate face normal
            Math::float3 edge1 = Math::sub(p1, p0);
            Math::float3 edge2 = Math::sub(p2, p0);
            Math::float3 faceNormal = Math::norm(Math::cross(edge1, edge2));

            // Accumulate to vertex normals
            mesh.vertices[i0].normal = Math::add(mesh.vertices[i0].normal, faceNormal);
            mesh.vertices[i1].normal = Math::add(mesh.vertices[i1].normal, faceNormal);
            mesh.vertices[i2].normal = Math::add(mesh.vertices[i2].normal, faceNormal);
        }

        // Normalize all vertex normals
        for (auto &vertex : mesh.vertices)
        {
            vertex.normal = Math::norm(vertex.normal);
        }
    }

    /**
     * @brief Generate UV coordinates for all vertices
     */
    void generateUVCoordinates(MeshData &mesh)
    {
        // UV coordinates are already set during vertex creation
        // This function could be used for post-processing UV coordinates if needed
    }
};
#include "ProceduralTextureGenerator.h"
#include <cmath>
#include <algorithm>
#include <random>
#include <sstream>

namespace ProceduralTexture
{

    // ============================================================================
    // Color Implementation
    // ============================================================================

    Color Color::lerp(const Color &a, const Color &b, float t)
    {
        t = std::clamp(t, 0.0f, 1.0f);
        return Color(
            static_cast<uint8_t>(a.r + t * (b.r - a.r)),
            static_cast<uint8_t>(a.g + t * (b.g - a.g)),
            static_cast<uint8_t>(a.b + t * (b.b - a.b)),
            static_cast<uint8_t>(a.a + t * (b.a - a.a)));
    }

    Color Color::fromFloat(float r, float g, float b, float a)
    {
        return Color(
            static_cast<uint8_t>(std::clamp(r * 255.0f, 0.0f, 255.0f)),
            static_cast<uint8_t>(std::clamp(g * 255.0f, 0.0f, 255.0f)),
            static_cast<uint8_t>(std::clamp(b * 255.0f, 0.0f, 255.0f)),
            static_cast<uint8_t>(std::clamp(a * 255.0f, 0.0f, 255.0f)));
    }

    Color Color::fromHSV(float h, float s, float v, float a)
    {
        h = std::fmod(h, 360.0f);
        if (h < 0)
            h += 360.0f;
        s = std::clamp(s, 0.0f, 1.0f);
        v = std::clamp(v, 0.0f, 1.0f);

        float c = v * s;
        float x = c * (1.0f - std::abs(std::fmod(h / 60.0f, 2.0f) - 1.0f));
        float m = v - c;

        float r, g, b;
        if (h < 60)
        {
            r = c;
            g = x;
            b = 0;
        }
        else if (h < 120)
        {
            r = x;
            g = c;
            b = 0;
        }
        else if (h < 180)
        {
            r = 0;
            g = c;
            b = x;
        }
        else if (h < 240)
        {
            r = 0;
            g = x;
            b = c;
        }
        else if (h < 300)
        {
            r = x;
            g = 0;
            b = c;
        }
        else
        {
            r = c;
            g = 0;
            b = x;
        }

        return fromFloat(r + m, g + m, b + m, a);
    }

    // ============================================================================
    // TextureData Implementation
    // ============================================================================

    TextureData::TextureData(uint32_t w, uint32_t h, const std::string &fmt)
        : width(w), height(h), format(fmt)
    {
        channels = (fmt == "RGB") ? 3 : 4;
        pixels.resize(width * height);
    }

    Color &TextureData::getPixel(uint32_t x, uint32_t y)
    {
        return pixels[y * width + x];
    }

    const Color &TextureData::getPixel(uint32_t x, uint32_t y) const
    {
        return pixels[y * width + x];
    }

    void TextureData::setPixel(uint32_t x, uint32_t y, const Color &color)
    {
        if (x < width && y < height)
        {
            pixels[y * width + x] = color;
        }
    }

    void TextureData::clear(const Color &color)
    {
        std::fill(pixels.begin(), pixels.end(), color);
    }

    void TextureData::resize(uint32_t newWidth, uint32_t newHeight)
    {
        width = newWidth;
        height = newHeight;
        pixels.resize(width * height);
    }

    std::vector<uint8_t> TextureData::getRawData() const
    {
        std::vector<uint8_t> data;
        data.reserve(pixels.size() * channels);

        for (const auto &pixel : pixels)
        {
            data.push_back(pixel.r);
            data.push_back(pixel.g);
            data.push_back(pixel.b);
            if (channels == 4)
            {
                data.push_back(pixel.a);
            }
        }

        return data;
    }

    // ============================================================================
    // Main Generation Methods
    // ============================================================================

    TextureData ProceduralTextureGenerator::generateTexture(const TextureParams &params)
    {
        switch (params.type)
        {
        case TextureParams::Type::Noise:
            return generateNoiseTexture(params);
        case TextureParams::Type::Gradient:
            return generateGradientTexture(params);
        case TextureParams::Type::Pattern:
            return generatePatternTexture(params);
        case TextureParams::Type::Composite:
            return generateCompositeTexture(params);
        default:
            return TextureData(params.width, params.height);
        }
    }

    TextureData ProceduralTextureGenerator::generateFromParameters(const std::string &type,
                                                                   const std::map<std::string, std::string> &parameters)
    {
        TextureParams params;
        params.type = parseTextureType(type);

        // Parse common parameters
        auto it = parameters.find("width");
        if (it != parameters.end())
        {
            params.width = static_cast<uint32_t>(std::stoi(it->second));
        }

        it = parameters.find("height");
        if (it != parameters.end())
        {
            params.height = static_cast<uint32_t>(std::stoi(it->second));
        }

        it = parameters.find("name");
        if (it != parameters.end())
        {
            params.name = it->second;
        }

        // Parse type-specific parameters
        switch (params.type)
        {
        case TextureParams::Type::Noise:
            params.noise = parseNoiseParameters(parameters);
            break;
        case TextureParams::Type::Gradient:
            params.gradient = parseGradientParameters(parameters);
            break;
        case TextureParams::Type::Pattern:
            params.pattern = parsePatternParameters(parameters);
            break;
        default:
            break;
        }

        return generateTexture(params);
    }

    // ============================================================================
    // Specific Generators
    // ============================================================================

    TextureData ProceduralTextureGenerator::generateNoise(const NoiseParams &params, uint32_t width, uint32_t height)
    {
        TextureData texture(width, height);

        for (uint32_t y = 0; y < height; ++y)
        {
            for (uint32_t x = 0; x < width; ++x)
            {
                float fx = static_cast<float>(x) / width;
                float fy = static_cast<float>(y) / height;

                float noise = 0.0f;
                switch (params.type)
                {
                case NoiseParams::Type::Perlin:
                    noise = fractalNoise(fx * params.frequency, fy * params.frequency, params);
                    break;
                case NoiseParams::Type::Simplex:
                    noise = simplexNoise(fx * params.frequency, fy * params.frequency, params.seed);
                    break;
                case NoiseParams::Type::Fractal:
                    noise = fractalNoise(fx * params.frequency, fy * params.frequency, params);
                    break;
                case NoiseParams::Type::Cellular:
                    noise = cellularNoise(fx * params.frequency, fy * params.frequency, params);
                    break;
                case NoiseParams::Type::Voronoi:
                    noise = voronoiNoise(fx * params.frequency, fy * params.frequency, params);
                    break;
                case NoiseParams::Type::White:
                {
                    std::mt19937 rng(params.seed + x * 1000 + y);
                    std::uniform_real_distribution<float> dist(0.0f, 1.0f);
                    noise = dist(rng);
                }
                break;
                }

                noise = std::clamp(noise, 0.0f, 1.0f);
                uint8_t value = static_cast<uint8_t>(noise * 255);
                texture.setPixel(x, y, Color(value, value, value, 255));
            }
        }

        return texture;
    }

    TextureData ProceduralTextureGenerator::generateGradient(const GradientParams &params, uint32_t width, uint32_t height)
    {
        TextureData texture(width, height);

        for (uint32_t y = 0; y < height; ++y)
        {
            for (uint32_t x = 0; x < width; ++x)
            {
                float fx = static_cast<float>(x) / width;
                float fy = static_cast<float>(y) / height;

                float t = calculateGradientPosition(params, fx, fy);
                if (params.repeat)
                {
                    t = std::fmod(t, 1.0f);
                    if (t < 0)
                        t += 1.0f;
                }
                else
                {
                    t = std::clamp(t, 0.0f, 1.0f);
                }

                Color color = evaluateGradient(params, t);
                texture.setPixel(x, y, color);
            }
        }

        return texture;
    }

    TextureData ProceduralTextureGenerator::generatePattern(const PatternParams &params, uint32_t width, uint32_t height)
    {
        TextureData texture(width, height);

        for (uint32_t y = 0; y < height; ++y)
        {
            for (uint32_t x = 0; x < width; ++x)
            {
                float fx = static_cast<float>(x) / width;
                float fy = static_cast<float>(y) / height;

                Color color;
                switch (params.type)
                {
                case PatternParams::Type::Checkerboard:
                    color = evaluateCheckerboard(params, fx, fy);
                    break;
                case PatternParams::Type::Stripes:
                    color = evaluateStripes(params, fx, fy);
                    break;
                case PatternParams::Type::Dots:
                    color = evaluateDots(params, fx, fy);
                    break;
                case PatternParams::Type::Grid:
                    color = evaluateGrid(params, fx, fy);
                    break;
                case PatternParams::Type::Spiral:
                    color = evaluateSpiral(params, fx, fy);
                    break;
                case PatternParams::Type::Waves:
                    color = evaluateWaves(params, fx, fy);
                    break;
                }

                texture.setPixel(x, y, color);
            }
        }

        return texture;
    }

    // ============================================================================
    // Noise Implementation
    // ============================================================================

    float ProceduralTextureGenerator::perlinNoise(float x, float y, uint32_t seed)
    {
        int X = static_cast<int>(std::floor(x)) & 255;
        int Y = static_cast<int>(std::floor(y)) & 255;

        x -= std::floor(x);
        y -= std::floor(y);

        float u = fade(x);
        float v = fade(y);

        uint32_t A = hash(X, Y, seed);
        uint32_t B = hash(X + 1, Y, seed);
        uint32_t C = hash(X, Y + 1, seed);
        uint32_t D = hash(X + 1, Y + 1, seed);

        return lerp(v,
                    lerp(u, grad(A, x, y), grad(B, x - 1, y)),
                    lerp(u, grad(C, x, y - 1), grad(D, x - 1, y - 1)));
    }

    float ProceduralTextureGenerator::simplexNoise(float x, float y, uint32_t seed)
    {
        // Simplified simplex noise implementation
        const float F2 = 0.5f * (std::sqrt(3.0f) - 1.0f);
        const float G2 = (3.0f - std::sqrt(3.0f)) / 6.0f;

        float s = (x + y) * F2;
        int i = static_cast<int>(std::floor(x + s));
        int j = static_cast<int>(std::floor(y + s));

        float t = (i + j) * G2;
        float X0 = i - t;
        float Y0 = j - t;
        float x0 = x - X0;
        float y0 = y - Y0;

        int i1, j1;
        if (x0 > y0)
        {
            i1 = 1;
            j1 = 0;
        }
        else
        {
            i1 = 0;
            j1 = 1;
        }

        float x1 = x0 - i1 + G2;
        float y1 = y0 - j1 + G2;
        float x2 = x0 - 1.0f + 2.0f * G2;
        float y2 = y0 - 1.0f + 2.0f * G2;

        uint32_t gi0 = hash(i, j, seed) % 12;
        uint32_t gi1 = hash(i + i1, j + j1, seed) % 12;
        uint32_t gi2 = hash(i + 1, j + 1, seed) % 12;

        float n0 = 0.0f, n1 = 0.0f, n2 = 0.0f;

        float t0 = 0.5f - x0 * x0 - y0 * y0;
        if (t0 >= 0)
        {
            t0 *= t0;
            n0 = t0 * t0 * grad(gi0, x0, y0);
        }

        float t1 = 0.5f - x1 * x1 - y1 * y1;
        if (t1 >= 0)
        {
            t1 *= t1;
            n1 = t1 * t1 * grad(gi1, x1, y1);
        }

        float t2 = 0.5f - x2 * x2 - y2 * y2;
        if (t2 >= 0)
        {
            t2 *= t2;
            n2 = t2 * t2 * grad(gi2, x2, y2);
        }

        return 70.0f * (n0 + n1 + n2);
    }

    float ProceduralTextureGenerator::fractalNoise(float x, float y, const NoiseParams &params)
    {
        float total = 0.0f;
        float frequency = params.frequency;
        float amplitude = params.amplitude;
        float maxValue = 0.0f;

        for (uint32_t i = 0; i < params.octaves; ++i)
        {
            total += perlinNoise(x * frequency, y * frequency, params.seed + i) * amplitude;
            maxValue += amplitude;
            amplitude *= params.persistence;
            frequency *= params.lacunarity;
        }

        return total / maxValue;
    }

    float ProceduralTextureGenerator::cellularNoise(float x, float y, const NoiseParams &params)
    {
        // Simple cellular automata implementation
        int gridSize = static_cast<int>(params.frequency);
        int gx = static_cast<int>(x * gridSize);
        int gy = static_cast<int>(y * gridSize);

        std::mt19937 rng(params.seed);
        std::uniform_real_distribution<float> dist(0.0f, 1.0f);

        // Initial random state
        bool alive = (hash(gx, gy, params.seed) % 100) < (params.threshold * 100);

        // Simple neighbor check for cellular pattern
        int neighbors = 0;
        for (int dx = -1; dx <= 1; ++dx)
        {
            for (int dy = -1; dy <= 1; ++dy)
            {
                if (dx == 0 && dy == 0)
                    continue;
                if ((hash(gx + dx, gy + dy, params.seed) % 100) < (params.threshold * 100))
                {
                    neighbors++;
                }
            }
        }

        // Conway's Game of Life rules (simplified)
        if (alive)
        {
            return (neighbors == 2 || neighbors == 3) ? 1.0f : 0.0f;
        }
        else
        {
            return (neighbors == 3) ? 1.0f : 0.0f;
        }
    }

    float ProceduralTextureGenerator::voronoiNoise(float x, float y, const NoiseParams &params)
    {
        float minDist = 1.0f;

        // Sample multiple cells
        for (int gx = -1; gx <= 1; ++gx)
        {
            for (int gy = -1; gy <= 1; ++gy)
            {
                int cellX = static_cast<int>(x * params.points) + gx;
                int cellY = static_cast<int>(y * params.points) + gy;

                // Generate random point in cell
                std::mt19937 rng(hash(cellX, cellY, params.seed));
                std::uniform_real_distribution<float> dist(0.0f, 1.0f);

                float pointX = (cellX + dist(rng) * params.jitter) / params.points;
                float pointY = (cellY + dist(rng) * params.jitter) / params.points;

                float dx = x - pointX;
                float dy = y - pointY;
                float distance = std::sqrt(dx * dx + dy * dy);

                minDist = std::min(minDist, distance);
            }
        }

        return std::clamp(minDist, 0.0f, 1.0f);
    }

    // ============================================================================
    // Helper Method Implementations
    // ============================================================================

    float ProceduralTextureGenerator::fade(float t)
    {
        return t * t * t * (t * (t * 6 - 15) + 10);
    }

    float ProceduralTextureGenerator::lerp(float t, float a, float b)
    {
        return a + t * (b - a);
    }

    float ProceduralTextureGenerator::grad(uint32_t hash, float x, float y)
    {
        uint32_t h = hash & 15;
        float u = h < 8 ? x : y;
        float v = h < 4 ? y : (h == 12 || h == 14 ? x : 0);
        return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
    }

    uint32_t ProceduralTextureGenerator::hash(uint32_t x, uint32_t y, uint32_t seed)
    {
        uint32_t h = seed;
        h ^= x + 0x9e3779b9 + (h << 6) + (h >> 2);
        h ^= y + 0x9e3779b9 + (h << 6) + (h >> 2);
        return h;
    }

    // ============================================================================
    // Pattern Evaluation Methods
    // ============================================================================

    Color ProceduralTextureGenerator::evaluateCheckerboard(const PatternParams &params, float x, float y)
    {
        int checkX = static_cast<int>(x * params.frequency);
        int checkY = static_cast<int>(y * params.frequency);
        return ((checkX + checkY) % 2 == 0) ? params.color1 : params.color2;
    }

    Color ProceduralTextureGenerator::evaluateStripes(const PatternParams &params, float x, float y)
    {
        float value = std::sin(x * params.frequency * 2.0f * M_PI + params.phase);
        return (value > 0) ? params.color1 : params.color2;
    }

    Color ProceduralTextureGenerator::evaluateDots(const PatternParams &params, float x, float y)
    {
        float fx = std::fmod(x * params.frequency, 1.0f);
        float fy = std::fmod(y * params.frequency, 1.0f);
        float dist = std::sqrt((fx - 0.5f) * (fx - 0.5f) + (fy - 0.5f) * (fy - 0.5f));
        return (dist < params.thickness * 0.5f) ? params.color1 : params.color2;
    }

    Color ProceduralTextureGenerator::evaluateGrid(const PatternParams &params, float x, float y)
    {
        float fx = std::fmod(x * params.frequency, 1.0f);
        float fy = std::fmod(y * params.frequency, 1.0f);
        bool isLine = (fx < params.thickness) || (fy < params.thickness);
        return isLine ? params.color1 : params.color2;
    }

    Color ProceduralTextureGenerator::evaluateSpiral(const PatternParams &params, float x, float y)
    {
        float dx = x - 0.5f;
        float dy = y - 0.5f;
        float angle = std::atan2(dy, dx);
        float radius = std::sqrt(dx * dx + dy * dy);

        float spiralValue = std::sin(angle * params.frequency + radius * params.amplitude * 20.0f + params.phase);
        return (spiralValue > 0) ? params.color1 : params.color2;
    }

    Color ProceduralTextureGenerator::evaluateWaves(const PatternParams &params, float x, float y)
    {
        float wave1 = std::sin(x * params.frequency * 2.0f * M_PI + params.phase);
        float wave2 = std::sin(y * params.frequency * 2.0f * M_PI + params.phase);
        float combined = (wave1 + wave2) * 0.5f * params.amplitude;

        float t = (combined + 1.0f) * 0.5f;
        return Color::lerp(params.color2, params.color1, t);
    }

    // ============================================================================
    // Internal Generation Methods
    // ============================================================================

    TextureData ProceduralTextureGenerator::generateNoiseTexture(const TextureParams &params)
    {
        auto texture = generateNoise(params.noise, params.width, params.height);
        texture.name = params.name;
        applyPostProcessing(texture, params);
        return texture;
    }

    TextureData ProceduralTextureGenerator::generateGradientTexture(const TextureParams &params)
    {
        auto texture = generateGradient(params.gradient, params.width, params.height);
        texture.name = params.name;
        applyPostProcessing(texture, params);
        return texture;
    }

    TextureData ProceduralTextureGenerator::generatePatternTexture(const TextureParams &params)
    {
        auto texture = generatePattern(params.pattern, params.width, params.height);
        texture.name = params.name;
        applyPostProcessing(texture, params);
        return texture;
    }

    TextureData ProceduralTextureGenerator::generateCompositeTexture(const TextureParams &params)
    {
        if (params.layers.empty())
        {
            return TextureData(params.width, params.height);
        }

        std::vector<TextureData> layerTextures;
        layerTextures.reserve(params.layers.size());

        for (const auto &layer : params.layers)
        {
            layerTextures.push_back(generateTexture(layer));
        }

        auto texture = generateComposite(layerTextures, params.blendModes, params.opacities);
        texture.name = params.name;
        applyPostProcessing(texture, params);
        return texture;
    }

    // ============================================================================
    // Parsing Methods
    // ============================================================================

    TextureParams::Type ProceduralTextureGenerator::parseTextureType(const std::string &typeStr)
    {
        if (typeStr == "noise")
            return TextureParams::Type::Noise;
        if (typeStr == "gradient")
            return TextureParams::Type::Gradient;
        if (typeStr == "pattern")
            return TextureParams::Type::Pattern;
        if (typeStr == "composite")
            return TextureParams::Type::Composite;
        return TextureParams::Type::Noise;
    }

    NoiseParams::Type ProceduralTextureGenerator::parseNoiseType(const std::string &typeStr)
    {
        if (typeStr == "perlin")
            return NoiseParams::Type::Perlin;
        if (typeStr == "simplex")
            return NoiseParams::Type::Simplex;
        if (typeStr == "fractal")
            return NoiseParams::Type::Fractal;
        if (typeStr == "cellular")
            return NoiseParams::Type::Cellular;
        if (typeStr == "voronoi")
            return NoiseParams::Type::Voronoi;
        if (typeStr == "white")
            return NoiseParams::Type::White;
        return NoiseParams::Type::Perlin;
    }

    // Implementation of remaining parsing and processing methods would continue...
    // This represents the core functionality of the texture generator

} // namespace ProceduralTexture
#pragma once

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <cstdint>
#include <functional>

namespace ProceduralTexture
{

    // ============================================================================
    // Texture Data Structures
    // ============================================================================

    struct Color
    {
        uint8_t r, g, b, a;

        Color() : r(0), g(0), b(0), a(255) {}
        Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255)
            : r(red), g(green), b(blue), a(alpha) {}

        static Color lerp(const Color &a, const Color &b, float t);
        static Color fromFloat(float r, float g, float b, float a = 1.0f);
        static Color fromHSV(float h, float s, float v, float a = 1.0f);
    };

    struct TextureData
    {
        std::vector<Color> pixels;
        uint32_t width;
        uint32_t height;
        uint32_t channels;  // 3 for RGB, 4 for RGBA
        std::string format; // "RGB", "RGBA", "LUMINANCE", etc.
        std::string name;

        TextureData() : width(0), height(0), channels(4), format("RGBA") {}
        TextureData(uint32_t w, uint32_t h, const std::string &fmt = "RGBA");

        Color &getPixel(uint32_t x, uint32_t y);
        const Color &getPixel(uint32_t x, uint32_t y) const;
        void setPixel(uint32_t x, uint32_t y, const Color &color);

        // Utility methods
        void clear(const Color &color = Color(0, 0, 0, 0));
        void resize(uint32_t newWidth, uint32_t newHeight);
        std::vector<uint8_t> getRawData() const;
    };

    // ============================================================================
    // Noise and Pattern Parameters
    // ============================================================================

    struct NoiseParams
    {
        enum class Type
        {
            Perlin,
            Simplex,
            Fractal,
            Cellular,
            Voronoi,
            White
        };

        Type type = Type::Perlin;
        uint32_t seed = 12345;
        float frequency = 1.0f;
        float amplitude = 1.0f;
        uint32_t octaves = 4;
        float persistence = 0.5f;
        float lacunarity = 2.0f;

        // Cellular automata specific
        uint32_t iterations = 5;
        float threshold = 0.5f;

        // Voronoi specific
        uint32_t points = 16;
        float jitter = 1.0f;
    };

    struct GradientParams
    {
        enum class Type
        {
            Linear,
            Radial,
            Angular,
            Diamond
        };

        Type type = Type::Linear;
        std::vector<Color> colors;
        std::vector<float> stops;             // 0.0 to 1.0
        float angle = 0.0f;                   // For linear gradients (degrees)
        float centerX = 0.5f, centerY = 0.5f; // For radial/angular gradients
        float radius = 0.5f;                  // For radial gradients
        bool repeat = false;
    };

    struct PatternParams
    {
        enum class Type
        {
            Checkerboard,
            Stripes,
            Dots,
            Grid,
            Spiral,
            Waves
        };

        Type type = Type::Checkerboard;
        uint32_t frequency = 8; // Pattern repetitions
        Color color1 = Color(255, 255, 255, 255);
        Color color2 = Color(0, 0, 0, 255);
        float thickness = 0.5f; // Line thickness for stripes/grid
        float amplitude = 1.0f; // Wave amplitude
        float phase = 0.0f;     // Wave phase
    };

    // ============================================================================
    // Texture Generator Parameters
    // ============================================================================

    struct TextureParams
    {
        enum class Type
        {
            Noise,
            Gradient,
            Pattern,
            Composite
        };

        Type type = Type::Noise;
        uint32_t width = 256;
        uint32_t height = 256;
        std::string name = "procedural_texture";

        // Generator-specific parameters
        NoiseParams noise;
        GradientParams gradient;
        PatternParams pattern;

        // Composite blending
        enum class BlendMode
        {
            Replace,
            Add,
            Multiply,
            Overlay,
            Screen,
            Darken,
            Lighten
        };

        std::vector<TextureParams> layers; // For composite textures
        std::vector<BlendMode> blendModes;
        std::vector<float> opacities;

        // Post-processing
        bool normalize = false;
        bool invert = false;
        float brightness = 0.0f; // -1.0 to 1.0
        float contrast = 1.0f;   // 0.0 to 2.0
        float gamma = 1.0f;      // Gamma correction
    };

    // ============================================================================
    // Main Texture Generator Class
    // ============================================================================

    class ProceduralTextureGenerator
    {
    public:
        // Construction and Configuration
        ProceduralTextureGenerator() = default;
        ~ProceduralTextureGenerator() = default;

        // Primary generation methods
        static TextureData generateTexture(const TextureParams &params);
        static TextureData generateFromParameters(const std::string &type,
                                                  const std::map<std::string, std::string> &parameters);

        // Specific generators
        static TextureData generateNoise(const NoiseParams &params, uint32_t width, uint32_t height);
        static TextureData generateGradient(const GradientParams &params, uint32_t width, uint32_t height);
        static TextureData generatePattern(const PatternParams &params, uint32_t width, uint32_t height);
        static TextureData generateComposite(const std::vector<TextureData> &layers,
                                             const std::vector<TextureParams::BlendMode> &blendModes,
                                             const std::vector<float> &opacities);

        // Noise generation methods
        static float perlinNoise(float x, float y, uint32_t seed = 12345);
        static float simplexNoise(float x, float y, uint32_t seed = 12345);
        static float fractalNoise(float x, float y, const NoiseParams &params);
        static float cellularNoise(float x, float y, const NoiseParams &params);
        static float voronoiNoise(float x, float y, const NoiseParams &params);

        // Utility and helper methods
        static TextureParams::Type parseTextureType(const std::string &typeStr);
        static NoiseParams::Type parseNoiseType(const std::string &typeStr);
        static GradientParams::Type parseGradientType(const std::string &typeStr);
        static PatternParams::Type parsePatternType(const std::string &typeStr);
        static TextureParams::BlendMode parseBlendMode(const std::string &modeStr);

        static std::string textureTypeToString(TextureParams::Type type);
        static std::string noiseTypeToString(NoiseParams::Type type);
        static std::string gradientTypeToString(GradientParams::Type type);
        static std::string patternTypeToString(PatternParams::Type type);
        static std::string blendModeToString(TextureParams::BlendMode mode);

        // Parameter validation and estimation
        static bool validateParameters(const TextureParams &params);
        static uint32_t estimateMemoryUsage(const TextureParams &params);
        static uint32_t estimateGenerationTime(const TextureParams &params); // In milliseconds

    private:
        // Internal generation helpers
        static TextureData generateNoiseTexture(const TextureParams &params);
        static TextureData generateGradientTexture(const TextureParams &params);
        static TextureData generatePatternTexture(const TextureParams &params);
        static TextureData generateCompositeTexture(const TextureParams &params);

        // Noise implementation helpers
        static float fade(float t);
        static float lerp(float t, float a, float b);
        static float grad(uint32_t hash, float x, float y);
        static uint32_t hash(uint32_t x, uint32_t y, uint32_t seed);

        // Gradient implementation helpers
        static Color evaluateGradient(const GradientParams &params, float t);
        static float calculateGradientPosition(const GradientParams &params, float x, float y);

        // Pattern implementation helpers
        static Color evaluateCheckerboard(const PatternParams &params, float x, float y);
        static Color evaluateStripes(const PatternParams &params, float x, float y);
        static Color evaluateDots(const PatternParams &params, float x, float y);
        static Color evaluateGrid(const PatternParams &params, float x, float y);
        static Color evaluateSpiral(const PatternParams &params, float x, float y);
        static Color evaluateWaves(const PatternParams &params, float x, float y);

        // Blending and compositing
        static Color blendColors(const Color &base, const Color &overlay,
                                 TextureParams::BlendMode mode, float opacity);
        static Color blendAdd(const Color &a, const Color &b);
        static Color blendMultiply(const Color &a, const Color &b);
        static Color blendOverlay(const Color &a, const Color &b);
        static Color blendScreen(const Color &a, const Color &b);
        static Color blendDarken(const Color &a, const Color &b);
        static Color blendLighten(const Color &a, const Color &b);

        // Post-processing
        static void applyPostProcessing(TextureData &texture, const TextureParams &params);
        static void applyNormalization(TextureData &texture);
        static void applyInversion(TextureData &texture);
        static void applyBrightness(TextureData &texture, float brightness);
        static void applyContrast(TextureData &texture, float contrast);
        static void applyGamma(TextureData &texture, float gamma);

        // XML parameter parsing helpers
        static NoiseParams parseNoiseParameters(const std::map<std::string, std::string> &params);
        static GradientParams parseGradientParameters(const std::map<std::string, std::string> &params);
        static PatternParams parsePatternParameters(const std::map<std::string, std::string> &params);
        static std::vector<Color> parseColorList(const std::string &colorStr);
        static Color parseColor(const std::string &colorStr);

        // Validation helpers
        static bool isValidDimension(uint32_t dimension);
        static bool isValidColorStop(float stop);
        static bool isValidBlendMode(TextureParams::BlendMode mode);
    };

} // namespace ProceduralTexture
#include "VoxelMeshGenerator.h"
#include <cmath>
#include <algorithm>
#include <unordered_map>

// ============================================================================
// Public Generation Methods
// ============================================================================

VoxelMesh::MeshData VoxelMeshGenerator::generatePrimitive(const VoxelMesh::VoxelParams &params)
{
    switch (params.type)
    {
    case VoxelMesh::VoxelType::Cube:
        return generateCube(params);
    case VoxelMesh::VoxelType::Sphere:
        return generateSphere(params);
    case VoxelMesh::VoxelType::Cylinder:
        return generateCylinder(params);
    case VoxelMesh::VoxelType::Plane:
        return generatePlane(params);
    default:
        return generateCube(params); // Default fallback
    }
}

VoxelMesh::MeshData VoxelMeshGenerator::generateCompound(const VoxelMesh::CompoundParams &params)
{
    std::vector<VoxelMesh::MeshData> meshes;
    meshes.reserve(params.parts.size());

    for (const auto &part : params.parts)
    {
        auto mesh = generatePrimitive(part.primitive);
        transformMesh(mesh, part.offset, part.scale);
        meshes.push_back(std::move(mesh));
    }

    auto result = mergeMeshes(meshes);
    result.name = params.name;
    optimizeMesh(result);
    return result;
}

VoxelMesh::MeshData VoxelMeshGenerator::generateFromParameters(const std::string &type,
                                                               const std::map<std::string, std::string> &parameters)
{
    VoxelMesh::VoxelParams params;
    params.type = parseVoxelType(type);

    // Parse common parameters
    auto it = parameters.find("size");
    if (it != parameters.end())
    {
        params.size = std::stof(it->second);
    }

    it = parameters.find("radius");
    if (it != parameters.end())
    {
        params.radius = std::stof(it->second);
    }

    it = parameters.find("height");
    if (it != parameters.end())
    {
        params.height = std::stof(it->second);
    }

    it = parameters.find("subdivisions");
    if (it != parameters.end())
    {
        params.subdivisions = static_cast<uint32_t>(std::stoi(it->second));
    }

    return generatePrimitive(params);
}

// ============================================================================
// Utility Methods
// ============================================================================

VoxelMesh::VoxelType VoxelMeshGenerator::parseVoxelType(const std::string &typeStr)
{
    if (typeStr == "cube")
        return VoxelMesh::VoxelType::Cube;
    if (typeStr == "sphere")
        return VoxelMesh::VoxelType::Sphere;
    if (typeStr == "cylinder")
        return VoxelMesh::VoxelType::Cylinder;
    if (typeStr == "plane")
        return VoxelMesh::VoxelType::Plane;
    return VoxelMesh::VoxelType::Cube; // Default fallback
}

std::string VoxelMeshGenerator::voxelTypeToString(VoxelMesh::VoxelType type)
{
    switch (type)
    {
    case VoxelMesh::VoxelType::Cube:
        return "cube";
    case VoxelMesh::VoxelType::Sphere:
        return "sphere";
    case VoxelMesh::VoxelType::Cylinder:
        return "cylinder";
    case VoxelMesh::VoxelType::Plane:
        return "plane";
    default:
        return "cube";
    }
}

uint32_t VoxelMeshGenerator::estimateVertexCount(const VoxelMesh::VoxelParams &params)
{
    switch (params.type)
    {
    case VoxelMesh::VoxelType::Cube:
        return 24; // 6 faces * 4 vertices
    case VoxelMesh::VoxelType::Sphere:
        return params.subdivisions * params.subdivisions * 6; // Approximation for icosphere
    case VoxelMesh::VoxelType::Cylinder:
        return params.subdivisions * 4 + 2; // Side faces + top/bottom
    case VoxelMesh::VoxelType::Plane:
        return 4;
    default:
        return 24;
    }
}

// ============================================================================
// Primitive Generation Implementation
// ============================================================================

VoxelMesh::MeshData VoxelMeshGenerator::generateCube(const VoxelMesh::VoxelParams &params)
{
    VoxelMesh::MeshData mesh;
    mesh.name = "cube";

    const float halfSize = params.size * 0.5f;
    const Math::float3 center = params.center;

    // Define cube faces with normals
    struct Face
    {
        Math::float3 vertices[4];
        Math::float3 normal;
    };

    Face faces[6] = {
        // Front face (+Z)
        {{{-halfSize, -halfSize, halfSize}, {halfSize, -halfSize, halfSize}, {halfSize, halfSize, halfSize}, {-halfSize, halfSize, halfSize}},
         {0, 0, 1}},
        // Back face (-Z)
        {{{halfSize, -halfSize, -halfSize}, {-halfSize, -halfSize, -halfSize}, {-halfSize, halfSize, -halfSize}, {halfSize, halfSize, -halfSize}},
         {0, 0, -1}},
        // Right face (+X)
        {{{halfSize, -halfSize, halfSize}, {halfSize, -halfSize, -halfSize}, {halfSize, halfSize, -halfSize}, {halfSize, halfSize, halfSize}},
         {1, 0, 0}},
        // Left face (-X)
        {{{-halfSize, -halfSize, -halfSize}, {-halfSize, -halfSize, halfSize}, {-halfSize, halfSize, halfSize}, {-halfSize, halfSize, -halfSize}},
         {-1, 0, 0}},
        // Top face (+Y)
        {{{-halfSize, halfSize, halfSize}, {halfSize, halfSize, halfSize}, {halfSize, halfSize, -halfSize}, {-halfSize, halfSize, -halfSize}},
         {0, 1, 0}},
        // Bottom face (-Y)
        {{{-halfSize, -halfSize, -halfSize}, {halfSize, -halfSize, -halfSize}, {halfSize, -halfSize, halfSize}, {-halfSize, -halfSize, halfSize}},
         {0, -1, 0}}};

    // Generate vertices and indices for each face
    for (int face = 0; face < 6; ++face)
    {
        Math::float3 v0 = Math::add(faces[face].vertices[0], center);
        Math::float3 v1 = Math::add(faces[face].vertices[1], center);
        Math::float3 v2 = Math::add(faces[face].vertices[2], center);
        Math::float3 v3 = Math::add(faces[face].vertices[3], center);

        addQuad(mesh, v0, v1, v2, v3, faces[face].normal);
    }

    return mesh;
}

VoxelMesh::MeshData VoxelMeshGenerator::generateSphere(const VoxelMesh::VoxelParams &params)
{
    VoxelMesh::MeshData mesh;
    mesh.name = "sphere";

    if (params.subdivisions <= 1)
    {
        // Generate basic icosphere for low subdivision
        generateIcosphere(mesh, params);
    }
    else
    {
        // Generate UV sphere for higher subdivisions
        const uint32_t rings = params.subdivisions;
        const uint32_t sectors = params.subdivisions * 2;
        const float radius = params.radius;
        const Math::float3 center = params.center;

        mesh.vertices.reserve((rings + 1) * (sectors + 1));
        mesh.indices.reserve(rings * sectors * 6);

        // Generate vertices
        for (uint32_t r = 0; r <= rings; ++r)
        {
            float y = radius * std::cos(Math::PI * r / rings);
            float ringRadius = radius * std::sin(Math::PI * r / rings);

            for (uint32_t s = 0; s <= sectors; ++s)
            {
                float x = ringRadius * std::cos(2.0f * Math::PI * s / sectors);
                float z = ringRadius * std::sin(2.0f * Math::PI * s / sectors);

                Math::float3 position = Math::add({x, y, z}, center);
                Math::float3 normal = Math::normalize({x, y, z});
                Math::float2 uv = {static_cast<float>(s) / sectors, static_cast<float>(r) / rings};

                mesh.vertices.emplace_back(position, normal, uv);
            }
        }

        // Generate indices
        for (uint32_t r = 0; r < rings; ++r)
        {
            for (uint32_t s = 0; s < sectors; ++s)
            {
                uint32_t current = r * (sectors + 1) + s;
                uint32_t next = current + sectors + 1;

                // Two triangles per quad
                mesh.indices.push_back(current);
                mesh.indices.push_back(next);
                mesh.indices.push_back(current + 1);

                mesh.indices.push_back(current + 1);
                mesh.indices.push_back(next);
                mesh.indices.push_back(next + 1);
            }
        }
    }

    return mesh;
}

VoxelMesh::MeshData VoxelMeshGenerator::generateCylinder(const VoxelMesh::VoxelParams &params)
{
    VoxelMesh::MeshData mesh;
    mesh.name = "cylinder";

    const float radius = params.radius;
    const float height = params.height;
    const float halfHeight = height * 0.5f;
    const uint32_t segments = std::max(3u, params.subdivisions * 8);
    const Math::float3 center = params.center;

    mesh.vertices.reserve(segments * 4 + 2);
    mesh.indices.reserve(segments * 12);

    // Generate side vertices
    for (uint32_t i = 0; i < segments; ++i)
    {
        float angle = 2.0f * Math::PI * i / segments;
        float x = radius * std::cos(angle);
        float z = radius * std::sin(angle);

        Math::float3 bottomPos = Math::add({x, -halfHeight, z}, center);
        Math::float3 topPos = Math::add({x, halfHeight, z}, center);
        Math::float3 normal = Math::normalize({x, 0, z});
        Math::float2 uvBottom = {static_cast<float>(i) / segments, 0.0f};
        Math::float2 uvTop = {static_cast<float>(i) / segments, 1.0f};

        mesh.vertices.emplace_back(bottomPos, normal, uvBottom);
        mesh.vertices.emplace_back(topPos, normal, uvTop);
    }

    // Add center vertices for caps
    uint32_t bottomCenterIdx = mesh.vertices.size();
    mesh.vertices.emplace_back(Math::add({0, -halfHeight, 0}, center), {0, -1, 0}, {0.5f, 0.5f});
    uint32_t topCenterIdx = mesh.vertices.size();
    mesh.vertices.emplace_back(Math::add({0, halfHeight, 0}, center), {0, 1, 0}, {0.5f, 0.5f});

    // Generate side faces
    for (uint32_t i = 0; i < segments; ++i)
    {
        uint32_t current = i * 2;
        uint32_t next = ((i + 1) % segments) * 2;

        // Two triangles per side quad
        mesh.indices.push_back(current);
        mesh.indices.push_back(next);
        mesh.indices.push_back(current + 1);

        mesh.indices.push_back(current + 1);
        mesh.indices.push_back(next);
        mesh.indices.push_back(next + 1);
    }

    // Generate cap faces
    for (uint32_t i = 0; i < segments; ++i)
    {
        uint32_t current = i * 2;
        uint32_t next = ((i + 1) % segments) * 2;

        // Bottom cap
        mesh.indices.push_back(bottomCenterIdx);
        mesh.indices.push_back(next);
        mesh.indices.push_back(current);

        // Top cap
        mesh.indices.push_back(topCenterIdx);
        mesh.indices.push_back(current + 1);
        mesh.indices.push_back(next + 1);
    }

    return mesh;
}

VoxelMesh::MeshData VoxelMeshGenerator::generatePlane(const VoxelMesh::VoxelParams &params)
{
    VoxelMesh::MeshData mesh;
    mesh.name = "plane";

    const float halfSize = params.size * 0.5f;
    const Math::float3 center = params.center;

    Math::float3 v0 = Math::add({-halfSize, 0, -halfSize}, center);
    Math::float3 v1 = Math::add({halfSize, 0, -halfSize}, center);
    Math::float3 v2 = Math::add({halfSize, 0, halfSize}, center);
    Math::float3 v3 = Math::add({-halfSize, 0, halfSize}, center);

    addQuad(mesh, v0, v1, v2, v3, {0, 1, 0});

    return mesh;
}

// ============================================================================
// Helper Methods Implementation
// ============================================================================

void VoxelMeshGenerator::addQuad(VoxelMesh::MeshData &mesh,
                                 const Math::float3 &v0, const Math::float3 &v1,
                                 const Math::float3 &v2, const Math::float3 &v3,
                                 const Math::float3 &normal)
{
    uint32_t startIdx = mesh.vertices.size();

    // Add vertices with UVs
    mesh.vertices.emplace_back(v0, normal, Math::float2{0, 0});
    mesh.vertices.emplace_back(v1, normal, Math::float2{1, 0});
    mesh.vertices.emplace_back(v2, normal, Math::float2{1, 1});
    mesh.vertices.emplace_back(v3, normal, Math::float2{0, 1});

    // Add indices for two triangles
    mesh.indices.push_back(startIdx);
    mesh.indices.push_back(startIdx + 1);
    mesh.indices.push_back(startIdx + 2);

    mesh.indices.push_back(startIdx);
    mesh.indices.push_back(startIdx + 2);
    mesh.indices.push_back(startIdx + 3);
}

void VoxelMeshGenerator::addTriangle(VoxelMesh::MeshData &mesh,
                                     const Math::float3 &v0, const Math::float3 &v1, const Math::float3 &v2,
                                     const Math::float3 &normal)
{
    uint32_t startIdx = mesh.vertices.size();

    mesh.vertices.emplace_back(v0, normal, Math::float2{0, 0});
    mesh.vertices.emplace_back(v1, normal, Math::float2{1, 0});
    mesh.vertices.emplace_back(v2, normal, Math::float2{0.5f, 1});

    mesh.indices.push_back(startIdx);
    mesh.indices.push_back(startIdx + 1);
    mesh.indices.push_back(startIdx + 2);
}

Math::float2 VoxelMeshGenerator::calculateSphericalUV(const Math::float3 &position)
{
    Math::float3 normalized = Math::normalize(position);
    float u = 0.5f + std::atan2(normalized.z, normalized.x) / (2.0f * Math::PI);
    float v = 0.5f - std::asin(normalized.y) / Math::PI;
    return {u, v};
}

Math::float2 VoxelMeshGenerator::calculateCubicUV(const Math::float3 &position, int faceIndex)
{
    // Simple planar projection based on face
    switch (faceIndex)
    {
    case 0:
    case 1: // Front/Back
        return {(position.x + 1.0f) * 0.5f, (position.y + 1.0f) * 0.5f};
    case 2:
    case 3: // Right/Left
        return {(position.z + 1.0f) * 0.5f, (position.y + 1.0f) * 0.5f};
    case 4:
    case 5: // Top/Bottom
        return {(position.x + 1.0f) * 0.5f, (position.z + 1.0f) * 0.5f};
    default:
        return {0.5f, 0.5f};
    }
}

void VoxelMeshGenerator::generateIcosphere(VoxelMesh::MeshData &mesh, const VoxelMesh::VoxelParams &params)
{
    // Basic icosphere implementation for low-poly spheres
    const float t = (1.0f + std::sqrt(5.0f)) / 2.0f; // Golden ratio
    const float radius = params.radius;
    const Math::float3 center = params.center;

    // Create icosahedron vertices
    std::vector<Math::float3> vertices = {
        {-1, t, 0}, {1, t, 0}, {-1, -t, 0}, {1, -t, 0}, {0, -1, t}, {0, 1, t}, {0, -1, -t}, {0, 1, -t}, {t, 0, -1}, {t, 0, 1}, {-t, 0, -1}, {-t, 0, 1}};

    // Normalize and scale
    for (auto &v : vertices)
    {
        v = Math::mul(Math::normalize(v), radius);
        v = Math::add(v, center);
    }

    // Create faces (20 triangles)
    std::vector<std::array<uint32_t, 3>> faces = {
        {0, 11, 5}, {0, 5, 1}, {0, 1, 7}, {0, 7, 10}, {0, 10, 11}, {1, 5, 9}, {5, 11, 4}, {11, 10, 2}, {10, 7, 6}, {7, 1, 8}, {3, 9, 4}, {3, 4, 2}, {3, 2, 6}, {3, 6, 8}, {3, 8, 9}, {4, 9, 5}, {2, 4, 11}, {6, 2, 10}, {8, 6, 7}, {9, 8, 1}};

    // Add vertices and indices
    for (const auto &vertex : vertices)
    {
        Math::float3 normal = Math::normalize(Math::sub(vertex, center));
        Math::float2 uv = calculateSphericalUV(normal);
        mesh.vertices.emplace_back(vertex, normal, uv);
    }

    for (const auto &face : faces)
    {
        mesh.indices.push_back(face[0]);
        mesh.indices.push_back(face[1]);
        mesh.indices.push_back(face[2]);
    }
}

VoxelMesh::MeshData VoxelMeshGenerator::mergeMeshes(const std::vector<VoxelMesh::MeshData> &meshes)
{
    VoxelMesh::MeshData result;

    if (meshes.empty())
    {
        return result;
    }

    // Calculate total size
    uint32_t totalVertices = 0;
    uint32_t totalIndices = 0;
    for (const auto &mesh : meshes)
    {
        totalVertices += mesh.vertices.size();
        totalIndices += mesh.indices.size();
    }

    result.vertices.reserve(totalVertices);
    result.indices.reserve(totalIndices);

    // Merge meshes
    uint32_t vertexOffset = 0;
    for (const auto &mesh : meshes)
    {
        // Copy vertices
        result.vertices.insert(result.vertices.end(), mesh.vertices.begin(), mesh.vertices.end());

        // Copy indices with offset
        for (uint32_t index : mesh.indices)
        {
            result.indices.push_back(index + vertexOffset);
        }

        vertexOffset += mesh.vertices.size();
    }

    result.name = "compound";
    return result;
}

void VoxelMeshGenerator::transformMesh(VoxelMesh::MeshData &mesh, const Math::float3 &offset, const Math::float3 &scale)
{
    for (auto &vertex : mesh.vertices)
    {
        // Apply scale
        vertex.position.x *= scale.x;
        vertex.position.y *= scale.y;
        vertex.position.z *= scale.z;

        // Apply offset
        vertex.position = Math::add(vertex.position, offset);
    }
}

void VoxelMeshGenerator::calculateNormals(VoxelMesh::MeshData &mesh)
{
    // Calculate face normals and accumulate vertex normals
    for (size_t i = 0; i < mesh.indices.size(); i += 3)
    {
        uint32_t i0 = mesh.indices[i];
        uint32_t i1 = mesh.indices[i + 1];
        uint32_t i2 = mesh.indices[i + 2];

        Math::float3 v0 = mesh.vertices[i0].position;
        Math::float3 v1 = mesh.vertices[i1].position;
        Math::float3 v2 = mesh.vertices[i2].position;

        Math::float3 edge1 = Math::sub(v1, v0);
        Math::float3 edge2 = Math::sub(v2, v0);
        Math::float3 normal = Math::normalize(Math::cross(edge1, edge2));

        mesh.vertices[i0].normal = Math::add(mesh.vertices[i0].normal, normal);
        mesh.vertices[i1].normal = Math::add(mesh.vertices[i1].normal, normal);
        mesh.vertices[i2].normal = Math::add(mesh.vertices[i2].normal, normal);
    }

    // Normalize accumulated normals
    for (auto &vertex : mesh.vertices)
    {
        vertex.normal = Math::normalize(vertex.normal);
    }
}

void VoxelMeshGenerator::optimizeMesh(VoxelMesh::MeshData &mesh)
{
    // Simple optimization: remove unused vertices
    // More sophisticated optimization could be added here
    if (mesh.vertices.empty() || mesh.indices.empty())
    {
        return;
    }

    // For now, just ensure normals are properly calculated
    calculateNormals(mesh);
}
#pragma once
#include "../math/MathUtils.h"
#include <vector>
#include <string>
#include <map>

/**
 * @file VoxelMeshGenerator.h
 * @brief Generic voxel-based mesh generation system
 *
 * This generator creates all mesh types using voxel primitives as building blocks.
 * Supports cubes, spheres, cylinders, and compound meshes built from multiple primitives.
 * All generation is deterministic and configurable through parameters.
 */

namespace VoxelMesh
{

    /**
     * @brief Vertex data structure for generated meshes
     */
    struct Vertex
    {
        Math::float3 position;
        Math::float3 normal;
        Math::float2 uv;

        Vertex() = default;
        Vertex(const Math::float3 &pos, const Math::float3 &norm, const Math::float2 &texCoord)
            : position(pos), normal(norm), uv(texCoord) {}
    };

    /**
     * @brief Generated mesh data
     */
    struct MeshData
    {
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
        std::string name;

        void clear()
        {
            vertices.clear();
            indices.clear();
            name.clear();
        }

        bool isEmpty() const
        {
            return vertices.empty() || indices.empty();
        }
    };

    /**
     * @brief Voxel primitive types
     */
    enum class VoxelType
    {
        Cube,
        Sphere,
        Cylinder,
        Plane
    };

    /**
     * @brief Parameters for voxel primitive generation
     */
    struct VoxelParams
    {
        VoxelType type = VoxelType::Cube;
        float size = 1.0f;            // Size for cubes/planes
        float radius = 1.0f;          // Radius for spheres/cylinders
        float height = 1.0f;          // Height for cylinders
        uint32_t subdivisions = 1;    // Level of detail
        Math::float3 center{0, 0, 0}; // Center position

        VoxelParams() = default;
        VoxelParams(VoxelType t, float s = 1.0f) : type(t), size(s), radius(s) {}
    };

    /**
     * @brief Parameters for compound mesh (multiple primitives)
     */
    struct CompoundPart
    {
        VoxelParams primitive;
        Math::float3 offset{0, 0, 0};
        Math::float3 scale{1, 1, 1};
        std::string name;

        CompoundPart() = default;
        CompoundPart(const VoxelParams &prim, const Math::float3 &pos = {0, 0, 0})
            : primitive(prim), offset(pos) {}
    };

    /**
     * @brief Parameters for compound meshes
     */
    struct CompoundParams
    {
        std::vector<CompoundPart> parts;
        std::string name;

        void addPart(const CompoundPart &part)
        {
            parts.push_back(part);
        }

        void addPart(const VoxelParams &primitive, const Math::float3 &offset = {0, 0, 0})
        {
            parts.emplace_back(primitive, offset);
        }
    };

} // namespace VoxelMesh

/**
 * @brief Generic voxel mesh generator
 *
 * Creates meshes from voxel primitives with configurable parameters.
 * All shapes are built from the same base system for consistency.
 */
class VoxelMeshGenerator
{
public:
    VoxelMeshGenerator() = default;
    ~VoxelMeshGenerator() = default;

    // ============================================================================
    // Primary Generation Methods
    // ============================================================================

    /**
     * @brief Generate a single voxel primitive
     * @param params Primitive parameters
     * @return Generated mesh data
     */
    VoxelMesh::MeshData generatePrimitive(const VoxelMesh::VoxelParams &params);

    /**
     * @brief Generate a compound mesh from multiple primitives
     * @param params Compound mesh parameters
     * @return Generated mesh data
     */
    VoxelMesh::MeshData generateCompound(const VoxelMesh::CompoundParams &params);

    /**
     * @brief Generate mesh from string parameters (for XML parsing)
     * @param type Primitive type as string
     * @param parameters Parameter map
     * @return Generated mesh data
     */
    VoxelMesh::MeshData generateFromParameters(const std::string &type,
                                               const std::map<std::string, std::string> &parameters);

    // ============================================================================
    // Utility Methods
    // ============================================================================

    /**
     * @brief Parse voxel type from string
     * @param typeStr Type string ("cube", "sphere", etc.)
     * @return Voxel type enum
     */
    static VoxelMesh::VoxelType parseVoxelType(const std::string &typeStr);

    /**
     * @brief Get voxel type as string
     * @param type Voxel type enum
     * @return Type string
     */
    static std::string voxelTypeToString(VoxelMesh::VoxelType type);

    /**
     * @brief Calculate approximate vertex count for primitive
     * @param params Primitive parameters
     * @return Estimated vertex count
     */
    static uint32_t estimateVertexCount(const VoxelMesh::VoxelParams &params);

private:
    // ============================================================================
    // Primitive Generation Methods
    // ============================================================================

    VoxelMesh::MeshData generateCube(const VoxelMesh::VoxelParams &params);
    VoxelMesh::MeshData generateSphere(const VoxelMesh::VoxelParams &params);
    VoxelMesh::MeshData generateCylinder(const VoxelMesh::VoxelParams &params);
    VoxelMesh::MeshData generatePlane(const VoxelMesh::VoxelParams &params);

    // ============================================================================
    // Helper Methods
    // ============================================================================

    /**
     * @brief Add a quad to mesh data
     */
    void addQuad(VoxelMesh::MeshData &mesh,
                 const Math::float3 &v0, const Math::float3 &v1,
                 const Math::float3 &v2, const Math::float3 &v3,
                 const Math::float3 &normal);

    /**
     * @brief Add a triangle to mesh data
     */
    void addTriangle(VoxelMesh::MeshData &mesh,
                     const Math::float3 &v0, const Math::float3 &v1, const Math::float3 &v2,
                     const Math::float3 &normal);

    /**
     * @brief Calculate UV coordinates for a vertex on a sphere
     */
    Math::float2 calculateSphericalUV(const Math::float3 &position);

    /**
     * @brief Calculate UV coordinates for a vertex on a cube face
     */
    Math::float2 calculateCubicUV(const Math::float3 &position, int faceIndex);

    /**
     * @brief Generate vertices for subdivided icosphere
     */
    void generateIcosphere(VoxelMesh::MeshData &mesh, const VoxelMesh::VoxelParams &params);

    /**
     * @brief Merge multiple mesh data objects
     */
    VoxelMesh::MeshData mergeMeshes(const std::vector<VoxelMesh::MeshData> &meshes);

    /**
     * @brief Transform mesh vertices
     */
    void transformMesh(VoxelMesh::MeshData &mesh, const Math::float3 &offset, const Math::float3 &scale);

    /**
     * @brief Calculate normals for mesh (if not provided)
     */
    void calculateNormals(VoxelMesh::MeshData &mesh);

    /**
     * @brief Optimize mesh (remove duplicates, etc.)
     */
    void optimizeMesh(VoxelMesh::MeshData &mesh);
};
#include "core/EventBus.h"
#include "core/World.h"
#include "core/SimClock.h"
#include "core/AssetRegistry.h"
#include "core/AssetPackLoader.h"
#include "physics/ExponentialAirDensityModel.h"
#include "physics/PerlinWindModel.h"
#include "physics/ImpulseCollisionResolver.h"
#include "systems/PhysicsSystem.h"
#include "systems/InputSystem.h"
#include "systems/VehicleControlSystem.h"
#include "systems/BootstrapSystem.h"
#include "systems/WorldGenSystem.h"
#include "systems/ConsoleSystem.h"
#include "systems/VisualizationSystem.h"
#include "systems/AssetHotReloadSystem.h"
#include "platform/WinInputDevice.h"
#include "utils/PugiXmlParser.h"
#include "vehicles/DroneBuilder.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <windows.h>

// Window procedure for handling messages
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CLOSE:
            PostQuitMessage(0);
            return 0;
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            // Fill with dark blue background
            HBRUSH brush = CreateSolidBrush(RGB(20, 30, 50));
            FillRect(hdc, &ps.rcPaint, brush);
            DeleteObject(brush);
            EndPaint(hwnd, &ps);
            return 0;
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// Create a proper Windows window
HWND CreateSimulationWindow()
{
    const char CLASS_NAME[] = "FPV_FlightSimWindow";
    
    WNDCLASSA wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    if (!RegisterClassA(&wc))
    {
        return NULL;
    }

    HWND hwnd = CreateWindowExA(
        0,                      // Optional window styles
        CLASS_NAME,             // Window class
        "FPV Flight Sim - Procedural Earth World",    // Window text
        WS_OVERLAPPEDWINDOW,    // Window style
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,        // Size and position
        NULL,       // Parent window    
        NULL,       // Menu
        GetModuleHandle(NULL),  // Instance handle
        NULL        // Additional application data
    );

    if (hwnd != NULL)
    {
        ShowWindow(hwnd, SW_SHOW);
        UpdateWindow(hwnd);
    }

    return hwnd;
}

int main()
{
    // Simulation init
    EventBus eventBus;
    SimClock simClock(1.0f / 60.0f); // 60Hz physics
    World world(eventBus);

    // Asset system initialization
    AssetRegistry assetRegistry;
    AssetPackLoader assetLoader(assetRegistry);

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

    // Create proper window for visualization
    HWND hwnd = CreateSimulationWindow();
    if (hwnd == NULL)
    {
        std::cerr << "Failed to create window!" << std::endl;
        return -1;
    }

    // Asset and bootstrap systems
    auto bootstrapSystem = std::make_unique<BootstrapSystem>(eventBus, world, assetRegistry, assetLoader);
    auto worldGenSystem = std::make_unique<WorldGenSystem>(eventBus, world, assetRegistry);
    auto consoleSystem = std::make_unique<ConsoleSystem>(eventBus);
    auto visualizationSystem = std::make_unique<VisualizationSystem>(eventBus, world, hwnd);
    auto hotReloadSystem = std::make_unique<AssetHotReloadSystem>(assetRegistry, assetLoader);

    world.addSystem(std::move(bootstrapSystem));
    world.addSystem(std::move(worldGenSystem));
    world.addSystem(std::move(consoleSystem));
    world.addSystem(std::move(visualizationSystem));
    world.addSystem(std::move(hotReloadSystem));

    // Initialize bootstrap system (BootstrapSystem is at index 3)
    static_cast<BootstrapSystem *>(world.getSystems()[3].get())->Init();

    // Setup hot reload watching (AssetHotReloadSystem is at index 7)
    static_cast<AssetHotReloadSystem *>(world.getSystems()[7].get())->watchPackage("assets/packages/DeveloperPackage/package.xml");

    // Use builder to create entity
    // DroneBuilder droneBuilder(*xmlParser);
    // std::unique_ptr<Entity> drone = droneBuilder.build("configs/drone_default.xml", eventBus);
    // world.addEntity(std::move(drone));

    // Main simulation loop
    auto lastFrameTime = std::chrono::high_resolution_clock::now();
    float angle = 0.0f;
    MSG msg = {};
    bool running = true;
    
    while (running)
    {
        // Handle Windows messages
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                running = false;
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        
        if (!running) break;

        auto currentFrameTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> frameDeltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        simClock.tick(frameDeltaTime.count());
        while (simClock.shouldStepPhysics())
        {
            world.update(simClock.getFixedTimestep());
        }

        // Rendering simulation of rotating Earth sphere
        std::cout << "Earth sphere rotating at angle " << angle << " degrees" << std::endl;
        angle += 1.0f;

        std::this_thread::sleep_for(std::chrono::milliseconds(16)); // ~60 FPS
    }
    return 0;
}
#pragma once
#include <cmath>
#include <algorithm>
#include <stdint.h>

/**
 * @file MathUtils.h
 * @brief Comprehensive math utilities for 3D graphics, physics, and procedural generation
 *
 * Contains constants, utility functions, vector/quaternion operations, orbital mechanics,
 * random number generation, and specialized functions for the voxel busy indicator scene.
 */

namespace Math
{

    // ============================================================================
    // 1) Constants and basic utilities
    // ============================================================================

    constexpr float DegToRad = 0.017453292519943295f;
    constexpr float RadToDeg = 57.29577951308232f;
    constexpr float PI = 3.14159265358979323846f;
    constexpr float TAU = 6.28318530717958647692f; // 2*PI

    inline float saturate(float x) { return std::min(1.f, std::max(0.f, x)); }
    inline float clamp(float x, float a, float b) { return std::min(b, std::max(a, x)); }
    inline float lerp(float a, float b, float t) { return a + (b - a) * t; }
    inline float invLerp(float a, float b, float x) { return (x - a) / (b - a); }
    inline float remap(float i0, float i1, float o0, float o1, float x)
    {
        return lerp(o0, o1, saturate(invLerp(i0, i1, x)));
    }

    inline float smoothstep(float a, float b, float x)
    {
        float t = saturate(invLerp(a, b, x));
        return t * t * (3.f - 2.f * t);
    }

    inline float smootherstep(float a, float b, float x)
    {
        float t = saturate(invLerp(a, b, x));
        return t * t * t * (t * (6.f * t - 15.f) + 10.f);
    }

    // ============================================================================
    // 2) Random & hashing (deterministic per seed)
    // ============================================================================

    /**
     * @brief PCG-like quick hash function for deterministic random generation
     * @param x Input value to hash
     * @return Hashed 32-bit unsigned integer
     */
    inline uint32_t hash_u32(uint32_t x)
    {
        x ^= x >> 16;
        x *= 0x7feb352dU;
        x ^= x >> 15;
        x *= 0x846ca68bU;
        x ^= x >> 16;
        return x;
    }

    /**
     * @brief Generate random float in [0,1) range using hash-based PRNG
     * @param state Reference to PRNG state (modified)
     * @return Random float in [0,1) range
     */
    inline float rand01(uint32_t &state)
    {
        state = hash_u32(state);
        return (state >> 8) * (1.f / 16777216.f); // 24-bit mantissa
    }

    /**
     * @brief Sample from exponential distribution for Poisson inter-arrival times
     * @param u Uniform random value in [0,1)
     * @param lambda Rate parameter (events per unit time)
     * @return Time until next event
     */
    inline float sample_exponential(float u, float lambda)
    {
        return -std::log(std::max(u, 1e-7f)) / lambda;
    }

    // ============================================================================
    // 3) Vector operations
    // ============================================================================

    /**
     * @brief 2D vector structure with basic operations
     */
    struct float2
    {
        float x, y;

        float2() : x(0), y(0) {}
        float2(float x_, float y_) : x(x_), y(y_) {}

        float2 operator+(const float2 &other) const { return {x + other.x, y + other.y}; }
        float2 operator-(const float2 &other) const { return {x - other.x, y - other.y}; }
        float2 operator*(float s) const { return {x * s, y * s}; }
        float2 &operator+=(const float2 &other)
        {
            x += other.x;
            y += other.y;
            return *this;
        }
    };

    /**
     * @brief 3D vector structure with basic operations
     */
    struct float3
    {
        float x, y, z;

        float3() : x(0), y(0), z(0) {}
        float3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}

        float3 operator+(const float3 &other) const { return {x + other.x, y + other.y, z + other.z}; }
        float3 operator-(const float3 &other) const { return {x - other.x, y - other.y, z - other.z}; }
        float3 operator*(float s) const { return {x * s, y * s, z * s}; }
        float3 &operator+=(const float3 &other)
        {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }
    };

    /**
     * @brief 4D vector structure with basic operations (useful for quaternions and colors)
     */
    struct float4
    {
        float x, y, z, w;

        float4() : x(0), y(0), z(0), w(0) {}
        float4(float x_, float y_, float z_, float w_) : x(x_), y(y_), z(z_), w(w_) {}

        float4 operator+(const float4 &other) const { return {x + other.x, y + other.y, z + other.z, w + other.w}; }
        float4 operator-(const float4 &other) const { return {x - other.x, y - other.y, z - other.z, w - other.w}; }
        float4 operator*(float s) const { return {x * s, y * s, z * s, w * s}; }
        float4 &operator+=(const float4 &other)
        {
            x += other.x;
            y += other.y;
            z += other.z;
            w += other.w;
            return *this;
        }
    };

    inline float2 add(const float2 &a, const float2 &b) { return {a.x + b.x, a.y + b.y}; }
    inline float2 sub(const float2 &a, const float2 &b) { return {a.x - b.x, a.y - b.y}; }
    inline float2 mul(const float2 &a, float s) { return {a.x * s, a.y * s}; }
    inline float dot(const float2 &a, const float2 &b) { return a.x * b.x + a.y * b.y; }
    inline float length(const float2 &v) { return std::sqrt(v.x * v.x + v.y * v.y); }
    inline float2 normalize(const float2 &v)
    {
        float len = length(v);
        return len > 1e-6f ? mul(v, 1.0f / len) : float2{0, 0};
    }

    inline float4 add(const float4 &a, const float4 &b) { return {a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w}; }
    inline float4 sub(const float4 &a, const float4 &b) { return {a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w}; }
    inline float4 mul(const float4 &a, float s) { return {a.x * s, a.y * s, a.z * s, a.w * s}; }
    inline float dot(const float4 &a, const float4 &b) { return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; }
    inline float length(const float4 &v) { return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w); }
    inline float4 normalize(const float4 &v)
    {
        float len = length(v);
        return len > 1e-6f ? mul(v, 1.0f / len) : float4{0, 0, 0, 0};
    }

    inline float3 add(const float3 &a, const float3 &b) { return {a.x + b.x, a.y + b.y, a.z + b.z}; }
    inline float3 sub(const float3 &a, const float3 &b) { return {a.x - b.x, a.y - b.y, a.z - b.z}; }
    inline float3 mul(const float3 &a, float s) { return {a.x * s, a.y * s, a.z * s}; }
    inline float dot(const float3 &a, const float3 &b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
    inline float3 cross(const float3 &a, const float3 &b)
    {
        return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
    }
    inline float len(const float3 &v) { return std::sqrt(dot(v, v)); }
    inline float lengthSq(const float3 &v) { return dot(v, v); }
    inline float3 norm(const float3 &v)
    {
        float L = len(v);
        return (L > 0) ? mul(v, 1.f / L) : float3{0, 0, 0};
    }

    // ============================================================================
    // 4) Quaternion operations
    // ============================================================================

    /**
     * @brief Quaternion structure for 3D rotations
     */
    struct quat
    {
        float w, x, y, z;

        quat() : w(1), x(0), y(0), z(0) {}
        quat(float w_, float x_, float y_, float z_) : w(w_), x(x_), y(y_), z(z_) {}

        static quat identity() { return quat(1, 0, 0, 0); }
    };

    /**
     * @brief Create quaternion from axis-angle representation
     * @param axis Rotation axis (will be normalized)
     * @param angleRad Rotation angle in radians
     * @return Quaternion representing the rotation
     */
    inline quat q_from_axis_angle(const float3 &axis, float angleRad)
    {
        float3 u = norm(axis);
        float s = std::sin(angleRad * 0.5f);
        return {std::cos(angleRad * 0.5f), u.x * s, u.y * s, u.z * s};
    }

    /**
     * @brief Rotate vector by quaternion
     * @param q Rotation quaternion
     * @param v Vector to rotate
     * @return Rotated vector
     */
    inline float3 q_rotate(const quat &q, const float3 &v)
    {
        // v' = q * (0,v) * q^-1
        float3 u = {q.x, q.y, q.z};
        float s = q.w;
        float3 t = mul(cross(u, v), 2.f);
        return add(add(v, mul(t, s)), cross(u, t));
    }

    /**
     * @brief Multiply two quaternions
     * @param a First quaternion
     * @param b Second quaternion
     * @return Product quaternion a * b
     */
    inline quat q_mul(const quat &a, const quat &b)
    {
        return {
            a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z,
            a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
            a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x,
            a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w};
    }

    /**
     * @brief Create look-at rotation quaternion
     * @param forward Forward direction (will be normalized)
     * @param up Up direction (will be normalized)
     * @return Quaternion representing the orientation
     */
    inline quat q_look_rotation(const float3 &forward, const float3 &up)
    {
        float3 f = norm(forward);
        float3 r = norm(cross(up, f));
        float3 u = cross(f, r);

        // Convert 3x3 rotation matrix to quaternion
        float m00 = r.x, m01 = u.x, m02 = f.x;
        float m11 = u.y, m22 = f.z;
        float trace = m00 + m11 + m22;

        quat q;
        if (trace > 0.f)
        {
            float s = std::sqrt(trace + 1.f) * 2.f; // s = 4 * qw
            q.w = 0.25f * s;
            q.x = (u.z - f.y) / s;
            q.y = (f.x - r.z) / s;
            q.z = (r.y - u.x) / s;
        }
        else
        {
            // Handle other cases - simplified for now
            q.w = 0.5f;
            q.x = 0.5f;
            q.y = 0.0f;
            q.z = 0.0f;
        }
        return q;
    }

    // ============================================================================
    // 5) Matrix operations (4x4 for camera transforms)
    // ============================================================================

    /**
     * @brief 4x4 transformation matrix
     */
    struct float4x4
    {
        float m[4][4];

        float4x4()
        {
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    m[i][j] = (i == j) ? 1.0f : 0.0f;
                }
            }
        }
    };

    /**
     * @brief Create look-at view matrix (right-handed, +Y up, -Z forward)
     * @param eye Camera position
     * @param target Look-at target
     * @param up Up direction
     * @return View transformation matrix
     */
    inline float4x4 lookAt(const float3 &eye, const float3 &target, const float3 &up)
    {
        float3 f = norm(sub(target, eye)); // forward
        float3 r = norm(cross(f, up));     // right
        float3 u = cross(r, f);            // corrected up

        float4x4 M{};
        M.m[0][0] = r.x;
        M.m[0][1] = u.x;
        M.m[0][2] = -f.x;
        M.m[0][3] = 0;
        M.m[1][0] = r.y;
        M.m[1][1] = u.y;
        M.m[1][2] = -f.y;
        M.m[1][3] = 0;
        M.m[2][0] = r.z;
        M.m[2][1] = u.z;
        M.m[2][2] = -f.z;
        M.m[2][3] = 0;
        M.m[3][0] = -dot(r, eye);
        M.m[3][1] = -dot(u, eye);
        M.m[3][2] = dot(f, eye);
        M.m[3][3] = 1;
        return M;
    }

    // ============================================================================
    // 6) Orbital mechanics utilities
    // ============================================================================

    /**
     * @brief Parameters for elliptical orbit calculation
     */
    struct OrbitParams
    {
        float semiMajorAxis; // a: semi-major axis
        float eccentricity;  // e: eccentricity [0,1)
        float inclination;   // i: inclination angle (radians)
        float angularRate;   // ω: angular rate (rad/s)
        float phaseOffset;   // φ₀: initial phase offset

        OrbitParams() : semiMajorAxis(1.0f), eccentricity(0.0f), inclination(0.0f),
                        angularRate(1.0f), phaseOffset(0.0f) {}
    };

    /**
     * @brief Calculate position on elliptical orbit
     * @param params Orbital parameters
     * @param time Current time
     * @return 3D position on orbit
     */
    inline float3 calculateOrbitPosition(const OrbitParams &params, float time)
    {
        float a = params.semiMajorAxis;
        float e = params.eccentricity;
        float b = a * (1.f - e); // semi-minor axis (simplified)
        float omega = params.angularRate;
        float i = params.inclination;
        float phi = omega * time + params.phaseOffset;

        // Ellipse in XZ plane
        float xP = a * std::cos(phi);
        float zP = b * std::sin(phi);

        // Rotate about X by inclination
        float x = xP;
        float y = -std::sin(i) * zP;
        float z = std::cos(i) * zP;

        return {x, y, z};
    }

    /**
     * @brief Calculate velocity on elliptical orbit
     * @param params Orbital parameters
     * @param time Current time
     * @return 3D velocity vector
     */
    inline float3 calculateOrbitVelocity(const OrbitParams &params, float time)
    {
        float a = params.semiMajorAxis;
        float e = params.eccentricity;
        float b = a * (1.f - e);
        float omega = params.angularRate;
        float i = params.inclination;
        float phi = omega * time + params.phaseOffset;

        // Velocity in XZ plane
        float vxP = -a * omega * std::sin(phi);
        float vzP = b * omega * std::cos(phi);

        // Rotate about X by inclination
        float vx = vxP;
        float vy = -std::sin(i) * vzP;
        float vz = std::cos(i) * vzP;

        return {vx, vy, vz};
    }

    /**
     * @brief Calculate banking angle for coordinated turn
     * @param velocity Current velocity vector
     * @param position Current position vector (for turn radius calculation)
     * @param maxBank Maximum banking angle (radians)
     * @return Banking angle in radians
     */
    inline float calculateBankingAngle(const float3 &velocity, const float3 &position, float maxBank = 15.f * DegToRad)
    {
        float3 Vh = {velocity.x, 0.f, velocity.z}; // horizontal velocity
        float3 Ph = {position.x, 0.f, position.z}; // horizontal position

        float speedH = len(Vh);
        if (speedH < 1e-4f)
            return 0.f;

        // Yaw rate calculation
        float yawRate = (velocity.x * position.z - velocity.z * position.x) / (Ph.x * Ph.x + Ph.z * Ph.z);

        // Coordinated turn banking
        float speed = len(velocity);
        float g = 9.81f;
        float bank = std::atan2(speed * yawRate, g);

        return clamp(bank, -maxBank, maxBank);
    }

    // ============================================================================
    // 7) Procedural generation utilities
    // ============================================================================

    /**
     * @brief Generate procedural texture noise value
     * @param x X coordinate
     * @param y Y coordinate
     * @param seed Random seed
     * @param amplitude Noise amplitude
     * @return Noise value
     */
    inline float proceduralNoise(int x, int y, uint32_t seed, float amplitude)
    {
        uint32_t state = hash_u32(seed + x * 73856093u + y * 19349663u);
        return (rand01(state) - 0.5f) * amplitude;
    }

    /**
     * @brief Check if pixel should be speckled based on density
     * @param x X coordinate
     * @param y Y coordinate
     * @param seed Random seed
     * @param density Speckle density [0,1]
     * @return True if pixel should be speckled
     */
    inline bool shouldSpeckle(int x, int y, uint32_t seed, float density)
    {
        uint32_t state = hash_u32(seed + x * 73856093u + y * 19349663u);
        return rand01(state) < density;
    }

    // ============================================================================
    // 8) Cel-shading utilities
    // ============================================================================

    /**
     * @brief Calculate cel-shaded lighting with band quantization
     * @param normal Surface normal (world space)
     * @param lightDir Light direction (from surface to light, normalized)
     * @param bands Number of shading bands
     * @return Shading factor [0,1]
     */
    inline float calculateCelShading(const float3 &normal, const float3 &lightDir, int bands = 4)
    {
        float NdotL = saturate(dot(normal, lightDir));

        // Band quantization
        float qIdx = std::floor(NdotL * bands);
        float qVal = (qIdx + 0.5f) / bands; // mid-band value

        return qVal;
    }

    /**
     * @brief Calculate rim lighting effect
     * @param normal Surface normal (world space)
     * @param viewDir View direction (from surface to camera, normalized)
     * @param power Rim falloff power
     * @return Rim lighting factor [0,1]
     */
    inline float calculateRimLighting(const float3 &normal, const float3 &viewDir, float power = 2.f)
    {
        return std::pow(1.f - saturate(dot(normal, viewDir)), power);
    }

    // ============================================================================
    // 9) Lifecycle and fade utilities
    // ============================================================================

    /**
     * @brief Calculate piecewise fade curve
     * @param t Current time
     * @param t0 Start time (0 alpha)
     * @param t1 Fade in complete time (1 alpha)
     * @param t2 Fade out start time (1 alpha)
     * @param t3 End time (0 alpha)
     * @return Alpha value [0,1]
     */
    inline float alpha_piecewise(float t, float t0, float t1, float t2, float t3)
    {
        if (t <= t0)
            return 0.f;
        if (t < t1)
            return smoothstep(t0, t1, t);
        if (t <= t2)
            return 1.f;
        if (t < t3)
            return 1.f - smoothstep(t2, t3, t);
        return 0.f;
    }

    /**
     * @brief Calculate exponential fade for contrails
     * @param elapsedTime Time since spawn
     * @param lifetime Total lifetime
     * @return Alpha value [0,1]
     */
    inline float alpha_contrail(float elapsedTime, float lifetime)
    {
        float s = saturate(1.f - elapsedTime / lifetime);
        return s * s; // quadratic falloff
    }

} // namespace Math
/**
 * @file ExponentialAirDensityModel.cpp
 * @brief Implementation of the exponential air density model.
 */

#include "ExponentialAirDensityModel.h"
#include <cmath>

/**
 * @brief Construct a new ExponentialAirDensityModel.
 *
 * Initializes the model with the given sea level density and scale height parameters.
 *
 * @param seaLevelDensity Air density at sea level in kg/m³ (typically ~1.225)
 * @param scaleHeight Atmospheric scale height in meters (typically ~8400)
 */
ExponentialAirDensityModel::ExponentialAirDensityModel(float seaLevelDensity, float scaleHeight)
    : seaLevelDensity_(seaLevelDensity), scaleHeight_(scaleHeight) {}

/**
 * @brief Calculate air density at a given altitude.
 *
 * Implements the exponential decay formula: ρ(h) = ρ₀ * exp(-h/H)
 * where ρ₀ is the sea level density and H is the scale height.
 *
 * @param altitude The altitude above sea level in meters
 * @return The air density in kg/m³ at the specified altitude
 */
float ExponentialAirDensityModel::getDensity(float altitude) const
{
    return seaLevelDensity_ * std::exp(-altitude / scaleHeight_);
}
/**
 * @file ExponentialAirDensityModel.h
 * @brief Implementation of an exponential air density model.
 *
 * This file implements an exponential decay model for atmospheric density,
 * commonly used in aviation and atmospheric physics. The model assumes
 * density decreases exponentially with altitude.
 */

#ifndef EXPONENTIALAIRDENSITYMODEL_H
#define EXPONENTIALAIRDENSITYMODEL_H

#include "IAirDensityModel.h"

/**
 * @class ExponentialAirDensityModel
 * @brief Air density model using exponential decay with altitude.
 *
 * This implementation uses the standard atmospheric model where air density
 * decreases exponentially with height according to the formula:
 * ρ(h) = ρ₀ * exp(-h/H)
 * where ρ₀ is sea level density and H is the scale height.
 */
class ExponentialAirDensityModel : public IAirDensityModel
{
public:
    /**
     * @brief Construct a new ExponentialAirDensityModel.
     *
     * @param seaLevelDensity Air density at sea level in kg/m³ (typically ~1.225)
     * @param scaleHeight Atmospheric scale height in meters (typically ~8400)
     */
    ExponentialAirDensityModel(float seaLevelDensity, float scaleHeight);

    /**
     * @brief Calculate air density at a given altitude.
     *
     * Uses the exponential decay formula: ρ(h) = ρ₀ * exp(-h/H)
     *
     * @param altitude The altitude above sea level in meters
     * @return The air density in kg/m³ at the specified altitude
     */
    float getDensity(float altitude) const override;

private:
    /** @brief Air density at sea level in kg/m³ */
    float seaLevelDensity_;

    /** @brief Atmospheric scale height in meters */
    float scaleHeight_;
};

#endif
/**
 * @file IAirDensityModel.h
 * @brief Interface for air density models used in physics calculations.
 *
 * This interface defines the contract for air density models that calculate
 * atmospheric density as a function of altitude. Different implementations
 * can provide various atmospheric models (exponential, tabulated, etc.).
 */

#ifndef IAIRDENSITYMODEL_H
#define IAIRDENSITYMODEL_H

/**
 * @class IAirDensityModel
 * @brief Abstract interface for calculating air density at different altitudes.
 *
 * This interface provides a standardized way to calculate atmospheric density
 * based on altitude. Implementations can use different mathematical models
 * such as exponential decay, lookup tables, or complex atmospheric simulations.
 */
class IAirDensityModel
{
public:
    /** @brief Virtual destructor for proper cleanup of derived classes */
    virtual ~IAirDensityModel() = default;

    /**
     * @brief Calculate air density at a given altitude.
     *
     * @param altitude The altitude above sea level in meters
     * @return The air density in kg/m³ at the specified altitude
     */
    virtual float getDensity(float altitude) const = 0;
};

#endif
/**
 * @file ICollisionResolver.h
 * @brief Interface for collision resolution algorithms.
 *
 * This interface defines the contract for collision resolution systems that
 * handle the physics of objects colliding with surfaces. Different implementations
 * can provide various collision response models (impulse-based, penalty-based, etc.).
 */

#ifndef ICOLLISIONRESOLVER_H
#define ICOLLISIONRESOLVER_H

/**
 * @class ICollisionResolver
 * @brief Abstract interface for resolving collisions between objects and surfaces.
 *
 * This interface provides a standardized way to handle collision responses.
 * Implementations calculate how an object's velocity should change when it
 * collides with a surface, taking into account factors like restitution (bounciness).
 */
class ICollisionResolver
{
public:
    /** @brief Virtual destructor for proper cleanup of derived classes */
    virtual ~ICollisionResolver() = default;

    /**
     * @brief Resolve a collision by modifying object velocity.
     *
     * This method calculates the post-collision velocity of an object based on
     * its pre-collision velocity, the surface normal, and the coefficient of restitution.
     *
     * @param vx [in,out] X component of object velocity (modified by collision response)
     * @param vy [in,out] Y component of object velocity (modified by collision response)
     * @param vz [in,out] Z component of object velocity (modified by collision response)
     * @param normalX X component of the surface normal vector
     * @param normalY Y component of the surface normal vector
     * @param normalZ Z component of the surface normal vector
     * @param restitution Coefficient of restitution (0.0 = perfectly inelastic, 1.0 = perfectly elastic)
     */
    virtual void resolveCollision(float &vx, float &vy, float &vz, float normalX, float normalY, float normalZ, float restitution) = 0;
};

#endif
/**
 * @file ImpulseCollisionResolver.cpp
 * @brief Implementation of impulse-based collision resolution.
 */

#include "ImpulseCollisionResolver.h"

/**
 * @brief Construct a new ImpulseCollisionResolver.
 *
 * Initializes the collision resolver with default friction and restitution values.
 *
 * @param friction Coefficient of friction (0.0 = no friction, 1.0 = high friction)
 * @param restitution Default coefficient of restitution (0.0 = inelastic, 1.0 = elastic)
 */
ImpulseCollisionResolver::ImpulseCollisionResolver(float friction, float restitution)
    : friction_(friction), restitution_(restitution) {}

/**
 * @brief Resolve a collision using impulse-based calculations.
 *
 * This is a simplified implementation that applies an impulse to reverse
 * the component of velocity towards the surface. The impulse magnitude
 * is calculated based on the coefficient of restitution.
 *
 * Note: This is currently a stub implementation. A full impulse-based
 * resolver would include friction calculations and proper impulse magnitude
 * determination based on object masses and collision geometry.
 *
 * @param vx [in,out] X component of object velocity (modified by collision response)
 * @param vy [in,out] Y component of object velocity (modified by collision response)
 * @param vz [in,out] Z component of object velocity (modified by collision response)
 * @param normalX X component of the surface normal vector
 * @param normalY Y component of the surface normal vector
 * @param normalZ Z component of the surface normal vector
 * @param restitution Coefficient of restitution for this collision
 */
void ImpulseCollisionResolver::resolveCollision(float &vx, float &vy, float &vz, float normalX, float normalY, float normalZ, float restitution)
{
    // Calculate the component of velocity towards the surface
    float dot = vx * normalX + vy * normalY + vz * normalZ;

    // Only resolve if object is moving towards the surface
    if (dot < 0)
    {
        // Apply impulse to reverse the normal component of velocity
        // Formula: v' = v - (1+e) * (v·n) * n
        // where e is the coefficient of restitution
        vx -= (1 + restitution) * dot * normalX;
        vy -= (1 + restitution) * dot * normalY;
        vz -= (1 + restitution) * dot * normalZ;
    }
}
/**
 * @file ImpulseCollisionResolver.h
 * @brief Implementation of impulse-based collision resolution.
 *
 * This file implements an impulse-based collision response system that
 * calculates collision impulses and applies them to resolve object collisions
 * with surfaces, taking into account friction and restitution.
 */

#ifndef IMPULSECOLLISIONRESOLVER_H
#define IMPULSECOLLISIONRESOLVER_H

#include "ICollisionResolver.h"

/**
 * @class ImpulseCollisionResolver
 * @brief Collision resolver using impulse-based response calculations.
 *
 * This implementation uses classical mechanics to calculate collision impulses
 * based on conservation of momentum and energy. It handles both normal and
 * tangential components of collisions, applying friction and restitution effects.
 */
class ImpulseCollisionResolver : public ICollisionResolver
{
public:
    /**
     * @brief Construct a new ImpulseCollisionResolver.
     *
     * @param friction Coefficient of friction (0.0 = no friction, 1.0 = high friction)
     * @param restitution Default coefficient of restitution if not specified in resolveCollision
     */
    ImpulseCollisionResolver(float friction, float restitution);

    /**
     * @brief Resolve a collision using impulse-based calculations.
     *
     * Calculates the collision impulse based on the relative velocity,
     * surface normal, and material properties. Applies both normal and
     * tangential impulse components.
     *
     * @param vx [in,out] X component of object velocity (modified by collision response)
     * @param vy [in,out] Y component of object velocity (modified by collision response)
     * @param vz [in,out] Z component of object velocity (modified by collision response)
     * @param normalX X component of the surface normal vector
     * @param normalY Y component of the surface normal vector
     * @param normalZ Z component of the surface normal vector
     * @param restitution Coefficient of restitution for this collision
     */
    void resolveCollision(float &vx, float &vy, float &vz, float normalX, float normalY, float normalZ, float restitution) override;

private:
    /** @brief Default coefficient of friction for surfaces */
    float friction_;

    /** @brief Default coefficient of restitution for collisions */
    float restitution_;
};

#endif
/**
 * @file IWindModel.h
 * @brief Interface for wind models used in aerodynamic calculations.
 *
 * This interface defines the contract for wind models that calculate
 * wind velocity vectors at different positions in 3D space. Different
 * implementations can provide various wind patterns (constant, turbulent, etc.).
 */

#ifndef IWINDMODEL_H
#define IWINDMODEL_H

/**
 * @class IWindModel
 * @brief Abstract interface for calculating wind velocity at spatial positions.
 *
 * This interface provides a standardized way to calculate wind velocity
 * vectors at any point in 3D space. Implementations can model different
 * types of wind conditions including steady winds, turbulence, and weather systems.
 */
class IWindModel
{
public:
    /** @brief Virtual destructor for proper cleanup of derived classes */
    virtual ~IWindModel() = default;

    /**
     * @brief Calculate wind velocity at a given position.
     *
     * @param x X coordinate of the position
     * @param y Y coordinate of the position
     * @param z Z coordinate of the position
     * @param wx [out] X component of wind velocity at the position
     * @param wy [out] Y component of wind velocity at the position
     * @param wz [out] Z component of wind velocity at the position
     */
    virtual void getWind(float x, float y, float z, float &wx, float &wy, float &wz) const = 0;
};

#endif
/**
 * @file PerlinWindModel.cpp
 * @brief Implementation of Perlin noise-based wind model.
 */

#include "PerlinWindModel.h"

/**
 * @brief Construct a new PerlinWindModel.
 *
 * Initializes the wind model with parameters for generating Perlin noise-based
 * wind fields. The parameters control the strength, frequency, and amplitude
 * of the wind variations.
 *
 * @param strength Base wind strength multiplier
 * @param frequency Spatial frequency of the wind variations
 * @param amplitude Maximum wind speed variation
 * @param seed Random seed for reproducible wind patterns
 */
PerlinWindModel::PerlinWindModel(float strength, float frequency, float amplitude, int seed)
    : strength_(strength), frequency_(frequency), amplitude_(amplitude), seed_(seed) {}

/**
 * @brief Calculate wind velocity at a given position using Perlin noise.
 *
 * This is currently a stub implementation that returns constant wind in the X direction.
 * A full implementation would use Perlin noise functions to generate spatially coherent
 * wind velocity fields with realistic turbulence patterns.
 *
 * @param x X coordinate of the position
 * @param y Y coordinate of the position
 * @param z Z coordinate of the position
 * @param wx [out] X component of wind velocity at the position
 * @param wy [out] Y component of wind velocity at the position
 * @param wz [out] Z component of wind velocity at the position
 */
void PerlinWindModel::getWind(float x, float y, float z, float &wx, float &wy, float &wz) const
{
    // Stub: return constant wind in X direction
    // TODO: Implement Perlin noise-based wind field generation
    wx = strength_;
    wy = 0.0f;
    wz = 0.0f;
}
/**
 * @file PerlinWindModel.h
 * @brief Implementation of a Perlin noise-based wind model.
 *
 * This file implements a wind model using Perlin noise to generate
 * realistic turbulent wind patterns. The model creates spatially
 * coherent wind fields that vary smoothly across 3D space.
 */

#ifndef PERLINWINDMODEL_H
#define PERLINWINDMODEL_H

#include "IWindModel.h"

/**
 * @class PerlinWindModel
 * @brief Wind model using Perlin noise for realistic turbulence.
 *
 * This implementation generates wind velocity fields using Perlin noise,
 * creating natural-looking wind patterns with spatial coherence. The wind
 * varies smoothly in space and can include multiple octaves for complex
 * turbulence patterns.
 */
class PerlinWindModel : public IWindModel
{
public:
    /**
     * @brief Construct a new PerlinWindModel.
     *
     * @param strength Base wind strength multiplier
     * @param frequency Spatial frequency of the wind variations
     * @param amplitude Maximum wind speed variation
     * @param seed Random seed for reproducible wind patterns
     */
    PerlinWindModel(float strength, float frequency, float amplitude, int seed);

    /**
     * @brief Calculate wind velocity at a given position using Perlin noise.
     *
     * Uses Perlin noise functions to generate spatially coherent wind
     * velocity components. The wind field varies smoothly and creates
     * realistic turbulence patterns.
     *
     * @param x X coordinate of the position
     * @param y Y coordinate of the position
     * @param z Z coordinate of the position
     * @param wx [out] X component of wind velocity at the position
     * @param wy [out] Y component of wind velocity at the position
     * @param wz [out] Z component of wind velocity at the position
     */
    void getWind(float x, float y, float z, float &wx, float &wy, float &wz) const override;

private:
    /** @brief Base wind strength multiplier */
    float strength_;

    /** @brief Spatial frequency of wind variations */
    float frequency_;

    /** @brief Maximum wind speed variation */
    float amplitude_;

    /** @brief Random seed for reproducible patterns */
    int seed_;
};

#endif
/**
 * @file IInputDevice.h
 * @brief Interface for platform-specific input device handling.
 *
 * This interface defines the contract for input device implementations
 * that handle user input from various sources (keyboard, mouse, gamepads, etc.).
 * Different platforms can provide their own implementations while maintaining
 * a consistent interface for the rest of the application.
 */

#ifndef IINPUTDEVICE_H
#define IINPUTDEVICE_H

/**
 * @class IInputDevice
 * @brief Abstract interface for handling user input devices.
 *
 * This interface provides a platform-independent way to access user input.
 * Implementations handle polling input devices and providing input state
 * to the application. The interface is designed to be extensible for
 * different types of input devices and platforms.
 */
class IInputDevice
{
public:
    /** @brief Virtual destructor for proper cleanup of derived classes */
    virtual ~IInputDevice() = default;

    /**
     * @brief Poll the input devices for new input events.
     *
     * This method should be called regularly to update the internal
     * input state. It handles platform-specific input processing and
     * updates the state of all connected input devices.
     */
    virtual void poll() = 0;

    // TODO: Add methods for querying specific input states
    // virtual bool isKeyPressed(KeyCode key) const = 0;
    // virtual bool isMouseButtonPressed(MouseButton button) const = 0;
    // virtual void getMousePosition(int& x, int& y) const = 0;
};

#endif
/**
 * @file WinInputDevice.cpp
 * @brief Implementation of Windows-specific input device handling.
 */

#include "WinInputDevice.h"

/**
 * @brief Poll Windows input devices for new input events.
 *
 * This is currently a stub implementation. A full implementation would:
 * - Process Windows messages from the message queue
 * - Update keyboard state using GetAsyncKeyState or similar
 * - Handle mouse input and cursor position
 * - Process raw input for game controllers
 * - Update internal input state for querying by other systems
 */
void WinInputDevice::poll()
{
    // Stub: poll Windows input
    // TODO: Implement Windows message processing and input state updates
}
/**
 * @file WinInputDevice.h
 * @brief Windows-specific implementation of the input device interface.
 *
 * This file implements the IInputDevice interface for Windows platforms,
 * providing input handling through the Windows API. It manages keyboard,
 * mouse, and other input devices available on Windows systems.
 */

#ifndef WININPUTDEVICE_H
#define WININPUTDEVICE_H

#include "IInputDevice.h"

/**
 * @class WinInputDevice
 * @brief Windows platform implementation of input device handling.
 *
 * This class provides Windows-specific input device management using
 * the Win32 API. It handles polling Windows messages, keyboard state,
 * mouse input, and other Windows-specific input sources.
 */
class WinInputDevice : public IInputDevice
{
public:
    /**
     * @brief Poll Windows input devices for new input events.
     *
     * Processes Windows messages and updates the internal input state.
     * This method should be called regularly in the application's main loop
     * to ensure responsive input handling.
     */
    void poll() override;
};

#endif
#include "ProceduralMeshGenerators.h"
#include <map>
#include <cmath>
#include <random>
#include <algorithm>

// IcoSphereGenerator Implementation
ProceduralMesh IcoSphereGenerator::generate(float radius, int subdivisions, bool flatShading)
{
    ProceduralMesh mesh;
    std::vector<Vector3D> tempVertices;

    // Create initial icosahedron vertices
    float t = (1.0f + std::sqrt(5.0f)) / 2.0f; // Golden ratio

    addVertex(tempVertices, Vector3D(-1, t, 0));
    addVertex(tempVertices, Vector3D(1, t, 0));
    addVertex(tempVertices, Vector3D(-1, -t, 0));
    addVertex(tempVertices, Vector3D(1, -t, 0));

    addVertex(tempVertices, Vector3D(0, -1, t));
    addVertex(tempVertices, Vector3D(0, 1, t));
    addVertex(tempVertices, Vector3D(0, -1, -t));
    addVertex(tempVertices, Vector3D(0, 1, -t));

    addVertex(tempVertices, Vector3D(t, 0, -1));
    addVertex(tempVertices, Vector3D(t, 0, 1));
    addVertex(tempVertices, Vector3D(-t, 0, -1));
    addVertex(tempVertices, Vector3D(-t, 0, 1));

    // Create initial faces
    std::vector<std::array<int, 3>> faces = {
        {0, 11, 5}, {0, 5, 1}, {0, 1, 7}, {0, 7, 10}, {0, 10, 11}, {1, 5, 9}, {5, 11, 4}, {11, 10, 2}, {10, 7, 6}, {7, 1, 8}, {3, 9, 4}, {3, 4, 2}, {3, 2, 6}, {3, 6, 8}, {3, 8, 9}, {4, 9, 5}, {2, 4, 11}, {6, 2, 10}, {8, 6, 7}, {9, 8, 1}};

    // Subdivide faces
    std::map<long, int> middlePointIndexCache;
    for (int i = 0; i < subdivisions; i++)
    {
        std::vector<std::array<int, 3>> newFaces;

        for (const auto &face : faces)
        {
            int a = getMiddlePoint(face[0], face[1], tempVertices, middlePointIndexCache, radius);
            int b = getMiddlePoint(face[1], face[2], tempVertices, middlePointIndexCache, radius);
            int c = getMiddlePoint(face[2], face[0], tempVertices, middlePointIndexCache, radius);

            newFaces.push_back({face[0], a, c});
            newFaces.push_back({face[1], b, a});
            newFaces.push_back({face[2], c, b});
            newFaces.push_back({a, b, c});
        }

        faces = newFaces;
    }

    // Convert to final mesh format
    if (flatShading)
    {
        // Duplicate vertices for flat shading
        for (const auto &face : faces)
        {
            Vector3D v1 = tempVertices[face[0]] * radius;
            Vector3D v2 = tempVertices[face[1]] * radius;
            Vector3D v3 = tempVertices[face[2]] * radius;

            Vector3D normal = (v2 - v1).cross(v3 - v1).normalized();

            float u1, v1_uv, u2, v2_uv, u3, v3_uv;
            calculateUV(v1, u1, v1_uv);
            calculateUV(v2, u2, v2_uv);
            calculateUV(v3, u3, v3_uv);

            int baseIndex = mesh.vertices.size();
            mesh.vertices.emplace_back(v1, normal, u1, v1_uv);
            mesh.vertices.emplace_back(v2, normal, u2, v2_uv);
            mesh.vertices.emplace_back(v3, normal, u3, v3_uv);

            mesh.indices.push_back(baseIndex);
            mesh.indices.push_back(baseIndex + 1);
            mesh.indices.push_back(baseIndex + 2);
        }
    }
    else
    {
        // Shared vertices for smooth shading
        for (const auto &vertex : tempVertices)
        {
            Vector3D pos = vertex * radius;
            Vector3D normal = vertex; // For sphere, normal = normalized position
            float u, v;
            calculateUV(pos, u, v);
            mesh.vertices.emplace_back(pos, normal, u, v);
        }

        for (const auto &face : faces)
        {
            mesh.indices.push_back(face[0]);
            mesh.indices.push_back(face[1]);
            mesh.indices.push_back(face[2]);
        }
    }

    return mesh;
}

void IcoSphereGenerator::addVertex(std::vector<Vector3D> &vertices, const Vector3D &v)
{
    vertices.push_back(v.normalized());
}

int IcoSphereGenerator::getMiddlePoint(int p1, int p2, std::vector<Vector3D> &vertices,
                                       std::map<long, int> &cache, float radius)
{
    bool firstIsSmaller = p1 < p2;
    long smallerIndex = firstIsSmaller ? p1 : p2;
    long greaterIndex = firstIsSmaller ? p2 : p1;
    long key = (smallerIndex << 32) + greaterIndex;

    auto found = cache.find(key);
    if (found != cache.end())
    {
        return found->second;
    }

    Vector3D point1 = vertices[p1];
    Vector3D point2 = vertices[p2];
    Vector3D middle = Vector3D(
                          (point1.x + point2.x) / 2.0f,
                          (point1.y + point2.y) / 2.0f,
                          (point1.z + point2.z) / 2.0f)
                          .normalized();

    vertices.push_back(middle);
    int index = vertices.size() - 1;
    cache[key] = index;

    return index;
}

void IcoSphereGenerator::calculateUV(const Vector3D &vertex, float &u, float &v)
{
    u = std::atan2(vertex.x, vertex.z) / (2.0f * M_PI) + 0.5f;
    v = std::asin(vertex.y) / M_PI + 0.5f;
}

// CubeGenerator Implementation
ProceduralMesh CubeGenerator::generate(float size, bool flatShading)
{
    ProceduralMesh mesh;
    float half = size * 0.5f;

    // Define cube vertices
    std::vector<Vector3D> positions = {
        // Front face
        Vector3D(-half, -half, half), Vector3D(half, -half, half),
        Vector3D(half, half, half), Vector3D(-half, half, half),
        // Back face
        Vector3D(-half, -half, -half), Vector3D(-half, half, -half),
        Vector3D(half, half, -half), Vector3D(half, -half, -half),
        // Top face
        Vector3D(-half, half, -half), Vector3D(-half, half, half),
        Vector3D(half, half, half), Vector3D(half, half, -half),
        // Bottom face
        Vector3D(-half, -half, -half), Vector3D(half, -half, -half),
        Vector3D(half, -half, half), Vector3D(-half, -half, half),
        // Right face
        Vector3D(half, -half, -half), Vector3D(half, half, -half),
        Vector3D(half, half, half), Vector3D(half, -half, half),
        // Left face
        Vector3D(-half, -half, -half), Vector3D(-half, -half, half),
        Vector3D(-half, half, half), Vector3D(-half, half, -half)};

    std::vector<Vector3D> normals = {
        Vector3D(0, 0, 1), Vector3D(0, 0, -1), Vector3D(0, 1, 0),
        Vector3D(0, -1, 0), Vector3D(1, 0, 0), Vector3D(-1, 0, 0)};

    // Add faces
    for (int face = 0; face < 6; face++)
    {
        int baseIndex = face * 4;

        if (flatShading)
        {
            // Each face gets its own vertices
            int meshBaseIndex = mesh.vertices.size();

            for (int i = 0; i < 4; i++)
            {
                float u = (i == 1 || i == 2) ? 1.0f : 0.0f;
                float v = (i == 2 || i == 3) ? 1.0f : 0.0f;
                mesh.vertices.emplace_back(positions[baseIndex + i], normals[face], u, v);
            }

            // Two triangles per face
            mesh.indices.push_back(meshBaseIndex);
            mesh.indices.push_back(meshBaseIndex + 1);
            mesh.indices.push_back(meshBaseIndex + 2);

            mesh.indices.push_back(meshBaseIndex);
            mesh.indices.push_back(meshBaseIndex + 2);
            mesh.indices.push_back(meshBaseIndex + 3);
        }
    }

    return mesh;
}

// ProceduralAircraftGenerator Implementation
ProceduralMesh ProceduralAircraftGenerator::generate(float length, int fuselageSegments,
                                                     float wingSpan, float tailSpan, bool flatShading)
{
    ProceduralMesh mesh;

    addFuselage(mesh, length, fuselageSegments);
    addWings(mesh, wingSpan, length * 0.6f);
    addTail(mesh, tailSpan, length * 0.3f);

    return mesh;
}

void ProceduralAircraftGenerator::addFuselage(ProceduralMesh &mesh, float length, int segments)
{
    float halfLength = length * 0.5f;
    float radius = length * 0.05f; // Thin fuselage

    // Simple tapered cylinder
    for (int i = 0; i <= segments; i++)
    {
        float t = static_cast<float>(i) / segments;
        float z = -halfLength + t * length;
        float currentRadius = radius * (1.0f - std::abs(2.0f * t - 1.0f) * 0.7f); // Taper at ends

        // Add circular cross-section
        int sides = 8;
        for (int j = 0; j < sides; j++)
        {
            float angle = 2.0f * M_PI * j / sides;
            float x = currentRadius * std::cos(angle);
            float y = currentRadius * std::sin(angle);

            Vector3D pos(x, y, z);
            Vector3D normal = Vector3D(x, y, 0).normalized();

            mesh.vertices.emplace_back(pos, normal, static_cast<float>(j) / sides, t);
        }
    }

    // Add triangles between segments
    for (int i = 0; i < segments; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            int current = i * 8 + j;
            int next = i * 8 + ((j + 1) % 8);
            int currentNext = (i + 1) * 8 + j;
            int nextNext = (i + 1) * 8 + ((j + 1) % 8);

            // Two triangles per quad
            mesh.indices.push_back(current);
            mesh.indices.push_back(currentNext);
            mesh.indices.push_back(next);

            mesh.indices.push_back(next);
            mesh.indices.push_back(currentNext);
            mesh.indices.push_back(nextNext);
        }
    }
}

void ProceduralAircraftGenerator::addWings(ProceduralMesh &mesh, float span, float length)
{
    float halfSpan = span * 0.5f;
    float halfLength = length * 0.5f;
    float thickness = length * 0.02f;

    int baseIndex = mesh.vertices.size();

    // Wing vertices (simple rectangular wings)
    std::vector<Vector3D> wingVerts = {
        // Top surface
        Vector3D(-halfSpan, thickness, -halfLength), Vector3D(halfSpan, thickness, -halfLength),
        Vector3D(halfSpan, thickness, halfLength), Vector3D(-halfSpan, thickness, halfLength),
        // Bottom surface
        Vector3D(-halfSpan, -thickness, -halfLength), Vector3D(-halfSpan, -thickness, halfLength),
        Vector3D(halfSpan, -thickness, halfLength), Vector3D(halfSpan, -thickness, -halfLength)};

    Vector3D upNormal(0, 1, 0);
    Vector3D downNormal(0, -1, 0);

    // Add vertices
    for (int i = 0; i < 4; i++)
    {
        mesh.vertices.emplace_back(wingVerts[i], upNormal, i % 2, i / 2);
    }
    for (int i = 4; i < 8; i++)
    {
        mesh.vertices.emplace_back(wingVerts[i], downNormal, i % 2, (i - 4) / 2);
    }

    // Add triangles
    std::vector<int> indices = {
        // Top face
        0, 1, 2, 0, 2, 3,
        // Bottom face
        4, 6, 5, 4, 7, 6};

    for (int idx : indices)
    {
        mesh.indices.push_back(baseIndex + idx);
    }
}

void ProceduralAircraftGenerator::addTail(ProceduralMesh &mesh, float span, float length)
{
    // Similar to wings but smaller and positioned at rear
    float halfSpan = span * 0.5f;
    float halfLength = length * 0.5f;
    float thickness = length * 0.01f;
    float zOffset = length * 1.5f; // Position at rear

    int baseIndex = mesh.vertices.size();

    std::vector<Vector3D> tailVerts = {
        Vector3D(-halfSpan, thickness, zOffset - halfLength),
        Vector3D(halfSpan, thickness, zOffset - halfLength),
        Vector3D(halfSpan, thickness, zOffset + halfLength),
        Vector3D(-halfSpan, thickness, zOffset + halfLength),
        Vector3D(-halfSpan, -thickness, zOffset - halfLength),
        Vector3D(-halfSpan, -thickness, zOffset + halfLength),
        Vector3D(halfSpan, -thickness, zOffset + halfLength),
        Vector3D(halfSpan, -thickness, zOffset - halfLength)};

    Vector3D upNormal(0, 1, 0);
    Vector3D downNormal(0, -1, 0);

    for (int i = 0; i < 4; i++)
    {
        mesh.vertices.emplace_back(tailVerts[i], upNormal, i % 2, i / 2);
    }
    for (int i = 4; i < 8; i++)
    {
        mesh.vertices.emplace_back(tailVerts[i], downNormal, i % 2, (i - 4) / 2);
    }

    std::vector<int> indices = {
        0, 1, 2, 0, 2, 3,
        4, 6, 5, 4, 7, 6};

    for (int idx : indices)
    {
        mesh.indices.push_back(baseIndex + idx);
    }
}

// SphericalPatchDisplaceGenerator Implementation
ProceduralMesh SphericalPatchDisplaceGenerator::generate(float baseRadius, int subdivisions,
                                                         int patchCount, float minHeight,
                                                         float maxHeight, int seed)
{
    // Start with base icosphere
    ProceduralMesh baseMesh = IcoSphereGenerator::generate(baseRadius, subdivisions, true);

    // Setup random number generator
    std::mt19937 rng;
    if (seed == -1)
    {
        std::random_device rd;
        rng.seed(rd());
    }
    else
    {
        rng.seed(seed);
    }

    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
    std::uniform_real_distribution<float> heightDist(minHeight, maxHeight);

    // Generate random patch centers
    std::vector<Vector3D> patchCenters;
    std::vector<float> patchRadii;
    std::vector<float> patchHeights;

    for (int i = 0; i < patchCount; i++)
    {
        Vector3D center(dist(rng), dist(rng), dist(rng));
        center = center.normalized();
        patchCenters.push_back(center);
        patchRadii.push_back(0.2f + dist(rng) * 0.1f); // Radius between 0.1-0.3
        patchHeights.push_back(heightDist(rng));
    }

    // Displace vertices based on patches
    for (auto &vertex : baseMesh.vertices)
    {
        Vector3D originalPos = vertex.position.normalized() * baseRadius;
        float totalDisplacement = 0.0f;

        for (size_t i = 0; i < patchCenters.size(); i++)
        {
            if (isInPatch(originalPos, patchCenters[i], patchRadii[i]))
            {
                float displacement = calculateDisplacement(originalPos, patchCenters[i],
                                                           patchRadii[i], 0.0f, patchHeights[i]);
                totalDisplacement += displacement;
            }
        }

        Vector3D direction = vertex.position.normalized();
        vertex.position = direction * (baseRadius + totalDisplacement);
        vertex.normal = direction; // Keep normal pointing outward
    }

    return baseMesh;
}

bool SphericalPatchDisplaceGenerator::isInPatch(const Vector3D &vertex, const Vector3D &patchCenter,
                                                float patchRadius)
{
    return vertex.normalized().dot(patchCenter) > std::cos(patchRadius);
}

float SphericalPatchDisplaceGenerator::calculateDisplacement(const Vector3D &vertex,
                                                             const Vector3D &patchCenter,
                                                             float patchRadius,
                                                             float minHeight, float maxHeight)
{
    float distance = std::acos(vertex.normalized().dot(patchCenter));
    float normalizedDistance = distance / patchRadius;

    if (normalizedDistance >= 1.0f)
        return 0.0f;

    // Smooth falloff using cosine
    float falloff = (std::cos(normalizedDistance * M_PI) + 1.0f) * 0.5f;
    return minHeight + (maxHeight - minHeight) * falloff;
}
#pragma once
#include <vector>
#include <memory>
#include "../math/MathUtils.h"

/**
 * @file ProceduralMeshGenerators.h
 * @brief Collection of procedural mesh generation utilities.
 *
 * This file contains various mesh generators used for creating low-poly
 * geometry procedurally, including spheres, cubes, and aircraft meshes
 * for the voxel busy indicator scene.
 */

/**
 * @struct Vertex
 * @brief Basic vertex structure for procedural mesh generation.
 */
struct Vertex
{
    Vector3D position;
    Vector3D normal;
    float u, v; // UV coordinates

    Vertex(Vector3D pos = Vector3D(), Vector3D norm = Vector3D(), float texU = 0.0f, float texV = 0.0f)
        : position(pos), normal(norm), u(texU), v(texV) {}
};

/**
 * @struct ProceduralMesh
 * @brief Container for generated mesh data.
 */
struct ProceduralMesh
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    ProceduralMesh() = default;

    void clear()
    {
        vertices.clear();
        indices.clear();
    }

    size_t getVertexCount() const { return vertices.size(); }
    size_t getTriangleCount() const { return indices.size() / 3; }
};

/**
 * @class IcoSphereGenerator
 * @brief Generates low-poly icospheres with flat shading.
 *
 * Creates spherical meshes using icosahedral subdivision for consistent
 * triangle distribution. Ideal for the voxel busy indicator globe.
 */
class IcoSphereGenerator
{
public:
    /**
     * @brief Generate an icosphere mesh.
     *
     * @param radius Radius of the sphere
     * @param subdivisions Number of subdivision levels (0-3 recommended)
     * @param flatShading Whether to use flat shading (duplicate vertices)
     * @return Generated mesh data
     */
    static ProceduralMesh generate(float radius = 1.0f, int subdivisions = 2, bool flatShading = true);

private:
    static void addVertex(std::vector<Vector3D> &vertices, const Vector3D &v);
    static int getMiddlePoint(int p1, int p2, std::vector<Vector3D> &vertices, std::map<long, int> &cache, float radius);
    static void calculateUV(const Vector3D &vertex, float &u, float &v);
};

/**
 * @class CubeGenerator
 * @brief Generates simple cube meshes with flat shading.
 *
 * Creates basic cube geometry for voxel clouds and contrail elements.
 */
class CubeGenerator
{
public:
    /**
     * @brief Generate a cube mesh.
     *
     * @param size Side length of the cube
     * @param flatShading Whether to use flat shading (separate faces)
     * @return Generated mesh data
     */
    static ProceduralMesh generate(float size = 1.0f, bool flatShading = true);

private:
    static void addQuad(ProceduralMesh &mesh,
                        const Vector3D &v1, const Vector3D &v2,
                        const Vector3D &v3, const Vector3D &v4,
                        const Vector3D &normal);
};

/**
 * @class ProceduralAircraftGenerator
 * @brief Generates low-poly aircraft meshes.
 *
 * Creates simple aircraft geometry with fuselage, wings, and tail
 * suitable for the busy indicator scene.
 */
class ProceduralAircraftGenerator
{
public:
    /**
     * @brief Generate an aircraft mesh.
     *
     * @param length Fuselage length
     * @param fuselageSegments Number of fuselage segments
     * @param wingSpan Wing span distance
     * @param tailSpan Tail span distance
     * @param flatShading Whether to use flat shading
     * @return Generated mesh data
     */
    static ProceduralMesh generate(float length = 0.25f,
                                   int fuselageSegments = 6,
                                   float wingSpan = 0.22f,
                                   float tailSpan = 0.12f,
                                   bool flatShading = true);

private:
    static void addFuselage(ProceduralMesh &mesh, float length, int segments);
    static void addWings(ProceduralMesh &mesh, float span, float length);
    static void addTail(ProceduralMesh &mesh, float span, float length);
};

/**
 * @class SphericalPatchDisplaceGenerator
 * @brief Generates displaced spherical patches for terrain bumps.
 *
 * Creates land masses and rock formations on the globe surface
 * by displacing spherical patches outward.
 */
class SphericalPatchDisplaceGenerator
{
public:
    /**
     * @brief Generate displaced spherical patches.
     *
     * @param baseRadius Base sphere radius
     * @param subdivisions Sphere subdivision level
     * @param patchCount Number of displacement patches
     * @param minHeight Minimum displacement height
     * @param maxHeight Maximum displacement height
     * @param seed Random seed (-1 for random)
     * @return Generated mesh data
     */
    static ProceduralMesh generate(float baseRadius = 1.0f,
                                   int subdivisions = 2,
                                   int patchCount = 24,
                                   float minHeight = 0.03f,
                                   float maxHeight = 0.06f,
                                   int seed = -1);

private:
    static bool isInPatch(const Vector3D &vertex, const Vector3D &patchCenter, float patchRadius);
    static float calculateDisplacement(const Vector3D &vertex, const Vector3D &patchCenter,
                                       float patchRadius, float minHeight, float maxHeight);
};
#pragma once

#include "../core/System.h"
#include "../math/MathUtils.h"
#include <vector>
#include <memory>
#include <map>
#include <string>

namespace ECS
{

    // Forward declarations
    class Entity;
    class MaterialComponent;
    class MeshComponent;
    class LightComponent;

    // ============================================================================
    // Advanced Cel-Shading Data Structures
    // ============================================================================

    struct AdvancedCelShadingMaterial
    {
        // Base material properties
        Math::float4 baseColor = {1.0f, 1.0f, 1.0f, 1.0f};
        Math::float4 shadowColor = {0.3f, 0.3f, 0.5f, 1.0f};
        Math::float4 highlightColor = {1.2f, 1.2f, 1.4f, 1.0f};

        // Cel-shading specific parameters
        uint32_t shadingLevels = 3;   // Number of discrete shading levels
        float shadowThreshold = 0.5f; // Light threshold for shadow transition
        float shadowSoftness = 0.1f;  // Softness of shadow transitions

        // Outline properties
        bool enableOutline = true;
        Math::float4 outlineColor = {0.0f, 0.0f, 0.0f, 1.0f};
        float outlineWidth = 0.01f; // Outline width in screen space
        float outlineDepthSensitivity = 1.0f;
        float outlineNormalSensitivity = 1.0f;

        // Rim lighting
        bool enableRimLighting = true;
        Math::float4 rimColor = {1.0f, 1.0f, 1.0f, 1.0f};
        float rimPower = 2.0f;
        float rimIntensity = 1.0f;

        // Specular highlights
        bool enableSpecular = true;
        Math::float4 specularColor = {1.0f, 1.0f, 1.0f, 1.0f};
        float specularPower = 32.0f;
        float specularIntensity = 0.5f;
        uint32_t specularLevels = 2; // Discrete specular levels

        // Texture properties
        std::string diffuseTexture;
        std::string shadowRampTexture;   // 1D texture for shadow ramp
        std::string specularRampTexture; // 1D texture for specular ramp
        std::string outlineTexture;      // Texture for outline variation

        // Animation properties
        bool animateColors = false;
        float colorAnimationSpeed = 1.0f;
        float colorAnimationAmplitude = 0.1f;

        // Advanced properties
        bool useVertexColors = false;
        bool useEnvironmentMapping = false;
        float environmentIntensity = 0.3f;
        bool useFresnel = true;
        float fresnelPower = 3.0f;
    };

    struct CelShadingLight
    {
        EntityId lightEntityId;
        Math::float3 direction;
        Math::float4 color;
        float intensity;

        // Cel-shading specific light properties
        float shadowBias = 0.001f;
        bool castCelShadows = true;
        uint32_t shadowSteps = 3; // Number of shadow cascade levels
        float shadowSoftness = 0.2f;

        // Light animation
        bool animateIntensity = false;
        float intensityAnimationSpeed = 1.0f;
        float intensityAnimationRange = 0.2f;
    };

    // ============================================================================
    // Advanced Cel-Shading System Configuration
    // ============================================================================

    struct AdvancedCelShadingSystemConfig
    {
        // Rendering quality
        bool enableMultiPass = true;     // Use multiple passes for better quality
        bool enableSSAO = false;         // Screen-space ambient occlusion
        bool enableShadowMapping = true; // Real-time shadows
        uint32_t shadowMapSize = 1024;   // Shadow map resolution

        // Performance settings
        uint32_t maxLights = 8;         // Maximum number of lights
        bool enableLightCulling = true; // Cull lights outside view
        float cullingDistance = 100.0f; // Light culling distance
        bool enableLOD = true;          // Level of detail for distant objects

        // Outline settings
        bool enableScreenSpaceOutlines = true;
        uint32_t outlineTextureSize = 512; // Outline detection texture size
        float outlineDepthThreshold = 0.1f;
        float outlineNormalThreshold = 0.4f;

        // Post-processing
        bool enableColorGrading = false;
        bool enableVignette = false;
        float vignetteIntensity = 0.3f;
        bool enableFilmGrain = false;
        float filmGrainIntensity = 0.1f;

        // Debug settings
        bool showWireframe = false;
        bool showNormals = false;
        bool showLightInfluence = false;
        bool showShadowCascades = false;
    };

    // ============================================================================
    // Advanced Cel-Shading System (extends the basic one)
    // ============================================================================

    class AdvancedCelShadingSystem : public System
    {
    public:
        explicit AdvancedCelShadingSystem(const AdvancedCelShadingSystemConfig &config = AdvancedCelShadingSystemConfig{});
        ~AdvancedCelShadingSystem() override;

        // System interface
        void initialize() override;
        void update(float deltaTime) override;
        void render() override;
        void shutdown() override;

        // Configuration management
        void setConfig(const AdvancedCelShadingSystemConfig &config);
        const AdvancedCelShadingSystemConfig &getConfig() const;

        // Material management
        void createCelMaterial(const std::string &materialId, const AdvancedCelShadingMaterial &material);
        void updateCelMaterial(const std::string &materialId, const AdvancedCelShadingMaterial &material);
        void removeCelMaterial(const std::string &materialId);
        bool hasCelMaterial(const std::string &materialId) const;
        const AdvancedCelShadingMaterial *getCelMaterial(const std::string &materialId) const;

        // Light management
        void registerLight(EntityId lightEntityId);
        void unregisterLight(EntityId lightEntityId);
        void updateLightProperties(EntityId lightEntityId);

        // Rendering controls
        void setGlobalToonLevel(uint32_t levels);
        void setGlobalOutlineWidth(float width);
        void setGlobalRimLightIntensity(float intensity);

        // Shadow controls
        void setShadowDistance(float distance);
        void setShadowCascades(uint32_t cascades);
        void setShadowSoftness(float softness);

        // Environment settings
        void setAmbientColor(const Math::float4 &color);
        void setFogColor(const Math::float4 &color);
        void setFogDensity(float density);

        // Performance monitoring
        uint32_t getActiveMaterialCount() const;
        uint32_t getActiveLightCount() const;
        float getAverageRenderTime() const;

        // Debug and visualization
        void setDebugVisualization(bool enabled);
        bool isDebugVisualizationEnabled() const;
        void renderDebugInfo();

    protected:
        // Component handling
        void onComponentAdded(EntityId entityId, ComponentType type) override;
        void onComponentRemoved(EntityId entityId, ComponentType type) override;
        void onComponentChanged(EntityId entityId, ComponentType type) override;

    private:
        AdvancedCelShadingSystemConfig config_;
        std::map<std::string, AdvancedCelShadingMaterial> celMaterials_;
        std::map<EntityId, CelShadingLight> celLights_;

        // Global settings
        uint32_t globalToonLevels_ = 3;
        float globalOutlineWidth_ = 0.01f;
        float globalRimLightIntensity_ = 1.0f;

        // Environment
        Math::float4 ambientColor_ = {0.2f, 0.2f, 0.3f, 1.0f};
        Math::float4 fogColor_ = {0.7f, 0.8f, 0.9f, 1.0f};
        float fogDensity_ = 0.01f;

        // Shadow settings
        float shadowDistance_ = 100.0f;
        uint32_t shadowCascades_ = 3;
        float shadowSoftness_ = 0.3f;

        // Performance tracking
        mutable float averageRenderTime_ = 0.0f;
        mutable uint32_t renderSampleCount_ = 0;

        // Debug visualization
        bool debugVisualization_ = false;

        // Core rendering methods
        void renderWithAdvancedCelShading();
        void setupAdvancedCelShadingUniforms(const AdvancedCelShadingMaterial &material);
        void renderScreenSpaceOutlines();
        void applyPostProcessingEffects();

        // Utility methods
        Math::float3 calculateAdvancedCelShading(const Math::float3 &normal, const Math::float3 &lightDir,
                                                 const AdvancedCelShadingMaterial &material) const;
        float quantizeLighting(float lightValue, uint32_t levels) const;
        Math::float3 quantizeColor(const Math::float3 &color, uint32_t levels) const;

        void updatePerformanceCounters(float deltaTime);
    };

    // ============================================================================
    // Inline Implementation
    // ============================================================================

    inline uint32_t AdvancedCelShadingSystem::getActiveMaterialCount() const
    {
        return static_cast<uint32_t>(celMaterials_.size());
    }

    inline uint32_t AdvancedCelShadingSystem::getActiveLightCount() const
    {
        return static_cast<uint32_t>(celLights_.size());
    }

    inline float AdvancedCelShadingSystem::getAverageRenderTime() const
    {
        return averageRenderTime_;
    }

    inline bool AdvancedCelShadingSystem::isDebugVisualizationEnabled() const
    {
        return debugVisualization_;
    }

    inline void AdvancedCelShadingSystem::setDebugVisualization(bool enabled)
    {
        debugVisualization_ = enabled;
    }

    inline const AdvancedCelShadingSystemConfig &AdvancedCelShadingSystem::getConfig() const
    {
        return config_;
    }

    inline bool AdvancedCelShadingSystem::hasCelMaterial(const std::string &materialId) const
    {
        return celMaterials_.find(materialId) != celMaterials_.end();
    }

    inline const AdvancedCelShadingMaterial *AdvancedCelShadingSystem::getCelMaterial(const std::string &materialId) const
    {
        auto it = celMaterials_.find(materialId);
        return (it != celMaterials_.end()) ? &it->second : nullptr;
    }

    inline float AdvancedCelShadingSystem::quantizeLighting(float lightValue, uint32_t levels) const
    {
        if (levels <= 1)
            return lightValue;

        float step = 1.0f / (levels - 1);
        return std::floor(lightValue / step) * step;
    }

    inline Math::float3 AdvancedCelShadingSystem::quantizeColor(const Math::float3 &color, uint32_t levels) const
    {
        return {
            quantizeLighting(color.x, levels),
            quantizeLighting(color.y, levels),
            quantizeLighting(color.z, levels)};
    }

} // namespace ECS
#pragma once

#include "../core/System.h"
#include "../math/MathUtils.h"
#include "../config/SceneConfigParser.h"
#include <vector>
#include <memory>
#include <map>
#include <functional>
#include <string>

namespace ECS
{

    // ============================================================================
    // Animation Data Structures
    // ============================================================================

    struct AnimationKeyframe
    {
        float time = 0.0f;
        Math::float3 position = {0.0f, 0.0f, 0.0f};
        Math::float4 rotation = {0.0f, 0.0f, 0.0f, 1.0f}; // Quaternion
        Math::float3 scale = {1.0f, 1.0f, 1.0f};
        Math::float4 color = {1.0f, 1.0f, 1.0f, 1.0f};
        float value = 0.0f; // Generic scalar value

        // Custom properties for specialized animations
        std::map<std::string, float> customFloats;
        std::map<std::string, Math::float3> customVectors;
        std::map<std::string, Math::float4> customColors;
    };

    struct AnimationTrack
    {
        enum class Type
        {
            Transform, // Position, rotation, scale
            Color,     // Color animation
            Value,     // Generic scalar value
            Orbital,   // Orbital motion
            Custom     // Custom animation with callback
        };

        enum class Interpolation
        {
            Linear,
            Cubic,
            Bezier,
            Step,
            Smooth
        };

        Type type = Type::Transform;
        Interpolation interpolation = Interpolation::Linear;
        std::string targetProperty; // Property name to animate
        std::vector<AnimationKeyframe> keyframes;

        // Track-specific parameters
        bool loop = true;
        bool pingPong = false;
        float speed = 1.0f;
        float delay = 0.0f;

        // Orbital motion specific
        Math::OrbitParams orbitParams;

        // Custom animation callback
        std::function<void(EntityId, float, const AnimationKeyframe &)> customCallback;
    };

    struct Animation
    {
        std::string id;
        std::string name;
        float duration = 1.0f;
        bool autoStart = true;
        bool loop = true;
        float playbackSpeed = 1.0f;

        // Animation tracks
        std::vector<AnimationTrack> tracks;

        // Animation state
        enum class State
        {
            Stopped,
            Playing,
            Paused,
            Finished
        };

        State state = State::Stopped;
        float currentTime = 0.0f;
        float normalizedTime = 0.0f; // 0.0 to 1.0
        uint32_t currentLoop = 0;

        // Events
        std::function<void(EntityId)> onStart;
        std::function<void(EntityId)> onComplete;
        std::function<void(EntityId, uint32_t)> onLoop;
        std::function<void(EntityId, float)> onUpdate;
    };

    struct AnimationGroup
    {
        std::string id;
        std::vector<std::string> animationIds;

        enum class PlayMode
        {
            Sequential, // Play animations one after another
            Parallel,   // Play all animations simultaneously
            Random      // Play animations in random order
        };

        PlayMode playMode = PlayMode::Parallel;
        bool loop = false;
        float delay = 0.0f;

        // Group state
        uint32_t currentAnimationIndex = 0;
        bool isPlaying = false;
    };

    // ============================================================================
    // Animation System Configuration
    // ============================================================================

    struct AnimationSystemConfig
    {
        // Performance settings
        uint32_t maxAnimationsPerEntity = 10;
        uint32_t maxActiveAnimations = 1000;
        float updateFrequency = 60.0f; // Updates per second
        bool enableInterpolation = true;

        // Quality settings
        bool enableSmoothing = true;
        float smoothingFactor = 0.1f;
        bool enableBlending = true;
        uint32_t maxBlendedAnimations = 4;

        // Optimization settings
        bool enableCulling = true;
        float cullingDistance = 200.0f;
        bool enableLOD = true;
        float lodNearDistance = 50.0f;
        float lodFarDistance = 150.0f;

        // Memory management
        bool useObjectPooling = true;
        uint32_t initialPoolSize = 500;
        uint32_t poolGrowthSize = 100;

        // Debug settings
        bool logAnimationEvents = false;
        bool validateKeyframes = true;
        bool enablePerformanceMetrics = true;
    };

    // ============================================================================
    // Main Animation System
    // ============================================================================

    class AnimationSystem : public System
    {
    public:
        explicit AnimationSystem(const AnimationSystemConfig &config = AnimationSystemConfig{});
        ~AnimationSystem() override;

        // System interface
        void initialize() override;
        void update(float deltaTime) override;
        void render() override;
        void shutdown() override;

        // Configuration management
        void setConfig(const AnimationSystemConfig &config);
        const AnimationSystemConfig &getConfig() const;

        // Animation management
        void createAnimation(const std::string &animationId, const Animation &animation);
        void removeAnimation(const std::string &animationId);
        bool hasAnimation(const std::string &animationId) const;
        Animation *getAnimation(const std::string &animationId);
        const Animation *getAnimation(const std::string &animationId) const;

        // Entity animation control
        void playAnimation(EntityId entityId, const std::string &animationId);
        void stopAnimation(EntityId entityId, const std::string &animationId);
        void pauseAnimation(EntityId entityId, const std::string &animationId);
        void resumeAnimation(EntityId entityId, const std::string &animationId);
        void stopAllAnimations(EntityId entityId);

        // Animation playback control
        void setAnimationTime(EntityId entityId, const std::string &animationId, float time);
        void setAnimationSpeed(EntityId entityId, const std::string &animationId, float speed);
        float getAnimationTime(EntityId entityId, const std::string &animationId) const;
        bool isAnimationPlaying(EntityId entityId, const std::string &animationId) const;

        // Animation groups
        void createAnimationGroup(const std::string &groupId, const AnimationGroup &group);
        void playAnimationGroup(EntityId entityId, const std::string &groupId);
        void stopAnimationGroup(EntityId entityId, const std::string &groupId);

        // Animation blending
        void blendAnimations(EntityId entityId, const std::vector<std::string> &animationIds,
                             const std::vector<float> &weights);
        void crossfadeAnimation(EntityId entityId, const std::string &fromAnimation,
                                const std::string &toAnimation, float duration);

        // Dynamic animation creation
        Animation createTransformAnimation(const std::string &id, const Math::float3 &startPos,
                                           const Math::float3 &endPos, float duration);
        Animation createRotationAnimation(const std::string &id, const Math::float4 &startRot,
                                          const Math::float4 &endRot, float duration);
        Animation createScaleAnimation(const std::string &id, const Math::float3 &startScale,
                                       const Math::float3 &endScale, float duration);
        Animation createOrbitalAnimation(const std::string &id, const Math::OrbitParams &params, float duration);
        Animation createColorAnimation(const std::string &id, const Math::float4 &startColor,
                                       const Math::float4 &endColor, float duration);

        // Scene integration
        void loadAnimationsFromScene(const SceneConfig::Scene &scene);
        void applyAnimationToEntity(EntityId entityId, const SceneConfig::Animation &sceneAnimation);

        // Performance monitoring
        uint32_t getActiveAnimationCount() const;
        uint32_t getTotalAnimationCount() const;
        float getAverageUpdateTime() const;

        // Debug and visualization
        void setDebugVisualization(bool enabled);
        bool isDebugVisualizationEnabled() const;
        void renderDebugInfo();

    protected:
        // Component handling
        void onComponentAdded(EntityId entityId, ComponentType type) override;
        void onComponentRemoved(EntityId entityId, ComponentType type) override;
        void onComponentChanged(EntityId entityId, ComponentType type) override;

    private:
        // ============================================================================
        // Internal Animation Management
        // ============================================================================

        struct EntityAnimationState
        {
            std::map<std::string, Animation> activeAnimations;
            std::map<std::string, AnimationGroup> activeGroups;
            std::vector<std::string> blendedAnimations;
            std::vector<float> blendWeights;

            // Transform accumulation for blending
            Math::float3 accumulatedPosition = {0.0f, 0.0f, 0.0f};
            Math::float4 accumulatedRotation = {0.0f, 0.0f, 0.0f, 1.0f};
            Math::float3 accumulatedScale = {1.0f, 1.0f, 1.0f};
            Math::float4 accumulatedColor = {1.0f, 1.0f, 1.0f, 1.0f};

            // Performance tracking
            float lastUpdateTime = 0.0f;
            uint32_t animationCount = 0;
        };

        AnimationSystemConfig config_;
        std::map<std::string, Animation> animationTemplates_;
        std::map<std::string, AnimationGroup> groupTemplates_;
        std::map<EntityId, EntityAnimationState> entityAnimations_;

        // Performance tracking
        mutable float averageUpdateTime_ = 0.0f;
        mutable uint32_t updateSampleCount_ = 0;

        // Debug visualization
        bool debugVisualization_ = false;

        // Object pooling
        std::vector<Animation> animationPool_;
        std::vector<size_t> freeAnimationIndices_;

        // ============================================================================
        // Core Update Methods
        // ============================================================================

        void updateEntityAnimations(EntityId entityId, EntityAnimationState &state, float deltaTime);
        void updateAnimation(EntityId entityId, Animation &animation, float deltaTime);
        void updateAnimationGroup(EntityId entityId, AnimationGroup &group, float deltaTime);
        void applyAnimationBlending(EntityId entityId, EntityAnimationState &state);

        // ============================================================================
        // Animation Track Processing
        // ============================================================================

        void processTransformTrack(EntityId entityId, const AnimationTrack &track, float time);
        void processColorTrack(EntityId entityId, const AnimationTrack &track, float time);
        void processValueTrack(EntityId entityId, const AnimationTrack &track, float time);
        void processOrbitalTrack(EntityId entityId, const AnimationTrack &track, float time);
        void processCustomTrack(EntityId entityId, const AnimationTrack &track, float time);

        // ============================================================================
        // Keyframe Interpolation
        // ============================================================================

        AnimationKeyframe interpolateKeyframes(const AnimationKeyframe &a, const AnimationKeyframe &b,
                                               float t, AnimationTrack::Interpolation interpolation) const;

        // Interpolation methods
        float interpolateLinear(float a, float b, float t) const;
        float interpolateCubic(float a, float b, float ta, float tb, float t) const;
        float interpolateBezier(float a, float b, float control1, float control2, float t) const;
        float interpolateStep(float a, float b, float t) const;
        float interpolateSmooth(float a, float b, float t) const;

        // Vector interpolation
        Math::float3 interpolateVector3(const Math::float3 &a, const Math::float3 &b, float t,
                                        AnimationTrack::Interpolation interpolation) const;
        Math::float4 interpolateQuaternion(const Math::float4 &a, const Math::float4 &b, float t) const;
        Math::float4 interpolateColor(const Math::float4 &a, const Math::float4 &b, float t) const;

        // ============================================================================
        // Animation Evaluation
        // ============================================================================

        std::pair<const AnimationKeyframe *, const AnimationKeyframe *>
        findKeyframeInterval(const AnimationTrack &track, float time) const;
        float calculateInterpolationFactor(const AnimationKeyframe &a, const AnimationKeyframe &b, float time) const;
        AnimationKeyframe evaluateTrackAtTime(const AnimationTrack &track, float time) const;

        // ============================================================================
        // Entity Transform Application
        // ============================================================================

        void applyTransformToEntity(EntityId entityId, const Math::float3 &position,
                                    const Math::float4 &rotation, const Math::float3 &scale);
        void applyColorToEntity(EntityId entityId, const Math::float4 &color);
        void applyValueToEntity(EntityId entityId, const std::string &property, float value);

        // Transform component integration
        Math::float3 getEntityPosition(EntityId entityId) const;
        Math::float4 getEntityRotation(EntityId entityId) const;
        Math::float3 getEntityScale(EntityId entityId) const;
        void setEntityTransform(EntityId entityId, const Math::float3 &position,
                                const Math::float4 &rotation, const Math::float3 &scale);

        // ============================================================================
        // Animation Validation and Optimization
        // ============================================================================

        bool validateAnimation(const Animation &animation) const;
        bool validateAnimationTrack(const AnimationTrack &track) const;
        void optimizeAnimation(Animation &animation);
        void sortKeyframes(AnimationTrack &track);
        void removeRedundantKeyframes(AnimationTrack &track);

        // ============================================================================
        // Performance Optimization
        // ============================================================================

        bool shouldUpdateAnimation(EntityId entityId, const Animation &animation) const;
        float calculateLODFactor(EntityId entityId) const;
        void cullDistantAnimations();
        void updatePerformanceCounters(float deltaTime);

        // Object pooling
        Animation *acquireAnimation();
        void releaseAnimation(Animation *animation);
        void expandAnimationPool();

        // ============================================================================
        // Event Handling
        // ============================================================================

        void triggerAnimationEvent(EntityId entityId, const Animation &animation, const std::string &eventType);
        void onAnimationStart(EntityId entityId, const Animation &animation);
        void onAnimationComplete(EntityId entityId, const Animation &animation);
        void onAnimationLoop(EntityId entityId, const Animation &animation, uint32_t loopCount);
        void onAnimationUpdate(EntityId entityId, const Animation &animation, float time);

        // ============================================================================
        // Debug and Profiling
        // ============================================================================

        void renderAnimationDebugInfo(EntityId entityId, const EntityAnimationState &state);
        void logAnimationStatistics() const;
        void validateAnimationState() const;
    };

    // ============================================================================
    // Inline Implementation for Performance-Critical Methods
    // ============================================================================

    inline uint32_t AnimationSystem::getActiveAnimationCount() const
    {
        uint32_t total = 0;
        for (const auto &[entityId, state] : entityAnimations_)
        {
            total += state.animationCount;
        }
        return total;
    }

    inline uint32_t AnimationSystem::getTotalAnimationCount() const
    {
        return static_cast<uint32_t>(animationTemplates_.size());
    }

    inline float AnimationSystem::getAverageUpdateTime() const
    {
        return averageUpdateTime_;
    }

    inline bool AnimationSystem::isDebugVisualizationEnabled() const
    {
        return debugVisualization_;
    }

    inline void AnimationSystem::setDebugVisualization(bool enabled)
    {
        debugVisualization_ = enabled;
    }

    inline const AnimationSystemConfig &AnimationSystem::getConfig() const
    {
        return config_;
    }

    inline bool AnimationSystem::hasAnimation(const std::string &animationId) const
    {
        return animationTemplates_.find(animationId) != animationTemplates_.end();
    }

    inline Animation *AnimationSystem::getAnimation(const std::string &animationId)
    {
        auto it = animationTemplates_.find(animationId);
        return (it != animationTemplates_.end()) ? &it->second : nullptr;
    }

    inline const Animation *AnimationSystem::getAnimation(const std::string &animationId) const
    {
        auto it = animationTemplates_.find(animationId);
        return (it != animationTemplates_.end()) ? &it->second : nullptr;
    }

    inline float AnimationSystem::interpolateLinear(float a, float b, float t) const
    {
        return a + t * (b - a);
    }

    inline float AnimationSystem::interpolateStep(float a, float b, float t) const
    {
        return (t < 1.0f) ? a : b;
    }

    inline float AnimationSystem::interpolateSmooth(float a, float b, float t) const
    {
        // Smoothstep interpolation
        t = t * t * (3.0f - 2.0f * t);
        return interpolateLinear(a, b, t);
    }

} // namespace ECS
/**
 * @file AssetHotReloadSystem.cpp
 * @brief Implementation of the asset hot-reload system.
 */

#include "AssetHotReloadSystem.h"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

/**
 * @brief Construct a new AssetHotReloadSystem.
 *
 * Initializes the system with references to the asset registry and loader.
 * The system starts with no watched packages.
 *
 * @param registry Reference to the asset registry for reloading assets
 * @param loader Reference to the asset pack loader for loading packages
 */
AssetHotReloadSystem::AssetHotReloadSystem(AssetRegistry &registry, AssetPackLoader &loader)
    : registry_(registry), loader_(loader)
{
}

/** @brief Destructor - currently no cleanup needed */
AssetHotReloadSystem::~AssetHotReloadSystem() {}

/**
 * @brief Update the system and check for asset file changes.
 *
 * Called each frame to monitor watched asset packages. Checks for file
 * modifications and reloads changed packages automatically.
 *
 * @param world Reference to the game world (unused in this system)
 * @param deltaTime Time elapsed since last update in seconds (unused)
 */
void AssetHotReloadSystem::update(World &world, float deltaTime)
{
    if (checkForChanges())
    {
        reloadChangedPackages();
    }
}

/**
 * @brief Add a package to the watch list for change monitoring.
 *
 * Registers an asset package file to be monitored for changes. Records
 * the initial modification time and adds it to the watch list.
 *
 * @param packagePath Path to the asset package file to watch
 */
void AssetHotReloadSystem::watchPackage(const std::string &packagePath)
{
    WatchedFile watched;
    watched.path = packagePath;
    watched.lastModified = getFileModifiedTime(packagePath);
    watched.needsReload = false;

    watchedFiles_[packagePath] = watched;
    std::cout << "Watching package for changes: " << packagePath << std::endl;
}

/**
 * @brief Check if any watched files have been modified.
 *
 * Iterates through all watched files and compares their current modification
 * times with the last recorded times. Files that have changed are marked
 * for reload.
 *
 * @return true if any files have changed since last check, false otherwise
 */
bool AssetHotReloadSystem::checkForChanges()
{
    bool hasChanges = false;

    for (auto &pair : watchedFiles_)
    {
        WatchedFile &watched = pair.second;
        auto currentTime = getFileModifiedTime(watched.path);

        if (currentTime > watched.lastModified)
        {
            watched.lastModified = currentTime;
            watched.needsReload = true;
            hasChanges = true;
            std::cout << "Detected change in: " << watched.path << std::endl;
        }
    }

    return hasChanges;
}

/**
 * @brief Reload all packages that have been marked as changed.
 *
 * Processes all watched files marked for reload. Currently performs a
 * full registry clear and reload, but a more sophisticated implementation
 * would reload only the changed assets.
 */
void AssetHotReloadSystem::reloadChangedPackages()
{
    for (auto &pair : watchedFiles_)
    {
        WatchedFile &watched = pair.second;

        if (watched.needsReload)
        {
            std::cout << "Reloading package: " << watched.path << std::endl;

            // Clear existing assets from this package
            // In a real implementation, we'd track which assets belong to which package
            // For now, we'll do a full reload
            registry_.clear();

            // Reload the package
            if (loader_.loadPackage(watched.path))
            {
                std::cout << "Successfully reloaded: " << watched.path << std::endl;
            }
            else
            {
                std::cerr << "Failed to reload: " << watched.path << std::endl;
            }

            watched.needsReload = false;
        }
    }
}

/**
 * @brief Get the last modification time of a file.
 *
 * Uses the C++ filesystem library to get the last write time of a file.
 * Handles errors gracefully by returning the minimum time point.
 *
 * @param path Path to the file
 * @return The file's last modification time, or minimum time if file doesn't exist or error occurs
 */
std::chrono::system_clock::time_point AssetHotReloadSystem::getFileModifiedTime(const std::string &path)
{
    try
    {
        if (fs::exists(path))
        {
            auto fileTime = fs::last_write_time(path);
            return std::chrono::system_clock::time_point(
                std::chrono::duration_cast<std::chrono::system_clock::duration>(
                    fileTime.time_since_epoch()));
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error checking file time for " << path << ": " << e.what() << std::endl;
    }

    return std::chrono::system_clock::time_point::min();
}
/**
 * @file AssetHotReloadSystem.h
 * @brief System for monitoring and hot-reloading asset packages during development.
 *
 * This system provides live asset reloading capabilities for development workflows.
 * It monitors asset package files for changes and automatically reloads them
 * when modifications are detected, allowing for rapid iteration during development.
 */

#ifndef ASSET_HOT_RELOAD_SYSTEM_H
#define ASSET_HOT_RELOAD_SYSTEM_H

#include "core/ISystem.h"
#include "core/AssetRegistry.h"
#include "core/AssetPackLoader.h"
#include <string>
#include <unordered_map>
#include <chrono>

/**
 * @class AssetHotReloadSystem
 * @brief System that monitors asset files and reloads them when changed.
 *
 * This system implements hot-reloading of asset packages by monitoring file
 * modification times. When changes are detected, it automatically reloads
 * the affected packages, making development iteration faster and more efficient.
 */
class AssetHotReloadSystem : public ISystem
{
public:
    /**
     * @brief Construct a new AssetHotReloadSystem.
     *
     * @param registry Reference to the asset registry for reloading assets
     * @param loader Reference to the asset pack loader for loading packages
     */
    AssetHotReloadSystem(AssetRegistry &registry, AssetPackLoader &loader);

    /** @brief Destructor */
    ~AssetHotReloadSystem();

    /**
     * @brief Update the system and check for asset file changes.
     *
     * Called each frame to monitor watched asset packages for changes.
     * When changes are detected, marks packages for reloading.
     *
     * @param world Reference to the game world
     * @param deltaTime Time elapsed since last update in seconds
     */
    void update(World &world, float deltaTime) override;

    /**
     * @brief Add a package to the watch list for change monitoring.
     *
     * Registers an asset package file to be monitored for changes.
     * The system will track the modification time of this file.
     *
     * @param packagePath Path to the asset package file to watch
     */
    void watchPackage(const std::string &packagePath);

    /**
     * @brief Check if any watched files have been modified.
     *
     * Scans all watched files and updates their modification status.
     * Files that have changed since last check are marked for reload.
     *
     * @return true if any files have changed, false otherwise
     */
    bool checkForChanges();

    /**
     * @brief Reload all packages that have been marked as changed.
     *
     * Processes all watched files marked for reload and reloads
     * their corresponding asset packages through the asset loader.
     */
    void reloadChangedPackages();

private:
    /** @brief Reference to the asset registry */
    AssetRegistry &registry_;

    /** @brief Reference to the asset pack loader */
    AssetPackLoader &loader_;

    /**
     * @struct WatchedFile
     * @brief Information about a file being watched for changes.
     */
    struct WatchedFile
    {
        /** @brief Path to the watched file */
        std::string path;

        /** @brief Last modification time of the file */
        std::chrono::system_clock::time_point lastModified;

        /** @brief Whether this file needs to be reloaded */
        bool needsReload;
    };

    /** @brief Map of package paths to their watched file information */
    std::unordered_map<std::string, WatchedFile> watchedFiles_;

    /**
     * @brief Get the last modification time of a file.
     *
     * @param path Path to the file
     * @return The file's last modification time, or epoch time if file doesn't exist
     */
    std::chrono::system_clock::time_point getFileModifiedTime(const std::string &path);
};

#endif
#include "BootstrapSystem.h"
#include "events/WorldGenEvents.h"
#include <iostream>
#include <filesystem>

BootstrapSystem::BootstrapSystem(EventBus &eventBus, World &world, AssetRegistry &assetRegistry, AssetPackLoader &assetLoader)
    : eventBus(eventBus), worldRef(world), assetRegistry_(assetRegistry), assetLoader_(assetLoader), initialized(false)
{
}

void BootstrapSystem::update(World &world, float deltaTime)
{
    // Bootstrap system doesn't need continuous updates
}

void BootstrapSystem::Init()
{
    if (initialized)
        return;

    std::cout << "Initializing bootstrap system..." << std::endl;

    // Try to load available packages
    bool packagesLoaded = LoadAvailablePackages();

    if (!packagesLoaded)
    {
        std::cout << "No asset packages found, triggering default world generation..." << std::endl;
        eventBus.publish(NoPackagesFoundEvent{});
    }
    else
    {
        std::cout << "Asset packages loaded successfully. Available packages:" << std::endl;
        for (const auto &package : assetRegistry_.getLoadedPackages())
        {
            std::cout << "  - " << package << std::endl;
        }

        // Check if we have a default scene configuration to use for world generation
        const std::string *defaultScene = assetRegistry_.getDefaultScene();
        if (defaultScene != nullptr)
        {
            std::cout << "Found default scene configuration, triggering world generation from XML..." << std::endl;
            // Trigger world generation with the loaded scene configuration
            eventBus.publish(DefaultWorldGeneratedEvent{});
        }
        else
        {
            std::cout << "No default scene found in loaded packages, falling back to default world generation..." << std::endl;
            eventBus.publish(NoPackagesFoundEvent{});
        }
    }

    initialized = true;
}

void BootstrapSystem::PostFrameUpdate()
{
    // Could handle hot-reloading here in the future
}

bool BootstrapSystem::CheckForAssetPackages()
{
    // Check if assets/packages directory exists and has package files
    std::filesystem::path packagesDir = "assets/packages";

    if (!std::filesystem::exists(packagesDir))
    {
        return false;
    }

    // Check for any .xml package files
    for (const auto &entry : std::filesystem::recursive_directory_iterator(packagesDir))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".xml")
        {
            return true;
        }
    }

    // Check runtime/data/packs for .pak files
    std::filesystem::path packsDir = "assets/runtime/data/packs";

    if (std::filesystem::exists(packsDir))
    {
        for (const auto &entry : std::filesystem::directory_iterator(packsDir))
        {
            if (entry.is_regular_file() && entry.path().extension() == ".pak")
            {
                return true;
            }
        }
    }

    return false;
}

bool BootstrapSystem::LoadAvailablePackages()
{
    std::filesystem::path packagesDir = "assets/packages";

    if (!std::filesystem::exists(packagesDir))
    {
        return false;
    }

    bool loadedAny = false;

    // Load DeveloperPackage first (fallback package)
    std::filesystem::path devPackagePath = packagesDir / "DeveloperPackage" / "package.xml";
    if (std::filesystem::exists(devPackagePath))
    {
        if (assetLoader_.loadPackage(devPackagePath.string()))
        {
            loadedAny = true;
        }
    }

    // Load other packages
    for (const auto &entry : std::filesystem::directory_iterator(packagesDir))
    {
        if (entry.is_directory() && entry.path().filename() != "DeveloperPackage")
        {
            std::filesystem::path packageXml = entry.path() / "package.xml";
            if (std::filesystem::exists(packageXml))
            {
                if (assetLoader_.loadPackage(packageXml.string()))
                {
                    loadedAny = true;
                }
            }
        }
    }

    return loadedAny;
}
#pragma once
#include "core/ISystem.h"
#include "core/EventBus.h"
#include "core/World.h"
#include "core/AssetRegistry.h"
#include "core/AssetPackLoader.h"
#include "events/WorldGenEvents.h"

/**
 * Bootstrap system responsible for initializing the world, loading assets, and checking for asset packages.
 */
class BootstrapSystem : public ISystem
{
public:
    BootstrapSystem(EventBus &eventBus, World &world, AssetRegistry &assetRegistry, AssetPackLoader &assetLoader);
    virtual ~BootstrapSystem() = default;

    void update(World &world, float deltaTime) override;
    void Init();
    void PostFrameUpdate();

private:
    EventBus &eventBus;
    World &worldRef;
    AssetRegistry &assetRegistry_;
    AssetPackLoader &assetLoader_;
    bool initialized;

    bool CheckForAssetPackages();
    bool LoadAvailablePackages();
};
/**
 * @file CelShadingSystem.h
 * @brief Cel-shading (toon shading) rendering system
 *
 * The CelShadingSystem implements stylized cel-shading with band quantization
 * and rim lighting for the voxel busy indicator scene. Features include:
 * - Multi-band light quantization for cartoon appearance
 * - Rim lighting for object definition
 * - Configurable shading parameters
 * - Integration with Math utilities for calculations
 * - Support for multiple light sources
 *
 * @author Generated for Voxel Busy Indicator Scene
 * @date 2024
 */

#pragma once

#include "../math/MathUtils.h"
#include <vector>
#include <cstdint>

/**
 * @brief Cel-shading rendering system
 *
 * Implements stylized cartoon-like shading with quantized lighting
 * bands and rim lighting effects for enhanced visual definition.
 */
class CelShadingSystem
{
public:
    /**
     * @brief Light source definition
     */
    struct Light
    {
        Math::float3 direction; /**< Light direction (normalized) */
        Math::float3 color;     /**< Light color (RGB) */
        float intensity;        /**< Light intensity */
        bool enabled;           /**< Whether light is active */

        Light() : direction{0, -1, 0}, color{1, 1, 1}, intensity(1.0f), enabled(true) {}
        Light(const Math::float3 &dir, const Math::float3 &col, float intens)
            : direction(Math::norm(dir)), color(col), intensity(intens), enabled(true) {}
    };

    /**
     * @brief Cel-shading parameters
     */
    struct CelShadingParams
    {
        uint32_t bandCount;          /**< Number of lighting bands */
        float bandSmoothness;        /**< Smoothness between bands */
        float rimPower;              /**< Rim lighting power */
        float rimIntensity;          /**< Rim lighting intensity */
        Math::float3 rimColor;       /**< Rim lighting color */
        Math::float3 ambientColor;   /**< Ambient light color */
        float ambientIntensity;      /**< Ambient light intensity */
        bool enableRimLighting;      /**< Whether rim lighting is enabled */
        bool enableBandQuantization; /**< Whether to quantize lighting bands */

        CelShadingParams()
            : bandCount(4), bandSmoothness(0.1f), rimPower(2.0f), rimIntensity(0.5f), rimColor{0.8f, 0.9f, 1.0f}, ambientColor{0.2f, 0.3f, 0.4f}, ambientIntensity(0.3f), enableRimLighting(true), enableBandQuantization(true)
        {
        }
    };

    /**
     * @brief Material properties for cel-shading
     */
    struct CelMaterial
    {
        Math::float3 baseColor;   /**< Base material color */
        Math::float3 shadowColor; /**< Color in shadowed areas */
        float roughness;          /**< Surface roughness [0,1] */
        float metallic;           /**< Metallic factor [0,1] */
        float subsurface;         /**< Subsurface scattering [0,1] */

        CelMaterial()
            : baseColor{0.8f, 0.8f, 0.8f}, shadowColor{0.3f, 0.3f, 0.5f}, roughness(0.5f), metallic(0.0f), subsurface(0.0f)
        {
        }

        CelMaterial(const Math::float3 &base, const Math::float3 &shadow)
            : baseColor(base), shadowColor(shadow), roughness(0.5f), metallic(0.0f), subsurface(0.0f)
        {
        }
    };

    /**
     * @brief Shading calculation result
     */
    struct ShadingResult
    {
        Math::float3 finalColor; /**< Final shaded color */
        float lightIntensity;    /**< Overall light intensity */
        float rimFactor;         /**< Rim lighting factor */
        uint32_t activeBand;     /**< Active lighting band index */

        ShadingResult() : finalColor{0, 0, 0}, lightIntensity(0), rimFactor(0), activeBand(0) {}
    };

private:
    /** @brief Current shading parameters */
    CelShadingParams params;

    /** @brief Active light sources */
    std::vector<Light> lights;

    /** @brief Cached band thresholds for performance */
    std::vector<float> bandThresholds;

public:
    /**
     * @brief Construct a new CelShadingSystem
     *
     * @param shadingParams Initial shading parameters
     */
    CelShadingSystem(const CelShadingParams &shadingParams = CelShadingParams())
        : params(shadingParams)
    {
        updateBandThresholds();
        setupDefaultLighting();
    }

    /**
     * @brief Calculate cel-shaded lighting for a surface point
     *
     * @param position World position of the surface point
     * @param normal Surface normal (normalized)
     * @param viewDirection Direction to viewer (normalized)
     * @param material Material properties
     * @return Shading calculation result
     */
    ShadingResult calculateShading(const Math::float3 &position,
                                   const Math::float3 &normal,
                                   const Math::float3 &viewDirection,
                                   const CelMaterial &material)
    {
        ShadingResult result;

        // Start with ambient lighting
        Math::float3 color = Math::scale(
            Math::mul(params.ambientColor, material.baseColor),
            params.ambientIntensity);

        float totalLightIntensity = 0.0f;

        // Process each light source
        for (const auto &light : lights)
        {
            if (!light.enabled)
                continue;

            // Calculate lighting contribution
            float dotNL = Math::dot(normal, Math::scale(light.direction, -1.0f));
            float lightContribution = Math::clamp(dotNL, 0.0f, 1.0f);

            // Apply cel-shading quantization
            if (params.enableBandQuantization)
            {
                lightContribution = quantizeToBands(lightContribution);
            }

            // Combine with light color and intensity
            Math::float3 lightColor = Math::scale(
                Math::mul(light.color, material.baseColor),
                lightContribution * light.intensity);

            color = Math::add(color, lightColor);
            totalLightIntensity += lightContribution * light.intensity;
        }

        // Apply rim lighting if enabled
        float rimFactor = 0.0f;
        if (params.enableRimLighting)
        {
            rimFactor = calculateRimLighting(normal, viewDirection);
            Math::float3 rimContribution = Math::scale(params.rimColor, rimFactor * params.rimIntensity);
            color = Math::add(color, rimContribution);
        }

        // Apply shadow color mixing in dark areas
        float shadowFactor = 1.0f - Math::clamp(totalLightIntensity, 0.0f, 1.0f);
        if (shadowFactor > 0.0f)
        {
            Math::float3 shadowContribution = Math::scale(material.shadowColor, shadowFactor);
            color = Math::lerp3(color, shadowContribution, shadowFactor * 0.5f);
        }

        // Store results
        result.finalColor = color;
        result.lightIntensity = totalLightIntensity;
        result.rimFactor = rimFactor;
        result.activeBand = getBandIndex(totalLightIntensity);

        return result;
    }

    /**
     * @brief Set cel-shading parameters
     *
     * @param newParams New shading parameters
     */
    void setParams(const CelShadingParams &newParams)
    {
        params = newParams;
        updateBandThresholds();
    }

    /**
     * @brief Get current cel-shading parameters
     *
     * @return Current parameters
     */
    const CelShadingParams &getParams() const
    {
        return params;
    }

    /**
     * @brief Add a light source
     *
     * @param light Light to add
     */
    void addLight(const Light &light)
    {
        lights.push_back(light);
    }

    /**
     * @brief Remove all lights
     */
    void clearLights()
    {
        lights.clear();
    }

    /**
     * @brief Set directional light (sun/moon)
     *
     * @param direction Light direction
     * @param color Light color
     * @param intensity Light intensity
     */
    void setDirectionalLight(const Math::float3 &direction,
                             const Math::float3 &color = {1, 1, 1},
                             float intensity = 1.0f)
    {
        clearLights();
        addLight(Light(direction, color, intensity));
    }

    /**
     * @brief Setup default three-point lighting
     */
    void setupDefaultLighting()
    {
        clearLights();

        // Key light (main directional light)
        addLight(Light({-0.3f, -0.7f, -0.6f}, {1.0f, 0.95f, 0.8f}, 1.0f));

        // Fill light (softer secondary light)
        addLight(Light({0.5f, -0.2f, 0.8f}, {0.6f, 0.7f, 1.0f}, 0.4f));

        // Rim light (back light for definition)
        addLight(Light({0.2f, 0.8f, -0.5f}, {0.9f, 0.9f, 1.0f}, 0.3f));
    }

    /**
     * @brief Get number of active lights
     *
     * @return Number of enabled lights
     */
    size_t getActiveLightCount() const
    {
        size_t count = 0;
        for (const auto &light : lights)
        {
            if (light.enabled)
                count++;
        }
        return count;
    }

private:
    /**
     * @brief Quantize light intensity to discrete bands
     *
     * @param intensity Input light intensity [0,1]
     * @return Quantized intensity
     */
    float quantizeToBands(float intensity)
    {
        if (bandThresholds.empty())
            return intensity;

        // Use Math utility for band quantization
        return Math::quantizeToBands(intensity, bandThresholds, params.bandSmoothness);
    }

    /**
     * @brief Calculate rim lighting factor
     *
     * @param normal Surface normal
     * @param viewDirection View direction
     * @return Rim lighting factor [0,1]
     */
    float calculateRimLighting(const Math::float3 &normal, const Math::float3 &viewDirection)
    {
        return Math::calculateRimLighting(normal, viewDirection, params.rimPower);
    }

    /**
     * @brief Get the active lighting band index
     *
     * @param intensity Light intensity
     * @return Band index
     */
    uint32_t getBandIndex(float intensity)
    {
        for (size_t i = 0; i < bandThresholds.size(); ++i)
        {
            if (intensity <= bandThresholds[i])
            {
                return static_cast<uint32_t>(i);
            }
        }
        return static_cast<uint32_t>(bandThresholds.size() - 1);
    }

    /**
     * @brief Update cached band threshold values
     */
    void updateBandThresholds()
    {
        bandThresholds.clear();
        if (params.bandCount == 0)
            return;

        // Create evenly spaced thresholds
        for (uint32_t i = 1; i <= params.bandCount; ++i)
        {
            float threshold = static_cast<float>(i) / static_cast<float>(params.bandCount);
            bandThresholds.push_back(threshold);
        }
    }
};
/**
 * @file CloudPrecessionSystem.h
 * @brief Animation system for voxel cloud orbital precession
 *
 * The CloudPrecessionSystem manages the complex orbital motion of
 * voxel cloud formations with precession and lifecycle management.
 * Features include:
 * - Dual orbital system management (primary + precession)
 * - Cloud lifecycle coordination (spawn, active, despawn)
 * - Hierarchical cloud organization
 * - Performance optimization for large cloud systems
 * - Integration with Math utilities for orbital calculations
 *
 * @author Generated for Voxel Busy Indicator Scene
 * @date 2024
 */

#pragma once

#include "../math/MathUtils.h"
#include "../components/VoxelCloudC.h"
#include "../components/TransformC.h"
#include <vector>
#include <memory>
#include <unordered_map>
#include <queue>

/**
 * @brief Animation system for voxel cloud precession
 *
 * Manages complex orbital cloud formations with precession,
 * lifecycle management, and hierarchical organization.
 */
class CloudPrecessionSystem
{
public:
    /**
     * @brief Entity with cloud precession
     */
    struct CloudEntity
    {
        uint32_t entityId;                     /**< Entity identifier */
        std::shared_ptr<VoxelCloudC> cloud;    /**< Voxel cloud component */
        std::shared_ptr<TransformC> transform; /**< Transform component */
        bool active;                           /**< Whether entity is active */
        float spawnTime;                       /**< Time when cloud was spawned */

        CloudEntity(uint32_t id, std::shared_ptr<VoxelCloudC> cl, std::shared_ptr<TransformC> trans)
            : entityId(id), cloud(cl), transform(trans), active(true), spawnTime(0.0f) {}
    };

    /**
     * @brief Cloud formation for organized group behavior
     */
    struct CloudFormation
    {
        std::string name;                /**< Formation name */
        std::vector<uint32_t> entityIds; /**< Clouds in this formation */
        Math::float3 centerPoint;        /**< Formation center point */
        float formationRadius;           /**< Formation extent radius */
        float rotationSpeed;             /**< Formation rotation speed */
        float precessionSpeed;           /**< Formation precession speed */
        Math::float3 precessionAxis;     /**< Formation precession axis */
        bool synchronized;               /**< Whether formation is synchronized */

        CloudFormation(const std::string &formationName = "default")
            : name(formationName), centerPoint{0, 0, 0}, formationRadius(10.0f), rotationSpeed(0.1f), precessionSpeed(0.02f), precessionAxis{0, 1, 0}, synchronized(true)
        {
        }
    };

    /**
     * @brief Cloud spawning configuration
     */
    struct SpawnConfig
    {
        float spawnRate;          /**< Clouds per second */
        float spawnRadius;        /**< Spawn radius from center */
        float cloudLifetime;      /**< Individual cloud lifetime */
        uint32_t maxClouds;       /**< Maximum concurrent clouds */
        Math::float3 spawnCenter; /**< Center point for spawning */
        float randomOffset;       /**< Random position offset */

        SpawnConfig()
            : spawnRate(0.1f), spawnRadius(8.0f), cloudLifetime(60.0f), maxClouds(20), spawnCenter{0, 0, 0}, randomOffset(2.0f)
        {
        }
    };

    /**
     * @brief System performance statistics
     */
    struct PerformanceStats
    {
        uint32_t totalClouds;     /**< Total active clouds */
        uint32_t totalVoxels;     /**< Total active voxel elements */
        float updateTime;         /**< Last update time in milliseconds */
        uint32_t cloudsSpawned;   /**< Clouds spawned this frame */
        uint32_t cloudsDespawned; /**< Clouds despawned this frame */

        PerformanceStats() : totalClouds(0), totalVoxels(0), updateTime(0), cloudsSpawned(0), cloudsDespawned(0) {}
    };

private:
    /** @brief All registered cloud entities */
    std::vector<CloudEntity> entities;

    /** @brief Cloud formations for organized behavior */
    std::unordered_map<std::string, CloudFormation> formations;

    /** @brief Spawn configuration */
    SpawnConfig spawnConfig;

    /** @brief Global time accumulator */
    float globalTime;

    /** @brief Global time scale */
    float globalTimeScale;

    /** @brief Whether system is active */
    bool systemActive;

    /** @brief Performance statistics */
    PerformanceStats stats;

    /** @brief Spawn timer accumulator */
    float spawnTimer;

    /** @brief Global center point for orbital motion */
    Math::float3 globalCenter;

    /** @brief Random state for procedural generation */
    uint32_t randomState;

    /** @brief Queue of entities to be removed */
    std::queue<uint32_t> removalQueue;

public:
    /**
     * @brief Construct a new CloudPrecessionSystem
     *
     * @param center Global center point for cloud motion
     */
    CloudPrecessionSystem(const Math::float3 &center = {0, 0, 0})
        : globalTime(0.0f), globalTimeScale(1.0f), systemActive(true), spawnTimer(0.0f), globalCenter(center), randomState(12345)
    {
        // Create default formation
        formations["default"] = CloudFormation("default");
    }

    /**
     * @brief Update all cloud animations
     *
     * @param deltaTime Time elapsed since last frame
     */
    void update(float deltaTime)
    {
        if (!systemActive)
            return;

        // Reset frame statistics
        stats.cloudsSpawned = 0;
        stats.cloudsDespawned = 0;
        stats.totalClouds = 0;
        stats.totalVoxels = 0;

        float startTime = globalTime; // For performance measurement

        float scaledDeltaTime = deltaTime * globalTimeScale;
        globalTime += scaledDeltaTime;
        spawnTimer += scaledDeltaTime;

        // Update all cloud entities
        for (auto &entity : entities)
        {
            if (!entity.active || !entity.cloud || !entity.transform)
                continue;

            updateCloudEntity(entity, scaledDeltaTime);
            stats.totalClouds++;
        }

        // Update formations
        updateFormations(scaledDeltaTime);

        // Handle spawning
        updateSpawning();

        // Handle removal of despawned clouds
        updateRemoval();

        // Calculate performance metrics
        stats.updateTime = (globalTime - startTime) * 1000.0f; // Convert to milliseconds
    }

    /**
     * @brief Register an entity for cloud animation
     *
     * @param entityId Entity identifier
     * @param cloud Voxel cloud component
     * @param transform Transform component
     * @param formationName Formation to assign entity to
     */
    void registerEntity(uint32_t entityId,
                        std::shared_ptr<VoxelCloudC> cloud,
                        std::shared_ptr<TransformC> transform,
                        const std::string &formationName = "default")
    {
        entities.emplace_back(entityId, cloud, transform);
        entities.back().spawnTime = globalTime;

        // Add to formation
        auto &formation = getOrCreateFormation(formationName);
        formation.entityIds.push_back(entityId);
    }

    /**
     * @brief Unregister an entity from cloud animation
     *
     * @param entityId Entity to remove
     */
    void unregisterEntity(uint32_t entityId)
    {
        // Remove from entities list
        entities.erase(
            std::remove_if(entities.begin(), entities.end(),
                           [entityId](const CloudEntity &e)
                           { return e.entityId == entityId; }),
            entities.end());

        // Remove from all formations
        for (auto &[formationName, formation] : formations)
        {
            formation.entityIds.erase(
                std::remove(formation.entityIds.begin(), formation.entityIds.end(), entityId),
                formation.entityIds.end());
        }
    }

    /**
     * @brief Create or get a cloud formation
     *
     * @param formationName Name of the formation
     * @return Reference to the formation
     */
    CloudFormation &getOrCreateFormation(const std::string &formationName)
    {
        if (formations.find(formationName) == formations.end())
        {
            formations[formationName] = CloudFormation(formationName);
        }
        return formations[formationName];
    }

    /**
     * @brief Set formation parameters
     *
     * @param formationName Formation name
     * @param centerPoint Formation center
     * @param radius Formation radius
     * @param rotationSpeed Formation rotation speed
     * @param precessionSpeed Formation precession speed
     */
    void setFormationParams(const std::string &formationName,
                            const Math::float3 &centerPoint = {0, 0, 0},
                            float radius = 10.0f,
                            float rotationSpeed = 0.1f,
                            float precessionSpeed = 0.02f)
    {
        auto &formation = getOrCreateFormation(formationName);
        formation.centerPoint = centerPoint;
        formation.formationRadius = radius;
        formation.rotationSpeed = rotationSpeed;
        formation.precessionSpeed = precessionSpeed;
    }

    /**
     * @brief Set spawn configuration
     *
     * @param config New spawn configuration
     */
    void setSpawnConfig(const SpawnConfig &config)
    {
        spawnConfig = config;
    }

    /**
     * @brief Get current spawn configuration
     *
     * @return Current spawn config
     */
    const SpawnConfig &getSpawnConfig() const
    {
        return spawnConfig;
    }

    /**
     * @brief Set global center point
     *
     * @param center New global center
     */
    void setGlobalCenter(const Math::float3 &center)
    {
        globalCenter = center;
    }

    /**
     * @brief Get global center point
     *
     * @return Current global center
     */
    const Math::float3 &getGlobalCenter() const
    {
        return globalCenter;
    }

    /**
     * @brief Set global time scale
     *
     * @param scale Time scaling factor (1.0 = normal speed)
     */
    void setGlobalTimeScale(float scale)
    {
        globalTimeScale = scale;
    }

    /**
     * @brief Get global time scale
     *
     * @return Current time scale
     */
    float getGlobalTimeScale() const
    {
        return globalTimeScale;
    }

    /**
     * @brief Pause/resume cloud animations
     *
     * @param active Whether system should be active
     */
    void setActive(bool active)
    {
        systemActive = active;
    }

    /**
     * @brief Check if system is active
     *
     * @return True if system is running
     */
    bool isActive() const
    {
        return systemActive;
    }

    /**
     * @brief Get performance statistics
     *
     * @return Current performance stats
     */
    const PerformanceStats &getPerformanceStats() const
    {
        return stats;
    }

    /**
     * @brief Get number of registered entities
     *
     * @return Entity count
     */
    size_t getEntityCount() const
    {
        return entities.size();
    }

    /**
     * @brief Get number of active entities
     *
     * @return Active entity count
     */
    size_t getActiveEntityCount() const
    {
        size_t count = 0;
        for (const auto &entity : entities)
        {
            if (entity.active)
                count++;
        }
        return count;
    }

private:
    /**
     * @brief Update a single cloud entity
     *
     * @param entity Entity to update
     * @param deltaTime Time delta for this update
     */
    void updateCloudEntity(CloudEntity &entity, float deltaTime)
    {
        // Update cloud component with global center
        entity.cloud->update(deltaTime, globalCenter);

        // Get current world position and orientation from cloud
        Math::float3 position = entity.cloud->getWorldPosition();
        Math::quat orientation = entity.cloud->getWorldOrientation();

        // Update transform component
        entity.transform->setPosition(position);
        entity.transform->setRotation(orientation);

        // Count voxel elements for statistics
        auto elements = entity.cloud->getActiveElements();
        stats.totalVoxels += elements.size();

        // Check if cloud should be despawned
        if (entity.cloud->shouldDestroy())
        {
            removalQueue.push(entity.entityId);
            stats.cloudsDespawned++;
        }
    }

    /**
     * @brief Update all formations
     *
     * @param deltaTime Time delta for this update
     */
    void updateFormations(float deltaTime)
    {
        for (auto &[formationName, formation] : formations)
        {
            updateFormation(formation, deltaTime);
        }
    }

    /**
     * @brief Update a specific cloud formation
     *
     * @param formation Formation to update
     * @param deltaTime Time delta for this update
     */
    void updateFormation(CloudFormation &formation, float deltaTime)
    {
        if (!formation.synchronized || formation.entityIds.empty())
            return;

        // Calculate formation-level transformations
        float rotationAngle = globalTime * formation.rotationSpeed;
        float precessionAngle = globalTime * formation.precessionSpeed;

        // Apply formation-level effects to member clouds
        for (uint32_t entityId : formation.entityIds)
        {
            for (auto &entity : entities)
            {
                if (entity.entityId == entityId && entity.active && entity.cloud)
                {
                    applyFormationEffects(entity, formation, rotationAngle, precessionAngle);
                }
            }
        }
    }

    /**
     * @brief Apply formation-level effects to a cloud entity
     *
     * @param entity Cloud entity to affect
     * @param formation Formation parameters
     * @param rotationAngle Current formation rotation
     * @param precessionAngle Current formation precession
     */
    void applyFormationEffects(CloudEntity &entity,
                               const CloudFormation &formation,
                               float rotationAngle,
                               float precessionAngle)
    {
        // Apply formation-level orbital modifications
        auto params = entity.cloud->getParams();

        // Modify primary orbit based on formation
        params.primaryOrbit.phaseOffset += rotationAngle * 0.1f;

        // Modify precession based on formation precession
        params.precessionOrbit.phaseOffset += precessionAngle;

        entity.cloud->setParams(params);
    }

    /**
     * @brief Update cloud spawning
     */
    void updateSpawning()
    {
        if (spawnConfig.spawnRate <= 0.0f)
            return;
        if (getActiveEntityCount() >= spawnConfig.maxClouds)
            return;

        float spawnInterval = 1.0f / spawnConfig.spawnRate;
        while (spawnTimer >= spawnInterval)
        {
            spawnNewCloud();
            spawnTimer -= spawnInterval;
            stats.cloudsSpawned++;
        }
    }

    /**
     * @brief Spawn a new cloud entity
     */
    void spawnNewCloud()
    {
        // Generate random spawn position
        float angle = 2.0f * Math::Pi * Math::rand01(randomState);
        float radius = spawnConfig.spawnRadius * Math::rand01(randomState);

        Math::float3 spawnPos = {
            spawnConfig.spawnCenter.x + radius * std::cos(angle),
            spawnConfig.spawnCenter.y + (Math::rand01(randomState) - 0.5f) * spawnConfig.randomOffset,
            spawnConfig.spawnCenter.z + radius * std::sin(angle)};

        // Create new cloud component with random parameters
        auto cloud = std::make_shared<VoxelCloudC>(spawnConfig.cloudLifetime, randomState);
        auto transform = std::make_shared<TransformC>();

        // Set initial transform
        transform->setPosition(spawnPos);

        // Generate unique entity ID
        uint32_t newEntityId = static_cast<uint32_t>(entities.size()) + 1000;

        // Register the new entity
        registerEntity(newEntityId, cloud, transform, "default");
    }

    /**
     * @brief Update removal of despawned clouds
     */
    void updateRemoval()
    {
        while (!removalQueue.empty())
        {
            uint32_t entityId = removalQueue.front();
            removalQueue.pop();
            unregisterEntity(entityId);
        }
    }
};
#include "ConsoleSystem.h"
#include "../core/World.h"
#include <iostream>

ConsoleSystem::ConsoleSystem(EventBus &eventBus)
    : eventBus(eventBus), isVisible(false)
{
    // Subscribe to console toggle events
    eventBus.subscribe(EventType::ConsoleToggle, [this](const IEvent &event)
                       {
        const auto& toggleEvent = static_cast<const ConsoleToggleEvent&>(event);
        OnConsoleToggle(toggleEvent); });

    AddOutput("Console initialized. Press ~ to toggle visibility.");
}

void ConsoleSystem::update(World &world, float deltaTime)
{
    // Console system doesn't need continuous updates
}

void ConsoleSystem::AddOutput(const std::string &message)
{
    outputBuffer.push_back(message);
    if (outputBuffer.size() > 100) // Limit buffer size
    {
        outputBuffer.erase(outputBuffer.begin());
    }
}

void ConsoleSystem::ExecuteCommand(const std::string &command)
{
    AddOutput("> " + command);

    // TODO: Implement command parsing and execution
    if (command == "help")
    {
        AddOutput("Available commands:");
        AddOutput("  help - Show this help");
        AddOutput("  clear - Clear console");
        AddOutput("  quit - Exit application");
    }
    else if (command == "clear")
    {
        outputBuffer.clear();
        AddOutput("Console cleared.");
    }
    else if (command == "quit")
    {
        AddOutput("Quitting application...");
        // TODO: Publish quit event
    }
    else
    {
        AddOutput("Unknown command: " + command);
    }
}

void ConsoleSystem::ToggleVisibility()
{
    isVisible = !isVisible;
    // TODO: Publish visibility changed event
}

void ConsoleSystem::OnConsoleToggle(const ConsoleToggleEvent &event)
{
    ToggleVisibility();
}

const std::vector<std::string> &ConsoleSystem::GetOutputBuffer() const
{
    return outputBuffer;
}

bool ConsoleSystem::IsVisible() const
{
    return isVisible;
}
#pragma once
#include "../core/ISystem.h"
#include "../core/EventBus.h"
#include "../events/InputEvents.h"
#include <string>
#include <vector>
#include <functional>

class World;

/**
 * Console system for managing developer console state and command processing.
 */
class ConsoleSystem : public ISystem
{
public:
    ConsoleSystem(EventBus &eventBus);
    virtual ~ConsoleSystem() = default;

    void update(World &world, float deltaTime) override;

    void AddOutput(const std::string &message);
    void ExecuteCommand(const std::string &command);
    void ToggleVisibility();

    const std::vector<std::string> &GetOutputBuffer() const;
    bool IsVisible() const;

private:
    EventBus &eventBus;
    bool isVisible;
    std::vector<std::string> outputBuffer;

    void OnConsoleToggle(const ConsoleToggleEvent &event);
};
#pragma once

#include "../core/System.h"
#include "../components/ContrailComponent.h"
#include "../math/MathUtils.h"
#include <vector>
#include <memory>
#include <map>

namespace ECS
{

    // ============================================================================
    // Particle Trail Data Structures
    // ============================================================================

    struct TrailParticle
    {
        Math::float3 position;
        Math::float3 velocity;
        float life = 1.0f; // 0.0 = dead, 1.0 = just spawned
        float size = 1.0f;
        Math::float4 color = {1.0f, 1.0f, 1.0f, 1.0f};
        float age = 0.0f; // Time since spawn

        // Trail-specific properties
        float trailWeight = 1.0f; // Influence on trail curve
        Math::float3 normal;      // For ribbon trails
        float distance = 0.0f;    // Distance along trail
    };

    struct TrailSegment
    {
        Math::float3 startPos;
        Math::float3 endPos;
        Math::float3 startNormal;
        Math::float3 endNormal;
        float startWidth;
        float endWidth;
        Math::float4 startColor;
        Math::float4 endColor;
        float startLife;
        float endLife;
        float length;
    };

    struct TrailMesh
    {
        std::vector<Math::float3> vertices;
        std::vector<Math::float3> normals;
        std::vector<Math::float2> uvs;
        std::vector<Math::float4> colors;
        std::vector<uint32_t> indices;

        bool needsUpdate = true;
        uint32_t vertexBufferId = 0;
        uint32_t indexBufferId = 0;

        void clear();
        void reserve(size_t vertexCount, size_t indexCount);
    };

    // ============================================================================
    // Contrail System Configuration
    // ============================================================================

    struct ContrailSystemConfig
    {
        // Performance settings
        uint32_t maxParticlesPerTrail = 100;
        uint32_t maxActiveTrails = 50;
        float updateFrequency = 60.0f; // Updates per second
        float cullDistance = 1000.0f;  // Distance beyond which trails are culled

        // Quality settings
        uint32_t segmentSubdivisions = 2; // Smoothing subdivisions
        bool enableCollision = false;
        bool enableWindEffect = false;
        bool enableTurbulence = false;

        // Rendering settings
        bool enableAlphaBlending = true;
        bool enableDepthWrite = false;
        bool enableSoftParticles = true;
        float fadeNearDistance = 1.0f;
        float fadeFarDistance = 100.0f;

        // Memory management
        bool useObjectPooling = true;
        uint32_t initialPoolSize = 1000;
        uint32_t poolGrowthSize = 500;
    };

    // ============================================================================
    // Main Contrail System
    // ============================================================================

    class ContrailSystem : public System
    {
    public:
        explicit ContrailSystem(const ContrailSystemConfig &config = ContrailSystemConfig{});
        ~ContrailSystem() override;

        // System interface
        void initialize() override;
        void update(float deltaTime) override;
        void render() override;
        void shutdown() override;

        // Configuration management
        void setConfig(const ContrailSystemConfig &config);
        const ContrailSystemConfig &getConfig() const;

        // Trail management
        void createTrail(EntityId entityId, const ContrailComponent &component);
        void removeTrail(EntityId entityId);
        void updateTrailComponent(EntityId entityId, const ContrailComponent &component);

        // Environmental effects
        void setWindVector(const Math::float3 &wind);
        void setGravity(const Math::float3 &gravity);
        void setTurbulenceIntensity(float intensity);

        // Performance monitoring
        uint32_t getActiveTrailCount() const;
        uint32_t getTotalParticleCount() const;
        float getAverageUpdateTime() const;

        // Debugging and visualization
        void setDebugVisualization(bool enabled);
        bool isDebugVisualizationEnabled() const;
        void renderDebugInfo();

    protected:
        // Component handling
        void onComponentAdded(EntityId entityId, ComponentType type) override;
        void onComponentRemoved(EntityId entityId, ComponentType type) override;
        void onComponentChanged(EntityId entityId, ComponentType type) override;

    private:
        // ============================================================================
        // Internal Trail Management
        // ============================================================================

        struct TrailData
        {
            ContrailComponent component;
            std::vector<TrailParticle> particles;
            TrailMesh mesh;

            // State tracking
            Math::float3 lastPosition;
            float timeSinceLastEmit = 0.0f;
            float totalLifeTime = 0.0f;
            bool isActive = true;

            // Performance data
            float lastUpdateTime = 0.0f;
            uint32_t particleCount = 0;

            TrailData() = default;
            TrailData(const ContrailComponent &comp) : component(comp) {}
        };

        ContrailSystemConfig config_;
        std::map<EntityId, std::unique_ptr<TrailData>> activeTrails_;

        // Environmental forces
        Math::float3 windVector_ = {0.0f, 0.0f, 0.0f};
        Math::float3 gravity_ = {0.0f, -9.81f, 0.0f};
        float turbulenceIntensity_ = 0.0f;

        // Performance tracking
        mutable float averageUpdateTime_ = 0.0f;
        mutable uint32_t updateSampleCount_ = 0;

        // Debug visualization
        bool debugVisualization_ = false;

        // Object pooling for performance
        std::vector<TrailParticle> particlePool_;
        std::vector<size_t> freeParticleIndices_;

        // ============================================================================
        // Core Update Methods
        // ============================================================================

        void updateTrailEmission(EntityId entityId, TrailData &trail, float deltaTime);
        void updateTrailParticles(TrailData &trail, float deltaTime);
        void updateTrailMesh(TrailData &trail);
        void cullDistantTrails();

        // ============================================================================
        // Particle Management
        // ============================================================================

        void emitParticle(TrailData &trail, const Math::float3 &position, const Math::float3 &velocity);
        void updateParticlePhysics(TrailParticle &particle, float deltaTime);
        void applyEnvironmentalForces(TrailParticle &particle, float deltaTime);
        void killExpiredParticles(TrailData &trail);

        // ============================================================================
        // Mesh Generation
        // ============================================================================

        void generateTrailMesh(TrailData &trail);
        void generateRibbonMesh(TrailData &trail);
        void generateTubeMesh(TrailData &trail);
        void smoothTrailCurve(std::vector<TrailParticle> &particles);
        void calculateTrailNormals(std::vector<TrailParticle> &particles);

        std::vector<TrailSegment> generateTrailSegments(const std::vector<TrailParticle> &particles);
        void addQuadToMesh(TrailMesh &mesh, const TrailSegment &segment, float uvStart, float uvEnd);
        void addTriangleToMesh(TrailMesh &mesh, const Math::float3 &v0, const Math::float3 &v1, const Math::float3 &v2,
                               const Math::float3 &n0, const Math::float3 &n1, const Math::float3 &n2,
                               const Math::float2 &uv0, const Math::float2 &uv1, const Math::float2 &uv2,
                               const Math::float4 &c0, const Math::float4 &c1, const Math::float4 &c2);

        // ============================================================================
        // Rendering Support
        // ============================================================================

        void renderTrail(const TrailData &trail);
        void setupTrailMaterial(const ContrailComponent &component);
        void bindTrailTextures(const ContrailComponent &component);
        void updateTrailUniforms(const ContrailComponent &component);

        // ============================================================================
        // Utility Methods
        // ============================================================================

        Math::float3 getEntityPosition(EntityId entityId) const;
        Math::float3 getEntityVelocity(EntityId entityId) const;
        float calculateEmissionRate(const ContrailComponent &component) const;
        Math::float4 calculateParticleColor(const ContrailComponent &component, float life) const;
        float calculateParticleSize(const ContrailComponent &component, float life) const;

        // Interpolation and smoothing
        Math::float3 catmullRomSpline(const Math::float3 &p0, const Math::float3 &p1,
                                      const Math::float3 &p2, const Math::float3 &p3, float t);
        Math::float3 calculateTangent(const std::vector<TrailParticle> &particles, size_t index);
        Math::float3 calculateBinormal(const Math::float3 &tangent, const Math::float3 &normal);

        // Object pooling
        TrailParticle *acquireParticle();
        void releaseParticle(TrailParticle *particle);
        void expandParticlePool();

        // Performance optimization
        bool shouldUpdateTrail(const TrailData &trail, float deltaTime) const;
        float calculateLODFactor(EntityId entityId) const;
        void optimizeTrailMesh(TrailMesh &mesh);

        // ============================================================================
        // Physics and Forces
        // ============================================================================

        Math::float3 calculateAerodynamicForce(const TrailParticle &particle, const Math::float3 &velocity) const;
        Math::float3 calculateTurbulence(const Math::float3 &position, float time) const;
        Math::float3 calculateWindForce(const TrailParticle &particle) const;
        void handleCollisions(TrailParticle &particle) const;

        // ============================================================================
        // Debug and Profiling
        // ============================================================================

        void renderTrailDebugInfo(const TrailData &trail, EntityId entityId);
        void updatePerformanceCounters(float deltaTime);
        void logTrailStatistics() const;
    };

    // ============================================================================
    // Inline Implementation for Performance-Critical Methods
    // ============================================================================

    inline void TrailMesh::clear()
    {
        vertices.clear();
        normals.clear();
        uvs.clear();
        colors.clear();
        indices.clear();
        needsUpdate = true;
    }

    inline void TrailMesh::reserve(size_t vertexCount, size_t indexCount)
    {
        vertices.reserve(vertexCount);
        normals.reserve(vertexCount);
        uvs.reserve(vertexCount);
        colors.reserve(vertexCount);
        indices.reserve(indexCount);
    }

    inline uint32_t ContrailSystem::getActiveTrailCount() const
    {
        return static_cast<uint32_t>(activeTrails_.size());
    }

    inline uint32_t ContrailSystem::getTotalParticleCount() const
    {
        uint32_t total = 0;
        for (const auto &[entityId, trail] : activeTrails_)
        {
            total += trail->particleCount;
        }
        return total;
    }

    inline float ContrailSystem::getAverageUpdateTime() const
    {
        return averageUpdateTime_;
    }

    inline bool ContrailSystem::isDebugVisualizationEnabled() const
    {
        return debugVisualization_;
    }

    inline void ContrailSystem::setDebugVisualization(bool enabled)
    {
        debugVisualization_ = enabled;
    }

    inline const ContrailSystemConfig &ContrailSystem::getConfig() const
    {
        return config_;
    }

} // namespace ECS
#include "InputSystem.h"
#include "core/World.h"

InputSystem::InputSystem(EventBus &eventBus, IInputDevice &inputDevice)
    : eventBus_(eventBus), inputDevice_(inputDevice) {}

void InputSystem::update(World &world, float dt)
{
    inputDevice_.poll();
    // Process input
}
#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H

#include "core/ISystem.h"
#include "core/EventBus.h"
#include "platform/IInputDevice.h"

class InputSystem : public ISystem
{
public:
    InputSystem(EventBus &eventBus, IInputDevice &inputDevice);
    void update(World &world, float dt) override;

private:
    EventBus &eventBus_;
    IInputDevice &inputDevice_;
};

#endif
#include "MaterialManager.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>

namespace Material
{
    MaterialManager::MaterialManager()
        : textureGenerator_(nullptr)
    {
        std::cout << "MaterialManager initialized" << std::endl;
    }

    bool MaterialManager::LoadMaterial(const std::string &materialId, const Material &material)
    {
        if (materialId.empty())
        {
            std::cerr << "Error: Cannot load material with empty ID" << std::endl;
            return false;
        }

        if (HasMaterial(materialId))
        {
            std::cout << "Warning: Overwriting existing material: " << materialId << std::endl;
        }

        materials_[materialId] = material;

        // Apply global cel-shading settings if not specifically set
        if (materials_[materialId].properties.toonSteps == 4)
        {
            ApplyGlobalCelShadingSettings(materials_[materialId].properties);
        }

        std::cout << "Loaded material: " << materialId << " (type: " << material.type << ")" << std::endl;
        return true;
    }

    std::optional<Material> MaterialManager::GetMaterial(const std::string &materialId) const
    {
        auto it = materials_.find(materialId);
        if (it != materials_.end())
        {
            return it->second;
        }
        return std::nullopt;
    }

    bool MaterialManager::HasMaterial(const std::string &materialId) const
    {
        return materials_.find(materialId) != materials_.end();
    }

    std::string MaterialManager::CreateDynamicMaterial(const std::string &baseType, const MaterialProperties &properties)
    {
        std::string materialId = GenerateUniqueMaterialId(baseType);

        Material material(materialId, baseType);
        material.properties = properties;
        material.isDynamic = true;

        ApplyGlobalCelShadingSettings(material.properties);

        if (LoadMaterial(materialId, material))
        {
            return materialId;
        }

        return "";
    }

    std::string MaterialManager::CreateEarthMaterial(float radius, int detailLevel)
    {
        std::string materialId = GenerateUniqueMaterialId("earth");

        Material material(materialId, "earth");
        material.properties = CreateEarthProperties(radius, detailLevel);
        material.isDynamic = true;

        // Generate and assign textures if texture generator is available
        if (textureGenerator_)
        {
            AssignEarthTextures(material.properties, radius, detailLevel);
        }

        if (LoadMaterial(materialId, material))
        {
            return materialId;
        }

        return "";
    }

    std::string MaterialManager::CreateAtmosphereMaterial(int layer, float density)
    {
        std::string materialId = GenerateUniqueMaterialId("atmosphere");

        Material material(materialId, "atmosphere");
        material.properties = CreateAtmosphereProperties(layer, density);
        material.isDynamic = true;

        if (textureGenerator_)
        {
            AssignAtmosphereTextures(material.properties, layer);
        }

        if (LoadMaterial(materialId, material))
        {
            return materialId;
        }

        return "";
    }

    std::string MaterialManager::CreateCloudMaterial(float coverage, float density)
    {
        std::string materialId = GenerateUniqueMaterialId("cloud");

        Material material(materialId, "cloud");
        material.properties = CreateCloudProperties(coverage, density);
        material.isDynamic = true;

        if (textureGenerator_)
        {
            AssignCloudTextures(material.properties, coverage);
        }

        if (LoadMaterial(materialId, material))
        {
            return materialId;
        }

        return "";
    }

    std::string MaterialManager::CreateContrailMaterial(const Math::float3 &color)
    {
        std::string materialId = GenerateUniqueMaterialId("contrail");

        Material material(materialId, "contrail");
        material.properties = CreateContrailProperties(color);
        material.isDynamic = true;

        if (textureGenerator_)
        {
            AssignContrailTextures(material.properties);
        }

        if (LoadMaterial(materialId, material))
        {
            return materialId;
        }

        return "";
    }

    void MaterialManager::SetGlobalCelShadingParams(int toonSteps, float threshold, bool enableRim)
    {
        globalToonSteps_ = std::max(1, std::min(toonSteps, 16));
        globalToonThreshold_ = std::max(0.0f, std::min(threshold, 1.0f));
        globalRimLighting_ = enableRim;

        std::cout << "Updated global cel-shading: " << globalToonSteps_ << " steps, "
                  << globalToonThreshold_ << " threshold, rim: " << (globalRimLighting_ ? "enabled" : "disabled") << std::endl;
    }

    void MaterialManager::EnableOutlinesForMaterial(const std::string &materialId, float width, const Math::float3 &color)
    {
        auto it = materials_.find(materialId);
        if (it != materials_.end())
        {
            it->second.properties.enableOutlines = true;
            it->second.properties.outlineWidth = std::max(0.001f, std::min(width, 0.1f));
            it->second.properties.outlineColor = color;
            std::cout << "Enabled outlines for material: " << materialId << std::endl;
        }
        else
        {
            std::cerr << "Error: Material not found: " << materialId << std::endl;
        }
    }

    void MaterialManager::SetMaterialAnimation(const std::string &materialId, const std::string &animType, float speed)
    {
        auto it = materials_.find(materialId);
        if (it != materials_.end())
        {
            it->second.properties.isAnimated = true;
            it->second.properties.animationType = animType;
            it->second.properties.animationSpeed = std::max(0.1f, std::min(speed, 10.0f));
            std::cout << "Set animation for material: " << materialId << " (" << animType << ", speed: " << speed << ")" << std::endl;
        }
        else
        {
            std::cerr << "Error: Material not found: " << materialId << std::endl;
        }
    }

    void MaterialManager::SetTextureGenerator(const ProceduralTexture::ProceduralTextureGenerator *generator)
    {
        textureGenerator_ = generator;
        std::cout << "Texture generator assigned to MaterialManager" << std::endl;
    }

    AssetId MaterialManager::GenerateAndAssignTexture(const std::string &materialId, const std::string &textureType)
    {
        if (!textureGenerator_)
        {
            std::cerr << "Error: No texture generator available" << std::endl;
            return "";
        }

        auto it = materials_.find(materialId);
        if (it == materials_.end())
        {
            std::cerr << "Error: Material not found: " << materialId << std::endl;
            return "";
        }

        // Create texture parameters based on material type and texture type
        ProceduralTexture::TextureParams params;
        params.width = 512;
        params.height = 512;
        params.name = materialId + "_" + textureType;

        if (it->second.type == "earth")
        {
            if (textureType == "albedo")
            {
                params.type = ProceduralTexture::TextureParams::Type::Noise;
                params.noise.type = ProceduralTexture::NoiseParams::Type::Perlin;
                params.noise.frequency = 0.01f;
                params.noise.octaves = 4;
            }
            else if (textureType == "normal")
            {
                params.type = ProceduralTexture::TextureParams::Type::Noise;
                params.noise.type = ProceduralTexture::NoiseParams::Type::Simplex;
                params.noise.frequency = 0.005f;
                params.noise.octaves = 3;
            }
        }
        else if (it->second.type == "atmosphere")
        {
            params.type = ProceduralTexture::TextureParams::Type::Gradient;
            params.gradient.type = ProceduralTexture::GradientParams::Type::Linear;
        }
        else if (it->second.type == "cloud")
        {
            params.type = ProceduralTexture::TextureParams::Type::Noise;
            params.noise.type = ProceduralTexture::NoiseParams::Type::Perlin;
            params.noise.frequency = 0.02f;
            params.noise.octaves = 4;
        }

        // Generate the texture (for now just return the name as AssetId)
        // In a real implementation, this would generate the texture and register it in an asset system
        AssetId textureId = params.name + "_generated";

        if (!textureId.empty())
        {
            // Assign to material
            if (textureType == "albedo")
            {
                it->second.properties.albedoTexture = textureId;
            }
            else if (textureType == "normal")
            {
                it->second.properties.normalTexture = textureId;
            }
            else if (textureType == "emission")
            {
                it->second.properties.emissionTexture = textureId;
            }

            std::cout << "Generated and assigned " << textureType << " texture to material: " << materialId << std::endl;
        }

        return textureId;
    }

    void MaterialManager::LoadDefaultMaterials()
    {
        std::cout << "Loading default materials..." << std::endl;

        // Load materials from the developer package
        if (LoadMaterialsFromFile("assets/packages/DeveloperPackage/materials.xml"))
        {
            std::cout << "Default materials loaded successfully" << std::endl;
            return;
        }

        // Fallback to hardcoded materials if file loading fails
        std::cerr << "Failed to load materials from file, using hardcoded defaults" << std::endl;

        // Default Earth material (blue)
        Material earthMaterial("EarthSurfaceMaterial", "earth");
        earthMaterial.properties.albedo = {0.2f, 0.4f, 0.9f}; // Blue earth
        earthMaterial.properties.roughness = 0.8f;
        earthMaterial.properties.metallic = 0.0f;
        earthMaterial.properties.toonSteps = 6;
        earthMaterial.properties.enableRimLighting = true;
        earthMaterial.properties.rimColor = {0.8f, 0.9f, 1.0f};
        LoadMaterial("EarthSurfaceMaterial", earthMaterial);

        // Default atmosphere material
        Material atmosphereMaterial("AtmosphereMaterial", "atmosphere");
        atmosphereMaterial.properties.albedo = {0.5f, 0.7f, 1.0f};
        atmosphereMaterial.properties.roughness = 0.0f;
        atmosphereMaterial.properties.metallic = 0.0f;
        atmosphereMaterial.properties.toonSteps = 3;
        atmosphereMaterial.properties.enableRimLighting = true;
        atmosphereMaterial.properties.rimStrength = 2.0f;
        LoadMaterial("AtmosphereMaterial", atmosphereMaterial);

        // Default cloud material
        Material cloudMaterial("CloudMaterial", "cloud");
        cloudMaterial.properties.albedo = {1.0f, 1.0f, 1.0f};
        cloudMaterial.properties.roughness = 0.1f;
        cloudMaterial.properties.toonSteps = 4;
        cloudMaterial.properties.isAnimated = true;
        cloudMaterial.properties.animationType = "scroll";
        cloudMaterial.properties.animationSpeed = 0.5f;
        LoadMaterial("CloudMaterial", cloudMaterial);

        // Default contrail material
        Material contrailMaterial("ContrailMaterial", "contrail");
        contrailMaterial.properties.albedo = {1.0f, 1.0f, 1.0f};
        contrailMaterial.properties.emission = {0.1f, 0.1f, 0.1f};
        contrailMaterial.properties.roughness = 0.0f;
        contrailMaterial.properties.toonSteps = 2;
        contrailMaterial.properties.isAnimated = true;
        contrailMaterial.properties.animationType = "wave";
        LoadMaterial("ContrailMaterial", contrailMaterial);

        std::cout << "Hardcoded default materials loaded" << std::endl;
    }

    bool MaterialManager::LoadMaterialsFromFile(const std::string &filePath)
    {
        // Read XML file
        std::ifstream file(filePath);
        if (!file.is_open())
        {
            std::cerr << "Failed to open materials file: " << filePath << std::endl;
            return false;
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string xmlContent = buffer.str();
        file.close();

        size_t materialsStart = xmlContent.find("<materials>");
        size_t materialsEnd = xmlContent.find("</materials>");

        if (materialsStart == std::string::npos || materialsEnd == std::string::npos)
        {
            std::cerr << "Invalid materials file format: " << filePath << std::endl;
            return false;
        }

        std::string materialsSection = xmlContent.substr(
            materialsStart,
            materialsEnd - materialsStart + std::string("</materials>").length());

        // Parse individual material elements using regex
        size_t currentPos = 0;
        while (true)
        {
            size_t materialStart = materialsSection.find("<material", currentPos);
            if (materialStart == std::string::npos)
                break;

            size_t materialEnd = materialsSection.find("</material>", materialStart);
            if (materialEnd == std::string::npos)
                break;

            materialEnd += std::string("</material>").length();

            std::string materialXml = materialsSection.substr(materialStart, materialEnd - materialStart);

            // Extract material attributes
            std::string materialId = ExtractAttributeValue(materialXml, "id");
            std::string materialType = ExtractAttributeValue(materialXml, "type");

            if (materialId.empty() || materialType.empty())
            {
                std::cerr << "Material missing required attributes: " << materialXml << std::endl;
                currentPos = materialEnd;
                continue;
            }

            // Create material
            Material material(materialId, materialType);

            // Parse properties section
            size_t propsStart = materialXml.find("<properties>");
            size_t propsEnd = materialXml.find("</properties>");

            if (propsStart != std::string::npos && propsEnd != std::string::npos)
            {
                std::string propsSection = materialXml.substr(propsStart, propsEnd - propsStart + std::string("</properties>").length());

                // Parse albedo color
                ParseColorProperty(propsSection, "albedo", material.properties.albedo);

                // Parse emission color
                ParseColorProperty(propsSection, "emission", material.properties.emission);

                // Parse rim color
                ParseColorProperty(propsSection, "rimColor", material.properties.rimColor);

                // Parse float properties
                ParseFloatProperty(propsSection, "roughness", material.properties.roughness);
                ParseFloatProperty(propsSection, "metallic", material.properties.metallic);
                ParseFloatProperty(propsSection, "rimPower", material.properties.rimPower);
                ParseFloatProperty(propsSection, "rimStrength", material.properties.rimStrength);

                // Parse integer properties
                ParseIntProperty(propsSection, "toonSteps", material.properties.toonSteps);

                // Parse boolean properties
                ParseBoolProperty(propsSection, "enableRimLighting", material.properties.enableRimLighting);
                ParseBoolProperty(propsSection, "enableOutlines", material.properties.enableOutlines);

                // Parse texture references
                material.properties.albedoTexture = ExtractTagValue(propsSection, "albedoTexture");
                material.properties.normalTexture = ExtractTagValue(propsSection, "normalTexture");
                material.properties.metallicTexture = ExtractTagValue(propsSection, "metallicTexture");
                material.properties.roughnessTexture = ExtractTagValue(propsSection, "roughnessTexture");
                material.properties.emissionTexture = ExtractTagValue(propsSection, "emissionTexture");
            }

            // Load the material
            LoadMaterial(materialId, material);

            currentPos = materialEnd;
        }

        std::cout << "Loaded materials from file: " << filePath << std::endl;
        return true;
    }

    void MaterialManager::ClearAllMaterials()
    {
        size_t count = materials_.size();
        materials_.clear();
        std::cout << "Cleared " << count << " materials" << std::endl;
    }

    size_t MaterialManager::GetMaterialCount() const
    {
        return materials_.size();
    }

    std::vector<std::string> MaterialManager::GetAllMaterialIds() const
    {
        std::vector<std::string> ids;
        ids.reserve(materials_.size());

        for (const auto &pair : materials_)
        {
            ids.push_back(pair.first);
        }

        std::sort(ids.begin(), ids.end());
        return ids;
    }

    bool MaterialManager::ValidateMaterial(const std::string &materialId) const
    {
        auto it = materials_.find(materialId);
        if (it == materials_.end())
        {
            return false;
        }

        const auto &props = it->second.properties;

        // Validate color values are in valid range
        auto validateColor = [](const Math::float3 &color)
        {
            return color.x >= 0.0f && color.x <= 1.0f &&
                   color.y >= 0.0f && color.y <= 1.0f &&
                   color.z >= 0.0f && color.z <= 1.0f;
        };

        if (!validateColor(props.albedo) || !validateColor(props.emission) || !validateColor(props.rimColor))
        {
            return false;
        }

        // Validate numeric ranges
        if (props.metallic < 0.0f || props.metallic > 1.0f ||
            props.roughness < 0.0f || props.roughness > 1.0f ||
            props.rimPower < 0.1f || props.rimPower > 10.0f ||
            props.toonSteps < 1 || props.toonSteps > 16)
        {
            return false;
        }

        return true;
    }

    void MaterialManager::PrintMaterialInfo(const std::string &materialId) const
    {
        auto it = materials_.find(materialId);
        if (it == materials_.end())
        {
            std::cout << "Material not found: " << materialId << std::endl;
            return;
        }

        const auto &material = it->second;
        const auto &props = material.properties;

        std::cout << "\\n=== Material Info: " << materialId << " ===" << std::endl;
        std::cout << "Type: " << material.type << std::endl;
        std::cout << "Dynamic: " << (material.isDynamic ? "Yes" : "No") << std::endl;
        std::cout << "Albedo: (" << props.albedo.x << ", " << props.albedo.y << ", " << props.albedo.z << ")" << std::endl;
        std::cout << "Metallic: " << props.metallic << ", Roughness: " << props.roughness << std::endl;
        std::cout << "Toon Steps: " << props.toonSteps << ", Threshold: " << props.toonThreshold << std::endl;
        std::cout << "Rim Lighting: " << (props.enableRimLighting ? "Enabled" : "Disabled") << std::endl;
        std::cout << "Outlines: " << (props.enableOutlines ? "Enabled" : "Disabled") << std::endl;
        std::cout << "Animation: " << (props.isAnimated ? props.animationType + " (speed: " + std::to_string(props.animationSpeed) + ")" : "None") << std::endl;
        std::cout << "=========================" << std::endl;
    }

    // Private helper methods

    std::string MaterialManager::GenerateUniqueMaterialId(const std::string &baseType)
    {
        static int counter = 1000;
        std::string materialId;

        do
        {
            std::stringstream ss;
            ss << baseType << "_material_" << std::setfill('0') << std::setw(4) << counter++;
            materialId = ss.str();
        } while (HasMaterial(materialId));

        return materialId;
    }

    MaterialProperties MaterialManager::CreateBaseProperties(const std::string &materialType)
    {
        MaterialProperties props;

        // Try to use the properties from loaded materials if available
        std::string materialId;
        if (materialType == "earth")
        {
            materialId = "EarthSurfaceMaterial";
        }
        else if (materialType == "atmosphere")
        {
            materialId = "AtmosphereMaterial";
        }
        else if (materialType == "cloud")
        {
            materialId = "CloudMaterial";
        }
        else if (materialType == "contrail")
        {
            materialId = "ContrailMaterial";
        }

        // If the material exists, copy its properties
        if (!materialId.empty() && HasMaterial(materialId))
        {
            auto material = GetMaterial(materialId);
            if (material)
            {
                return material->properties;
            }
        }

        // Fallback to default properties if the material isn't loaded
        if (materialType == "earth")
        {
            props.albedo = {0.2f, 0.4f, 0.9f}; // Blue earth (updated from green)
            props.roughness = 0.8f;
            props.metallic = 0.0f;
            props.toonSteps = 6;
        }
        else if (materialType == "atmosphere")
        {
            props.albedo = {0.5f, 0.7f, 1.0f};
            props.roughness = 0.0f;
            props.metallic = 0.0f;
            props.toonSteps = 3;
        }
        else if (materialType == "cloud")
        {
            props.albedo = {1.0f, 1.0f, 1.0f};
            props.roughness = 0.1f;
            props.metallic = 0.0f;
            props.toonSteps = 4;
        }
        else if (materialType == "contrail")
        {
            props.albedo = {1.0f, 1.0f, 1.0f};
            props.emission = {0.1f, 0.1f, 0.1f};
            props.roughness = 0.0f;
            props.metallic = 0.0f;
            props.toonSteps = 2;
        }

        return props;
    }

    void MaterialManager::ApplyGlobalCelShadingSettings(MaterialProperties &properties)
    {
        if (properties.toonSteps == 4)
        { // Only apply if using default
            properties.toonSteps = globalToonSteps_;
        }
        if (properties.toonThreshold == 0.5f)
        { // Only apply if using default
            properties.toonThreshold = globalToonThreshold_;
        }
        if (properties.enableRimLighting)
        { // Only apply if rim lighting is enabled
            properties.enableRimLighting = globalRimLighting_;
        }
    }

    MaterialProperties MaterialManager::CreateEarthProperties(float radius, int detailLevel)
    {
        MaterialProperties props = CreateBaseProperties("earth");

        // Adjust properties based on radius (for LOD)
        if (radius > 5000000.0f)
        { // Large scale (space view)
            props.toonSteps = 8;
            props.roughness = 0.6f;
        }
        else if (radius > 1000000.0f)
        { // Medium scale
            props.toonSteps = 6;
            props.roughness = 0.7f;
        }
        else
        { // Close scale
            props.toonSteps = 4;
            props.roughness = 0.9f;
        }

        // Detail level affects rim lighting
        props.rimStrength = 1.0f + (detailLevel * 0.2f);
        props.enableRimLighting = true;
        props.rimColor = {0.8f, 0.9f, 1.0f};

        return props;
    }

    MaterialProperties MaterialManager::CreateAtmosphereProperties(int layer, float density)
    {
        MaterialProperties props = CreateBaseProperties("atmosphere");

        // Layer affects color and properties
        float layerFactor = static_cast<float>(layer) / 3.0f;
        props.albedo.x = 0.4f + layerFactor * 0.2f;
        props.albedo.y = 0.6f + layerFactor * 0.2f;
        props.albedo.z = 0.9f + layerFactor * 0.1f;

        // Density affects rim lighting
        props.rimStrength = density * 3.0f;
        props.rimPower = 1.5f + density;
        props.enableRimLighting = true;

        props.toonSteps = 2 + layer;
        props.toonThreshold = 0.3f + density * 0.4f;

        return props;
    }

    MaterialProperties MaterialManager::CreateCloudProperties(float coverage, float density)
    {
        MaterialProperties props = CreateBaseProperties("cloud");

        // Coverage affects albedo
        props.albedo = {0.9f + coverage * 0.1f, 0.9f + coverage * 0.1f, 0.9f + coverage * 0.1f};

        // Density affects roughness and animation
        props.roughness = 0.05f + density * 0.15f;
        props.isAnimated = true;
        props.animationType = "scroll";
        props.animationSpeed = 0.3f + density * 0.4f;

        props.enableRimLighting = true;
        props.rimColor = {0.9f, 0.95f, 1.0f};
        props.rimStrength = 1.2f;

        return props;
    }

    MaterialProperties MaterialManager::CreateContrailProperties(const Math::float3 &color)
    {
        MaterialProperties props = CreateBaseProperties("contrail");

        props.albedo = color;
        props.emission = {color.x * 0.2f, color.y * 0.2f, color.z * 0.2f};

        props.isAnimated = true;
        props.animationType = "wave";
        props.animationSpeed = 1.5f;

        props.enableRimLighting = true;
        props.rimColor = color;
        props.rimStrength = 2.0f;
        props.rimPower = 1.0f;

        return props;
    }

    void MaterialManager::AssignEarthTextures(MaterialProperties &properties, float radius, int detailLevel)
    {
        if (!textureGenerator_)
            return;

        // For now, just assign placeholder texture names
        // In a real implementation, we would generate textures using ProceduralTexture::ProceduralTextureGenerator::generateTexture
        std::string baseId = "earth_" + std::to_string(static_cast<int>(radius)) + "_detail" + std::to_string(detailLevel);

        properties.albedoTexture = baseId + "_albedo";
        properties.normalTexture = baseId + "_normal";
    }

    void MaterialManager::AssignAtmosphereTextures(MaterialProperties &properties, int layer)
    {
        if (!textureGenerator_)
            return;

        std::string baseId = "atmosphere_layer" + std::to_string(layer);
        properties.albedoTexture = baseId + "_albedo";
    }

    void MaterialManager::AssignCloudTextures(MaterialProperties &properties, float coverage)
    {
        if (!textureGenerator_)
            return;

        std::string baseId = "cloud_coverage" + std::to_string(static_cast<int>(coverage * 100));
        properties.albedoTexture = baseId + "_albedo";
    }

    void MaterialManager::AssignContrailTextures(MaterialProperties &properties)
    {
        if (!textureGenerator_)
            return;

        properties.albedoTexture = "contrail_albedo";
    }

    // XML parsing helper methods
    std::string MaterialManager::ExtractAttributeValue(const std::string &xml, const std::string &attributeName)
    {
        std::string searchStr = attributeName + "=\"";
        size_t start = xml.find(searchStr);
        if (start == std::string::npos)
            return "";

        start += searchStr.length();
        size_t end = xml.find("\"", start);
        if (end == std::string::npos)
            return "";

        return xml.substr(start, end - start);
    }

    std::string MaterialManager::ExtractTagValue(const std::string &xml, const std::string &tagName)
    {
        std::string openTag = "<" + tagName + ">";
        std::string closeTag = "</" + tagName + ">";

        size_t start = xml.find(openTag);
        if (start == std::string::npos)
            return "";

        start += openTag.length();
        size_t end = xml.find(closeTag, start);
        if (end == std::string::npos)
            return "";

        return xml.substr(start, end - start);
    }

    void MaterialManager::ParseColorProperty(const std::string &xml, const std::string &propName, Math::float3 &colorValue)
    {
        std::string startTag = "<" + propName;
        size_t start = xml.find(startTag);
        if (start == std::string::npos)
            return;

        std::string r = ExtractAttributeValue(xml.substr(start), "r");
        std::string g = ExtractAttributeValue(xml.substr(start), "g");
        std::string b = ExtractAttributeValue(xml.substr(start), "b");

        if (!r.empty())
            colorValue.x = std::stof(r);
        if (!g.empty())
            colorValue.y = std::stof(g);
        if (!b.empty())
            colorValue.z = std::stof(b);
    }

    void MaterialManager::ParseFloatProperty(const std::string &xml, const std::string &propName, float &floatValue)
    {
        std::string value = ExtractTagValue(xml, propName);
        if (!value.empty())
        {
            try
            {
                floatValue = std::stof(value);
            }
            catch (const std::exception &e)
            {
                std::cerr << "Error parsing float property " << propName << ": " << e.what() << std::endl;
            }
        }
    }

    void MaterialManager::ParseIntProperty(const std::string &xml, const std::string &propName, int &intValue)
    {
        std::string value = ExtractTagValue(xml, propName);
        if (!value.empty())
        {
            try
            {
                intValue = std::stoi(value);
            }
            catch (const std::exception &e)
            {
                std::cerr << "Error parsing int property " << propName << ": " << e.what() << std::endl;
            }
        }
    }

    void MaterialManager::ParseBoolProperty(const std::string &xml, const std::string &propName, bool &boolValue)
    {
        std::string value = ExtractTagValue(xml, propName);
        if (!value.empty())
        {
            boolValue = (value == "true" || value == "1");
        }
    }
}
#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include <optional>
#include "../math/MathUtils.h"
#include "../generators/ProceduralTextureGenerator.h"

using AssetId = std::string;

namespace Material
{
    // Core material properties for cel-shading and PBR workflows
    struct MaterialProperties
    {
        // Cel-shading properties
        Math::float3 albedo = {1.0f, 1.0f, 1.0f};
        Math::float3 emission = {0.0f, 0.0f, 0.0f};
        float metallic = 0.0f;
        float roughness = 0.5f;
        float rimPower = 2.0f;
        float rimStrength = 1.0f;
        Math::float3 rimColor = {1.0f, 1.0f, 1.0f};

        // Texture asset IDs
        std::string albedoTexture;
        std::string normalTexture;
        std::string metallicTexture;
        std::string roughnessTexture;
        std::string emissionTexture;

        // Cel-shading specific
        int toonSteps = 4;
        float toonThreshold = 0.5f;
        bool enableRimLighting = true;
        bool enableOutlines = false;
        float outlineWidth = 0.02f;
        Math::float3 outlineColor = {0.0f, 0.0f, 0.0f};

        // Animation properties
        bool isAnimated = false;
        float animationSpeed = 1.0f;
        std::string animationType = "none"; // "scroll", "rotate", "pulse", "wave"
    };

    // Material definition combining properties and metadata
    struct Material
    {
        std::string name;
        std::string type; // "standard", "earth", "atmosphere", "cloud", "contrail"
        MaterialProperties properties;
        bool isDynamic = false; // Whether textures are generated at runtime

        Material() = default;
        Material(const std::string &materialName, const std::string &materialType)
            : name(materialName), type(materialType) {}
    };

    // Material manager for dynamic loading and cel-shading setup
    class MaterialManager
    {
    public:
        MaterialManager();
        ~MaterialManager() = default;

        // Core material management
        bool LoadMaterial(const std::string &materialId, const Material &material);
        std::optional<Material> GetMaterial(const std::string &materialId) const;
        bool HasMaterial(const std::string &materialId) const;

        // Dynamic material creation
        std::string CreateDynamicMaterial(const std::string &baseType, const MaterialProperties &properties);
        std::string CreateEarthMaterial(float radius, int detailLevel = 1);
        std::string CreateAtmosphereMaterial(int layer = 0, float density = 0.1f);
        std::string CreateCloudMaterial(float coverage = 0.6f, float density = 0.3f);
        std::string CreateContrailMaterial(const Math::float3 &color = {1.0f, 1.0f, 1.0f});

        // Cel-shading configuration
        void SetGlobalCelShadingParams(int toonSteps, float threshold, bool enableRim);
        void EnableOutlinesForMaterial(const std::string &materialId, float width, const Math::float3 &color);
        void SetMaterialAnimation(const std::string &materialId, const std::string &animType, float speed);

        // Texture integration (internal use only)
        void SetTextureGenerator(const ProceduralTexture::ProceduralTextureGenerator *generator);
        AssetId GenerateAndAssignTexture(const std::string &materialId, const std::string &textureType);

        // Bulk operations
        bool LoadMaterialsFromFile(const std::string &filePath);
        void LoadDefaultMaterials(); // Deprecated - use LoadMaterialsFromFile
        void ClearAllMaterials();
        size_t GetMaterialCount() const;

        // Debugging and validation
        std::vector<std::string> GetAllMaterialIds() const;
        bool ValidateMaterial(const std::string &materialId) const;
        void PrintMaterialInfo(const std::string &materialId) const;

    private:
        std::unordered_map<std::string, Material> materials_;
        const ProceduralTexture::ProceduralTextureGenerator *textureGenerator_;

        // Global cel-shading settings
        int globalToonSteps_ = 4;
        float globalToonThreshold_ = 0.5f;
        bool globalRimLighting_ = true;

        // Helper methods
        std::string GenerateUniqueMaterialId(const std::string &baseType);
        MaterialProperties CreateBaseProperties(const std::string &materialType);
        void ApplyGlobalCelShadingSettings(MaterialProperties &properties);

        // Material type creators
        MaterialProperties CreateEarthProperties(float radius, int detailLevel);
        MaterialProperties CreateAtmosphereProperties(int layer, float density);
        MaterialProperties CreateCloudProperties(float coverage, float density);
        MaterialProperties CreateContrailProperties(const Math::float3 &color);

        // Texture assignment helpers
        void AssignEarthTextures(MaterialProperties &properties, float radius, int detailLevel);
        void AssignAtmosphereTextures(MaterialProperties &properties, int layer);
        void AssignCloudTextures(MaterialProperties &properties, float coverage);
        void AssignContrailTextures(MaterialProperties &properties);

        // XML parsing helpers
        std::string ExtractAttributeValue(const std::string &xml, const std::string &attributeName);
        std::string ExtractTagValue(const std::string &xml, const std::string &tagName);
        void ParseColorProperty(const std::string &xml, const std::string &propName, Math::float3 &colorValue);
        void ParseFloatProperty(const std::string &xml, const std::string &propName, float &floatValue);
        void ParseIntProperty(const std::string &xml, const std::string &propName, int &intValue);
        void ParseBoolProperty(const std::string &xml, const std::string &propName, bool &boolValue);
    };
}
/**
 * @file OrbitalAnimationSystem.h
 * @brief Animation system for orbital motion management
 *
 * The OrbitalAnimationSystem manages orbital motion for entities with
 * OrbitalC components. Features include:
 * - Automatic time advancement and position updates
 * - Synchronization between multiple orbital entities
 * - Speed scaling and time manipulation
 * - Integration with transform components
 * - Support for coordinated group animations
 *
 * @author Generated for Voxel Busy Indicator Scene
 * @date 2024
 */

#pragma once

#include "../math/MathUtils.h"
#include "../components/OrbitalC.h"
#include "../components/TransformC.h"
#include <vector>
#include <memory>
#include <unordered_map>

/**
 * @brief Animation system for orbital motion
 *
 * Manages the update cycle for all entities with orbital motion,
 * ensuring synchronized and smooth orbital animations.
 */
class OrbitalAnimationSystem
{
public:
    /**
     * @brief Entity reference for orbital updates
     */
    struct OrbitalEntity
    {
        uint32_t entityId;                     /**< Entity identifier */
        std::shared_ptr<OrbitalC> orbital;     /**< Orbital component */
        std::shared_ptr<TransformC> transform; /**< Transform component */
        bool active;                           /**< Whether entity is active */

        OrbitalEntity(uint32_t id, std::shared_ptr<OrbitalC> orb, std::shared_ptr<TransformC> trans)
            : entityId(id), orbital(orb), transform(trans), active(true) {}
    };

    /**
     * @brief Animation group for synchronized orbital motion
     */
    struct OrbitalGroup
    {
        std::string name;                /**< Group name */
        std::vector<uint32_t> entityIds; /**< Entities in this group */
        float timeScale;                 /**< Time scaling factor */
        float phaseOffset;               /**< Group phase offset */
        Math::float3 centerPoint;        /**< Group center point */
        bool synchronized;               /**< Whether group is synchronized */

        OrbitalGroup(const std::string &groupName = "default")
            : name(groupName), timeScale(1.0f), phaseOffset(0.0f), centerPoint{0, 0, 0}, synchronized(true)
        {
        }
    };

private:
    /** @brief All registered orbital entities */
    std::vector<OrbitalEntity> entities;

    /** @brief Orbital groups for synchronized animation */
    std::unordered_map<std::string, OrbitalGroup> groups;

    /** @brief Global time accumulator */
    float globalTime;

    /** @brief Global time scale */
    float globalTimeScale;

    /** @brief Whether system is active */
    bool systemActive;

    /** @brief Frame delta time for smooth updates */
    float deltaTime;

public:
    /**
     * @brief Construct a new OrbitalAnimationSystem
     */
    OrbitalAnimationSystem()
        : globalTime(0.0f), globalTimeScale(1.0f), systemActive(true), deltaTime(0.0f)
    {
        // Create default group
        groups["default"] = OrbitalGroup("default");
    }

    /**
     * @brief Update all orbital animations
     *
     * @param frameTime Time elapsed since last frame
     */
    void update(float frameTime)
    {
        if (!systemActive)
            return;

        deltaTime = frameTime * globalTimeScale;
        globalTime += deltaTime;

        // Update all orbital entities
        for (auto &entity : entities)
        {
            if (!entity.active || !entity.orbital || !entity.transform)
                continue;

            updateEntity(entity);
        }

        // Update group-specific animations
        updateGroups();
    }

    /**
     * @brief Register an entity for orbital animation
     *
     * @param entityId Entity identifier
     * @param orbital Orbital component
     * @param transform Transform component
     * @param groupName Group to assign entity to
     */
    void registerEntity(uint32_t entityId,
                        std::shared_ptr<OrbitalC> orbital,
                        std::shared_ptr<TransformC> transform,
                        const std::string &groupName = "default")
    {
        entities.emplace_back(entityId, orbital, transform);

        // Add to group
        auto &group = getOrCreateGroup(groupName);
        group.entityIds.push_back(entityId);
    }

    /**
     * @brief Unregister an entity from orbital animation
     *
     * @param entityId Entity to remove
     */
    void unregisterEntity(uint32_t entityId)
    {
        // Remove from entities list
        entities.erase(
            std::remove_if(entities.begin(), entities.end(),
                           [entityId](const OrbitalEntity &e)
                           { return e.entityId == entityId; }),
            entities.end());

        // Remove from all groups
        for (auto &[groupName, group] : groups)
        {
            group.entityIds.erase(
                std::remove(group.entityIds.begin(), group.entityIds.end(), entityId),
                group.entityIds.end());
        }
    }

    /**
     * @brief Create or get an orbital group
     *
     * @param groupName Name of the group
     * @return Reference to the group
     */
    OrbitalGroup &getOrCreateGroup(const std::string &groupName)
    {
        if (groups.find(groupName) == groups.end())
        {
            groups[groupName] = OrbitalGroup(groupName);
        }
        return groups[groupName];
    }

    /**
     * @brief Set group parameters
     *
     * @param groupName Group name
     * @param timeScale Time scaling factor
     * @param centerPoint Center point for group
     * @param synchronized Whether group should be synchronized
     */
    void setGroupParams(const std::string &groupName,
                        float timeScale = 1.0f,
                        const Math::float3 &centerPoint = {0, 0, 0},
                        bool synchronized = true)
    {
        auto &group = getOrCreateGroup(groupName);
        group.timeScale = timeScale;
        group.centerPoint = centerPoint;
        group.synchronized = synchronized;
    }

    /**
     * @brief Set global time scale
     *
     * @param scale Time scaling factor (1.0 = normal speed)
     */
    void setGlobalTimeScale(float scale)
    {
        globalTimeScale = scale;
    }

    /**
     * @brief Get global time scale
     *
     * @return Current time scale
     */
    float getGlobalTimeScale() const
    {
        return globalTimeScale;
    }

    /**
     * @brief Pause/resume orbital animations
     *
     * @param active Whether system should be active
     */
    void setActive(bool active)
    {
        systemActive = active;
    }

    /**
     * @brief Check if system is active
     *
     * @return True if system is running
     */
    bool isActive() const
    {
        return systemActive;
    }

    /**
     * @brief Reset global time
     *
     * @param time New time value
     */
    void setGlobalTime(float time)
    {
        globalTime = time;

        // Update all orbital components
        for (auto &entity : entities)
        {
            if (entity.orbital)
            {
                entity.orbital->setTime(time);
            }
        }
    }

    /**
     * @brief Get current global time
     *
     * @return Current global time
     */
    float getGlobalTime() const
    {
        return globalTime;
    }

    /**
     * @brief Get number of registered entities
     *
     * @return Entity count
     */
    size_t getEntityCount() const
    {
        return entities.size();
    }

    /**
     * @brief Get number of active entities
     *
     * @return Active entity count
     */
    size_t getActiveEntityCount() const
    {
        size_t count = 0;
        for (const auto &entity : entities)
        {
            if (entity.active)
                count++;
        }
        return count;
    }

private:
    /**
     * @brief Update a single orbital entity
     *
     * @param entity Entity to update
     */
    void updateEntity(OrbitalEntity &entity)
    {
        // Find the group this entity belongs to
        OrbitalGroup *entityGroup = nullptr;
        for (auto &[groupName, group] : groups)
        {
            auto it = std::find(group.entityIds.begin(), group.entityIds.end(), entity.entityId);
            if (it != group.entityIds.end())
            {
                entityGroup = &group;
                break;
            }
        }

        // Calculate time delta for this entity
        float entityDelta = deltaTime;
        if (entityGroup)
        {
            entityDelta *= entityGroup->timeScale;
        }

        // Update orbital component
        entity.orbital->update(entityDelta);

        // Get current orbital position and orientation
        Math::float3 position = entity.orbital->getCurrentPosition();
        Math::quat orientation = entity.orbital->getCurrentOrientation();

        // Apply group center offset if applicable
        if (entityGroup)
        {
            position = Math::add(position, entityGroup->centerPoint);
        }

        // Update transform component
        entity.transform->setPosition(position);
        entity.transform->setRotation(orientation);
    }

    /**
     * @brief Update group-specific animations
     */
    void updateGroups()
    {
        for (auto &[groupName, group] : groups)
        {
            if (!group.synchronized)
                continue;

            // For synchronized groups, ensure all entities have the same phase
            if (group.entityIds.size() > 1)
            {
                updateSynchronizedGroup(group);
            }
        }
    }

    /**
     * @brief Update a synchronized orbital group
     *
     * @param group Group to synchronize
     */
    void updateSynchronizedGroup(OrbitalGroup &group)
    {
        if (group.entityIds.empty())
            return;

        // Find the first active entity as reference
        OrbitalEntity *referenceEntity = nullptr;
        for (uint32_t entityId : group.entityIds)
        {
            for (auto &entity : entities)
            {
                if (entity.entityId == entityId && entity.active && entity.orbital)
                {
                    referenceEntity = &entity;
                    break;
                }
            }
            if (referenceEntity)
                break;
        }

        if (!referenceEntity)
            return;

        // Get reference time from the reference entity
        float referenceTime = globalTime + group.phaseOffset;

        // Apply to all entities in the group
        for (uint32_t entityId : group.entityIds)
        {
            for (auto &entity : entities)
            {
                if (entity.entityId == entityId && entity.active && entity.orbital)
                {
                    // Maintain individual phase offsets while synchronizing base time
                    float individualPhase = entity.orbital->orbitParams.phaseOffset;
                    entity.orbital->setTime(referenceTime + individualPhase);
                }
            }
        }
    }
};
/**
 * @file ParticleAnimationSystem.h
 * @brief Animation system for particle effects management
 *
 * The ParticleAnimationSystem manages particle-based effects including
 * contrails, explosions, and other dynamic particle systems. Features include:
 * - Automatic particle lifecycle management
 * - Physics integration for realistic motion
 * - Emitter following for trail effects
 * - Performance optimization through pooling
 * - Integration with Math utilities for physics
 *
 * @author Generated for Voxel Busy Indicator Scene
 * @date 2024
 */

#pragma once

#include "../math/MathUtils.h"
#include "../components/ContrailC.h"
#include "../components/TransformC.h"
#include <vector>
#include <memory>
#include <unordered_map>

/**
 * @brief Animation system for particle effects
 *
 * Manages the update cycle for all particle-based effects,
 * ensuring smooth physics simulation and lifecycle management.
 */
class ParticleAnimationSystem
{
public:
    /**
     * @brief Entity with particle effects
     */
    struct ParticleEntity
    {
        uint32_t entityId;                     /**< Entity identifier */
        std::shared_ptr<ContrailC> contrail;   /**< Contrail component */
        std::shared_ptr<TransformC> transform; /**< Transform component */
        bool active;                           /**< Whether entity is active */
        Math::float3 lastPosition;             /**< Last known position */
        bool hasLastPosition;                  /**< Whether last position is valid */

        ParticleEntity(uint32_t id, std::shared_ptr<ContrailC> cont, std::shared_ptr<TransformC> trans)
            : entityId(id), contrail(cont), transform(trans), active(true), lastPosition{0, 0, 0}, hasLastPosition(false) {}
    };

    /**
     * @brief Particle effect group for synchronized behavior
     */
    struct ParticleGroup
    {
        std::string name;                /**< Group name */
        std::vector<uint32_t> entityIds; /**< Entities in this group */
        Math::float3 windVelocity;       /**< Shared wind velocity */
        float gravityStrength;           /**< Shared gravity strength */
        float timeScale;                 /**< Time scaling factor */
        bool sharedPhysics;              /**< Whether to use shared physics params */

        ParticleGroup(const std::string &groupName = "default")
            : name(groupName), windVelocity{0, 0, 0}, gravityStrength(9.81f), timeScale(1.0f), sharedPhysics(false)
        {
        }
    };

    /**
     * @brief Performance statistics
     */
    struct PerformanceStats
    {
        uint32_t totalParticles;   /**< Total active particles */
        uint32_t totalEmitters;    /**< Total active emitters */
        float updateTime;          /**< Last update time in milliseconds */
        uint32_t particlesSpawned; /**< Particles spawned this frame */
        uint32_t particlesDied;    /**< Particles died this frame */

        PerformanceStats() : totalParticles(0), totalEmitters(0), updateTime(0), particlesSpawned(0), particlesDied(0) {}
    };

private:
    /** @brief All registered particle entities */
    std::vector<ParticleEntity> entities;

    /** @brief Particle groups for synchronized behavior */
    std::unordered_map<std::string, ParticleGroup> groups;

    /** @brief Global time accumulator */
    float globalTime;

    /** @brief Global time scale */
    float globalTimeScale;

    /** @brief Whether system is active */
    bool systemActive;

    /** @brief Performance statistics */
    PerformanceStats stats;

    /** @brief Global physics parameters */
    Math::float3 globalWindVelocity;
    float globalGravityStrength;

public:
    /**
     * @brief Construct a new ParticleAnimationSystem
     */
    ParticleAnimationSystem()
        : globalTime(0.0f), globalTimeScale(1.0f), systemActive(true), globalWindVelocity{0, 0, 0}, globalGravityStrength(9.81f)
    {
        // Create default group
        groups["default"] = ParticleGroup("default");
    }

    /**
     * @brief Update all particle animations
     *
     * @param deltaTime Time elapsed since last frame
     */
    void update(float deltaTime)
    {
        if (!systemActive)
            return;

        // Reset frame statistics
        stats.particlesSpawned = 0;
        stats.particlesDied = 0;
        stats.totalParticles = 0;
        stats.totalEmitters = 0;

        float startTime = globalTime; // For performance measurement

        float scaledDeltaTime = deltaTime * globalTimeScale;
        globalTime += scaledDeltaTime;

        // Update all particle entities
        for (auto &entity : entities)
        {
            if (!entity.active || !entity.contrail || !entity.transform)
                continue;

            updateParticleEntity(entity, scaledDeltaTime);
            stats.totalEmitters++;
        }

        // Update group-specific effects
        updateGroups(scaledDeltaTime);

        // Calculate performance metrics
        stats.updateTime = (globalTime - startTime) * 1000.0f; // Convert to milliseconds
    }

    /**
     * @brief Register an entity for particle animation
     *
     * @param entityId Entity identifier
     * @param contrail Contrail component
     * @param transform Transform component
     * @param groupName Group to assign entity to
     */
    void registerEntity(uint32_t entityId,
                        std::shared_ptr<ContrailC> contrail,
                        std::shared_ptr<TransformC> transform,
                        const std::string &groupName = "default")
    {
        entities.emplace_back(entityId, contrail, transform);

        // Add to group
        auto &group = getOrCreateGroup(groupName);
        group.entityIds.push_back(entityId);
    }

    /**
     * @brief Unregister an entity from particle animation
     *
     * @param entityId Entity to remove
     */
    void unregisterEntity(uint32_t entityId)
    {
        // Remove from entities list
        entities.erase(
            std::remove_if(entities.begin(), entities.end(),
                           [entityId](const ParticleEntity &e)
                           { return e.entityId == entityId; }),
            entities.end());

        // Remove from all groups
        for (auto &[groupName, group] : groups)
        {
            group.entityIds.erase(
                std::remove(group.entityIds.begin(), group.entityIds.end(), entityId),
                group.entityIds.end());
        }
    }

    /**
     * @brief Create or get a particle group
     *
     * @param groupName Name of the group
     * @return Reference to the group
     */
    ParticleGroup &getOrCreateGroup(const std::string &groupName)
    {
        if (groups.find(groupName) == groups.end())
        {
            groups[groupName] = ParticleGroup(groupName);
        }
        return groups[groupName];
    }

    /**
     * @brief Set group physics parameters
     *
     * @param groupName Group name
     * @param windVelocity Wind velocity vector
     * @param gravityStrength Gravity strength
     * @param timeScale Time scaling factor
     * @param sharedPhysics Whether to use shared physics
     */
    void setGroupPhysics(const std::string &groupName,
                         const Math::float3 &windVelocity = {0, 0, 0},
                         float gravityStrength = 9.81f,
                         float timeScale = 1.0f,
                         bool sharedPhysics = true)
    {
        auto &group = getOrCreateGroup(groupName);
        group.windVelocity = windVelocity;
        group.gravityStrength = gravityStrength;
        group.timeScale = timeScale;
        group.sharedPhysics = sharedPhysics;
    }

    /**
     * @brief Set global physics parameters
     *
     * @param windVelocity Global wind velocity
     * @param gravityStrength Global gravity strength
     */
    void setGlobalPhysics(const Math::float3 &windVelocity, float gravityStrength)
    {
        globalWindVelocity = windVelocity;
        globalGravityStrength = gravityStrength;
    }

    /**
     * @brief Set global time scale
     *
     * @param scale Time scaling factor (1.0 = normal speed)
     */
    void setGlobalTimeScale(float scale)
    {
        globalTimeScale = scale;
    }

    /**
     * @brief Get global time scale
     *
     * @return Current time scale
     */
    float getGlobalTimeScale() const
    {
        return globalTimeScale;
    }

    /**
     * @brief Pause/resume particle animations
     *
     * @param active Whether system should be active
     */
    void setActive(bool active)
    {
        systemActive = active;
    }

    /**
     * @brief Check if system is active
     *
     * @return True if system is running
     */
    bool isActive() const
    {
        return systemActive;
    }

    /**
     * @brief Get performance statistics
     *
     * @return Current performance stats
     */
    const PerformanceStats &getPerformanceStats() const
    {
        return stats;
    }

    /**
     * @brief Clear all particles in a group
     *
     * @param groupName Group to clear (empty = all groups)
     */
    void clearParticles(const std::string &groupName = "")
    {
        if (groupName.empty())
        {
            // Clear all particles
            for (auto &entity : entities)
            {
                if (entity.contrail)
                {
                    entity.contrail->clearParticles();
                }
            }
        }
        else
        {
            // Clear particles in specific group
            auto groupIt = groups.find(groupName);
            if (groupIt != groups.end())
            {
                for (uint32_t entityId : groupIt->second.entityIds)
                {
                    for (auto &entity : entities)
                    {
                        if (entity.entityId == entityId && entity.contrail)
                        {
                            entity.contrail->clearParticles();
                        }
                    }
                }
            }
        }
    }

    /**
     * @brief Get number of registered entities
     *
     * @return Entity count
     */
    size_t getEntityCount() const
    {
        return entities.size();
    }

    /**
     * @brief Get number of active entities
     *
     * @return Active entity count
     */
    size_t getActiveEntityCount() const
    {
        size_t count = 0;
        for (const auto &entity : entities)
        {
            if (entity.active)
                count++;
        }
        return count;
    }

private:
    /**
     * @brief Update a single particle entity
     *
     * @param entity Entity to update
     * @param deltaTime Time delta for this update
     */
    void updateParticleEntity(ParticleEntity &entity, float deltaTime)
    {
        // Get current position from transform
        Math::float3 currentPosition = entity.transform->getPosition();

        // Find the group this entity belongs to
        ParticleGroup *entityGroup = nullptr;
        for (auto &[groupName, group] : groups)
        {
            auto it = std::find(group.entityIds.begin(), group.entityIds.end(), entity.entityId);
            if (it != group.entityIds.end())
            {
                entityGroup = &group;
                break;
            }
        }

        // Apply group-specific physics if enabled
        if (entityGroup && entityGroup->sharedPhysics)
        {
            applyGroupPhysics(entity, *entityGroup);
            deltaTime *= entityGroup->timeScale;
        }
        else
        {
            applyGlobalPhysics(entity);
        }

        // Update contrail with current position
        entity.contrail->update(deltaTime, currentPosition);

        // Count particles for statistics
        stats.totalParticles += entity.contrail->getActiveParticleCount();

        // Update last position
        entity.lastPosition = currentPosition;
        entity.hasLastPosition = true;
    }

    /**
     * @brief Apply group-specific physics parameters
     *
     * @param entity Entity to update
     * @param group Group physics parameters
     */
    void applyGroupPhysics(ParticleEntity &entity, const ParticleGroup &group)
    {
        auto params = entity.contrail->getParams();
        params.windVelocity = group.windVelocity;
        params.gravityStrength = group.gravityStrength;
        entity.contrail->setParams(params);
    }

    /**
     * @brief Apply global physics parameters
     *
     * @param entity Entity to update
     */
    void applyGlobalPhysics(ParticleEntity &entity)
    {
        auto params = entity.contrail->getParams();
        params.windVelocity = globalWindVelocity;
        params.gravityStrength = globalGravityStrength;
        entity.contrail->setParams(params);
    }

    /**
     * @brief Update group-specific effects
     *
     * @param deltaTime Time delta for this update
     */
    void updateGroups(float deltaTime)
    {
        for (auto &[groupName, group] : groups)
        {
            updateGroup(group, deltaTime);
        }
    }

    /**
     * @brief Update a specific particle group
     *
     * @param group Group to update
     * @param deltaTime Time delta for this update
     */
    void updateGroup(ParticleGroup &group, float deltaTime)
    {
        // Group-specific animations could be added here
        // For example: synchronized emission patterns, group-wide effects, etc.

        // Currently, individual entity updates handle most functionality
        // This method is reserved for future group-level effects
    }
};
#include "PhysicsSystem.h"
#include "core/World.h"

PhysicsSystem::PhysicsSystem(EventBus &eventBus, IAirDensityModel &airDensityModel, IWindModel &windModel, ICollisionResolver &collisionResolver)
    : eventBus_(eventBus), airDensityModel_(airDensityModel), windModel_(windModel), collisionResolver_(collisionResolver) {}

void PhysicsSystem::update(World &world, float dt)
{
    // Stub: update physics for entities
}
#ifndef PHYSICSSYSTEM_H
#define PHYSICSSYSTEM_H

#include "core/ISystem.h"
#include "core/EventBus.h"
#include "physics/IAirDensityModel.h"
#include "physics/IWindModel.h"
#include "physics/ICollisionResolver.h"

class PhysicsSystem : public ISystem
{
public:
    PhysicsSystem(EventBus &eventBus, IAirDensityModel &airDensityModel, IWindModel &windModel, ICollisionResolver &collisionResolver);
    void update(World &world, float dt) override;

private:
    EventBus &eventBus_;
    IAirDensityModel &airDensityModel_;
    IWindModel &windModel_;
    ICollisionResolver &collisionResolver_;
};

#endif
#include "VehicleControlSystem.h"
#include "core/World.h"

VehicleControlSystem::VehicleControlSystem(EventBus &eventBus) : eventBus_(eventBus) {}

void VehicleControlSystem::update(World &world, float dt)
{
    // Stub: control vehicles
}
#ifndef VEHICLECONTROLSYSTEM_H
#define VEHICLECONTROLSYSTEM_H

#include "core/ISystem.h"
#include "core/EventBus.h"

class VehicleControlSystem : public ISystem
{
public:
    VehicleControlSystem(EventBus &eventBus);
    void update(World &world, float dt) override;

private:
    EventBus &eventBus_;
};

#endif
#include "VisualizationSystem.h"
#include <iostream>
#include <string>
#include <cmath>
#include <memory>

// Component definitions
#include "core/IComponent.h"

struct TransformC : public IComponent
{
    struct Vector3
    {
        float x, y, z;
        Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z) {}
    };

    struct Quaternion
    {
        float x, y, z, w;
        Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f) : x(x), y(y), z(z), w(w) {}
        static Quaternion Identity() { return Quaternion(0, 0, 0, 1); }
    };

    Vector3 position;
    Quaternion orientation;
    Vector3 scale;

    TransformC(Vector3 pos = Vector3(), Quaternion rot = Quaternion::Identity(), Vector3 scl = Vector3(1, 1, 1))
        : position(pos), orientation(rot), scale(scl) {}
};

struct RenderableC : public IComponent
{
    std::string meshId;
    std::string materialId;
    bool isVisible;

    RenderableC(std::string mesh = "", std::string material = "", bool visible = true)
        : meshId(mesh), materialId(material), isVisible(visible) {}
};

VisualizationSystem::VisualizationSystem(EventBus &eventBus, World &world, HWND windowHandle)
    : eventBus(eventBus), worldRef(world), hwnd(windowHandle),
      displayNoPackagesMessage(false), consoleVisible(false), rotationAngle(0.0f)
{
    hdc = GetDC(hwnd);

    // Subscribe to events
    eventBus.subscribe(EventType::NoPackagesFound, [this](const IEvent &event)
                       {
        const auto& packagesEvent = static_cast<const NoPackagesFoundEvent&>(event);
        OnNoPackagesFound(packagesEvent); });

    eventBus.subscribe(EventType::ConsoleVisibilityChanged, [this](const IEvent &event)
                       {
        const auto& visibilityEvent = static_cast<const ConsoleVisibilityChangedEvent&>(event);
        OnConsoleVisibilityChanged(visibilityEvent); });
}

VisualizationSystem::~VisualizationSystem()
{
    ReleaseDC(hwnd, hdc);
}

void VisualizationSystem::update(World &world, float deltaTime)
{
    // Get a fresh device context for this frame
    HDC frameDC = GetDC(hwnd);
    
    // Clear the screen
    RECT rect;
    GetClientRect(hwnd, &rect);
    FillRect(frameDC, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));

    // Temporarily switch to frame DC for rendering
    HDC oldDC = hdc;
    hdc = frameDC;

    // Render entities
    RenderEntities();

    // Render console if visible
    if (consoleVisible)
    {
        RenderConsole();
    }

    // Render no packages message if needed
    if (displayNoPackagesMessage)
    {
        RenderNoPackagesMessage();
    }

    // Restore original DC and release frame DC
    hdc = oldDC;
    ReleaseDC(hwnd, frameDC);

    // Update rotation for animation
    rotationAngle += deltaTime * 0.1f;
}

void VisualizationSystem::OnNoPackagesFound(const NoPackagesFoundEvent &event)
{
    displayNoPackagesMessage = true;
}

void VisualizationSystem::OnConsoleVisibilityChanged(const ConsoleVisibilityChangedEvent &event)
{
    consoleVisible = event.isVisible;
}

void VisualizationSystem::RenderEntities()
{
    // Simple rendering of entities with TransformC and RenderableC
    for (const auto &entity : worldRef.getEntities())
    {
        auto transform = entity->getComponent<TransformC>();
        auto renderable = entity->getComponent<RenderableC>();

        if (transform && renderable && renderable->isVisible)
        {
            // Simple 2D projection for now - just draw circles at positions
            float screenX = 400 + transform->position.x * 0.01f; // Simple scaling
            float screenY = 300 + transform->position.z * 0.01f;
            float radius = 50.0f; // Fixed radius for now

            // Color based on material ID (simple mapping)
            COLORREF color = RGB(0, 255, 0); // Default green
            if (renderable->materialId == "earth_material")
                color = RGB(0, 0, 255); // Blue for Earth
            else if (renderable->materialId.find("atmosphere_material") == 0)
                color = RGB(135, 206, 235); // Sky blue for atmosphere
            else if (renderable->materialId == "cloud_material")
                color = RGB(255, 255, 255); // White for clouds

            DrawSphere(screenX, screenY, radius, color);
        }
    }
}

void VisualizationSystem::RenderConsole()
{
    // Simple console rendering at the bottom of the screen
    RECT rect;
    GetClientRect(hwnd, &rect);

    // Draw semi-transparent background
    HBRUSH bgBrush = CreateSolidBrush(RGB(0, 0, 0));
    RECT consoleRect = {0, rect.bottom - 200, rect.right, rect.bottom};
    FillRect(hdc, &consoleRect, bgBrush);
    DeleteObject(bgBrush);

    // Draw border
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
    SelectObject(hdc, pen);
    Rectangle(hdc, consoleRect.left, consoleRect.top, consoleRect.right, consoleRect.bottom);
    DeleteObject(pen);

    // Draw console text
    DrawText(10, rect.bottom - 180, "Developer Console", RGB(255, 255, 0));
    DrawText(10, rect.bottom - 160, "Press ~ to toggle", RGB(255, 255, 255));
}

void VisualizationSystem::RenderNoPackagesMessage()
{
    RECT rect;
    GetClientRect(hwnd, &rect);

    DrawText(rect.right / 2 - 100, rect.bottom / 2 - 50, "No Asset Packages Found", RGB(255, 0, 0));
    DrawText(rect.right / 2 - 150, rect.bottom / 2 - 20, "Generating Default Earth World...", RGB(255, 255, 0));
}

void VisualizationSystem::DrawSphere(float x, float y, float radius, COLORREF color)
{
    HPEN pen = CreatePen(PS_SOLID, 2, color);
    HBRUSH brush = CreateSolidBrush(color);
    SelectObject(hdc, pen);
    SelectObject(hdc, brush);

    Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);

    DeleteObject(pen);
    DeleteObject(brush);
}

void VisualizationSystem::DrawText(float x, float y, const std::string &text, COLORREF color)
{
    SetTextColor(hdc, color);
    SetBkMode(hdc, TRANSPARENT);
    TextOutA(hdc, x, y, text.c_str(), text.length());
}
#ifndef VISUALIZATION_SYSTEM_H
#define VISUALIZATION_SYSTEM_H

#include "core/ISystem.h"
#include "core/EventBus.h"
#include "core/World.h"
#include "events/InputEvents.h"
#include "events/WorldGenEvents.h"
#include <windows.h>
#include <string>
#include <vector>

class VisualizationSystem : public ISystem
{
public:
    VisualizationSystem(EventBus &eventBus, World &world, HWND hwnd);
    ~VisualizationSystem();

    void update(World &world, float deltaTime) override;

private:
    EventBus &eventBus;
    World &worldRef;
    HWND hwnd;
    HDC hdc;

    bool displayNoPackagesMessage;
    bool consoleVisible;
    float rotationAngle;

    void OnNoPackagesFound(const NoPackagesFoundEvent &event);
    void OnConsoleVisibilityChanged(const ConsoleVisibilityChangedEvent &event);

    void RenderEntities();
    void RenderConsole();
    void RenderNoPackagesMessage();
    void DrawSphere(float x, float y, float radius, COLORREF color);
    void DrawText(float x, float y, const std::string &text, COLORREF color);
};

#endif
#pragma once

#include "../core/System.h"
#include "../components/VoxelCloudComponent.h"
#include "../math/MathUtils.h"
#include <vector>
#include <memory>
#include <map>
#include <array>

namespace ECS
{

    // ============================================================================
    // Voxel Cloud Data Structures
    // ============================================================================

    struct VoxelData
    {
        float density = 0.0f; // 0.0 = empty, 1.0 = solid
        Math::float4 color = {1.0f, 1.0f, 1.0f, 1.0f};
        Math::float3 normal = {0.0f, 1.0f, 0.0f};
        float temperature = 0.0f; // For heat distortion effects
        float humidity = 0.0f;    // For cloud formation
        uint8_t materialId = 0;   // Different cloud types

        bool isEmpty() const { return density <= 0.001f; }
        bool isSolid() const { return density >= 0.999f; }
    };

    struct VoxelChunk
    {
        static constexpr uint32_t CHUNK_SIZE = 16; // 16x16x16 voxels per chunk
        static constexpr uint32_t VOXEL_COUNT = CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE;

        std::array<VoxelData, VOXEL_COUNT> voxels;
        Math::float3 worldPosition;
        bool needsMeshUpdate = true;
        bool isEmpty = true;

        // Mesh data for rendering
        std::vector<Math::float3> vertices;
        std::vector<Math::float3> normals;
        std::vector<Math::float2> uvs;
        std::vector<Math::float4> colors;
        std::vector<uint32_t> indices;

        // GPU buffer handles
        uint32_t vertexBufferId = 0;
        uint32_t indexBufferId = 0;
        uint32_t instanceBufferId = 0;

        // Optimization data
        uint32_t activeVoxelCount = 0;
        float boundingRadius = 0.0f;
        float lastUpdateTime = 0.0f;

        VoxelData &getVoxel(uint32_t x, uint32_t y, uint32_t z);
        const VoxelData &getVoxel(uint32_t x, uint32_t y, uint32_t z) const;
        void setVoxel(uint32_t x, uint32_t y, uint32_t z, const VoxelData &voxel);

        void clear();
        void updateBounds();
        size_t getVoxelIndex(uint32_t x, uint32_t y, uint32_t z) const;
    };

    struct CloudLayer
    {
        float altitude = 0.0f;
        float thickness = 100.0f;
        float coverage = 0.5f; // 0.0 = no clouds, 1.0 = full coverage
        float density = 0.8f;
        Math::float4 baseColor = {1.0f, 1.0f, 1.0f, 1.0f};
        Math::float4 shadowColor = {0.3f, 0.3f, 0.5f, 1.0f};

        // Animation properties
        Math::float2 windSpeed = {2.0f, 0.0f};
        float evolutionSpeed = 0.1f; // How fast clouds change shape
        float turbulence = 0.3f;

        // Noise parameters for generation
        uint32_t seed = 12345;
        float noiseScale = 0.01f;
        uint32_t noiseOctaves = 4;
        float noisePersistence = 0.5f;
        float noiseLacunarity = 2.0f;
    };

    // ============================================================================
    // Voxel Cloud System Configuration
    // ============================================================================

    struct VoxelCloudSystemConfig
    {
        // World parameters
        Math::float3 worldSize = {1000.0f, 200.0f, 1000.0f};
        float voxelSize = 2.0f;    // Size of each voxel in world units
        uint32_t maxChunks = 1000; // Maximum number of active chunks

        // Rendering settings
        uint32_t renderDistance = 500; // Distance in voxels
        uint32_t lodLevels = 4;        // Number of LOD levels
        bool enableVolumetricLighting = true;
        bool enableShadows = true;
        bool enableScattering = true;

        // Performance settings
        uint32_t maxChunkUpdatesPerFrame = 5;
        uint32_t maxMeshGenerationsPerFrame = 2;
        float cullingDistance = 1000.0f;
        bool enableFrustumCulling = true;
        bool enableOcclusionCulling = false;

        // Quality settings
        bool enableSmoothNormals = true;
        bool enableAmbientOcclusion = false;
        float ambientOcclusionRadius = 3.0f;
        uint32_t ambientOcclusionSamples = 16;

        // Animation settings
        bool enableCloudEvolution = true;
        float globalWindSpeed = 1.0f;
        Math::float3 globalWindDirection = {1.0f, 0.0f, 0.0f};
        float turbulenceIntensity = 0.5f;

        // Memory management
        bool useChunkPooling = true;
        uint32_t chunkPoolSize = 200;
        bool enableGarbageCollection = true;
        float garbageCollectionInterval = 5.0f; // seconds
    };

    // ============================================================================
    // Main Voxel Cloud System
    // ============================================================================

    class VoxelCloudSystem : public System
    {
    public:
        explicit VoxelCloudSystem(const VoxelCloudSystemConfig &config = VoxelCloudSystemConfig{});
        ~VoxelCloudSystem() override;

        // System interface
        void initialize() override;
        void update(float deltaTime) override;
        void render() override;
        void shutdown() override;

        // Configuration management
        void setConfig(const VoxelCloudSystemConfig &config);
        const VoxelCloudSystemConfig &getConfig() const;

        // Cloud management
        void createVoxelCloud(EntityId entityId, const VoxelCloudComponent &component);
        void removeVoxelCloud(EntityId entityId);
        void updateVoxelCloudComponent(EntityId entityId, const VoxelCloudComponent &component);

        // World interaction
        void setVoxel(const Math::float3 &worldPos, const VoxelData &voxel);
        VoxelData getVoxel(const Math::float3 &worldPos) const;
        void clearVoxels(const Math::float3 &center, float radius);
        void addCloudMass(const Math::float3 &center, float radius, float density);

        // Environmental controls
        void setGlobalWind(const Math::float3 &windDirection, float windSpeed);
        void addCloudLayer(const CloudLayer &layer);
        void removeCloudLayer(uint32_t layerIndex);
        void updateCloudLayer(uint32_t layerIndex, const CloudLayer &layer);

        // Lighting and atmosphere
        void setSunDirection(const Math::float3 &direction);
        void setSunColor(const Math::float4 &color);
        void setAmbientColor(const Math::float4 &color);
        void setScatteringCoefficients(float rayleigh, float mie);

        // Performance monitoring
        uint32_t getActiveChunkCount() const;
        uint32_t getTotalVoxelCount() const;
        float getAverageUpdateTime() const;

        // Debug and visualization
        void setDebugVisualization(bool enabled);
        bool isDebugVisualizationEnabled() const;
        void renderDebugInfo();

    protected:
        // Component handling
        void onComponentAdded(EntityId entityId, ComponentType type) override;
        void onComponentRemoved(EntityId entityId, ComponentType type) override;
        void onComponentChanged(EntityId entityId, ComponentType type) override;

    private:
        // ============================================================================
        // Internal Cloud Management
        // ============================================================================

        struct CloudData
        {
            VoxelCloudComponent component;
            std::map<Math::int3, std::unique_ptr<VoxelChunk>, Math::Int3Comparator> chunks;

            // Generation parameters
            Math::float3 center;
            Math::float3 size;
            float totalDensity = 0.0f;

            // Animation state
            float animationTime = 0.0f;
            Math::float3 windOffset = {0.0f, 0.0f, 0.0f};

            // Performance tracking
            uint32_t activeChunkCount = 0;
            float lastFullUpdate = 0.0f;

            CloudData() = default;
            CloudData(const VoxelCloudComponent &comp) : component(comp) {}
        };

        VoxelCloudSystemConfig config_;
        std::map<EntityId, std::unique_ptr<CloudData>> activeClouds_;
        std::vector<CloudLayer> cloudLayers_;

        // Environmental state
        Math::float3 sunDirection_ = {0.707f, 0.707f, 0.0f};
        Math::float4 sunColor_ = {1.0f, 0.9f, 0.7f, 1.0f};
        Math::float4 ambientColor_ = {0.2f, 0.3f, 0.5f, 1.0f};
        float rayleighScattering_ = 0.0025f;
        float mieScattering_ = 0.004f;

        Math::float3 globalWindDirection_ = {1.0f, 0.0f, 0.0f};
        float globalWindSpeed_ = 1.0f;

        // Performance tracking
        mutable float averageUpdateTime_ = 0.0f;
        mutable uint32_t updateSampleCount_ = 0;
        float lastGarbageCollection_ = 0.0f;

        // Debug visualization
        bool debugVisualization_ = false;

        // Chunk pooling for performance
        std::vector<std::unique_ptr<VoxelChunk>> chunkPool_;
        std::vector<VoxelChunk *> freeChunks_;

        // ============================================================================
        // Core Update Methods
        // ============================================================================

        void updateCloudGeneration(CloudData &cloud, float deltaTime);
        void updateCloudAnimation(CloudData &cloud, float deltaTime);
        void updateChunkMeshes(CloudData &cloud);
        void updateVisibility(CloudData &cloud);
        void performGarbageCollection();

        // ============================================================================
        // Chunk Management
        // ============================================================================

        Math::int3 worldToChunkCoord(const Math::float3 &worldPos) const;
        Math::float3 chunkToWorldPos(const Math::int3 &chunkCoord) const;
        Math::int3 voxelToLocalCoord(const Math::float3 &worldPos) const;

        VoxelChunk *getOrCreateChunk(CloudData &cloud, const Math::int3 &chunkCoord);
        void removeChunk(CloudData &cloud, const Math::int3 &chunkCoord);
        bool isChunkVisible(const VoxelChunk &chunk) const;
        void cullDistantChunks(CloudData &cloud);

        // ============================================================================
        // Voxel Generation and Manipulation
        // ============================================================================

        void generateCloudVoxels(CloudData &cloud);
        float calculateCloudDensity(const Math::float3 &worldPos, const CloudData &cloud, float time) const;
        Math::float4 calculateCloudColor(const Math::float3 &worldPos, float density, const CloudData &cloud) const;

        void applyCloudLayers(const Math::float3 &worldPos, VoxelData &voxel, float time) const;
        float sampleLayerDensity(const CloudLayer &layer, const Math::float3 &worldPos, float time) const;

        // Noise functions for cloud generation
        float fractalNoise(const Math::float3 &pos, uint32_t seed, uint32_t octaves,
                           float persistence, float lacunarity, float scale) const;
        float billowNoise(const Math::float3 &pos, uint32_t seed, float scale) const;
        float ridgedNoise(const Math::float3 &pos, uint32_t seed, float scale) const;

        // ============================================================================
        // Mesh Generation
        // ============================================================================

        void generateChunkMesh(VoxelChunk &chunk);
        void generateMarchingCubesMesh(VoxelChunk &chunk);
        void generateInstancedMesh(VoxelChunk &chunk);

        // Marching cubes implementation
        void marchCube(const VoxelChunk &chunk, uint32_t x, uint32_t y, uint32_t z,
                       std::vector<Math::float3> &vertices, std::vector<uint32_t> &indices);
        Math::float3 interpolateVertex(const Math::float3 &p1, const Math::float3 &p2,
                                       float density1, float density2, float isoLevel = 0.5f);

        // Mesh optimization
        void smoothMeshNormals(VoxelChunk &chunk);
        void calculateAmbientOcclusion(VoxelChunk &chunk);
        void optimizeMesh(VoxelChunk &chunk);

        // ============================================================================
        // Rendering Support
        // ============================================================================

        void renderCloud(const CloudData &cloud);
        void renderChunk(const VoxelChunk &chunk, const CloudData &cloud);
        void setupCloudMaterial(const VoxelCloudComponent &component);
        void setupVolumetricLighting();
        void setupAtmosphericScattering();

        // Volumetric rendering
        void renderVolumetricClouds(const CloudData &cloud);
        void renderCloudShadows(const CloudData &cloud);
        void applyAtmosphericPerspective(const VoxelChunk &chunk);

        // ============================================================================
        // Utility Methods
        // ============================================================================

        Math::float3 getEntityPosition(EntityId entityId) const;
        Math::float3 getCameraPosition() const;
        float calculateLODLevel(const Math::float3 &position) const;
        bool isInFrustum(const VoxelChunk &chunk) const;

        // Lighting calculations
        float calculateShadowFactor(const Math::float3 &worldPos, const CloudData &cloud) const;
        Math::float4 calculateVolumetricLighting(const Math::float3 &worldPos, const Math::float3 &viewDir) const;
        float calculateScattering(float cosTheta, float g) const; // Henyey-Greenstein phase function

        // Object pooling
        VoxelChunk *acquireChunk();
        void releaseChunk(VoxelChunk *chunk);
        void expandChunkPool();

        // Performance optimization
        bool shouldUpdateChunk(const VoxelChunk &chunk, float deltaTime) const;
        void updatePerformanceCounters(float deltaTime);

        // ============================================================================
        // Physics and Simulation
        // ============================================================================

        void simulateCloudPhysics(CloudData &cloud, float deltaTime);
        void applyWindForces(VoxelChunk &chunk, const Math::float3 &wind, float deltaTime);
        void simulateEvaporation(VoxelChunk &chunk, float deltaTime);
        void simulateCondensation(VoxelChunk &chunk, float deltaTime);

        // ============================================================================
        // Debug and Profiling
        // ============================================================================

        void renderCloudDebugInfo(const CloudData &cloud, EntityId entityId);
        void renderChunkBounds(const VoxelChunk &chunk);
        void logCloudStatistics() const;
    };

    // ============================================================================
    // Inline Implementation for Performance-Critical Methods
    // ============================================================================

    inline VoxelData &VoxelChunk::getVoxel(uint32_t x, uint32_t y, uint32_t z)
    {
        return voxels[getVoxelIndex(x, y, z)];
    }

    inline const VoxelData &VoxelChunk::getVoxel(uint32_t x, uint32_t y, uint32_t z) const
    {
        return voxels[getVoxelIndex(x, y, z)];
    }

    inline void VoxelChunk::setVoxel(uint32_t x, uint32_t y, uint32_t z, const VoxelData &voxel)
    {
        voxels[getVoxelIndex(x, y, z)] = voxel;
        needsMeshUpdate = true;
    }

    inline size_t VoxelChunk::getVoxelIndex(uint32_t x, uint32_t y, uint32_t z) const
    {
        return x + y * CHUNK_SIZE + z * CHUNK_SIZE * CHUNK_SIZE;
    }

    inline uint32_t VoxelCloudSystem::getActiveChunkCount() const
    {
        uint32_t total = 0;
        for (const auto &[entityId, cloud] : activeClouds_)
        {
            total += cloud->activeChunkCount;
        }
        return total;
    }

    inline uint32_t VoxelCloudSystem::getTotalVoxelCount() const
    {
        return getActiveChunkCount() * VoxelChunk::VOXEL_COUNT;
    }

    inline float VoxelCloudSystem::getAverageUpdateTime() const
    {
        return averageUpdateTime_;
    }

    inline bool VoxelCloudSystem::isDebugVisualizationEnabled() const
    {
        return debugVisualization_;
    }

    inline void VoxelCloudSystem::setDebugVisualization(bool enabled)
    {
        debugVisualization_ = enabled;
    }

    inline const VoxelCloudSystemConfig &VoxelCloudSystem::getConfig() const
    {
        return config_;
    }

    inline Math::int3 VoxelCloudSystem::worldToChunkCoord(const Math::float3 &worldPos) const
    {
        float chunkWorldSize = VoxelChunk::CHUNK_SIZE * config_.voxelSize;
        return {
            static_cast<int32_t>(std::floor(worldPos.x / chunkWorldSize)),
            static_cast<int32_t>(std::floor(worldPos.y / chunkWorldSize)),
            static_cast<int32_t>(std::floor(worldPos.z / chunkWorldSize))};
    }

    inline Math::float3 VoxelCloudSystem::chunkToWorldPos(const Math::int3 &chunkCoord) const
    {
        float chunkWorldSize = VoxelChunk::CHUNK_SIZE * config_.voxelSize;
        return {
            chunkCoord.x * chunkWorldSize,
            chunkCoord.y * chunkWorldSize,
            chunkCoord.z * chunkWorldSize};
    }

} // namespace ECS
#include "WorldGenSystem.h"
#include "MaterialManager.h"
#include "core/Entity.h"
#include "../math/MathUtils.h"
#include <iostream>
#include <cmath>
#include <memory>
#include <fstream>
#include <regex>
#include <sstream>

// Component definitions (using Math:: types)
#include "../core/IComponent.h"

struct TransformC : public IComponent
{
    Math::float3 position;
    Math::float4 orientation; // Quaternion (x, y, z, w)
    Math::float3 scale;

    TransformC(Math::float3 pos = {0.0f, 0.0f, 0.0f},
               Math::float4 rot = {0.0f, 0.0f, 0.0f, 1.0f},
               Math::float3 scl = {1.0f, 1.0f, 1.0f})
        : position(pos), orientation(rot), scale(scl) {}
};

struct RenderableC : public IComponent
{
    std::string meshId;
    std::string materialId;
    bool isVisible;

    RenderableC(std::string mesh = "", std::string material = "", bool visible = true)
        : meshId(mesh), materialId(material), isVisible(visible) {}
};

WorldGenSystem::WorldGenSystem(EventBus &eventBus, World &world, AssetRegistry &assetRegistry)
    : eventBus(eventBus), worldRef(world), assetRegistry_(assetRegistry), sceneLoaded(false)
{
    // Initialize generic backend systems
    meshGenerator_ = std::make_unique<VoxelMeshGenerator>();
    textureGenerator_ = std::make_unique<ProceduralTexture::ProceduralTextureGenerator>();
    sceneParser_ = std::make_unique<SceneConfig::SceneConfigParser>();
    materialManager_ = std::make_unique<Material::MaterialManager>();

    // Connect systems together
    materialManager_->SetTextureGenerator(textureGenerator_.get());
    materialManager_->LoadDefaultMaterials();
    
    // Load configuration from file
    if (!LoadWorldGenerationConfig()) {
        std::cout << "Warning: Using default world generation parameters." << std::endl;
    }

    // Subscribe to no packages found event
    eventBus.subscribe(EventType::NoPackagesFound, [this](const IEvent &event)
                       {
        const auto& packagesEvent = static_cast<const NoPackagesFoundEvent&>(event);
        OnNoPackagesFound(packagesEvent); });

    // Subscribe to default world generated event (when we have XML configuration)
    eventBus.subscribe(EventType::DefaultWorldGenerated, [this](const IEvent &event)
                       {
        const auto& worldEvent = static_cast<const DefaultWorldGeneratedEvent&>(event);
        OnDefaultWorldRequested(worldEvent); });
}

void WorldGenSystem::update(World &world, float deltaTime)
{
    // World generation is event-driven, no continuous updates needed
}

void WorldGenSystem::LoadScene(const std::string &sceneType)
{
    if (sceneLoaded)
        return;

    std::cout << "Loading scene of type: " << sceneType << std::endl;

    // For now, fallback to default generation
    // TODO: Implement proper XML scene loading when SceneConfigParser API is ready
    GenerateDefaultSphereWorld();
}

void WorldGenSystem::LoadSceneEntities(const SceneConfig::Scene &sceneData)
{
    // TODO: Implement when SceneConfig API is properly defined
    std::cout << "Loading scene entities from XML configuration..." << std::endl;
}

AssetId WorldGenSystem::GenerateVoxelMesh(const SceneConfig::CompoundMesh &meshConfig)
{
    // TODO: Bridge to VoxelMeshGenerator when API is aligned
    return "generated_mesh_placeholder";
}

void WorldGenSystem::GenerateDefaultSphereWorld()
{
    if (sceneLoaded)
        return;

    std::cout << "Generating default Earth-like sphere world..." << std::endl;

    static unsigned int nextEntityId = 1;

    // Create Earth entity using MaterialManager
    auto earthEntity = std::make_unique<Entity>(nextEntityId++);
    earthEntity->addComponent(std::make_unique<TransformC>(
        worldConfig_.earthPosition,
        worldConfig_.earthOrientation,
        worldConfig_.earthScale));

    // Use MaterialManager to create dynamic Earth material
    std::string earthMaterialId = materialManager_->HasMaterial("EarthSurfaceMaterial") ? 
        "EarthSurfaceMaterial" : materialManager_->CreateEarthMaterial(worldConfig_.earthRadius, worldConfig_.earthDetailLevel);

    // For now, use placeholder mesh ID
    earthEntity->addComponent(std::make_unique<RenderableC>(
        "earth_sphere_mesh",
        earthMaterialId,
        true));
    worldRef.addEntity(std::move(earthEntity));

    // Create atmosphere entity
    auto atmosphereEntity = std::make_unique<Entity>(nextEntityId++);
    atmosphereEntity->addComponent(std::make_unique<TransformC>(
        worldConfig_.earthPosition,
        worldConfig_.earthOrientation,
        worldConfig_.earthScale));

    std::string atmosphereMaterialId = materialManager_->HasMaterial("AtmosphereMaterial") ? 
        "AtmosphereMaterial" : materialManager_->CreateAtmosphereMaterial(1, worldConfig_.atmosphereDensity);

    atmosphereEntity->addComponent(std::make_unique<RenderableC>(
        "atmosphere_sphere_mesh",
        atmosphereMaterialId,
        true));
    worldRef.addEntity(std::move(atmosphereEntity));

    // Create cloud entity
    auto cloudEntity = std::make_unique<Entity>(nextEntityId++);
    cloudEntity->addComponent(std::make_unique<TransformC>(
        worldConfig_.earthPosition,
        worldConfig_.earthOrientation,
        worldConfig_.earthScale));

    std::string cloudMaterialId = materialManager_->HasMaterial("CloudMaterial") ? 
        "CloudMaterial" : materialManager_->CreateCloudMaterial(worldConfig_.cloudCoverage, worldConfig_.cloudDensity);

    cloudEntity->addComponent(std::make_unique<RenderableC>(
        "cloud_sphere_mesh",
        cloudMaterialId,
        true));
    worldRef.addEntity(std::move(cloudEntity));

    sceneLoaded = true;
    eventBus.publish(DefaultWorldGeneratedEvent{});
    std::cout << "Default world generation complete." << std::endl;
}

void WorldGenSystem::OnNoPackagesFound(const NoPackagesFoundEvent &event)
{
    LoadScene(worldConfig_.defaultSceneType);
}

void WorldGenSystem::OnDefaultWorldRequested(const DefaultWorldGeneratedEvent &event)
{
    if (sceneLoaded)
        return;

    // Try to load the default scene configuration
    try
    {
        LoadScene(worldConfig_.defaultSceneType);
    }
    catch (const std::exception &e)
    {
        std::cout << "Error loading default scene: " << e.what() << ", falling back to hardcoded generation..." << std::endl;
        GenerateDefaultSphereWorld();
    }
}

// Legacy material methods (placeholder implementations)
AssetId WorldGenSystem::GetEarthMaterialId()
{
    return materialManager_->HasMaterial("EarthSurfaceMaterial") ? 
        "EarthSurfaceMaterial" : materialManager_->CreateEarthMaterial(worldConfig_.earthRadius, worldConfig_.earthDetailLevel);
}

AssetId WorldGenSystem::GetAtmosphereMaterialId(int layer)
{
    std::string materialName = "AtmosphereMaterial_Layer" + std::to_string(layer);
    return materialManager_->HasMaterial(materialName) ? 
        materialName : materialManager_->CreateAtmosphereMaterial(layer, worldConfig_.atmosphereDensity);
}

AssetId WorldGenSystem::GetCloudMaterialId()
{
    return materialManager_->HasMaterial("CloudMaterial") ? 
        "CloudMaterial" : materialManager_->CreateCloudMaterial(worldConfig_.cloudCoverage, worldConfig_.cloudDensity);
}
#pragma once
#include "core/ISystem.h"
#include "core/EventBus.h"
#include "core/World.h"
#include "core/AssetRegistry.h"
#include "events/WorldGenEvents.h"
#include "../config/SceneConfigParser.h"
#include "../generators/VoxelMeshGenerator.h"
#include "../generators/ProceduralTextureGenerator.h"
#include "MaterialManager.h"
#include "../math/MathUtils.h"
#include <memory>

/**
 * Generic world generation system using XML-driven scene configuration.
 * Supports all scene types through SceneConfigParser and VoxelMeshGenerator.
 */
class WorldGenSystem : public ISystem
{
public:
    WorldGenSystem(EventBus &eventBus, World &world, AssetRegistry &assetRegistry);
    virtual ~WorldGenSystem() = default;

    void update(World &world, float deltaTime) override;
    void GenerateDefaultSphereWorld();
    void GenerateWorldFromXMLScene(const std::string &sceneXml);
    void GenerateWorldFromSceneFile(const std::string &sceneFilePath);
    void LoadScene(const SceneConfig::Scene &scene);
    
    // Configuration methods
    bool LoadWorldGenerationConfig(const std::string& configPath = "configs/world_gen_config.xml");

private:
    EventBus &eventBus;
    World &worldRef;
    AssetRegistry &assetRegistry_;
    bool sceneLoaded;
    
    // Configuration parameters (formerly hardcoded)
    struct WorldConfig {
        // Earth parameters
        float earthRadius = 6371000.0f;
        int earthDetailLevel = 2;
        Math::float3 earthPosition = {0.0f, -6371000.0f, 0.0f};
        Math::float4 earthOrientation = {0.0f, 0.0f, 0.0f, 1.0f};
        Math::float3 earthScale = {1.0f, 1.0f, 1.0f};
        
        // Atmosphere parameters
        float atmosphereDensity = 0.1f;
        
        // Cloud parameters
        float cloudCoverage = 0.6f;
        float cloudDensity = 0.3f;
        
        // Scene parameters
        std::string defaultSceneType = "loading_indicator";
    } worldConfig_;

    // Generic backend systems
    std::unique_ptr<VoxelMeshGenerator> meshGenerator_;
    std::unique_ptr<ProceduralTexture::ProceduralTextureGenerator> textureGenerator_;
    std::unique_ptr<SceneConfig::SceneConfigParser> sceneParser_;
    std::unique_ptr<Material::MaterialManager> materialManager_;

    // Core scene loading methods
    void LoadScene(const std::string &sceneType);
    void LoadSceneEntities(const SceneConfig::Scene &scene);
    AssetId GenerateVoxelMesh(const SceneConfig::CompoundMesh &meshConfig);
    
    // Helper methods for XML parsing
    std::string ExtractNodeValue(const std::string& xml, const std::string& nodeName, const std::string& defaultValue = "");
    float ExtractFloatValue(const std::string& xml, const std::string& nodePath, float defaultValue = 0.0f);
    int ExtractIntValue(const std::string& xml, const std::string& nodePath, int defaultValue = 0);

    // Event handlers
    void OnNoPackagesFound(const NoPackagesFoundEvent &event);
    void OnDefaultWorldRequested(const DefaultWorldGeneratedEvent &event);

    // Legacy material methods (will be removed when MaterialManager is fully integrated)
    AssetId GetEarthMaterialId();
    AssetId GetAtmosphereMaterialId(int layer);
    AssetId GetCloudMaterialId();
};
bool WorldGenSystem::LoadWorldGenerationConfig(const std::string& configPath)
{
    std::ifstream file(configPath);
    if (!file.is_open()) {
        std::cerr << "Failed to open world generation config file: " << configPath << std::endl;
        return false;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string xmlContent = buffer.str();
    file.close();

    // Parse Earth parameters
    worldConfig_.earthRadius = ExtractFloatValue(xmlContent, "world_generation/earth/radius", 6371000.0f);
    worldConfig_.earthDetailLevel = ExtractIntValue(xmlContent, "world_generation/earth/detail_level", 2);
    
    // Extract Earth position
    worldConfig_.earthPosition.x = ExtractFloatValue(xmlContent, "world_generation/earth/position/x", 0.0f);
    worldConfig_.earthPosition.y = ExtractFloatValue(xmlContent, "world_generation/earth/position/y", -6371000.0f);
    worldConfig_.earthPosition.z = ExtractFloatValue(xmlContent, "world_generation/earth/position/z", 0.0f);
    
    // Extract Earth orientation
    worldConfig_.earthOrientation.x = ExtractFloatValue(xmlContent, "world_generation/earth/orientation/x", 0.0f);
    worldConfig_.earthOrientation.y = ExtractFloatValue(xmlContent, "world_generation/earth/orientation/y", 0.0f);
    worldConfig_.earthOrientation.z = ExtractFloatValue(xmlContent, "world_generation/earth/orientation/z", 0.0f);
    worldConfig_.earthOrientation.w = ExtractFloatValue(xmlContent, "world_generation/earth/orientation/w", 1.0f);
    
    // Extract Earth scale
    worldConfig_.earthScale.x = ExtractFloatValue(xmlContent, "world_generation/earth/scale/x", 1.0f);
    worldConfig_.earthScale.y = ExtractFloatValue(xmlContent, "world_generation/earth/scale/y", 1.0f);
    worldConfig_.earthScale.z = ExtractFloatValue(xmlContent, "world_generation/earth/scale/z", 1.0f);
    
    // Parse Atmosphere parameters
    worldConfig_.atmosphereDensity = ExtractFloatValue(xmlContent, "world_generation/atmosphere/layer[@id='1']/density", 0.1f);
    
    // Parse Cloud parameters
    worldConfig_.cloudCoverage = ExtractFloatValue(xmlContent, "world_generation/clouds/coverage", 0.6f);
    worldConfig_.cloudDensity = ExtractFloatValue(xmlContent, "world_generation/clouds/density", 0.3f);
    
    // Parse Scene parameters
    worldConfig_.defaultSceneType = ExtractNodeValue(xmlContent, "world_generation/scenes/default_scene", "loading_indicator");
    
    std::cout << "Loaded world generation config from: " << configPath << std::endl;
    std::cout << " - Earth radius: " << worldConfig_.earthRadius << std::endl;
    std::cout << " - Default scene type: " << worldConfig_.defaultSceneType << std::endl;
    
    return true;
}

// Helper method to extract a node value from XML content
std::string WorldGenSystem::ExtractNodeValue(const std::string& xml, const std::string& nodePath, const std::string& defaultValue)
{
    // Simple XML node extraction - basic implementation
    std::string pattern = "<" + nodePath + ">([^<]*)</" + nodePath.substr(nodePath.find_last_of("/") + 1) + ">";
    std::regex re(pattern);
    std::smatch match;
    
    if (std::regex_search(xml, match, re) && match.size() > 1) {
        return match[1].str();
    }
    return defaultValue;
}

// Helper method to extract a float value from XML content
float WorldGenSystem::ExtractFloatValue(const std::string& xml, const std::string& nodePath, float defaultValue)
{
    std::string valueStr = ExtractNodeValue(xml, nodePath);
    if (!valueStr.empty()) {
        try {
            return std::stof(valueStr);
        } catch (const std::exception& e) {
            std::cerr << "Error parsing float value for " << nodePath << ": " << e.what() << std::endl;
        }
    }
    return defaultValue;
}

// Helper method to extract an integer value from XML content
int WorldGenSystem::ExtractIntValue(const std::string& xml, const std::string& nodePath, int defaultValue)
{
    std::string valueStr = ExtractNodeValue(xml, nodePath);
    if (!valueStr.empty()) {
        try {
            return std::stoi(valueStr);
        } catch (const std::exception& e) {
            std::cerr << "Error parsing integer value for " << nodePath << ": " << e.what() << std::endl;
        }
    }
    return defaultValue;
}
#include "WorldGenSystem.h"
#include "MaterialManager.h"
#include "core/Entity.h"
#include "../math/MathUtils.h"
#include <iostream>
#include <cmath>
#include <memory>
#include <fstream>

// Component definitions (using Math:: types)
#include "../core/IComponent.h"

struct TransformC : public IComponent
{
    Math::float3 position;
    Math::float4 orientation; // Quaternion (x, y, z, w)
    Math::float3 scale;

    TransformC(Math::float3 pos = {0.0f, 0.0f, 0.0f},
               Math::float4 rot = {0.0f, 0.0f, 0.0f, 1.0f},
               Math::float3 scl = {1.0f, 1.0f, 1.0f})
        : position(pos), orientation(rot), scale(scl) {}
};

struct RenderableC : public IComponent
{
    std::string meshId;
    std::string materialId;
    bool isVisible;

    RenderableC(std::string mesh = "", std::string material = "", bool visible = true)
        : meshId(mesh), materialId(material), isVisible(visible) {}
};

WorldGenSystem::WorldGenSystem(EventBus &eventBus, World &world, AssetRegistry &assetRegistry)
    : eventBus(eventBus), worldRef(world), assetRegistry_(assetRegistry), sceneLoaded(false)
{
    // Initialize generic backend systems
    meshGenerator_ = std::make_unique<VoxelMeshGenerator>();
    textureGenerator_ = std::make_unique<ProceduralTexture::ProceduralTextureGenerator>();
    sceneParser_ = std::make_unique<SceneConfig::SceneConfigParser>();
    materialManager_ = std::make_unique<Material::MaterialManager>();

    // Connect systems together
    materialManager_->SetTextureGenerator(textureGenerator_.get());
    materialManager_->LoadDefaultMaterials();

    // Subscribe to no packages found event
    eventBus.subscribe(EventType::NoPackagesFound, [this](const IEvent &event)
                       {
        const auto& packagesEvent = static_cast<const NoPackagesFoundEvent&>(event);
        OnNoPackagesFound(packagesEvent); });

    // Subscribe to default world generated event (when we have XML configuration)
    eventBus.subscribe(EventType::DefaultWorldGenerated, [this](const IEvent &event)
                       {
        const auto& worldEvent = static_cast<const DefaultWorldGeneratedEvent&>(event);
        OnDefaultWorldRequested(worldEvent); });
}

void WorldGenSystem::update(World &world, float deltaTime)
{
    // World generation is event-driven, no continuous updates needed
}

void WorldGenSystem::LoadScene(const std::string &sceneType)
{
    if (sceneLoaded)
        return;

    std::cout << "Loading scene of type: " << sceneType << std::endl;

    // For now, fallback to default generation
    // TODO: Implement proper XML scene loading when SceneConfigParser API is ready
    GenerateDefaultSphereWorld();
}

void WorldGenSystem::LoadSceneEntities(const SceneConfig::Scene &sceneData)
{
    // TODO: Implement when SceneConfig API is properly defined
    std::cout << "Loading scene entities from XML configuration..." << std::endl;
}

AssetId WorldGenSystem::GenerateVoxelMesh(const SceneConfig::CompoundMesh &meshConfig)
{
    // TODO: Bridge to VoxelMeshGenerator when API is aligned
    return "generated_mesh_placeholder";
}

void WorldGenSystem::GenerateDefaultSphereWorld()
{
    if (sceneLoaded)
        return;

    std::cout << "Generating default Earth-like sphere world..." << std::endl;

    static unsigned int nextEntityId = 1;

    // Create Earth entity using MaterialManager
    auto earthEntity = std::make_unique<Entity>(nextEntityId++);
    earthEntity->addComponent(std::make_unique<TransformC>(
        Math::float3(0.0f, -6371000.0f, 0.0f),
        Math::float4(0.0f, 0.0f, 0.0f, 1.0f),
        Math::float3(1.0f, 1.0f, 1.0f)));

    // Use MaterialManager to create dynamic Earth material
    std::string earthMaterialId = materialManager_->HasMaterial("EarthSurfaceMaterial") ? "EarthSurfaceMaterial" : materialManager_->CreateEarthMaterial(6371000.0f, 2);

    // For now, use placeholder mesh ID
    earthEntity->addComponent(std::make_unique<RenderableC>(
        "earth_sphere_mesh",
        earthMaterialId,
        true));
    worldRef.addEntity(std::move(earthEntity));

    // Create atmosphere entity
    auto atmosphereEntity = std::make_unique<Entity>(nextEntityId++);
    atmosphereEntity->addComponent(std::make_unique<TransformC>(
        Math::float3(0.0f, -6371000.0f, 0.0f),
        Math::float4(0.0f, 0.0f, 0.0f, 1.0f),
        Math::float3(1.0f, 1.0f, 1.0f)));

    std::string atmosphereMaterialId = materialManager_->HasMaterial("AtmosphereMaterial") ? "AtmosphereMaterial" : materialManager_->CreateAtmosphereMaterial(1, 0.1f);

    atmosphereEntity->addComponent(std::make_unique<RenderableC>(
        "atmosphere_sphere_mesh",
        atmosphereMaterialId,
        true));
    worldRef.addEntity(std::move(atmosphereEntity));

    // Create cloud entity
    auto cloudEntity = std::make_unique<Entity>(nextEntityId++);
    cloudEntity->addComponent(std::make_unique<TransformC>(
        Math::float3(0.0f, -6371000.0f, 0.0f),
        Math::float4(0.0f, 0.0f, 0.0f, 1.0f),
        Math::float3(1.0f, 1.0f, 1.0f)));

    std::string cloudMaterialId = materialManager_->HasMaterial("CloudMaterial") ? "CloudMaterial" : materialManager_->CreateCloudMaterial(0.6f, 0.3f);

    cloudEntity->addComponent(std::make_unique<RenderableC>(
        "cloud_sphere_mesh",
        cloudMaterialId,
        true));
    worldRef.addEntity(std::move(cloudEntity));

    sceneLoaded = true;
    eventBus.publish(DefaultWorldGeneratedEvent{});
    std::cout << "Default world generation complete." << std::endl;
}

void WorldGenSystem::OnNoPackagesFound(const NoPackagesFoundEvent &event)
{
    LoadScene("loading_indicator");
}

void WorldGenSystem::OnDefaultWorldRequested(const DefaultWorldGeneratedEvent &event)
{
    if (sceneLoaded)
        return;

    // Try to load the default scene configuration
    try
    {
        LoadScene("loading_indicator");
    }
    catch (const std::exception &e)
    {
        std::cout << "Error loading default scene: " << e.what() << ", falling back to hardcoded generation..." << std::endl;
        GenerateDefaultSphereWorld();
    }
}

// Legacy material methods (placeholder implementations)
AssetId WorldGenSystem::GetEarthMaterialId()
{
    return materialManager_->HasMaterial("EarthSurfaceMaterial") ? "EarthSurfaceMaterial" : materialManager_->CreateEarthMaterial(6371000.0f, 1);
}

AssetId WorldGenSystem::GetAtmosphereMaterialId(int layer)
{
    std::string materialName = "AtmosphereMaterial_Layer" + std::to_string(layer);
    return materialManager_->HasMaterial(materialName) ? materialName : materialManager_->CreateAtmosphereMaterial(layer, 0.1f);
}

AssetId WorldGenSystem::GetCloudMaterialId()
{
    return materialManager_->HasMaterial("CloudMaterial") ? "CloudMaterial" : materialManager_->CreateCloudMaterial(0.6f, 0.3f);
}
#include "WorldGenSystem.h"
#include "MaterialManager.h"
#include "core/Entity.h"
#include "../math/MathUtils.h"
#include <iostream>
#include <cmath>
#include <memory>
#include <fstream>

// Component definitions (using Math:: types instead of old Vector3D/Quaternion)
#include "../core/IComponent.h"

struct TransformC : public IComponent
{
    Math::float3 position;
    Math::float4 orientation; // Quaternion (x, y, z, w)
    Math::float3 scale;

    TransformC(Math::float3 pos = {0.0f, 0.0f, 0.0f}, 
               Math::float4 rot = {0.0f, 0.0f, 0.0f, 1.0f}, 
               Math::float3 scl = {1.0f, 1.0f, 1.0f})
        : position(pos), orientation(rot), scale(scl) {}
};

struct RenderableC : public IComponent
{
    std::string meshId;
    std::string materialId;
    bool isVisible;

    RenderableC(std::string mesh = "", std::string material = "", bool visible = true)
        : meshId(mesh), materialId(material), isVisible(visible) {}
};

WorldGenSystem::WorldGenSystem(EventBus &eventBus, World &world, AssetRegistry &assetRegistry)
    : eventBus(eventBus), worldRef(world), assetRegistry_(assetRegistry), sceneLoaded(false)
{
    // Initialize generic backend systems
    meshGenerator_ = std::make_unique<VoxelMeshGenerator>();
    textureGenerator_ = std::make_unique<ProceduralTexture::ProceduralTextureGenerator>();
    sceneParser_ = std::make_unique<SceneConfig::SceneConfigParser>();
    materialManager_ = std::make_unique<Material::MaterialManager>();
    
    // Connect systems together
    materialManager_->SetTextureGenerator(textureGenerator_.get());
    materialManager_->LoadDefaultMaterials();

    // Subscribe to no packages found event
    eventBus.subscribe(EventType::NoPackagesFound, [this](const IEvent &event)
                       {
        const auto& packagesEvent = static_cast<const NoPackagesFoundEvent&>(event);
        OnNoPackagesFound(packagesEvent); });

    // Subscribe to default world generated event (when we have XML configuration)
    eventBus.subscribe(EventType::DefaultWorldGenerated, [this](const IEvent &event)
                       {
        const auto& worldEvent = static_cast<const DefaultWorldGeneratedEvent&>(event);
        OnDefaultWorldRequested(worldEvent); });
}

void WorldGenSystem::update(World &world, float deltaTime)
{
    // World generation is event-driven, no continuous updates needed
}

void WorldGenSystem::LoadScene(const std::string& sceneType)
{
    if (sceneLoaded)
        return;

    try 
    {
        auto sceneData = sceneParser_.LoadScene(sceneType);
        if (sceneData)
        {
            std::cout << "Loading scene of type: " << sceneType << std::endl;
            LoadSceneEntities(*sceneData);
            defaultWorldGenerated = true;
            eventBus.publish(DefaultWorldGeneratedEvent{});
            std::cout << "Scene loading complete." << std::endl;
        }
        else
        {
            std::cout << "Failed to load scene, falling back to default generation..." << std::endl;
            GenerateDefaultSphereWorld();
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "Error loading scene: " << e.what() << ", falling back to default generation..." << std::endl;
        GenerateDefaultSphereWorld();
    }
}

void WorldGenSystem::LoadSceneEntities(const SceneConfig& sceneData)
{
    static unsigned int nextEntityId = 1;

    for (const auto& entityConfig : sceneData.entities)
    {
        auto entity = std::make_unique<Entity>(nextEntityId++);
        
        // Add transform component
        entity->addComponent(std::make_unique<TransformC>(
            entityConfig.position,
            entityConfig.rotation, 
            entityConfig.scale
        ));

        // Generate mesh based on primitive type
        AssetId meshId = GenerateVoxelMesh(entityConfig.primitive);
        
        // Create or get material based on entity type
        std::string materialId = entityConfig.material;
        if (materialId.empty() || !materialManager_->HasMaterial(materialId)) {
            // Create dynamic material based on entity type
            if (entityConfig.name.find("Earth") != std::string::npos) {
                materialId = materialManager_->CreateEarthMaterial(entityConfig.primitive.radius, 1);
            } else if (entityConfig.name.find("Atmosphere") != std::string::npos) {
                int layer = 0;
                if (entityConfig.name.find("Layer1") != std::string::npos) layer = 1;
                else if (entityConfig.name.find("Layer2") != std::string::npos) layer = 2;
                materialId = materialManager_->CreateAtmosphereMaterial(layer, 0.1f);
            } else if (entityConfig.name.find("Cloud") != std::string::npos) {
                materialId = materialManager_->CreateCloudMaterial(0.6f, 0.3f);
            } else {
                // Use default material
                materialId = entityConfig.material.empty() ? "default_material" : entityConfig.material;
            }
        }
        
        // Add renderable component with generated mesh and material
        entity->addComponent(std::make_unique<RenderableC>(
            meshId,
            materialId,
            true
        ));

        // Add optional components based on configuration
        if (!entityConfig.animationClips.empty())
        {
            entity->addComponent(std::make_unique<AnimationC>(
                entityConfig.animationClips,
                0.0f, // current time
                true  // playing
            ));
        }

        if (entityConfig.hasContrail)
        {
            entity->addComponent(std::make_unique<ContrailC>(
                std::vector<Math::float3>(), // trail points
                entityConfig.contrailWidth,
                entityConfig.contrailLength,
                materialManager_->CreateContrailMaterial({1.0f, 1.0f, 1.0f}),
                entityConfig.contrailLifetime
            ));
        }

        if (entityConfig.hasVoxelCloud)
        {
            entity->addComponent(std::make_unique<VoxelCloudC>(
                entityConfig.cloudDensity,
                entityConfig.cloudScale,
                materialManager_->CreateCloudMaterial(entityConfig.cloudDensity, entityConfig.cloudScale),
                entityConfig.cloudNoiseScale
            ));
        }

        worldRef.addEntity(std::move(entity));
        std::cout << "Created entity: " << entityConfig.name << " with material: " << materialId << std::endl;
    }
}

AssetId WorldGenSystem::GenerateVoxelMesh(const VoxelPrimitive& primitive)
{
    return meshGenerator_.GenerateMesh(primitive);
}

void WorldGenSystem::GenerateDefaultSphereWorld()
{
    if (sceneLoaded)
        return;

    std::cout << "Generating default Earth-like sphere world..." << std::endl;

    static unsigned int nextEntityId = 1;

    // Create Earth entity using MaterialManager
    auto earthEntity = std::make_unique<Entity>(nextEntityId++);
    earthEntity->addComponent(std::make_unique<TransformC>(
        Math::float3(0.0f, -6371000.0f, 0.0f),
        Math::float4(0.0f, 0.0f, 0.0f, 1.0f),
        Math::float3(1.0f, 1.0f, 1.0f)
    ));
    
    // Use MaterialManager to create dynamic Earth material
    std::string earthMaterialId = materialManager_->HasMaterial("EarthSurfaceMaterial") ? 
                                 "EarthSurfaceMaterial" : 
                                 materialManager_->CreateEarthMaterial(6371000.0f, 2);
    
    // For now, use placeholder mesh ID
    earthEntity->addComponent(std::make_unique<RenderableC>(
        "earth_sphere_mesh",
        earthMaterialId,
        true
    ));
    worldRef.addEntity(std::move(earthEntity));

    // Create atmosphere entity
    auto atmosphereEntity = std::make_unique<Entity>(nextEntityId++);
    atmosphereEntity->addComponent(std::make_unique<TransformC>(
        Math::float3(0.0f, -6371000.0f, 0.0f),
        Math::float4(0.0f, 0.0f, 0.0f, 1.0f),
        Math::float3(1.0f, 1.0f, 1.0f)
    ));
    
    std::string atmosphereMaterialId = materialManager_->HasMaterial("AtmosphereMaterial") ? 
                                      "AtmosphereMaterial" : 
                                      materialManager_->CreateAtmosphereMaterial(1, 0.1f);
    
    atmosphereEntity->addComponent(std::make_unique<RenderableC>(
        "atmosphere_sphere_mesh",
        atmosphereMaterialId,
        true
    ));
    worldRef.addEntity(std::move(atmosphereEntity));

    // Create cloud entity
    auto cloudEntity = std::make_unique<Entity>(nextEntityId++);
    cloudEntity->addComponent(std::make_unique<TransformC>(
        Math::float3(0.0f, -6371000.0f, 0.0f),
        Math::float4(0.0f, 0.0f, 0.0f, 1.0f),
        Math::float3(1.0f, 1.0f, 1.0f)
    ));
    
    std::string cloudMaterialId = materialManager_->HasMaterial("CloudMaterial") ? 
                                 "CloudMaterial" : 
                                 materialManager_->CreateCloudMaterial(0.6f, 0.3f);
    
    cloudEntity->addComponent(std::make_unique<RenderableC>(
        "cloud_sphere_mesh",
        cloudMaterialId,
        true
    ));
    worldRef.addEntity(std::move(cloudEntity));

    sceneLoaded = true;
    eventBus.publish(DefaultWorldGeneratedEvent{});
    std::cout << "Default world generation complete." << std::endl;
}

void WorldGenSystem::OnNoPackagesFound(const NoPackagesFoundEvent &event)
{
    LoadScene("loading_indicator");
}

void WorldGenSystem::OnDefaultWorldRequested(const DefaultWorldGeneratedEvent &event)
{
    if (sceneLoaded)
        return;

    // Try to load the default scene configuration
    try 
    {
        LoadScene("loading_indicator");
    }
    catch (const std::exception& e)
    {
        std::cout << "Error loading default scene: " << e.what() << ", falling back to hardcoded generation..." << std::endl;
        GenerateDefaultSphereWorld();
    }
}

// Simplified scene loading for now
void WorldGenSystem::LoadScene(const std::string& sceneType)
{
    if (sceneLoaded)
        return;

    std::cout << "Loading scene of type: " << sceneType << std::endl;
    
    // For now, fallback to default generation
    // TODO: Implement proper XML scene loading when SceneConfigParser API is ready
    GenerateDefaultSphereWorld();
}

void WorldGenSystem::LoadSceneEntities(const SceneConfig::Scene& sceneData)
{
    // TODO: Implement when SceneConfig API is properly defined
    std::cout << "Loading scene entities from XML configuration..." << std::endl;
}

AssetId WorldGenSystem::GenerateVoxelMesh(const SceneConfig::CompoundMesh& meshConfig)
{
    // TODO: Bridge to VoxelMeshGenerator when API is aligned
    return "generated_mesh_placeholder";
}
#ifndef IXMLPARSER_H
#define IXMLPARSER_H

#include <string>

class IXmlParser
{
public:
    virtual ~IXmlParser() = default;
    virtual bool loadFile(const std::string &path) = 0;
    // Add more methods as needed
};

#endif
#include "PugiXmlParser.h"

bool PugiXmlParser::loadFile(const std::string &path)
{
    // Stub: simulate loading
    return true;
}
#ifndef PUGIXMLPARSER_H
#define PUGIXMLPARSER_H

#include "IXmlParser.h"

class PugiXmlParser : public IXmlParser
{
public:
    bool loadFile(const std::string &path) override;
    // Add more methods
};

#endif
#include "DroneBuilder.h"

DroneBuilder::DroneBuilder(IXmlParser &xmlParser) : xmlParser_(xmlParser) {}

std::unique_ptr<Entity> DroneBuilder::build(const std::string &configPath, EventBus &eventBus)
{
    // Stub: parse config, create entity with components
    auto entity = std::make_unique<Entity>(1); // id 1
    // Add components, e.g. TransformC, BatteryC, etc.
    return entity;
}
#ifndef DRONEBUILDER_H
#define DRONEBUILDER_H

#include "IVehicleBuilder.h"
#include "utils/IXmlParser.h"

class DroneBuilder : public IVehicleBuilder
{
public:
    DroneBuilder(IXmlParser &xmlParser);
    std::unique_ptr<Entity> build(const std::string &configPath, EventBus &eventBus) override;

private:
    IXmlParser &xmlParser_;
};

#endif
#ifndef IVEHICLEBUILDER_H
#define IVEHICLEBUILDER_H

#include <memory>
#include <string>
#include "core/Entity.h"
#include "core/EventBus.h"

class IVehicleBuilder
{
public:
    virtual ~IVehicleBuilder() = default;
    virtual std::unique_ptr<Entity> build(const std::string &configPath, EventBus &eventBus) = 0;
};

#endif
/* This source file must have a .cpp extension so that all C++ compilers
   recognize the extension without flags.  Borland does not know .cxx for
   example.  */
#ifndef __cplusplus
# error "A C compiler has been selected for C++."
#endif

#if !defined(__has_include)
/* If the compiler does not have __has_include, pretend the answer is
   always no.  */
#  define __has_include(x) 0
#endif


/* Version number components: V=Version, R=Revision, P=Patch
   Version date components:   YYYY=Year, MM=Month,   DD=Day  */

#if defined(__INTEL_COMPILER) || defined(__ICC)
# define COMPILER_ID "Intel"
# if defined(_MSC_VER)
#  define SIMULATE_ID "MSVC"
# endif
# if defined(__GNUC__)
#  define SIMULATE_ID "GNU"
# endif
  /* __INTEL_COMPILER = VRP prior to 2021, and then VVVV for 2021 and later,
     except that a few beta releases use the old format with V=2021.  */
# if __INTEL_COMPILER < 2021 || __INTEL_COMPILER == 202110 || __INTEL_COMPILER == 202111
#  define COMPILER_VERSION_MAJOR DEC(__INTEL_COMPILER/100)
#  define COMPILER_VERSION_MINOR DEC(__INTEL_COMPILER/10 % 10)
#  if defined(__INTEL_COMPILER_UPDATE)
#   define COMPILER_VERSION_PATCH DEC(__INTEL_COMPILER_UPDATE)
#  else
#   define COMPILER_VERSION_PATCH DEC(__INTEL_COMPILER   % 10)
#  endif
# else
#  define COMPILER_VERSION_MAJOR DEC(__INTEL_COMPILER)
#  define COMPILER_VERSION_MINOR DEC(__INTEL_COMPILER_UPDATE)
   /* The third version component from --version is an update index,
      but no macro is provided for it.  */
#  define COMPILER_VERSION_PATCH DEC(0)
# endif
# if defined(__INTEL_COMPILER_BUILD_DATE)
   /* __INTEL_COMPILER_BUILD_DATE = YYYYMMDD */
#  define COMPILER_VERSION_TWEAK DEC(__INTEL_COMPILER_BUILD_DATE)
# endif
# if defined(_MSC_VER)
   /* _MSC_VER = VVRR */
#  define SIMULATE_VERSION_MAJOR DEC(_MSC_VER / 100)
#  define SIMULATE_VERSION_MINOR DEC(_MSC_VER % 100)
# endif
# if defined(__GNUC__)
#  define SIMULATE_VERSION_MAJOR DEC(__GNUC__)
# elif defined(__GNUG__)
#  define SIMULATE_VERSION_MAJOR DEC(__GNUG__)
# endif
# if defined(__GNUC_MINOR__)
#  define SIMULATE_VERSION_MINOR DEC(__GNUC_MINOR__)
# endif
# if defined(__GNUC_PATCHLEVEL__)
#  define SIMULATE_VERSION_PATCH DEC(__GNUC_PATCHLEVEL__)
# endif

#elif (defined(__clang__) && defined(__INTEL_CLANG_COMPILER)) || defined(__INTEL_LLVM_COMPILER)
# define COMPILER_ID "IntelLLVM"
#if defined(_MSC_VER)
# define SIMULATE_ID "MSVC"
#endif
#if defined(__GNUC__)
# define SIMULATE_ID "GNU"
#endif
/* __INTEL_LLVM_COMPILER = VVVVRP prior to 2021.2.0, VVVVRRPP for 2021.2.0 and
 * later.  Look for 6 digit vs. 8 digit version number to decide encoding.
 * VVVV is no smaller than the current year when a version is released.
 */
#if __INTEL_LLVM_COMPILER < 1000000L
# define COMPILER_VERSION_MAJOR DEC(__INTEL_LLVM_COMPILER/100)
# define COMPILER_VERSION_MINOR DEC(__INTEL_LLVM_COMPILER/10 % 10)
# define COMPILER_VERSION_PATCH DEC(__INTEL_LLVM_COMPILER    % 10)
#else
# define COMPILER_VERSION_MAJOR DEC(__INTEL_LLVM_COMPILER/10000)
# define COMPILER_VERSION_MINOR DEC(__INTEL_LLVM_COMPILER/100 % 100)
# define COMPILER_VERSION_PATCH DEC(__INTEL_LLVM_COMPILER     % 100)
#endif
#if defined(_MSC_VER)
  /* _MSC_VER = VVRR */
# define SIMULATE_VERSION_MAJOR DEC(_MSC_VER / 100)
# define SIMULATE_VERSION_MINOR DEC(_MSC_VER % 100)
#endif
#if defined(__GNUC__)
# define SIMULATE_VERSION_MAJOR DEC(__GNUC__)
#elif defined(__GNUG__)
# define SIMULATE_VERSION_MAJOR DEC(__GNUG__)
#endif
#if defined(__GNUC_MINOR__)
# define SIMULATE_VERSION_MINOR DEC(__GNUC_MINOR__)
#endif
#if defined(__GNUC_PATCHLEVEL__)
# define SIMULATE_VERSION_PATCH DEC(__GNUC_PATCHLEVEL__)
#endif

#elif defined(__PATHCC__)
# define COMPILER_ID "PathScale"
# define COMPILER_VERSION_MAJOR DEC(__PATHCC__)
# define COMPILER_VERSION_MINOR DEC(__PATHCC_MINOR__)
# if defined(__PATHCC_PATCHLEVEL__)
#  define COMPILER_VERSION_PATCH DEC(__PATHCC_PATCHLEVEL__)
# endif

#elif defined(__BORLANDC__) && defined(__CODEGEARC_VERSION__)
# define COMPILER_ID "Embarcadero"
# define COMPILER_VERSION_MAJOR HEX(__CODEGEARC_VERSION__>>24 & 0x00FF)
# define COMPILER_VERSION_MINOR HEX(__CODEGEARC_VERSION__>>16 & 0x00FF)
# define COMPILER_VERSION_PATCH DEC(__CODEGEARC_VERSION__     & 0xFFFF)

#elif defined(__BORLANDC__)
# define COMPILER_ID "Borland"
  /* __BORLANDC__ = 0xVRR */
# define COMPILER_VERSION_MAJOR HEX(__BORLANDC__>>8)
# define COMPILER_VERSION_MINOR HEX(__BORLANDC__ & 0xFF)

#elif defined(__WATCOMC__) && __WATCOMC__ < 1200
# define COMPILER_ID "Watcom"
   /* __WATCOMC__ = VVRR */
# define COMPILER_VERSION_MAJOR DEC(__WATCOMC__ / 100)
# define COMPILER_VERSION_MINOR DEC((__WATCOMC__ / 10) % 10)
# if (__WATCOMC__ % 10) > 0
#  define COMPILER_VERSION_PATCH DEC(__WATCOMC__ % 10)
# endif

#elif defined(__WATCOMC__)
# define COMPILER_ID "OpenWatcom"
   /* __WATCOMC__ = VVRP + 1100 */
# define COMPILER_VERSION_MAJOR DEC((__WATCOMC__ - 1100) / 100)
# define COMPILER_VERSION_MINOR DEC((__WATCOMC__ / 10) % 10)
# if (__WATCOMC__ % 10) > 0
#  define COMPILER_VERSION_PATCH DEC(__WATCOMC__ % 10)
# endif

#elif defined(__SUNPRO_CC)
# define COMPILER_ID "SunPro"
# if __SUNPRO_CC >= 0x5100
   /* __SUNPRO_CC = 0xVRRP */
#  define COMPILER_VERSION_MAJOR HEX(__SUNPRO_CC>>12)
#  define COMPILER_VERSION_MINOR HEX(__SUNPRO_CC>>4 & 0xFF)
#  define COMPILER_VERSION_PATCH HEX(__SUNPRO_CC    & 0xF)
# else
   /* __SUNPRO_CC = 0xVRP */
#  define COMPILER_VERSION_MAJOR HEX(__SUNPRO_CC>>8)
#  define COMPILER_VERSION_MINOR HEX(__SUNPRO_CC>>4 & 0xF)
#  define COMPILER_VERSION_PATCH HEX(__SUNPRO_CC    & 0xF)
# endif

#elif defined(__HP_aCC)
# define COMPILER_ID "HP"
  /* __HP_aCC = VVRRPP */
# define COMPILER_VERSION_MAJOR DEC(__HP_aCC/10000)
# define COMPILER_VERSION_MINOR DEC(__HP_aCC/100 % 100)
# define COMPILER_VERSION_PATCH DEC(__HP_aCC     % 100)

#elif defined(__DECCXX)
# define COMPILER_ID "Compaq"
  /* __DECCXX_VER = VVRRTPPPP */
# define COMPILER_VERSION_MAJOR DEC(__DECCXX_VER/10000000)
# define COMPILER_VERSION_MINOR DEC(__DECCXX_VER/100000  % 100)
# define COMPILER_VERSION_PATCH DEC(__DECCXX_VER         % 10000)

#elif defined(__IBMCPP__) && defined(__COMPILER_VER__)
# define COMPILER_ID "zOS"
  /* __IBMCPP__ = VRP */
# define COMPILER_VERSION_MAJOR DEC(__IBMCPP__/100)
# define COMPILER_VERSION_MINOR DEC(__IBMCPP__/10 % 10)
# define COMPILER_VERSION_PATCH DEC(__IBMCPP__    % 10)

#elif defined(__open_xl__) && defined(__clang__)
# define COMPILER_ID "IBMClang"
# define COMPILER_VERSION_MAJOR DEC(__open_xl_version__)
# define COMPILER_VERSION_MINOR DEC(__open_xl_release__)
# define COMPILER_VERSION_PATCH DEC(__open_xl_modification__)
# define COMPILER_VERSION_TWEAK DEC(__open_xl_ptf_fix_level__)
# define COMPILER_VERSION_INTERNAL_STR  __clang_version__


#elif defined(__ibmxl__) && defined(__clang__)
# define COMPILER_ID "XLClang"
# define COMPILER_VERSION_MAJOR DEC(__ibmxl_version__)
# define COMPILER_VERSION_MINOR DEC(__ibmxl_release__)
# define COMPILER_VERSION_PATCH DEC(__ibmxl_modification__)
# define COMPILER_VERSION_TWEAK DEC(__ibmxl_ptf_fix_level__)


#elif defined(__IBMCPP__) && !defined(__COMPILER_VER__) && __IBMCPP__ >= 800
# define COMPILER_ID "XL"
  /* __IBMCPP__ = VRP */
# define COMPILER_VERSION_MAJOR DEC(__IBMCPP__/100)
# define COMPILER_VERSION_MINOR DEC(__IBMCPP__/10 % 10)
# define COMPILER_VERSION_PATCH DEC(__IBMCPP__    % 10)

#elif defined(__IBMCPP__) && !defined(__COMPILER_VER__) && __IBMCPP__ < 800
# define COMPILER_ID "VisualAge"
  /* __IBMCPP__ = VRP */
# define COMPILER_VERSION_MAJOR DEC(__IBMCPP__/100)
# define COMPILER_VERSION_MINOR DEC(__IBMCPP__/10 % 10)
# define COMPILER_VERSION_PATCH DEC(__IBMCPP__    % 10)

#elif defined(__NVCOMPILER)
# define COMPILER_ID "NVHPC"
# define COMPILER_VERSION_MAJOR DEC(__NVCOMPILER_MAJOR__)
# define COMPILER_VERSION_MINOR DEC(__NVCOMPILER_MINOR__)
# if defined(__NVCOMPILER_PATCHLEVEL__)
#  define COMPILER_VERSION_PATCH DEC(__NVCOMPILER_PATCHLEVEL__)
# endif

#elif defined(__PGI)
# define COMPILER_ID "PGI"
# define COMPILER_VERSION_MAJOR DEC(__PGIC__)
# define COMPILER_VERSION_MINOR DEC(__PGIC_MINOR__)
# if defined(__PGIC_PATCHLEVEL__)
#  define COMPILER_VERSION_PATCH DEC(__PGIC_PATCHLEVEL__)
# endif

#elif defined(__clang__) && defined(__cray__)
# define COMPILER_ID "CrayClang"
# define COMPILER_VERSION_MAJOR DEC(__cray_major__)
# define COMPILER_VERSION_MINOR DEC(__cray_minor__)
# define COMPILER_VERSION_PATCH DEC(__cray_patchlevel__)
# define COMPILER_VERSION_INTERNAL_STR __clang_version__


#elif defined(_CRAYC)
# define COMPILER_ID "Cray"
# define COMPILER_VERSION_MAJOR DEC(_RELEASE_MAJOR)
# define COMPILER_VERSION_MINOR DEC(_RELEASE_MINOR)

#elif defined(__TI_COMPILER_VERSION__)
# define COMPILER_ID "TI"
  /* __TI_COMPILER_VERSION__ = VVVRRRPPP */
# define COMPILER_VERSION_MAJOR DEC(__TI_COMPILER_VERSION__/1000000)
# define COMPILER_VERSION_MINOR DEC(__TI_COMPILER_VERSION__/1000   % 1000)
# define COMPILER_VERSION_PATCH DEC(__TI_COMPILER_VERSION__        % 1000)

#elif defined(__CLANG_FUJITSU)
# define COMPILER_ID "FujitsuClang"
# define COMPILER_VERSION_MAJOR DEC(__FCC_major__)
# define COMPILER_VERSION_MINOR DEC(__FCC_minor__)
# define COMPILER_VERSION_PATCH DEC(__FCC_patchlevel__)
# define COMPILER_VERSION_INTERNAL_STR __clang_version__


#elif defined(__FUJITSU)
# define COMPILER_ID "Fujitsu"
# if defined(__FCC_version__)
#   define COMPILER_VERSION __FCC_version__
# elif defined(__FCC_major__)
#   define COMPILER_VERSION_MAJOR DEC(__FCC_major__)
#   define COMPILER_VERSION_MINOR DEC(__FCC_minor__)
#   define COMPILER_VERSION_PATCH DEC(__FCC_patchlevel__)
# endif
# if defined(__fcc_version)
#   define COMPILER_VERSION_INTERNAL DEC(__fcc_version)
# elif defined(__FCC_VERSION)
#   define COMPILER_VERSION_INTERNAL DEC(__FCC_VERSION)
# endif


#elif defined(__ghs__)
# define COMPILER_ID "GHS"
/* __GHS_VERSION_NUMBER = VVVVRP */
# ifdef __GHS_VERSION_NUMBER
# define COMPILER_VERSION_MAJOR DEC(__GHS_VERSION_NUMBER / 100)
# define COMPILER_VERSION_MINOR DEC(__GHS_VERSION_NUMBER / 10 % 10)
# define COMPILER_VERSION_PATCH DEC(__GHS_VERSION_NUMBER      % 10)
# endif

#elif defined(__TASKING__)
# define COMPILER_ID "Tasking"
  # define COMPILER_VERSION_MAJOR DEC(__VERSION__/1000)
  # define COMPILER_VERSION_MINOR DEC(__VERSION__ % 100)
# define COMPILER_VERSION_INTERNAL DEC(__VERSION__)

#elif defined(__ORANGEC__)
# define COMPILER_ID "OrangeC"
# define COMPILER_VERSION_MAJOR DEC(__ORANGEC_MAJOR__)
# define COMPILER_VERSION_MINOR DEC(__ORANGEC_MINOR__)
# define COMPILER_VERSION_PATCH DEC(__ORANGEC_PATCHLEVEL__)

#elif defined(__RENESAS__)
# define COMPILER_ID "Renesas"
/* __RENESAS_VERSION__ = 0xVVRRPP00 */
# define COMPILER_VERSION_MAJOR HEX(__RENESAS_VERSION__ >> 24 & 0xFF)
# define COMPILER_VERSION_MINOR HEX(__RENESAS_VERSION__ >> 16 & 0xFF)
# define COMPILER_VERSION_PATCH HEX(__RENESAS_VERSION__ >> 8  & 0xFF)

#elif defined(__SCO_VERSION__)
# define COMPILER_ID "SCO"

#elif defined(__ARMCC_VERSION) && !defined(__clang__)
# define COMPILER_ID "ARMCC"
#if __ARMCC_VERSION >= 1000000
  /* __ARMCC_VERSION = VRRPPPP */
  # define COMPILER_VERSION_MAJOR DEC(__ARMCC_VERSION/1000000)
  # define COMPILER_VERSION_MINOR DEC(__ARMCC_VERSION/10000 % 100)
  # define COMPILER_VERSION_PATCH DEC(__ARMCC_VERSION     % 10000)
#else
  /* __ARMCC_VERSION = VRPPPP */
  # define COMPILER_VERSION_MAJOR DEC(__ARMCC_VERSION/100000)
  # define COMPILER_VERSION_MINOR DEC(__ARMCC_VERSION/10000 % 10)
  # define COMPILER_VERSION_PATCH DEC(__ARMCC_VERSION    % 10000)
#endif


#elif defined(__clang__) && defined(__apple_build_version__)
# define COMPILER_ID "AppleClang"
# if defined(_MSC_VER)
#  define SIMULATE_ID "MSVC"
# endif
# define COMPILER_VERSION_MAJOR DEC(__clang_major__)
# define COMPILER_VERSION_MINOR DEC(__clang_minor__)
# define COMPILER_VERSION_PATCH DEC(__clang_patchlevel__)
# if defined(_MSC_VER)
   /* _MSC_VER = VVRR */
#  define SIMULATE_VERSION_MAJOR DEC(_MSC_VER / 100)
#  define SIMULATE_VERSION_MINOR DEC(_MSC_VER % 100)
# endif
# define COMPILER_VERSION_TWEAK DEC(__apple_build_version__)

#elif defined(__clang__) && defined(__ARMCOMPILER_VERSION)
# define COMPILER_ID "ARMClang"
  # define COMPILER_VERSION_MAJOR DEC(__ARMCOMPILER_VERSION/1000000)
  # define COMPILER_VERSION_MINOR DEC(__ARMCOMPILER_VERSION/10000 % 100)
  # define COMPILER_VERSION_PATCH DEC(__ARMCOMPILER_VERSION/100   % 100)
# define COMPILER_VERSION_INTERNAL DEC(__ARMCOMPILER_VERSION)

#elif defined(__clang__) && defined(__ti__)
# define COMPILER_ID "TIClang"
  # define COMPILER_VERSION_MAJOR DEC(__ti_major__)
  # define COMPILER_VERSION_MINOR DEC(__ti_minor__)
  # define COMPILER_VERSION_PATCH DEC(__ti_patchlevel__)
# define COMPILER_VERSION_INTERNAL DEC(__ti_version__)

#elif defined(__clang__)
# define COMPILER_ID "Clang"
# if defined(_MSC_VER)
#  define SIMULATE_ID "MSVC"
# endif
# define COMPILER_VERSION_MAJOR DEC(__clang_major__)
# define COMPILER_VERSION_MINOR DEC(__clang_minor__)
# define COMPILER_VERSION_PATCH DEC(__clang_patchlevel__)
# if defined(_MSC_VER)
   /* _MSC_VER = VVRR */
#  define SIMULATE_VERSION_MAJOR DEC(_MSC_VER / 100)
#  define SIMULATE_VERSION_MINOR DEC(_MSC_VER % 100)
# endif

#elif defined(__LCC__) && (defined(__GNUC__) || defined(__GNUG__) || defined(__MCST__))
# define COMPILER_ID "LCC"
# define COMPILER_VERSION_MAJOR DEC(__LCC__ / 100)
# define COMPILER_VERSION_MINOR DEC(__LCC__ % 100)
# if defined(__LCC_MINOR__)
#  define COMPILER_VERSION_PATCH DEC(__LCC_MINOR__)
# endif
# if defined(__GNUC__) && defined(__GNUC_MINOR__)
#  define SIMULATE_ID "GNU"
#  define SIMULATE_VERSION_MAJOR DEC(__GNUC__)
#  define SIMULATE_VERSION_MINOR DEC(__GNUC_MINOR__)
#  if defined(__GNUC_PATCHLEVEL__)
#   define SIMULATE_VERSION_PATCH DEC(__GNUC_PATCHLEVEL__)
#  endif
# endif

#elif defined(__GNUC__) || defined(__GNUG__)
# define COMPILER_ID "GNU"
# if defined(__GNUC__)
#  define COMPILER_VERSION_MAJOR DEC(__GNUC__)
# else
#  define COMPILER_VERSION_MAJOR DEC(__GNUG__)
# endif
# if defined(__GNUC_MINOR__)
#  define COMPILER_VERSION_MINOR DEC(__GNUC_MINOR__)
# endif
# if defined(__GNUC_PATCHLEVEL__)
#  define COMPILER_VERSION_PATCH DEC(__GNUC_PATCHLEVEL__)
# endif

#elif defined(_MSC_VER)
# define COMPILER_ID "MSVC"
  /* _MSC_VER = VVRR */
# define COMPILER_VERSION_MAJOR DEC(_MSC_VER / 100)
# define COMPILER_VERSION_MINOR DEC(_MSC_VER % 100)
# if defined(_MSC_FULL_VER)
#  if _MSC_VER >= 1400
    /* _MSC_FULL_VER = VVRRPPPPP */
#   define COMPILER_VERSION_PATCH DEC(_MSC_FULL_VER % 100000)
#  else
    /* _MSC_FULL_VER = VVRRPPPP */
#   define COMPILER_VERSION_PATCH DEC(_MSC_FULL_VER % 10000)
#  endif
# endif
# if defined(_MSC_BUILD)
#  define COMPILER_VERSION_TWEAK DEC(_MSC_BUILD)
# endif

#elif defined(_ADI_COMPILER)
# define COMPILER_ID "ADSP"
#if defined(__VERSIONNUM__)
  /* __VERSIONNUM__ = 0xVVRRPPTT */
#  define COMPILER_VERSION_MAJOR DEC(__VERSIONNUM__ >> 24 & 0xFF)
#  define COMPILER_VERSION_MINOR DEC(__VERSIONNUM__ >> 16 & 0xFF)
#  define COMPILER_VERSION_PATCH DEC(__VERSIONNUM__ >> 8 & 0xFF)
#  define COMPILER_VERSION_TWEAK DEC(__VERSIONNUM__ & 0xFF)
#endif

#elif defined(__IAR_SYSTEMS_ICC__) || defined(__IAR_SYSTEMS_ICC)
# define COMPILER_ID "IAR"
# if defined(__VER__) && defined(__ICCARM__)
#  define COMPILER_VERSION_MAJOR DEC((__VER__) / 1000000)
#  define COMPILER_VERSION_MINOR DEC(((__VER__) / 1000) % 1000)
#  define COMPILER_VERSION_PATCH DEC((__VER__) % 1000)
#  define COMPILER_VERSION_INTERNAL DEC(__IAR_SYSTEMS_ICC__)
# elif defined(__VER__) && (defined(__ICCAVR__) || defined(__ICCRX__) || defined(__ICCRH850__) || defined(__ICCRL78__) || defined(__ICC430__) || defined(__ICCRISCV__) || defined(__ICCV850__) || defined(__ICC8051__) || defined(__ICCSTM8__))
#  define COMPILER_VERSION_MAJOR DEC((__VER__) / 100)
#  define COMPILER_VERSION_MINOR DEC((__VER__) - (((__VER__) / 100)*100))
#  define COMPILER_VERSION_PATCH DEC(__SUBVERSION__)
#  define COMPILER_VERSION_INTERNAL DEC(__IAR_SYSTEMS_ICC__)
# endif

#elif defined(__DCC__) && defined(_DIAB_TOOL)
# define COMPILER_ID "Diab"
  # define COMPILER_VERSION_MAJOR DEC(__VERSION_MAJOR_NUMBER__)
  # define COMPILER_VERSION_MINOR DEC(__VERSION_MINOR_NUMBER__)
  # define COMPILER_VERSION_PATCH DEC(__VERSION_ARCH_FEATURE_NUMBER__)
  # define COMPILER_VERSION_TWEAK DEC(__VERSION_BUG_FIX_NUMBER__)



/* These compilers are either not known or too old to define an
  identification macro.  Try to identify the platform and guess that
  it is the native compiler.  */
#elif defined(__hpux) || defined(__hpua)
# define COMPILER_ID "HP"

#else /* unknown compiler */
# define COMPILER_ID ""
#endif

/* Construct the string literal in pieces to prevent the source from
   getting matched.  Store it in a pointer rather than an array
   because some compilers will just produce instructions to fill the
   array rather than assigning a pointer to a static array.  */
char const* info_compiler = "INFO" ":" "compiler[" COMPILER_ID "]";
#ifdef SIMULATE_ID
char const* info_simulate = "INFO" ":" "simulate[" SIMULATE_ID "]";
#endif

#ifdef __QNXNTO__
char const* qnxnto = "INFO" ":" "qnxnto[]";
#endif

#if defined(__CRAYXT_COMPUTE_LINUX_TARGET)
char const *info_cray = "INFO" ":" "compiler_wrapper[CrayPrgEnv]";
#endif

#define STRINGIFY_HELPER(X) #X
#define STRINGIFY(X) STRINGIFY_HELPER(X)

/* Identify known platforms by name.  */
#if defined(__linux) || defined(__linux__) || defined(linux)
# define PLATFORM_ID "Linux"

#elif defined(__MSYS__)
# define PLATFORM_ID "MSYS"

#elif defined(__CYGWIN__)
# define PLATFORM_ID "Cygwin"

#elif defined(__MINGW32__)
# define PLATFORM_ID "MinGW"

#elif defined(__APPLE__)
# define PLATFORM_ID "Darwin"

#elif defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
# define PLATFORM_ID "Windows"

#elif defined(__FreeBSD__) || defined(__FreeBSD)
# define PLATFORM_ID "FreeBSD"

#elif defined(__NetBSD__) || defined(__NetBSD)
# define PLATFORM_ID "NetBSD"

#elif defined(__OpenBSD__) || defined(__OPENBSD)
# define PLATFORM_ID "OpenBSD"

#elif defined(__sun) || defined(sun)
# define PLATFORM_ID "SunOS"

#elif defined(_AIX) || defined(__AIX) || defined(__AIX__) || defined(__aix) || defined(__aix__)
# define PLATFORM_ID "AIX"

#elif defined(__hpux) || defined(__hpux__)
# define PLATFORM_ID "HP-UX"

#elif defined(__HAIKU__)
# define PLATFORM_ID "Haiku"

#elif defined(__BeOS) || defined(__BEOS__) || defined(_BEOS)
# define PLATFORM_ID "BeOS"

#elif defined(__QNX__) || defined(__QNXNTO__)
# define PLATFORM_ID "QNX"

#elif defined(__tru64) || defined(_tru64) || defined(__TRU64__)
# define PLATFORM_ID "Tru64"

#elif defined(__riscos) || defined(__riscos__)
# define PLATFORM_ID "RISCos"

#elif defined(__sinix) || defined(__sinix__) || defined(__SINIX__)
# define PLATFORM_ID "SINIX"

#elif defined(__UNIX_SV__)
# define PLATFORM_ID "UNIX_SV"

#elif defined(__bsdos__)
# define PLATFORM_ID "BSDOS"

#elif defined(_MPRAS) || defined(MPRAS)
# define PLATFORM_ID "MP-RAS"

#elif defined(__osf) || defined(__osf__)
# define PLATFORM_ID "OSF1"

#elif defined(_SCO_SV) || defined(SCO_SV) || defined(sco_sv)
# define PLATFORM_ID "SCO_SV"

#elif defined(__ultrix) || defined(__ultrix__) || defined(_ULTRIX)
# define PLATFORM_ID "ULTRIX"

#elif defined(__XENIX__) || defined(_XENIX) || defined(XENIX)
# define PLATFORM_ID "Xenix"

#elif defined(__WATCOMC__)
# if defined(__LINUX__)
#  define PLATFORM_ID "Linux"

# elif defined(__DOS__)
#  define PLATFORM_ID "DOS"

# elif defined(__OS2__)
#  define PLATFORM_ID "OS2"

# elif defined(__WINDOWS__)
#  define PLATFORM_ID "Windows3x"

# elif defined(__VXWORKS__)
#  define PLATFORM_ID "VxWorks"

# else /* unknown platform */
#  define PLATFORM_ID
# endif

#elif defined(__INTEGRITY)
# if defined(INT_178B)
#  define PLATFORM_ID "Integrity178"

# else /* regular Integrity */
#  define PLATFORM_ID "Integrity"
# endif

# elif defined(_ADI_COMPILER)
#  define PLATFORM_ID "ADSP"

#else /* unknown platform */
# define PLATFORM_ID

#endif

/* For windows compilers MSVC and Intel we can determine
   the architecture of the compiler being used.  This is because
   the compilers do not have flags that can change the architecture,
   but rather depend on which compiler is being used
*/
#if defined(_WIN32) && defined(_MSC_VER)
# if defined(_M_IA64)
#  define ARCHITECTURE_ID "IA64"

# elif defined(_M_ARM64EC)
#  define ARCHITECTURE_ID "ARM64EC"

# elif defined(_M_X64) || defined(_M_AMD64)
#  define ARCHITECTURE_ID "x64"

# elif defined(_M_IX86)
#  define ARCHITECTURE_ID "X86"

# elif defined(_M_ARM64)
#  define ARCHITECTURE_ID "ARM64"

# elif defined(_M_ARM)
#  if _M_ARM == 4
#   define ARCHITECTURE_ID "ARMV4I"
#  elif _M_ARM == 5
#   define ARCHITECTURE_ID "ARMV5I"
#  else
#   define ARCHITECTURE_ID "ARMV" STRINGIFY(_M_ARM)
#  endif

# elif defined(_M_MIPS)
#  define ARCHITECTURE_ID "MIPS"

# elif defined(_M_SH)
#  define ARCHITECTURE_ID "SHx"

# else /* unknown architecture */
#  define ARCHITECTURE_ID ""
# endif

#elif defined(__WATCOMC__)
# if defined(_M_I86)
#  define ARCHITECTURE_ID "I86"

# elif defined(_M_IX86)
#  define ARCHITECTURE_ID "X86"

# else /* unknown architecture */
#  define ARCHITECTURE_ID ""
# endif

#elif defined(__IAR_SYSTEMS_ICC__) || defined(__IAR_SYSTEMS_ICC)
# if defined(__ICCARM__)
#  define ARCHITECTURE_ID "ARM"

# elif defined(__ICCRX__)
#  define ARCHITECTURE_ID "RX"

# elif defined(__ICCRH850__)
#  define ARCHITECTURE_ID "RH850"

# elif defined(__ICCRL78__)
#  define ARCHITECTURE_ID "RL78"

# elif defined(__ICCRISCV__)
#  define ARCHITECTURE_ID "RISCV"

# elif defined(__ICCAVR__)
#  define ARCHITECTURE_ID "AVR"

# elif defined(__ICC430__)
#  define ARCHITECTURE_ID "MSP430"

# elif defined(__ICCV850__)
#  define ARCHITECTURE_ID "V850"

# elif defined(__ICC8051__)
#  define ARCHITECTURE_ID "8051"

# elif defined(__ICCSTM8__)
#  define ARCHITECTURE_ID "STM8"

# else /* unknown architecture */
#  define ARCHITECTURE_ID ""
# endif

#elif defined(__ghs__)
# if defined(__PPC64__)
#  define ARCHITECTURE_ID "PPC64"

# elif defined(__ppc__)
#  define ARCHITECTURE_ID "PPC"

# elif defined(__ARM__)
#  define ARCHITECTURE_ID "ARM"

# elif defined(__x86_64__)
#  define ARCHITECTURE_ID "x64"

# elif defined(__i386__)
#  define ARCHITECTURE_ID "X86"

# else /* unknown architecture */
#  define ARCHITECTURE_ID ""
# endif

#elif defined(__clang__) && defined(__ti__)
# if defined(__ARM_ARCH)
#  define ARCHITECTURE_ID "ARM"

# else /* unknown architecture */
#  define ARCHITECTURE_ID ""
# endif

#elif defined(__TI_COMPILER_VERSION__)
# if defined(__TI_ARM__)
#  define ARCHITECTURE_ID "ARM"

# elif defined(__MSP430__)
#  define ARCHITECTURE_ID "MSP430"

# elif defined(__TMS320C28XX__)
#  define ARCHITECTURE_ID "TMS320C28x"

# elif defined(__TMS320C6X__) || defined(_TMS320C6X)
#  define ARCHITECTURE_ID "TMS320C6x"

# else /* unknown architecture */
#  define ARCHITECTURE_ID ""
# endif

# elif defined(__ADSPSHARC__)
#  define ARCHITECTURE_ID "SHARC"

# elif defined(__ADSPBLACKFIN__)
#  define ARCHITECTURE_ID "Blackfin"

#elif defined(__TASKING__)

# if defined(__CTC__) || defined(__CPTC__)
#  define ARCHITECTURE_ID "TriCore"

# elif defined(__CMCS__)
#  define ARCHITECTURE_ID "MCS"

# elif defined(__CARM__) || defined(__CPARM__)
#  define ARCHITECTURE_ID "ARM"

# elif defined(__CARC__)
#  define ARCHITECTURE_ID "ARC"

# elif defined(__C51__)
#  define ARCHITECTURE_ID "8051"

# elif defined(__CPCP__)
#  define ARCHITECTURE_ID "PCP"

# else
#  define ARCHITECTURE_ID ""
# endif

#elif defined(__RENESAS__)
# if defined(__CCRX__)
#  define ARCHITECTURE_ID "RX"

# elif defined(__CCRL__)
#  define ARCHITECTURE_ID "RL78"

# elif defined(__CCRH__)
#  define ARCHITECTURE_ID "RH850"

# else
#  define ARCHITECTURE_ID ""
# endif

#else
#  define ARCHITECTURE_ID
#endif

/* Convert integer to decimal digit literals.  */
#define DEC(n)                   \
  ('0' + (((n) / 10000000)%10)), \
  ('0' + (((n) / 1000000)%10)),  \
  ('0' + (((n) / 100000)%10)),   \
  ('0' + (((n) / 10000)%10)),    \
  ('0' + (((n) / 1000)%10)),     \
  ('0' + (((n) / 100)%10)),      \
  ('0' + (((n) / 10)%10)),       \
  ('0' +  ((n) % 10))

/* Convert integer to hex digit literals.  */
#define HEX(n)             \
  ('0' + ((n)>>28 & 0xF)), \
  ('0' + ((n)>>24 & 0xF)), \
  ('0' + ((n)>>20 & 0xF)), \
  ('0' + ((n)>>16 & 0xF)), \
  ('0' + ((n)>>12 & 0xF)), \
  ('0' + ((n)>>8  & 0xF)), \
  ('0' + ((n)>>4  & 0xF)), \
  ('0' + ((n)     & 0xF))

/* Construct a string literal encoding the version number. */
#ifdef COMPILER_VERSION
char const* info_version = "INFO" ":" "compiler_version[" COMPILER_VERSION "]";

/* Construct a string literal encoding the version number components. */
#elif defined(COMPILER_VERSION_MAJOR)
char const info_version[] = {
  'I', 'N', 'F', 'O', ':',
  'c','o','m','p','i','l','e','r','_','v','e','r','s','i','o','n','[',
  COMPILER_VERSION_MAJOR,
# ifdef COMPILER_VERSION_MINOR
  '.', COMPILER_VERSION_MINOR,
#  ifdef COMPILER_VERSION_PATCH
   '.', COMPILER_VERSION_PATCH,
#   ifdef COMPILER_VERSION_TWEAK
    '.', COMPILER_VERSION_TWEAK,
#   endif
#  endif
# endif
  ']','\0'};
#endif

/* Construct a string literal encoding the internal version number. */
#ifdef COMPILER_VERSION_INTERNAL
char const info_version_internal[] = {
  'I', 'N', 'F', 'O', ':',
  'c','o','m','p','i','l','e','r','_','v','e','r','s','i','o','n','_',
  'i','n','t','e','r','n','a','l','[',
  COMPILER_VERSION_INTERNAL,']','\0'};
#elif defined(COMPILER_VERSION_INTERNAL_STR)
char const* info_version_internal = "INFO" ":" "compiler_version_internal[" COMPILER_VERSION_INTERNAL_STR "]";
#endif

/* Construct a string literal encoding the version number components. */
#ifdef SIMULATE_VERSION_MAJOR
char const info_simulate_version[] = {
  'I', 'N', 'F', 'O', ':',
  's','i','m','u','l','a','t','e','_','v','e','r','s','i','o','n','[',
  SIMULATE_VERSION_MAJOR,
# ifdef SIMULATE_VERSION_MINOR
  '.', SIMULATE_VERSION_MINOR,
#  ifdef SIMULATE_VERSION_PATCH
   '.', SIMULATE_VERSION_PATCH,
#   ifdef SIMULATE_VERSION_TWEAK
    '.', SIMULATE_VERSION_TWEAK,
#   endif
#  endif
# endif
  ']','\0'};
#endif

/* Construct the string literal in pieces to prevent the source from
   getting matched.  Store it in a pointer rather than an array
   because some compilers will just produce instructions to fill the
   array rather than assigning a pointer to a static array.  */
char const* info_platform = "INFO" ":" "platform[" PLATFORM_ID "]";
char const* info_arch = "INFO" ":" "arch[" ARCHITECTURE_ID "]";



#define CXX_STD_98 199711L
#define CXX_STD_11 201103L
#define CXX_STD_14 201402L
#define CXX_STD_17 201703L
#define CXX_STD_20 202002L
#define CXX_STD_23 202302L

#if defined(__INTEL_COMPILER) && defined(_MSVC_LANG)
#  if _MSVC_LANG > CXX_STD_17
#    define CXX_STD _MSVC_LANG
#  elif _MSVC_LANG == CXX_STD_17 && defined(__cpp_aggregate_paren_init)
#    define CXX_STD CXX_STD_20
#  elif _MSVC_LANG > CXX_STD_14 && __cplusplus > CXX_STD_17
#    define CXX_STD CXX_STD_20
#  elif _MSVC_LANG > CXX_STD_14
#    define CXX_STD CXX_STD_17
#  elif defined(__INTEL_CXX11_MODE__) && defined(__cpp_aggregate_nsdmi)
#    define CXX_STD CXX_STD_14
#  elif defined(__INTEL_CXX11_MODE__)
#    define CXX_STD CXX_STD_11
#  else
#    define CXX_STD CXX_STD_98
#  endif
#elif defined(_MSC_VER) && defined(_MSVC_LANG)
#  if _MSVC_LANG > __cplusplus
#    define CXX_STD _MSVC_LANG
#  else
#    define CXX_STD __cplusplus
#  endif
#elif defined(__NVCOMPILER)
#  if __cplusplus == CXX_STD_17 && defined(__cpp_aggregate_paren_init)
#    define CXX_STD CXX_STD_20
#  else
#    define CXX_STD __cplusplus
#  endif
#elif defined(__INTEL_COMPILER) || defined(__PGI)
#  if __cplusplus == CXX_STD_11 && defined(__cpp_namespace_attributes)
#    define CXX_STD CXX_STD_17
#  elif __cplusplus == CXX_STD_11 && defined(__cpp_aggregate_nsdmi)
#    define CXX_STD CXX_STD_14
#  else
#    define CXX_STD __cplusplus
#  endif
#elif (defined(__IBMCPP__) || defined(__ibmxl__)) && defined(__linux__)
#  if __cplusplus == CXX_STD_11 && defined(__cpp_aggregate_nsdmi)
#    define CXX_STD CXX_STD_14
#  else
#    define CXX_STD __cplusplus
#  endif
#elif __cplusplus == 1 && defined(__GXX_EXPERIMENTAL_CXX0X__)
#  define CXX_STD CXX_STD_11
#else
#  define CXX_STD __cplusplus
#endif

const char* info_language_standard_default = "INFO" ":" "standard_default["
#if CXX_STD > CXX_STD_23
  "26"
#elif CXX_STD > CXX_STD_20
  "23"
#elif CXX_STD > CXX_STD_17
  "20"
#elif CXX_STD > CXX_STD_14
  "17"
#elif CXX_STD > CXX_STD_11
  "14"
#elif CXX_STD >= CXX_STD_11
  "11"
#else
  "98"
#endif
"]";

const char* info_language_extensions_default = "INFO" ":" "extensions_default["
#if (defined(__clang__) || defined(__GNUC__) || defined(__xlC__) ||           \
     defined(__TI_COMPILER_VERSION__) || defined(__RENESAS__)) &&             \
  !defined(__STRICT_ANSI__)
  "ON"
#else
  "OFF"
#endif
"]";

/*--------------------------------------------------------------------------*/

int main(int argc, char* argv[])
{
  int require = 0;
  require += info_compiler[argc];
  require += info_platform[argc];
  require += info_arch[argc];
#ifdef COMPILER_VERSION_MAJOR
  require += info_version[argc];
#endif
#if defined(COMPILER_VERSION_INTERNAL) || defined(COMPILER_VERSION_INTERNAL_STR)
  require += info_version_internal[argc];
#endif
#ifdef SIMULATE_ID
  require += info_simulate[argc];
#endif
#ifdef SIMULATE_VERSION_MAJOR
  require += info_simulate_version[argc];
#endif
#if defined(__CRAYXT_COMPUTE_LINUX_TARGET)
  require += info_cray[argc];
#endif
  require += info_language_standard_default[argc];
  require += info_language_extensions_default[argc];
  (void)argv;
  return require;
}
#include <iostream>
#include <vector>
#include "../src/math/MathUtils.h"

int main()
{
    std::cout << "=== Testing Orbital Mechanics Math Implementation ===" << std::endl;

    // Test basic vector operations
    Math::float3 v1{1.0f, 2.0f, 3.0f};
    Math::float3 v2{4.0f, 5.0f, 6.0f};

    Math::float3 sum = Math::add(v1, v2);
    std::cout << "Vector addition: (" << sum.x << ", " << sum.y << ", " << sum.z << ")" << std::endl;

    float dot = Math::dot(v1, v2);
    std::cout << "Dot product: " << dot << std::endl;

    Math::float3 cross = Math::cross(v1, v2);
    std::cout << "Cross product: (" << cross.x << ", " << cross.y << ", " << cross.z << ")" << std::endl;

    // Test orbital mechanics
    Math::OrbitParams orbit;
    orbit.semiMajorAxis = 5.0f;
    orbit.eccentricity = 0.2f;
    orbit.angularRate = 1.0f;
    orbit.inclination = 0.0f;
    orbit.phaseOffset = 0.0f;

    float time = 0.0f;
    Math::float3 position = Math::calculateOrbitPosition(orbit, time);
    std::cout << "Orbital position at t=0: (" << position.x << ", " << position.y << ", " << position.z << ")" << std::endl;

    Math::float3 velocity = Math::calculateOrbitVelocity(orbit, time);
    std::cout << "Orbital velocity at t=0: (" << velocity.x << ", " << velocity.y << ", " << velocity.z << ")" << std::endl;

    // Test quaternions
    Math::quat q1{0.0f, 0.0f, 0.0f, 1.0f};
    Math::quat q2{0.0f, 0.5f, 0.0f, 0.866f}; // 60 degree rotation around Y
    Math::quat result = Math::q_mul(q1, q2);
    std::cout << "Quaternion multiplication: (" << result.x << ", " << result.y << ", " << result.z << ", " << result.w << ")" << std::endl;

    // Test random number generation
    uint32_t seed = 12345;
    float rand1 = Math::rand01(seed);
    float rand2 = Math::rand01(seed);
    std::cout << "Random numbers: " << rand1 << ", " << rand2 << std::endl;

    std::cout << "=== All tests completed ===" << std::endl;
    return 0;
}
#include <iostream>
#include "src/math/MathUtils.h"

int main()
{
    std::cout << "=== Testing Orbital Mechanics Math Implementation ===" << std::endl;

    // Test basic vector operations
    Math::float3 v1{1.0f, 2.0f, 3.0f};
    Math::float3 v2{4.0f, 5.0f, 6.0f};

    Math::float3 sum = Math::add(v1, v2);
    std::cout << "Vector addition: (" << sum.x << ", " << sum.y << ", " << sum.z << ")" << std::endl;

    float dot = Math::dot(v1, v2);
    std::cout << "Dot product: " << dot << std::endl;

    Math::float3 cross = Math::cross(v1, v2);
    std::cout << "Cross product: (" << cross.x << ", " << cross.y << ", " << cross.z << ")" << std::endl;

    // Test orbital mechanics
    Math::OrbitParams orbit;
    orbit.semiMajorAxis = 5.0f;
    orbit.eccentricity = 0.2f;
    orbit.angularRate = 1.0f;
    orbit.inclination = 0.0f;
    orbit.phaseOffset = 0.0f;

    float time = 0.0f;
    Math::float3 position = Math::calculateOrbitPosition(orbit, time);
    std::cout << "Orbital position at t=0: (" << position.x << ", " << position.y << ", " << position.z << ")" << std::endl;

    Math::float3 velocity = Math::calculateOrbitVelocity(orbit, time);
    std::cout << "Orbital velocity at t=0: (" << velocity.x << ", " << velocity.y << ", " << velocity.z << ")" << std::endl;

    // Test cel-shading
    std::vector<float> bands = {0.2f, 0.5f, 0.8f, 1.0f};
    float intensity = 0.6f;
    float quantized = Math::quantizeToBands(intensity, bands, 0.1f);
    std::cout << "Cel-shading quantized intensity: " << quantized << std::endl;

    // Test quaternions
    Math::quat q1{0.0f, 0.0f, 0.0f, 1.0f};
    Math::quat q2{0.0f, 0.5f, 0.0f, 0.866f}; // 60 degree rotation around Y
    Math::quat result = Math::q_mul(q1, q2);
    std::cout << "Quaternion multiplication: (" << result.x << ", " << result.y << ", " << result.z << ", " << result.w << ")" << std::endl;

    std::cout << "=== All tests completed ===" << std::endl;
    return 0;
}
