#pragma once

#include "includes.h"
#include <string>
#include "framework.h"


class GameObject{
public:
	//some attributes
	std::string name;
	Matrix44 model;

	//virtual methods which will be overwritten
	virtual void render();
	virtual void update(float elapsed_time);
	/*virtual Mesh* getMesh();
	virtual void setMesh(Mesh* change);
	GameObjectPlayer* getPlayer();*/

	//modificar constructor de gameobject poara decir
	//parent = NULL;
	GameObject* parent;
	std::vector<GameObject*> children;
	//...
	void addChild(GameObject* obj);
	void removeChild(GameObject* obj);
	void clear();//you implement this!
	Matrix44 getGlobalMatrix(); //returns transform in world coordinates


};