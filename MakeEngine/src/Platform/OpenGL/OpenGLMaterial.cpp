#include "mkpch.h"

#include "OpenGLMaterial.h"

namespace MK {
	OpenGLMaterial::OpenGLMaterial(const Ref<Shader> shader, const Ref<Texture> diffuse)
		: Material(shader, diffuse)
	{}
}