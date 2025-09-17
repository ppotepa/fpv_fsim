# JSON Schema Definitions for FPV Flight Simulator

## Package.json Schema

```json
{
  "$schema": "http://json-schema.org/draft-07/schema#",
  "type": "object",
  "required": ["metadata", "assets"],
  "properties": {
    "metadata": {
      "type": "object",
      "required": ["id", "name", "version"],
      "properties": {
        "id": {
          "type": "string",
          "description": "Unique package identifier"
        },
        "name": {
          "type": "string",
          "description": "Human-readable package name"
        },
        "version": {
          "type": "string",
          "pattern": "^\\d+\\.\\d+\\.\\d+$",
          "description": "Semantic version (major.minor.patch)"
        },
        "description": {
          "type": "string",
          "description": "Package description"
        },
        "author": {
          "type": "string",
          "description": "Package author"
        }
      }
    },
    "dependencies": {
      "type": "array",
      "items": {
        "type": "object",
        "required": ["id", "version"],
        "properties": {
          "id": {
            "type": "string",
            "description": "Dependency package ID"
          },
          "version": {
            "type": "string",
            "description": "Required version"
          },
          "required": {
            "type": "boolean",
            "default": true,
            "description": "Whether dependency is required"
          }
        }
      }
    },
    "assets": {
      "type": "object",
      "properties": {
        "textures": {
          "type": "array",
          "items": { "$ref": "#/definitions/TextureAsset" }
        },
        "materials": {
          "type": "array",
          "items": { "$ref": "#/definitions/MaterialAsset" }
        },
        "meshes": {
          "type": "array", 
          "items": { "$ref": "#/definitions/MeshAsset" }
        },
        "shaders": {
          "type": "array",
          "items": { "$ref": "#/definitions/ShaderAsset" }
        },
        "audio": {
          "type": "array",
          "items": { "$ref": "#/definitions/AudioAsset" }
        },
        "fonts": {
          "type": "array",
          "items": { "$ref": "#/definitions/FontAsset" }
        }
      }
    },
    "scenes": {
      "type": "array",
      "items": { "$ref": "#/definitions/Scene" }
    }
  },
  "definitions": {
    "TextureAsset": {
      "type": "object",
      "required": ["id", "path"],
      "properties": {
        "id": {
          "type": "string",
          "description": "Unique texture identifier"
        },
        "path": {
          "type": "string",
          "description": "Path to texture file relative to package"
        },
        "format": {
          "type": "string",
          "enum": ["rgba8", "rgb8", "dxt1", "dxt5"],
          "default": "rgba8"
        },
        "wrap": {
          "type": "string",
          "enum": ["repeat", "clamp", "mirror"],
          "default": "repeat"
        },
        "filter": {
          "type": "string", 
          "enum": ["linear", "nearest"],
          "default": "linear"
        }
      }
    },
    "MaterialAsset": {
      "type": "object",
      "required": ["id", "shader"],
      "properties": {
        "id": {
          "type": "string"
        },
        "shader": {
          "type": "string",
          "description": "Shader asset ID"
        },
        "properties": {
          "type": "object",
          "additionalProperties": {
            "oneOf": [
              { "type": "string" },
              { "type": "number" },
              { "type": "boolean" },
              { "type": "array" }
            ]
          }
        }
      }
    },
    "MeshAsset": {
      "type": "object",
      "required": ["id", "path"],
      "properties": {
        "id": {
          "type": "string"
        },
        "path": {
          "type": "string"
        },
        "format": {
          "type": "string",
          "enum": ["obj", "fbx", "gltf"]
        }
      }
    },
    "ShaderAsset": {
      "type": "object",
      "required": ["id", "vertex", "fragment"],
      "properties": {
        "id": {
          "type": "string"
        },
        "vertex": {
          "type": "string",
          "description": "Path to vertex shader"
        },
        "fragment": {
          "type": "string",
          "description": "Path to fragment shader"
        },
        "geometry": {
          "type": "string",
          "description": "Optional geometry shader path"
        }
      }
    },
    "AudioAsset": {
      "type": "object",
      "required": ["id", "path"],
      "properties": {
        "id": {
          "type": "string"
        },
        "path": {
          "type": "string"
        },
        "format": {
          "type": "string",
          "enum": ["wav", "ogg", "mp3"]
        },
        "volume": {
          "type": "number",
          "minimum": 0,
          "maximum": 1,
          "default": 1.0
        }
      }
    },
    "FontAsset": {
      "type": "object",
      "required": ["id", "path", "size"],
      "properties": {
        "id": {
          "type": "string"
        },
        "path": {
          "type": "string"
        },
        "size": {
          "type": "integer",
          "minimum": 8,
          "maximum": 128
        }
      }
    },
    "Scene": {
      "type": "object",
      "required": ["id", "name"],
      "properties": {
        "id": {
          "type": "string"
        },
        "name": {
          "type": "string"
        },
        "description": {
          "type": "string"
        },
        "entities": {
          "type": "array",
          "items": { "$ref": "#/definitions/Entity" }
        }
      }
    },
    "Entity": {
      "type": "object",
      "required": ["id", "components"],
      "properties": {
        "id": {
          "type": "string"
        },
        "name": {
          "type": "string"
        },
        "components": {
          "type": "object",
          "properties": {
            "transform": { "$ref": "#/definitions/TransformComponent" },
            "renderable": { "$ref": "#/definitions/RenderableComponent" },
            "physics": { "$ref": "#/definitions/PhysicsComponent" },
            "behavior": { "$ref": "#/definitions/BehaviorComponent" }
          }
        }
      }
    },
    "TransformComponent": {
      "type": "object",
      "properties": {
        "position": {
          "type": "array",
          "items": { "type": "number" },
          "minItems": 3,
          "maxItems": 3,
          "default": [0, 0, 0]
        },
        "rotation": {
          "type": "array",
          "items": { "type": "number" },
          "minItems": 3,
          "maxItems": 3,
          "default": [0, 0, 0]
        },
        "scale": {
          "type": "array",
          "items": { "type": "number" },
          "minItems": 3,
          "maxItems": 3,
          "default": [1, 1, 1]
        }
      }
    },
    "RenderableComponent": {
      "type": "object",
      "required": ["mesh", "material"],
      "properties": {
        "mesh": {
          "type": "string",
          "description": "Mesh asset ID"
        },
        "material": {
          "type": "string",
          "description": "Material asset ID"
        },
        "visible": {
          "type": "boolean",
          "default": true
        }
      }
    },
    "PhysicsComponent": {
      "type": "object",
      "properties": {
        "type": {
          "type": "string",
          "enum": ["static", "dynamic", "kinematic"],
          "default": "dynamic"
        },
        "mass": {
          "type": "number",
          "minimum": 0,
          "default": 1.0
        },
        "friction": {
          "type": "number",
          "minimum": 0,
          "maximum": 1,
          "default": 0.5
        },
        "restitution": {
          "type": "number",
          "minimum": 0,
          "maximum": 1,
          "default": 0.0
        }
      }
    },
    "BehaviorComponent": {
      "type": "object",
      "required": ["type"],
      "properties": {
        "type": {
          "type": "string",
          "description": "Behavior class name"
        },
        "parameters": {
          "type": "object",
          "additionalProperties": {
            "oneOf": [
              { "type": "string" },
              { "type": "number" },
              { "type": "boolean" },
              { "type": "array" }
            ]
          }
        }
      }
    }
  }
}
```

