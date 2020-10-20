#pragma once
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <OgreTrays.h>
#include <OgreInput.h>
using namespace Ogre;

class AspasMolino: public OgreBites::InputListener
{
public:
	AspasMolino(Ogre::SceneNode* node, int numAspas) {
		aspasNode = node;
		//aspasNode->createChildSceneNode("aspas");
		for (int i = 0; i < numAspas; i++) {
			aspasNode->createChildSceneNode("aspa_" + std::to_string(i));
			
			aspasNode->getChild("aspa_" + std::to_string(i))->createChild("tablero_" + std::to_string(i));
			Ogre::Entity* tabla = aspasNode->getCreator()->createEntity("cube.mesh");
			aspasNode->attachObject(tabla);//getChild("aspa_" + std::to_string(i))->getChild("tablero_" + std::to_string(i))->attachObject(tabla);
			aspasNode->getChild("aspa_" + std::to_string(i))->getChild("tablero_" + std::to_string(i))->setScale(3.5, 0.7, 0.1);
			aspasNode->getChild("aspa_" + std::to_string(i))->getChild("tablero_" + std::to_string(i))->setPosition(0, 0, 0);
			aspasNode->getChild("aspa_" + std::to_string(i))->getChild("tablero_" + std::to_string(i))->translate(200, 0, 0);

			aspasNode->getSceneNode("aspa_" + std::to_string(i))->createChildSceneNode("adorno_" + std::to_string(i));
			Ogre::Entity* cilindro = aspasNode->createEntity("Barrel.mesh");
			aspasNode->getSceneNode("adorno_" + std::to_string(i))->attachObject(cilindro);
			aspasNode->getSceneNode("adorno_" + std::to_string(i))->setScale(5, 10, 5);
			aspasNode->getSceneNode("adorno_" + std::to_string(i))->setPosition(0, 0, 0);
			aspasNode->getSceneNode("adorno_" + std::to_string(i))->translate(340, 0, 20);

			aspasNode->getSceneNode("aspa_" + std::to_string(i))->roll(Degree((360 / 12) * i));
			aspasNode->getSceneNode("adorno_" + std::to_string(i))->roll(Degree(-(360 / 12) * i));
		}
	}
	~AspasMolino();
protected:
	Ogre::SceneNode* aspasNode;
	int numAspas;
};

