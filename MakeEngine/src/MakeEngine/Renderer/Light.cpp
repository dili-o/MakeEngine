#include "mkpch.h"
#include "Light.h"
#include "Shader.h"

namespace MK {
	// Directional Lights
	void DirectionalLight::Bind(Ref<Shader> shader, int index)
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
	void WorldLight::Bind(Ref<Shader> shader, int index)
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
	void PointLight::Bind(Ref<Shader> shader, int index)
	{
		std::string light = "pointLights[" + std::to_string(index) + "]";
		shader->UploadUniformMat3(light + ".position", glm::mat3(1.f));
		shader->UploadUniformFloat3(light + ".position", m_Position);
		shader->UploadUniformFloat3(light + ".ambient", m_Ambient);
		shader->UploadUniformFloat3(light + ".diffuse", m_Diffuse);
		shader->UploadUniformFloat3(light + ".specular", m_Specular);
		shader->UploadUniformFloat(light + ".constant", m_Constant);
		shader->UploadUniformFloat(light + ".linear", m_Linear);
		shader->UploadUniformFloat(light + ".quadratic", m_Quadratic);
	}
	Ref<PointLight> PointLight::Create(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position, float constant, float linear, float quadratic)
	{
		return CreateRef<PointLight>(ambient, diffuse, specular, position, constant, linear, quadratic);
	}

	// Spot Light
	void SpotLight::Bind(Ref<Shader> shader, int index)
	{
		shader->UploadUniformFloat3("light.position", m_Position);
		shader->UploadUniformFloat3("light.direction", m_Direction);
		shader->UploadUniformFloat3("light.ambient", m_Ambient);
		shader->UploadUniformFloat3("light.diffuse", m_Diffuse);
		shader->UploadUniformFloat3("light.specular", m_Specular);
		shader->UploadUniformFloat("light.constant", m_Constant);
		shader->UploadUniformFloat("light.linear", m_Linear);
		shader->UploadUniformFloat("light.quadratic", m_Quadratic);
		shader->UploadUniformFloat("light.cutOff", m_CutOff);
		shader->UploadUniformFloat("light.outerCutOff", m_OuterCutOff);
	}

	Ref<SpotLight> SpotLight::Create(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 position, glm::vec3 direction, float constant, float linear, float quadratic, float cutOff, float outerCutOff)
	{
		return CreateRef<SpotLight>(ambient, diffuse, specular, position, direction, constant, linear, quadratic, cutOff, outerCutOff);
	}

}