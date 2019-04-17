#pragma once

#include "Core.h"

namespace ivaldi {
	class IVALDI_API Event {
	public:
		enum class EventType {
			None, KeyDown, KeyUp, KeyRepeat,
			MouseDown, MouseUp, MouseRepeat,
			IvaldiTick, IvaldiRender
		};
		
		Event() = default;
		~Event() = default;

		virtual const char* getName() const = 0;
		virtual EventType getType() const = 0;
	};
}


