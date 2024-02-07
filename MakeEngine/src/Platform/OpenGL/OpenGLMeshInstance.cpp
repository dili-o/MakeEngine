#include "mkpch.h"
#include "OpenGLMeshInstance.h"
#include "glad/glad.h"

namespace MK {
	void OpenGLMeshInstance::CreateInstance(const Ref<VertexArray>& vertexArray, float* translations, unsigned int instanceCount)
	{
		m_InstanceCount = instanceCount;
		m_VertexArray = vertexArray;

        MK_CORE_WARN("Array size: {0}", sizeof(translations));

        MK::Ref<MK::VertexBuffer> instanceBuffer;
        instanceBuffer.reset(VertexBuffer::Create(translations, instanceCount * (4 * 4 * sizeof(float))));

        MK::BufferLayout layout = {
            { MK::ShaderDataType::Float4, "a_InstanceMatrix[0]" },
            { MK::ShaderDataType::Float4, "a_InstanceMatrix[1]" },
            { MK::ShaderDataType::Float4, "a_InstanceMatrix[2]" },
            { MK::ShaderDataType::Float4, "a_InstanceMatrix[3]" }
        };
        instanceBuffer->SetLayout(layout);

        m_VertexArray->AddInstanceBuffer(instanceBuffer);
	}
}