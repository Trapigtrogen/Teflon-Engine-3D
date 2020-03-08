#include "Demo.h"

Demo::Demo() {}

Demo::~Demo() {}

int main() {
	engine::Window window;
	engine::GraphicsSystem graphics;

	int w = 1920 / 2;
	int h = 1080 / 2;

	GLFWwindow* app = window.CreateWindow();
	glEnable(GL_DEPTH_TEST);

	engine::Shader cubeShader("Assets/vertexShader.txt", "Assets/fragmentShader.txt");

	int texture = graphics.loadTexture((char*)"Assets/wall.jpg");
	int texture2 = graphics.loadTexture((char*)"Assets/wall2.jpg");

	float cameraSpeedDefault = 1.0f;
	float cameraSpeed = 0;
	int rotX = 1;
	int rotY = 1;
	float pitch = 0.0f, yaw = 0.0f, roll = 0.0f;

	// render loop
	while (!glfwWindowShouldClose(app)) {
		float deltaTime = window.functions.DeltaTime();

		// render
		graphics.ClearScreen(app, 0.2f, 0.2f, 0.22f, true);

		// draw and move objects
		graphics.DrawCube(cubeShader, texture);
		graphics.transform(cubeShader, (float)(glfwGetTime() / 2.0f), sin(glfwGetTime() / 2.0f), 0.0f, 0.0f, rotX, rotY, 0, 0.5f);
		graphics.DrawCube(cubeShader, texture2);
		graphics.transform(cubeShader, (float)(glfwGetTime() / 2.0f), 0.0f, sin(glfwGetTime() / 2.0f), 1.5f, rotX, -rotY, 0, 0.5f);
		graphics.DrawCube(cubeShader, texture);
		graphics.transform(cubeShader, (float)(glfwGetTime() / 2.0f), -1.5f, -1.0f, -1.0f, -rotX, rotY, 0, 0.5f);


		// Input
		// Move camera
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

		// Faster movement
		if (window.input.GetKey(GLFW_KEY_LEFT_SHIFT))
			cameraSpeed = cameraSpeedDefault * 3.0f * deltaTime;
		else cameraSpeed = cameraSpeedDefault * deltaTime;

		// Rotate camera (not working)
		if (window.input.GetKey(GLFW_KEY_I))
			pitch--;

		if (window.input.GetKey(GLFW_KEY_K))
			pitch++;

		if (window.input.GetKey(GLFW_KEY_J))
			yaw--;

		if (window.input.GetKey(GLFW_KEY_L))
			yaw++;

		if (window.input.GetKey(GLFW_KEY_O))
			roll++;

		if (window.input.GetKey(GLFW_KEY_U))
			roll--;

		//graphics.RotateCamera(pitch, yaw, roll);

		window.input.ProcessInput();

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(app);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	glfwTerminate();
	return 0;
}