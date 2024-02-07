#pragma

#include "MakeEngine/Renderer/MeshInstance.h"

namespace MK {
	class OpenGLMeshInstance : public MeshInstance
	{
	public:
		OpenGLMeshInstance() = default;
		virtual ~OpenGLMeshInstance() = default;
		virtual void CreateInstance(const Ref<VertexArray>& vertexArray, float* translations, unsigned int instanceCount) override;
		virtual const unsigned int GetInstanceCount() const override { return m_InstanceCount; }
		virtual const Ref<VertexArray>& GetVertexArray() const override { return m_VertexArray; };

	};
}