#pragma once

#include "Core.h"

namespace ivaldi {
	namespace gpu {
		class ShaderInputLayout {
		public:
			struct ShaderAttribute {
				VertexAttribute vertex_attribute;
				unsigned short size;
				unsigned short offset;
				unsigned short stride;
			};

			ShaderInputLayout() = default;
			~ShaderInputLayout() = default;
			
			void addAttribute(const ShaderAttribute& attribute) { m_layout.push_back(attribute); }
			const std::vector<ShaderAttribute>& getLayout() const { return m_layout; }

		private:
			std::vector<ShaderAttribute> m_layout;
		};
	}
}