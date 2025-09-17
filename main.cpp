#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <bits/stdc++.h>

#include <engine/camera.h>
#include <engine/entity.h>
#include <engine/mesh_renderer.h>
#include <engine/physics.h>
#include <engine/scene.h>
#include <engine/utils.h>
#include <engine/math/vec3.h>

using namespace std;


namespace engine {
	
	bool runningApplication = true;
	bool canExit = false;
	
	float lastFrameTime(glfwGetTime());
	float lastPhysicsFrameTime(glfwGetTime());
	
	float speed(2.8);
	float sensitivity(.1);
	
	float physicsUpdateTime(1 / 10'000.f);
	
	// placeholder methods.
	void awake();
	
	void start(GLFWwindow *window);
	
	void update(GLFWwindow *window);
	
	void physicsUpdate(GLFWwindow *window);
	
	float randomFloat(float min, float max)
	{
		float randomFloat = min + static_cast<float>(rand()) / (RAND_MAX / (max - min));
		return randomFloat;
	}
	
	void terminateApplication()
	{
		runningApplication = false;
	}
	
	void framebuffer_size_callback(GLFWwindow *window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
	
	void glfwInputUpdateHandler(GLFWwindow *window)
	{
		Mouse::updateCursorPosition(window);
	}
	
	void dataSync()
	{
		if (!runningApplication)
			return;

		Camera::get_main()->updateCamera();
		
		for (const auto &r : Scene::activeScene->m_drawables)
		{
			for (auto &entity : r->get_entities())
			{
				entity->renderData = EntityRenderData {
						entity->transform.modelMatrix(),
						entity->color
				};
			}
		}
	}
	
	void physicsLoop(GLFWwindow *window)
	{
		while (runningApplication)
		{
			float startTime = glfwGetTime();
			Time::physicsDeltaTime = (startTime - lastPhysicsFrameTime) * Time::timeScale;
			lastPhysicsFrameTime = startTime;
			
			// physics shit
			Scene::activeScene->updateScene(window);
			
			physicsUpdate(window);
			
			// sync
			dataSync();
			
			// physics fps cap
			double timeToWait = max(physicsUpdateTime - (glfwGetTime() - startTime), 0.);
			this_thread::sleep_for(chrono::duration<double>(timeToWait));

			// std::cout << "Physics Frame time: " << glfwGetTime() - startTime << std::endl;
		}
		
		canExit = true;
		std::cout << "Terminated Application!" << std::endl;
	}
	
	void renderLoop(GLFWwindow *window)
	{
		// main loop
		while (!glfwWindowShouldClose(window))
		{
			// delta time
			Time::runTime = glfwGetTime();
			Time::deltaTime = (Time::runTime - lastFrameTime) * Time::timeScale;
			lastFrameTime = Time::runTime;
			
			update(window);
			
			// RENDERING
			glClearColor(0, 0, 0, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			// upload/draw all MeshRenderers
			
			Scene::activeScene->drawScene(window);
			
			glfwPollEvents();
			glfwInputUpdateHandler(window);
			
			// BUFFER
			glfwSwapBuffers(window);

			// std::cout << "Rendering Frame time: " << glfwGetTime() - Time::runTime << std::endl;
		}
		
		terminateApplication();
	}
	
	int main()
	{
		awake();
		
		// initialize openGL
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		
		GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL 😎", nullptr,
											  nullptr);
		if (window == nullptr)
		{
			cerr << "Failed to create GLFW window" << endl;
			glfwTerminate();
			return EXIT_FAILURE;
		}
		glfwMakeContextCurrent(window);
		
		if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
		{
			cerr << "Failed to initialize GLAD" << endl;
			return EXIT_FAILURE;
		}
		
		glViewport(0, 0, 800, 600);
		
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//		glEnable(GL_CULL_FACE);
//		glCullFace(GL_BACK);
//		glFrontFace(GL_CCW);
		
		glfwSwapInterval(0);
		
		Scene *scene;
		scene = SOL::readScene("Scenes/main/main.scene");
		scene->activate();
		
		
		start(window);
		
		thread physicsThread(physicsLoop, window);
		
		if (physicsThread.joinable())
			physicsThread.detach();
		
		engine::renderLoop(window);
		
		// timeout check
		float startTime(glfwGetTime());
		float timeout(5);
		while (!canExit)
		{
			if (glfwGetTime() - startTime > timeout)
			{
				std::cout << "Timeout reached. Force quitting!" << std::endl;
				break;
			}
		}
		
		// potential cleanup
		
		glfwTerminate();
		
		// exit
		return EXIT_SUCCESS;
	}
}

void engine::awake()
{
	Time::timeScale = 0;
}

void engine::start(GLFWwindow *window)
{
}

void engine::physicsUpdate(GLFWwindow *window)
{
//  ----- MOVEMENT -----
//	float toMove(speed * Time::physicsDeltaTime);
//
//	if (Input::getKeyState(window, GLFW_KEY_LEFT_SHIFT) == KeyState::Hold)
//		toMove *= 1.2;
//
//	if (Input::getKeyState(window, GLFW_KEY_W) == KeyState::Hold)
//		Camera::get_main()->transform.translate(toMove * Camera::get_main()->get_forwards());
//	if (Input::getKeyState(window, GLFW_KEY_S) == KeyState::Hold)
//		Camera::get_main()->transform.translate(-toMove * Camera::get_main()->get_forwards());
//	if (Input::getKeyState(window, GLFW_KEY_A) == KeyState::Hold)
//		Camera::get_main()->transform.translate(-toMove * Camera::get_main()->get_right());
//	if (Input::getKeyState(window, GLFW_KEY_D) == KeyState::Hold)
//		Camera::get_main()->transform.translate(toMove * Camera::get_main()->get_right());
//	if (Input::getKeyState(window, GLFW_KEY_SPACE) == KeyState::Hold)
//		Camera::get_main()->transform.translate(toMove * math::vec3(0, 1, 0));
//	if (Input::getKeyState(window, GLFW_KEY_LEFT_CONTROL) == KeyState::Hold)
//		Camera::get_main()->transform.translate(-toMove * math::vec3(0, 1, 0));

//  ----- OBJECT PLACEMENT -----
// 	if (Mouse::getButtonState(window, GLFW_MOUSE_BUTTON_1) == ButtonState::Press)
// 	{
// 		auto *newEntity = new Entity(
// 				Camera::get_main()->transform.position + Camera::get_main()->get_direction(),
// 				math::vec3(0, Camera::get_main()->transform.rotation.y, 0),
// 				math::vec3(1));
//
// 		newEntity->color = math::vec3(1);
// 		newEntity->addComponent(new BoxCollider(math::vec3(1), math::vec3(0)));
// //		newEntity->addComponent(new Rigidbody(0));
// 		newEntity->transform.set_parent(Scene::activeScene->find("cubeParent"));
//
// 		Scene::activeScene->findDrawable("cubeR")->addEntity(newEntity);
// 	}
//
// 	if (Mouse::getButtonState(window, GLFW_MOUSE_BUTTON_2) == ButtonState::Press)
// 	{
// 		auto *newEntity = new Entity(
// 				Camera::get_main()->transform.position + Camera::get_main()->get_direction(),
// 				math::vec3(0, Camera::get_main()->transform.rotation.y, 0),
// 				math::vec3(1));
//
// 		newEntity->color = math::vec3(1);
// 		newEntity->addComponent(new BoxCollider(math::vec3(1), math::vec3(0)));
// 		newEntity->addComponent(new Rigidbody(0));
// 		newEntity->transform.set_parent(Scene::activeScene->find("cubeParent"));
//
// 		Scene::activeScene->findDrawable("cubeR")->addEntity(newEntity);
// 	}
}

void engine::update(GLFWwindow *window)
{
//  ----- MOUSE MOVEMENT -----
	math::vec2 offset = Mouse::getMouseOffset();
	Camera::get_main()->transform
			.rotateAxis(offset.x * sensitivity * Time::timeScale, math::vec3(0, 1, 0));
	Camera::get_main()->transform
			.rotateAxis(-offset.y * sensitivity * Time::timeScale, math::vec3(1, 0, 0));
	
	Camera::get_main()->transform
			.rotateTo(clamp(Camera::get_main()->transform.rotation.x, -89.f, 89.f),
					  Camera::get_main()->transform.rotation.y,
					  0);

//  ----- ESCAPE 'MENU' -----
	if (Input::getKeyState(window, GLFW_KEY_ESCAPE) == KeyState::Press)
	{
		if (Mouse::getCursorMode(window) == CursorState::Normal)
		{
			Mouse::setCursorMode(window, CursorState::Disabled);
			Time::timeScale = 1;
		} else if (Mouse::getCursorMode(window) == CursorState::Disabled)
		{
			Mouse::setCursorMode(window, CursorState::Normal);
			Time::timeScale = 0;
		}
	}
}


int main()
{
	return engine::main();
}
