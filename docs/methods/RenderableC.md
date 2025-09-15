# RenderableC.h

## Struct RenderableC

### Constructors

- `RenderableC(std::string mesh = "", std::string material = "", bool visible = true)`

  **Summary:** Constructor for the renderable component with default empty mesh/material IDs and visible flag.

### Members

- `std::string meshId;`

  **Summary:** Identifier for the mesh asset used for rendering.

- `std::string materialId;`

  **Summary:** Identifier for the material asset used for rendering.

- `bool isVisible;`

  **Summary:** Boolean flag indicating whether the entity should be rendered.
