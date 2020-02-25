#include <GLFW/glfw3.h> 

namespace engine {
	class InputManager {
	public:
		InputManager();
		~InputManager();

		void ProcessInput();
		bool GetKey(int keyCode);

		void SetWindow(GLFWwindow* appWindow);
	private:
		GLFWwindow* window;
	};
}