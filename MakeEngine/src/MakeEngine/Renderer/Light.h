#pragma once

#include "MakeEngine/Core.h"

#include "glm/glm.hpp"


namespace MK {
	class Shader;
	class Light
	{
	public:
		~Light() = default;

		Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
			:m_Ambient(ambient), m_Diffuse(diffuse), m_Specular(specular)
		{}
											  
		virtual void Bind(Ref<Shader> shader, int index) = 0;
	protected:
		glm::vec3 m_Ambient;
		glm::vec3 m_Diffuse;
		glm::vec3 m_Specular;
	};

	class DirectionalLight : public Light
	{
	public:
		DirectionalLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 direction)
			:Light(ambient, diffuse, specular), m_Direction(direction)
		{}
		virtual void Bind(Ref<Shader> shader, int index) override;
		static Ref<DirectionalLight> Create(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 direction);

	private:
		glm::vec3 m_Direction;
	};

	class WorldLight : public Light
	{
	public:
		WorldLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position)
			:Light(ambient, diffuse, specular), m_Position(position)
		{}

		virtual void Bind(Ref<Shader> shader, int index) override;
		static Ref<WorldLight> Create(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position);

	private:
		glm::vec3 m_Position;
	};

	class PointLight : public Light
	{
	public:
		PointLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position, float constant, float linear, float quadratic)
			:Light(ambient, diffuse, specular), m_Position(position), m_Constant(constant), m_Linear(linear), m_Quadratic(quadratic)
		{}

		virtual void Bind(Ref<Shader> shader, int index) override;
		static Ref<PointLight> Create(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position, float constant, float linear, float quadratic);
	private:
		glm::vec3 m_Position;
		float m_Constant;
		float m_Linear;
		float m_Quadratic;
	};

	class SpotLight : public Light
	{
	public:
		SpotLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position, glm::vec3 direction,
			float constant, float linear, float quadratic, float cutOff, float outerCutOff)
			:Light(ambient, diffuse, specular), m_Position(position), m_Constant(constant), m_Direction(direction),
			m_Linear(linear), m_Quadratic(quadratic), m_CutOff(cutOff), m_OuterCutOff(outerCutOff)
		{}

		virtual void Bind(Ref<Shader> shader, int index) override;
		static Ref<SpotLight> Create(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position, glm::vec3 direction,
			float constant, float linear, float quadratic, float cutOff, float outerCutOff);
	private:
		glm::vec3 m_Position;
		glm::vec3 m_Direction;
		float m_Constant;
		float m_Linear;
		float m_Quadratic;
		float m_CutOff;
		float m_OuterCutOff;
	};
}
