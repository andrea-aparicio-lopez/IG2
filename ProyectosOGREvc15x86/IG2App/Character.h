#pragma once

#include <array>
#include "IG2Object.h"
#include "Constants.h"
class Labyrinth;



class Character : public IG2Object
{
public:
	Character(Vector3 position, SceneNode* node, SceneManager* sM, Labyrinth* lab, std::string mesh);
	~Character();


protected:
	std::array<Vector3, 4> directions = { 
		Vector3(0,0,-1),	// up
		Vector3(-1,0,0),	// left
		Vector3(0,0,1),		// down
		Vector3(1,0,0)		// right
	};

	Vector3 dir = {0,0,1};
	Vector3 nextDir = {0,0,1};

	Labyrinth* lab;

public:
	void setNewDir(Vector3 const& nDir);
	virtual void frameRendered(const Ogre::FrameEvent& evt) override;

	virtual void moveCharacter(double dt);
	void turnCharacter();

};

