#pragma

#include "Mesh.h"

namespace MK {
	class MeshInstance
	{
	public:
		virtual ~MeshInstance() = default;

		virtual void CreateInstance(const Ref<VertexArray>& vertexArray, float* translations, unsigned int instanceCount) = 0;
		virtual const Ref<VertexArray>& GetVertexArray() const = 0;
		virtual const unsigned int GetInstanceCount() const = 0;
		virtual void SetVertexArray(const Ref<VertexArray>& vertexArray) { m_VertexArray = vertexArray; }
		
		static Ref<MeshInstance> Create();
	protected:
		unsigned int m_InstanceCount;
		Ref<VertexArray> m_VertexArray;
	};
}