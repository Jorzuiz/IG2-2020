#pragma once
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <OgreTrays.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include <string>
#include <OgreViewport.h>
#include <OgreRenderTexture.h>
#include <OgreMovablePlane.h>
#include "IG2ApplicationContext.h"

#include "EntidadIG.h"
using namespace Ogre;
using namespace OgreBites;
using namespace std;

class Plano : public EntidadIG
{
public:
	Plano(SceneNode* node, std::string plano);
	Plano(SceneNode* node, Camera* cam, Ogre::RenderWindow* render);	// Constructora para el plano con reflejo
	~Plano() {
		if (mpRef != nullptr) {
			delete mpRef;
			mpRef = nullptr;
		}
	};

	bool keyPressed(const OgreBites::KeyboardEvent& evt);
	void receiveEvent(EntidadIG* entidad, string mensaje);
	
protected:
	SceneNode* PlanoNode_;
	Ogre::Entity* plane = nullptr;
	string plano;
	Ogre::MovablePlane* mpRef;
};

