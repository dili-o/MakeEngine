#pragma once

#include "Core.h"

#include "Window.h"
#include "MakeEngine/Events/ApplicationEvent.h"

#include "MakeEngine/Renderer/Shader.h"
#include "MakeEngine/Renderer/Buffer.h"
#include "MakeEngine/Renderer/VertexArray.h"

#include "MakeEngine/Renderer/PerspectiveCamera.h"

#include "MakeEngine/LayerStack.h"
#include "MakeEngine/ImGui/ImGuiLayer.h"


namespace MK {
	class MK_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		PerspectiveCamera m_Camera;
	private:
		static Application* s_Instance;
	};

	// To be defined in the client i.e Sandbox
	Application* CreateApplication();
}


