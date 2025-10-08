#include "Hero.h"
#include "Constants.h"
#include "Labyrinth.h"

Hero::Hero(Vector3 position, SceneNode* node, SceneManager* sM) 
: IG2Object(position, node->createChildSceneNode(), sM, "Sinbad.mesh")
{
	entity->getParentSceneNode()->_update(true, true);

	auto s = getAABB().getSize();
	s = cte::SCALE_HERO / s ;
	setScale(s);
}

Hero::~Hero() {

}

void Hero::setNewDir(Vector2 const& nDir) {
	nextDir = nDir;
}

void Hero::moveHero() {
	// checkear colision
	Vector3 nextPos = getPosition() + Vector3(dir.x, 0, dir.y) * cte::HERO_VEL;
	nextPos /= cte::SCALE_CUBE;

	Vector2i nextBoardPos((int)nextPos.x, (int)nextPos.z);

	if (!lab->isWall(nextBoardPos)) {
		IG2Object::move(cte::HERO_VEL * Vector3(dir.x, 0, dir.y));
	}

	// mover en el mundo
	// actualizar posicion casillas
}

bool Hero::keyPressed(const OgreBites::KeyboardEvent& evt) {
	dir = { 0,0 };
	switch (evt.keysym.sym) {
		case SDLK_UP:
			dir.y = 1;
			break;
		case SDLK_DOWN:
			dir.y = -1;
			break;
		case SDLK_LEFT:
			dir.x = -1;
			break;
		case SDLK_RIGHT:
			dir.x = 1;
			break;
	}

	return true;
}