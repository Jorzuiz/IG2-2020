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
	Molino(Ogre::SceneNode* node,const int numAspas) {
		molinoNode = node;
		numAspas_ = numAspas;
		Ogre::SceneManager* mSM = molinoNode->getCreator();
		molinoNode->createChildSceneNode("techo");
		Ogre::Entity* techo = molinoNode->getCreator()->createEntity("sphere.mesh");
		mSM->getSceneNode("techo")->attachObject(techo);
		mSM->getSceneNode("techo")->setScale(50, 50, 50);
		mSM->getSceneNode("techo")->setPosition(0, -50, 0);

		molinoNode->createChildSceneNode("pared");
		Ogre::Entity* pared = molinoNode->getCreator()->createEntity("barrel.mesh");
		mSM->getSceneNode("pared")->attachObject(pared);
		mSM->getSceneNode("pared")->setScale(50, 100, 50);
		mSM->getSceneNode("pared")->setPosition(0, -50, -25);

		molinoNode->createChildSceneNode("eje");
		Ogre::Entity* eje = molinoNode->getCreator()->createEntity("barrel.mesh");
		mSM->getSceneNode("eje")->attachObject(eje);
		mSM->getSceneNode("eje")->setScale(15, 30, 15);
		mSM->getSceneNode("eje")->setPosition(0, 0, 0);
		mSM->getSceneNode("eje")->yaw(Degree(90));


		molinoNode->createChildSceneNode("aspas");		
		aspasMolino = new AspasMolino(mSM->getSceneNode("aspas"), numAspas_);		

	}

	~Molino() {}

	void giro() {
		aspasMolino->giro();
	}
	void retraEje() {
		molinoNode->getChild("eje")->setPosition(0, 0, -1);
	}
	void giroTop() {
		// 2 tipos

	}
protected:
	Ogre::SceneNode* molinoNode, aspasMolinoNode;
	AspasMolino* aspasMolino;
	int numAspas_;
};

