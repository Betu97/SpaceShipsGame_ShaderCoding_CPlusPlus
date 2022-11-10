#include "SceneParser.h"
#include "game.h"
#include <string>
#include <algorithm>

SceneParser::SceneParser(){

}

void SceneParser::parse(const char * name){
	TextParser file;

	Game* game = Game::instance;
	int waypy = 0;


	if (file.create(name) == false) {
		std::cout << "Could not open file" << std::endl;
	}

	file.seek("RESOURCES");
	int resources = file.getint();
	for(int i = 0; i<resources; i++){
		file.seek("RESOURCE");
		std::string resource = file.getword();
		std::string name;
		std::string path;
		if(resource == "MESH"){
			file.seek("NAME");
			name = file.getword();
			std::transform(name.begin(), name.end(), name.begin(), ::tolower);
			file.seek("PATH");
			path = file.getword();
			std::transform(path.begin(), path.end(), path.begin(), ::tolower);
			game->resource_manager->loadMesh(name,path);
		}else if(resource == "TEXTURE"){
			file.seek("NAME");
			name = file.getword();
			std::transform(name.begin(), name.end(), name.begin(), ::tolower);
			file.seek("PATH");
			path = file.getword();
			std::transform(path.begin(), path.end(), path.begin(), ::tolower);
			game->resource_manager->loadTexture(name,path);
		}else if(resource == "SHADER"){
			std::string path2;
			file.seek("NAME");
			name = file.getword();
			std::transform(name.begin(), name.end(), name.begin(), ::tolower);
			file.seek("PATH");
			path = file.getword();
			std::transform(path.begin(), path.end(), path.begin(), ::tolower);
			path2 = file.getword();
			std::transform(path2.begin(), path2.end(), path2.begin(), ::tolower);
			game->resource_manager->loadShader(name,path, path2);
		}
	}
	file.seek("OBJECTS");
	int objects = file.getint();
	for (int j = 0; j<objects; j++) {
		file.seek("OBJECT");
		std::string objectType = file.getword();
		std::string name;
		std::string mesh;
		std::string shader;
		std::string texture;
		float Ap;
		float Bp;
		float Cp;
		float As;
		float Bs;
		float Cs;
		float An;
		float Ar;
		float Br;
		float Cr;
		if (objectType == "GAMEOBJECTMESH" || objectType == "GAMEOBJECTENVIRONMENT" || objectType == "GAMEOBJECTENEMY" || objectType == "GAMEOBJECTPLAYER") {
			file.seek("NAME");
			name = file.getword();
			std::transform(name.begin(), name.end(), name.begin(), ::tolower);
			file.seek("MESH");
			mesh = file.getword();
			std::transform(mesh.begin(), mesh.end(), mesh.begin(), ::tolower);
			file.seek("SHADER");
			shader = file.getword();
			std::transform(shader.begin(), shader.end(), shader.begin(), ::tolower);
			file.seek("TEXTURE");
			texture = file.getword();
			std::transform(texture.begin(), texture.end(), texture.begin(), ::tolower);
			file.seek("POSITION");
			Ap = file.getfloat();
			Bp = file.getfloat();
			Cp = file.getfloat();
			file.seek("ROTATION");
			An = file.getfloat();
			Ar = file.getfloat();
			Br = file.getfloat();
			Cr = file.getfloat();
			file.seek("SCALE");
			As = file.getfloat();
			Bs = file.getfloat();
			Cs = file.getfloat();
			if (objectType == "GAMEOBJECTMESH"){
				GameObjectMesh* object = new GameObjectMesh();
				object->name = name;
				object->mesh = game->resource_manager->getMesh(mesh);
				object->shader = game->resource_manager->getShader(shader);
				object->texture = game->resource_manager->getTexture(texture);
				object->model.traslate(Ap, Bp, Cp);
				if (Ar != 0 || Br != 0 || Cr != 0) {
					object->model.rotate(An, Vector3(Ar, Br, Cr));
				}
				object->model.scale(As, Bs, Cs);
				object->mesh->setCollisionModel();
				game->scene->root->addChild(object);
			}
			else if(objectType == "GAMEOBJECTENEMY"){
				GameObjectEnemy* object = new GameObjectEnemy();
				object->name = name;
				object->mesh = game->resource_manager->getMesh(mesh);
				object->shader = game->resource_manager->getShader(shader);
				object->texture = game->resource_manager->getTexture(texture);
				object->model.traslate(Ap, Bp, Cp);
				object->w = waypy;
				waypy = waypy + 2;
				if (Ar != 0 || Br != 0 || Cr != 0) {
					object->model.rotate(An, Vector3(Ar, Br, Cr));
				}
				object->model.scale(As, Bs, Cs);
				object->mesh->setCollisionModel();
				game->scene->root->addChild(object);
			}
			else if(objectType == "GAMEOBJECTPLAYER") {
				GameObjectPlayer* object = new GameObjectPlayer();
				object->name = name;
				object->mesh = game->resource_manager->getMesh(mesh);
				object->shader = game->resource_manager->getShader(shader);
				object->texture = game->resource_manager->getTexture(texture);
				object->model.traslate(Ap, Bp, Cp);
				if (Ar != 0 || Br != 0 || Cr != 0) {
					object->model.rotate(An, Vector3(Ar, Br, Cr));
				}
				object->model.scale(As, Bs, Cs);
				object->mesh->setCollisionModel();
				game->scene->root->addChild(object);
			}
			else {
				GameObjectEnvironment* object = new GameObjectEnvironment();
				object->name = name;
				object->mesh = game->resource_manager->getMesh(mesh);
				object->shader = game->resource_manager->getShader(shader);
				object->texture = game->resource_manager->getTexture(texture);
				object->model.setTranslation(Ap,Bp,Cp);
				if (Ar != 0 || Br != 0 || Cr != 0) {
					object->model.rotate(An, Vector3(Ar, Br, Cr));
				}
				object->model.scale(As, Bs, Cs);
				game->scene->root->addChild(object);
			}
		}
	}
	file.seek("WAYPOINTS");
	int waypoints = file.getint();
	float Ae;
	float Be;
	float Ce;
	for (int k = 0; k < waypoints; k++) {
		file.seek("POSITION");
		Ae = file.getfloat();
		Be = file.getfloat();
		Ce = file.getfloat();
		game->waypoints.push_back(Vector3(Ae, Be, Ce));
	}
}