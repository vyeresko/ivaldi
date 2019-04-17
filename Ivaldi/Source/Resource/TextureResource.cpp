#include "Precompiled.h"

#include "TextureResource.h"
#include "Log/Log.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

namespace ivaldi {
	namespace res {
		TextureResource::TextureResource(const std::string path)
			: m_path(path)
		{}

		TextureResource::~TextureResource()
		{
			if (m_is_loaded)
				stbi_image_free(m_data);
		}
		
		void TextureResource::load()
		{
			auto logger = Logger::get("Ivaldi");

			if (m_is_loaded) {
				logger.warn("Trying to load already loaded texture data: {0}", m_path);
				return;	
			}

			logger.info("Loading texture data...");
			m_data = stbi_load(m_path.c_str(), &m_width, &m_height, &m_channels, 0);
			logger.info("Data loaded: {0}", m_path);
			m_is_loaded = true;
		}
		
		const unsigned char* const TextureResource::getData() const
		{
			auto logger = Logger::get("Ivaldi");

			if (!m_is_loaded) 
				logger.warn("Query not loaded texture data: {0}", m_path);
			
			logger.info("Get data: {0}", m_path);
			return m_data;
		}
	}
}