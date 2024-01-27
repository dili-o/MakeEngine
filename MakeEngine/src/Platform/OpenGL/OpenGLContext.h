#pragma once

#include "MakeEngine/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace MK {

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};

}