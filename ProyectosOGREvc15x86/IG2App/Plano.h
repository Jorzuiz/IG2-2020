#pragma once
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <OgreTrays.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include <string>

#include "EntidadIG.h"
using namespace Ogre;
using namespace std;

class Plano : public EntidadIG
{
public:
	Plano(SceneNode* node, std::string plano);
	~Plano() {};
	bool keyPressed(const OgreBites::KeyboardEvent& evt);
	void receiveEvent(EntidadIG* entidad, string mensaje);
	
protected:
	SceneNode* PlanoNode_;
	Ogre::Entity* plane = nullptr;
	string plano;
};

