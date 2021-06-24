#pragma once
#include <memory>
#include "Engine/Renderer/Buffer.h"

namespace Engine
{
	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(Ref<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(Ref<IndexBuffer>& vertexBuffer) = 0;

		virtual std::vector<Ref<VertexBuffer>>& GetVertexBuffers() = 0;
		virtual Ref<IndexBuffer>& GetIndexBuffer() = 0;

		static Ref<VertexArray> Create();
	};
}