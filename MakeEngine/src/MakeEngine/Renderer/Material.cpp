#include "mkpch.h"
#include "Material.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLMaterial.h"


namespace MK {
	void Material::Bind()
	{
		m_DiffuseTexture->Bind(0);
		m_Shader->UploadUniformInt("material.diffuse", m_DiffuseTexture->GetSlot());
		if (m_SpecularTexture)
		{
			m_SpecularTexture->Bind(1);
			m_Shader->UploadUniformInt("material.specular", m_SpecularTexture->GetSlot());
		}
			
		m_Shader->UploadUniformFloat("material.shininess", m_Shininess);
	}

	Ref<Material> Material::Create(const Ref<Shader> shader, const Ref<Texture> diffuse, const Ref<Texture> spec, float shininess)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    MK_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLMaterial>(shader, diffuse, spec, shininess);
		}
		MK_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}