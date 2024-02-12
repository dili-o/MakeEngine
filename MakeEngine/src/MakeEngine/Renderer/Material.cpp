#include "mkpch.h"
#include "Material.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLMaterial.h"


namespace MK {
	void Material::Bind()
	{
		m_DiffuseTexture->Bind(0);
		m_Shader->UploadUniformInt("u_DiffuseTexture", m_DiffuseTexture->GetSlot());
	}

	Ref<Material> Material::Create(const Ref<Shader> shader, const Ref<Texture> diffuse)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    MK_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLMaterial>(shader, diffuse);
		}
		MK_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}