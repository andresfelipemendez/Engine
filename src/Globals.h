//
// Created by Andres on 27/06/22.
//

#ifndef ENGINE_GLOBALS_H
#define ENGINE_GLOBALS_H

#include <glm/glm.hpp>

struct GLFWwindow;

struct vec4
{
	float x;
	float y;
	float z;
	float w;
};

union color {

	float f[4];
	vec4 v;
	
};


namespace Globals {

	class Renderer {
	public:
		static GLFWwindow *window;
		static color clearColor;
		inline static int width = 800;
		inline static int height = 600;

		inline static float deltaTime;
		inline static double lastFrame;

		inline static float yaw;
		inline static float pitch;
		inline static glm::vec3 direction;
		inline static float lastX = width/2.0f, lastY = height / 2.0f;
		inline static glm::vec3 cameraRot = { 
			0.0f, // pitch
			0.0f, // yaw
			0.0f  // roll
		};
		inline static glm::vec3 cameraPos = { 0.0f, 0.0f, 3.0f };
		inline static glm::vec3 cameraFront = { 0.0f, 0.0f, -1.0f };
		inline static glm::vec3 cameraUp = { 0.0f, 1.0f, 0.0f };
		
		
	};
}

#endif //ENGINE_GLOBALS_H
