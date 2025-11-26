#pragma once
#include "ExplosionSmoke.h"
#include <OgreFrameListener.h>

class Labyrinth;

class SmokePool : public OgreBites::InputListener
{
public:
	SmokePool(Ogre::SceneNode* node, SceneManager* sm, Labyrinth* lab);
	~SmokePool();

	virtual void frameRendered(const Ogre::FrameEvent& evt) override;

	void placeAllSmokes(Ogre::Vector3 pos);

protected:
	void placeSmoke(Ogre::Vector3 pos);
	void clearSmoke(int index);


protected:
	std::vector<ExplosionSmoke*> _mySmoke;
	int _poolIndex; // primera bomba libre

	SceneManager* _mSM;
	Labyrinth* _lab;
};

