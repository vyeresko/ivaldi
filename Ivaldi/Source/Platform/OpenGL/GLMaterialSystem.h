#pragma once
#include "Precompiled.h"

#include "MaterialSystem/MaterialSystem.h"

namespace ivaldi {
	namespace gpu {
		class IVALDI_API GLMaterialSystem : public MaterialSystem {
		public:
			GLMaterialSystem() = default;
			~GLMaterialSystem() = default;

			std::string createVertexShaderSrc(VertexAttribute channels, const char* info) const override;
			std::string createPixelShaderSrc(VertexAttribute channels, const char* info) const override;
		};
	}
}