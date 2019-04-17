#pragma once


namespace ivaldi {
	namespace res {
		class TextureResource {
		public:
			TextureResource(const std::string path);
			~TextureResource();

			void load();
			const unsigned char* const getData() const;

			std::string getPath() const { return m_path; }
			int getWidth() const { return m_width; }
			int getHeight() const { return m_height;  }
			int getChannelsNum() const { return m_channels;  }

			bool isLoaded() const { return m_is_loaded; }
			
		private:
			std::string m_path;
			unsigned char* m_data;
			int m_width, m_height;
			int m_channels;
			bool m_is_loaded = false;
		};
	}
}