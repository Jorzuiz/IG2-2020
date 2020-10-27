#pragma once
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <OgreTrays.h>
#include <OgreInput.h>
#include "AspasMolino.h"
using namespace Ogre;
class Molino : public OgreBites::InputListener
{
public:
	Molino(Ogre::SceneNode* node, const int numAspas);

	~Molino() {}

	void giro() {
		aspasMolino->giro();
	}
	void retraEje() {
		molinoNode->getChild("eje")->setPosition(0, 0, -10);//corregir posicion
	}
	void giroTop() {
		// 2 tipos

	}
protected:
	Ogre::SceneNode* molinoNode;
	AspasMolino* aspasMolino;
	int numAspas_;
};

