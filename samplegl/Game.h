#pragma once
#ifndef GAME_H
#define GAME_H
#include "RenderEngine.h"
#include "window.h"
#include "Input.h"
#include "model.h"
#include <iostream>
#include "filesystem.h"
#include <string>
#include "camera.h"
#include <math.h>

class Game {
public:
	CGeometryNode*geometry;
	float deltaTime;
	Game() {

	}
	unsigned int TextureFromFile(const char *path, const string &directory, bool gamma)
	{
		string filename = string(path);
		//filename = directory + '/' + filename;

		unsigned int textureID;
		glGenTextures(1, &textureID);

		int width, height, nrComponents;
		unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
		if (data)
		{
			GLenum format;
			if (nrComponents == 1)
				format = GL_RED;
			else if (nrComponents == 3)
				format = GL_RGB;
			else if (nrComponents == 4)
				format = GL_RGBA;

			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			stbi_image_free(data);
		}
		else
		{
			std::cout << "Texture failed to load at path: " << path << std::endl;
			stbi_image_free(data);
		}

		return textureID;
	}
	void Init() {
		deltaTime = 0;
		Model*model=new Model(FileSystem::getPath("house/WoodenCabinObj.obj"));
		geometry = new CGeometryNode(model->GetMeshes());
		//RenderEngine::AddObj(geometry);

		vector<Vertex> vertices;
		Vertex*vertex = new Vertex;
		vertex->Position = glm::vec3(0.5f, 0.5f, 0.0f);
		
		vertex->TexCoords = glm::vec2(0.0f, 0.0f);
		vertices.push_back(*vertex);

		vertex = new Vertex;
		vertex->Position = glm::vec3(0.5f, -0.5f, 0.0f);
		vertex->TexCoords = glm::vec2(0.0f, 1.0f);
		vertices.push_back(*vertex);

		vertex = new Vertex;
		vertex->Position = glm::vec3(-0.5f, -0.5f, 0.0f);
		
		vertex->TexCoords = glm::vec2(1.0f, 1.0f);
		vertices.push_back(*vertex);

		vertex = new Vertex;
		vertex->Position = glm::vec3(-0.5f, 0.5f, 0.0f);
		
		vertex->TexCoords = glm::vec2(1.0f, 0.0f);
		vertices.push_back(*vertex);
		vertex = NULL;

		vector<unsigned int> indices;
		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(3);
		indices.push_back(1);
		indices.push_back(2);
		indices.push_back(3);
		
		vector<Texture> textures;

		Texture texture;
		texture.id = TextureFromFile("2.png",string(""),false);
		texture.type = "texture_diffuse";
		texture.path = "2.png";
		textures.push_back(texture);
		
			vector<Mesh> mesh;
			mesh.push_back(*new Mesh(vertices, indices, textures));
			CGeometryNode*padle = new CGeometryNode(mesh);
		RenderEngine::AddObj(padle);
		padle->SetScale(new glm::vec3(1.0f));
		RenderEngine::SetCamera(new Camera(glm::vec3(0.0f, 3.0f, 20.0f)));
		geometry->SetTranslation(new glm::vec3(0.0f, -1.75f, 1.0f));
		RenderEngine::currentShader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
		RenderEngine::currentShader->setFloat("lightRadius",15.0f);
		RenderEngine::currentShader->setFloat("compression", 2.0f);
		delete model;
	}
	void Input() {
		float offset = 5.0f;
		if (Input::GetDownKey(GLFW_KEY_ESCAPE))
		{
			Window::Close();
		}
		if (Input::GetDownKey(GLFW_KEY_W)) {
			RenderEngine::GetCamera()->ProcessKeyboard(FORWARD,deltaTime);
		}
		if (Input::GetDownKey(GLFW_KEY_S)) {
			RenderEngine::GetCamera()->ProcessKeyboard(BACKWARD, deltaTime);
		}
		if (Input::GetDownKey(GLFW_KEY_D)) {
			RenderEngine::GetCamera()->ProcessKeyboard(RIGHT, deltaTime);
		}
		if (Input::GetDownKey(GLFW_KEY_A)) {
			RenderEngine::GetCamera()->ProcessKeyboard(LEFT, deltaTime);
		}
		if (Input::GetDownKey(GLFW_KEY_UP)) {
			RenderEngine::GetCamera()->ProcessMouseMovement(0.0f, offset);
		}
		if (Input::GetDownKey(GLFW_KEY_DOWN)) {
			RenderEngine::GetCamera()->ProcessMouseMovement(0.1f, -offset);
		}
		if (Input::GetDownKey(GLFW_KEY_RIGHT)) {
			RenderEngine::GetCamera()->ProcessMouseMovement(offset,0.0f);
		}
		if (Input::GetDownKey(GLFW_KEY_LEFT)) {
			RenderEngine::GetCamera()->ProcessMouseMovement(-offset, 0.0f);
		}
		if (Input::GetDownKey(GLFW_KEY_Q)) {
			RenderEngine::GetCamera()->ProcessMouseScroll(0.1f);
		}
		if (Input::GetDownKey(GLFW_KEY_Z)) {
			RenderEngine::GetCamera()->ProcessMouseScroll(-0.1f);
		}
	}
	void Update() {
		static float rotate = 0.0f;
		static float red, green, blue;
		float currentFrame = glfwGetTime();
		static float lastFrame = 0.0f;
		static float time = 0;
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		if (time>0.01) {
			rotate += 0.01f;
			Window::SetTitle((char*)std::to_string(1/deltaTime).c_str());
			time = 0;
		}
		//geometry->SetRotation(new glm::vec3(0.0f, rotate, 0.0f));

		//RenderEngine::currentShader->setVec3("lightColor", glm::vec3((sin(rotate)), (cos(rotate)), (sin(rotate+0.5f))));
		time += deltaTime;

	}
	void Render() {
	}
};
#endif