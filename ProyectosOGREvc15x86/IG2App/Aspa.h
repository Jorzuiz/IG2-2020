#pragma once
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <OgreTrays.h>
#include <OgreInput.h>
using namespace Ogre;

class Aspa : public OgreBites::InputListener
{
public:
	
	Aspa(Ogre::SceneNode* node, int i) {

		mNode = node;
		Ogre::SceneManager* mSM = mNode->getCreator();

		tableroNode = mNode->createChildSceneNode("tablero"+ std::to_string(i));
		Ogre::Entity* tabla = mSM->createEntity("cube.mesh");
		tableroNode->attachObject(tabla);
		tableroNode->setScale(3.5, 0.7, 0.1);
		tableroNode->setPosition(0, 0, 0);
		tableroNode->translate(200, 0, 0);

		cilindroNode = mNode->createChildSceneNode("adorno" + std::to_string(i));
		Ogre::Entity* cilindro = mSM->createEntity("Barrel.mesh");
		cilindroNode->attachObject(cilindro);
		cilindroNode->setScale(5, 10, 5);
		cilindroNode->setPosition(0, 0, 0);
		cilindroNode->translate(340, 0, 20);

	};
	~Aspa() {};

	void giro(int i) {
		mSM->getSceneNode("aspa" + std::to_string(i))->roll(Degree(1));
		mSM->getSceneNode("adorno" + std::to_string(i))->roll(Degree(-1));
	};

	/*virtual void frameRendered(const Ogre::FrameEvent& evt);
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	virtual bool keyReleased(const OgreBites::KeyboardEvent& evt);
	virtual bool mousePressed(const OgreBites::MouseButtonEvent& evt);
	virtual bool mouseRelease(const OgreBites::MouseButtonEvent& evt);
	virtual bool mouseMoved(const OgreBites::MouseMotionEvent& evt);
	virtual bool mouseWheelRolled(const OgreBites::MouseWheelEvent& evt);*/

protected:
	Ogre::SceneNode* mNode, *tableroNode, *cilindroNode;
	Ogre::SceneManager* mSM;
};
