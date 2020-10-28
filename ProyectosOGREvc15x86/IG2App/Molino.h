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

	~Molino() {
		delete aspasMolino;
		aspasMolino = nullptr;
	}

	void giro() {
		aspasMolino->giro();
	}
	void retraEje() {
		molinoNode->getChild("aspas")->getChild("eje")->translate(0, -1, 0, Ogre::Node::TS_LOCAL);
	}
	void giroTop() {
				
		molinoNode->getChild("aspas")->translate(-posicionGiro, Ogre::Node::TS_LOCAL);
		molinoNode->getChild("aspas")->yaw(Degree(1));
		molinoNode->getChild("aspas")->translate(posicionGiro, Ogre::Node::TS_LOCAL);
		
	}
protected:
	Ogre::SceneNode* molinoNode;
	Ogre::Vector3 const posicionGiro = {0, 170, 140};
	AspasMolino* aspasMolino;
	int numAspas_;
};

