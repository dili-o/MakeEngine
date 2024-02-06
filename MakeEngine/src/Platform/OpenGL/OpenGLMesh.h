#pragma once
#include "MakeEngine/Renderer/Mesh.h"

namespace MK
{
	class OpenGLMesh : public Mesh
	{
	public:
		OpenGLMesh() = default;
		virtual ~OpenGLMesh() = default;
		virtual void CreateTriangle() override;
		virtual void CreateQuad() override;
		virtual void CreateCube() override;
		virtual void CreateTexturedCube() override;
		inline virtual const Ref<VertexArray>& GetVertexArray() const override { return m_VertexArray; }
	};
}