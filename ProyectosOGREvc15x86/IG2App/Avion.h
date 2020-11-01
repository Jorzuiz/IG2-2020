#pragma once
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <OgreTrays.h>
#include <OgreInput.h>
#include "AspasMolino.h"
#include "EntidadIG.h"
using namespace Ogre;
class Avion : public EntidadIG
{
public:
	Avion(Ogre::SceneNode* node, const int numAspas) :EntidadIG(node) {
		AvionNode = node;
		numAspas_ = numAspas;

		Ogre::SceneManager* mSM = AvionNode->getCreator();
		// Esfera del cuerpo del avion
		cuerpoNode = AvionNode->createChildSceneNode();
		Ogre::Entity* cuerpo= AvionNode->getCreator()->createEntity("sphere.mesh");
		cuerpoNode->attachObject(cuerpo);
		cuerpoNode->setScale(1, 1, 1);
		// Ala izquierda
		alaINode = AvionNode->createChildSceneNode();
		Ogre::Entity* alaI = AvionNode->getCreator()->createEntity("cube.mesh");
		alaINode->attachObject(alaI);
		alaINode->setScale(3, 0.2, 1);
		alaINode->translate(-150, 0, 0, Ogre::Node::TS_LOCAL);
		// Ala derecha
		alaDNode = AvionNode->createChildSceneNode();
		Ogre::Entity* alaD = AvionNode->getCreator()->createEntity("cube.mesh");
		alaDNode->attachObject(alaD);
		alaDNode->setScale(3, 0.2, 1);
		alaDNode->translate(150, 0, 0, Ogre::Node::TS_LOCAL);
		// Morro
		frenteNode = AvionNode->createChildSceneNode();
		Ogre::Entity* frente = AvionNode->getCreator()->createEntity("Barrel.mesh");
		frenteNode->attachObject(frente);
		frenteNode->setScale(10, 10, 10);
		frenteNode->pitch(Degree(90), Ogre::Node::TS_LOCAL);
		frenteNode->translate(0, 100, 0, Ogre::Node::TS_LOCAL);
		// Piloto NINJA
		pilotoNode = AvionNode->createChildSceneNode();
		Ogre::Entity* piloto= AvionNode->getCreator()->createEntity("ninja.mesh");
		pilotoNode->attachObject(piloto);
		pilotoNode->setScale(1, 1, 1);
		pilotoNode->translate(0, -50, 0, Ogre::Node::TS_LOCAL);
		pilotoNode->yaw(Degree(180), Ogre::Node::TS_LOCAL);
		// Aspa IZQ
		aspas1 = AvionNode->createChildSceneNode();
		aspasMolino1 = new AspasMolino(aspas1, numAspas_);
		aspas1->setPosition(-250, 0, 55);
		aspas1->setScale(0.3, 0.3, 0.3);
		// Aspa DER
		aspas2 = AvionNode->createChildSceneNode();
		aspasMolino2 = new AspasMolino(aspas2, numAspas_);
		aspas2->setPosition(250, 0, 55);
		aspas2->setScale(0.3, 0.3, 0.3);
	}
	~Avion() {}

	void giro() {
			aspasMolino1->giro();
			aspasMolino2->giro();
	}
	void retraEje() {
		aspasMolino1->retraEje();
		aspasMolino2->retraEje();
	}
protected:
	Ogre::SceneNode* AvionNode, *cuerpoNode, *alaINode, *alaDNode, 
	*frenteNode, *pilotoNode, *aspas1, *aspas2;
	AspasMolino* aspasMolino1;
	AspasMolino* aspasMolino2;
	int numAspas_;
};

