#pragma once

#include "RenderCommand.h"
#include "PerspectiveCamera.h"
#include "Shader.h"
#include "Mesh.h"

namespace MK {

	class Renderer
	{
	public:
		static void Init();

		static void BeginScene(PerspectiveCamera& camera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const Ref<Mesh>& mesh, const glm::mat4& modelMatrix = glm::mat4(1.0f));
		static void Renderer::SubmitInstance(const Ref<Shader>& shader, const Ref<Mesh>& mesh, int instanceCount);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};


}