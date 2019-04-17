#pragma once

namespace ivaldi {
	namespace gpu {
		class Texture {
		public:
			friend class GPUClient;
			Texture() = default;

			unsigned short getWidth() const { return m_width; }
			void setWidth(unsigned short width) { m_width = width; }
			
			unsigned short getHeight() const { return m_height; }
			void setHeight(unsigned short height) { m_height = height; }

			int getChannels() const { return m_channels; }
			void setChannels(int channels) { m_channels = channels; }

			virtual void copyData(const unsigned char* data, const unsigned short width, const unsigned short height) = 0;
			
		protected:
			virtual void bind(unsigned short unit) = 0;
			virtual void unbind() = 0;

		private:
			unsigned short m_width, m_height;
			int m_channels;
		};
	}
}