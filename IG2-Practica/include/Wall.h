#pragma once

#include "IG2Object.h"

class Wall: public IG2Object{
public:
    Wall(Vector3 position, SceneNode* node, SceneManager* sM);
};