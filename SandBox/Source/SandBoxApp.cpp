#include "Ivaldi.h"

#include "Log/Log.h"
#include "Scene/Camera/Camera.h"
#include "Scene/SimpleScene.h"
#include "Scene/SimpleSceneParser.h"
#include "Event/KeyEvent.h"
#include "Platform/Assimp/AssimpSceneLoader.h"
#include "Platform/OpenGL/GLClient.h"
#include "Platform/OpenGL/GLMaterialSystem.h"
#include "Window.h"

class SandBoxApp : public ivaldi::IvaldiApp {
public:
	SandBoxApp()
		: m_logger(ivaldi::Logger::create("Client"))
	{
		
	}

	~SandBoxApp() = default;

	void init() override
	{
		m_window = ivaldi::Window::createWindow({ 720, 480, "Ivaldi test" });
		m_window->setVSync(true);
		m_window->registerEventCallback(std::bind(&SandBoxApp::onEvent, this, std::placeholders::_1));
		m_window->start();

		ivaldi::gpu::GLMaterialSystem material_system;
		ivaldi::AssimpSceneLoader scene_loader(material_system);
		
		m_gpu_client = std::make_unique<ivaldi::gpu::GLClient>();
		m_gpu_client->setViewport(0, 0, 800, 600);
		
		auto scene_parser = new ivaldi::scene::SimpleSceneParser(*m_gpu_client);
		
		ivaldi::scene::Camera::CameraParams camera_params {
			ivaldi::math::Point3::zero,
			ivaldi::math::Quaternion::identity,
			ivaldi::scene::Camera::CameraType::Perspective
		};

		m_scene = std::make_unique<ivaldi::scene::SimpleScene>(scene_parser, camera_params);
		m_scene->parse("E:/Models/nanosuit/Nanosuit.obj", scene_loader);

		m_scene->getCamera().setPosition(ivaldi::math::Point3::zero);
	}

	void update() override
	{
		m_window->preRender();
		m_scene->update(1/60.f);
		m_scene->render(*m_gpu_client, 1/60.f);
		m_window->postRender();
	}

	bool onEvent(ivaldi::Event& event)
	{
		if (event.getType() == ivaldi::Event::EventType::KeyDown) {
			ivaldi::KeyEvent& key_event = (ivaldi::KeyEvent&)event;
			m_logger.info("{0} key code: {1}", event.getName(), key_event.getKeyCode());
			
			auto camera_pos = m_scene->getCamera().getPosition();
			auto camera_rot = m_scene->getCamera().getRotation();

			switch (key_event.getKeyCode()) {
			case 17:
				m_logger.info("W pressed");
				camera_pos.z += 0.1f;
				m_scene->getCamera().setPosition(camera_pos);
				break;
			case 31:
				m_logger.info("S pressed");
				camera_pos.z -= 0.1f;
				m_scene->getCamera().setPosition(camera_pos);
				break;
			case 30:
				m_logger.info("A pressed");
				camera_pos.x -= 0.1f;
				m_scene->getCamera().setPosition(camera_pos);
				break;
			case 32:
				m_logger.info("D pressed");
				camera_pos.x += 0.1f;
				m_scene->getCamera().setPosition(camera_pos);
				break;
			default:
				m_logger.info("Not binded key");
			}
		}

		return true;
	}

private:
	ivaldi::Window* m_window;
	ivaldi::Logger m_logger;
	std::unique_ptr<ivaldi::scene::SimpleScene> m_scene;
	std::unique_ptr<ivaldi::gpu::GPUClient> m_gpu_client;
};

ivaldi::IvaldiApp* ivaldi::createApplication()
{
	return new SandBoxApp();
}