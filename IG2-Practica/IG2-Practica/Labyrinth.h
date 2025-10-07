#pragma once

#include "IG2Object.h"
#include "Constants.h"

#include <vector>

class Labyrinth : public IG2Object {
private:
	

public:
	Labyrinth(std::string filename, SceneNode* node, SceneManager* sM);
	~Labyrinth();

	std::vector<std::vector<bool>> walls;

};