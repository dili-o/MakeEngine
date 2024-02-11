#include "mkpch.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"


namespace MK {
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::BeginScene(PerspectiveCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<Mesh>& mesh, const glm::mat4& modelMatrix )
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ModelMatrix", modelMatrix);

		mesh->GetVertexArray()->Bind();
		mesh->GetMaterial()->Bind();
		RenderCommand::DrawIndexed(mesh->GetVertexArray());
	}

	void Renderer::SubmitInstance(const Ref<Shader>& shader, const Ref<Mesh>& mesh, int instanceCount)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);

		mesh->GetVertexArray()->Bind();
		mesh->GetMaterial()->Bind();
		RenderCommand::DrawInstance(mesh->GetVertexArray(), instanceCount);
	}
}
