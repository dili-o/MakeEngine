#include "mkpch.h"
#include "Light.h"

namespace MK {
	Ref<Light> Light::Create(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position)
	{
		return CreateRef<Light>(ambient, diffuse, specular, position);
	}
}