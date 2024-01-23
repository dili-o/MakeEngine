#pragma once

#include "Core.h"

namespace MK {
	class MK_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in the client i.e Sandbox
	Application* CreateApplication();
}


