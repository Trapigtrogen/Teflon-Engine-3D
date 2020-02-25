#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <GLFW/glfw3.h> 

namespace engine {
	class Functionality {
	public:
		Functionality();
		~Functionality();

		float DeltaTime();

		int getRandomInt(int start, int end);
		float getRandomFloat(float start, int end);

		std::string loadFile(const std::string fileName);
		void writeFile(const std::string fileName, const std::string string);
	private:
		float deltaTime = 0.0f;	// Time between current frame and last frame
		float lastFrame = 0.0f; // Time of last frame
	};
}