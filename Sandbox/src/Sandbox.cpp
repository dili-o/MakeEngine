#include <MakeEngine.h>

#include "imgui/imgui.h"


class ExampleLayer : public MK::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera({ 0.0f, 1.f, 3.f })
	{
		// Create a vertex array
		m_VertexArray.reset(MK::VertexArray::Create());
		// Square Vertices
		float vertices[] = {
			-0.5f,  0.5f, 0.f, 0.8f, 0.8f, 0.2f, //1
			 0.5f, -0.5f, 0.f, 0.2f, 0.8f, 0.2f, //2
			-0.5f, -0.5f, 0.f, 0.8f, 0.2f, 0.8f, //3
			 0.5f,  0.5f, 0.f, 0.2f, 0.8f, 0.8f  //4
		};

		float cubeVertices[] = {
			// Front face
			-0.5f, -0.5f, 0.5f, 0.8f, 0.8f, 0.2f,
			 0.5f, -0.5f, 0.5f, 0.2f, 0.8f, 0.2f,
			 0.5f,  0.5f, 0.5f, 0.8f, 0.2f, 0.8f,
			-0.5f,  0.5f, 0.5f, 0.2f, 0.8f, 0.8f,

			// Back face
			-0.5f, -0.5f, -0.5f, 0.8f, 0.8f, 0.2f,
			 0.5f, -0.5f, -0.5f, 0.2f, 0.8f, 0.2f,
			 0.5f,  0.5f, -0.5f, 0.8f, 0.2f, 0.8f,
			-0.5f,  0.5f, -0.5f, 0.2f, 0.8f, 0.8f,

			// Left face
			-0.5f, -0.5f, -0.5f, 0.8f, 0.8f, 0.2f,
			-0.5f,  0.5f, -0.5f, 0.2f, 0.8f, 0.2f,
			-0.5f,  0.5f,  0.5f, 0.8f, 0.2f, 0.8f,
			-0.5f, -0.5f,  0.5f, 0.2f, 0.8f, 0.8f,

			// Right face
			0.5f, -0.5f, -0.5f, 0.8f, 0.8f, 0.2f,
			0.5f,  0.5f, -0.5f, 0.2f, 0.8f, 0.2f,
			0.5f,  0.5f,  0.5f, 0.8f, 0.2f, 0.8f,
			0.5f, -0.5f,  0.5f, 0.2f, 0.8f, 0.8f,

			// Bottom face
			-0.5f, -0.5f, -0.5f, 0.8f, 0.8f, 0.2f,
			 0.5f, -0.5f, -0.5f, 0.2f, 0.8f, 0.2f,
			 0.5f, -0.5f,  0.5f, 0.8f, 0.2f, 0.8f,
			-0.5f, -0.5f,  0.5f, 0.2f, 0.8f, 0.8f,

			// Top face
			-0.5f, 0.5f, -0.5f, 0.8f, 0.8f, 0.2f,
			 0.5f, 0.5f, -0.5f, 0.2f, 0.8f, 0.2f,
			 0.5f, 0.5f,  0.5f, 0.8f, 0.2f, 0.8f,
			-0.5f, 0.5f,  0.5f, 0.2f, 0.8f, 0.8f
		};
		// Create a vertex buffer
		std::shared_ptr<MK::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(MK::VertexBuffer::Create(cubeVertices, sizeof(cubeVertices)));
		// Create the vertex buffer layout
		MK::BufferLayout layout = {
			{ MK::ShaderDataType::Float3, "a_Position" },
			{ MK::ShaderDataType::Float3, "a_Color" }
		};
		// Set the vertex buffer layout and add it to vertex array
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);
		// Create the index buffer
		uint32_t indices[6] = { 0, 1, 2, 0, 1, 3 };
		uint32_t cubeIndicies[] =
		{
			0, 1, 2, 2, 3, 0, // Front face
			4, 5, 6, 6, 7, 4, // Back face
			8, 9, 10, 10, 11, 8, // Left face
			12, 13, 14, 14, 15, 12, // Right face
			16, 17, 18, 18, 19, 16, // Bottom face
			20, 21, 22, 22, 23, 20 // Top face
		};
		std::shared_ptr<MK::IndexBuffer> indexBuffer;
		indexBuffer.reset(MK::IndexBuffer::Create(cubeIndicies, sizeof(cubeIndicies) / sizeof(uint32_t)));
		// Add the index buffer to the vertex array
		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec3 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_ModelMatrix;

			out vec3 v_Position;
			out vec3 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_ModelMatrix * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			out vec4 color;

			in vec3 v_Color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(v_Color, 1.0);
			}
		)";

		m_Shader.reset(new MK::Shader(vertexSrc, fragmentSrc));
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
		glm::mat4 model = glm::scale(glm::mat4(1.f), glm::vec3(10.f, 0.2f, 10.0f));
		MK::Renderer::Submit(m_Shader, m_VertexArray, model);

		model = glm::mat4(1.f);
		MK::Renderer::Submit(m_Shader, m_VertexArray, model);

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
	std::shared_ptr<MK::Shader> m_Shader;
	std::shared_ptr<MK::VertexArray> m_VertexArray;

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