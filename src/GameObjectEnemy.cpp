#include "GameObject.h"
#include "game.h"
#include "GameObjectEnemy.h"

void GameObjectEnemy::render() {

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
void GameObjectEnemy::update(float dt) {
	Game* g = Game::instance;
	Vector3 object_pos(this->model.m[12],this->model.m[13],this->model.m[14]);
	
	Vector3 f = this->model.frontVector().normalize();
	Vector3 plane_normal = f.cross(this->model.rightVector().normalize());

	Vector3 to_target = (g->waypoints[w] - object_pos);
	to_target = to_target.normalize();
	
	float angle = acos(to_target.dot(f));
	if (abs(angle) > 0.01) {
		
		Vector3 axis = to_target.cross(f);
		Matrix44 inv = this->model;
		inv.inverse();
		Vector3 rot_axis = inv.rotateVector(axis);
		this->model.rotateLocal(-0.005, rot_axis);
	}

	
	float distance = (g->waypoints[w] - object_pos).length();
	this->model.traslate(-f.x*dt, -f.y*dt, -f.z*dt);
	Vector3 new_position(this->model.m[12], this->model.m[13], this->model.m[14]);
	float distanceMoved = (object_pos - new_position).length();
	if (distanceMoved >= distance) {
		if (w == 25) {
			w = 0;
		}
		else {
			w++;
		}
	}

	this->mesh->collision_model->setTransform(this->model.m);

}
/*
Mesh* GameObjectPlayer::getMesh() {
	return this->mesh;
}

void GameObjectPlayer::setMesh(Mesh* change) {
	this->mesh = change;
}*/