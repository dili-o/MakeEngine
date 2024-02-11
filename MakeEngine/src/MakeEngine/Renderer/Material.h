#pragma once

#include "Shader.h"
#include "Texture.h"
#include "MakeEngine/Core.h"


namespace MK {
	class Material
	{
	public:
		virtual ~Material() = default;

		void Bind()
		{
			m_Texture->Bind();
		}

		static Ref<Material> Create(const Ref<Shader> shader, const Ref<Texture> texture);

	protected:
		Material(const Ref<Shader> shader, const Ref<Texture> texture)
			: m_Shader(shader), m_Texture(texture)
		{}
		Ref<Shader> m_Shader;
		Ref<Texture> m_Texture;
	};
}