#pragma once
#include "IG2Object.h"
class Bomb: public IG2Object
{
public:
	Bomb(Vector3 position, SceneNode* node, SceneManager* sM);
	~Bomb();

protected:
	IG2Object* _fuse;
};

