#pragma once
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <OgreTrays.h>
#include <OgreInput.h>
#include "AspasMolino.h"
using namespace Ogre;
class Avion : public OgreBites::InputListener
{
public:
	Avion(Ogre::SceneNode* node, const int numAspas){
		AvionNode = node;
		numAspas_ = numAspas;
		Ogre::SceneManager* mSM = AvionNode->getCreator();
		// Esfera del cuerpo del avion
		AvionNode->createChildSceneNode("cuerpoNode");
		Ogre::Entity* cuerpoNode = AvionNode->getCreator()->createEntity("sphere.mesh");
		mSM->getSceneNode("cuerpoNode")->attachObject(cuerpoNode);
		mSM->getSceneNode("cuerpoNode")->setScale(1, 1, 1);
		// Ala izquierda
		AvionNode->createChildSceneNode("alaINode");
		Ogre::Entity* alaINode = AvionNode->getCreator()->createEntity("cube.mesh");
		mSM->getSceneNode("alaINode")->attachObject(alaINode);
		mSM->getSceneNode("alaINode")->setScale(3, 0.2, 1);
		mSM->getSceneNode("alaINode")->translate(-150, 0, 0, Ogre::Node::TS_LOCAL);
		// Ala derecha
		AvionNode->createChildSceneNode("alaDNode");
		Ogre::Entity* alaDNode = AvionNode->getCreator()->createEntity("cube.mesh");
		mSM->getSceneNode("alaDNode")->attachObject(alaDNode);
		mSM->getSceneNode("alaDNode")->setScale(3, 0.2, 1);
		mSM->getSceneNode("alaDNode")->translate(150, 0, 0, Ogre::Node::TS_LOCAL);
		// Morro
		AvionNode->createChildSceneNode("frenteNode");
		Ogre::Entity* frenteNode = AvionNode->getCreator()->createEntity("Barrel.mesh");
		mSM->getSceneNode("frenteNode")->attachObject(frenteNode);
		mSM->getSceneNode("frenteNode")->setScale(10, 10, 10);
		mSM->getSceneNode("frenteNode")->pitch(Degree(90), Ogre::Node::TS_LOCAL);
		mSM->getSceneNode("frenteNode")->translate(0, 100, 0, Ogre::Node::TS_LOCAL);
		// Piloto NINJA
		AvionNode->createChildSceneNode("pilotoNode");
		Ogre::Entity* pilotoNode = AvionNode->getCreator()->createEntity("ninja.mesh");
		mSM->getSceneNode("pilotoNode")->attachObject(pilotoNode);
		mSM->getSceneNode("pilotoNode")->setScale(1, 1, 1);
		mSM->getSceneNode("pilotoNode")->translate(0, -50, 0, Ogre::Node::TS_LOCAL);
		mSM->getSceneNode("pilotoNode")->yaw(Degree(180), Ogre::Node::TS_LOCAL);
		// Aspa IZQ
		AvionNode->createChildSceneNode("aspas1");
		aspasMolino1 = new AspasMolino(mSM->getSceneNode("aspas1"), numAspas_);
		mSM->getSceneNode("aspas1")->setPosition(0, -100, 0);
		// Aspa DER
		//AvionNode->createChildSceneNode("aspas2");
		//aspasMolino2 = new AspasMolino(mSM->getSceneNode("aspas2"), numAspas_);
		//mSM->getSceneNode("aspas2")->setPosition(0, 100, 0);
	}
	~Avion() {}
protected:
	Ogre::SceneNode* AvionNode;
	AspasMolino* aspasMolino1;
	AspasMolino* aspasMolino2;
	int numAspas_;
};

