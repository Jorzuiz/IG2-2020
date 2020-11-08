#pragma once
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <OgreTrays.h>
#include <OgreInput.h>
#include "EntidadIG.h"
class Simbad : public EntidadIG
{
public:
	Simbad(Ogre::SceneNode* node) :EntidadIG(node) {
		addListener(this);
		Simbad_ = node;
		Ogre::Entity* ent = mSM->createEntity("Sinbad.mesh");

		Simbad_ = mSM->getRootSceneNode()->createChildSceneNode("nSinbad");
		Simbad_->attachObject(ent);

		Simbad_->setPosition(-400, 100, 300);
		Simbad_->setScale(20, 20, 20);
	}
protected:
	Ogre::SceneNode* Simbad_;
};

