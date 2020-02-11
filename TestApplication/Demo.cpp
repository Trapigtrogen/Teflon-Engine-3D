#include "Demo.h"

Demo::Demo() {}

Demo::~Demo() {}

int main() {
	engine::Window window;
	engine::GraphicsSystem graphics;

	GLFWwindow* app = window.CreateWindow(1920/2, 1080/2);
	GLuint spriteShader = graphics.CreateShader(0);
	//GLuint cubeShader = graphics.CreateShader(1);

	int texture = graphics.loadTexture((char*)"wall.jpg");

	int rotX = 0;
	int rotY = 0;
	int rotZ = 0;

	// render loop
	while (!glfwWindowShouldClose(app))
	{
		// render
		graphics.ClearScreen(0.2f, 0.3f, 0.3f, false);

		// draw
		graphics.DrawSprite(spriteShader, texture);
		//graphics.DrawCube(cubeShader, texture);
		//graphics.transform(spriteShader, (float)glfwGetTime(), 0.0f, 0.0f, 0.0f, rotX, rotY, rotZ, 1.0f);
		//graphics.moveCamera();

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(app);
		glfwPollEvents();

		rotX++;
		rotZ--;
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	glfwTerminate();
	return 0;
}