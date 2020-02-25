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
	GLuint cubeShader2 = graphics.CreateShader("Assets/vertexShader.txt", "Assets/fragmentShader.txt");
	int texture = graphics.loadTexture((char*)"Assets/wall.jpg");
	int texture2 = graphics.loadTexture((char*)"Assets/wall2.jpg");

	float cameraSpeed = 0.01f;
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

		graphics.DrawCube(cubeShader, texture2);
		graphics.transform(cubeShader, (float)(glfwGetTime() / 2.0f), 0.0f, sin(glfwGetTime() / 2.0f), 1.5f, rotX, -rotY, rotZ, 0.5f);
		
		graphics.DrawCube(cubeShader2, texture);
		graphics.transform(cubeShader2, (float)(glfwGetTime() / 2.0f), -1.5f, -1.0f, -1.0f, -rotX, rotY, rotZ, 0.5f);

		//graphics.MoveCameraContinuous(0.0f, 0.0f, 0.0f);
		//graphics.MoveCamera(0.0f, 0.0f, 3.0f);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(app);
		glfwPollEvents();

		if (window.input.GetKey(GLFW_KEY_W))
			graphics.MoveCameraForwards(cameraSpeed);
		if (window.input.GetKey(GLFW_KEY_S))
			graphics.MoveCameraBackwards(cameraSpeed);
		if (window.input.GetKey(GLFW_KEY_A))
			graphics.MoveCameraLeft(cameraSpeed);
		if (window.input.GetKey(GLFW_KEY_D))
			graphics.MoveCameraRight(cameraSpeed);
		if (window.input.GetKey(GLFW_KEY_E))
			graphics.MoveCameraUp(cameraSpeed);
		if (window.input.GetKey(GLFW_KEY_Q))
			graphics.MoveCameraDown(cameraSpeed);

		window.input.ProcessInput();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	glfwTerminate();
	return 0;
}