#pragma once

#include "MakeEngine/Renderer/RendererAPI.h"

namespace MK {

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
		virtual void DrawInstance(const Ref<VertexArray>& vertexArray, int instanceCount) override;
	};


}