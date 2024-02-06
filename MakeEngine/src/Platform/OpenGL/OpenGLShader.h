#pragma once

#include "MakeEngine/Renderer/Shader.h"
#include <glm/glm.hpp>
#include <unordered_map>

#include <glad/glad.h>

namespace MK {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const char* vertexSrc, const char* fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		void UploadUniformInt(const std::string& name, int value);

		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& value);

		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
	private:
		std::unordered_map<std::string, GLint> m_UniformLocationCache;
		uint32_t m_RendererID;
	private:
		GLint GetUniformLocation(const std::string& name);
	};

}