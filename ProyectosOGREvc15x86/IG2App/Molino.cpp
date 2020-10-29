#include "Molino.h"

Molino::Molino(Ogre::SceneNode* node, const int numAspas)
{
	molinoNode = node;
	numAspas_ = numAspas;
	Ogre::SceneManager* mSM = molinoNode->getCreator();

	techoNode = molinoNode->createChildSceneNode();
	Ogre::Entity* techo = mSM->createEntity("sphere.mesh");
	techoNode->attachObject(techo);
	techoNode->setScale(1.25, 1.25, 1.25);
	techoNode->setPosition(0, 170, 0);

	paredNode = molinoNode->createChildSceneNode();
	Ogre::Entity* pared = mSM->createEntity("Barrel.mesh");
	paredNode->attachObject(pared);
	paredNode->setScale(50, 60, 50);
	paredNode->setPosition(0, 0, 0);

	aspasMolino = molinoNode->createChildSceneNode();		// Esto es nodo
	aspasMolino_ = new AspasMolino(aspasMolino, numAspas_);	// Esto es creadora de clase
	aspasMolino->setPosition(0, 170, 140);
	
}
