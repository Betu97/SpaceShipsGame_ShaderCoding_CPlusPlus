#include "GameObject.h"
#include "game.h"
#include "GameObjectPlayer.h"

void GameObjectPlayer::render() {

	Game* g = Game::instance;
	speed = 0.8;

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

void GameObjectPlayer::update(float dt) {

	Game* g = Game::instance;

	double pitch_speed = dt * 0.02;
	double roll_speed = dt * 0.03;

	this->mesh->collision_model->setTransform(this->model.m);
	
	if (g->keystate[SDL_SCANCODE_W] || g->keystate[SDL_SCANCODE_UP]) {
		this->model.rotateLocal(-dt*pitch_speed, Vector3(1, 0, 0));
	}
	if (g->keystate[SDL_SCANCODE_S] || g->keystate[SDL_SCANCODE_DOWN]) {
		this->model.rotateLocal(dt*pitch_speed, Vector3(1, 0, 0));
	}
	if (g->keystate[SDL_SCANCODE_A] || g->keystate[SDL_SCANCODE_LEFT]) {
		this->model.rotateLocal(-dt*roll_speed, Vector3(0, 0, 1));
	}
	if (g->keystate[SDL_SCANCODE_D] || g->keystate[SDL_SCANCODE_RIGHT]) {
		this->model.rotateLocal(dt*roll_speed, Vector3(0, 0, 1));
	}

	//if (g->keystate[SDL_SCANCODE_SPACE]) {
		Vector3 f = this->model.frontVector().normalize();
		float speed_dt = -dt * this->speed * 1.5;
		this->model.traslate(f.x*speed_dt, f.y*speed_dt, f.z*speed_dt);
	//}

}

/*Mesh* GameObjectPlayer::getMesh() {
	return this->mesh;
}

void GameObjectPlayer::setMesh(Mesh* change) {
	this->mesh = change;
}*/