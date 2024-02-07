#include "mkpch.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLMeshInstance.h"

namespace MK {
	Ref<MeshInstance> MK::MeshInstance::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    MK_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLMeshInstance>();
		}
		MK_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}