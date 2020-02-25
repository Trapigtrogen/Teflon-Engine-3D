#include <InputManager.h>

namespace engine {
	InputManager::InputManager() {}
	InputManager::~InputManager() {}

	void InputManager::ProcessInput() {
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
	}

	bool InputManager::GetKey(int keyCode) {
		return (glfwGetKey(window, keyCode) == GLFW_PRESS);
	}

	void InputManager::SetWindow(GLFWwindow* appWindow) {
		window = appWindow;
	}
}