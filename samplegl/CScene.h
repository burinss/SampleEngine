#pragma once
#include <vector>
#include <list>
#include <iostream>
#include "mesh.h"
#include "transform.h"
#include "shader.h"

#include "Physics.h"

class CSceneNode : public Transform 
{
public:
	// constructor
	CSceneNode() { 

	}

	// destructor - calls destroy
	virtual ~CSceneNode() { /*Destroy();*/ }

	// release this object from memory
	void Release() { delete this; }

	// update our scene node
	virtual void Update(bool drawable)
	{
		//this->drawable = drawable;
		// loop through the list and update the children
		for (std::list<CSceneNode*>::iterator i = m_lstChildren.begin();
			i != m_lstChildren.end(); i++)
		{
			(*i)->Update(drawable);
		}
	}
	// destroy all the children
	virtual void Destroy()
	{
		for (std::list<CSceneNode*>::iterator i = m_lstChildren.begin();
			i != m_lstChildren.end(); i++)
			(*i)->Release();

		m_lstChildren.clear();
	}
	virtual void Draw(Shader*shader) {
		if (drawable) {
			if (parent != nullptr) {
				GetTransform();
				ModelTransform *= parent->GetTransform();
			}
			else
				GetTransform();
			for (std::list<CSceneNode*>::iterator i = m_lstChildren.begin();
				i != m_lstChildren.end(); i++)
			{
				(*i)->Draw(shader);
			}
		}
	};
	// add a child to our custody
	CSceneNode* AddChild(CSceneNode*pNode,string name="Node",bool drawable=true)
	{
		mNumMeshes++;
		m_lstChildren.push_back(pNode);
		pNode->parent = this;
		pNode->drawable = drawable;
		//pNode->name = name;
		return pNode;
	}
public:
	bool drawable=true;
	string name;
	CSceneNode*parent;
	static unsigned int mNumMeshes;
protected:
	
private:
	std::list<CSceneNode*> m_lstChildren;
};
unsigned int CSceneNode::mNumMeshes;

class CGeometryNode : public CSceneNode , public PhysicsObject
{
public:
	CGeometryNode(Mesh mesh) {
		this->mesh=mesh;
		name = mesh.name;
	}
	~CGeometryNode() {

	}
	void Update(bool drawable)
	{
		this->drawable = drawable;
		
		// Draw our geometry here! 
		//CSceneNode::Update(drawable);
	}
	void Draw(Shader*shader) {
		shader->setMat4("model", parent->ModelTransform*ModelTransform);
		//for (unsigned int i = 0; i < meshes.size(); i++)
		//	this->meshes[i].Draw(*shader);
		mesh.Draw(*shader);
	}
	void Destroy() {
		//delete mesh;
	}
private:
	Mesh mesh;
};

