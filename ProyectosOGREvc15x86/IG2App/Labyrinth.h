#pragma once

#include "IG2Object.h"
#include "Constants.h"

#include <vector>

class Labyrinth : public IG2Object {
protected:
	std::vector<std::vector<bool>> walls;
	Vector3 _heroPos; // pos inicial del héroe

public:
	Labyrinth(std::string filename, SceneNode* node, SceneManager* sM);
	~Labyrinth();

	bool isWall(Vector3 pos) const;

	Vector3 getHeroPos() const;
};