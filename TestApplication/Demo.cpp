#include "Demo.h"

Demo::Demo() {}

Demo::~Demo() {}

int main() {
	engine::Window window;
	engine::GraphicsSystem graphics;

	int w = 1920 / 2;
	int h = 1080 / 2;
	GLFWwindow* app = window.CreateWindow(w, h);
	glEnable(GL_DEPTH_TEST);
	GLuint cubeShader = graphics.CreateShader("Assets/vertexShader.txt", "Assets/fragmentShader.txt");
	int texture = graphics.loadTexture((char*)"Assets/wall.jpg");

	int rotX = 1;
	int rotY = 1;
	int rotZ = 0;

	// render loop
	while (!glfwWindowShouldClose(app)) {
		// render
		graphics.ClearScreen(app, 0.2f, 0.2f, 0.22f, true);

		// draw
		graphics.DrawCube(cubeShader, texture);
		graphics.transform(cubeShader, (float)(glfwGetTime() / 2.0f), sin(glfwGetTime() / 2.0f), 0.0f, 0.0f, rotX, rotY, rotZ, 0.5f);

		graphics.DrawCube(cubeShader, texture);
		graphics.transform(cubeShader, (float)(glfwGetTime() / 2.0f), 0.0f, sin(glfwGetTime() / 2.0f), 0.0f, rotX, rotY, rotZ, 0.5f);
		
		graphics.DrawCube(cubeShader, texture);
		graphics.transform(cubeShader, (float)(glfwGetTime() / 2.0f), -1.5f, -1.0f, -1.0f, rotX, rotY, rotZ, 0.5f);

		//graphics.moveCamera();

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(app);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	glfwTerminate();
	return 0;
}