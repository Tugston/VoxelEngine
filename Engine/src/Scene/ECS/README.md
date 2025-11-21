# ECS

The Entity Component System is fully custom built and includes two methods of utilization. You may work purely with GameObjects and design system
level components and go the more object oriented route, **or** you may freely extend the ECS system to build your own data oriented components, entities
*(which are just uintegers)*, and systems. While full experimentation has not been conducted as of now *(11/20/2025)*, because I am still building the systems,
the plan is to allow both systems run in conjunction with each other. Reason being is the GameObjects class is just a convoluted, yet simple wrapper
over the Registry that abstracts ECS functionality into an object state.

You can find out more information covering each part of the ECS in the READMEs contained in the respective subsystem folders

## Registry
The registry handles all the creation, deletion, and communications between the Entities, Components, and Systems. It is build upon a sparse set, which
drastically increases storage, but brings insertion, deletion, random access all down to o(1). For pure iteration (determining if a entity contains a
component) the time complexity should be o(k).

*For example: o(n) would be checking if the entities themselves have a component, so without a sparse set you loop over the entire pool size of entities.
With o(k) complexity you only have to loop over active k items (components in this case)*

