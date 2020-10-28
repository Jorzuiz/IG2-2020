#pragma once
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <OgreTrays.h>
#include <OgreInput.h>
#include "Aspa.h"
using namespace Ogre;

class AspasMolino: public OgreBites::InputListener
{
public:
	AspasMolino(Ogre::SceneNode* node, const int numAspa) {
		
		aspasNode = node;
		Ogre::SceneManager* mSM = aspasNode->getCreator();
		numAspas = numAspa;
		arrayAspas = new Aspa*[numAspas];	//Damos el tamaño al array de aspas dinamico
		//introduce en el array punteros de aspa, reservando espacio de tamaño aspa
		aspasNode->createChildSceneNode("eje");		
		Ogre::Entity* eje_ = aspasNode->getCreator()->createEntity("Barrel.mesh");
		mSM->getSceneNode("eje")->attachObject(eje_);
		mSM->getSceneNode("eje")->setScale(15, 30, 15);		
		mSM->getSceneNode("eje")->pitch(Degree(90));

		for (int i = 0; i < numAspas; i++) {

			aspasNode->createChildSceneNode("aspa" + std::to_string(i)); //crea X nodos para las aspas
			arrayAspas[i] = new Aspa(mSM->getSceneNode("aspa" + std::to_string(i)), i); //asigna los punteros y crea las instancias

			mSM->getSceneNode("aspa" + std::to_string(i))->roll(Degree((360 / numAspas) * i));
			mSM->getSceneNode("adorno" + std::to_string(i))->roll(Degree(-(360 / numAspas) * i));

			/*aspasNode->createChildSceneNode("aspa_" + std::to_string(i));
			
			aspasNode->getChild("aspa_" + std::to_string(i))->createChild("tablero_" + std::to_string(i));
			Ogre::Entity* tabla = aspasNode->getCreator()->createEntity("cube.mesh");
			mSM->getSceneNode("tablero_" + std::to_string(i))->attachObject(tabla);
			mSM->getSceneNode("tablero_" + std::to_string(i))->setScale(3.5, 0.7, 0.1);
			mSM->getSceneNode("tablero_" + std::to_string(i))->setPosition(0, 0, 0);
			mSM->getSceneNode("tablero_" + std::to_string(i))->translate(200, 0, 0);

			mSM->getSceneNode("aspa_" + std::to_string(i))->createChildSceneNode("adorno_" + std::to_string(i));
			Ogre::Entity* cilindro = mSM->createEntity("Barrel.mesh");
			mSM->getSceneNode("adorno_" + std::to_string(i))->attachObject(cilindro);
			mSM->getSceneNode("adorno_" + std::to_string(i))->setScale(5, 10, 5);
			mSM->getSceneNode("adorno_" + std::to_string(i))->setPosition(0, 0, 0);
			mSM->getSceneNode("adorno_" + std::to_string(i))->translate(340, 0, 20);

			mSM->getSceneNode("aspa_" + std::to_string(i))->roll(Degree((360 / numAspas) * i));
			mSM->getSceneNode("adorno_" + std::to_string(i))->roll(Degree(-(360 / numAspas) * i));*/
		}
	}
	~AspasMolino() {}

	void giro() {
		for (int i = 0; i < numAspas; i++)
		{
			arrayAspas[i]->giro(i);
		}
	}

protected:
	Ogre::SceneNode* aspasNode;
	Aspa **arrayAspas;
	int numAspas;
};

