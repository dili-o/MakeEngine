#include "mkpch.h"
#include "OpenGLMesh.h"

namespace MK {
	void OpenGLMesh::CreateTriangle()
	{

	}

	void OpenGLMesh::CreateQuad()
	{
	}

	void OpenGLMesh::CreateCube()
	{
		
	}
	void OpenGLMesh::CreateTexturedCube()
	{
		float cubeVertices[] = {
			
			// Front face
			-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.5f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.5f, 0.0f, 1.0f,

			// Back face
			-0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f, 1.0f, 1.0f,

			// Left face
			-0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f, 0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
			-0.5f, -0.5f,  0.5f, 1.0f, 0.0f,

			// Right face
			0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
			0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
			0.5f,  0.5f,  0.5f, 0.0f, 1.0f,
			0.5f, -0.5f,  0.5f, 0.0f, 0.0f,

			// Bottom face
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f, 1.0f, 1.0f,
			-0.5f, -0.5f,  0.5f, 0.0f, 1.0f,

			// Top face
			-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
			 0.5f, 0.5f,  0.5f, 1.0f, 0.0f,
			 0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
			-0.5f, 0.5f,  0.5f, 0.0f, 0.0f
		};

		MK::Ref<MK::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(cubeVertices, sizeof(cubeVertices)));
		// Create the vertex buffer layout
		MK::BufferLayout layout = {
			{ MK::ShaderDataType::Float3, "a_Position" },
			{ MK::ShaderDataType::Float2, "a_TexCoord" }
		};
		// Set the vertex buffer layout and add it to vertex array
		vertexBuffer->SetLayout(layout);

		m_VertexArray.reset(VertexArray::Create());
		m_VertexArray->AddVertexBuffer(vertexBuffer);
		// Create the index buffer
		uint32_t cubeIndicies[] =
		{
			0, 1, 2, 2, 3, 0, // Front face
			4, 5, 6, 5, 4, 7, // Back face
			8, 9, 10, 10, 11, 8, // Left face
			12, 13, 14, 14, 15, 12, // Right face
			16, 17, 18, 18, 19, 16, // Bottom face
			20, 21, 22, 21, 20, 23 // Top face
		};
		MK::Ref<MK::IndexBuffer> indexBuffer;
		indexBuffer.reset(MK::IndexBuffer::Create(cubeIndicies, sizeof(cubeIndicies) / sizeof(uint32_t)));
		// Add the index buffer to the vertex array
		m_VertexArray->SetIndexBuffer(indexBuffer);
	}
}