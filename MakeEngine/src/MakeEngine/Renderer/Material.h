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
		static Ref<Material> Create(const Ref<Shader> shader, const Ref<Texture> diffuse);

	protected:
		Material(const Ref<Shader> shader, const Ref<Texture> diffuse)
			: m_Shader(shader), m_DiffuseTexture(diffuse)
		{}
		Ref<Shader> m_Shader;
		Ref<Texture> m_DiffuseTexture;
	};
}