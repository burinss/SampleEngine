#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <assimp/matrix4x4.h>

class Transform {
private:
	glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
public:
	glm::mat4 ModelTransform;
public:
	Transform() {

	}
	~Transform() {
	}
	glm::mat4 GetTransform() {
		glm::mat4 translationMatrix;
		glm::mat4 rotationMatrix;
		glm::mat4 scaleMatrix;

		scaleMatrix = glm::scale(scaleMatrix,scale);
		translationMatrix = glm::translate(translationMatrix, translation);
		rotationMatrix=glm::yawPitchRoll(glm::radians(rotation.y), glm::radians(rotation.z), glm::radians(rotation.x));
		ModelTransform = glm::scale(scaleMatrix, scale) * glm::yawPitchRoll(glm::radians(rotation.y), glm::radians(rotation.z), glm::radians(rotation.x)) *  glm::translate(translationMatrix, translation);
		return ModelTransform;
	}
	inline glm::vec3 GetTranslation() {
		return translation;
	}
	inline void SetTranslation (glm::vec3 translation) {
		this->translation = translation;
	}
	inline glm::vec3 GetRotation() {
		return rotation;
	}
	inline void SetRotation(glm::vec3 rotation) {
		this->rotation = rotation;
	}
	inline glm::vec3 GetScale() {
		return scale;
	}
	inline void SetScale(glm::vec3 scale) {
		this->scale = scale;
	}
	static inline glm::mat4 aiMatrix4x4ToGlm(aiMatrix4x4* from)
	{
		glm::mat4 to;


		to[0][0] = from->a1; to[0][1] = from->b1;  to[0][2] = from->c1; to[0][3] = from->d1;
		to[1][0] = from->a2; to[1][1] = from->b2;  to[1][2] = from->c2; to[1][3] = from->d2;
		to[2][0] = from->a3; to[2][1] = from->b3;  to[2][2] = from->c3; to[2][3] = from->d3;
		to[3][0] = from->a4; to[3][1] = from->b4;  to[3][2] = from->c4; to[3][3] = from->d4;


		return to;
	}
};