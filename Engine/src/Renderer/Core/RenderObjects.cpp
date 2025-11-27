#include "egpch.h"
#include "RenderObjects.h"

//ENGN
#include "Renderer.h"

namespace Engine::Renderer
{
	//***********
	//MESH OBJECT
	//***********

	void MeshObject::SubmitToRender(Renderer* renderer) const
	{
		renderer->RegisterOpaqueObject(std::make_shared<OpaquePackets>(static_cast<const Engine::Renderer::MeshObject*>(this)));
	}

	void MeshObject::Render() const
	{
	}
	
	//***********
	//MESH OBJECT
	//***********


	//********************
	//Instance Mesh Object
	//********************

	void InstanceMeshObject::SubmitToRender(Renderer* renderer) const
	{
		renderer->RegisterOpaqueObject(std::make_shared<OpaquePackets>(static_cast<const Engine::Renderer::InstanceMeshObject*>(this)));
	}

	void InstanceMeshObject::Render() const
	{

	}
	//********************
	//Instance Mesh Object
	//********************

}
