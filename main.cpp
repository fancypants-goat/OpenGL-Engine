#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <bits/stdc++.h>
#include <vector>
#include <glm/glm.hpp>


#include "mesh.h"
#include "shader.h"
#include "vertex.h"
#include "camera.h"
#include "resources.h"
#include "input.h"
#include "transform.h"
#include "mesh_group.h"


using namespace std;


namespace engine {
	vector <Vertex> indexedVertices
			{
					Vertex { // front top right
							glm::vec3(0.5f, 0.5f, 0.5f),
							glm::vec3(0, 0, 0),
							glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
							glm::vec2(1.0f, 1.0f)
					},
					Vertex { // front top left
							glm::vec3(-0.5f, 0.5f, 0.5f),
							glm::vec3(0, 0, 0),
							glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
							glm::vec2(0.0f, 1.0f)
					},
					Vertex { // front bottom left
							glm::vec3(-0.5f, -0.5f, 0.5f),
							glm::vec3(0, 0, 0),
							glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
							glm::vec2(0.0f, 0.0f)
					},
					
					Vertex { // front bottom right
							glm::vec3(0.5f, -0.5f, 0.5f),
							glm::vec3(0, 0, 0),
							glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
							glm::vec2(1.0f, 0.0f)
					},
					
					Vertex { // back top right
							glm::vec3(0.5f, 0.5f, -0.5f),
							glm::vec3(0, 0, 0),
							glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
							glm::vec2(1.0f, 1.0f)
					},
					Vertex { // back top left
							glm::vec3(-0.5f, 0.5f, -0.5f),
							glm::vec3(0, 0, 0),
							glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
							glm::vec2(0.0f, 1.0f)
					},
					Vertex { // back bottom left
							glm::vec3(-0.5f, -0.5f, -0.5f),
							glm::vec3(0, 0, 0),
							glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
							glm::vec2(0.0f, 0.0f)
					},
					
					Vertex { // back bottom right
							glm::vec3(0.5f, -0.5f, -0.5f),
							glm::vec3(0, 0, 0),
							glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
							glm::vec2(1.0f, 0.0f)
					}
			};
	vector<unsigned int> indices {
			1, 2, 3, 0, 1, 3, // front
			4, 5, 6, 4, 6, 7, // back
			2, 3, 6, 3, 6, 7, // bottom
			0, 1, 4, 1, 4, 5, // top
			1, 2, 6, 1, 5, 6, // left
			0, 3, 7, 0, 4, 7, // right
	};
	
	
	void framebuffer_size_callback(GLFWwindow *window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
	
	float randomFloat(float min, float max)
	{
		float randomFloat = min + static_cast<float>(rand()) / (RAND_MAX / (max - min));
		return randomFloat;
	}
	
	int createCubeBatch(MeshGroup *group, int batchSize, float minBorder, float maxBorder)
	{
		glm::vec3 p, r, s;
		int count (0);
		for (count = 0; count < batchSize; count++)
		{
			p = glm::vec3(randomFloat(minBorder, maxBorder), randomFloat(minBorder, maxBorder), randomFloat(minBorder, maxBorder));
			r = glm::vec3(randomFloat(0, 360), randomFloat(0, 360), randomFloat(0, 360));
			s = glm::vec3(randomFloat(0.7, 1.3));
			group->addTransform(Transform(p, r, s));
		}
		
		group->upload();
		
		return count;
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
		
		Shader shader(Resources::Get("Shaders/rainbow.vert").c_str(),
					  Resources::Get("Shaders/rainbow.frag").c_str());
		Texture texture(Resources::Get("Textures/container.jpg").c_str());
		
		Mesh mesh(&shader, &texture, indexedVertices, indices);
		
		// load all transforms
		
		
		const int cubeCount = 2'000'000;
		int currentCubeCount (0);
		const int batchSize = 200000;
		const float minBorder (-1000);
		const float maxBorder (1000);
		
		MeshGroup group(&mesh);
		
		currentCubeCount += createCubeBatch(&group, batchSize, minBorder, maxBorder);
		
		Camera camera(Camera::Perspective);
		camera.position = glm::vec3(0, 0, 0);
		camera.set_depthPlanes(0.1f, 100000);
		camera.size = glm::vec2(8, 8);
		camera.fovy = 90;
		const float speed(5);
		const float sensitivity(0.1f);
		
		// delta time shit
		float timeSinceLastFrame(glfwGetTime());
		float deltaTime(0);
		float timeScale(1);
		
		// main loop
		while (!glfwWindowShouldClose(window))
		{
			if (currentCubeCount < cubeCount)
			{
				currentCubeCount += createCubeBatch(&group, batchSize, minBorder, maxBorder);
			}
			
			// delta time
			deltaTime = (glfwGetTime() - timeSinceLastFrame) * timeScale;
			timeSinceLastFrame = glfwGetTime();
			// mouse
			Mouse::mouse_move_callback(window);
			
			
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
			camera.rotation.x -= cursorOffset.y * sensitivity * timeScale;
			
			if (camera.rotation.x > 89.0f)
				camera.rotation.x = 89.0f;
			if (camera.rotation.x < -89.0f)
				camera.rotation.x = -89.0f;
			
			camera.updateCamera();
			
			
			// RENDERING
			// 0. reset the screen buffer
			glClearColor(0, 0, 0, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			glm::ivec2 viewport(0);
			glfwGetWindowSize(window, &viewport.x, &viewport.y);
			
			mesh.shader->uniformmat4("camera", false, camera.cameraProjection(viewport));
			
			group.draw();
			
			
			// mouse
			cursorOffset = glm::vec2(0);
			
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
