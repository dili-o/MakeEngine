#include <MakeEngine.h>
#include <glm/gtc/type_ptr.hpp>


#include "imgui/imgui.h"
//#include <Platform/OpenGL/OpenGLShader.h>


class ExampleLayer : public MK::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera({ 0.0f, 1.f, 3.f })
	{
		int amount = 10000;
		glm::mat4* positions = new glm::mat4[amount];
		for (int row = 0; row < 100; row++)
		{
			int index = 100 * row;
			for (int col = 0; col < 100; col++)
				positions[index + col] = glm::translate(glm::mat4(1.f), glm::vec3(row, 0.f, col));
		}
		mat4ArrayToFloatArray(positions, amount, positionsArray);
		// Meshes
		m_CubeMesh = MK::Mesh::Create();
		m_CubeMesh->CreateTexturedCube();
		//m_CubeMesh->CreateInstance(positionsArray, amount);

		m_LightingMesh = MK::Mesh::Create();
		m_LightingMesh->CreateCube();
		m_LightingMesh->CreateInstance(positionsArray, amount);

		// Shaders
		m_Shader.reset(MK::Shader::Create("assets/shaders/Texture.vs", "assets/shaders/Texture.fs"));
		//m_InstanceShader.reset(MK::Shader::Create("assets/shaders/TextureInstance.vs", "assets/shaders/Texture.fs"));
		m_LightingShader.reset(MK::Shader::Create("assets/shaders/Mesh.vs", "assets/shaders/Mesh.fs"));

		// Textures
		m_Texture = MK::Texture2D::Create("assets/textures/stonebrick.png");
		m_SpecTexture = MK::Texture2D::Create("assets/textures/stonebrick_spec.png");
		m_DefaultDiffuse = MK::Texture2D::Create("assets/textures/default_diff.png");

		// Materials
		m_Material = MK::Material::Create(m_Shader, m_DefaultDiffuse);
		m_CubeMesh->SetMaterial(m_Material);
		m_LightingMaterial = MK::Material::Create(m_LightingShader, m_Texture, m_SpecTexture, 32.f);
		m_LightingMesh->SetMaterial(m_LightingMaterial);

		m_Light = MK::Light::Create(glm::vec3(0.1f), glm::vec3(0.7f), glm::vec3(1.0f), glm::vec3(50.f, 10.f, 50.f));
	}

	void OnUpdate(MK::Timestep ts) override
	{
		MK::Camera_Movement direction = MK::Camera_Movement::NO_DIRECTION;
		if (MK::Input::IsKeyPressed(MK_KEY_A))
			direction = MK::Camera_Movement::LEFT;
		if (MK::Input::IsKeyPressed(MK_KEY_D))
			direction = MK::Camera_Movement::RIGHT;
		if (MK::Input::IsKeyPressed(MK_KEY_W))
			direction = MK::Camera_Movement::FORWARD;
		if (MK::Input::IsKeyPressed(MK_KEY_S))
			direction = MK::Camera_Movement::BACKWARD;
		if (MK::Input::IsKeyPressed(MK_KEY_SPACE))
			direction = MK::Camera_Movement::UP;
		if (MK::Input::IsKeyPressed(MK_KEY_LEFT_CONTROL))
			direction = MK::Camera_Movement::DOWN;

		m_Camera.ProcessKeyboard(direction, ts);

		MK::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		MK::RenderCommand::Clear();


		MK::Renderer::BeginScene(m_Camera, m_Light);

		// Cube
		glm::mat4 model = glm::mat4(1.f);
		model = glm::translate(model, glm::vec3(50.f, 10.f, 50.f));
		model = glm::scale(model, glm::vec3(0.2f));
		MK::Renderer::Submit(m_Shader, m_CubeMesh, model);

		//MK::Renderer::SubmitInstance(m_InstanceShader, m_CubeMesh, m_CubeMesh->GetInstanceCount());
		MK::Renderer::SubmitInstance(m_LightingShader, m_LightingMesh, m_LightingMesh->GetInstanceCount());

		MK::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{

	}

	void OnEvent(MK::Event& event) override
	{
		MK::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MK::MouseMovedEvent>(MK_BIND_EVENT_FN(ExampleLayer::OnMouseMovedEvent));
		dispatcher.Dispatch<MK::MouseScrolledEvent>(MK_BIND_EVENT_FN(ExampleLayer::OnMouseScrolledEvent));
	}

	bool OnMouseMovedEvent(MK::MouseMovedEvent& event)
	{
		float fXPos = static_cast<float>(event.GetX());
		float fYPos = static_cast<float>(event.GetY());

		if (FirstMouse)
		{
			LastX = fXPos;
			LastY = static_cast<float>(fYPos);
			FirstMouse = false;
		}

		float xoffset = fXPos - LastX;
		float yoffset = LastY - fYPos; // reversed: y ranges bottom to top
		LastX = fXPos;
		LastY = fYPos;

		m_Camera.ProcessMouseMovement(xoffset, yoffset);

		return true;
	}

	bool OnMouseScrolledEvent(MK::MouseScrolledEvent& event)
	{
		MK_TRACE("Mouse YScroll: {0}", event.GetYOffset());
		m_Camera.ProcessMouseScroll(event.GetYOffset());
		return true;
	}

	void mat4ArrayToFloatArray(const glm::mat4* matrices, size_t numMatrices, float* floatArray) {
		for (size_t i = 0; i < numMatrices; ++i) {
			const float* matData = glm::value_ptr(matrices[i]);

			// Copy the elements of the mat4 into the float array
			for (size_t j = 0; j < 16; ++j) {
				floatArray[i * 16 + j] = matData[j];
			}
		}
	}

private:
	MK::Ref<MK::Shader> m_Shader;
	MK::Ref<MK::Shader> m_InstanceShader;
	MK::Ref<MK::Shader> m_LightingShader;

	MK::Ref<MK::Mesh> m_CubeMesh;
	MK::Ref<MK::Mesh> m_LightingMesh;

	MK::Ref<MK::Texture2D> m_Texture;
	MK::Ref<MK::Texture2D> m_SpecTexture;
	MK::Ref<MK::Texture2D> m_DefaultDiffuse;

	MK::Ref<MK::Material> m_Material;
	MK::Ref<MK::Material> m_LightingMaterial;

	MK::Ref<MK::Light> m_Light;

	float positionsArray[10000 * 16];

	bool FirstMouse = true;
	float LastX = 1280.f / 2.f;
	float LastY = 780.f / 2.f;
	


	MK::PerspectiveCamera m_Camera;
};

class Sandbox : public MK::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox()
	{

	}
};

MK::Application* MK::CreateApplication()
{
	return new Sandbox();
}