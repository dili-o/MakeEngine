#include <MakeEngine.h>

class ExampleLayer : public MK::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		//MK_INFO("ExampleLayer::Update");
	}

	void OnEvent(MK::Event& event) override
	{
		//MK_TRACE("{0}", event);
		if (event.GetEventType() == MK::EventType::KeyPressed)
		{
			MK::KeyPressedEvent& e = (MK::KeyPressedEvent&)event;
			if (e.GetKeyCode() == MK_KEY_TAB)
				MK_TRACE("Tab key is pressed (event)!");
			MK_TRACE("{0}", (char)e.GetKeyCode());
		}
	}

};

class Sandbox : public MK::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new MK::ImGuiLayer());
	}
	~Sandbox()
	{

	}
};

MK::Application* MK::CreateApplication()
{
	return new Sandbox();
}