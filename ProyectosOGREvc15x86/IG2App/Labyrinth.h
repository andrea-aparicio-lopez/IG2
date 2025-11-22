#pragma once

#include "IG2Object.h"
#include "Constants.h"

#include <vector>
#include <string>

class Wall;

class Labyrinth : public IG2Object {
protected:

	enum SquareType {
		EMPTY, WALL, BOMB
	};

	std::vector<std::vector<SquareType>> walls;
	std::vector<Wall*> _wallEntities;
	IG2Object* _plane;

	Vector3 _heroPos; // pos inicial del héroe
	std::vector<Vector3> _villainPos; // pos inicial de los villanos
	std::vector<Vector3> _megaVillainPos; // pos inicial de los mega villanos

	std::string _lightType;

	Vector2 labSize;

public:
	Labyrinth(std::string filename, SceneNode* node, SceneManager* sM);
	~Labyrinth();

	bool isWall(Vector3 pos) const;

	void setBomb(Vector2 pos);
	void removeBomb(Vector2 pos);
	bool hasBomb(Vector2 pos)const;

	std::string getLightType();

	Vector3 getHeroPos() const;
	std::vector<Vector3> getVillainPos() const;
	std::vector<Vector3> getMegaVillainPos() const;

	inline Vector2 getLabyrinthSize() { return labSize; }
};