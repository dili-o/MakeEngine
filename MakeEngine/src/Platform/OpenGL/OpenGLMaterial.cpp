#include "mkpch.h"

#include "OpenGLMaterial.h"

namespace MK {
	OpenGLMaterial::OpenGLMaterial(const Ref<Shader> shader, const Ref<Texture> texture)
		: Material(shader, texture)
	{}
}