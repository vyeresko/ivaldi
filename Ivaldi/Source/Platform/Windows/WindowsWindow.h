#pragma once

#include "Window.h"

#include "glfw/glfw3.h"

namespace ivaldi {
	class WindowsWindow: public Window {
	public:
		WindowsWindow(const Window::WindowParams& params);
		~WindowsWindow();

		void start() override;
		void shutdown() override;
		void preRender() override;
		void postRender() override;
		void registerEventCallback(const CallbackFunc& callback_func) override;
		void setVSync(bool v_sync) override;

	private:
		
		Window::WindowParams m_params;
		GLFWwindow* m_window;
		CallbackFunc m_callback_func;
		static bool m_glfw_initialized;
	};
}