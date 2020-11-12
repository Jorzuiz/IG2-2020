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
#include<OgreAnimation.h>
#include <OgreKeyFrame.h>

#include <iostream>
#include <vector>
class Simbad : public EntidadIG
{
public:
	Simbad(Ogre::SceneNode* node) :EntidadIG(node) {
		addListener(this);
		Simbad_ = node;
		ent = mSM->createEntity("Sinbad.mesh");

		Simbad_ = mSM->getRootSceneNode()->createChildSceneNode("nSinbad");
		Simbad_->attachObject(ent);

		Simbad_->setPosition(-400, 100, 300);
		Simbad_->setScale(20, 20, 20);

		AnimationStateSet* aux = ent->getAllAnimationStates();
		auto it = aux->getAnimationStateIterator().begin();
		while (it != aux->getAnimationStateIterator().end())
		{
			auto s = it->first; 
			cout << s << endl;
			++it;
		}
		////////////////////////////////////
		/*Ogre::AnimationStateSet* aux = Simbad_->getAllAnimationStates();
		auto it = aux->getAnimationStateIterator().begin();

		int cont = 0;
		while (it != aux->getAnimationStateIterator().end()) {
			auto s = it->first;
			++it;
			std::cout << " Sinbad Animation " << cont << ": " << s << "\n";
			animationsSinbad_.push_back(Simbad_->getAnimationState(s));
			++cont;
		}
		/*
		auto skeleton = Simbad_->getSkeleton();
		auto numBones = skeleton->getNumBones();
		for (cont = 0; cont < numBones; cont++) {
			std::cout << " Sinbad Bone " << cont << ": " << skeleton->getBone(cont)->getName() << "\n";
		}*/
		////////////////////////////////////////
	}
	bool keyPressed(const OgreBites::KeyboardEvent& evento);
	void frameRendered(const Ogre::FrameEvent& evento);
	void receiveEvent(EntidadIG* entidad,string mensaje);
protected:
	Ogre::SceneNode* Simbad_;
	/// 
	std::vector<Ogre::AnimationState*> animationsSinbad_;
	Ogre::Entity* ent;
	Ogre::SceneNode* sword1Node = nullptr;
	Ogre::SceneNode* sword2Node = nullptr;

	// Animation 1
	Ogre::AnimationState* animationState;
	Ogre::NodeAnimationTrack* track;
	Ogre::Animation* animation;

	Ogre::Vector3 keyframePos;
	Ogre::Vector3 desplazamiento;

	Ogre::Vector3 orientation;
	Ogre::Vector3 destino;

	const Ogre::Real duration = 20;
};

