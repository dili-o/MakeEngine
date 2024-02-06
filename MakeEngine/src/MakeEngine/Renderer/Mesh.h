#pragma once
#include "VertexArray.h"
#include "MakeEngine/Core.h"


namespace MK
{
	class Mesh
	{
	public:
		virtual ~Mesh() = default;
		virtual void CreateTriangle() = 0;
		virtual void CreateQuad() = 0;
		virtual void CreateCube() = 0;
		virtual void CreateTexturedCube() = 0;
		virtual const Ref<VertexArray>& GetVertexArray() const = 0;
		virtual void SetVertexArray(const Ref<VertexArray>& vertexArray) { m_VertexArray = vertexArray; }
	public:
		static Ref<Mesh> Create();
	protected:
		Ref<VertexArray> m_VertexArray;
	};
}