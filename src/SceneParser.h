#pragma once

#include "includes.h"
#include <string>
#include "mesh.h"
#include "texture.h"
#include "shader.h"
#include "extra\textparser.h"

class SceneParser
{
public:
	SceneParser();

	void parse(const char*);
};
