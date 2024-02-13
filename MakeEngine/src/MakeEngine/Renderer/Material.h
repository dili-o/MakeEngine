#pragma once

#include "Shader.h"
#include "Texture.h"
#include "MakeEngine/Core.h"


namespace MK {
	class Material
	{
	public:
		virtual ~Material() = default;

		void Bind();

		static Ref<Material> Create(const Ref<Shader> shader, const Ref<Texture> diffuse, const Ref<Texture> spec = nullptr, float shininess = 32.f);

	protected:
		Material(const Ref<Shader> shader, const Ref<Texture> diffuse, const Ref<Texture> spec = nullptr, float shininess = 32.f)
			: m_Shader(shader), m_DiffuseTexture(diffuse), m_SpecularTexture(spec), m_Shininess(shininess)
		{}
		Ref<Shader> m_Shader;
		Ref<Texture> m_DiffuseTexture;
		Ref<Texture> m_SpecularTexture;
		float m_Shininess;
	};
}