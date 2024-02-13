#include "mkpch.h"

#include "OpenGLMaterial.h"

namespace MK {
	OpenGLMaterial::OpenGLMaterial(const Ref<Shader> shader, const Ref<Texture> diffuse, const Ref<Texture> spec, float shininess)
		: Material(shader, diffuse, spec, shininess)
	{
		MK_CORE_INFO("Material created");
	}
}