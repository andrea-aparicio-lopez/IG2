#pragma once

#include "IG2Object.h"

//#ifndef __WALL_H__
//#define __WALL_H__

class Wall: public IG2Object{
public:
    Wall(Vector3 position, SceneNode* node, SceneManager* sM);
};

//#endif // !__WALL_H__