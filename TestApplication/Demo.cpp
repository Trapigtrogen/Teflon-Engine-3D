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
	int texture2 = graphics.loadTexture((char*)"Assets/wall2.jpg");

	float cameraSpeedDefault = 1.0f;
	float cameraSpeed = 0;
	int rotX = 1;
	int rotY = 1;
	int rotZ = 0;

	// render loop
	while (!glfwWindowShouldClose(app)) {
		float deltaTime = window.functions.DeltaTime();

		// render
		graphics.ClearScreen(app, 0.2f, 0.2f, 0.22f, true);

		// draw
		graphics.DrawCube(cubeShader, texture);
		graphics.transform(cubeShader, (float)(glfwGetTime() / 2.0f), sin(glfwGetTime() / 2.0f), 0.0f, 0.0f, rotX, rotY, rotZ, 0.5f);
		graphics.DrawCube(cubeShader, texture2);
		graphics.transform(cubeShader, (float)(glfwGetTime() / 2.0f), 0.0f, sin(glfwGetTime() / 2.0f), 1.5f, rotX, -rotY, rotZ, 0.5f);
		graphics.DrawCube(cubeShader, texture);
		graphics.transform(cubeShader, (float)(glfwGetTime() / 2.0f), -1.5f, -1.0f, -1.0f, -rotX, rotY, rotZ, 0.5f);

		// Camra
		//graphics.MoveCamera(0.0f, 0.0f, 0.0f);
		//graphics.PositionCamera(0.0f, 0.0f, 3.0f);
		//graphics.RotateCameraContinuous(0.1f, 0.1f, 0.1f);

		// Input
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

		if (window.input.GetKey(GLFW_KEY_LEFT_SHIFT))
			cameraSpeed = cameraSpeedDefault * 3.0f * deltaTime;
		else cameraSpeed = cameraSpeedDefault * deltaTime;

		window.input.ProcessInput();

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(app);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	glfwTerminate();
	return 0;
}