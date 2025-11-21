# Scene

The scene is self explanatory, it basically just a container for all the game specific implementations. Engine related features required in scenes *(like the
editor camera)* are controlled in the application itself. Personally I feel its right to seperate the concerns, so the scene can just deal with final production
game data, as stated. The Scene object itself **is nothing more than a temporary container** it is purely responsible for containerizing Objects or Entities
*(see ECS README)* and adding an abstraction layer for the internal layers.

## Scene Manager
This is where all the scene management occurs, again self explanatory. As of today *(11/20/2025)* the scene manager is just a header file with a base class
implementation. Eventually this should be a singleton that will handle changing scenes, saving scenes, loading scenes, and a static access for the current
loaded scene. **This will alleviate the current temporary structure of the ECS needing a scene reference passed to it.**

## ECS - Notice
I'm storing the ECS here, because it feels very tightly coupled with the Scene. A Scene is just an encapsulation of a large chunk of data, and the ECS
is purely a large chunk of data, so it goes hand in hand. *Checkout ECS README for more details.*
