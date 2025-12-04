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
		renderer->RegisterOpaqueObject(std::make_unique<OpaquePackets>(static_cast<const Engine::Renderer::MeshObject*>(this)));
	}

	void MeshObject::Render() const
	{
		material->shader->Use();
		material->shader->SetUniformMat4("uModel", transform);

		mesh->vao.Bind();
		mesh->vbo.Bind();
		mesh->ebo.Bind();

		glDrawElements(mesh->primitiveMode, mesh->indexCount, GL_UNSIGNED_INT, 0);
	}
	
	//***********
	//MESH OBJECT
	//***********


	//********************
	//Instance Mesh Object
	//********************

	void InstanceMeshObject::SubmitToRender(Renderer* renderer) const
	{
		renderer->RegisterOpaqueObject(std::make_unique<OpaquePackets>(static_cast<const Engine::Renderer::InstanceMeshObject*>(this)));
	}

	void InstanceMeshObject::Render() const
	{

	}
	//********************
	//Instance Mesh Object
	//********************

}
