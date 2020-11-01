#pragma once
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <OgreTrays.h>
#include <OgreInput.h>

#include "EntidadIG.h"
using namespace Ogre;

class Aspa : public EntidadIG//OgreBites::InputListener
{
public:
	
	Aspa(Ogre::SceneNode* node):EntidadIG(node){

		mNode = node;
		Ogre::SceneManager* mSM = mNode->getCreator();

		tableroNode = mNode->createChildSceneNode();// "tablero" + std::to_string(i));
		Ogre::Entity* tabla = mSM->createEntity("cube.mesh");
		tableroNode->attachObject(tabla);
		tableroNode->setScale(3.5, 0.7, 0.1);
		tableroNode->setPosition(0, 0, 0);
		tableroNode->translate(200, 0, 0);

		cilindroNode = mNode->createChildSceneNode();// "adorno" + std::to_string(i));
		Ogre::Entity* cilindro = mSM->createEntity("Barrel.mesh");
		cilindroNode->attachObject(cilindro);
		cilindroNode->setScale(5, 10, 5);
		cilindroNode->setPosition(0, 0, 0);
		cilindroNode->translate(340, 0, 20);

	};
	~Aspa() {};

	void giro() {
		mNode->roll(Degree(-1));
		cilindroNode->roll(Degree(1));
	};

	Ogre::SceneNode* getAdorno() {	return cilindroNode;	};
	Ogre::SceneNode* getTablero() {	return tableroNode;	};
	Ogre::SceneNode* getAspa() {	return mNode;	}; 
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evento);
	virtual void frameRendered(const Ogre::FrameEvent& evento);
	virtual void receiveEvent(EntidadIG* entidad) { };

protected:
	Ogre::SceneNode* mNode, *tableroNode, *cilindroNode;
	Ogre::SceneManager* mSM;
};
