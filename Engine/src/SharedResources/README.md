# Shared Resources

This folder is just a dump of internal container structs that are useful in allowing several systems to communicate data. Most commonly used with the
Renderer and ECS, but can work with pretty much anything. Although a couple values may heavily resemble ECS components, these helpers have absolutely zero
coorelation with the ECS.


## Generaic Resources

Generic Resources are simply anything generic. What do I mean by this, well I'm not quite sure. I could not think of a solid name for this folder, but it
is utilized as a dump for random helpers like Mesh, Materials, Shaders, etc. This folder will most likely always be a mess, so there is no use trying to 
organize or fix this. The entire SharedResources directory is just a mess, but like I said its only for helpers.


## Primitive Shapes

Primitive Shapes is for predefined meshes that are available to use within the engine. Instead of having to make quads and stuff over and over, I figured
why not just define the basic shapes manually a single time and throw them somewhere. Each shape has its own header and cpp, because I would prefer this
to be very modular. Although it leads to more files overall, there is absolutely zero reason why any extra code pertaining to other shapes is needed. The
shared resources folder will also not be included in Engine.h and will serve as being completely optional helpers for the game. So just another reason why
it should be as modular as possible
