#pragma once
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <OgreTrays.h>
#include <OgreInput.h>
#include "EntidadIG.h"
#include <iostream>
#include <string>
#include <OgreSkeletonInstance.h>
#include <OgreBone.h>
#include <SDL_keycode.h>
#include <OgreAnimation.h>
#include <OgreKeyFrame.h>
#include <OgreAnimationState.h>
#include <OgreAnimationTrack.h>

#include <iostream>
#include <vector>
using namespace Ogre;
class Simbad : public EntidadIG
{
public:
	Simbad(Ogre::SceneNode* node);
	bool keyPressed(const OgreBites::KeyboardEvent& evento);
	void frameRendered(const Ogre::FrameEvent& evento);
	void receiveEvent(EntidadIG* entidad,string mensaje);

protected:
	void StopAnim();
	Ogre::SceneNode* Simbad_;
	bool anim = true;
	bool paseo = false;
	bool muerte = false;
	Ogre::Real scale = 20;
	
	std::vector<AnimationState*> animationsSinbad_;
	Ogre::Entity* ent;
	Ogre::Entity* sword1_ = nullptr;
	Ogre::Entity* sword2_ = nullptr;

	Ogre::SceneNode* sword1Node = nullptr;
	Ogre::SceneNode* sword2Node = nullptr;

	// Animation 1
	Ogre::AnimationState* walking;
	Ogre::NodeAnimationTrack* track;
	Ogre::Animation* SimbadAnim;

	Ogre::AnimationState* dead;
	Ogre::NodeAnimationTrack* trackMuerte;
	Ogre::Animation* SimbadAnimM;
	Ogre::Quaternion aaa;

	Ogre::Vector3 keyframePos;
	Ogre::Vector3 desplazamiento;
	Ogre::Vector3 orientation;
	Ogre::Vector3 destino;
	//AnimationState* animationState;
	const Ogre::Real duration = 21;
};

	/*Dance			0
	DrawSwords
	HandsClosed
	HandsRelaxed
	IdleBase
	IdleTop			5
	JumpEnd
	JumpLoop
	JumpStart
	RunBase
	RunTop			10
	SliceHorizontal
	SliceVertical*/
