#pragma once
#include "EntidadIG.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <OgreTrays.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreAnimation.h>
#include <OgreAnimationState.h>
#include <OgreAnimationTrack.h>
#include <OgreKeyFrame.h>

using namespace Ogre;

class Boya : public EntidadIG
{
public:
	Boya(Ogre::SceneNode* node);
	~Boya() {};
	void frameRendered(const Ogre::FrameEvent& evt);
protected:
	Ogre::SceneNode* BoyaNode_;
	Ogre::Entity* ent;
	Ogre::Animation* animation;
	NodeAnimationTrack* track;
	Ogre::Vector3 keyframePos;
	Ogre::Vector3 desplazamiento;
	Ogre::Vector3 orientation;
	Ogre::Vector3 destino;
	AnimationState* animationState;
};	
