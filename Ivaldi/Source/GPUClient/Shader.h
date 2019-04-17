#pragma once

namespace ivaldi {
	namespace gpu {
		class Shader {
		public:
			friend class GPUClient;

			virtual void setSource(const std::string& source) = 0;
			virtual void compile() = 0;
		};
	}
}