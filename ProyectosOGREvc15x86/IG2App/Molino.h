#pragma once
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <OgreTrays.h>
#include <OgreInput.h>
#include <SDL_keycode.h>

#include "AspasMolino.h"
//#include "EntidadIG.h"	// Permite heredar Molino de EntidadIG

using namespace Ogre;

class Molino: public EntidadIG //: public OgreBites::InputListener
{
public:
	Molino(Ogre::SceneNode* node, const int numAspas);
	~Molino();

	void giro();
	void retraEje();
	void giroTop();

protected:
	Ogre::SceneNode* molinoNode, *paredNode, *techoNode, *aspasMolino;
	Ogre::Vector3 const posicionGiro = {0, 170, 140};
	AspasMolino* aspasMolino_;
	int numAspas_;
};

