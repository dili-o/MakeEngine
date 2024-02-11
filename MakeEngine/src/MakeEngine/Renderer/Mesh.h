#pragma once
#include "VertexArray.h"
#include "Material.h"


namespace MK
{
	class Mesh
	{
	public:
		virtual ~Mesh() = default;
		virtual void CreateCube() = 0;
		virtual void CreateTexturedCube() = 0;
		virtual void CreateInstance(float* translations, unsigned int instanceCount) = 0;

		virtual void SetVertexArray(const Ref<VertexArray>& vertexArray) { m_VertexArray = vertexArray; }
		virtual void SetMaterial(const Ref<Material>& material) { m_Material = material; }

		virtual const Ref<VertexArray>& GetVertexArray() const = 0;
		virtual const uint32_t			GetInstanceCount() { return m_InstanceCount; }
		virtual const Ref<Material>&    GetMaterial() { return m_Material; }
	public:
		static Ref<Mesh> Create();
	protected:
		Ref<VertexArray> m_VertexArray;
		Ref<Material> m_Material;
		uint32_t m_InstanceCount = 1;
	};
}