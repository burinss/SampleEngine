#pragma once
#include <vector>
#include <list>

//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
#include "mesh.h"
#include "transform.h"
#include "shader.h"
#include <iostream>

class CSceneNode : public Transform
{
public:
	// constructor
	CSceneNode() { }

	// destructor - calls destroy
	virtual ~CSceneNode() { Destroy(); }

	// release this object from memory
	void Release() { delete this; }

	// update our scene node
	virtual void Update(float dT)
	{
		// loop through the list and update the children
		for (std::list<CSceneNode*>::iterator i = m_lstChildren.begin();
			i != m_lstChildren.end(); i++)
		{
			(*i)->Update(dT);	
		}
	}
	// destroy all the children
	void Destroy()
	{
		for (std::list<CSceneNode*>::iterator i = m_lstChildren.begin();
			i != m_lstChildren.end(); i++)
			(*i)->Release();

		m_lstChildren.clear();
	}
	virtual void Draw(Shader*shader) {
		for (std::list<CSceneNode*>::iterator i = m_lstChildren.begin();
			i != m_lstChildren.end(); i++) {
			(*i)->Draw(shader);
		}
	};
	// add a child to our custody
	void AddChild(CSceneNode* pNode)
	{
		m_lstChildren.push_back(pNode);
		pNode->parent = this;
	}
protected:
	CSceneNode*parent;
private:
	std::list<CSceneNode*> m_lstChildren;
};

class CGeometryNode : public CSceneNode 
{
public:
	CGeometryNode(std::vector<Mesh> meshes) {
		//this->meshes = meshes;
		this->meshes = meshes;
		SetTranslation(new glm::vec3(0.0f, -1.75f, 0.0f));
		SetScale(new glm::vec3(0.2f, 0.2f, 0.2f));
		
	}
	~CGeometryNode() { }
	void Update(float dT)
	{
		// Draw our geometry here! 
		CSceneNode::Update(dT);
	}
	void Draw(Shader*shader) {
		glm::mat4 Model= /*parent->ModelTransform**/GetTransform();
		
		shader->setMat4("model",Model);

		for (unsigned int i = 0; i < meshes.size(); i++)
			this->meshes[i].Draw(*shader);
	}
private:
	std::vector<Mesh> meshes;
};
