#pragma once

#include <vector>

namespace ivaldi {
	namespace gpu {
		class IndexBuffer {
		public:
			IndexBuffer() = default;
			virtual ~IndexBuffer() = default;

			virtual void copyData(const std::vector<unsigned int> &data) = 0;
			virtual int getSize() const = 0;

			virtual void bind() = 0;
			virtual void unbind() = 0;
		};
	}
}