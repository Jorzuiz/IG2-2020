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
		delete aspasMolino_;
		aspasMolino_ = nullptr;
	}

	void giro() {
		aspasMolino_->giro();
	}

	void retraEje() {
		aspasMolino_->retraEje();// getEje()->translate(0, -1, 0, Ogre::Node::TS_LOCAL);
	}

	void giroTop() {
		aspasMolino->translate(-posicionGiro, Ogre::Node::TS_LOCAL);
		aspasMolino->yaw(Degree(1));
		aspasMolino->translate(posicionGiro, Ogre::Node::TS_LOCAL);
	}

protected:
	Ogre::SceneNode* molinoNode, *paredNode, *techoNode, *aspasMolino;
	Ogre::Vector3 const posicionGiro = {0, 170, 140};
	AspasMolino* aspasMolino_;
	int numAspas_;
};

