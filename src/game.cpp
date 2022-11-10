#include "game.h"
#include "utils.h"
#include "mesh.h"
#include "texture.h"
#include "rendertotexture.h"
#include "shader.h"
#include <string>
#include "SceneParser.h"


#include <cmath>

//some globals

float angle = 0;
bool pause = false;
bool collision = false;
bool final_collision = false;
RenderToTexture* rt = NULL;

Game* Game::instance = NULL;

Game::Game(SDL_Window* window)
{
	this->window = window;
	instance = this;

	// initialize attributes
	// Warning: DO NOT CREATE STUFF HERE, USE THE INIT 
	// things create here cannot access opengl
	SDL_GetWindowSize( window, &window_width, &window_height );
	std::cout << " * Window size: " << window_width << " x " << window_height << std::endl;

	keystate = NULL;
	mouse_locked = false;
}

//Here we have already GL working, so we can create meshes and textures
void Game::init(void)
{
	SceneParser* scene_parser = new SceneParser();
    std::cout << " * Path: " << getPath() << std::endl;
	scene = new Scene();
    //SDL_SetWindowSize(window, 50,50);

	//OpenGL flags
	glEnable( GL_CULL_FACE ); //render both sides of every triangle

	//Create resource manager
	resource_manager = new ResourceManager();

	//create our camera
	scene->camera = new Camera();
	scene->camera->lookAt(Vector3(0,10,50),Vector3(0,0,0), Vector3(0,1,0)); //position the camera and point to 0,0,0
	scene->camera->setPerspective(70.0f,(float)window_width/(float)window_height,0.1f,10000.0f); //set the projection, we want to be perspective

	//cargamos todos los recursos y objetos al resource_manager
	scene_parser->parse("src/level1.txt");	
	
	SDL_ShowCursor(!mouse_locked); //hide or show the mouse
}

//what to do when the image has to be draw
void Game::render(void)
{
	//set the clear color (the background color)
	glClearColor(0.0, 0.0, 0.0, 1.0);

	// Clear the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//update view and projection matrices, and push gl matrices for fixed pipeline rendering
	scene->camera->set();

	//*** Drawing code starts here ***
	scene->render();
	
	//*** Drawing code ends here ***

	//swap between front buffer and back buffer
	SDL_GL_SwapWindow(this->window);
}

void Game::update(double seconds_elapsed)
{
	double speed = seconds_elapsed * 100; //the speed is defined by the seconds_elapsed so it goes constant
	double enemySpeed = seconds_elapsed * 100;

	Vector3 player_pos(scene->root->children[2]->model.m[12], scene->root->children[2]->model.m[13], scene->root->children[2]->model.m[14]);
	Vector3 player_up(scene->root->children[2]->model.m[4], scene->root->children[2]->model.m[5], scene->root->children[2]->model.m[6]);
	scene->camera->eye = player_pos + scene->root->children[2]->model.frontVector().normalize() * 50;
	scene->camera->center = player_pos;
	scene->camera->up = player_up;
	scene->root->children[0]->model.setTranslation(scene->camera->eye.x, scene->camera->eye.y, scene->camera->eye.z);
    
	//to navigate with the mouse fixed in the middle
	if (mouse_locked)
	{
		int center_x = (int)floor(window_width*0.5f);
		int center_y = (int)floor(window_height*0.5f);
        //center_x = center_y = 50;
		SDL_WarpMouseInWindow(this->window, center_x, center_y); //put the mouse back in the middle of the screen
		//SDL_WarpMouseGlobal(center_x, center_y); //put the mouse back in the middle of the screen
        
        this->mouse_position.x = (float)center_x;
        this->mouse_position.y = (float)center_y;
	}

	//scene->root->children[3]->model.traslate(scene->camera->center.x, scene->camera->center.x, scene->camera->center.z);
	

	scene->update((float)enemySpeed);
	angle += (float)seconds_elapsed * 10;
	for (int m = 3; m < 5; m++) {
		collision = ((GameObjectPlayer*)(scene->root->children[2]))->mesh->collision_model->collision(((GameObjectEnemy*)(scene->root->children[m]))->mesh->collision_model);
		if (collision) { 
			break; 
		}
	}
	final_collision = ((GameObjectPlayer*)(scene->root->children[2]))->mesh->collision_model->collision(((GameObjectMesh*)(scene->root->children[1]))->mesh->collision_model);
	if (collision) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
			"You WIN",
			"You've destroyed your oponent. The asault has been neutralized. CONGRATULATIONS!!",
			NULL);
		exit(0);
	}
	if (final_collision) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
			"Game Over",
			"You've been destroyed.",
			NULL);
		exit(0);
	}
}

//Keyboard event handler (sync input)
void Game::onKeyPressed( SDL_KeyboardEvent event )
{
	switch(event.keysym.sym)
	{
		case SDLK_ESCAPE: exit(0); //ESC key, kill the app
	}
}


void Game::onMouseButton( SDL_MouseButtonEvent event )
{
	if (event.button == SDL_BUTTON_MIDDLE) //middle mouse
	{
		mouse_locked = !mouse_locked;
		SDL_ShowCursor(!mouse_locked);
	}
}

void Game::setWindowSize(int width, int height)
{
    std::cout << "window resized: " << width << "," << height << std::endl;
    
	/*
    Uint32 flags = SDL_GetWindowFlags(window);
    if(flags & SDL_WINDOW_ALLOW_HIGHDPI)
    {
        width *= 2;
        height *= 2;
    }
	*/

	glViewport( 0,0, width, height );
	scene->camera->aspect =  width / (float)height;
	window_width = width;
	window_height = height;
}

