//#include "CScene.h"
//
//class CSceneNode : public Transform
//{
//public:
//	// constructor
//	CSceneNode() { }
//
//	// destructor - calls destroy
//	virtual ~CSceneNode() { Destroy(); }
//
//	// release this object from memory
//	void Release() { delete this; }
//
//	// update our scene node
//	virtual void Update(float dT)
//	{
//		// loop through the list and update the children
//		for (std::list<CSceneNode*>::iterator i = m_lstChildren.begin();
//			i != m_lstChildren.end(); i++)
//		{
//			(*i)->Update(dT);
//		}
//	}
//	// destroy all the children
//	void Destroy()
//	{
//		for (std::list<CSceneNode*>::iterator i = m_lstChildren.begin();
//			i != m_lstChildren.end(); i++)
//			(*i)->Release();
//
//		m_lstChildren.clear();
//	}
//	virtual void Draw() { };
//	// add a child to our custody
//	void AddChild(CSceneNode* pNode)
//	{
//		m_lstChildren.push_back(pNode);
//		pNode->parent = this;
//	}
//protected:
//	CSceneNode*parent;
//private:
//	std::list<CSceneNode*> m_lstChildren;
//};
//
//class CGeometryNode : public CSceneNode
//{
//public:
//	CGeometryNode(std::vector<Mesh> meshes) {
//		//this->meshes = meshes;
//		this->meshes = meshes;
//	}
//	~CGeometryNode() { }
//
//	void Update(float dT)
//	{
//		// Draw our geometry here! 
//		CSceneNode::Update(dT);
//	}
//	void Draw() {
//		glm::mat4 Model = parent->ModelTransform*GetTransform();
//		//glm::mat4 View = RenderEngine::GetCamera()->GetViewMatrix();
//		//glm::mat4 Perspective = glm::perspective(glm::radians(RenderEngine::GetCamera()->Zoom), ((float)Window::GetWidth() / (float)Window::GetHeight()), 0.1f, 100.0f);
//	//	RenderEngine::currentShader->setMat4("MVP", Model*View*Perspective);
//
//		for (unsigned int i = 0; i < meshes.size(); i++)
//			//this->meshes[i].Draw(*RenderEngine::currentShader);
//	}
//private:
//	std::vector<Mesh> meshes;
//};
