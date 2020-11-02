#pragma once
#include <OgreInput.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>

class EntidadIG : public OgreBites::InputListener {
public:
	EntidadIG(Ogre::SceneNode* node);
	~EntidadIG();

	static std::vector<EntidadIG*> appListeners;
	static void addListener(EntidadIG* entidad) {	appListeners.push_back(entidad);	};
	void sendEvent(EntidadIG* entidad);

protected:
	Ogre::SceneNode* mNode;
	Ogre::SceneManager* mSM;

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt) { return false; };
	virtual void frameRendered(const Ogre::FrameEvent& evt) { };
	virtual void receiveEvent(EntidadIG* entidad) { };
};
