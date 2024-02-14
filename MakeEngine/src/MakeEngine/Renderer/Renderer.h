#pragma once

#include "RenderCommand.h"
#include "PerspectiveCamera.h"
#include "Shader.h"
#include "Mesh.h"
#include "Light.h"

namespace MK {
	struct LightData{
		std::vector<Ref<PointLight>> PointLights;
	};
	class Renderer
	{
	public:
		static void Init();

		static void BeginScene(PerspectiveCamera& camera, LightData* lightData);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const Ref<Mesh>& mesh, const glm::mat4& modelMatrix = glm::mat4(1.0f));
		static void Renderer::SubmitInstance(const Ref<Shader>& shader, const Ref<Mesh>& mesh, int instanceCount);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
			glm::vec3 ViewPos;
			Ref<Light> Light;
		};

		static LightData* m_LightData;
		static SceneData* m_SceneData;
	};
}