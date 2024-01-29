#include "mkpch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace MK {

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glEnable(GL_DEPTH_TEST);
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

}