#include "mkpch.h"
#include "Mesh.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLMesh.h"

namespace MK
{
	Ref<Mesh> Mesh::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    MK_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLMesh>();
		}
		MK_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}