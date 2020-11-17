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
using namespace Ogre;
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

		
		Ogre::AnimationStateSet* aux = ent->getAllAnimationStates();
		auto it = aux->getAnimationStateIterator().begin();

		int cont = 0;
		while (it != aux->getAnimationStateIterator().end()) {
			auto s = it->first;
			++it;
			std::cout << " Sinbad Animation " << cont << ": " << s << "\n";
			animationsSinbad_.push_back(ent->getAnimationState(s));
			++cont;
		}

		auto skeleton = ent->getSkeleton();
		auto numBones = skeleton->getNumBones();
		for (cont = 0; cont < numBones; cont++) {
			std::cout << " Sinbad Bone " << cont << ": " << skeleton->getBone(cont)->getName() << "\n";
		}

		animationsSinbad_.at(0)->setEnabled(anim);
		animationsSinbad_.at(0)->setLoop(anim);

		// ESPADAS
		// Espada 1
		sword1_ = mSM->createEntity("Sword.mesh");
		sword1Node = Simbad_->createChildSceneNode("sword1");
		
		// Espada 2
		sword2_ = mSM->createEntity("Sword.mesh");
		sword2Node = Simbad_->createChildSceneNode("sword2");		

		ent->attachObjectToBone("Sheath.L", sword1_);
		ent->attachObjectToBone("Sheath.R", sword2_);

	}
	bool keyPressed(const OgreBites::KeyboardEvent& evento);
	void frameRendered(const Ogre::FrameEvent& evento);
	void receiveEvent(EntidadIG* entidad,string mensaje);

protected:
	void StopAnim();
	Ogre::SceneNode* Simbad_;
	bool anim = true;
	std::vector<AnimationState*> animationsSinbad_;
	Ogre::Entity* ent;
	Ogre::Entity* sword1_ = nullptr;
	Ogre::Entity* sword2_ = nullptr;

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
