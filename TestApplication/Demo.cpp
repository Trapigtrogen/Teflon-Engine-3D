#include "Demo.h"

Demo::Demo() {}

Demo::~Demo() {}

int main() {
	// Default sprite information
	float size = 1.0f;
	float dx = -0.5f; //starting corner X
	float dy = -0.5f; //starting corner Y
	float depth = 0.0f; // Z-index

	// Default sprite vertice coordinates
	GLfloat spriteVertices[18] = {
		dx + 0.0f,  dy + size, depth,
		dx + 0.0f, dy + 0.0f, depth,
		dx + size, dy + 0.0f, depth,
		dx + size, dy + size, depth,
		dx + size, dy + 0.0f, depth,
		dx + 0.0f,  dy + size, depth
	};

	// Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
	GLfloat cubeVertices[] = {
		-1.0f,-1.0f,-1.0f, // triangle 1 : begin
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f, // triangle 1 : end
		1.0f, 1.0f,-1.0f, // triangle 2 : begin
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f, // triangle 2 : end
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f
	};

	engine::Window window;
	engine::GraphicsSystem graphics;

	GLFWwindow* app = window.CreateWindow(1920/2, 1080/2);
	int spriteShader = graphics.CreateShader(spriteVertices);
	int cubeShader = graphics.CreateShader(cubeVertices);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(app))
	{
		// input
		//app.processInput(app);

		// render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw rectangle
		graphics.DrawSprite(spriteShader);
		//graphics.DrawCube(cubeShader);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(app);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}