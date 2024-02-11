#pragma once

#include "MakeEngine/Renderer/Material.h"

namespace MK {
	class OpenGLMaterial : public Material
	{
	public:
		OpenGLMaterial(const Ref<Shader> shader, const Ref<Texture> texture);
	};
}