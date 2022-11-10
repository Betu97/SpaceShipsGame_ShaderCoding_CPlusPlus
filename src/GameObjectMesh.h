#pragma once

#include "includes.h"
#include "framework.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "GameObject.h"


class GameObjectMesh : public GameObject{
public:
	//Attributes of this class
	Mesh* mesh;
	Texture* texture;
	Shader* shader;
	Vector3 color;

	//overwritten virtual functions
	virtual void render();
	virtual void update(float dt);
};