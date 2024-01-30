#pragma once

#include "Core.h"

#include "Window.h"
#include "MakeEngine/Events/ApplicationEvent.h"

#include "MakeEngine/Core/Timestep.h"

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
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
		
	private:
		static Application* s_Instance;
	};

	// To be defined in the client i.e Sandbox
	Application* CreateApplication();
}


