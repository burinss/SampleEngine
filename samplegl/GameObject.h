#pragma once
#include <vector>

class GameObject {
private:
	std::vector<GameObject*>*child;
public:
	GameObject() {
		child = new std::vector<GameObject*>();
	}
	~GameObject()
	{
		for (GameObject children : child->begin) {
			children.~GameObject();
		}
		delete child;
	}
	void add(GameObject*child) {
		this->child->push_back(child);
	}
	void input() {
		for (GameObject children : child->begin) {
			children.input();
		}
	}
	void update() {
		for (GameObject children : child->begin) {
			children.update();
		}
	}
	void render() {
		for (GameObject children : child->begin) {
			children.render();
		}
	}
};