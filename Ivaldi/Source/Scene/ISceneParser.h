#pragma once
#include "Precompiled.h"

#include "GPUClient/GPUClient.h"
#include "Scene/Entity.h"

namespace ivaldi {
	
	// FWD DEC
	namespace res {
		class ResourceBundle;
	}

	namespace scene {
		class IVALDI_API ISceneParser {
		public:
			virtual ~ISceneParser() = default;

			virtual Entity getEntity(const res::ResourceBundle& res_bundle) = 0;
		};
	}
}