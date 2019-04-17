#pragma once

#include "Core.h"
#include "Event/Event.h"

namespace ivaldi {
	class IVALDI_API Window {
	public:
		using CallbackFunc = std::function<bool(Event&)>;

		struct WindowParams {
			unsigned short width;
			unsigned short height;
			const char* title;
		};
		
		virtual void start() = 0;
		virtual void preRender() = 0;
		virtual void postRender() = 0;
		virtual void shutdown() = 0;
		virtual void registerEventCallback(const CallbackFunc& callback_func) = 0;
		virtual void setVSync(bool v_sync) = 0;
		
		static Window* createWindow(const WindowParams& params);
	};
}
