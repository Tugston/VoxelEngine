#pragma once

//VNDR
#include <glm/glm.hpp>

//ENGN
#include "SharedResources/GenericResources/Mesh.h"
#include "SharedResources/GenericResources/Material.h"

//STND
#include <memory>

namespace Engine::Renderer
{
	class Renderer;

	struct RenderObject {
		RenderObject(unsigned int layer) : layer(layer) {};
		RenderObject(glm::mat4 transform, unsigned int layer): transform(transform), layer(layer) {};
		glm::mat4 transform{};
		const unsigned int layer;

	private:
		virtual void SubmitToRender(Renderer* renderer) const = 0;
		virtual void Render() const = 0;

		friend class Renderer;
	};

	struct MeshObject : public RenderObject
	{
		MeshObject(unsigned int layer) : RenderObject(layer) {};
		MeshObject(glm::mat4 transform, std::shared_ptr<Utility::Mesh> mesh, std::shared_ptr<Utility::Material> material, unsigned int layer) :
		RenderObject(transform, layer), mesh(mesh), material(material) {};
		const std::weak_ptr<Utility::Mesh> mesh;
		const std::weak_ptr<Utility::Material> material;
		
	private:
		virtual void SubmitToRender(Renderer* renderer) const override;
		virtual void Render() const override;

		friend class Renderer;
	};

	struct InstanceMeshObject : public RenderObject
	{
		InstanceMeshObject() : RenderObject(0) {};

		//each instance should only have a single actual mesh
		//the instancedMesh stores the 
		static const std::weak_ptr<Utility::InstancedMesh> mesh;

		const std::weak_ptr<Utility::Material> material;

	private:
		virtual void SubmitToRender(Renderer* renderer) const override;
		virtual void Render() const override;

		friend class Renderer;
	};
}
