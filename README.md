![Static Badge](https://img.shields.io/badge/Version-0.0.1-green)
![Static Badge](https://img.shields.io/badge/License-GPL3-blue)

# Voxel Engine

Welcome! This is my first real attempt at making a voxel based game engine. The project is designed for experimental purposes and side projects only, and 
I highly recommend not utilizing this for any serious applications. However, feel free to do so as you wish its just a suggestion!

For the full documentation, please checkout the documentation folder [here](https://github.com/Tugston/VoxelEngine/tree/main/Documentation).


## Features
- [x] Fully custom Entity Component System with underlying sparse set
- [x] Levels *(with full saving / loading coming soon)*
- [ ] Simple editor with custom scripting


## Setup & Installation
All library dependencies are included in the repo, and PreMake is utilized to setup the project. The only hiccup is the absence of CMake.
The **GenerateProject.bat** sets up the entire project accordingly. Get started by cloning, and running the batch file.

```sh
git clone https://github.com/Tugston/VoxelEngine.git
```
then run command in terminal at root project directory
```
/GenerateProject
```

## Usage
To have the project working, as of now *(11/20/2025)* you **must**

1. Delete Game project that was downloaded with the project *(or download the gameless branch if you wish)*
	2. rerun the bat file in the Setup & Installation step to get a fresh game project
	2. add Game.cpp file in a folder labeled "EngineExtensions"

1. Add ```#include <Core/EntryPoint.h>``` and ```#include<Engine.h>``` to the file
	2.  EntryPoint contains the main function, so it **must** be included exactly once in the Game project
	2.	Engine.h includes the entire public API for the engine and can be added everywhere

1. Create your GameClass *(call it whatever you want)* and publicly inherit from Application

1. Copy and paste this in the Game.cpp outside of the class and any namespaces
```
Application* Engine::CreateApplication()
{
	return new YourNamespace::YourClassName();
}
```

and thats it! The engine is fully ready to be used. From here you can add GameObjects and everything to your Game. There are going to be frequent updates
so things will change quite a bit. I will try to keep this README updated as changes progress. There are currently a lot of systems just needing to be
fit together at this current moment, but they should come together eventually.


Anyways, once this engine becomes a bit more robust and people may stumble upon it, I will add a means to send example projects of stuff you may make.
Would be cool seeing other peoples creations with my project. Until then, just feel free to play around with it as I progress. **Contributions may open up
in the future if this project grows** but as of now I am not accepting any.

---

*This Voxel Engine is open-sourced software licensed under the [GPL3](https://opensource.org/license/gpl-3-0)*
