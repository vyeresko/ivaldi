#pragma once

#include "Core.h"
#include "GPUClient/ShaderInputLayout.h"

namespace ivaldi {
	namespace gpu {
		class VertexBuffer {
		public:
			friend class GPUClient;

			VertexBuffer() = default;
			virtual ~VertexBuffer() = default;
			
			virtual void copyData(const std::vector<float> &data) = 0;

			virtual void bind() = 0;
			virtual void unbind() = 0;			
		};
	}
}