#pragma once
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <OgreTrays.h>
#include <OgreInput.h>
#include "Aspa.h"

using namespace Ogre;

class AspasMolino: public EntidadIG
{
public:
	AspasMolino(Ogre::SceneNode* node, const int numAspa);
	~AspasMolino() {}

	void giro();
	void retraEje();

protected:
	Ogre::SceneNode* aspasNode, *ejeNode, *aspa;
	Aspa **arrayAspas;
	int numAspas;
};