## Configuration File Schemas

### Physics Configuration (physics_config.json)
```json
{
  "$schema": "http://json-schema.org/draft-07/schema#",
  "type": "object",
  "properties": {
    "simulation": {
      "type": "object",
      "properties": {
        "fixedTimestep": { "type": "number", "default": 0.016667 },
        "maxSubSteps": { "type": "integer", "default": 10 },
        "gravity": {
          "type": "array",
          "items": { "type": "number" },
          "minItems": 3,
          "maxItems": 3,
          "default": [0, -9.81, 0]
        }
      }
    },
    "world": {
      "type": "object", 
      "properties": {
        "broadphaseType": {
          "type": "string",
          "enum": ["dbvt", "simple"],
          "default": "dbvt"
        },
        "collisionMargin": { "type": "number", "default": 0.04 }
      }
    },
    "wind": {
      "type": "object",
      "properties": {
        "enabled": { "type": "boolean", "default": false },
        "direction": {
          "type": "array",
          "items": { "type": "number" },
          "minItems": 3,
          "maxItems": 3,
          "default": [1, 0, 0]
        },
        "strength": { "type": "number", "default": 0.0 }
      }
    }
  }
}
```

### Render Configuration (render_config.json)
```json
{
  "$schema": "http://json-schema.org/draft-07/schema#",
  "type": "object",
  "properties": {
    "display": {
      "type": "object",
      "properties": {
        "title": { "type": "string", "default": "FPV Flight Simulator" },
        "width": { "type": "integer", "default": 1920 },
        "height": { "type": "integer", "default": 1080 },
        "fullscreen": { "type": "boolean", "default": false },
        "vsync": { "type": "boolean", "default": true }
      }
    },
    "camera": {
      "type": "object",
      "properties": {
        "fov": { "type": "number", "default": 75.0 },
        "nearPlane": { "type": "number", "default": 0.1 },
        "farPlane": { "type": "number", "default": 1000.0 },
        "position": {
          "type": "array",
          "items": { "type": "number" },
          "minItems": 3,
          "maxItems": 3,
          "default": [0, 10, 20]
        }
      }
    },
    "quality": {
      "type": "object",
      "properties": {
        "shadows": { "type": "boolean", "default": true },
        "antialiasing": { "type": "boolean", "default": true },
        "anisotropicFiltering": { "type": "integer", "default": 16 }
      }
    }
  }
}
```

### Input Configuration (input_config.json)
```json
{
  "$schema": "http://json-schema.org/draft-07/schema#",
  "type": "object",
  "properties": {
    "keyBindings": {
      "type": "object",
      "additionalProperties": {
        "type": "string"
      }
    },
    "mouseBindings": {
      "type": "object",
      "properties": {
        "sensitivity": { "type": "number", "default": 1.0 },
        "invertY": { "type": "boolean", "default": false }
      }
    },
    "gamepadBindings": {
      "type": "object",
      "properties": {
        "deadzone": { "type": "number", "default": 0.1 }
      }
    }
  }
}
```
