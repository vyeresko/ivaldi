#pragma once

#include "Precompiled.h"
#include "Core.h"

namespace ivaldi {
	class IVALDI_API IvaldiApp {
	public:
		IvaldiApp() = default;
		~IvaldiApp() = default;

		virtual void init() = 0;
		virtual void update() = 0;
	};

	IvaldiApp* createApplication();
}
