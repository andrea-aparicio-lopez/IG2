#pragma once

#include "IG2Object.h"
#include "Constants.h"

#include <vector>

class Labyrinth : public IG2Object {
private:
	std::vector<std::vector<bool>> walls;
	

public:
	Labyrinth(std::string filename, SceneNode* node, SceneManager* sM);
	~Labyrinth();

	bool isWall(Vector2i position);
};