#pragma once

#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
using namespace Ogre;

class EntityIG: public OgreBites::InputListener
{
public:
	SceneNode* mNode;
	SceneManager* mSM;
};

