#include "Precompiled.h"
#include "Platform/Windows/WindowsWindow.h"

#include "Core.h"

#include "Event/MouseEvent.h"
#include "Event/KeyEvent.h"

namespace ivaldi {

	WindowsWindow::WindowsWindow(const Window::WindowParams& params)
		: m_params(params)
	{}

	WindowsWindow::~WindowsWindow() { glfwDestroyWindow(m_window); }

	void WindowsWindow::start()
	{
		if (!m_glfw_initialized) {
			auto success = glfwInit();
			IVALDI_ASSERT(success);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			m_glfw_initialized = true;
		}

		m_window = glfwCreateWindow(m_params.width, m_params.height, m_params.title, NULL, NULL);

		glfwSetWindowUserPointer(m_window, &m_callback_func);
		glfwMakeContextCurrent(m_window);

		glfwSetKeyCallback(m_window, [] (GLFWwindow* window, int key , int scancode, int action, int modes)
		{
			auto callback = *(WindowsWindow::CallbackFunc*)glfwGetWindowUserPointer(window);

			switch (action) {
				case GLFW_PRESS: {
					KeyDown event(scancode, false);
					callback(event);
					break;
				}
				case GLFW_REPEAT: {
					KeyDown event(scancode, true);
					callback(event);
					break;
				}
				case GLFW_RELEASE: {
					KeyUp event(scancode);
					callback(event);
					break;
				}
			}
		});
	}

	void WindowsWindow::preRender()
	{
		glfwPollEvents();
	}

	void WindowsWindow::postRender()
	{
		glfwSwapBuffers(m_window);
	}
	
	void WindowsWindow::shutdown()
	{
		glfwTerminate();
	}

	void WindowsWindow::registerEventCallback(const CallbackFunc& callback_func)
	{
		m_callback_func = callback_func;
	}

	void WindowsWindow::setVSync(bool v_sync)
	{
		glfwSwapInterval(v_sync);
	}

	Window* Window::createWindow(const WindowParams& params)
	{
		return new WindowsWindow(params);
	}

	bool WindowsWindow::m_glfw_initialized = false;
}
