#pragma once
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <OgreTrays.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>

#include "EntidadIG.h"
using namespace Ogre;

class Plano : public EntidadIG
{
public:
	Plano(SceneNode* node);
	~Plano() {};
protected:
	SceneNode* PlanoNode_;

};

