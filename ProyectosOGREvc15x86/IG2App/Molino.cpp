#include "Molino.h"

Molino::Molino(Ogre::SceneNode* node, const int numAspas)
{
	molinoNode = node;
	numAspas_ = numAspas;
	Ogre::SceneManager* mSM = molinoNode->getCreator();
	molinoNode->createChildSceneNode("techo");
	Ogre::Entity* techo = molinoNode->getCreator()->createEntity("sphere.mesh");
	mSM->getSceneNode("techo")->attachObject(techo);
	mSM->getSceneNode("techo")->setScale(0.5, 0.5, 0.5);
	mSM->getSceneNode("techo")->setPosition(0, -5, 0);

	molinoNode->createChildSceneNode("pared");
	Ogre::Entity* pared = molinoNode->getCreator()->createEntity("Barrel.mesh");
	mSM->getSceneNode("pared")->attachObject(pared);
	mSM->getSceneNode("pared")->setScale(25, 25, 25);
	mSM->getSceneNode("pared")->setPosition(0, -50, -25);

	molinoNode->createChildSceneNode("eje");
	Ogre::Entity* eje = molinoNode->getCreator()->createEntity("Barrel.mesh");
	mSM->getSceneNode("eje")->attachObject(eje);
	mSM->getSceneNode("eje")->setScale(15, 30, 15);
	mSM->getSceneNode("eje")->setPosition(0, 0, 0);
	mSM->getSceneNode("eje")->yaw(Degree(90));


	molinoNode->createChildSceneNode("aspas");
	aspasMolino = new AspasMolino(mSM->getSceneNode("aspas"), numAspas_);
}
