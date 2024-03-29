#include "mkpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace MK {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case MK::ShaderDataType::Float:    return GL_FLOAT;
		case MK::ShaderDataType::Float2:   return GL_FLOAT;
		case MK::ShaderDataType::Float3:   return GL_FLOAT;
		case MK::ShaderDataType::Float4:   return GL_FLOAT;
		case MK::ShaderDataType::Mat3:     return GL_FLOAT;
		case MK::ShaderDataType::Mat4:     return GL_FLOAT;
		case MK::ShaderDataType::Int:      return GL_INT;
		case MK::ShaderDataType::Int2:     return GL_INT;
		case MK::ShaderDataType::Int3:     return GL_INT;
		case MK::ShaderDataType::Int4:     return GL_INT;
		case MK::ShaderDataType::Bool:     return GL_BOOL;
		}

		MK_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		MK_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index + m_VertexBufferIndexOffset);
			glVertexAttribPointer(
				index + m_VertexBufferIndexOffset,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)(intptr_t)element.Offset
			);
			index++;
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

	void OpenGLVertexArray::AddInstanceBuffer(const Ref<VertexBuffer>& instanceBuffer)
	{
		MK_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_RendererID);
		instanceBuffer->Bind();

		const auto& layout = instanceBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index + m_VertexBufferIndexOffset);
			glVertexAttribPointer(
				index + m_VertexBufferIndexOffset,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)(intptr_t)element.Offset
			);
			glVertexAttribDivisor(index + m_VertexBufferIndexOffset, 1);
			index++;
		}
		m_VertexBuffers.push_back(instanceBuffer);
		glBindVertexArray(0);
	}

}