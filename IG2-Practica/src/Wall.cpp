#include "Wall.h"

Wall::Wall(Vector3 pos, SceneNode* mazeNode, SceneManager* sM):IG2Object(pos, mazeNode->createChildSceneNode(), sM, "cube.mesh"){

}