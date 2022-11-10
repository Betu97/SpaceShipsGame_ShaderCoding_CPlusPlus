#pragma once

#include "includes.h"
#include <string>
#include <map>
#include <unordered_map>
#include "mesh.h"
#include "texture.h"
#include "shader.h"


class ResourceManager{
private:
	std::unordered_map<std::string, Mesh*>m_meshes;
	std::unordered_map<std::string, Texture*>m_textures;
	std::unordered_map<std::string, Shader*>m_shaders;
public:

	ResourceManager();
	~ResourceManager();

	//carga recursos a la memoria
	void loadMesh(const std::string, const std::string);
	void loadTexture(const std::string, const std::string);
	void loadShader(const std::string, const std::string, const std::string);

	//descarga recursos de la memoria
	void unloadMesh(const std::string);
	void unloadTexture(const std::string);
	void unloadShader(const std::string);

	//getters para los recursos
	Mesh*getMesh(const std::string);
	Texture*getTexture(const std::string);
	Shader*getShader(const std::string);
};


