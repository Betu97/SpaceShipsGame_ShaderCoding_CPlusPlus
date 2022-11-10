#include "GameObject.h"
#include "game.h"
#include "GameObjectMesh.h"

void GameObjectMesh::render() {

	Game* g = Game::instance;

	//create our mvp
	Matrix44 mvp = this->getGlobalMatrix() * g->scene->camera->viewprojection_matrix;
	//create normal matrix
	Matrix44 inverse_m = model;
	inverse_m.inverse();
	Matrix44 normal_m = inverse_m.transpose();
	//light position
	Vector3 light_pos(100.0f, 100.0f, 100.0f);
	
	//enable shader and set uniforms
	shader->enable();
	shader->setMatrix44("u_mvp", mvp);
	shader->setMatrix44("u_normal_matrix", normal_m );
	shader->setUniform3("u_light", light_pos);
	shader->setTexture("u_texture_diffuse", texture);


	//call render function for mesh, passing shader as param
	//mesh->render() binds the relevant attributes, and drawing code
	mesh->render(GL_TRIANGLES,shader);
	
	//disable the shader
	shader->disable();
	
	//disable blending to draw text on top
    glDisable( GL_BLEND );
	for (int i = 0; i < this->children.size(); i++) {
		this->children[i]->render();
	}


}
void GameObjectMesh::update(float dt) {
	this->mesh->collision_model->setTransform(this->model.m);
}