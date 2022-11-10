#include "resourceManager.h"
#include "game.h"

ResourceManager::ResourceManager(){

}

ResourceManager::~ResourceManager(){

}

void ResourceManager::loadMesh(const std::string handle, const std::string path){
	Mesh* mesh = new Mesh();
	mesh ->loadASE(path.c_str());
	m_meshes[handle] = mesh;
}

void ResourceManager::unloadMesh(const std::string handle){
	//intenta encontrar la mesh en el mapa
	std::unordered_map<std::string, Mesh*>::iterator itr = m_meshes.find(handle);

	//comprueba que esta
	if(itr != m_meshes.end()){
		//encuentralo, eliminalo y borralo
		delete itr -> second;
		m_meshes.erase(itr);
	}
	else //printa un error y sal si no se ha encontrado
	{
		std::cout <<"no se han encontrado los recursos"<<handle<<std::endl;
		exit(0);
	}
}

Mesh*ResourceManager::getMesh(const std::string name){
	return m_meshes.at(name);
}

void ResourceManager::loadTexture(const std::string handle, const std::string path){
	Texture* texture = new Texture();
	texture ->load(path.c_str());
	m_textures[handle] = texture;
}

void ResourceManager::unloadTexture(const std::string handle){
	//intenta encontrar la mesh en el mapa
	std::unordered_map<std::string, Texture*>::iterator itr = m_textures.find(handle);

	//comprueba que esta
	if(itr != m_textures.end()){
		//encuentralo, eliminalo y borralo
		delete itr -> second;
		m_textures.erase(itr);
	}
	else //printa un error y sal si no se ha encontrado
	{
		std::cout <<"no se han encontrado los recursos"<<handle<<std::endl;
		exit(0);
	}
}

Texture*ResourceManager::getTexture(const std::string name){
	return m_textures.at(name);
}

void ResourceManager::loadShader(const std::string handle, const std::string pathvert, const std::string pathfrag){
	Shader* shader = new Shader();
	if( !shader->load(pathvert.c_str(),pathfrag.c_str() ) )
	{
		std::cout << "shader not found or error" << std::endl;
		exit(0);
	}else{
		m_shaders[handle] = shader;
	}
}
	
void ResourceManager::unloadShader(const std::string handle){
	//intenta encontrar la mesh en el mapa
	std::unordered_map<std::string, Shader*>::iterator itr = m_shaders.find(handle);

	//comprueba que esta
	if(itr != m_shaders.end()){
		//encuentralo, eliminalo y borralo
		delete itr -> second;
		m_shaders.erase(itr);
	}
	else //printa un error y sal si no se ha encontrado
	{
		std::cout <<"no se han encontrado los recursos"<<handle<<std::endl;
		exit(0);
	}
}

Shader*ResourceManager::getShader(const std::string name){
	return m_shaders.at(name);
}

