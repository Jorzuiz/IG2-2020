#include "Aspa.h"

Aspa::Aspa(Ogre::SceneNode* node) : EntidadIG(node) {

	addListener(this);
	mNode = node;
	Ogre::SceneManager* mSM = mNode->getCreator();

	tableroNode = mNode->createChildSceneNode();// "tablero" + std::to_string(i));
	Ogre::Entity* tabla = mSM->createEntity("cube.mesh");
	tabla->setMaterialName("IG2App/marron");
	tableroNode->attachObject(tabla);
	tableroNode->setScale(3.5, 0.7, 0.1);
	tableroNode->setPosition(0, 0, 0);
	tableroNode->translate(200, 0, 0);

	cilindroNode = mNode->createChildSceneNode();// "adorno" + std::to_string(i));
	Ogre::Entity* cilindro = mSM->createEntity("Barrel.mesh");
	cilindro->setMaterialName("IG2App/azul");
	cilindroNode->attachObject(cilindro);
	cilindroNode->setScale(5, 10, 5);
	cilindroNode->setPosition(0, 0, 0);
	cilindroNode->translate(340, 0, 20);

};


void Aspa::giro(Ogre::Real time) {
	mNode->roll(Degree(-100)*time);
	cilindroNode->roll(Degree(100)*time);
}

void Aspa::adornoGone()
{
	adornoV = !adornoV;
	if(adornoV)
		cilindroNode->setVisible(true);
	else
		cilindroNode->setVisible(false);
}
