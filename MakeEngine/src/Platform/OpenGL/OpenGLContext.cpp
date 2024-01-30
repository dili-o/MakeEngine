#include "mkpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>

namespace MK {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		MK_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		glfwSetInputMode(m_WindowHandle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		MK_CORE_ASSERT(status, "Failed to initialize Glad!");

		MK_CORE_INFO("OpenGL Info:");
		MK_CORE_INFO("Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		MK_CORE_INFO("Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		MK_CORE_INFO("Version: {0}", (const char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}