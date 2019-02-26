//#include "RenderEngine.h"
//
//class RenderEngine {
//private:
//	static Camera*currentCamera;
//public:
//	static void SetCamera(Camera*NewCamera) {
//		if (currentCamera)
//			delete currentCamera;
//		currentCamera = NewCamera;
//	}
//	static inline Camera* GetCamera() {
//		return currentCamera;
//	}
//	static void AddObj(CGeometryNode*node) {
//		scene.AddChild(node);
//	}
//	static void Render() {
//		scene.Draw();
//	}
//	inline static void Clear() {
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	}
//	static void Init() {
//		currentShader = new Shader("vertex.vs", "fragment.fs");
//		currentShader->use();
//		//mainCamera = new Camera();
//
//		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
//		glEnable(GL_DEPTH_TEST);
//		glEnable(GL_CULL_FACE);
//		glFrontFace(GL_CW);
//		glCullFace(GL_BACK);
//
//		glEnable(GL_FRAMEBUFFER_SRGB);
//	}
//	static void Terminate() {
//		glfwTerminate();
//	}
//public:
//	static Shader*currentShader;
//	static CSceneNode scene;
//};
//CSceneNode RenderEngine::scene;
//Camera*RenderEngine::currentCamera;
//Shader*RenderEngine::currentShader;