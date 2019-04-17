#pragma once
#include "GPUClient/Texture.h"

#include <glad/glad.h>

namespace ivaldi {
	namespace gpu {
		class GLTexture : public Texture {
		public:
			GLTexture();
			~GLTexture();

			void copyData(const unsigned char *data, const unsigned short width, const unsigned short height) override;

		protected:
			void bind(unsigned short unit) override;
			void unbind() override;

		private:
			GLuint m_index;

 		};
	}
}