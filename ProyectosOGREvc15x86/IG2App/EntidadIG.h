#pragma once
#include <OgreInput.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>
#include <SDL_keycode.h>
#include <string>

using namespace std;
class EntidadIG : public OgreBites::InputListener {
public:
	EntidadIG(Ogre::SceneNode* node);
	~EntidadIG();

	static std::vector<EntidadIG*> appListeners;
	static void addListener(EntidadIG* entidad) {	appListeners.push_back(entidad);	};

protected:
	Ogre::SceneNode* mNode;
	Ogre::SceneManager* mSM;

	virtual void frameRendered(const Ogre::FrameEvent& evt);
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) { return false; };

	void sendEvent(EntidadIG* entidad, string mensaje);
	virtual void receiveEvent(EntidadIG* entidad, string mensaje) {};
	 
};
