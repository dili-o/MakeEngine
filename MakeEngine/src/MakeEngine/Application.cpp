#include "mkpch.h"
#include "Application.h"

#include "MakeEngine/Log.h"
#include <glad/glad.h>

#include "Input.h"

namespace MK {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		MK_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(MK_BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		// Create a vertex array
		m_VertexArray.reset(VertexArray::Create());
		// Square Vertices
		float vertices[] = {
			-0.5f,  0.5f, 0.f, 1.0f, 0.0f, 0.0f, //1
			 0.5f, -0.5f, 0.f, 0.0f, 1.0f, 0.0f, //2
			-0.5f, -0.5f, 0.f, 0.0f, 0.0f, 1.0f, //3
			 0.5f,  0.5f, 0.f, 0.0f, 1.0f, 1.0f  //4
		};
		// Create a vertex buffer
		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		// Create the vertex buffer layout
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float3, "a_Color" }
		};
		// Set the vertex buffer layout and add it to vertex array
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);
		// Create the index buffer
		uint32_t indices[6] = { 0, 1, 2, 0, 1, 3 };
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		// Add the index buffer to the vertex array
		m_VertexArray->SetIndexBuffer(indexBuffer);
		
		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec3 a_Color;

			out vec3 v_Position;
			out vec3 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);	
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

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
	}
	

	Application::~Application()
	{

	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(MK_BIND_EVENT_FN(Application::OnWindowClose));

		// iterate over the stack backwards to handle events
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();
			m_VertexArray->Bind();
			glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();



			m_Window->OnUpdate();
		};
	}


}

