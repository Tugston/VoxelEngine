#pragma once

//ENGN
#include "SharedResources/GenericResources/Mesh.h"

//currently transitioning the primitive shapes to make instances instead of completely new meshes
//just trying to get the ecs working with the render objects first

namespace Engine::Utility
{
	Mesh CreateQuad();
}
