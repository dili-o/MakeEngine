#include "mkpch.h"
#include "Renderer.h"


namespace MK {
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::BeginScene(PerspectiveCamera& camera, Ref<Light> light)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
		m_SceneData->ViewPos = camera.Position;
		m_SceneData->Light = light;
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<Mesh>& mesh, const glm::mat4& modelMatrix )
	{
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		shader->UploadUniformMat4("u_ModelMatrix", modelMatrix);

		mesh->GetVertexArray()->Bind();
		mesh->GetMaterial()->Bind();
		RenderCommand::DrawIndexed(mesh->GetVertexArray());
	}

	void Renderer::SubmitInstance(const Ref<Shader>& shader, const Ref<Mesh>& mesh, int instanceCount)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		shader->UploadUniformFloat3("u_ViewPos", m_SceneData->ViewPos);

		m_SceneData->Light->Bind(shader);

		mesh->GetVertexArray()->Bind();
		mesh->GetMaterial()->Bind();
		RenderCommand::DrawInstance(mesh->GetVertexArray(), instanceCount);
	}
}
