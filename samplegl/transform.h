#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Transform {
public:
	glm::mat4 ModelTransform;
public:
	Transform() {
		translation = new glm::vec3(0.0f, 0.0f, 0.0f);
		rotation = new glm::vec3(0.0f, 0.0f, 0.0f);
		scale = new glm::vec3(1.0f, 1.0f, 1.0f);
	}
	~Transform() {
		delete translation;
		delete rotation;
		delete scale;
	}
	inline glm::mat4 GetTransform() {
		glm::mat4 translationMatrix;
		glm::mat4 rotationMatrix;
		glm::mat4 scaleMatrix;
	
		scaleMatrix = glm::scale(scaleMatrix,*scale);
		translationMatrix = glm::translate(translationMatrix, *translation);
		rotationMatrix = glm::rotate(rotationMatrix, rotation->x, glm::vec3(1.0f, 0.0f, 0.0f));
		rotationMatrix = glm::rotate(rotationMatrix, rotation->y, glm::vec3(0.0f, 1.0f, 0.0f));
		rotationMatrix = glm::rotate(rotationMatrix, rotation->z, glm::vec3(0.0f, 0.0f, 1.0f));
		ModelTransform = scaleMatrix * rotationMatrix * translationMatrix;
		return ModelTransform;
	}
	inline glm::vec3*GetTranslate() {
		return translation;
	}
	inline void SetTranslation (glm::vec3*transform) {
		delete this->translation;
		this->translation = transform;
	}
	inline glm::vec3*GetRotation() {
		return rotation;
	}
	inline void SetRotation(glm::vec3 *rotation) {
		delete this->rotation;
		this->rotation = rotation;
	}
	inline glm::vec3*GetScale() {
		return scale;
	}
	inline void SetScale(glm::vec3*scale) {
		delete this->scale;
		this->scale = scale;
	}

private:
	glm::vec3*translation;
	glm::vec3*rotation;
	glm::vec3*scale;
};