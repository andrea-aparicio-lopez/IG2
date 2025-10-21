#pragma once

#include "IG2Object.h"
#include "Constants.h"

#include <vector>
#include <string>

class Labyrinth : public IG2Object {
protected:
	std::vector<std::vector<bool>> walls;
	Vector3 _heroPos; // pos inicial del héroe
	std::vector<Vector3> _villainPos; // pos inicial de los villanos

	std::string _lightType;

public:
	Labyrinth(std::string filename, SceneNode* node, SceneManager* sM);
	~Labyrinth();

	bool isWall(Vector3 pos) const;

	std::string getLightType();

	Vector3 getHeroPos() const;
	std::vector<Vector3> getVillainPos() const;
};