#include "mkpch.h"
#include "Light.h"
#include "Shader.h"

namespace MK {
	// Directional Lights
	void DirectionalLight::Bind(Ref<Shader> shader)
	{
		shader->UploadUniformFloat3("light.direction", m_Direction);
		shader->UploadUniformFloat3("light.ambient", m_Ambient);
		shader->UploadUniformFloat3("light.diffuse", m_Diffuse);
		shader->UploadUniformFloat3("light.specular", m_Specular);
	}
	Ref<DirectionalLight> DirectionalLight::Create(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 direction)
	{
		return CreateRef<DirectionalLight>(ambient, diffuse, specular, direction);
	}
	// World Lights
	void WorldLight::Bind(Ref<Shader> shader)
	{
		shader->UploadUniformFloat3("light.position", m_Position);
		shader->UploadUniformFloat3("light.ambient", m_Ambient);
		shader->UploadUniformFloat3("light.diffuse", m_Diffuse);
		shader->UploadUniformFloat3("light.specular", m_Specular);
	}
	Ref<WorldLight> WorldLight::Create(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position)
	{
		return CreateRef<WorldLight>(ambient, diffuse, specular, position);
	}
	// Point Lights
	void PointLight::Bind(Ref<Shader> shader)
	{
		shader->UploadUniformFloat3("light.position", m_Position);
		shader->UploadUniformFloat3("light.ambient", m_Ambient);
		shader->UploadUniformFloat3("light.diffuse", m_Diffuse);
		shader->UploadUniformFloat3("light.specular", m_Specular);
		shader->UploadUniformFloat("light.constant", m_Constant);
		shader->UploadUniformFloat("light.linear", m_Linear);
		shader->UploadUniformFloat("light.quadratic", m_Quadratic);
	}
	Ref<PointLight> PointLight::Create(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position, float constant, float linear, float quadratic)
	{
		return CreateRef<PointLight>(ambient, diffuse, specular, position, constant, linear, quadratic);
	}
	
}