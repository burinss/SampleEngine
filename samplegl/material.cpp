//#include <string>
//#include <fstream>
//#include <sstream>
//#include <iostream>
//#include <vector>
//#include <tuple>
//
//#include <glad/glad.h>
//#include "texture.h"
//#include "material.h"
//#include "shader.h"
//
//
//
//
//Material::Material()
//{
//
//}
//
//
//Material::~Material()
//{
//
//}
//
//
//void Material::addTexture(std::string uniformName, Texture texObj)
//{
//	this->texList.push_back(std::tuple<std::string, Texture>(uniformName, texObj));
//}
//
//
//void Material::setShader(Shader& shader)
//{
//	this->matShader = shader;
//}
//
//
//void Material::renderToShader()
//{
//	this->matShader.use();
//
//	std::cout << "texList Size : " << this->texList.size() << std::endl;
//
//	for (GLuint i = 0; i < this->texList.size(); i++)
//	{
//		std::string currentUniformName = std::get<0>(this->texList[i]);
//		Texture currentTex = std::get<1>(this->texList[i]);
//
//		glActiveTexture(GL_TEXTURE0 + i);
//		currentTex.useTexture();
//		this->matShader.setInt(currentUniformName.c_str(),i);
//	}
//}