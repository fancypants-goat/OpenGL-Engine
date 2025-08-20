#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <bits/stdc++.h>
#include <vector>
#include <glm/glm.hpp>


#include <engine/mouse.h>
#include <engine/input.h>
#include <engine/shader.h>
#include <engine/texture.h>
#include <engine/resources.h>
#include <engine/object_loader.h>
#include <engine/mesh.h>
#include <engine/mesh_renderer.h>
#include <engine/transform.h>
#include <engine/camera.h>


using namespace std;


namespace engine {
	void framebuffer_size_callback(GLFWwindow *window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
	
	float randomFloat(float min, float max)
	{
		float randomFloat = min + static_cast<float>(rand()) / (RAND_MAX / (max - min));
		return randomFloat;
	}
	
	
	int main()
	{
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
			return -1;
		}
		glfwMakeContextCurrent(window);
		
		if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
		{
			cerr << "Failed to initialize GLAD" << endl;
			return -1;
		}
		
		int nrAttributes;
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
		// std::cout << "Max nr of attributes supported: " << nrAttributes << std::endl;
		
		glViewport(0, 0, 800, 600);
		
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glEnable(GL_DEPTH_TEST);
		
		glfwSwapInterval(0);
		
		Mouse::setCursorMode(window, CursorState::Disabled);
		
		srand(time(0));
		
		
		Shader unlitShader(Resources::Get("Shaders/unlit.vert"),
					  Resources::Get("Shaders/unlit.frag"));
		Shader litShader(Resources::Get("Shaders/shader.vert"),
						 Resources::Get("Shaders/shader.frag"));
		Shader normalsShader(Resources::Get("Shaders/unlit.vert"),
							 Resources::Get("Shaders/unlit.frag"));
		
		Texture container(Resources::Get("Textures/container.jpg"));
		Texture wall(Resources::Get("Textures/wall.jpg"));
		
		ObjectLoader homerLoader(Resources::Get("Objects/homer.obj"));
		ObjectLoader monkeyLoader(Resources::Get("Objects/Monkey.obj"));
		ObjectLoader bunnyLoader(Resources::Get("Objects/stanford-bunny.obj"));
		ObjectLoader teapotLoader(Resources::Get("Objects/teapot.obj"));
		ObjectLoader dragonLoader(Resources::Get("Objects/Dragon.obj"));
		ObjectLoader wCubeLoader(Resources::Get("Objects/Something.obj"));
		
		MeshRenderer dragon(dragonLoader.LoadAsMesh(), &normalsShader,
							Transform(glm::vec3(0, -2, 0), glm::vec3(0, 60, 0), glm::vec3(.8)));
		dragon.color = glm::vec4(0.5, 0.5, 1, 1);
		MeshRenderer suzanne(monkeyLoader.LoadAsMesh(), &normalsShader,
							 Transform(glm::vec3(2.5, 0, .5), glm::vec3(0), glm::vec3(.8)));
		suzanne.color = glm::vec4(0.5, 1, 0.5, 1);
		MeshRenderer teapot(teapotLoader.LoadAsMesh(), &normalsShader,
							Transform(glm::vec3(1.7, -2, 2.2), glm::vec3(0), glm::vec3(.8)));
		teapot.color = glm::vec4(1);
		MeshRenderer wCube(wCubeLoader.LoadAsMesh(), &normalsShader,
						   Transform(glm::vec3(2, -2, 4), glm::vec3(0, -80, 0), glm::vec3(1.5)));
		wCube.color = glm::vec4(1);
		
		
		Camera camera(Camera::Perspective);
		Camera::set_main(&camera);
		camera.position = glm::vec3(0, 0, 1);
		camera.rotation = glm::vec3(0, 0, 0);
		camera.set_depthPlanes(0.1f, 100000);
		camera.size = glm::vec2(5);
		camera.fovy = 90;
		const float speed(5);
		const float sensitivity(0.1f);
		camera.updateCamera();
		
		// delta time shit
		float timeSinceLastFrame(glfwGetTime());
		float deltaTime(0);
		float timeScale(1);
		
		// main loop
		while (!glfwWindowShouldClose(window))
		{
			// delta time
			deltaTime = (glfwGetTime() - timeSinceLastFrame) * timeScale;
			timeSinceLastFrame = glfwGetTime();
			
			
			// INPUT
			if (Input::getKeyState(window, GLFW_KEY_ESCAPE) == KeyState::Press)
			{
				if (Mouse::getCursorMode(window) == CursorState::Disabled)
					Mouse::setCursorMode(window, CursorState::Normal);
				
				else if (Mouse::getCursorMode(window) == CursorState::Normal)
					Mouse::setCursorMode(window, CursorState::Disabled);
				
				timeScale = !timeScale;
			}
			
			
			if (Input::getKeyState(window, GLFW_KEY_TAB) == KeyState::Hold)
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			else if (Input::getKeyState(window, GLFW_KEY_TAB) == KeyState::Off)
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			
			// movement
			float toMove = speed * deltaTime;
			
			if (Input::getKeyState(window, GLFW_KEY_LEFT_SHIFT) == KeyState::Hold) toMove *= 2;
			
			if (Input::getKeyState(window, GLFW_KEY_W) == KeyState::Hold)
				camera.position += toMove * camera.get_direction();
			if (Input::getKeyState(window, GLFW_KEY_S) == KeyState::Hold)
				camera.position -= toMove * camera.get_direction();
			if (Input::getKeyState(window, GLFW_KEY_A) == KeyState::Hold)
				camera.position -= toMove * camera.get_right();
			if (Input::getKeyState(window, GLFW_KEY_D) == KeyState::Hold)
				camera.position += toMove * camera.get_right();
			if (Input::getKeyState(window, GLFW_KEY_SPACE) == KeyState::Hold)
				camera.position.y += toMove;
			if (Input::getKeyState(window, GLFW_KEY_LEFT_CONTROL) == KeyState::Hold)
				camera.position.y -= toMove;
			
			glm::vec2 cursorOffset = Mouse::getMouseOffset(window);
			camera.rotation.y += cursorOffset.x * sensitivity * timeScale;
			camera.rotation.x += -cursorOffset.y * sensitivity * timeScale;
			
			if (camera.rotation.x > 89.0f)
				camera.rotation.x = 89.0f;
			if (camera.rotation.x < -89.0f)
				camera.rotation.x = -89.0f;
			
			camera.updateCamera();
			
			
			// RENDERING
			// 0. reset the screen buffer
			glClearColor(0, 0, 0, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			dragon.draw(window);
			suzanne.draw(window);
			teapot.draw(window);
//			wCube.draw(window);
			
			
			
			// mouse
			Mouse::mouse_move_callback(window);
			
			// EVENTS AND BUFFER
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		
		
		glfwTerminate();
		return 0;
	}
}


int main()
{
	return engine::main();
}
