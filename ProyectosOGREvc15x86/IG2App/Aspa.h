#pragma once
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <OgreTrays.h>
#include <OgreInput.h>

#include "EntidadIG.h"
using namespace Ogre;

class Aspa : public EntidadIG//OgreBites::InputListener
{
public:

	Aspa(Ogre::SceneNode* node);
	~Aspa() {};

	void giro(Ogre::Real time);
	void adornoGone();
	Ogre::SceneNode* getAdorno() { return cilindroNode; };
	Ogre::SceneNode* getTablero() { return tableroNode; };
	Ogre::SceneNode* getAspa() { return mNode; };

protected:
	Ogre::SceneNode* mNode, *tableroNode, *cilindroNode;
	Ogre::SceneManager* mSM;
	bool adornoV = true;
};
