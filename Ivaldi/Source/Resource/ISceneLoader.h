#pragma once

#include "Precompiled.h"
#include "Resource/IResourceIterator.h"

namespace ivaldi {
	namespace res {
		class ISceneLoader {
		public:
			virtual ~ISceneLoader() = default;

			virtual void load(const std::string& path) = 0;
			virtual void unload() = 0;
			virtual res::IResourceIterator* getIterator() const = 0;
		};
	};
};