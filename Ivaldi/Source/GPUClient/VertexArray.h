#pragma once

#include "GPUClient/VertexArray.h"
#include "GPUClient/VertexBuffer.h"

namespace ivaldi {
	namespace gpu {
		// FWD DEC
		class VertexBuffer;
		class IndexBuffer;
		class ShaderInputLayout;
		
		class VertexArray {
		public:
			VertexArray() = default;
			virtual ~VertexArray() = default;

			const VertexBuffer& getVertexBuffer() const { return *m_vbuffer; }
			void setVertexBuffer(std::shared_ptr<VertexBuffer> buffer) { m_vbuffer = buffer; }

			const IndexBuffer& getIndexBuffer() const { return *m_ibuffer; }
			void setIndexBuffer(std::shared_ptr<IndexBuffer> buffer) { m_ibuffer = buffer; }
			
			virtual void setInputLayout(const ShaderInputLayout& input_layout) = 0;

			virtual void bind() = 0;
			virtual void unbind() = 0;

		protected:
			std::shared_ptr<VertexBuffer> m_vbuffer;
			std::shared_ptr<IndexBuffer> m_ibuffer;			
		};
	}
}


