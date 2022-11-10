#include "Scene.h"
#include "game.h"

Scene::Scene() {
	this->root = new GameObject();
}
Scene::~Scene() {
	this->root->clear();
	delete this->root;
}
void Scene::render() {
	this->root->render();
}
void Scene::update(float dt) {
	this->root->update(dt);
}
