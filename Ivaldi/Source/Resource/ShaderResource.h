#pragma once
#include "Core.h"

namespace ivaldi {
	namespace res {
		class ShaderResource {
		public:
			ShaderResource() = default;
			ShaderResource(ShaderType type)
				: m_type(type)
			{}

			~ShaderResource() = default;

			std::string getSource() const { return m_source; }
			void setSource(const std::string& source) { m_source = source; }

			ShaderType getType() const { return m_type; }

		private:
			ShaderType m_type;
			std::string m_source;
		};
	}
}