#pragma once

#include "Core.h"

namespace ivaldi {
	class MaterialSystem {
	public:
		MaterialSystem() = default;
		~MaterialSystem() = default;

		virtual std::string createVertexShaderSrc(VertexAttribute channels, const char* info) const = 0;
		virtual std::string createPixelShaderSrc(VertexAttribute channels, const char* info) const = 0;
	};
}