#include "mkpch.h"
#include "Material.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLMaterial.h"


namespace MK {
	Ref<Material> Material::Create(const Ref<Shader> shader, const Ref<Texture> texture)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    MK_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLMaterial>(shader, texture);
		}
		MK_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}