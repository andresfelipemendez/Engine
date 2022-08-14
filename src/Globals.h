//
// Created by Andres on 27/06/22.
//

#ifndef ENGINE_GLOBALS_H
#define ENGINE_GLOBALS_H

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
	};
}

#endif //ENGINE_GLOBALS_H
