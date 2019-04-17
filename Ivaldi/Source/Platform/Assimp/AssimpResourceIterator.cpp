#include "Precompiled.h"
#include "AssimpResourceIterator.h"

#include "Core.h"
#include "Platform/Assimp/AssimpSceneLoader.h"

namespace ivaldi {
	bool AssimpResourceIterator::hasNext() const 
	{
		// always one object
		return m_index != 1;
	}

	void AssimpResourceIterator::advance()
	{
		++m_index;
	}

	const res::ResourceBundle& AssimpResourceIterator::get() const
	{
		return m_scene_loader.m_bundle_res;
	}
}