# Components

This folder contains all components that are currently available within the engine. Each component is designed to be agnostic within each GameObject.
They are very lightweight and **decoupled** from any third party engine reliant libraries (IE, all transforms and other maths are custom built).
Basically, it just ensures there are absolutely zero issues when adding components to your GameObjects; the engine handles all the conversions internally.

## Extendability
All components *should* be freely customizable, though you may have to change some of the systems processes. Like mentioned in the overall ECS docs,
completely new components may be created as well if you do not wish to use the GameObject structure. Just make sure the namespaces are all appropraite.

