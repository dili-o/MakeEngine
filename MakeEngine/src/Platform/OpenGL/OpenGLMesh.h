#pragma once
#include "MakeEngine/Renderer/Mesh.h"

namespace MK
{
	class OpenGLMesh : public Mesh
	{
	public:
		OpenGLMesh() = default;
		virtual ~OpenGLMesh() = default;
		virtual void CreateCube() override;
		virtual void CreateTexturedCube() override;
		virtual void CreateInstance(float* translations, unsigned int instanceCount) override;

		inline virtual const Ref<VertexArray>& GetVertexArray() const override { return m_VertexArray; }
	};
}