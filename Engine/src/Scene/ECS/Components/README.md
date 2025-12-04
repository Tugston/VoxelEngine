# Components

This folder contains all components that are currently available within the engine. Each component is designed to be agnostic within each GameObject.
They are very lightweight and **decoupled** from any third party engine reliant libraries (IE, all transforms and other maths are custom built).
Basically, it just ensures there are absolutely zero issues when adding components to your GameObjects; the engine handles all the conversion
internally. Some of the shared resource types are pointers in the components. This is simply due to the vao, ebo, and vbo being move only which
is also implemented in the Mesh. The ecs storage of components is contigous and most components values are, but some just can't.

## Extendability
All components *should* be freely customizable, though you may have to change some of the systems processes. Like mentioned in the overall ECS docs,
completely new components may be created as well if you do not wish to use the GameObject structure. Just make sure the namespaces are all appropraite.

