#pragma once

#include "Resource/IResourceIterator.h"

namespace ivaldi {
	class AssimpSceneLoader;

	class AssimpResourceIterator : public res::IResourceIterator {
	public:
		AssimpResourceIterator(const AssimpSceneLoader& scene_loader)
			: m_scene_loader(scene_loader)
		{}

		bool hasNext() const override;
		void advance() override;
		const res::ResourceBundle& get() const override;
	
	private:
		const AssimpSceneLoader& m_scene_loader;
		size_t m_index = 0;
	};
}