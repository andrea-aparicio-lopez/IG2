#pragma once

#include "IG2Object.h"

#include <vector>

class Labyrinth : public IG2Object {
private:
	const int SCALE = 100;

public:
	Labyrinth(std::string filename, SceneNode* node, SceneManager* sM);
	~Labyrinth();

	std::vector<std::vector<bool>> walls;

};