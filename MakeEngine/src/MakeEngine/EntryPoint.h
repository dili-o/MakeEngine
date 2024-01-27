#pragma once

#ifdef MK_PLATFORM_WINDOWS

extern MK::Application* MK::CreateApplication();


int main(int argc, char** argv)
{
	MK::Log::Init();
	MK_CORE_WARN("Initialised Log!");
	MK_INFO("Initialised Log!");

	MK::Application* app = MK::CreateApplication();
	app->Run();
	delete app;
}

#endif