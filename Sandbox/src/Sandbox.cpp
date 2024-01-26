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
		MK_TRACE("{0}", event);
	}

};

class Sandbox : public MK::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
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