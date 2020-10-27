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
		molinoNode->getChild("eje")->translate(0, 0, -1); //corregir posicion
	}
	void giroTop() {
		// 2 tipos
		/*
		posicionEje = molinoNode->getChild("eje")->getPosition();	//Brujería
		molinoNode->getChild("eje")->setPosition(0, 0, 0);
		molinoNode->getChild("eje")->yaw(Degree(1), Ogre::Node::TS_PARENT);
		molinoNode->getChild("eje")->translate(posicionEje);

		molinoNode->getChild("aspas")->setPosition(0, 0, 0);
		molinoNode->getChild("aspas")->yaw(Degree(1));
		molinoNode->getChild("aspas")->translate(posicionGiro); */
		//molinoNode->yaw(Degree(-1));
	}
protected:
	Ogre::SceneNode* molinoNode;
	Ogre::Vector3 const posicionGiro = {0, 170, 140};
	Ogre::Vector3 posicionEje;
	AspasMolino* aspasMolino;
	int numAspas_;
};

