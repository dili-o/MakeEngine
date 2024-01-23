#include <MakeEngine.h>


class Sandbox : public MK::Application
{
public:
	Sandbox()
	{

	}
	~Sandbox()
	{

	}
};

MK::Application* MK::CreateApplication()
{
	return new Sandbox();
}