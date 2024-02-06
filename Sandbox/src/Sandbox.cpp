#include <MakeEngine.h>

#include "imgui/imgui.h"
//#include <Platform/OpenGL/OpenGLShader.h>


class ExampleLayer : public MK::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera({ 0.0f, 1.f, 3.f })
	{
		
		m_CubeMesh = MK::Mesh::Create();
		m_CubeMesh->CreateTexturedCube();

		m_Shader.reset(MK::Shader::Create("assets/shaders/Texture.vs", "assets/shaders/Texture.fs"));

		m_Texture = MK::Texture2D::Create("assets/textures/stonebrick.png");

		
		//std::dynamic_pointer_cast<MK::OpenGLShader>(m_Shader)->Bind();
		//std::dynamic_pointer_cast<MK::OpenGLShader>(m_Shader)->UploadUniformInt("u_Texture", 0);
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


		MK::Renderer::BeginScene(m_Camera);

		// Cube
		m_Texture->Bind();
		glm::mat4 model = glm::mat4(1.f);
		//model = glm::translate(model, glm::vec3(2.0f, 0.0f, 2.0f));
		MK::Renderer::Submit(m_Shader, m_CubeMesh->GetVertexArray(), model);

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

private:
	MK::Ref<MK::Shader> m_Shader;
	MK::Ref<MK::Mesh> m_CubeMesh;
	MK::Ref<MK::Texture2D> m_Texture;

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