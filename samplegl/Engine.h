#ifndef ENGINE_H
#define ENGINE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <AL/alut.h>
#include <ft2build.h>
#include FT_FREETYPE_H  
#define GLM_FORCE_SSE3
#define GLM_FORCE_SSSE3
#define GLM_FORCE_SSE41
#define GLM_FORCE_SSE42
#define GLM_FORCE_AVX
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "filesystem.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "shader_s.h"
#include "camera.h"
#include "model.h"
#include "interface.h"
#include <iostream>

using namespace std;
using namespace glm;

class Engine {
private:
	Engine() {
		
	}
	void Draw() {

	}
public:
	~Engine() {

	}
		
};
#endif