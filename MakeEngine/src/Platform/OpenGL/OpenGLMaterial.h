#pragma once

#include "MakeEngine/Renderer/Material.h"

namespace MK {
	class OpenGLMaterial : public Material
	{
	public:
		OpenGLMaterial(const Ref<Shader> shader, const Ref<Texture> diffuse, const Ref<Texture> spec = nullptr, float shininess = 32.f);
	};
}