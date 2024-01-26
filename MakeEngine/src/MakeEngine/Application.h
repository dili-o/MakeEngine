#pragma once

#include "Core.h"
#include "MakeEngine/Events/ApplicationEvent.h"
#include "MakeEngine/LayerStack.h"
#include "Window.h"


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
		bool m_Running = true;
		LayerStack m_LayerStack;

		static Application* s_Instance;
	};

	// To be defined in the client i.e Sandbox
	Application* CreateApplication();
}


