#pragma once

#include "MakeEngine/Core.h"

#include "glm/glm.hpp"

namespace MK {
	class Light
	{
	public:
		~Light() = default;

		Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position)
			:m_Ambient(ambient), m_Diffuse(diffuse), m_Specualar(specular), m_Position(position)
		{}

		static Ref<Light> Create(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position);
	public:
		glm::vec3 m_Ambient;
		glm::vec3 m_Diffuse;
		glm::vec3 m_Specualar;
		glm::vec3 m_Position;
	};
}
